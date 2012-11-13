#include "tlocTestCommon.h"

#include <tlocCore/error/tlocError.h>

#include <tlocMath/vector/tlocVector2.h>
#include <tlocMath/vector/tlocVector2.inl>

#include <tlocPhysics/tlocBox2D/tlocPhysicsManager.h>

namespace TestingPhysicsManager
{
  using namespace tloc;
  using namespace tloc::physics;

  TEST_CASE("Physics/Box2D/PhysicsManager", "")
  {
    using namespace tloc::core;
    using namespace math;

    typedef box2d::PhysicsManager pm_type;
    pm_type physicsMgr;

    typedef core::error::Error error_type;
    error_type result;

    result = physicsMgr.Initialize(pm_type::gravity(math::Vec2f(0.0f,-10.0f)), 
                                   pm_type::velocity_iterations(6),
                                   pm_type::position_iterations(2));

    CHECK(result == ErrorSuccess());
    CHECK(&physicsMgr.GetWorld() != NULL);

    physicsMgr.Update(1.0f/60.0f);
  }
};
