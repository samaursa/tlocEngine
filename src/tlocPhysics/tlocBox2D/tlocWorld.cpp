#include "tlocWorld.h"

#include <tlocMath/vector/tlocVector2.inl>

namespace tloc { namespace physics { namespace box2d {

  World::World(const math::Vec2f& a_gravity) 
    : m_world(b2Vec2(a_gravity[0], a_gravity[1]))
  {
  }

  World::world_type& World::GetWorld()
  {
    return m_world;
  }

  const World::world_type& World::GetWorld() const
  {
    return m_world;
  }

};};};