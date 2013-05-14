#include "tlocRigidBody.h"

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/component_system/tlocEntityManager.h>

#include <tlocMath/component_system/tlocTransform.h>

#include <tlocMath/component_system/tlocComponentType.h>

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace prefab { namespace physics {

  using namespace core_conts;
  using namespace core_cs;
  using tloc::physics::box2d::rigid_body_def_sptr;
  using tloc::physics::box2d::RigidBodyShapeDef;

  Entity*
    CreateRigidBody
    (EntityManager& a_mgr,
     ComponentPoolManager& a_poolMgr,
     rigid_body_def_sptr a_rbDef)
  {
    using namespace math_cs;
    using namespace math_cs::components;

    typedef ComponentPoolManager                    pool_mgr;
    typedef tloc::math_cs::transform_f32_sptr_pool  t_pool;

    transform_f32_sptr_pool_sptr                    tPool;

    if (a_poolMgr.Exists(transform) == false)
    { tPool = a_poolMgr.CreateNewPool<transform_sptr>(); }
    else
    { tPool = a_poolMgr.GetPool<transform_sptr>(); }

    t_pool::iterator itrTransform = tPool->GetNext();
    itrTransform->SetValue(transform_sptr(new Transform()) );

    Entity* ent = a_mgr.CreateEntity();
    a_mgr.InsertComponent(ent, &*(itrTransform->GetValue()) );

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

    typedef ComponentPoolManager      pool_mgr;
    typedef rigid_body_sptr_pool      rb_pool;

    core_sptr::SharedPtr<rb_pool>     rbPool;

    // Create the RigidBody (and the RigidBody pool if necessary)
    if (a_poolMgr.Exists(k_rigidBody) == false)
    { rbPool = a_poolMgr.CreateNewPool<rigid_body_sptr>(); }
    else
    { rbPool = a_poolMgr.GetPool<rigid_body_sptr>(); }

    typedef rigid_body_sptr_pool      rb_pool;

    rb_pool::iterator itrRb = rbPool->GetNext();
    itrRb->SetValue(rigid_body_sptr(new RigidBody(a_rbDef)) );

    a_mgr.InsertComponent(a_ent, &*(itrRb->GetValue()) );
  }

  void AddRigidBodyShape(Entity* a_ent,
                         EntityManager& a_mgr,
                         ComponentPoolManager& a_poolMgr,
                         RigidBodyShapeDef a_rbShape)
  {
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    typedef ComponentPoolManager        pool_mgr;
    typedef rigid_body_shape_sptr_pool  rb_shape_pool;

    core_sptr::SharedPtr<rb_shape_pool> rbShapePool;

    // Create the RigidBody (and the RigidBody pool if necessary)
    if (a_poolMgr.Exists(k_rigidBodyShape) == false)
    { rbShapePool = a_poolMgr.CreateNewPool<rigid_body_shape_sptr>(); }
    else
    { rbShapePool = a_poolMgr.GetPool<rigid_body_shape_sptr>(); }


    rb_shape_pool::iterator itrRbShape = rbShapePool->GetNext();
    itrRbShape->SetValue(rigid_body_shape_sptr(new RigidBodyShape(a_rbShape)) );

    a_mgr.InsertComponent(a_ent, &*(itrRbShape->GetValue()) );
  }

  void AddRigidBodyShape
    (Entity* a_ent,
     EntityManager& a_mgr,
     ComponentPoolManager& a_poolMgr,
     const core_conts::
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

    typedef ComponentPoolManager            pool_mgr;
    typedef rigid_body_listener_sptr_pool   rb_listener_pool;

    rigid_body_listener_sptr_pool_sptr      rbListenerPool;

    // Create the RigidBody (and the RigidBody pool if necessary)
    if (a_poolMgr.Exists(k_rigidBodyListener) == false)
    { rbListenerPool = a_poolMgr.CreateNewPool<rigid_body_listener_sptr>(); }
    else
    { rbListenerPool = a_poolMgr.GetPool<rigid_body_listener_sptr>(); }

    typedef rigid_body_listener_sptr_pool rb_listener_pool;

    rb_listener_pool::iterator itrRbListener = rbListenerPool->GetNext();
    itrRbListener->SetValue
      (rigid_body_listener_sptr(new RigidBodyListener(a_listener)) );

    a_mgr.InsertComponent(a_ent, &*(itrRbListener->GetValue()) );
  }

};};};
