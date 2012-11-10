#include "tlocPhysicsManager.h"

#include <tlocMath/vector/tlocVector2.h>
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

  void PhysicsManager::Initialize(const math::Vec2f& a_gravity, 
                                  s32 a_velocityIterations, 
                                  s32 a_positionIterations)
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