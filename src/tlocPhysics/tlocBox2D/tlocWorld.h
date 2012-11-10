#ifndef _TLOC_PHYSICS_BOX2D_WORLD_
#define _TLOC_PHYSICS_BOX2D_WORLD_

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <Box2D/Dynamics/b2World.h>

namespace tloc { namespace math {

  template <typename T>
  class Vector2;
  typedef Vector2<tl_float> Vec2f;

};};

namespace tloc { namespace physics { namespace box2d {

  class World : public core::NonCopyable
  {
  public:
    friend class PhysicsManager;

  public:
    typedef World     this_type;
    typedef b2World   world_type;

  protected:
    World(const math::Vec2f& a_gravity);
    
  public:
    TLOC_DECL_AND_DEF_GETTERS_DIRECT(world_type, GetWorld, m_world);

  private:
    world_type m_world;
  };

};};};

#endif