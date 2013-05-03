#ifndef _TLOC_PREFAB_GRAPHICS_FAN_H_
#define _TLOC_PREFAB_GRAPHICS_FAN_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocMath/types/tlocCircle.h>

namespace tloc { namespace prefab { namespace graphics {

  core_cs::Entity*
    CreateFan(core_cs::EntityManager& a_mgr,
              core_cs::ComponentPoolManager& a_poolMgr,
              math_t::Circlef32 a_circle,
              tl_size a_numSides);

};};};

#endif