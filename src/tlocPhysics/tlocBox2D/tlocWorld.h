#ifndef _TLOC_PHYSICS_BOX2D_WORLD_
#define _TLOC_PHYSICS_BOX2D_WORLD_

#include <Box2D/Dynamics/b2World.h>

namespace tloc { namespace physics { namespace box2d {

  class World
  {
  public:
    typedef World     this_type;
    typedef b2World   world_type;
    
    World(const world_type& a_world);

    void SetWorld(world_type& a_world);
    world_type& GetWorld();

  private:
    world_type m_world;
  };

};};};

#endif