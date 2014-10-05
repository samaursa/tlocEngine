#include "tlocRenderSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/logging/tlocLogger.h>

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
  // RenderSystem_TI

#define RENDER_SYSTEM_TEMPS   typename T_RendererSptr, typename T_AttributeType
#define RENDER_SYSTEM_PARAMS  T_RendererSptr, T_AttributeType
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
  // RenderSystem_TO

  template <RENDER_SYSTEM_TEMPS>
  RENDER_SYSTEM_TYPE::error_type
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Pre_Initialize()
  {
    // -----------------------------------------------------------------------

    if (m_mvpMat.second.empty())
    { m_mvpMat.second = "u_mvp"; }

    if (m_vpMat.second.empty())
    { m_vpMat.second = "u_vpMat"; }

    if (m_modelMat.second.empty())
    { m_modelMat.second = "u_modelMat"; }

    if (m_scaleMat.second.empty())
    { m_scaleMat.second = "u_scaleMat"; }

    if (m_vertexData.second.empty())
    { m_vertexData.second = "a_vPos"; }

    // -----------------------------------------------------------------------

    m_shaderOp->reserve_attributes(9);
    m_shaderOp->reserve_uniforms(4);

    m_tData.resize(m_tData.capacity());
    m_tData[0] = m_shaderOp->AddAttribute(gl::Attribute().SetName("a_tCoord"));
    m_tData[1] = m_shaderOp->AddAttribute(gl::Attribute().SetName("a_tCoord2"));
    m_tData[2] = m_shaderOp->AddAttribute(gl::Attribute().SetName("a_tCoord3"));
    m_tData[3] = m_shaderOp->AddAttribute(gl::Attribute().SetName("a_tCoord4"));
    m_tData[4] = m_shaderOp->AddAttribute(gl::Attribute().SetName("a_tCoord5"));
    m_tData[5] = m_shaderOp->AddAttribute(gl::Attribute().SetName("a_tCoord6"));
    m_tData[6] = m_shaderOp->AddAttribute(gl::Attribute().SetName("a_tCoord7"));
    m_tData[7] = m_shaderOp->AddAttribute(gl::Attribute().SetName("a_tCoord8"));

    for (tl_size i = 0; i < m_tData.size(); ++i)
    { m_tData[i]->SetEnabled(false); }

    m_vertexData.first  = 
      m_shaderOp->AddAttribute(gl::Attribute().SetName(m_vertexData.second));

    m_mvpMat.first      = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_mvpMat.second));
    m_vpMat.first       = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_vpMat.second));
    m_modelMat.first    = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_modelMat.second));
    m_scaleMat.first    = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_scaleMat.second));

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
    TLOC_ASSERT( m_sharedCam->HasComponent(gfx_cs::components::camera),
      "The passed entity is not a camera!");
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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void 
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Pre_ProcessActiveEntities( f64 )
  {
    if (m_sharedCam && m_sharedCam->HasComponent(gfx_cs::components::camera))
    {
      m_vpMatrix = m_sharedCam->GetComponent<Camera>()->GetViewProjRef();
    }
    else
    {
      m_vpMatrix.MakeIdentity();
    }

    TLOC_ASSERT(m_renderer != nullptr, "No renderer attached");
    m_renderOneFrame.reset(new typename rof_uptr::value_type(m_renderer.get()) );
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

    if (ent->HasComponent(components::material) == false)
    { return; }

    gfx_cs::material_sptr matPtr = ent->GetComponent<gfx_cs::Material>();

    using math_t::Mat4f32; using math_t::Mat3f32; using math_t::Vec4f32;

    Mat4f32 tMatrix; Mat3f32 scaleMat;
    if (ent->HasComponent(components::scene_node))
    { tMatrix = ent->GetComponent<gfx_cs::SceneNode>()->GetWorldTransform(); }
    else if (ent->HasComponent(math_cs::components::transform))
    { 
      math_cs::transform_f32_sptr t = ent->GetComponent<math_cs::Transformf32>();
      tMatrix = t->GetTransformation().Cast<Mat4f32>();
      scaleMat.MakeIdentity();
      scaleMat[0] = t->GetScale()[0];
      scaleMat[4] = t->GetScale()[1];
      scaleMat[8] = t->GetScale()[2];
    }

    // -----------------------------------------------------------------------
    // populate and enable uniforms/attributes as needed

    const Mat4f32 viewProjMat = GetViewProjectionMatrix();
    if (other_base_type::IsUniformVPEnabled())
    { 
      m_vpMat.first->SetValueAs(viewProjMat);
      m_vpMat.first->SetEnabled(true);
    }
    else
    { m_vpMat.first->SetEnabled(false); }

    Mat4f32 tFinalMat = viewProjMat * tMatrix;
    if (other_base_type::IsUniformMVPMatrixEnabled())
    { 
      m_mvpMat.first->SetValueAs(tFinalMat);
      m_mvpMat.first->SetEnabled(true);
    }
    else
    { m_mvpMat.first->SetEnabled(false); }

    // position data
    if (other_base_type::IsUseVBOsEnabled() == false)
    {
      m_vertexData.first->SetEnabled(other_base_type::IsAttributePosDataEnabled());
      m_vertexData.first->SetEnabled(true);
    }
    else
    { m_vertexData.first->SetEnabled(false); }

    // model matrix uniform
    if (other_base_type::IsUniformModelMatrixEnabled()) 
    { 
      m_modelMat.first->SetValueAs(tMatrix);
      m_modelMat.first->SetEnabled(true);
    }
    else 
    { m_modelMat.first->SetEnabled(false); }

    // scale matrix uniform
    if (other_base_type::IsUniformScaleMatrixEnabled()) 
    { 
      m_scaleMat.first->SetValueAs(scaleMat);
      m_scaleMat.first->SetEnabled(true);
    }
    else 
    { m_scaleMat.first->SetEnabled(false); }

    // -----------------------------------------------------------------------
    // texture coordinates

    const tl_size numTexCoordsSupported = m_tData.size();

    for (tl_size i = 0; i < numTexCoordsSupported; ++i)
    { m_tData[i]->SetEnabled(false); }

    // populate the texture coordinate attributes
    if (ent->HasComponent(components::texture_coords))
    {
      typedef gfx_cs::TextureCoords::set_index        set_index;

      const tl_size numTexCoords =
        ent->GetComponents(gfx_cs::TextureCoords::k_component_type).size();

      TLOC_LOG_GFX_WARN_IF(numTexCoords > numTexCoordsSupported) 
        << "Requested " << numTexCoords << " but only " << numTexCoordsSupported
        << " supported";

      for (tl_size i = 0; i < numTexCoords && i < numTexCoordsSupported; ++i)
      {
        gfx_cs::texture_coords_sptr texCoordPtr =
          ent->GetComponent<gfx_cs::TextureCoords>(i);

        if (texCoordPtr && texCoordPtr->GetNumSets())
        {
          gfx_cs::TextureCoords::cont_type_ptr
            texCoordCont = texCoordPtr->GetCoords
            (set_index(texCoordPtr->GetCurrentSet()));

          m_tData[i]->SetEnabled(true);
          m_tData[i]->SetVertexArray(texCoordCont,
                                     gl::p_shader_variable_ti::Pointer());
        }
      }
    }

    // -----------------------------------------------------------------------
    // Prepare shader

    const_shader_prog_ptr sp = matPtr->GetShaderProg();

    error_type uniformErr = ErrorSuccess;
    error_type attribErr = ErrorSuccess;
    error_type vboErr = ErrorSuccess;

    // we just need to store the Binds, when they are destroyed, they will 
    // unbind the VAOs
    typedef core_conts::Array<gl::VertexArrayObject::bind_sptr>   vao_bind_cont;
    vao_bind_cont vaoBinds;

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

      typedef mat_type::shader_op_cont::iterator  shader_op_itr;

      mat_type::shader_op_cont& cont = matPtr->GetShaderOperators();

      for (shader_op_itr itr = cont.begin(), itrEnd = cont.end();
           itr != itrEnd; ++itr)
      {
        gl::shader_operator_vptr so = itr->get();

        if (so->IsAttributesCached() == false)
        { so->PrepareAllAttributes(*m_shaderPtr); }

        if (so->IsUniformsCached() == false)
        { so->PrepareAllUniforms(*m_shaderPtr); }

        so->EnableAllUniforms(*m_shaderPtr);
        so->EnableAllAttributes(*m_shaderPtr);

        if (IsUseVBOsEnabled())
        { 
          if (so->IsVBOsCached() == false)
          { so->PrepareAllVBOs(*m_shaderPtr); }

          vaoBinds.push_back(so->EnableAllVBOs(*m_shaderPtr));
        }
      }

      // shader switch requires us to re-prepare the attributes/uniforms
      m_shaderOp->ClearCache();
      uniformErr = m_shaderOp->PrepareAllUniforms(*m_shaderPtr);
      attribErr = m_shaderOp->PrepareAllAttributes(*m_shaderPtr);

      if (IsUseVBOsEnabled())
      { vboErr = m_shaderOp->PrepareAllVBOs(*m_shaderPtr); }
    }

    // Add the mvp
    if (uniformErr.Succeeded())
    { m_shaderOp->EnableAllUniforms(*m_shaderPtr); }

    if (attribErr.Succeeded())
    { m_shaderOp->EnableAllAttributes(*m_shaderPtr); }

    if (IsUseVBOsEnabled() && vboErr.Succeeded())
    { vaoBinds.push_back(m_shaderOp->EnableAllVBOs(*m_shaderPtr)); }

    // prepare/enable user's shader operator
    if (a_di.m_shaderOp)
    {
      // prepare and enable user uniforms/attributes
      uniformErr = a_di.m_shaderOp->PrepareAllUniforms(*m_shaderPtr);
      attribErr = a_di.m_shaderOp->PrepareAllAttributes(*m_shaderPtr);

      if (uniformErr.Succeeded())
      { a_di.m_shaderOp->EnableAllUniforms(*m_shaderPtr); }

      if (attribErr.Succeeded())
      { a_di.m_shaderOp->EnableAllAttributes(*m_shaderPtr); }

      if (IsUseVBOsEnabled())
      { 
        vboErr = a_di.m_shaderOp->PrepareAllVBOs(*m_shaderPtr);

        if (vboErr.Succeeded())
        { vaoBinds.push_back(a_di.m_shaderOp->EnableAllVBOs(*m_shaderPtr)); }
      }
    }

    // -----------------------------------------------------------------------
    // Render

    glDrawArrays(a_di.m_drawCommand, 0,
                 core_utils::CastNumber<gfx_t::gl_sizei>(a_di.m_numVertices));
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