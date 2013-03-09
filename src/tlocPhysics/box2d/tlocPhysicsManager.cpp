#include "tlocPhysicsManager.h"

#include <tlocMath/types/tlocVector2.inl>

#include <tlocPhysics/box2d/tlocWorld.h>

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Dynamics/b2Fixture.h>

namespace tloc { namespace physics { namespace box2d {

  //////////////////////////////////////////////////////////////////////////
  // Free functions and definitions

  namespace {

    typedef ContactEvent::entity_type   entity_type;
    typedef b2Fixture                   fixture_type;

    typedef f32                         float_internal_type;

    enum flags
    {
      initialized,
      count
    };

    entity_type*
      DoGetParentEntity(fixture_type* a_fixture)
    {
      return static_cast<entity_type*>
        (a_fixture->GetUserData());
    }

    //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    // @note: Decided against passing the rigid body shape components (that is
    // the fixture) in event due to the processing involved in finding the
    // shape components.
    ContactEvent
      DoCreateContactEvent(fixture_type* a_fixtureA, fixture_type* a_fixtureB)
    {
      entity_type* entityA;
      entity_type* entityB;

      entityA = DoGetParentEntity(a_fixtureA);
      entityB = DoGetParentEntity(a_fixtureB);

      return ContactEvent(entityA, entityB);
    }

  };

  namespace priv {

    //////////////////////////////////////////////////////////////////////////
    // ContactListener

    // Note: This is defined in a priv namespace so that we can keep a pointer to
    // an instance in the PhysicsManager itself. If defined in an anonymous
    // namespace, the compiler will not be able to find the constructor.
    class ContactListener : public b2ContactListener
    {
    public:
      typedef PhysicsManager                      physics_manager;
      typedef ContactEvent                        contact_event_type;

    public:
      ContactListener(physics_manager* a_physicsManager)
        : m_physicsManager(a_physicsManager) {}

    public:
      void
        BeginContact(b2Contact* contact)
      {
        contact_event_type event =
          DoCreateContactEvent(contact->GetFixtureA(), contact->GetFixtureB());

        m_physicsManager->SendOnContactBegin(event);
      }

      void
        EndContact(b2Contact* contact)
      {
        contact_event_type event =
          DoCreateContactEvent(contact->GetFixtureA(), contact->GetFixtureB());

        m_physicsManager->SendOnContactEnd(event);
      }

    private:
      physics_manager* m_physicsManager;
    };

  };

  //////////////////////////////////////////////////////////////////////////
  // PhysicsManager

  PhysicsManager::
    PhysicsManager()
    : m_flags(count)
    , m_world(NULL)
    , m_contactListener(NULL)
  {
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  PhysicsManager::error_type PhysicsManager::
    Initialize(gravity a_gravity,
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

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  PhysicsManager::error_type PhysicsManager::
    Shutdown()
  {
    TLOC_ASSERT(m_flags[initialized],
                "PhysicsManager has not been initialized!");

    delete m_world;
    delete m_contactListener;

    return ErrorSuccess();
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void PhysicsManager::
    Update(tl_float a_timeStep)
  {
    TLOC_ASSERT(m_flags[initialized], "PhysicsManager is not initialized!");
    TLOC_ASSERT_NOT_NULL(m_world);

    m_world->GetWorld().Step(static_cast<float_internal_type>(a_timeStep),
                             m_velocityIterations, m_positionIterations);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  PhysicsManager::world_type& PhysicsManager::
    GetWorld()
  {
    TLOC_ASSERT(m_flags[initialized], "PhysicsManager is not initialized!");
    TLOC_ASSERT_NOT_NULL(m_world);
    return *m_world;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const PhysicsManager::world_type& PhysicsManager::
    GetWorld() const
  {
    TLOC_ASSERT(m_flags[initialized], "PhysicsManager is not initialized!");
    TLOC_ASSERT_NOT_NULL(m_world);
    return *m_world;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void PhysicsManager::
    SendOnContactBegin(const contact_event_type& a_event)
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->OnContactBegin(a_event) == true)
      {
        return;
      }
    }
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void PhysicsManager::
    SendOnContactEnd(const contact_event_type& a_event)
  {
    for (size_type i = 0; i < m_allObservers.size(); ++i)
    {
      if (m_allObservers[i]->OnContactEnd(a_event) == true)
      {
        return;
      }

    }
  }

};};};

//////////////////////////////////////////////////////////////////////////
// Explicit instantiation

#include <tlocCore/types/tlocStrongType.inl>
#include <tlocCore/types/tlocStrongTypeExplicitMacros.h>
TLOC_INSTANTIATE_STRONG_TYPE(tloc::physics::box2d::PhysicsManager::vec_type);