#ifndef _TLOC_PREFAB_GRAPHICS_BOUNDING_BOX_H_
#define _TLOC_PREFAB_GRAPHICS_BOUNDING_BOX_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocBoundingBox.h>

namespace tloc { namespace prefab { namespace graphics {

  // ///////////////////////////////////////////////////////////////////////
  // BoundingBox2D

  class BoundingBox2D
    : public Prefab_TI<BoundingBox2D, gfx_cs::BoundingBox2D>
  {
  public:
    typedef BoundingBox2D                             this_type;
    typedef Prefab_TI<this_type, component_type>      base_type;

  public:
    BoundingBox2D(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr   Construct();
    entity_ptr      Create();
    void            Add   (entity_ptr a_ent);
  };

  // ///////////////////////////////////////////////////////////////////////
  // BoundingBox3D

  class BoundingBox3D
    : public Prefab_TI<BoundingBox3D, gfx_cs::BoundingBox3D>
  {
  public:
    typedef BoundingBox3D                             this_type;
    typedef Prefab_TI<this_type, component_type>      base_type;

  public:
    BoundingBox3D(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr   Construct();
    entity_ptr      Create();
    void            Add   (entity_ptr a_ent);
  };

};};};

#endif