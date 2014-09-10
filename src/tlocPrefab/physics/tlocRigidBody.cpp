#include "tlocRigidBody.h"

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/component_system/tlocEntityManager.h>

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocPhysics/component_system/tlocComponentType.h>

#include <tlocPrefab/math/tlocTransform.h>

namespace tloc { namespace prefab { namespace physics {

  using namespace core_conts;
  using namespace core_cs;
  using tloc::physics::box2d::rigid_body_def_sptr;
  using tloc::physics::box2d::RigidBodyShapeDef;

  // ///////////////////////////////////////////////////////////////////////
  // RigidBody

  RigidBody::
    RigidBody(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : Prefab_TI(a_entMgr, a_poolMgr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::component_ptr
    RigidBody::
    Construct(const rb_def_sptr& a_rbDef) const
  {
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    typedef ComponentPoolManager      pool_mgr;
    typedef rigid_body_pool           rb_pool;

    rigid_body_pool_vptr rbPool
      = m_compPoolMgr->GetOrCreatePool<phys_cs::RigidBody>();

    rb_pool::iterator itrRb = rbPool->GetNext();
    (*itrRb)->SetValue(core_sptr::MakeShared<phys_cs::RigidBody>(a_rbDef) );

    return *(*itrRb)->GetValuePtr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBody::entity_ptr
    RigidBody::
    Create(const rb_def_sptr& a_rbDef) const
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
    Add(entity_ptr a_ent, const rb_def_sptr& a_rbDef) const
  {
    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // RigidBody component

    m_entMgr->InsertComponent(insert_params(a_ent, Construct(a_rbDef))
                              .DispatchTo(GetListeners()) );
  }

  // ///////////////////////////////////////////////////////////////////////
  // RigidBodyShape

  RigidBodyShape::
    RigidBodyShape(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : Prefab_TI(a_entMgr, a_poolMgr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodyShape::component_ptr
    RigidBodyShape::
    Construct(rb_shape_def a_rbShapeDef) const
  { 
    using namespace tloc::physics::component_system;
    using namespace tloc::physics::component_system::components;

    typedef ComponentPoolManager        pool_mgr;
    typedef rigid_body_shape_pool       rb_shape_pool;

    rigid_body_shape_pool_vptr rbShapePool 
      = m_compPoolMgr->GetOrCreatePool<phys_cs::RigidBodyShape>();

    rb_shape_pool::iterator itrRbShape = rbShapePool->GetNext();
    (*itrRbShape)->SetValue
      (core_sptr::MakeShared<phys_cs::RigidBodyShape>(a_rbShapeDef) );

    return *(*itrRbShape)->GetValuePtr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBodyShape::
    Add(entity_ptr a_ent, RigidBodyShapeDef a_rbShape) const
  {
    m_entMgr->InsertComponent(insert_params(a_ent, Construct(a_rbShape))
                              .DispatchTo(GetListeners()).Orphan(true));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBodyShape::
    Add(entity_ptr a_ent, const rb_shape_def_cont& a_rbShapes) const
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

  RigidBodyListener::
    RigidBodyListener(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : Prefab_TI(a_entMgr, a_poolMgr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RigidBodyListener::component_ptr
    RigidBodyListener::
    Construct(rb_listener_ptr a_listener) const
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

    return *(*itrRbListener)->GetValuePtr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    RigidBodyListener::
    Add(entity_ptr a_ent, rb_listener_ptr a_listener) const
  {
    m_entMgr->InsertComponent(insert_params(a_ent, Construct(a_listener))
                              .DispatchTo(GetListeners()));
  }

};};};
