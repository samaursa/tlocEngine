#include "tlocPhysicsManager.h"

#include <tlocMath/vector/tlocVector2.inl>

#include <tlocPhysics/box2d/tlocWorld.h>

namespace tloc { namespace physics { namespace box2d {

  enum flags
  {
    // CHANGE FLAG TYPE
    initialized,
    count
  };

  PhysicsManager::PhysicsManager()
    : m_flags(count)
    , m_world(NULL)
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

    m_flags.Mark(initialized);
    return ErrorSuccess();
  }

  PhysicsManager::error_type PhysicsManager::Shutdown()
  {
    TLOC_ASSERT(m_flags[initialized],
                "PhysicsManager has not been initialized!");

    delete m_world;
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