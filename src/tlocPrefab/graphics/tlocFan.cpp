#include "tlocFan.h"

#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocGraphics/component_system/tlocFan.h>

namespace tloc { namespace prefab { namespace graphics {

  using core::component_system::Entity;
  using core::component_system::EntityManager;
  using core::component_system::ComponentPoolManager;

  using math::types::Circle;

  template <typename T_Real>
  core::component_system::Entity*
    CreateFan(core::component_system::EntityManager& a_mgr,
              core::component_system::ComponentPoolManager& a_poolMgr,
              math::types::Circle<T_Real> a_circle,
              tl_size a_numSides)
  {
    using namespace core::component_system;
    using namespace math::component_system;
    using namespace math::component_system::components;
    using namespace tloc::graphics::component_system;
    using namespace tloc::graphics::component_system::components;

    typedef ComponentPoolManager    pool_mgr;
    typedef pool_mgr::iterator      comp_pool_ptr;

    // Create the fan (and the fan pool if necessary)
    comp_pool_ptr cpool;
    if (a_poolMgr.Exists(fan) == false)
    { cpool = a_poolMgr.CreateNewPool<FanPtr>(fan); }
    else
    { cpool = a_poolMgr.GetPool(fan); }

    typedef tloc::graphics::component_system::FanPool fan_pool;

    fan_pool* fanPool = (*cpool)->GetAs<fan_pool>();

    fan_pool::iterator itr = fanPool->GetNext();
    itr->GetElement() = FanPtr(new Fan(a_circle, Fan::sides(a_numSides) ) );

    // Create the transform component (and the transform pool if necessary)
    cpool;

    if (a_poolMgr.Exists(transform) == false)
    { cpool = a_poolMgr.CreateNewPool<TransformPtr>(transform); }
    else
    { cpool = a_poolMgr.GetPool(transform); }

    typedef tloc::math::component_system::TransformPool  t_pool;

    t_pool* tPool = (*cpool)->GetAs<t_pool>();

    t_pool::iterator itrTransform = tPool->GetNext();
    itrTransform->GetElement() = TransformPtr(new Transform());

    // Create an entity from the manager and return to user
    Entity* ent = a_mgr.CreateEntity();
    a_mgr.InsertComponent(ent, &*(itrTransform->GetElement()) );
    a_mgr.InsertComponent(ent, &*(itr->GetElement()) );

    return ent;
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit Instantiations

   template Entity* CreateFan<f32>(EntityManager&, ComponentPoolManager&,
                                   Circle<f32>, tl_size);

};};};