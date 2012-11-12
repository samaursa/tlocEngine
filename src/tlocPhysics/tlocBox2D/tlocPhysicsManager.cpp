#include "tlocPhysicsManager.h"

#include <tlocMath/vector/tlocVector2.inl>

#include <tlocPhysics/tlocBox2D/tlocWorld.h>

namespace tloc { namespace physics { namespace box2d {

  PhysicsManager::PhysicsManager()
    : m_world(NULL)
  {
  }

  PhysicsManager::~PhysicsManager()
  {
    delete m_world;
  }

  void PhysicsManager::Initialize(gravity a_gravity, 
                                  velocity_iterations a_velocityIterations, 
                                  position_iterations a_positionIterations)
  {
    TLOC_ASSERT(m_world, "PhysicsManager has already been initialized!");

    m_world = new World(a_gravity);
    m_velocityIterations = a_velocityIterations;
    m_positionIterations = a_positionIterations;
  }

  void PhysicsManager::Update(tl_float a_timeStep)
  {
    m_world->GetWorld().Step(a_timeStep, 
                             m_velocityIterations, m_positionIterations);
  }

};};};

#include <tlocCore/types/tlocStrongType.inl>
#include <tlocCore/types/tlocStrongTypeExplicitMacros.h>
TLOC_INSTANTIATE_STRONG_TYPE(tloc::physics::box2d::PhysicsManager::vec_type);