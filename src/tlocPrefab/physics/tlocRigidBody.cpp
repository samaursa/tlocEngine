#include "tlocRigidBody.h"

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/component_system/tlocEntityManager.h>

#include <tlocMath/component_system/tlocTransform.h>

#include <tlocMath/component_system/tlocComponentType.h>

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace prefab { namespace physics {

  core::component_system::Entity*
    CreateRigidBody(const tloc::physics::box2d::RigidBodyDef& a_rbDef,
                    core::component_system::EntityManager& a_mgr,
                    core::component_system::ComponentPoolManager& a_poolMgr)
  {
    using namespace core::component_system;
    using namespace math::component_system;
    using namespace math::component_system::components;

    typedef ComponentPoolManager  pool_mgr;
    typedef pool_mgr::iterator    comp_pool_ptr;

    comp_pool_ptr cpool;

    if (a_poolMgr.Exists(transform) == false)
    { cpool = a_poolMgr.CreateNewPool<TransformPtr>(transform); }
    else
    { cpool = a_poolMgr.GetPool(transform); }

    typedef TransformPool t_pool;

    t_pool * tPool = (*cpool)->GetAs<t_pool>();

    t_pool::iterator itrTransform = tPool->GetNext();
    itrTransform->GetElement() = new Transform();

    Entity* ent = a_mgr.CreateEntity();
    a_mgr.InsertComponent(ent, &*(itrTransform->GetElement()) );

    AddRigidBody(a_rbDef, ent, a_mgr, a_poolMgr);

    return ent;
  }

  void AddRigidBody(const tloc::physics::box2d::RigidBodyDef& a_rbDef,
                    core::component_system::Entity* a_ent,
                    core::component_system::EntityManager& a_mgr,
                    core::component_system::ComponentPoolManager& a_poolMgr)
  {
    using namespace core::component_system;
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    typedef ComponentPoolManager  pool_mgr;
    typedef pool_mgr::iterator    comp_pool_ptr;

    // Create the RigidBody (and the RigidBody pool if necessary)
    comp_pool_ptr cpool;
    if (a_poolMgr.Exists(k_rigid_body) == false)
    { cpool = a_poolMgr.CreateNewPool<RigidBodyPtr>(k_rigid_body); }
    else
    { cpool = a_poolMgr.GetPool(k_rigid_body); }

    typedef rigid_body_pool  rb_pool;

    rb_pool* rbPool = (*cpool)->GetAs<rb_pool>();

    rb_pool::iterator itrRb = rbPool->GetNext();
    itrRb->GetElement() = new RigidBody(a_rbDef);

    a_mgr.InsertComponent(a_ent, &*(itrRb->GetElement()) );
  }

  void AddRigidBodyShape(const tloc::physics::box2d::RigidBodyShape* a_rbShape,
                         core::component_system::Entity* a_ent,
                         core::component_system::EntityManager& a_mgr,
                         core::component_system::ComponentPoolManager& a_poolMgr)
  {
    using namespace core::component_system;
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    typedef ComponentPoolManager  pool_mgr;
    typedef pool_mgr::iterator    comp_pool_ptr;

    // Create the RigidBody (and the RigidBody pool if necessary)
    comp_pool_ptr cpool;
    if (a_poolMgr.Exists(k_rigid_body_shape) == false)
    { cpool = a_poolMgr.CreateNewPool<RigidBodyPtr>(k_rigid_body_shape); }
    else
    { cpool = a_poolMgr.GetPool(k_rigid_body_shape); }

    typedef rigid_body_shape_pool  rb_shape_pool;

    rb_shape_pool* rbShapePool = (*cpool)->GetAs<rb_shape_pool>();

    rb_shape_pool::iterator itrRbShape = rbShapePool->GetNext();
    itrRbShape->GetElement() = new RigidBodyShape(a_rbShape);

    a_mgr.InsertComponent(a_ent, &*(itrRbShape->GetElement()) );
  }

  void AddRigidBodyShape
    (const core::tl_array<const tloc::physics::box2d::RigidBodyShape*>::type a_rbShapes,
    core::component_system::Entity* a_ent,
    core::component_system::EntityManager& a_mgr,
    core::component_system::ComponentPoolManager& a_poolMgr)
  {
    typedef core::tl_array<const tloc::physics::box2d::RigidBodyShape*>::type
      rb_shape_ptr_array;

    typedef rb_shape_ptr_array::const_iterator  rb_const_iterator;

    rb_const_iterator itr = a_rbShapes.begin();
    const rb_const_iterator itrEnd = a_rbShapes.end();

    for (/* */; itr != itrEnd; ++itr)
    {
      AddRigidBodyShape(*itr, a_ent, a_mgr, a_poolMgr);
    }
  }

  void AddRigidBodyListener(tloc::physics::RigidBodyListener* a_listener,
                            core::component_system::Entity* a_ent,
                            core::component_system::EntityManager& a_mgr,
                            core::component_system::ComponentPoolManager& a_poolMgr)
  {
    using namespace core::component_system;
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    typedef ComponentPoolManager  pool_mgr;
    typedef pool_mgr::iterator    comp_pool_ptr;

    // Create the RigidBody (and the RigidBody pool if necessary)
    comp_pool_ptr cpool;
    if (a_poolMgr.Exists(k_rigid_body_listener) == false)
    { cpool = a_poolMgr.CreateNewPool<RigidBodyPtr>(k_rigid_body_listener); }
    else
    { cpool = a_poolMgr.GetPool(k_rigid_body_listener); }

    typedef rigid_body_listener_pool rb_listener_pool;

    rb_listener_pool* rbListenerPool = (*cpool)->GetAs<rb_listener_pool>();

    rb_listener_pool::iterator itrRbListener = rbListenerPool->GetNext();
    itrRbListener->GetElement() = new RigidBodyListener(a_listener);

    a_mgr.InsertComponent(a_ent, &*(itrRbListener->GetElement()) );
  }

};};};
