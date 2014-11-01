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
             gfx_t::gl_sizei a_numVertices)
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
                    register_type       a_registerTypes)

    : base_type(a_eventMgr, a_entityMgr, a_registerTypes)
    , m_sharedCam(nullptr)
    , m_renderer(nullptr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  RENDER_SYSTEM_TYPE::error_type
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Pre_Initialize()
  {
    // -----------------------------------------------------------------------

    if (m_vertexAttribName.empty())
    { m_vertexAttribName = "a_vPos"; }

    if (m_textureAttribPrefix.empty())
    { m_textureAttribPrefix = "a_tCoord"; }

    if (m_normalAttribName.empty())
    { m_normalAttribName = "a_vNorm"; }

    if (m_colorAttribName.empty())
    { m_colorAttribName = "a_vCol"; }

    // -----------------------------------------------------------------------

    if (m_uniMVPMat.second.empty())
    { m_uniMVPMat.second = "u_mvp"; }
    if (m_uniMVPInverseMat.second.empty())
    { m_uniMVPInverseMat.second = "u_mvpInverse"; }

    if (m_uniVPMat.second.empty())
    { m_uniVPMat.second = "u_vpMat"; }
    if (m_uniVPInverseMat.second.empty())
    { m_uniVPInverseMat.second = "u_vpInverseMat"; }

    if (m_uniMVMat.second.empty())
    { m_uniMVMat.second = "u_mvMat"; }
    if (m_uniMVInverseMat.second.empty())
    { m_uniMVInverseMat.second = "u_mvInverseMat"; }

    if (m_uniProjMat.second.empty())
    { m_uniProjMat.second = "u_projectionMat"; }
    if (m_uniProjInverseMat.second.empty())
    { m_uniProjInverseMat.second = "u_projectionInverseMat"; }

    if (m_uniViewMat.second.empty())
    { m_uniViewMat.second = "u_viewMat"; }
    if (m_uniViewInverseMat.second.empty())
    { m_uniViewInverseMat.second = "u_viewInverseMat"; }

    if (m_uniModelMat.second.empty())
    { m_uniModelMat.second = "u_modelMat"; }
    if (m_uniModelInverseMat.second.empty())
    { m_uniModelInverseMat.second = "u_modelInverseMat"; }

    if (m_uniScaleMat.second.empty())
    { m_uniScaleMat.second = "u_scaleMat"; }
    if (m_uniScaleInverseMat.second.empty())
    { m_uniScaleInverseMat.second = "u_scaleInverseMat"; }

    if (m_uniNormalMat.second.empty())
    { m_uniNormalMat.second = "u_normalMat"; }

    // -----------------------------------------------------------------------

    m_shaderOp->reserve_uniforms(15);

    m_uniMVPMat.first      = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniMVPMat.second));
    m_uniMVPInverseMat.first      = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniMVPInverseMat.second));

    m_uniVPMat.first       = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniVPMat.second));
    m_uniVPInverseMat.first       = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniVPInverseMat.second));

    m_uniMVMat.first       = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniMVMat.second));
    m_uniMVInverseMat.first       = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniMVInverseMat.second));

    m_uniProjMat.first     = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniProjMat.second));
    m_uniProjInverseMat.first     = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniProjInverseMat.second));

    m_uniViewMat.first     = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniViewMat.second));
    m_uniViewInverseMat.first     = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniViewInverseMat.second));

    m_uniModelMat.first    = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniModelMat.second));
    m_uniModelInverseMat.first    = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniModelInverseMat.second));

    m_uniScaleMat.first    = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniScaleMat.second));
    m_uniScaleInverseMat.first    = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniScaleInverseMat.second));

    m_uniNormalMat.first    = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniNormalMat.second));

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
        if (i != 0)
        { vbo.AddName(core_str::Format("%s%i", m_textureAttribPrefix.c_str(), i + 1)); }
        else
        { vbo.AddName(m_textureAttribPrefix); }

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
          core_str::Format("%s%i", m_textureAttribPrefix.c_str(), i + 1);
        if (i == 0)
        { currTextureName = m_textureAttribPrefix; }

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  RENDER_SYSTEM_TYPE::error_type
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    InitializeEntity(entity_ptr a_ent)
  {
    TLOC_LOG_CORE_WARN_IF(a_ent->HasComponent<gfx_cs::Material>() == false) 
      << "Entity (" << a_ent->GetDebugName() << ") doesn't have "
      << "a material.";

    return ErrorSuccess;
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

    // -----------------------------------------------------------------------
    // populate and enable uniforms as needed

    // view matrix
    if (other_base_type::IsUniformViewMatrixEnabled())
    { 
      m_uniViewMat.first->SetValueAs(m_viewMatrix);
      m_uniViewMat.first->SetEnabled(true);
    }
    else
    { m_uniViewMat.first->SetEnabled(false); }

    if (other_base_type::IsUniformViewMatrixInverseEnabled())
    { 
      m_uniViewInverseMat.first->SetValueAs(m_viewMatrix.Invert());
      m_uniViewInverseMat.first->SetEnabled(true);
    }
    else
    { m_uniViewInverseMat.first->SetEnabled(false); }

    // projection matrix
    if (other_base_type::IsUniformProjectionEnabled())
    { 
      m_uniProjMat.first->SetValueAs(m_projMat);
      m_uniProjMat.first->SetEnabled(true);
    }
    else
    { m_uniProjMat.first->SetEnabled(false); }

    if (other_base_type::IsUniformProjectionInverseEnabled())
    { 
      m_uniProjInverseMat.first->SetValueAs(m_projMat.Invert());
      m_uniProjInverseMat.first->SetEnabled(true);
    }
    else
    { m_uniProjInverseMat.first->SetEnabled(false); }

    // view projection matrix
    if (other_base_type::IsUniformVPMatrixEnabled())
    { 
      m_uniVPMat.first->SetValueAs(m_vpMatrix);
      m_uniVPMat.first->SetEnabled(true);
    }
    else
    { m_uniVPMat.first->SetEnabled(false); }

    if (other_base_type::IsUniformVPInverseMatrixEnabled())
    { 
      m_uniVPInverseMat.first->SetValueAs(m_vpMatrix.Invert());
      m_uniVPInverseMat.first->SetEnabled(true);
    }
    else
    { m_uniVPInverseMat.first->SetEnabled(false); }


    TLOC_ASSERT(m_renderer != nullptr, "No renderer attached");
    m_renderOneFrame.reset(new typename rof_uptr::value_type(m_renderer.get()) );

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
    if (other_base_type::IsUniformMVPMatrixEnabled())
    { 
      m_uniMVPMat.first->SetValueAs(tFinalMat);
      m_uniMVPMat.first->SetEnabled(true);
    }
    else
    { m_uniMVPMat.first->SetEnabled(false); }

    if (other_base_type::IsUniformMVPInverseMatrixEnabled())
    { 
      m_uniMVPInverseMat.first->SetValueAs(tFinalMat.Invert());
      m_uniMVPInverseMat.first->SetEnabled(true);
    }
    else
    { m_uniMVPInverseMat.first->SetEnabled(false); }

    // mv matrix
    if (other_base_type::IsUniformMVMatrixEnabled())
    { 
      Mat4f32 mvMatInv = m_viewMatrix * modelMatrix;

      m_uniMVMat.first->SetValueAs(mvMatInv);
      m_uniMVMat.first->SetEnabled(true);
    }
    else
    { m_uniMVMat.first->SetEnabled(false); }

    if (other_base_type::IsUniformMVInverseMatrixEnabled())
    { 
      Mat4f32 mvMatInv = m_viewMatrix * modelMatrix;
      mvMatInv = mvMatInv.Invert();

      m_uniMVInverseMat.first->SetValueAs(mvMatInv) ;
      m_uniMVPInverseMat.first->SetEnabled(true);
    }
    else
    { m_uniMVInverseMat.first->SetEnabled(false); }

    // model matrix uniform
    if (other_base_type::IsUniformModelMatrixEnabled()) 
    { 
      m_uniModelMat.first->SetValueAs(modelMatrix);
      m_uniModelMat.first->SetEnabled(true);
    }
    else 
    { m_uniModelMat.first->SetEnabled(false); }

    if (other_base_type::IsUniformModelInverseMatrixEnabled()) 
    { 
      m_uniModelInverseMat.first->SetValueAs(modelMatrix.Invert());
      m_uniModelInverseMat.first->SetEnabled(true);
    }
    else 
    { m_uniModelInverseMat.first->SetEnabled(false); }

    // scale matrix uniform
    if (other_base_type::IsUniformScaleMatrixEnabled()) 
    { 
      m_uniScaleMat.first->SetValueAs(scaleMat);
      m_uniScaleMat.first->SetEnabled(true);
    }
    else 
    { m_uniScaleMat.first->SetEnabled(false); }

    if (other_base_type::IsUniformScaleInverseMatrixEnabled()) 
    { 
      m_uniScaleInverseMat.first->SetValueAs(scaleMat.Inverse());
      m_uniScaleInverseMat.first->SetEnabled(true);
    }
    else 
    { m_uniScaleInverseMat.first->SetEnabled(false); }

    // normal matrix uniform
    if (other_base_type::IsUniformNormalMatrixEnabled()) 
    { 
      math_t::Mat4f32 normMatrix = m_viewMatrix * modelMatrix;
      normMatrix = normMatrix.Invert();
      normMatrix = normMatrix.Transpose();
      m_uniNormalMat.first->SetValueAs( normMatrix.ConvertTo<math_t::Mat3f32>() ) ;
      m_uniNormalMat.first->SetEnabled(true);
    }
    else 
    { m_uniNormalMat.first->SetEnabled(false); }

    // -----------------------------------------------------------------------
    // Prepare shader

    const_shader_prog_ptr sp = matPtr->GetShaderProg();

    error_type uniformErr = ErrorSuccess;
    error_type vboErr = ErrorSuccess;

    // Don't 're-enable' the shader if it was already enabled by the previous
    // entity
    if (m_shaderPtr == nullptr || m_shaderPtr.get() != sp.get())
    {
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
      { matSO->PrepareAllUniforms(*m_shaderPtr); }

      matSO->EnableAllUniforms(*m_shaderPtr);

      // shader switch requires us to re-prepare the attributes/uniforms
      TLOC_ASSERT(m_shaderOp->size_attributeVBOs() == 0, 
        "RenderSystem's internal ShaderOperator should not have any attributes");

      m_shaderOp->ClearCache();
      uniformErr = m_shaderOp->PrepareAllUniforms(*m_shaderPtr);
    }

    if (uniformErr.Succeeded())
    { m_shaderOp->EnableAllUniforms(*m_shaderPtr); }

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