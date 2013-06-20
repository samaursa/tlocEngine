#ifndef _TLOC_PREFAB_GRAPHICS_MESH_H_
#define _TLOC_PREFAB_GRAPHICS_MESH_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocMesh.h>

namespace tloc { namespace prefab { namespace graphics {

  core_cs::Entity*
    CreateMesh(core_cs::EntityManager& a_mgr,
               core_cs::ComponentPoolManager& a_poolMgr,
               core_conts::Array<gfx_cs::Mesh::vert_type> a_vertices);


};};};

#endif