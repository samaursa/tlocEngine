#include "tlocTestCommon.h"

#include <tlocGraphics/component_system/tlocMesh.h>

namespace TestingColor
{
  using namespace tloc::graphics::component_system;

  TEST_CASE("Graphics/component_system/Quad", "")
  {
    Quad::rect_type rect(Quad::rect_type::half_width(1),
                         Quad::rect_type::half_height(1));
    Quad q(rect);

    {
      Quad::vert_type const & vert = q.GetVertex<Quad::vert_se>();
      CHECK(vert.GetPosition()[0] == Approx(1.0f));
      CHECK(vert.GetPosition()[1] == Approx(-1.0f));
    }

    {
      Quad::vert_type vert = q.GetVertex<Quad::vert_ne>();
      CHECK(vert.GetPosition()[0] == Approx(1.0f));
      CHECK(vert.GetPosition()[1] == Approx(1.0f));
    }

    {
      Quad::vert_type vert = q.GetVertex<Quad::vert_nw>();
      CHECK(vert.GetPosition()[0] == Approx(-1.0f));
      CHECK(vert.GetPosition()[1] == Approx(1.0f));
    }

    {
      Quad::vert_type vert = q.GetVertex<Quad::vert_sw>();
      CHECK(vert.GetPosition()[0] == Approx(-1.0f));
      CHECK(vert.GetPosition()[1] == Approx(-1.0f));
    }
  }
};