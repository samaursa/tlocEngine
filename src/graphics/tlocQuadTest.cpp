#include "tlocTestCommon.h"

#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>

#include <tlocGraphics/component_system/tlocQuad.h>

namespace TestingQuad
{
  using namespace tloc;
  using namespace tloc::graphics::component_system;

  TEST_CASE("Graphics/component_system/Quad", "")
  {
    using namespace graphics::win;

    typedef Window::graphics_mode       graphics_mode;

    Window win;
    win.Create(graphics_mode(graphics_mode::Properties(1, 1)),
               WindowSettings("Atom & Eve"));

    // Initialize glew
    REQUIRE(gfx_gl::InitializePlatform() == ErrorSuccess);

    SECTION("Quad construction", "")
    {
      using math_t::Rectf32_c;

      Rectf32_c r(Rectf32_c::width(1.0f), Rectf32_c::height(2.0f));
      Quad q(r);
      CHECK(q.GetRectangleRef() == r);
    }
  }
};