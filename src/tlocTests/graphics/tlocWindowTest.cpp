#include "tlocTestCommon.h"
#include "tlocCore/platform/tlocPlatformDefines.h"

#if defined(TLOC_OS_WIN)
# include <tlocGraphics/window/tlocWindowImplWin.h>
#elif defined(TLOC_OS_IPHONE)
# include <tlocGraphics/window/tlocWindowImplIphone.h>
#endif
#include <tlocGraphics/window/tlocWindow.h>

namespace TestingWindow
{
  USING_TLOC;
  using namespace graphics;

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
    typedef Window_T<>::graphics_mode graphics_mode;

    Window_T<> win;
    CHECK(win.IsValid() == false);
    CHECK(win.IsCreated() == false);
    win.Create();
    CHECK(win.IsValid() == true);
    CHECK(win.IsCreated() == true);

    sampleObject callbacks;
    CHECK(callbacks.m_windowEventCount == 0);
    {
      Window_T<> win2;
      CHECK(win2.IsValid() == false);
      CHECK(win2.IsCreated() == false);
      win2.Create(graphics_mode(graphics_mode::Properties(200, 200)),
        WindowSettings("Test"), WindowSettings::style_titlebar);
      CHECK(win2.IsValid() == true);
      CHECK(win2.IsCreated() == true);

      CHECK(IsWindow(win.GetWindowHandle()) == 1);
      win2.Register(&callbacks);
    }
    CHECK(callbacks.m_windowEventCount == 2); // win2 was destroyed and lost focus,
                                              // 2 events were raised
    CHECK(callbacks.m_counts[WindowEvent::lost_focus] == 1);
    CHECK(callbacks.m_counts[WindowEvent::destroy] == 1);
  }

  TEST_CASE("./Graphics/Window/Fullscreen", "")
  {
    typedef Window_T<>::graphics_mode graphics_mode;

    Window_T<> win3;
    CHECK(win3.IsValid() == false);
    CHECK(win3.IsCreated() == false);
    win3.Create(graphics_mode(graphics_mode::Properties(1920, 1080)),
      WindowSettings("Testing"), WindowSettings::style_fullscreen);
    CHECK(win3.IsValid() == true);
    CHECK(win3.IsCreated() == true);
  }

  TEST_CASE("Graphics/Window/Callbacks", "")
  {
    typedef Window_T<>::graphics_mode graphics_mode;
    Window_T<> win;
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
    typedef Window_T<>::graphics_mode graphics_mode;
    {
      Window_T<> win1;
      CHECK(win1.IsValid() == false);
      CHECK(win1.IsCreated() == false);
      win1.Create(graphics_mode(graphics_mode::Properties(200, 200)),
                  WindowSettings("Test"), WindowSettings::style_titlebar);
      CHECK(win1.IsValid() == true);
      CHECK(win1.IsCreated() == true);
      CHECK(win1.GetWindowHandle() != NULL);
    }

    {
      Window_T<> win2;
      CHECK(win2.IsValid() == false);
      CHECK(win2.IsCreated() == false);
      win2.Create(graphics_mode(graphics_mode::Properties(300, 300)),
                  WindowSettings("Testing"), WindowSettings::style_fullscreen);
      CHECK(win2.IsValid() == true);
      CHECK(win2.IsCreated() == true);
      CHECK(win2.GetWindowHandle() != NULL);
    }
  }

  TEST_CASE("Graphics/Window/Callbacks", "")
  {
    typedef Window_T<>::graphics_mode graphics_mode;
    Window_T<> win;
    CHECK(win.IsValid() == false);
    CHECK(win.IsCreated() == false);
    win.Create(graphics_mode(graphics_mode::Properties(200, 200)),
                WindowSettings("Test"), WindowSettings::style_titlebar);
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