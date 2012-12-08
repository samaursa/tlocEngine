#include "tlocTestCommon.h"

#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntity.inl>

#include <tlocPhysics/box2d/tlocPhysicsManager.h>
#include <tlocPhysics/box2d/tlocRigidBodyShape.h>
#include <tlocPhysics/box2d/tlocCircleShape.h>

#include <tlocPhysics/component_system/tlocRigidBodyShapeComponent.h>
#include <tlocPhysics/component_system/tlocRigidBodyComponent.h>
#include <tlocPhysics/component_system/tlocRigidBodySystem.h>

namespace TestingRigidBodySystem
{
  using namespace tloc;
  using namespace tloc::physics;
  using namespace tloc::physics::component_system;

  TEST_CASE("Physics/component_system/RigidBodySystem/General", "")
  {
    typedef core::component_system::EventManager  event_manager;
    typedef core::component_system::EntityManager entity_manager;
    typedef core::component_system::Entity        entity_type;

    typedef box2d::PhysicsManager physics_manager;
    typedef box2d::RigidBodyShape rigid_body_shape;
    typedef box2d::CircleShape    circle_shape_type;

    typedef RigidBody       rigid_body_component;
    typedef RigidBodyShape  rigid_body_shape_component;

    typedef RigidBodySystem rigid_body_system;

    // Initialize essential systems
    physics_manager physicsMgr;
    physics_manager::vec_type gravity(0.0f, -1000.0f);

    physicsMgr.Initialize(physics_manager::gravity(gravity));

    event_manager evntMgr;
    entity_manager entityMgr(&evntMgr);

    rigid_body_system rigidBodySys(&evntMgr, &entityMgr, &physicsMgr.GetWorld());

    // Create a rigid body entity
    entity_type* rbEntity = entityMgr.CreateEntity();

    rigid_body_component rbComponent;

    circle_shape_type circleShape;
    circleShape.SetRadius(1.0f);

    rigid_body_shape rbCircleShape(&circleShape);
    rigid_body_shape_component rbShapeComponent(&rbCircleShape);

    entityMgr.InsertComponent(rbEntity, &rbComponent);
    entityMgr.InsertComponent(rbEntity, &rbShapeComponent);

    rigidBodySys.Initialize();
  }
};