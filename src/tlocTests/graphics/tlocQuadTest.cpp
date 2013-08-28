#include "tlocTestCommon.h"

#include <tlocGraphics/component_system/tlocQuad.h>

namespace TestingQuad
{
  using namespace tloc;
  using namespace tloc::graphics::component_system;

  TEST_CASE("Graphics/component_system/Quad", "")
  {
    using math::types::Rectf32;

    Rectf32 r(Rectf32::width(1.0f), Rectf32::height(2.0f));
    Quad q(r);
    CHECK(q.GetRectangleRef() == r);
  }
};