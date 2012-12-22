#include "tlocTestCommon.h"

#include <tlocGraphics/component_system/tlocQuad.h>

namespace TestingColor
{
  using namespace tloc::graphics::component_system;

  TEST_CASE("Graphics/component_system/Quad", "")
  {
    Quad q(Quad::size(2.0f));
    CHECK(q.GetSize() == Approx(2.0f));

    q.SetSize(Quad::size(1.0f));
    CHECK(q.GetSize() == Approx(1.0f));
  }
};