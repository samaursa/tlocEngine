#include "tlocRigidBodySystem.h"

#include <tlocCore/component_system/tlocComponentMapper.h>

#include <tlocPhysics/component_system/tlocRigidBody.h>
#include <tlocPhysics/component_system/tlocFixture.h>

namespace tloc { namespace physics { namespace box2d { namespace component_system {

  RigidBodySystem::RigidBodySystem
    (event_manager* a_eventMgr, entity_manager* a_entityMgr, world_type* a_world)
    : base_type(a_eventMgr, a_entityMgr
    , core::Variadic<component_type, 1>(components::k_rigid_body))
    , m_world(a_world)
  {
  }

  RigidBodySystem::error_type RigidBodySystem::Initialize()
  {
    return ErrorSuccess();
  }

  RigidBodySystem::error_type RigidBodySystem::Shutdown()
  {
    return ErrorSuccess();
  }

  void RigidBodySystem::ProcessEntity(entity_manager* a_mgr, entity_type* a_ent)
  {
    using namespace core::component_system;

    const entity_type* ent = a_ent;
    ComponentMapper<RigidBody> rigidBodyComponents =
      ent->GetComponents(components::k_rigid_body);

    RigidBody& currRigidBody = rigidBodyComponents[0];

    // Transfer the transform to the transform component
    TLOC_UNUSED(currRigidBody);

    TLOC_UNUSED(a_mgr);
  }

  void RigidBodySystem::Pre_OnEvent(const event_type& a_event)
  {
    TLOC_UNUSED(a_event);
  }

  void RigidBodySystem::Post_OnEvent(const event_type& a_event)
  {
    using namespace tloc::core;
    using namespace tloc::core::component_system;

    typedef RigidBody                   rigid_body_type;
    typedef Fixture                     fixture_type;

    event_value_type eventValueType = a_event.GetType();

    switch(eventValueType)
    {
    case entity_events::insert_component:
    case entity_events::remove_component:
      {
        const EntityComponentEvent& entEvent =
          a_event.GetAs<EntityComponentEvent>();
        const Entity* ent = entEvent.GetEntity();

        ComponentMapper<rigid_body_type> rigidBodyComponents =
          ent->GetComponents(components::k_rigid_body);

        rigid_body_type& currRigidBody = rigidBodyComponents[0];

        if (eventValueType == entity_events::insert_component)
        {
          rigid_body_type::rigid_body_def_type box2dRigidBodyDef =
            currRigidBody.GetBox2dRigidBodyDef();

          world_type::world_type& box2dWorld = m_world->GetWorld();
          rigid_body_type::rigid_body_type* box2dRigidBody =
            box2dWorld.CreateBody(&box2dRigidBodyDef);

          currRigidBody.SetBox2dRigidBody(box2dRigidBody);

          ComponentMapper<Fixture> fixtureComponents =
            ent->GetComponents(components::k_fixture);

          typedef ComponentMapper<Fixture>::size_type size_type;
          size_type numFixtures = fixtureComponents.size();

          for (size_type i = 0; i < numFixtures; ++i)
          {
            fixture_type::fixture_def_type box2dFixtureDef =
              fixtureComponents[i].GetBox2dFixtureDef();

            fixture_type::fixture_type* box2dFixture =
              box2dRigidBody->CreateFixture(&box2dFixtureDef);

            fixtureComponents[i].SetBox2dFixture(box2dFixture);
          }
        }
        else
        {
          rigid_body_type::rigid_body_type* box2dRigidBody =
            currRigidBody.GetBox2dRigidBody();

          world_type::world_type& box2dWorld = m_world->GetWorld();
          box2dWorld.DestroyBody(box2dRigidBody);

          currRigidBody.SetBox2dRigidBodyToNull();

          ComponentMapper<Fixture> fixtureComponents =
            ent->GetComponents(components::k_fixture);

          typedef ComponentMapper<Fixture>::size_type size_type;
          size_type numFixtures = fixtureComponents.size();

          for (size_type i = 0; i < numFixtures; ++i)
          {
            fixtureComponents[i].SetBox2dFixtureToNull();
          }
        }

        break;
      }
    }
  }

};};};};