#ifndef _TLOC_PREFAB_GRAPHICS_CAMERA_H_
#define _TLOC_PREFAB_GRAPHICS_CAMERA_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

namespace tloc { namespace prefab { namespace graphics {

  core_cs::Entity*
    CreateCamera(core_cs::EntityManager& a_mgr,
                 core_cs::ComponentPoolManager& a_poolMgr);

};};};

#endif