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

  using namespace core::data_structs;

#define MESH_RENDER_SYSTEM_TEMPS    typename Mesh_T
#define MESH_RENDER_SYSTEM_PARAMS   Mesh_T
#define MESH_RENDER_SYSTEM_TYPE     typename MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    MeshRenderSystem_T(event_manager_ptr a_eventMgr,
                       entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr,
                register_type().Add<mesh_type>(), 
                "MeshRenderSystem")
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  MESH_RENDER_SYSTEM_TYPE::error_type
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    Pre_Initialize()
  {
    base_type::SetEnabledAttributePosData(false);
    base_type::SetEnabledUniformViewMatrix(true);
    base_type::SetEnabledUniformNormalMatrix(true);
    return base_type::Pre_Initialize();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  MESH_RENDER_SYSTEM_TYPE::error_type
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    InitializeEntity(entity_ptr a_ent)
  {
    base_type::InitializeEntity(a_ent);

    mesh_ptr meshType = a_ent->GetComponent<mesh_type>();
    meshType->SetUpdateRequired(false);
    
    const gfx_gl::shader_operator_vptr so = meshType->GetShaderOperator().get();

    { // Positions
      gfx_gl::AttributeVBO vbo;
      vbo.SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer, 
                     gfx_gl::p_vbo::usage::StaticDraw>(*meshType->GetPositions());
      vbo.AddName(base_type::GetVertexAttributeName());
      so->AddAttributeVBO(vbo);
    }

    // Normals
    if (meshType->IsNormalsEnabled())
    {
      gfx_gl::AttributeVBO vbo;
      vbo.SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer, 
                     gfx_gl::p_vbo::usage::StaticDraw>(*meshType->GetNormals());
      vbo.AddName(base_type::GetNormalAttributeName());
      so->AddAttributeVBO(vbo);
    }

    // TexCoords
    if (meshType->IsTexCoordsEnabled())
    {
      gfx_gl::AttributeVBO vbo;
      vbo.SetValueAs<gfx_gl::p_vbo::target::ArrayBuffer, 
                     gfx_gl::p_vbo::usage::StaticDraw>(*meshType->GetTCoords());
      vbo.AddName(base_type::GetTextureAttributePrefix());
      so->AddAttributeVBO(vbo);
    }

    return base_type::InitializeEntity(a_ent);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  MESH_RENDER_SYSTEM_TYPE::error_type
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    ShutdownEntity(entity_ptr)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  void
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    ProcessEntity(entity_ptr a_ent, f64)
  {
    typedef gfx_cs::Material          mat_type;

    if (a_ent->HasComponent<gfx_cs::Material>() == false)
    { return; }

    mesh_ptr                meshPtr = a_ent->GetComponent<Mesh_T>();

    const tl_size numVertices = meshPtr->size();

    base_type::DrawInfo di(a_ent, GL_TRIANGLES, numVertices);
    di.m_shaderOp = core_sptr::ToVirtualPtr(meshPtr->GetShaderOperator());
    di.m_meshVAO  = meshPtr->GetVAO();

    base_type::DoDrawEntity(di);
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template class MeshRenderSystem_T<Mesh>;

};};};

// -----------------------------------------------------------------------
// explicit instantiation

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(MeshRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(MeshRenderSystem);