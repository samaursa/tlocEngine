#ifndef _TLOC_PHYSICS_BOX2D_WORLD_
#define _TLOC_PHYSICS_BOX2D_WORLD_

#include <tlocPhysics/tlocPhysicsBase.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <tlocMath/types/tlocVector2.h>

#include <Box2D/Dynamics/b2World.h>

namespace tloc { namespace physics { namespace box2d {

  ///-------------------------------------------------------------------------
  /// @brief  A physics world used to contain and simulate multiple bodies and
  /// constraints. An instance can only be constructed by the PhysicsManager.
  ///-------------------------------------------------------------------------
  class World
    : public core_bclass::NonCopyable_I
  {
  public:
    friend class PhysicsManager;

  public:
    typedef World     this_type;
    typedef b2World   world_type;

    typedef math::types::Vec2f vec_type;

    typedef core::types::StrongType_T<vec_type, 0> gravity;

  protected:
    World(gravity a_gravity);

  public:
    TLOC_DECL_AND_DEF_GETTERS_DIRECT(world_type, GetWorld, m_world);

  private:
    world_type m_world;
  };

};};};

#endif