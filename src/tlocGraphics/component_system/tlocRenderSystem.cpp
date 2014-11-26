#include "tlocRenderSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/tlocAlgorithms.h>

#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocVertexArrayObject.h>
#include <tlocGraphics/component_system/tlocCamera.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocSceneNode.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace {

    math_t::Mat3f32
      DoInvertOrIdentity(const math_t::Mat3f32& a_mat, BufferArg a_name)
    {
      math_t::Mat3f32 ret = math_t::Mat3f32::IDENTITY;
      if (math::IsEqual(a_mat.Determinant(), 0.0f) == false)
      { ret = a_mat.Inverse(); }
      else
      { TLOC_LOG_GFX_WARN() << a_name << "(Mat3f) is non-invertible"; }

      return ret;
    }

    math_t::Mat4f32
      DoInvertOrIdentity(const math_t::Mat4f32& a_mat, BufferArg a_name)
    {
      math_t::Mat4f32 ret = math_t::Mat4f32::IDENTITY;
      if (math::IsEqual(a_mat.Determinant(), 0.0f) == false)
      { ret = a_mat.Invert(); }
      else
      { TLOC_LOG_GFX_WARN() << a_name << "(Mat4f) is non-invertible"; }

      return ret;
    }

  };

  // ///////////////////////////////////////////////////////////////////////
  // Entity Compare Materials

  struct MaterialCompareFromEntity
  {
    typedef gfx_cs::material_sptr                         ptr_type;
    typedef core_cs::EntitySystemBase::entity_count_pair  entity_ptr_type;
    typedef ptr_type::value_type                          comp_type;

    bool
      operator()(entity_ptr_type a, entity_ptr_type b)
    {
      if (a.first->HasComponent<comp_type>() == false)
      { return true; }
      else if (b.first->HasComponent<comp_type>() == false)
      { return false; }

      ptr_type first = a.first->GetComponent<comp_type>();
      ptr_type second = b.first->GetComponent<comp_type>();

      return first < second;
    }
  };

  // ///////////////////////////////////////////////////////////////////////
  // RenderSystem_TI::DrawInfo

#define RENDER_SYSTEM_TEMPS   typename T_RendererSptr
#define RENDER_SYSTEM_PARAMS  T_RendererSptr
#define RENDER_SYSTEM_TYPE    typename RenderSystem_TI<RENDER_SYSTEM_PARAMS>

  // ///////////////////////////////////////////////////////////////////////
  // RenderSystem_T::DrawInfo

  template <RENDER_SYSTEM_TEMPS>
  RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    DrawInfo::
    DrawInfo()
    : m_drawCommand(GL_NONE)
    , m_numVertices(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    DrawInfo::
    DrawInfo(entity_ptr a_ent, 
             gfx_t::gl_int a_drawCommand, 
             tl_size a_numVertices)
    : m_entity(a_ent)
    , m_drawCommand(a_drawCommand)
    , m_numVertices(a_numVertices)
  { }

  // ///////////////////////////////////////////////////////////////////////
  // RenderSystem_TI

  template <RENDER_SYSTEM_TEMPS>
  void
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    SortEntities()
  {
    if (IsSortingByMaterialEnabled())
    {
      core::sort(DoGetActiveEntities().begin(), DoGetActiveEntities().end(), 
                 MaterialCompareFromEntity());
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    RenderSystem_TI(event_manager_ptr   a_eventMgr,
                    entity_manager_ptr  a_entityMgr,
                    register_type       a_registerTypes, 
                    BufferArg           a_debugName)

    : base_type(a_eventMgr, a_entityMgr, a_registerTypes, a_debugName)
    , m_sharedCam(nullptr)
    , m_renderer(nullptr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  RENDER_SYSTEM_TYPE::error_type
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Pre_Initialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TLOC_DECL_ALGO_WITH_CTOR_UNARY(CompareMatSO_T, gfx_cs::material_vptr,);
  TLOC_DEFINE_ALGO_WITH_CTOR_UNARY(CompareMatSO_T,)
  { return extract()( a ).m_mat == m_value; }

  typedef CompareMatSO_T<core::use_reference>       CompareMatSO;
  typedef CompareMatSO_T<core::use_pointee>         CompareMatSOPointer;

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  RENDER_SYSTEM_TYPE::error_type
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    InitializeEntity(entity_ptr a_ent)
  {
    TLOC_LOG_CORE_WARN_IF(a_ent->HasComponent<gfx_cs::Material>() == false) 
      << "Entity (" << a_ent->GetDebugName() << ") doesn't have a material.";

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void 
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    SetCamera(const_entity_ptr a_cameraEntity)
  {
    m_sharedCam = a_cameraEntity;

    // Ensure that camera entity has the projection component
    TLOC_ASSERT( m_sharedCam->HasComponent<gfx_cs::Camera>(),
      "The passed entity is not a camera!");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void 
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    DoInitializeTexCoords(entity_ptr a_ent, so_type& a_so) const
  {
    string_type texCoordPrefix = "a_vertTexCoord0";
    if (a_ent->HasComponent<gfx_cs::Material>())
    {
      auto matPtr = a_ent->GetComponent<gfx_cs::Material>();
      texCoordPrefix = 
        matPtr->GetAttributeName<p_material::Attributes::k_texCoordPrefix>();
    }

    // populate the texture coordinate attributes
    if (a_ent->HasComponent<gfx_cs::TextureCoords>() == false)
    { return; }

    const size_type texCoordIndex =
      a_ent->size_components<gfx_cs::TextureCoords>();

    typedef gfx_cs::TextureCoords::set_index        set_index;

    for (tl_size i = 0; i < texCoordIndex; ++i)
    {
      gfx_cs::texture_coords_sptr tcPtr =
        a_ent->GetComponent<gfx_cs::TextureCoords>(i);
      tcPtr->SetUpdateRequired(false);

      if (tcPtr->GetNumSets() != 0)
      {
        gfx_cs::TextureCoords::cont_type_ptr texCoordCont =
          tcPtr->GetCoords(set_index(tcPtr->GetCurrentSet()));

        gfx_gl::AttributeVBO vbo;

        // hard coded tex-coord names
        vbo.AddName(core_str::Format("%s%i", texCoordPrefix.c_str(), i));

        vbo.SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer,
                       gfx_gl::p_vbo::usage::DynamicDraw>(*texCoordCont);

        a_so.AddAttributeVBO(vbo);
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void 
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    DoUpdateTexCoords(entity_ptr a_ent, so_type& a_so) const
  {
    string_type texCoordPrefix = "a_vertTexCoord0";
    if (a_ent->HasComponent<gfx_cs::Material>())
    {
      auto matPtr = a_ent->GetComponent<gfx_cs::Material>();
      texCoordPrefix = 
        matPtr->GetAttributeName<p_material::Attributes::k_texCoordPrefix>();
    }

    if (a_ent->HasComponent<gfx_cs::TextureCoords>() == false)
    { return; }

    const size_type numTexCoords =
      a_ent->size_components<gfx_cs::TextureCoords>();

    typedef gfx_cs::TextureCoords::set_index        set_index;

    for (tl_size i = 0; i < numTexCoords; ++i)
    {
      gfx_cs::texture_coords_sptr tcPtr =
        a_ent->GetComponent<gfx_cs::TextureCoords>(i);

      if (tcPtr->IsUpdateRequired() == false)
      { continue; }

      tcPtr->SetUpdateRequired(false);

      if (tcPtr->GetNumSets() != 0)
      {
        gfx_cs::TextureCoords::cont_type_ptr texCoordCont =
          tcPtr->GetCoords(set_index(tcPtr->GetCurrentSet()));

        core_str::String currTextureName = 
          core_str::Format("%s%i", texCoordPrefix.c_str(), i);

        using gl::algos::shader_operator::compare::AttributeVBOName;
        gl::ShaderOperator::attributeVBO_iterator itr = 
          core::find_if(a_so.begin_attributeVBOs(), 
                        a_so.end_attributeVBOs(), 
                        AttributeVBOName(currTextureName));

        if (itr != a_so.end_attributeVBOs())
        {
          itr->first->UpdateData(*texCoordCont);
        }
        else
        {
          gfx_gl::AttributeVBO vbo;
          vbo.AddName(currTextureName);
          vbo.SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer,
                         gfx_gl::p_vbo::usage::DynamicDraw>(*texCoordCont);

          a_so.AddAttributeVBO(vbo);
        }
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  RENDER_SYSTEM_TYPE::error_type
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Post_Initialize()
  {
    SortEntities();
    return base_type::Post_Initialize();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  RENDER_SYSTEM_TYPE::error_type
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Post_ReInitialize()
  {
    SortEntities();
    return base_type::Post_ReInitialize();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void 
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Pre_ProcessActiveEntities( f64 a_deltaT )
  {
    if (m_sharedCam && m_sharedCam->HasComponent<gfx_cs::Camera>())
    {
      m_vpMatrix = m_sharedCam->GetComponent<Camera>()->GetViewProjRef();
      m_viewMatrix = m_sharedCam->GetComponent<Camera>()->GetViewMatrix();
      m_projMat = m_sharedCam->GetComponent<Camera>()->GetProjectionMatrix();
    }
    else
    {
      m_vpMatrix.MakeIdentity();
      m_viewMatrix.MakeIdentity();
      m_projMat.MakeIdentity();
    }
    
    TLOC_ASSERT(m_renderer != nullptr, "No renderer attached");
    m_renderOneFrame = 
      core_sptr::MakeUnique<typename rof_uptr::value_type>(m_renderer.get());

    base_type::Pre_ProcessActiveEntities(a_deltaT);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void 
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    DoDrawEntity(const DrawInfo& a_di)
  {
    using namespace core::component_system;
    typedef math::component_system::Transform     transform_type;
    typedef graphics::component_system::Material  mat_type;

    entity_ptr  ent = a_di.m_entity;

    if (ent->HasComponent<gfx_cs::Material>() == false)
    { return; }

    gfx_cs::material_sptr matPtr = ent->GetComponent<gfx_cs::Material>();

    using math_t::Mat4f32; using math_t::Mat3f32; using math_t::Vec4f32;

    Mat4f32 modelMatrix; Mat3f32 scaleMat;
    if (ent->HasComponent<gfx_cs::SceneNode>())
    { modelMatrix = ent->GetComponent<gfx_cs::SceneNode>()->GetWorldTransform(); }
    else if (ent->HasComponent<math_cs::Transform>())
    { 
      math_cs::transform_f32_sptr t = ent->GetComponent<math_cs::Transformf32>();
      modelMatrix = t->GetTransformation().Cast<Mat4f32>();
      scaleMat.MakeIdentity();
      scaleMat[0] = t->GetScale()[0];
      scaleMat[4] = t->GetScale()[1];
      scaleMat[8] = t->GetScale()[2];
    }

    // -----------------------------------------------------------------------
    // populate and enable uniforms/attributes as needed

    // mvp matrix
    Mat4f32 tFinalMat = m_vpMatrix * modelMatrix;

    using namespace p_material::Uniforms;

    // model view projection
    if (matPtr->IsUniformEnabled<k_modelViewProjectionMatrix>())
    { matPtr->GetUniform<k_modelViewProjectionMatrix>()->SetValueAs(tFinalMat); }
    
    if (matPtr->IsUniformEnabled<k_modelViewProjectionMatrixInverse>())
    { 
      matPtr->GetUniform<k_modelViewProjectionMatrixInverse>()->
        SetValueAs(DoInvertOrIdentity(tFinalMat, "ModelViewProjectionMatrix")); 
    }

    // model view
    if (matPtr->IsUniformEnabled<k_modelViewMatrix>())
    { 
      const auto mvMat = m_viewMatrix * modelMatrix;
      matPtr->GetUniform<k_modelViewMatrix>()->SetValueAs(mvMat);
    }
    
    if (matPtr->IsUniformEnabled<k_modelViewMatrixInverse>())
    { 
      auto mvMatInv = m_viewMatrix * modelMatrix;
      mvMatInv = DoInvertOrIdentity(mvMatInv, "ModelViewMatrix");

      matPtr->GetUniform<k_modelViewMatrixInverse>()->SetValueAs(mvMatInv); 
    }

    // model
    if (matPtr->IsUniformEnabled<k_modelMatrix>())
    { matPtr->GetUniform<k_modelMatrix>()->SetValueAs(modelMatrix); }

    if (matPtr->IsUniformEnabled<k_modelMatrixInverse>())
    { 
      matPtr->GetUniform<k_modelMatrixInverse>()->
        SetValueAs(DoInvertOrIdentity(modelMatrix, "ModelMatrix")); 
    }

    // scale
    if (matPtr->IsUniformEnabled<k_scaleMatrix>())
    { matPtr->GetUniform<k_scaleMatrix>()->SetValueAs(scaleMat); }

    if (matPtr->IsUniformEnabled<k_scaleMatrixInverse>())
    { 
      matPtr->GetUniform<k_scaleMatrixInverse>()->
        SetValueAs(DoInvertOrIdentity(scaleMat, "ScaleMatrix")); 
    }

    // scale
    if (matPtr->IsUniformEnabled<k_normalMatrix>())
    { 
      math_t::Mat4f32 normMatrix = m_viewMatrix * modelMatrix;
      normMatrix = DoInvertOrIdentity(normMatrix, "NormalMatrix");
      normMatrix = normMatrix.Transpose();

      matPtr->GetUniform<k_normalMatrix>()->
        SetValueAs(normMatrix.ConvertTo<math_t::Mat3f32>());
    }
    if (matPtr->IsUniformEnabled<k_normalMatrixInverse>())
    { 
      math_t::Mat4f32 normMatrix = m_viewMatrix * modelMatrix;
      normMatrix = DoInvertOrIdentity(normMatrix, "ViewModelMatrix");
      normMatrix = normMatrix.Transpose();

      matPtr->GetUniform<k_normalMatrix>()->
        SetValueAs(DoInvertOrIdentity(normMatrix.ConvertTo<math_t::Mat3f32>(), 
                                      "NormalMatrix"));
    }

    // -----------------------------------------------------------------------
    // Prepare shader

    const_shader_prog_ptr sp = matPtr->GetShaderProg();

    error_type uniformErr = ErrorSuccess;
    error_type vboErr = ErrorSuccess;

    // Don't 're-enable' the shader if it was already enabled by the previous
    // entity
    if (m_shaderPtr == nullptr || m_shaderPtr.get() != sp.get())
    {
      // -----------------------------------------------------------------------
      // populate and enable uniforms as needed

      using namespace p_material::Uniforms;

      // -----------------------------------------------------------------------
      // view matrix

      if (matPtr->IsUniformEnabled<k_viewMatrix>())
      { matPtr->GetUniform<k_viewMatrix>()->SetValueAs(m_viewMatrix); }

      if (matPtr->IsUniformEnabled<k_viewMatrixInverse>())
      { 
        matPtr->GetUniform<k_viewMatrixInverse>()->
          SetValueAs(DoInvertOrIdentity(m_viewMatrix, "ViewMatrix")); 
      }

      // -----------------------------------------------------------------------
      // projection matrix

      if (matPtr->IsUniformEnabled<k_projectionMatrix>())
      { matPtr->GetUniform<k_projectionMatrix>()->SetValueAs(m_projMat); }

      if (matPtr->IsUniformEnabled<k_projectionMatrix>())
      { 
        matPtr->GetUniform<k_projectionMatrix>()->
          SetValueAs(DoInvertOrIdentity(m_projMat, "ProjectionMatrix"));
      }

      // -----------------------------------------------------------------------
      // view projection matrix

      if (matPtr->IsUniformEnabled<k_viewProjectionMatrix>())
      { matPtr->GetUniform<k_viewProjectionMatrix>()->SetValueAs(m_vpMatrix); }

      if (matPtr->IsUniformEnabled<k_viewProjectionMatrix>())
      { 
        matPtr->GetUniform<k_viewProjectionMatrix>()->
          SetValueAs(DoInvertOrIdentity(m_vpMatrix, "ViewProjMatrix")); 
      }

      // -----------------------------------------------------------------------
      // switch shader

      if (m_shaderPtr)
      { m_shaderPtr->Disable(); }

      if (sp->Enable().Failed())
      {
        TLOC_LOG_GFX_WARN() << "ShaderProgram #" << sp->GetHandle()
          << " could not be enabled.";
        return;
      }

      m_shaderPtr = sp;

      auto matSO = matPtr->GetShaderOperator();

      // shader switch requires us to re-prepare the attributes/uniforms
      TLOC_LOG_GFX_WARN_IF(matSO->size_attributeVBOs() > 0)
        << "Material's ShaderOperator should not have any attributes";

      if (matSO->IsUniformsCached() == false)
      { uniformErr = matSO->PrepareAllUniforms(*m_shaderPtr); }

      if (uniformErr.Succeeded())
      { matSO->EnableAllUniforms(*m_shaderPtr); }

      uniformErr = 
        matPtr->m_internalShaderOp->PrepareAllUniforms(*m_shaderPtr);
    }

    if (uniformErr.Succeeded())
    { matPtr->m_internalShaderOp->EnableAllUniforms(*m_shaderPtr); }

    // prepare/enable derived render system's shader operator
    if (a_di.m_shaderOp)
    {
      DoUpdateTexCoords(ent, *a_di.m_shaderOp);

      uniformErr = a_di.m_shaderOp->PrepareAllUniforms(*m_shaderPtr);
      if (uniformErr.Succeeded())
      { a_di.m_shaderOp->EnableAllUniforms(*m_shaderPtr); }

      vboErr = a_di.m_shaderOp->PrepareAllAttributeVBOs(*m_shaderPtr, 
                                                        *a_di.m_meshVAO);
    }

    // -----------------------------------------------------------------------
    // Render

    if (vboErr == ErrorSuccess)
    {
      gl::VertexArrayObject::Bind b(*a_di.m_meshVAO);
      glDrawArrays(a_di.m_drawCommand, 0,
                   core_utils::CastNumber<gfx_t::gl_sizei>(a_di.m_numVertices));
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Post_ProcessActiveEntities( f64 )
  {
    TLOC_ASSERT(m_renderer != nullptr, "No renderer attached");
    m_shaderPtr.reset();
    m_renderOneFrame.reset();
  }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class RenderSystem_TI<gfx_rend::renderer_depth32_sptr>;
  template class RenderSystem_TI<gfx_rend::renderer_depth64_sptr>;

};};};