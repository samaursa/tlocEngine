#ifndef _TLOC_PREFAB_GRAPHICS_CAMERA_H_
#define _TLOC_PREFAB_GRAPHICS_CAMERA_H_

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocGraphics/component_system/tlocProjectionComponent.h>

namespace tloc { namespace prefab { namespace graphics {

  void CreateCamera(Entity* a_ent,
                    EntityManager& a_mgr,
                    core::component_system::ComponentPoolManager& a_poolMgr)
  {
    TLOC_ASSERT(a_ent, "Entity cannot be NULL");

    using core::component_system;
    using math::component_system;
    using math::component_system::components;
    using graphics::component_system;
    using graphics::component_system::components;

    typedef ComponentPoolManager    pool_mgr;
    typedef pool_mgr::iterator      comp_pool;

    comp_pool cpool;

    // Get or create the transform pool
    if (a_poolMgr.Exists(transform) == false)
    { cpool = a_poolMgr.CreateNewPool(transform); }
    else
    { cpool = a_poolMgr.GetPool(transform); }

    comp_pool::iterator itr = cpool.GetNext();
    itr->GetElement() = new Transform();
    a_mgr.InsertComponent(a_ent, itr->GetElement()->Expose());

    // Get or create the projection pool
    if (a_poolMgr.Exists(projection) == false)
    { cpool = a_poolMgr.CreateNewPool(projection); }
    else
    { cpool = a_poolMgr.GetPool(projection); }
  }

};};};

#endif