#include "tlocTestCommon.h"

#include <tlocCore/error/tlocError.h>

#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntity.inl>

#include <tlocMath/tlocMath.h>
#include <tlocMath/component_system/tlocTransform.h>

#include <tlocPhysics/box2d/tlocPhysicsManager.h>
#include <tlocPhysics/box2d/tlocRigidBodyShape.h>
#include <tlocPhysics/box2d/tlocCircleShape.h>
#include <tlocPhysics/box2d/tlocRigidBodyDef.h>

#include <tlocPhysics/component_system/tlocRigidBodyShapeComponent.h>
#include <tlocPhysics/component_system/tlocRigidBodyComponent.h>
#include <tlocPhysics/component_system/tlocRigidBodySystem.h>

namespace TestingRigidBodySystem
{
  using namespace tloc;
  using namespace tloc::physics;
  using namespace tloc::physics::component_system;

  struct RigidBodySystemFixture
  {
    typedef core::error::Error  error_type;

    typedef core::component_system::EventManager  event_manager;
    typedef core::component_system::EntityManager entity_manager;
    typedef core::component_system::Entity        entity_type;

    typedef math::component_system::Transform transform_type;

    typedef box2d::PhysicsManager physics_manager;
    typedef box2d::RigidBodyShape rigid_body_shape;
    typedef box2d::CircleShape    circle_shape_type;
    typedef box2d::RigidBodyDef   rigid_body_def_type;

    typedef RigidBodyShape  rigid_body_shape_component;
    typedef RigidBody       rigid_body_component;

    typedef rigid_body_component::rigid_body_type::vec_type  vec_type;

    typedef RigidBodySystem rigid_body_system;
  };

  typedef RigidBodySystemFixture rb_sys_fixture;

  TEST_CASE("Physics/component_system/RigidBodySystem/General", "")
  {
    const float gravityY = -1000.0f;

    // Initialize essential systems
    rb_sys_fixture::physics_manager physicsMgr;
    rb_sys_fixture::physics_manager::vec_type gravity(0.0f, gravityY);

    physicsMgr.Initialize(rb_sys_fixture::physics_manager::gravity(gravity));

    rb_sys_fixture::event_manager evntMgr;
    rb_sys_fixture::entity_manager entityMgr(&evntMgr);

    rb_sys_fixture::rigid_body_system
      rigidBodySys(&evntMgr, &entityMgr, &physicsMgr.GetWorld());

    // Create a static rigid body entity
    rb_sys_fixture::entity_type* rbStaticEntity = entityMgr.CreateEntity();

    rb_sys_fixture::transform_type transformComponent1;

    rb_sys_fixture::rigid_body_component rbStaticComponent;

    rb_sys_fixture::circle_shape_type circleShape;
    circleShape.SetRadius(1.0f);

    rb_sys_fixture::rigid_body_shape rbCircleShape(&circleShape);
    rb_sys_fixture::rigid_body_shape_component rbShapeComponent1(&rbCircleShape);

    entityMgr.InsertComponent(rbStaticEntity, &transformComponent1);
    entityMgr.InsertComponent(rbStaticEntity, &rbStaticComponent);
    entityMgr.InsertComponent(rbStaticEntity, &rbShapeComponent1);

    // Create a dynamic rigid body
    rb_sys_fixture::entity_type* rbDynamicEntity = entityMgr.CreateEntity();

    rb_sys_fixture::transform_type transformComponent2;

    const float rbDynamicStartPositionY = 3.0f;

    rb_sys_fixture::rigid_body_def_type rbDef;
    rbDef.SetType(box2d::rigid_body::k_dynamicBody);
    rbDef.SetPosition(rb_sys_fixture::vec_type(0.0f, rbDynamicStartPositionY));

    rb_sys_fixture::rigid_body_component rbDynamicComponent(rbDef);

    rb_sys_fixture::rigid_body_shape_component rbShapeComponent2(&rbCircleShape);

    entityMgr.InsertComponent(rbDynamicEntity, &transformComponent2);
    entityMgr.InsertComponent(rbDynamicEntity, &rbDynamicComponent);
    entityMgr.InsertComponent(rbDynamicEntity, &rbShapeComponent2);

    CHECK(rigidBodySys.Initialize() == ErrorSuccess());

    // Update everything once so everything is in the right position
    rigidBodySys.ProcessActiveEntities();

    rb_sys_fixture::vec_type position;
    rbDynamicComponent.GetRigidBody().GetPosition(position);
    CHECK(position[1] == Approx(3.0f));

    // Note: The "tolerance" of 0.25f is only valid within the first 4
    // iterations on the Box2D platform. Adjust if necessary.
    const tl_float tolerance = 0.25f;

    rb_sys_fixture::vec_type previousPosition;
    const tl_float timeStep = 0.01f;
    const tl_size maxIterations = 4;

    // Ball is falling. At the end of the max iterations it will hit
    // another ball and stop
    for (tl_size i = 0; i < maxIterations; ++i)
    {
      physicsMgr.Update(timeStep);
      rigidBodySys.ProcessActiveEntities();

      previousPosition = position;
      rbDynamicComponent.GetRigidBody().GetPosition(position);
      CHECK((previousPosition != position));

      // +1 since we've already told the physics manager to move "ahead" one step.
      float time = timeStep * (i + 1);
      float calculatedPositionY =
        rbDynamicStartPositionY + 0.5f * gravityY * time * time;

      CHECK(Mathf::Approx(calculatedPositionY, position[1], tolerance));
    }

    // Update one more time. The ball should have hit the floor and "stopped"
    // thus having the same position
    {
      physicsMgr.Update(timeStep);
      rigidBodySys.ProcessActiveEntities();

      previousPosition = position;
      rbDynamicComponent.GetRigidBody().GetPosition(position);
      CHECK((position == previousPosition));
    }

    CHECK(rigidBodySys.Shutdown() == ErrorSuccess());
    CHECK(physicsMgr.Shutdown() == ErrorSuccess());
  }
};