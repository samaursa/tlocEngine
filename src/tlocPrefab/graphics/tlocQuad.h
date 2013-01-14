#ifndef _TLOC_PREFAB_GRAPHICS_QUAD_H_
#define _TLOC_PREFAB_GRAPHICS_QUAD_H_

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace prefab { namespace graphics {

  template <typename T_Real>
  core::component_system::Entity*
    CreateQuad(core::component_system::EntityManager& a_mgr,
               core::component_system::ComponentPoolManager& a_poolMgr,
               math::types::Rectangle<T_Real> a_rect);


};};};

#endif