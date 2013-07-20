#include "tlocTestCommon.h"

#include <tlocMath/types/tlocCuboid.h>

#include <tlocCore/data_structures/tlocVariadic.h>
#include <tlocCore/data_structures/tlocVariadic.inl.h>

namespace TestingCuboid
{
  using namespace tloc;
  using namespace tloc::math::types;

  TEST_CASE("Graphics/types/Cuboid/Size", "")
  {
    CHECK(sizeof(Cuboidf32) == sizeof(Cuboidf32::point_type));
    CHECK(sizeof(Cuboidf64) == sizeof(Cuboidf64::point_type));
  }

  TEST_CASE("Graphics/types/Rectangle", "")
  {
    Cuboidf c(Cuboidf::left(1), Cuboidf::right(-1),
              Cuboidf::top(1), Cuboidf::bottom(-1),
              Cuboidf::front(1), Cuboidf::back(-1));

  }
};