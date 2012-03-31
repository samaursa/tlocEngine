#include "tlocTestCommon.h"

#define private public
#define protected public
#include "tlocGraphics/tlocWindowImplWin.h"
#include "tlocGraphics/tlocWindow.h"

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
      TLOC_ASSERT(a_event.m_type < WindowEvent::events_count, "Unknown event!");
      m_windowEventCount++;
      m_counts[a_event.m_type] = m_counts[a_event.m_type] + 1;
    }

    s32 m_windowEventCount;
    s32 m_counts[WindowEvent::events_count];
  };

  TLOC_DEF_TYPE(sampleObject);

  TEST_CASE("Graphics/Window/General", "")
  {
    typedef Window<>::graphics_mode graphics_mode;

    Window<> win;
    CHECK(win.IsValid() == false);
    CHECK(win.IsCreated() == false);
    win.Create();
    CHECK(win.IsValid() == true);
    CHECK(win.IsCreated() == true);

    sampleObject callbacks;
    CHECK(callbacks.m_windowEventCount == 0);
    {
      Window<> win2;
      CHECK(win2.IsValid() == false);
      CHECK(win2.IsCreated() == false);
      win2.Create(graphics_mode(graphics_mode::Properties(200, 200)),
        "Test", WindowSettings::style_titlebar, WindowSettings("Test"));
      CHECK(win2.IsValid() == true);
      CHECK(win2.IsCreated() == true);

      CHECK(IsWindow(win.m_impl->m_handle) == 1);
      win2.Register(&callbacks);
    }
    CHECK(callbacks.m_windowEventCount == 2); // win2 was destroyed and lost focus,
                                              // 2 events were raised
    CHECK(callbacks.m_counts[WindowEvent::lost_focus] == 1);
    CHECK(callbacks.m_counts[WindowEvent::destroy] == 1);

    Window<> win3;
    CHECK(win3.IsValid() == false);
    CHECK(win3.IsCreated() == false);
    win3.Create(graphics_mode(graphics_mode::Properties(1920, 1080)),
      "Testing", WindowSettings::style_fullscreen, WindowSettings("Testing"));
    CHECK(win3.IsValid() == true);
    CHECK(win3.IsCreated() == true);
  }

  TEST_CASE("Graphics/Window/Callbacks", "")
  {
    typedef Window<>::graphics_mode graphics_mode;
    Window<> win;
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
};