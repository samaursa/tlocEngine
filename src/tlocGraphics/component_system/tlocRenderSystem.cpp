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
  // RenderSystem_TO

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

    if (m_uniVPMat.second.empty())
    { m_uniVPMat.second = "u_vpMat"; }

    if (m_uniViewMat.second.empty())
    { m_uniViewMat.second = "u_viewMat"; }

    if (m_uniProjMat.second.empty())
    { m_uniProjMat.second = "u_projectionMat"; }

    if (m_uniModelMat.second.empty())
    { m_uniModelMat.second = "u_modelMat"; }

    if (m_uniScaleMat.second.empty())
    { m_uniScaleMat.second = "u_scaleMat"; }

    // -----------------------------------------------------------------------

    m_shaderOp->reserve_uniforms(6);

    m_uniMVPMat.first      = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniMVPMat.second));
    m_uniVPMat.first       = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniVPMat.second));
    m_uniViewMat.first       = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniViewMat.second));
    m_uniProjMat.first       = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniProjMat.second));
    m_uniModelMat.first    = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniModelMat.second));
    m_uniScaleMat.first    = 
      m_shaderOp->AddUniform(gl::Uniform().SetName(m_uniScaleMat.second));

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void 
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    DoInitializeTexCoords(entity_ptr a_ent, so_type& a_so) const
  {
    // populate the texture coordinate attributes
    if (a_ent->HasComponent(components::texture_coords) == false)
    { return; }

    const size_type texCoordIndex =
      a_ent->GetComponents<gfx_cs::TextureCoords>().size();

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
      a_ent->GetComponents<gfx_cs::TextureCoords>().size();

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDER_SYSTEM_TEMPS>
  void 
    RenderSystem_TI<RENDER_SYSTEM_PARAMS>::
    Pre_ProcessActiveEntities( f64 )
  {
    if (m_sharedCam && m_sharedCam->HasComponent(gfx_cs::components::camera))
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

    if (other_base_type::IsUniformViewEnabled())
    { 
      m_uniViewMat.first->SetValueAs(m_viewMatrix);
      m_uniViewMat.first->SetEnabled(true);
    }
    else
    { m_uniViewMat.first->SetEnabled(false); }

    if (other_base_type::IsUniformProjectionEnabled())
    { 
      m_uniProjMat.first->SetValueAs(m_projMat);
      m_uniProjMat.first->SetEnabled(true);
    }
    else
    { m_uniProjMat.first->SetEnabled(false); }

    if (other_base_type::IsUniformVPEnabled())
    { 
      m_uniVPMat.first->SetValueAs(m_vpMatrix);
      m_uniVPMat.first->SetEnabled(true);
    }
    else
    { m_uniVPMat.first->SetEnabled(false); }


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

    Mat4f32 tFinalMat = m_vpMatrix * tMatrix;
    if (other_base_type::IsUniformMVPMatrixEnabled())
    { 
      m_uniMVPMat.first->SetValueAs(tFinalMat);
      m_uniMVPMat.first->SetEnabled(true);
    }
    else
    { m_uniMVPMat.first->SetEnabled(false); }

    // model matrix uniform
    if (other_base_type::IsUniformModelMatrixEnabled()) 
    { 
      m_uniModelMat.first->SetValueAs(tMatrix);
      m_uniModelMat.first->SetEnabled(true);
    }
    else 
    { m_uniModelMat.first->SetEnabled(false); }

    // scale matrix uniform
    if (other_base_type::IsUniformScaleMatrixEnabled()) 
    { 
      m_uniScaleMat.first->SetValueAs(scaleMat);
      m_uniScaleMat.first->SetEnabled(true);
    }
    else 
    { m_uniScaleMat.first->SetEnabled(false); }

    // -----------------------------------------------------------------------
    // Prepare shader

    typedef mat_type::shader_op_cont::iterator      shader_op_itr;
    typedef core_conts::Array<gl::const_vao_vptr>   vao_cont;

    vao_cont VAOs;

    const_shader_prog_ptr sp = matPtr->GetShaderProg();

    error_type uniformErr = ErrorSuccess;
    error_type vboErr = ErrorSuccess;

    mat_type::shader_op_cont& cont = matPtr->GetShaderOperators();

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

      for (shader_op_itr itr = cont.begin(), itrEnd = cont.end();
           itr != itrEnd; ++itr)
      {
        gl::shader_operator_vptr so = itr->get();

        if (so->IsUniformsCached() == false)
        { so->PrepareAllUniforms(*m_shaderPtr); }

        so->EnableAllUniforms(*m_shaderPtr);

        if (so->IsAttributeVBOsCached() == false)
        { so->PrepareAllAttributeVBOs(*m_shaderPtr); }
      }

      // shader switch requires us to re-prepare the attributes/uniforms
      m_shaderOp->ClearCache();
      uniformErr = m_shaderOp->PrepareAllUniforms(*m_shaderPtr);
      vboErr = m_shaderOp->PrepareAllAttributeVBOs(*m_shaderPtr);
    }

    // material's SOs
    for (shader_op_itr itr = cont.begin(), itrEnd = cont.end();
         itr != itrEnd; ++itr)
    { 
      gl::shader_operator_vptr so = itr->get();
      VAOs.push_back(so->GetVAO()); 
    }

    // Add the mvp
    if (uniformErr.Succeeded())
    { m_shaderOp->EnableAllUniforms(*m_shaderPtr); }

    if (vboErr.Succeeded())
    { VAOs.push_back(m_shaderOp->GetVAO()); }

    // prepare/enable derived render system's shader operator
    if (a_di.m_shaderOp)
    {
      DoUpdateTexCoords(ent, *a_di.m_shaderOp);
      
      // prepare and enable user uniforms/attributes
      uniformErr = a_di.m_shaderOp->PrepareAllUniforms(*m_shaderPtr);

      if (uniformErr.Succeeded())
      { a_di.m_shaderOp->EnableAllUniforms(*m_shaderPtr); }

      vboErr = a_di.m_shaderOp->PrepareAllAttributeVBOs(*m_shaderPtr);

      if (vboErr.Succeeded())
      { VAOs.push_back(a_di.m_shaderOp->GetVAO()); }
    }

    // -----------------------------------------------------------------------
    // Render

    // we just need to store the Binds, when they are destroyed, they will 
    // unbind the VAOs
    typedef core_conts::Array<gl::VertexArrayObject::late_bind_sptr>   vao_bind_cont;
    vao_bind_cont vaoBinds; vaoBinds.resize(VAOs.size());

    for (tl_size i = 0; i < vaoBinds.size(); ++i)
    { 
      if (VAOs[i])
      { 
        vaoBinds[i] = core_sptr::MakeShared<gl::VertexArrayObject::LateBind>(); 
        vaoBinds[i]->Bind(*VAOs[i]);
      }
    }

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