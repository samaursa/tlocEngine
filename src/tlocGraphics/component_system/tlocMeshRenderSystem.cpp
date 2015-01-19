#include "tlocMeshRenderSystem.h"

#include <tlocCore/logging/tlocLogger.h>

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocProjectionComponent.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocMesh.h>
#include <tlocGraphics/component_system/tlocSceneNode.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocCamera.h>
#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace graphics { namespace component_system {

  namespace {

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    math_t::Mat3f32
      DoInvertOrIdentity(const math_t::Mat3f32& a_mat, BufferArg a_name)
    {
      math_t::Mat3f32 ret = math_t::Mat3f32::IDENTITY;
      if (math::IsEqual(a_mat.Determinant(), 0.0f) == false)
      { ret = a_mat.Inverse(); }
      else
      { TLOC_LOG_GFX_WARN_NO_FILENAME() << a_name << "(Mat3f) is non-invertible"; }

      return ret;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    math_t::Mat4f32
      DoInvertOrIdentity(const math_t::Mat4f32& a_mat, BufferArg a_name)
    {
      math_t::Mat4f32 ret = math_t::Mat4f32::IDENTITY;
      if (math::IsEqual(a_mat.Determinant(), 0.0f) == false)
      { ret = a_mat.Invert(); }
      else
      { TLOC_LOG_GFX_WARN_NO_FILENAME() << a_name << "(Mat4f) is non-invertible"; }

      return ret;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Target, typename T_Usage>
    void 
      DoSetVBOValue(gfx_gl::AttributeVBO& a_vbo, const gfx_cs::Mesh& a_mesh)
    {
      switch(a_mesh.GetVertexType())
      {
        case(GL_FLOAT_VEC2):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fp>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        case(GL_FLOAT_VEC3):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fp>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        // POSITION2F
        case(TLOC_GL_POSITION2F_NORMAL3F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fpn>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        case(TLOC_GL_POSITION2F_TEXTURE2F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fpt>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        case(TLOC_GL_POSITION2F_COLOR4F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fpc>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        case(TLOC_GL_POSITION2F_NORMAL3F_COLOR4F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fpnc>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        case(TLOC_GL_POSITION2F_NORMAL3F_TEXTURE2F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fpnt>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        case(TLOC_GL_POSITION2F_NORMAL3F_COLOR4F_TEXTURE2F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert2fpnct>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        // POSITION3F
        case(TLOC_GL_POSITION3F_NORMAL3F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fpn>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        case(TLOC_GL_POSITION3F_TEXTURE2F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fpt>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        case(TLOC_GL_POSITION3F_COLOR4F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fpc>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        case(TLOC_GL_POSITION3F_NORMAL3F_COLOR4F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fpnc>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        case(TLOC_GL_POSITION3F_NORMAL3F_TEXTURE2F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fpnt>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        case(TLOC_GL_POSITION3F_NORMAL3F_COLOR4F_TEXTURE2F):
        {
          auto& arr = a_mesh.GetVertices<gfx_t::Vert3fpnct>();
          a_vbo.SetValueAs<T_Target, T_Usage>(arr);
          break;
        }
        default: TLOC_LOG_GFX_ERR_FILENAME_ONLY() 
          << "Unsupported vertex type (" << a_mesh.GetVertexType() << ") in Mesh";
      }
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void 
      DoAddVBONames(gfx_gl::AttributeVBO& a_vbo, const gfx_cs::Mesh& a_mesh)
    {
      using namespace gfx_cs::p_renderable;

      const auto& texCoordPrefix = a_mesh.GetAttributeName
        <p_renderable::attributes::k_texCoordPrefix>();
      const auto& texCoordName =
        core_str::Format("%s0", texCoordPrefix.c_str());

      // all vertex types get a position
      {
        auto& name = a_mesh.GetAttributeName<attributes::k_vertexPosition>();
        a_vbo.AddName(name);
      }

      switch(a_mesh.GetVertexType())
      {
        case(TLOC_GL_POSITION2F):
        case(TLOC_GL_POSITION3F):
        case(GL_FLOAT_VEC2):
        case(GL_FLOAT_VEC3):
        { break; /* do nothing - we already took care of this case above */ }

        // POSITION2F
        case(TLOC_GL_POSITION2F_NORMAL3F):
        case(TLOC_GL_POSITION3F_NORMAL3F):
        {
          auto& name = a_mesh.GetAttributeName<attributes::k_vertexNormal>();
          a_vbo.AddName(name);
          break;
        }
        case(TLOC_GL_POSITION2F_TEXTURE2F):
        case(TLOC_GL_POSITION3F_TEXTURE2F):
        {
          a_vbo.AddName(texCoordName);
          break;
        }
        case(TLOC_GL_POSITION2F_COLOR4F):
        case(TLOC_GL_POSITION3F_COLOR4F):
        {
          auto& name = a_mesh.GetAttributeName<attributes::k_vertexColor>();
          a_vbo.AddName(name);
          break;
        }
        case(TLOC_GL_POSITION2F_NORMAL3F_COLOR4F):
        case(TLOC_GL_POSITION3F_NORMAL3F_COLOR4F):
        {
          {
            auto& name = a_mesh.GetAttributeName<attributes::k_vertexNormal>();
            a_vbo.AddName(name);
          }
          {
            auto& name = a_mesh.GetAttributeName<attributes::k_vertexColor>();
            a_vbo.AddName(name);
          }
          break;
        }
        case(TLOC_GL_POSITION2F_NORMAL3F_TEXTURE2F):
        case(TLOC_GL_POSITION3F_NORMAL3F_TEXTURE2F):
        {
          {
            auto& name = a_mesh.GetAttributeName<attributes::k_vertexNormal>();
            a_vbo.AddName(name);
          }
          {
            a_vbo.AddName(texCoordName);
          }
          break;
        }
        case(TLOC_GL_POSITION2F_NORMAL3F_COLOR4F_TEXTURE2F):
        case(TLOC_GL_POSITION3F_NORMAL3F_COLOR4F_TEXTURE2F):
        {
          {
            auto& name = a_mesh.GetAttributeName<attributes::k_vertexNormal>();
            a_vbo.AddName(name);
          }
          {
            auto& name = a_mesh.GetAttributeName<attributes::k_vertexColor>();
            a_vbo.AddName(name);
          }
          {
            a_vbo.AddName(texCoordName);
          }
          break;
        }
        default: TLOC_LOG_GFX_ERR_FILENAME_ONLY() 
          << "Unsupported vertex type (" << a_mesh.GetVertexType() << ") in Mesh";
      }
    }

  };

  using namespace core::data_structs;

  // ///////////////////////////////////////////////////////////////////////
  // MeshRenderSystem_T

#define MESH_RENDER_SYSTEM_TEMPS  typename T_RendererSptr, typename T_MeshCompType, typename T_RenderingTechnique
#define MESH_RENDER_SYSTEM_PARAMS T_RendererSptr, T_MeshCompType, T_RenderingTechnique

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    MeshRenderSystem_T(event_manager_ptr a_eventMgr, 
                       entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                register_type().Add<mesh_comp_type>(), 
                "MeshRenderSystem")
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  auto
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    Pre_Initialize() -> error_type
  { 
    return base_type::Pre_Initialize();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  auto
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    InitializeEntity(entity_ptr a_ent) -> error_type
  {
    TLOC_LOG_CORE_WARN_IF(a_ent->HasComponent<gfx_cs::Material>() == false) 
      << "Entity (" << a_ent->GetDebugName() << ") doesn't have a material.";

    DoInitializeMesh(a_ent, static_dynamic_type(), rendering_technique());
    DoInitializeTexCoords(a_ent, static_dynamic_type(), rendering_technique());

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  auto
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    Post_Initialize() -> error_type
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  auto
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    ShutdownEntity(entity_ptr) -> error_type
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    Pre_ProcessActiveEntities(f64 a_deltaT)
  {
    base_type::Pre_ProcessActiveEntities(a_deltaT);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    ProcessEntity(entity_ptr a_ent, f64)
  {
    typedef gfx_cs::Material          mat_type;

    if (a_ent->HasComponent<gfx_cs::Material>() == false)
    { return; }

    auto  matPtr = a_ent->GetComponent<gfx_cs::Material>();

    DoProcessMesh(a_ent, static_dynamic_type(), rendering_technique());
    DoProcessTextureCoords(a_ent, static_dynamic_type(), rendering_technique());

    auto  sp = matPtr->GetShaderProg();

    // some uniforms need only be updated per shader switch
    if (m_shaderPtr == nullptr || m_shaderPtr.get() != sp.get())
    {
      using namespace p_material::uniforms;

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

      if (matPtr->IsUniformEnabled<k_projectionMatrixInverse>())
      { 
        matPtr->GetUniform<k_projectionMatrixInverse>()->
          SetValueAs(DoInvertOrIdentity(m_projMat, "ProjectionMatrix"));
      }

      // -----------------------------------------------------------------------
      // view projection matrix

      if (matPtr->IsUniformEnabled<k_viewProjectionMatrix>())
      { matPtr->GetUniform<k_viewProjectionMatrix>()->SetValueAs(m_vpMatrix); }

      if (matPtr->IsUniformEnabled<k_viewProjectionMatrixInverse>())
      { 
        matPtr->GetUniform<k_viewProjectionMatrixInverse>()->
          SetValueAs(DoInvertOrIdentity(m_vpMatrix, "ViewProjMatrix")); 
      }
    }

    auto matSO = matPtr->GetShaderOperator();

    // shader switch requires us to re-prepare the attributes/uniforms
    TLOC_LOG_GFX_WARN_NO_FILENAME_IF(matSO->size_attributeVBOs() > 0)
      << "Material's ShaderOperator should not have any attributes";

    auto  meshPtr = a_ent->GetComponent<mesh_comp_type>();
    auto  meshSO = meshPtr->DoGetShaderOperator();
    //DoUpdateTexCoords(a_ent, *meshSO);

    gfx_rend::DrawCommand dc(sp, matSO);
    dc.AddShaderOperator(core_sptr::ToVirtualPtr(matPtr->m_internalShaderOp))
      .AddShaderOperator(meshSO)
      .AddShaderOperator(meshPtr->GetUserShaderOperator())
      .SetVAO(meshPtr->DoGetVAO())
      .SetDrawMode(meshPtr->GetDrawMode())
      .SetStartIndex(0)
      .SetVertexCount(meshPtr->GetNumVertices());

    m_renderer->AddDrawCommand(dc);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    Post_ProcessActiveEntities( f64 )
  { m_shaderPtr.reset(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoInitializeMesh(entity_ptr a_ent, p_mesh::Static , 
                     p_mesh_render_sytem::Instanced )
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoInitializeMesh(entity_ptr a_ent, p_mesh::Static , 
                     p_mesh_render_sytem::NonInstanced )
  {
  }


  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoInitializeMesh(entity_ptr a_ent, p_mesh::Dynamic , 
                     p_mesh_render_sytem::Instanced )
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoInitializeMesh(entity_ptr a_ent, p_mesh::Dynamic , 
                     p_mesh_render_sytem::NonInstanced )
  {
    auto meshPtr = a_ent->GetComponent<mesh_comp_type>();
    meshPtr->SetUpdateRequired(false);

    gfx_cs::material_sptr matPtr;
    if (a_ent->HasComponent<gfx_cs::Material>())
    { matPtr = a_ent->GetComponent<gfx_cs::Material>(); }
    else // create material temporarily for names
    { matPtr = core_sptr::MakeShared<gfx_cs::Material>(); }
    
    auto so = meshPtr->DoGetShaderOperator();

    gfx_gl::AttributeVBO vbo;
    DoSetVBOValue<gfx_gl::p_vbo::target::ArrayBuffer,
                  gfx_gl::p_vbo::usage::StaticDraw>(vbo, *meshPtr);
    DoAddVBONames(vbo, *meshPtr);

    if (so->size_attributeVBOs() > 0)
    { *so->begin_attributeVBOs()->first = vbo; }
    else
    { so->AddAttributeVBO(vbo); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoInitializeTexCoords(entity_ptr a_ent, p_mesh::Static , 
                          p_mesh_render_sytem::Instanced )
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoInitializeTexCoords(entity_ptr a_ent, p_mesh::Static , 
                          p_mesh_render_sytem::NonInstanced )
  {
  }


  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoInitializeTexCoords(entity_ptr a_ent, p_mesh::Dynamic , 
                          p_mesh_render_sytem::Instanced )
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoInitializeTexCoords(entity_ptr a_ent, p_mesh::Dynamic dyn, 
                          p_mesh_render_sytem::NonInstanced ni)
  {
    DoProcessTextureCoords(a_ent, dyn, ni);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoProcessMesh(entity_ptr a_ent, p_mesh::Static , 
                  p_mesh_render_sytem::Instanced )
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoProcessMesh(entity_ptr a_ent, p_mesh::Static , 
                  p_mesh_render_sytem::NonInstanced )
  {
  }


  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoProcessMesh(entity_ptr a_ent, p_mesh::Dynamic , 
                  p_mesh_render_sytem::Instanced )
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoProcessMesh(entity_ptr a_ent, p_mesh::Dynamic , 
                  p_mesh_render_sytem::NonInstanced )
  {
    using namespace core::component_system;
    typedef math::component_system::Transform     transform_type;

    using math_t::Mat4f32; using math_t::Mat3f32; using math_t::Vec4f32;

    math_cs::transform_f32_sptr t = a_ent->GetComponent<math_cs::Transformf32>();

    const auto scaleVec = t->GetScale();

    Mat4f32 modelMatrix; modelMatrix.MakeIdentity();
    if (a_ent->HasComponent<gfx_cs::SceneNode>())
    { 
      modelMatrix = a_ent->GetComponent<gfx_cs::SceneNode>()->GetWorldTransform();
    }
    else if (a_ent->HasComponent<math_cs::Transform>())
    { 
      modelMatrix = t->GetTransformation().Cast<Mat4f32>();
    }

    // -----------------------------------------------------------------------
    // populate and enable uniforms/attributes as needed

    auto  meshPtr = a_ent->GetComponent<mesh_comp_type>();

    if (meshPtr->IsUpdateRequired())
    {
      InitializeEntity(a_ent);
      meshPtr = a_ent->GetComponent<mesh_comp_type>();
    }

    using namespace p_renderable::uniforms;

    // model view projection
    if (meshPtr->IsUniformEnabled<k_modelViewProjectionMatrix>())
    { 
      // mvp matrix
      Mat4f32 tFinalMat = m_vpMatrix * modelMatrix;
      meshPtr->GetUniform<k_modelViewProjectionMatrix>()->SetValueAs(tFinalMat);
    }
    
    if (meshPtr->IsUniformEnabled<k_modelViewProjectionMatrixInverse>())
    { 
      Mat4f32 tFinalMat = m_vpMatrix * modelMatrix;
      meshPtr->GetUniform<k_modelViewProjectionMatrixInverse>()->
        SetValueAs(DoInvertOrIdentity(tFinalMat, "ModelViewProjectionMatrix")); 
    }

    // model view
    if (meshPtr->IsUniformEnabled<k_modelViewMatrix>())
    { 
      const auto mvMat = m_viewMatrix * modelMatrix;
      meshPtr->GetUniform<k_modelViewMatrix>()->SetValueAs(mvMat);
    }
    
    if (meshPtr->IsUniformEnabled<k_modelViewMatrixInverse>())
    { 
      auto mvMatInv = m_viewMatrix * modelMatrix;
      mvMatInv = DoInvertOrIdentity(mvMatInv, "ModelViewMatrix");

      meshPtr->GetUniform<k_modelViewMatrixInverse>()->SetValueAs(mvMatInv); 
    }

    // model
    if (meshPtr->IsUniformEnabled<k_modelMatrix>())
    { meshPtr->GetUniform<k_modelMatrix>()->SetValueAs(modelMatrix); }

    if (meshPtr->IsUniformEnabled<k_modelMatrixInverse>())
    { 
      meshPtr->GetUniform<k_modelMatrixInverse>()->
        SetValueAs(DoInvertOrIdentity(modelMatrix, "ModelMatrix")); 
    }

    // scale
    if (meshPtr->IsUniformEnabled<k_scaleMatrix>())
    { 
      Mat3f32 scaleMat;

      scaleMat.MakeIdentity();
      scaleMat[0] = scaleVec[0];
      scaleMat[4] = scaleVec[1];
      scaleMat[8] = scaleVec[2];

      meshPtr->GetUniform<k_scaleMatrix>()->SetValueAs(scaleMat);
    }

    if (meshPtr->IsUniformEnabled<k_scaleMatrixInverse>())
    { 
      Mat3f32 scaleMat;

      scaleMat.MakeIdentity();
      scaleMat[0] = scaleVec[0];
      scaleMat[4] = scaleVec[1];
      scaleMat[8] = scaleVec[2];

      meshPtr->GetUniform<k_scaleMatrixInverse>()->
        SetValueAs(DoInvertOrIdentity(scaleMat, "ScaleMatrix")); 
    }

    // scale vector
    if (meshPtr->IsUniformEnabled<k_scaleMatrix>())
    {
      meshPtr->GetUniform<k_scaleVector>()->SetValueAs(scaleVec);
    }

    if (meshPtr->IsUniformEnabled<k_scaleMatrixInverse>())
    { 
      meshPtr->GetUniform<k_scaleMatrixInverse>()->
        SetValueAs(scaleVec.Inverse()); 
    }

    // normal
    if (meshPtr->IsUniformEnabled<k_normalMatrix>())
    { 
      math_t::Mat4f32 normMatrix = m_viewMatrix * modelMatrix;
      normMatrix = DoInvertOrIdentity(normMatrix, "NormalMatrix");
      normMatrix = normMatrix.Transpose();

      meshPtr->GetUniform<k_normalMatrix>()->
        SetValueAs(normMatrix.ConvertTo<math_t::Mat3f32>());
    }
    if (meshPtr->IsUniformEnabled<k_normalMatrixInverse>())
    { 
      math_t::Mat4f32 normMatrix = m_viewMatrix * modelMatrix;
      normMatrix = DoInvertOrIdentity(normMatrix, "ViewModelMatrix");
      normMatrix = normMatrix.Transpose();

      meshPtr->GetUniform<k_normalMatrixInverse>()->
        SetValueAs(DoInvertOrIdentity(normMatrix.ConvertTo<math_t::Mat3f32>(), 
                                      "NormalMatrix"));
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoProcessTextureCoords(entity_ptr a_ent, p_mesh::Static , 
                           p_mesh_render_sytem::Instanced )
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoProcessTextureCoords(entity_ptr a_ent, p_mesh::Static , 
                           p_mesh_render_sytem::NonInstanced )
  {
  }


  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoProcessTextureCoords(entity_ptr a_ent, p_mesh::Dynamic , 
                           p_mesh_render_sytem::Instanced )
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    DoProcessTextureCoords(entity_ptr a_ent, p_mesh::Dynamic , 
                           p_mesh_render_sytem::NonInstanced )
  {
    if (a_ent->HasComponent<gfx_cs::TextureCoords>() == false)
    { return ; }

    auto meshPtr = a_ent->GetComponent<mesh_comp_type>();
    auto so = meshPtr->DoGetShaderOperator();
    const auto& texCoordPrefix = 
      meshPtr->GetAttributeName<p_renderable::attributes::k_texCoordPrefix>();

    const auto numTexCoords = a_ent->size_components<gfx_cs::TextureCoords>();

    typedef gfx_cs::TextureCoords::set_index          set_index;

    for (tl_size i = 0; i < numTexCoords; ++i)
    {
      auto tcPtr = a_ent->GetComponent<gfx_cs::TextureCoords>(i);

      if (tcPtr->IsUpdateRequired() == false)
      { continue; }
      tcPtr->SetUpdateRequired(false);

      if (tcPtr->GetNumSets() != 0)
      {
        auto texCoordCont = tcPtr->GetCoords(set_index(tcPtr->GetCurrentSet()));

        const auto& currTexCoordName = 
          core_str::Format("%s%d", texCoordPrefix.c_str(), i);

        using gl::algos::shader_operator::compare::AttributeVBOName;
        auto itr = core::find_if(so->begin_attributeVBOs(),
                                 so->end_attributeVBOs(),
                                 AttributeVBOName(currTexCoordName));

        if (itr != so->end_attributeVBOs())
        {
          itr->first->UpdateData(*texCoordCont);
        }
        else
        {
          gfx_gl::AttributeVBO  vbo;
          vbo.AddName(currTexCoordName);
          vbo.SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer,
                         gfx_gl::p_vbo::usage::DynamicDraw>(*texCoordCont);

          so->AddAttributeVBO(vbo);
        }
      }
    }
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template class MeshRenderSystem_T<>;

};};};

// -----------------------------------------------------------------------
// explicit instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(MeshRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(MeshRenderSystem);