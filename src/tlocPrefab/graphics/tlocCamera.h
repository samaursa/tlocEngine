#ifndef _TLOC_PREFAB_GRAPHICS_CAMERA_H_
#define _TLOC_PREFAB_GRAPHICS_CAMERA_H_

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

namespace tloc { namespace prefab { namespace graphics {

  core::component_system::Entity*
    CreateCamera(core::component_system::EntityManager& a_mgr,
                 core::component_system::ComponentPoolManager& a_poolMgr);

};};};

#endif