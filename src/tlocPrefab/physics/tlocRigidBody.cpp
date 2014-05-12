#include "tlocRigidBody.h"

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/component_system/tlocEntityManager.h>

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocPhysics/component_system/tlocComponentType.h>

#include <tlocPrefab/math/tlocTransform.h>

namespace tloc { namespace prefab { namespace physics {

  // ///////////////////////////////////////////////////////////////////////
  // RigidBody

  using namespace core_conts;
  using namespace core_cs;
  using tloc::physics::box2d::rigid_body_def_sptr;
  using tloc::physics::box2d::RigidBodyShapeDef;

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::entity_ptr
    RigidBody::
    Create(const rb_def_sptr& a_rbDef)
  {
    using namespace math_cs;
    using namespace math_cs::components;

    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_rbDef);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBody::
    Add(entity_ptr a_ent, const rb_def_sptr& a_rbDef)
  {
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // RigidBody component

    typedef ComponentPoolManager      pool_mgr;
    typedef rigid_body_pool           rb_pool;

    rigid_body_pool_vptr rbPool
      = m_compPoolMgr->GetOrCreatePool<phys_cs::RigidBody>();

    rb_pool::iterator itrRb = rbPool->GetNext();
    (*itrRb)->SetValue(core_sptr::MakeShared<phys_cs::RigidBody>(a_rbDef) );

    m_entMgr->InsertComponent(a_ent, *(*itrRb)->GetValuePtr() );
  }

  // ///////////////////////////////////////////////////////////////////////
  // RigidBodyShape

  void
    RigidBodyShape::
    Add(entity_ptr a_ent, RigidBodyShapeDef a_rbShape)
  {
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    typedef ComponentPoolManager        pool_mgr;
    typedef rigid_body_shape_pool       rb_shape_pool;

    rigid_body_shape_pool_vptr rbShapePool 
      = m_compPoolMgr->GetOrCreatePool<phys_cs::RigidBodyShape>();

    rb_shape_pool::iterator itrRbShape = rbShapePool->GetNext();
    (*itrRbShape)->SetValue
      (core_sptr::MakeShared<phys_cs::RigidBodyShape>(a_rbShape) );

    m_entMgr->
      InsertComponent(a_ent, *(*itrRbShape)->GetValuePtr(), 
                      EntityManager::orphan(true) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBodyShape::
    Add(entity_ptr a_ent, const rb_shape_def_cont& a_rbShapes)
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
    Add(entity_ptr a_ent, rb_listener_ptr a_listener)
  {
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    typedef ComponentPoolManager                pool_mgr;
    typedef rigid_body_listener_pool            rb_listener_pool;

    rigid_body_listener_pool_vptr rbListenerPool
      = m_compPoolMgr->GetOrCreatePool<phys_cs::RigidBodyListener>();

    rb_listener_pool::iterator itrRbListener = rbListenerPool->GetNext();
    (*itrRbListener)->SetValue
      ( core_sptr::MakeShared<phys_cs::RigidBodyListener>(a_listener) );

    m_entMgr->InsertComponent(a_ent, *(*itrRbListener)->GetValuePtr() );
  }

};};};
