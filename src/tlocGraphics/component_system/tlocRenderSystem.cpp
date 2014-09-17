#include "tlocRenderSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocMath/component_system/tlocTransform.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/component_system/tlocCamera.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocSceneNode.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // RenderSystem_I

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  // ///////////////////////////////////////////////////////////////////////
  // RenderSystem_TO

  template <RENDER_SYSTEM_TEMPS>
  RENDER_SYSTEM_TYPE::error_type
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Pre_Initialize()
  {
    m_shaderOp->reserve_attributes(9);
    m_shaderOp->reserve_uniforms(2);

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

    m_uniMvpMat   = m_shaderOp->AddUniform(gl::Uniform().SetName(m_mvpName));
    m_uniModelMat = m_shaderOp->AddUniform(gl::Uniform().SetName(m_modelMatName));
    m_vData       = m_shaderOp->AddAttribute(gl::Attribute().SetName(m_vertexDataName));

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

    using math_t::Mat4f32; using math_t::Vec4f32;

    Mat4f32 tMatrix;
    if (ent->HasComponent(components::scene_node))
    { tMatrix = ent->GetComponent<gfx_cs::SceneNode>()->GetWorldTransform(); }
    else if (ent->HasComponent(math_cs::components::transform))
    { 
      math_cs::transform_f32_sptr t = ent->GetComponent<math_cs::Transformf32>();
      tMatrix = t->GetTransformation().Cast<Mat4f32>();
    }

    Mat4f32 tFinalMat = GetViewProjectionMatrix() * tMatrix;
    m_uniMvpMat->SetValueAs(tFinalMat);

    // model matrix uniform
    if (m_enableUniModelMat) { m_uniModelMat->SetValueAs(tMatrix); }
    else { m_uniModelMat->SetEnabled(false); }

    // texture co-ordinates attributes
    const tl_size numTexCoordsSupported = m_tData.size();

    for (tl_size i = 0; i < numTexCoordsSupported; ++i)
    { m_tData[i]->SetEnabled(false); }

    // populate the texture co-orindate attributes
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
    // Prepare user shader operator

    gl::shader_operator_vso userShaderOp;

    {
      uniform_array::const_iterator itr = a_di.m_uniforms.begin(),
                                    itrEnd = a_di.m_uniforms.end();

      for (; itr != itrEnd; ++itr)
      { userShaderOp->AddUniform(**itr); }
    }

    {
      attribute_array::const_iterator itr = a_di.m_attributes.begin(),
                                      itrEnd = a_di.m_attributes.end();

      for (; itr != itrEnd; ++itr)
      { userShaderOp->AddAttribute(**itr); }
    }

    // -----------------------------------------------------------------------
    // Prepare shader

    const_shader_prog_ptr sp = matPtr->GetShaderProg();

    error_type uniformErr = ErrorSuccess;
    error_type attribErr = ErrorSuccess;

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

      typedef mat_type::shader_op_cont::const_iterator  shader_op_itr;

      const mat_type::shader_op_cont& cont = matPtr->GetShaderOperators();

      for (shader_op_itr itr = cont.begin(), itrEnd = cont.end();
           itr != itrEnd; ++itr)
      {
        gl::const_shader_operator_vptr so = itr->get();

        so->EnableAllUniforms(*m_shaderPtr);
        so->EnableAllAttributes(*m_shaderPtr);
      }

      // shader switch requires us to re-prepare the attributes/uniforms
      m_shaderOp->ClearCache();
      uniformErr = m_shaderOp->PrepareAllUniforms(*m_shaderPtr);
      attribErr = m_shaderOp->PrepareAllAttributes(*m_shaderPtr);
    }

    // Add the mvp
    if (uniformErr.Succeeded())
    { m_shaderOp->EnableAllUniforms(*m_shaderPtr); }

    if (attribErr.Succeeded())
    { m_shaderOp->EnableAllAttributes(*m_shaderPtr); }

    // prepare and enable user uniforms/attributes
    uniformErr = userShaderOp->PrepareAllUniforms(*m_shaderPtr);
    attribErr = userShaderOp->PrepareAllAttributes(*m_shaderPtr);

    if (uniformErr.Succeeded())
    { userShaderOp->EnableAllUniforms(*m_shaderPtr); }

    if (attribErr.Succeeded())
    { userShaderOp->EnableAllAttributes(*m_shaderPtr); }

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