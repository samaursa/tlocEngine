#include "tlocPhysicsManager.h"

#include <tlocMath/vector/tlocVector2.inl>

#include <tlocPhysics/box2d/tlocWorld.h>
#include <tlocPhysics/component_system/tlocRigidBodyShapeComponent.h>

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Dynamics/b2Fixture.h>

namespace tloc { namespace physics { namespace box2d {

  //------------------------------------------------------------------------
  // Free functions

  ContactEvent::rigid_body_shape_type*
    GetParentRigidBodyShape(b2Fixture* a_fixture)
  {
    typedef ContactEvent::rigid_body_shape_type rigid_body_shape_component_type;

    return static_cast<rigid_body_shape_component_type*>
      (a_fixture->GetUserData());
  }

  ContactEvent CreateContactEvent(b2Fixture* a_fixtureA, b2Fixture* a_fixtureB)
  {
    typedef ContactEvent::rigid_body_shape_type rigid_body_shape_component_type;

    rigid_body_shape_component_type* rbShapeA;
    rigid_body_shape_component_type* rbShapeB;

    rbShapeA = GetParentRigidBodyShape(a_fixtureA);
    rbShapeB = GetParentRigidBodyShape(a_fixtureB);

    return ContactEvent(rbShapeA, rbShapeB);
  }

  //------------------------------------------------------------------------
  // ContactListener

  class ContactListener : public b2ContactListener
  {
  public:
    typedef PhysicsManager                      physics_manager_type;
    typedef ContactEvent                        contact_event_type;

  public:
    ContactListener(physics_manager_type* a_physicsManager)
      : m_physicsManager(a_physicsManager) {}

  public:
    void BeginContact(b2Contact* contact)
    {
      contact_event_type event =
        CreateContactEvent(contact->GetFixtureA(), contact->GetFixtureB());

      m_physicsManager->SendOnContactBegin(event);
    }

    void EndContact(b2Contact* contact)
    {
      contact_event_type event =
        CreateContactEvent(contact->GetFixtureA(), contact->GetFixtureB());

      m_physicsManager->SendOnContactEnd(event);
    }

  private:
    physics_manager_type* m_physicsManager;
  };

  //------------------------------------------------------------------------
  // PhysicsManager

  enum flags
  {
    // CHANGE FLAG TYPE
    initialized,
    count
  };

  PhysicsManager::PhysicsManager()
    : m_flags(count)
    , m_world(NULL)
    , m_contactListener(NULL)
  {
  }

  PhysicsManager::error_type
    PhysicsManager::Initialize(gravity a_gravity,
                               velocity_iterations a_velocityIterations,
                               position_iterations a_positionIterations)
  {
    TLOC_ASSERT(!m_flags[initialized],
                "PhysicsManager has already been initialized!");

    m_world = new World(a_gravity);
    m_velocityIterations = a_velocityIterations;
    m_positionIterations = a_positionIterations;

    m_contactListener = new contact_listener_type(this);
    m_world->GetWorld().SetContactListener(m_contactListener);

    m_flags.Mark(initialized);
    return ErrorSuccess();
  }

  PhysicsManager::error_type PhysicsManager::Shutdown()
  {
    TLOC_ASSERT(m_flags[initialized],
                "PhysicsManager has not been initialized!");

    delete m_world;
    delete m_contactListener;

    return ErrorSuccess();
  }

  void PhysicsManager::Update(tl_float a_timeStep)
  {
    TLOC_ASSERT(m_flags[initialized], "PhysicsManager is not initialized!");
    TLOC_ASSERT_NOT_NULL(m_world);

    m_world->GetWorld().Step(a_timeStep,
                             m_velocityIterations, m_positionIterations);
  }

  PhysicsManager::world_type& PhysicsManager::GetWorld()
  {
    TLOC_ASSERT(m_flags[initialized], "PhysicsManager is not initialized!");
    TLOC_ASSERT_NOT_NULL(m_world);
    return *m_world;
  }

  const PhysicsManager::world_type& PhysicsManager::GetWorld() const
  {
    TLOC_ASSERT(m_flags[initialized], "PhysicsManager is not initialized!");
    TLOC_ASSERT_NOT_NULL(m_world);
    return *m_world;
  }

  void PhysicsManager::SendOnContactBegin(const contact_event_type& a_event)
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      m_allObservers[i]->OnContactBegin(a_event);
    }
  }

  void PhysicsManager::SendOnContactEnd(const contact_event_type& a_event)
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      m_allObservers[i]->OnContactEnd(a_event);
    }
  }

};};};

#include <tlocCore/types/tlocStrongType.inl>
#include <tlocCore/types/tlocStrongTypeExplicitMacros.h>
TLOC_INSTANTIATE_STRONG_TYPE(tloc::physics::box2d::PhysicsManager::vec_type);