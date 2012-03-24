#include "tlocTestCommon.h"

#define private public
#define protected public
#include "tlocGraphics/tlocWindowImplWin.h"
#include "tlocGraphics/tlocWindow.h"

namespace TestingWindow
{
  USING_TLOC;
  using namespace graphics;

  TEST_CASE("Graphics/Window/General", "")
  {
    typedef Window<>::graphics_mode graphics_mode;

    Window<> win;
    CHECK(win.IsValid() == false);
    CHECK(win.IsCreated() == false);
    win.Create();
    CHECK(win.IsValid() == true);
    CHECK(win.IsCreated() == true);

    Window<> win2;
    CHECK(win2.IsValid() == false);
    CHECK(win2.IsCreated() == false);
    win2.Create(graphics_mode(graphics_mode::Properties(200, 200)),
      "Test", WindowSettings::style_titlebar, WindowSettings("Test"));
    CHECK(win2.IsValid() == true);
    CHECK(win2.IsCreated() == true);

    CHECK(IsWindow(win.m_impl->m_handle) == 1);

    Window<> win3;
    CHECK(win3.IsValid() == false);
    CHECK(win3.IsCreated() == false);
    win3.Create(graphics_mode(graphics_mode::Properties(1920, 1080)),
      "Testing", WindowSettings::style_fullscreen, WindowSettings("Testing"));
    CHECK(win3.IsValid() == true);
    CHECK(win3.IsCreated() == true);
  }
};