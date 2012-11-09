#ifndef _TLOC_PHYSICS_BOX2D_WORLD_
#define _TLOC_PHYSICS_BOX2D_WORLD_

#include <tlocCore/tlocBase.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>

#include <tlocMath/vector/tlocVector2.h>

#include <Box2D/Dynamics/b2World.h>

namespace tloc { namespace physics { namespace box2d {

  class World : public core::NonCopyable
  {
  public:
    typedef World     this_type;
    typedef b2World   world_type;

  protected:
    World(const math::Vec2f& a_gravity);
    
  public:
    world_type& GetWorld();
    const world_type& GetWorld() const;

  private:
    world_type m_world;
  };

};};};

#endif