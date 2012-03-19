#include "tlocTestCommon.h"

#include "tlocGraphics/tlocWindow.h"

namespace TestingWindow
{
  USING_TLOC;
  using namespace graphics;

  TEST_CASE("Graphics/Window/General", "")
  {
    typedef Window<>::graphics_mode graphics_mode;

    Window<> win;
    win.Create();

    Window<> win2;
    win2.Create(graphics_mode(graphics_mode::Properties(200, 200)),
      "Test", WindowSettings::style_titlebar, WindowSettings("Test"));
  }
};