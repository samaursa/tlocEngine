#include "tlocTestCommon.h"

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/window/tlocWindow.h>
#include <tlocGraphics/renderer/tlocRenderer.h>

namespace TestingGLGeneral
{
  using namespace tloc;
  using namespace tloc::graphics;

  TEST_CASE("Graphics/gl/Get", "")
  {
    using namespace graphics::win;
    using gfx_rend::Renderer;

    typedef Window::graphics_mode       g_mode;
    Window win;
    win.Create(g_mode(g_mode::Properties(1, 1)), WindowSettings("Blank"));

    REQUIRE(gl::InitializePlatform() != common_error_types::error_initialize);

    CHECK(gl::Get<gl::p_get::CurrentProgram>() == 0);
    CHECK(gl::Error().Succeeded());
  }
};