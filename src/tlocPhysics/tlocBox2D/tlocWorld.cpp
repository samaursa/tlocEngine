#include "tlocWorld.h"

namespace tloc { namespace physics { namespace box2d {

  World::World(const world_type& a_world) 
    : m_world(a_world)
  {
  }

  void World::SetWorld(world_type& a_world)
  {
    m_world = a_world;
  }

  World::world_type& World::GetWorld()
  {
    return m_world;
  }

};};};