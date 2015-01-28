#ifndef _TLOC_PREFAB_GRAPHICS_RAYPICK_H_
#define _TLOC_PREFAB_GRAPHICS_RAYPICK_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocRaypick.h>

namespace tloc { namespace prefab { namespace graphics {

  // ///////////////////////////////////////////////////////////////////////
  // Raypick

  class Raypick
    : public Prefab_TI<Raypick, gfx_cs::Raypick>
  {
  public:
    typedef Raypick                                     this_type;
    typedef Prefab_TI<this_type, component_type>        base_type;

  public:
    Raypick(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr   Construct();

    entity_ptr      Create();
    void            Add   (entity_ptr a_ent);

    TLOC_DECL_PARAM_VAR(bool, DistanceChecked, m_distanceChecked);
  };

};};};

#endif