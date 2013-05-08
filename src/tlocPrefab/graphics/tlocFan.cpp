#include "tlocFan.h"

#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocGraphics/component_system/tlocFan.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

  using math_t::Circle_T;

  core_cs::Entity*
    CreateFan(core_cs::EntityManager& a_mgr,
              core_cs::ComponentPoolManager& a_poolMgr,
              math_t::Circlef32 a_circle,
              tl_size a_numSides)
  {
    using namespace core_cs;
    using namespace math_cs;
    using namespace math_cs::components;
    using namespace tloc::graphics::component_system;
    using namespace tloc::graphics::component_system::components;

    typedef ComponentPoolManager    pool_mgr;
    typedef gfx_cs::fan_sptr_pool   fan_pool;

    gfx_cs::fan_sptr_pool_sptr      fanPool;

    // Create the fan (and the fan pool if necessary)
    if (a_poolMgr.Exists(fan) == false)
    { fanPool = a_poolMgr.CreateNewPool<fan_sptr>(); }
    else
    { fanPool = a_poolMgr.GetPool<fan_sptr>(); }

    fan_pool::iterator itr = fanPool->GetNext();
    itr->SetValue(fan_sptr(new Fan(a_circle, Fan::sides(a_numSides)) ) );


    typedef math_cs::transform_f32_sptr_pool  t_pool;
    math_cs::transform_f32_sptr_pool_sptr     tPool;

    if (a_poolMgr.Exists(transform) == false)
    { tPool = a_poolMgr.CreateNewPool<transform_sptr>(); }
    else
    { tPool = a_poolMgr.GetPool<transform_sptr>(); }

    t_pool::iterator itrTransform = tPool->GetNext();
    itrTransform->SetValue(transform_sptr(new Transform()) );

    // Create an entity from the manager and return to user
    Entity* ent = a_mgr.CreateEntity();
    a_mgr.InsertComponent(ent, &*(itrTransform->GetValue()) );
    a_mgr.InsertComponent(ent, &*(itr->GetValue()) );

    return ent;
  }

};};};