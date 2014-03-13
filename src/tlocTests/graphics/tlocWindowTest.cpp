#include "tlocTestCommon.h"
#include "tlocCore/platform/tlocPlatformDefines.h"

#if defined(TLOC_OS_WIN)
# include <tlocGraphics/window/tlocWindowImplWin.h>
#elif defined(TLOC_OS_IPHONE)
# include <tlocGraphics/window/tlocWindowImplIphone.h>
# import <UIKit/UIKit.h>
#endif
#include <tlocGraphics/window/tlocWindow.h>

namespace TestingWindow
{
  using namespace tloc;
  using namespace graphics;
  using namespace graphics::win;

  tl_size g_windowSizeX = 0;
  tl_size g_windowSizeY = 0;

  struct sampleObject
  {
    sampleObject() : m_windowEventCount(0)
    {
      for (u32 i = 0; i < WindowEvent::events_count; ++i)
      {
        m_counts[i] = 0;
      }
    }

    void OnWindowEvent(const WindowEvent& a_event)
    {
      INFO("Unknown event was passed.");
      REQUIRE(a_event.m_type < WindowEvent::events_count);

      m_windowEventCount++;
      m_counts[a_event.m_type] = m_counts[a_event.m_type] + 1;

      CHECK(a_event.GetWidth() == g_windowSizeX);
      CHECK(a_event.GetHeight() == g_windowSizeY);
    }

    s32 m_windowEventCount;
    s32 m_counts[WindowEvent::events_count];
  };

};

TLOC_DEF_TYPE(TestingWindow::sampleObject);

namespace TestingWindow
{

#if defined(TLOC_OS_WIN)

  TEST_CASE("Graphics/Window/General", "")
  {
    typedef Window::graphics_mode graphics_mode;

    Window win;
    CHECK(win.IsValid() == false);
    CHECK(win.IsCreated() == false);
    win.Create();
    CHECK(win.IsValid() == true);
    CHECK(win.IsCreated() == true);

    win.SetMouseVisibility(false);
    CHECK(GetCursor() == TLOC_NULL);

    sampleObject callbacks;
    CHECK(callbacks.m_windowEventCount == 0);
    {
      g_windowSizeX = 200; g_windowSizeY = 200;

      Window win2;
      CHECK(win2.IsValid() == false);
      CHECK(win2.IsCreated() == false);
      win2.Create(graphics_mode
        (graphics_mode::Properties(g_windowSizeX, g_windowSizeY)),
        WindowSettings("Test").ClearStyles().AddStyle<p_window_settings::style::TitleBar>());
      CHECK(win2.IsValid() == true);
      CHECK(win2.IsCreated() == true);
      CHECK(win2.GetWidth() == g_windowSizeX);
      CHECK(win2.GetHeight() == g_windowSizeY);
      CHECK(win2.GetAspectRatio().Get() == Approx(1.0f));

      CHECK(IsWindow(win.GetWindowHandle()) == 1);
      win2.Register(&callbacks);
    }
    CHECK(callbacks.m_windowEventCount == 2); // win2 was destroyed and lost focus,
                                              // 2 events were raised
    CHECK(callbacks.m_counts[WindowEvent::lost_focus] == 1);
    CHECK(callbacks.m_counts[WindowEvent::destroy] == 1);

    { // Bug-fix test - Client is incorrect size with default window styles
      g_windowSizeX = 400; g_windowSizeY = 400;
      Window win2;
      CHECK(win2.IsValid() == false);
      CHECK(win2.IsCreated() == false);
      win2.Create(graphics_mode
        (graphics_mode::Properties(g_windowSizeX, g_windowSizeY)),
        WindowSettings("Test"));
      CHECK(win2.IsValid() == true);
      CHECK(win2.IsCreated() == true);
      CHECK(win2.GetWidth() == g_windowSizeX);
      CHECK(win2.GetHeight() == g_windowSizeY);
      CHECK(win2.GetAspectRatio().Get() == Approx(1.0f));
    }
  }

  TEST_CASE("Graphics/Window/Fullscreen", "")
  {
    typedef Window::graphics_mode graphics_mode;

    g_windowSizeX = 1920; g_windowSizeY = 1080;

    Window win3;
    CHECK(win3.IsValid() == false);
    CHECK(win3.IsCreated() == false);
    win3.Create(graphics_mode
      (graphics_mode::Properties(g_windowSizeX, g_windowSizeY)),
      WindowSettings("Testing").ClearStyles()
      .AddStyle<p_window_settings::style::FullScreen>());
    CHECK(win3.IsValid() == true);
    CHECK(win3.IsCreated() == true);
  }

  TEST_CASE("Graphics/Window/Callbacks", "")
  {
    typedef Window::graphics_mode graphics_mode;
    Window win;
    CHECK(win.IsValid() == false);
    CHECK(win.IsCreated() == false);
    win.Create();
    CHECK(win.IsValid() == true);
    CHECK(win.IsCreated() == true);

    sampleObject callbacks;
    CHECK(callbacks.m_windowEventCount == 0);
    win.Register(&callbacks);

    win.SetSize(100, 100);
    // TODO: Fix these tests
    //CHECK(callbacks.m_windowEventCount == 1);
    //CHECK(callbacks.m_counts[WindowEvent::resized] == 1);
  }

#elif defined(TLOC_OS_IPHONE)

  TEST_CASE("Graphics/Window/General", "")
  {
    typedef Window::graphics_mode graphics_mode;
    {
      Window win1;
      CHECK(win1.IsValid() == false);
      CHECK(win1.IsCreated() == false);
      win1.Create(graphics_mode(graphics_mode::Properties(200, 200)),
                  WindowSettings("Test").
                  AddStyle<p_window_settings::style::TitleBar>());
      CHECK(win1.IsValid() == true);
      CHECK(win1.IsCreated() == true);
      CHECK( (win1.GetWindowHandle().Cast<UIWindow*>() != nullptr) );
    }

    {
      Window win2;
      CHECK(win2.IsValid() == false);
      CHECK(win2.IsCreated() == false);
      win2.Create(graphics_mode(graphics_mode::Properties(300, 300)),
                  WindowSettings("Testing").
                  AddStyle<p_window_settings::style::FullScreen>());
      CHECK(win2.IsValid() == true);
      CHECK(win2.IsCreated() == true);
      CHECK( (win2.GetWindowHandle().Cast<UIWindow*>() != nullptr) );
    }
  }

  TEST_CASE("Graphics/Window/Callbacks", "")
  {
    typedef Window::graphics_mode graphics_mode;
    Window win;
    CHECK(win.IsValid() == false);
    CHECK(win.IsCreated() == false);
    win.Create(graphics_mode(graphics_mode::Properties(200, 200)),
               WindowSettings("Test").
               AddStyle<p_window_settings::style::TitleBar>());
    CHECK(win.IsValid() == true);
    CHECK(win.IsCreated() == true);

    sampleObject callbacks;
    CHECK(callbacks.m_windowEventCount == 0);
    win.Register(&callbacks);

    win.SetSize(100, 100);
    // TODO: Fix these tests
    //CHECK(callbacks.m_windowEventCount == 1);
    //CHECK(callbacks.m_counts[WindowEvent::resized] == 1);
  }

#endif

};