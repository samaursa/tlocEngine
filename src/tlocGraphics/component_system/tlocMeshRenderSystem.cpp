#include "tlocMeshRenderSystem.h"

#include <tlocCore/logging/tlocLogger.h>

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocProjectionComponent.h>

#include <tlocGraphics/component_system/tlocSceneNode.h>
#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocMesh.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocCamera.h>
#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace {
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
        default: TLOC_LOG_GFX_WARN_NO_FILENAME() << "Unsupported vertex type in Mesh";
      }
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void 
      DoAddVBONames(gfx_gl::AttributeVBO& a_vbo, const gfx_cs::Mesh& a_mesh, 
                    gfx_cs::Material& a_material)
    {
      using namespace gfx_cs::p_material;

      // all vertex types get a position
      {
        auto& name = a_material.GetAttributeName<Attributes::k_vertexPosition>();
        a_vbo.AddName(name);
      }

      switch(a_mesh.GetVertexType())
      {
        // POSITION2F
        case(TLOC_GL_POSITION2F_NORMAL3F):
        case(TLOC_GL_POSITION3F_NORMAL3F):
        {
          auto& name = a_material.GetAttributeName<Attributes::k_vertexNormal>();
          a_vbo.AddName(name);
          break;
        }
        case(TLOC_GL_POSITION2F_TEXTURE2F):
        case(TLOC_GL_POSITION3F_TEXTURE2F):
        {
          auto& name = a_material.GetAttributeName<Attributes::k_texCoordPrefix>();
          a_vbo.AddName(core_str::Format("%s0", name.c_str()));
          break;
        }
        case(TLOC_GL_POSITION2F_COLOR4F):
        case(TLOC_GL_POSITION3F_COLOR4F):
        {
          auto& name = a_material.GetAttributeName<Attributes::k_vertexColor>();
          a_vbo.AddName(name);
          break;
        }
        case(TLOC_GL_POSITION2F_NORMAL3F_COLOR4F):
        case(TLOC_GL_POSITION3F_NORMAL3F_COLOR4F):
        {
          {
            auto& name = a_material.GetAttributeName<Attributes::k_vertexNormal>();
            a_vbo.AddName(name);
          }
          {
            auto& name = a_material.GetAttributeName<Attributes::k_vertexColor>();
            a_vbo.AddName(name);
          }
          break;
        }
        case(TLOC_GL_POSITION2F_NORMAL3F_TEXTURE2F):
        case(TLOC_GL_POSITION3F_NORMAL3F_TEXTURE2F):
        {
          {
            auto& name = a_material.GetAttributeName<Attributes::k_vertexNormal>();
            a_vbo.AddName(name);
          }
          {
            auto& name = a_material.GetAttributeName<Attributes::k_texCoordPrefix>();
            a_vbo.AddName(core_str::Format("%s0", name.c_str()));
          }
          break;
        }
        case(TLOC_GL_POSITION2F_NORMAL3F_COLOR4F_TEXTURE2F):
        case(TLOC_GL_POSITION3F_NORMAL3F_COLOR4F_TEXTURE2F):
        {
          {
            auto& name = a_material.GetAttributeName<Attributes::k_vertexNormal>();
            a_vbo.AddName(name);
          }
          {
            auto& name = a_material.GetAttributeName<Attributes::k_vertexColor>();
            a_vbo.AddName(name);
          }
          {
            auto& name = a_material.GetAttributeName<Attributes::k_texCoordPrefix>();
            a_vbo.AddName(core_str::Format("%s0", name.c_str()));
          }
          break;
        }
        default: TLOC_LOG_GFX_WARN_NO_FILENAME() << "Unsupported vertex type in Mesh";
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
    SortEntities();
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  auto
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    InitializeEntity(entity_ptr a_ent) -> error_type
  {
    TLOC_LOG_CORE_WARN_IF(a_ent->HasComponent<gfx_cs::Material>() == false) 
      << "Entity (" << a_ent->GetDebugName() << ") doesn't have a material.";

    auto meshType = a_ent->GetComponent<mesh_comp_type>();
    meshType->SetUpdateRequired(false);

    gfx_cs::material_sptr matPtr;
    if (a_ent->HasComponent<gfx_cs::Material>())
    { matPtr = a_ent->GetComponent<gfx_cs::Material>(); }
    else // create material temporarily for names
    { matPtr = core_sptr::MakeShared<gfx_cs::Material>(); }
    
    const gfx_gl::shader_operator_vptr so = meshType->GetShaderOperator().get();

    gfx_gl::AttributeVBO vbo;
    DoSetVBOValue<gfx_gl::p_vbo::target::ArrayBuffer,
                  gfx_gl::p_vbo::usage::StaticDraw>(vbo, *meshType);
    DoAddVBONames(vbo, *meshType, *matPtr);

    so->AddAttributeVBO(vbo);

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

    auto  meshPtr = a_ent->GetComponent<mesh_comp_type>();
    auto  matPtr = a_ent->GetComponent<gfx_cs::Material>();

    DoProcessMesh(a_ent, static_dynamic_type(), rendering_technique());

    auto  sp = matPtr->GetShaderProg();

    // some uniforms need only be updated per shader switch
    if (m_shaderPtr == nullptr || m_shaderPtr.get() != sp.get())
    {
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
    }

    auto matSO = matPtr->GetShaderOperator();

    // shader switch requires us to re-prepare the attributes/uniforms
    TLOC_LOG_GFX_WARN_NO_FILENAME_IF(matSO->size_attributeVBOs() > 0)
      << "Material's ShaderOperator should not have any attributes";

    auto meshSO = meshPtr->GetShaderOperator().get();
    //DoUpdateTexCoords(a_ent, *meshSO);

    gfx_rend::DrawCommand dc(sp, matSO);
    dc.AddShaderOperator(core_sptr::ToVirtualPtr(matPtr->m_internalShaderOp))
      .AddShaderOperator(matPtr->GetShaderOperator())
      .SetVAO(meshPtr->GetVAO())
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
    SetCamera(const_entity_ptr a_cameraEntity)
  {
    TLOC_ASSERT( m_sharedCam->HasComponent<gfx_cs::Camera>(),
      "The passed entity is not a camera!");

    m_sharedCam = a_cameraEntity;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    SortEntities()
  {
    if (IsSortingByMaterialEnabled())
    {
      core::sort(DoGetActiveEntities().begin(), DoGetActiveEntities().end(), 
                 MaterialCompareFromEntity(), core::sort_insertionsort());
    }
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
    DoProcessMesh(entity_ptr a_ptr, p_mesh::Dynamic , 
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

    Mat4f32 modelMatrix; Mat3f32 scaleMat;
    if (a_ent->HasComponent<gfx_cs::SceneNode>())
    { modelMatrix = a_ent->GetComponent<gfx_cs::SceneNode>()->GetWorldTransform(); }
    else if (a_ent->HasComponent<math_cs::Transform>())
    { 
      math_cs::transform_f32_sptr t = a_ent->GetComponent<math_cs::Transformf32>();
      modelMatrix = t->GetTransformation().Cast<Mat4f32>();
      scaleMat.MakeIdentity();
      scaleMat[0] = t->GetScale()[0];
      scaleMat[4] = t->GetScale()[1];
      scaleMat[8] = t->GetScale()[2];
    }

    // -----------------------------------------------------------------------
    // populate and enable uniforms/attributes as needed

    auto  matPtr = a_ent->GetComponent<gfx_cs::Material>();

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

    // normal
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
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template class MeshRenderSystem_T<>;

};};};

// -----------------------------------------------------------------------
// explicit instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

//TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(MeshRenderSystem);
//TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(MeshRenderSystem);