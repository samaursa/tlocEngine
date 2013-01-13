#ifndef _TLOC_PREFAB_GRAPHICS_FAN_H_
#define _TLOC_PREFAB_GRAPHICS_FAN_H_

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocMath/types/tlocCircle.h>

namespace tloc { namespace prefab { namespace graphics {

  template <typename T_Real>
  core::component_system::Entity*
    CreateFan(core::component_system::EntityManager& a_mgr,
              core::component_system::ComponentPoolManager& a_poolMgr,
              math::types::Circle<T_Real> a_circle,
              tl_size a_numSides);

};};};

#endif