#include "tlocMeshRenderSystem.h"
#include <tlocGraphics/component_system/tlocGfxComponentType.h>
#include <tlocGraphics/component_system/tlocMesh.h>

#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocComponentMapper.inl>

#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace component_system {

  MeshRenderSystem::MeshRenderSystem
    (event_manager* a_eventMgr, entity_manager* a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr
    , core::Variadic<component_type, 1>(components::mesh))
  {
  }

  void MeshRenderSystem::ProcessEntity(entity_manager* a_mgr, entity_type* a_ent)
  {
    using namespace core::component_system;
    typedef graphics::component_system::Mesh            mesh_type;

    const entity_type* ent = a_ent;
    ComponentMapper<mesh_type> mesh = ent->GetComponents(components::mesh);

    if (a_ent->HasComponent(components::material))
    {
      // Prepare the material
    }

    // Render
    TLOC_UNUSED(a_mgr);
  }

};};};