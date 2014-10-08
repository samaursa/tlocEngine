#include "tlocMeshRenderSystem.h"

#include <tlocCore/component_system/tlocComponentMapper.h>
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
                Variadic<component_type, 1>
                (mesh_type::vertex_storage_policy::k_component_id) )
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <MESH_RENDER_SYSTEM_TEMPS>
  MESH_RENDER_SYSTEM_TYPE::error_type
    MeshRenderSystem_T<MESH_RENDER_SYSTEM_PARAMS>::
    Pre_Initialize()
  {
    base_type::SetEnabledAttributePosData(false);
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

    gl::attribute_vso posAttr, normAttr, tcoordAttr;

    { // Positions
      posAttr->SetVertexArray(meshType->GetPositions(),
                              gl::p_shader_variable_ti::Pointer());
      posAttr->SetName("a_vPos");
      meshType->SetPosAttribute(*posAttr);
    }

    // Normals
    if (meshType->IsNormalsEnabled())
    {
      normAttr->SetVertexArray(meshType->GetNormals(),
                              gl::p_shader_variable_ti::Pointer());
      normAttr->SetName("a_vNorm");
      meshType->SetNormAttribute(*normAttr);
    }

    // TexCoords
    if (meshType->IsTexCoordsEnabled())
    {
      tcoordAttr->SetVertexArray(meshType->GetTCoords(),
                              gl::p_shader_variable_ti::Pointer());
      tcoordAttr->SetName("a_tCoord");
      meshType->SetTCoordAttribute(*tcoordAttr);
    }

    return ErrorSuccess;
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

    so_mesh->RemoveAllAttributes();
    so_mesh->AddAttribute(*meshPtr->GetPosAttribute());

    if (meshPtr->IsTexCoordsEnabled())
    { so_mesh->AddAttribute(*meshPtr->GetTCoordAttribute()); }

    if (meshPtr->IsNormalsEnabled())
    { so_mesh->AddAttribute(*meshPtr->GetNormAttribute()); }

    base_type::DrawInfo di(a_ent, GL_TRIANGLES, numVertices);
    di.m_shaderOp = so_mesh.get();
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