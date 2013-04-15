#ifndef _TLOC_PREFAB_GRAPHICS_QUAD_H_
#define _TLOC_PREFAB_GRAPHICS_QUAD_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace prefab { namespace graphics {

  core_cs::Entity*
    CreateQuad(core_cs::EntityManager& a_mgr,
               core_cs::ComponentPoolManager& a_poolMgr,
               const math_t::Rectf32& a_rect);


};};};

#endif