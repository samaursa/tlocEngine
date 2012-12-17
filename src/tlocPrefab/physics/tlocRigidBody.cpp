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
    itrTransform->GetElement() = TransformPtr(new Transform());

    Entity* ent = a_mgr.CreateEntity();
    a_mgr.InsertComponent(ent, &*(itrTransform->GetElement()) );

    AddRigidBody(a_rbDef, ent, a_mgr, a_poolMgr);

    return ent;
  }

  void AddRigidBody(const tloc::physics::box2d::RigidBodyDef a_rbDef,
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
    if (a_poolMgr.Exists(k_rigidBody) == false)
    { cpool = a_poolMgr.CreateNewPool<RigidBodyPtr>(k_rigidBody); }
    else
    { cpool = a_poolMgr.GetPool(k_rigidBody); }

    typedef rigid_body_pool  rb_pool;

    rb_pool* rbPool = (*cpool)->GetAs<rb_pool>();

    rb_pool::iterator itrRb = rbPool->GetNext();
    itrRb->GetElement() = RigidBodyPtr(new RigidBody(a_rbDef));

    a_mgr.InsertComponent(a_ent, &*(itrRb->GetElement()) );
  }

  void AddRigidBodyShape(const tloc::physics::box2d::RigidBodyShapeDef* a_rbShape,
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
    if (a_poolMgr.Exists(k_rigidBodyShape) == false)
    { cpool = a_poolMgr.CreateNewPool<RigidBodyPtr>(k_rigidBodyShape); }
    else
    { cpool = a_poolMgr.GetPool(k_rigidBodyShape); }

    typedef rigid_body_shape_pool  rb_shape_pool;

    rb_shape_pool* rbShapePool = (*cpool)->GetAs<rb_shape_pool>();

    rb_shape_pool::iterator itrRbShape = rbShapePool->GetNext();
    itrRbShape->GetElement() = RigidBodyShapePtr(new RigidBodyShape(a_rbShape));

    a_mgr.InsertComponent(a_ent, &*(itrRbShape->GetElement()) );
  }

  void AddRigidBodyShape
    (const core::
    tl_array<const tloc::physics::box2d::RigidBodyShapeDef*>::type& a_rbShapes,
    core::component_system::Entity* a_ent,
    core::component_system::EntityManager& a_mgr,
    core::component_system::ComponentPoolManager& a_poolMgr)
  {
    typedef core::tl_array<const tloc::physics::box2d::RigidBodyShapeDef*>::type
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
    if (a_poolMgr.Exists(k_rigidBodyListener) == false)
    { cpool = a_poolMgr.CreateNewPool<RigidBodyPtr>(k_rigidBodyListener); }
    else
    { cpool = a_poolMgr.GetPool(k_rigidBodyListener); }

    typedef rigid_body_listener_pool rb_listener_pool;

    rb_listener_pool* rbListenerPool = (*cpool)->GetAs<rb_listener_pool>();

    rb_listener_pool::iterator itrRbListener = rbListenerPool->GetNext();
    itrRbListener->GetElement() =
      RigidBodyListenerPtr(new RigidBodyListener(a_listener));

    a_mgr.InsertComponent(a_ent, &*(itrRbListener->GetElement()) );
  }

};};};
