#ifndef _TLOC_PREFAB_PHYSICS_RIGID_BODY_H_
#define _TLOC_PREFAB_PHYSICS_RIGID_BODY_H_

#include <tlocCore/tlocBase.h>

#include <tlocPhysics/component_system/tlocRigidBodyComponent.h>
#include <tlocPhysics/component_system/tlocRigidBodyShapeComponent.h>
#include <tlocPhysics/component_system/tlocRigidbodyListenerComponent.h>

namespace tloc { namespace prefab { namespace physics {

  core::component_system::Entity*
    CreateRigidBody(core::component_system::EntityManager& a_mgr,
                    core::component_system::ComponentPoolManager& a_poolMgr,
                    tloc::physics::box2d::rigid_body_def_sptr a_rbDef);

  void AddRigidBody(core::component_system::Entity* a_ent,
                    core::component_system::EntityManager& a_mgr,
                    core::component_system::ComponentPoolManager& a_poolMgr,
                    tloc::physics::box2d::rigid_body_def_sptr a_rbDef);

  void AddRigidBodyShape(core::component_system::Entity* a_ent,
                         core::component_system::EntityManager& a_mgr,
                         core::component_system::ComponentPoolManager& a_poolMgr,
                         const tloc::physics::box2d::RigidBodyShapeDef a_rbShape);

  void AddRigidBodyShape
    (core::component_system::Entity* a_ent,
     core::component_system::EntityManager& a_mgr,
     core::component_system::ComponentPoolManager& a_poolMgr,
     const core::containers::
     tl_array<const tloc::physics::box2d::RigidBodyShapeDef>::type& a_rbShapes);

  void AddRigidBodyListener(core::component_system::Entity* a_ent,
                            core::component_system::EntityManager& a_mgr,
                            core::component_system::ComponentPoolManager,
                            tloc::physics::RigidBodyListener* a_listener);

  template <typename T_Shape>
  void AddRigidBodyShape(core::component_system::Entity* a_ent,
                         core::component_system::EntityManager& a_mgr,
                         core::component_system::ComponentPoolManager& a_poolMgr,
                         const T_Shape a_shape, 
                         tl_float a_density)
  {
    tloc::physics::box2d::RigidBodyShapeDef rbShape(a_shape);
    rbShape.SetDensity(a_density);

    AddRigidBodyShape(a_ent, a_mgr, a_poolMgr, rbShape);
  }

};};};

#endif