#include "tlocRigidBody.h"

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/component_system/tlocEntityManager.h>

#include <tlocMath/component_system/tlocTransform.h>

#include <tlocMath/component_system/tlocComponentType.h>

#include <tlocPhysics/component_system/tlocComponentType.h>

namespace tloc { namespace prefab { namespace physics {

  // ///////////////////////////////////////////////////////////////////////
  // RigidBody

  using namespace core_conts;
  using namespace core_cs;
  using tloc::physics::box2d::rigid_body_def_sptr;
  using tloc::physics::box2d::RigidBodyShapeDef;

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::entity_type*
    RigidBody::
    Create(const rb_def_sptr& a_rbDef)
  {
    using namespace math_cs;
    using namespace math_cs::components;

    typedef ComponentPoolManager                    pool_mgr;
    typedef tloc::math_cs::transform_f32_sptr_pool  t_pool;

    transform_f32_sptr_pool_sptr                    tPool;

    if (m_compPoolMgr->Exists(transform) == false)
    { tPool = m_compPoolMgr->CreateNewPool<transform_sptr>(); }
    else
    { tPool = m_compPoolMgr->GetPool<transform_sptr>(); }

    t_pool::iterator itrTransform = tPool->GetNext();
    itrTransform->SetValue(transform_sptr(new Transform()) );

    entity_type* ent = m_entMgr->CreateEntity();
    m_entMgr->InsertComponent(ent, &*(itrTransform->GetValue()) );

    Add(ent, a_rbDef);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    Add(entity_type* a_ent, const rb_def_sptr& a_rbDef)
  {
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    typedef ComponentPoolManager      pool_mgr;
    typedef rigid_body_sptr_pool      rb_pool;

    core_sptr::SharedPtr<rb_pool>     rbPool;

    // Create the RigidBody (and the RigidBody pool if necessary)
    if (m_compPoolMgr->Exists(k_rigidBody) == false)
    { rbPool = m_compPoolMgr->CreateNewPool<rigid_body_sptr>(); }
    else
    { rbPool = m_compPoolMgr->GetPool<rigid_body_sptr>(); }

    typedef rigid_body_sptr_pool      rb_pool;

    rb_pool::iterator itrRb = rbPool->GetNext();
    itrRb->SetValue(rigid_body_sptr(new phys_cs::RigidBody(a_rbDef)) );

    m_entMgr->InsertComponent(a_ent, &*(itrRb->GetValue()) );
  }

  // ///////////////////////////////////////////////////////////////////////
  // RigidBodyShape

  void
    RigidBodyShape::
    Add(Entity* a_ent, RigidBodyShapeDef a_rbShape)
  {
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    typedef ComponentPoolManager        pool_mgr;
    typedef rigid_body_shape_sptr_pool  rb_shape_pool;

    core_sptr::SharedPtr<rb_shape_pool> rbShapePool;

    // Create the RigidBody (and the RigidBody pool if necessary)
    if (m_compPoolMgr->Exists(k_rigidBodyShape) == false)
    { rbShapePool = m_compPoolMgr->CreateNewPool<rigid_body_shape_sptr>(); }
    else
    { rbShapePool = m_compPoolMgr->GetPool<rigid_body_shape_sptr>(); }


    rb_shape_pool::iterator itrRbShape = rbShapePool->GetNext();
    itrRbShape->SetValue(rigid_body_shape_sptr
      (new phys_cs::RigidBodyShape(a_rbShape)) );

    m_entMgr->InsertComponent(a_ent, &*(itrRbShape->GetValue()) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBodyShape::
    Add(entity_type* a_ent, const rb_shape_def_cont& a_rbShapes)
  {
    typedef tl_array<const RigidBodyShapeDef>::type
      rb_shape_ptr_array;

    typedef rb_shape_ptr_array::const_iterator  rb_const_iterator;

    rb_const_iterator itr = a_rbShapes.begin();
    const rb_const_iterator itrEnd = a_rbShapes.end();

    for (/* */; itr != itrEnd; ++itr)
    {
      Add(a_ent, *itr);
    }
  }

  // ///////////////////////////////////////////////////////////////////////
  // RigidBodyListener

  void
    RigidBodyListener::
    Add(entity_type* a_ent, rb_listener* a_listener)
  {
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    typedef ComponentPoolManager            pool_mgr;
    typedef rigid_body_listener_sptr_pool   rb_listener_pool;

    rigid_body_listener_sptr_pool_sptr      rbListenerPool;

    // Create the RigidBody (and the RigidBody pool if necessary)
    if (m_compPoolMgr->Exists(k_rigidBodyListener) == false)
    { rbListenerPool = m_compPoolMgr->CreateNewPool<rigid_body_listener_sptr>(); }
    else
    { rbListenerPool = m_compPoolMgr->GetPool<rigid_body_listener_sptr>(); }

    typedef rigid_body_listener_sptr_pool rb_listener_pool;

    rb_listener_pool::iterator itrRbListener = rbListenerPool->GetNext();
    itrRbListener->SetValue
      (rigid_body_listener_sptr( new rb_listener_comp(a_listener)) );

    m_entMgr->InsertComponent(a_ent, itrRbListener->GetValue().get() );
  }

};};};
