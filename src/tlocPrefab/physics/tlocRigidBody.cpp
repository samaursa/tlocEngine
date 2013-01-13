#include "tlocRigidBody.h"

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/component_system/tlocEntityManager.h>

#include <tlocMath/component_system/tlocTransform.h>

#include <tlocMath/component_system/tlocComponentType.h>

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace prefab { namespace physics {

  using namespace core::containers;
  using namespace core::component_system;
  using tloc::physics::box2d::rigid_body_def_sptr;
  using tloc::physics::box2d::RigidBodyShapeDef;

  Entity*
    CreateRigidBody
    (EntityManager& a_mgr,
     ComponentPoolManager& a_poolMgr,
     rigid_body_def_sptr a_rbDef)
  {
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

    AddRigidBody(ent, a_mgr, a_poolMgr, a_rbDef);

    return ent;
  }

  void AddRigidBody
    (Entity* a_ent,
     EntityManager& a_mgr,
     ComponentPoolManager& a_poolMgr,
     rigid_body_def_sptr a_rbDef)
  {
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

  void AddRigidBodyShape(Entity* a_ent,
                         EntityManager& a_mgr,
                         ComponentPoolManager& a_poolMgr,
                         RigidBodyShapeDef a_rbShape)
  {
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    typedef ComponentPoolManager  pool_mgr;
    typedef pool_mgr::iterator    comp_pool_ptr;

    // Create the RigidBody (and the RigidBody pool if necessary)
    comp_pool_ptr cpool;
    if (a_poolMgr.Exists(k_rigidBodyShape) == false)
    { cpool = a_poolMgr.CreateNewPool<RigidBodyShapePtr>(k_rigidBodyShape); }
    else
    { cpool = a_poolMgr.GetPool(k_rigidBodyShape); }

    typedef rigid_body_shape_pool  rb_shape_pool;

    rb_shape_pool* rbShapePool = (*cpool)->GetAs<rb_shape_pool>();

    rb_shape_pool::iterator itrRbShape = rbShapePool->GetNext();
    itrRbShape->GetElement() = RigidBodyShapePtr(new RigidBodyShape(a_rbShape));

    a_mgr.InsertComponent(a_ent, &*(itrRbShape->GetElement()) );
  }

  void AddRigidBodyShape
    (Entity* a_ent,
     EntityManager& a_mgr,
     ComponentPoolManager& a_poolMgr,
     const core::containers::
     tl_array<const RigidBodyShapeDef>::type& a_rbShapes)
  {
    typedef tl_array<const RigidBodyShapeDef>::type
      rb_shape_ptr_array;

    typedef rb_shape_ptr_array::const_iterator  rb_const_iterator;

    rb_const_iterator itr = a_rbShapes.begin();
    const rb_const_iterator itrEnd = a_rbShapes.end();

    for (/* */; itr != itrEnd; ++itr)
    {
      AddRigidBodyShape(a_ent, a_mgr, a_poolMgr, *itr);
    }
  }

  void AddRigidBodyListener(Entity* a_ent,
                            EntityManager& a_mgr,
                            ComponentPoolManager& a_poolMgr,
                            tloc::physics::RigidBodyListener* a_listener)
  {
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    typedef ComponentPoolManager  pool_mgr;
    typedef pool_mgr::iterator    comp_pool_ptr;

    // Create the RigidBody (and the RigidBody pool if necessary)
    comp_pool_ptr cpool;
    if (a_poolMgr.Exists(k_rigidBodyListener) == false)
    { cpool = a_poolMgr.CreateNewPool<RigidBodyListenerPtr>(k_rigidBodyListener); }
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
