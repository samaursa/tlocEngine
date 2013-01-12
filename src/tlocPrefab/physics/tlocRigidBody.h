#ifndef _TLOC_PREFAB_PHYSICS_RIGID_BODY_H_
#define _TLOC_PREFAB_PHYSICS_RIGID_BODY_H_

#include <tlocCore/tlocBase.h>

#include <tlocPhysics/component_system/tlocRigidBodyComponent.h>
#include <tlocPhysics/component_system/tlocRigidBodyShapeComponent.h>
#include <tlocPhysics/component_system/tlocRigidbodyListenerComponent.h>

namespace tloc { namespace prefab { namespace physics {

  core::component_system::Entity*
    CreateRigidBody(tloc::physics::box2d::rigid_body_def_sptr a_rbDef,
                    core::component_system::EntityManager& a_mgr,
                    core::component_system::ComponentPoolManager& a_poolMgr);

  void AddRigidBody(tloc::physics::box2d::rigid_body_def_sptr a_rbDef,
                    core::component_system::Entity* a_ent,
                    core::component_system::EntityManager& a_mgr,
                    core::component_system::ComponentPoolManager& a_poolMgr);

  void AddRigidBodyShape(const tloc::physics::box2d::RigidBodyShapeDef a_rbShape,
                         core::component_system::Entity* a_ent,
                         core::component_system::EntityManager& a_mgr,
                         core::component_system::ComponentPoolManager& a_poolMgr);

  void AddRigidBodyShape
    (const core::containers::
    tl_array<const tloc::physics::box2d::RigidBodyShapeDef>::type& a_rbShapes,
    core::component_system::Entity* a_ent,
    core::component_system::EntityManager& a_mgr,
    core::component_system::ComponentPoolManager& a_poolMgr);

  void AddRigidBodyListener(tloc::physics::RigidBodyListener* a_listener,
                            core::component_system::Entity* a_ent,
                            core::component_system::EntityManager& a_mgr,
                            core::component_system::ComponentPoolManager);

  template <typename T_Shape>
  void AddRigidBodyShape(const T_Shape a_shape, 
                         tl_float a_density,
                         core::component_system::Entity* a_ent,
                         core::component_system::EntityManager& a_mgr,
                         core::component_system::ComponentPoolManager& a_poolMgr)
  {
    tloc::physics::box2d::RigidBodyShapeDef rbShape(a_shape);
    rbShape.SetDensity(a_density);

    AddRigidBodyShape(rbShape, a_ent, a_mgr, a_poolMgr);
  }

};};};

#endif