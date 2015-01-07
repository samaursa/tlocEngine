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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  MeshRenderSystem::
    MeshRenderSystem(event_manager_ptr a_eventMgr, 
                     entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                register_type().Add<mesh_type>(), 
                "MeshRenderSystem")
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    MeshRenderSystem::
    Pre_Initialize() -> error_type
  { return base_type::Pre_Initialize(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    MeshRenderSystem::
    InitializeEntity(entity_ptr a_ent) -> error_type
  {
    base_type::InitializeEntity(a_ent);

    auto meshType = a_ent->GetComponent<mesh_type>();
    meshType->SetUpdateRequired(false);

    gfx_cs::material_sptr matPtr;
    if (a_ent->HasComponent<gfx_cs::Material>())
    {
      matPtr = a_ent->GetComponent<gfx_cs::Material>();
      matPtr->SetEnableUniform<p_material::Uniforms::k_normalMatrix>();
    }
    else // create material temporarily for names
    { matPtr = core_sptr::MakeShared<gfx_cs::Material>(); }
    
    const gfx_gl::shader_operator_vptr so = meshType->GetShaderOperator().get();

    gfx_gl::AttributeVBO vbo;
    DoSetVBOValue<gfx_gl::p_vbo::target::ArrayBuffer,
                  gfx_gl::p_vbo::usage::StaticDraw>(vbo, *meshType);
    DoAddVBONames(vbo, *meshType, *matPtr);

    return base_type::InitializeEntity(a_ent);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    MeshRenderSystem::
    ShutdownEntity(entity_ptr) -> error_type
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    MeshRenderSystem::
    ProcessEntity(entity_ptr a_ent, f64)
  {
    typedef gfx_cs::Material          mat_type;

    if (a_ent->HasComponent<gfx_cs::Material>() == false)
    { return; }

    auto  meshPtr = a_ent->GetComponent<Mesh>();
    auto  drawMode = meshPtr->GetDrawMode();
    auto  numVertices = meshPtr->GetNumVertices();

    base_type::DrawInfo di(a_ent, drawMode, numVertices);
    di.m_shaderOp = core_sptr::ToVirtualPtr(meshPtr->GetShaderOperator());
    di.m_meshVAO  = meshPtr->GetVAO();

    base_type::DoDrawEntity(di);
  }

};};};

// -----------------------------------------------------------------------
// explicit instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(MeshRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(MeshRenderSystem);