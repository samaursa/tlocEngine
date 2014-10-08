#include "tlocTestCommon.h"

#include <tlocGraphics/component_system/tlocQuad.h>

namespace TestingQuad
{
  using namespace tloc;
  using namespace tloc::graphics::component_system;

  TEST_CASE("Graphics/component_system/Quad", "")
  {
    using math_t::Rectf32_c;

    Rectf32_c r(Rectf32_c::width(1.0f), Rectf32_c::height(2.0f));
    Quad q(r);
    CHECK(q.GetRectangleRef() == r);
  }
};