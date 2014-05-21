#include "tlocTestCommon.h"

#include <tlocCore/dispatch/tlocTemplateDispatchDefaults.h>
#include <tlocCore/dispatch/tlocEvent.h>

// This class is purposefully declared/defined before the dispatchers to 
// ensure that dispatching works when class (pipes) has no prior knowledge
// of dispatcher or its callbacks
namespace ns
{
  using namespace tloc::core_dispatch;
  struct pipes
  {
    Event C1() { return f_event::Continue(); }
    Event C2() { return f_event::Continue(); }
    Event C3() { return f_event::Continue(); }
  };
};

TLOC_DEF_TYPE(ns::pipes);

namespace TestingTemplateDispatch
{
  using namespace tloc;
  using namespace core;
  using namespace dispatch;

  struct bullets
  {
    bullets() : m_c1(0), m_c2(0), m_c3(0) {}

    Event C1() { ++m_c1; return f_event::Continue(); }
    Event C2() { ++m_c2; return f_event::Continue(); }
    Event C3() { ++m_c3; return f_event::Continue(); }

    u32 m_c1, m_c2, m_c3;
  };

  struct particles
  {
    particles() : m_c1(0), m_c2(0), m_c3(0) {}

    Event C1() { ++m_c1; return f_event::Continue(); }
    Event C2() { ++m_c2; return f_event::Continue(); }
    Event C3() { ++m_c3; return f_event::Continue(); }

    u32 m_c1, m_c2, m_c3;
  };

  struct WindowCallbacks
  {
    virtual void C1() = 0;
    virtual void C2() = 0;
    virtual void C3() = 0;
  };

  template <typename T>
  struct WindowCallbackGroupT
    : public dispatch::CallbackGroupTArray<T, WindowCallbacks>::type
  {
    typedef typename dispatch::
      CallbackGroupTArray<T, WindowCallbacks>::type       base_type;
    using base_type::m_observers;

    virtual void C1()
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->C1().IsVeto())
        { break; }
      }
    }

    virtual void C2()
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->C2().IsVeto())
        { break; }
      }
    }

    virtual void C3()
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        if (m_observers[i]->C3().IsVeto())
        { break; }
      }
    }
  };

  struct Window
    : public dispatch::DispatcherBaseArray
             <WindowCallbacks, WindowCallbackGroupT>::type
  {
    void CallC1()
    {
      for (u32 i = 0; i < m_allObservers.size(); ++i)
      {
        m_allObservers[i]->C1();
      }
    }

    void CallC2()
    {
      for (u32 i = 0; i < m_allObservers.size(); ++i)
      {
        m_allObservers[i]->C2();
      }
    }

    void CallC3()
    {
      for (u32 i = 0; i < m_allObservers.size(); ++i)
      {
        m_allObservers[i]->C3();
      }
    }
  };
};

TLOC_DEF_TYPE(TestingTemplateDispatch::bullets);
TLOC_DEF_TYPE(TestingTemplateDispatch::particles);

namespace TestingTemplateDispatch
{
  struct Fixture
  {
    bullets b1, b2, b3, b4, b5, b6, b7;
    particles p1, p2, p3, p4, p5, p6, p7;
    ns::pipes pi;
  };

  TEST_CASE_METHOD(Fixture, "Core/BaseClasses/TemplateDispatch/Register", "")
  {
    using namespace ns;

    Window win;
    win.Register(&b1);
    win.Register(&b2);
    win.Register(&b3);

    CHECK(b1.m_c1 == 0);
    CHECK(b2.m_c2 == 0);
    CHECK(b3.m_c3 == 0);

    CHECK(win.GetNumRegisteredGroups() == 1);
    CHECK(win.GetNumRegisteredTypes<bullets>() == 3);
    CHECK(win.GetNumRegisteredTypes<particles>() == 0);

    win.CallC1();

    CHECK(b1.m_c1 == 1);
    CHECK(b2.m_c2 == 0);
    CHECK(b3.m_c3 == 0);

    win.Register(&p1);
    win.Register(&p2);
    win.Register(&p3);

    CHECK(win.GetNumRegisteredGroups() == 2);
    CHECK(win.GetNumRegisteredTypes<bullets>() == 3);
    CHECK(win.GetNumRegisteredTypes<particles>() == 3);

    win.CallC2();

    CHECK(b1.m_c1 == 1);
    CHECK(b2.m_c2 == 1);
    CHECK(b3.m_c3 == 0);

    CHECK(p1.m_c1 == 0);
    CHECK(p1.m_c2 == 1);
    CHECK(p1.m_c3 == 0);

    win.Register(&pi);

    CHECK(win.GetNumRegisteredGroups() == 3);
    CHECK(win.GetNumRegisteredTypes<pipes>() == 1);
  }

  TEST_CASE_METHOD(Fixture, "Core/BaseClasses/TemplateDispatch/UnRegister", "")
  {
    Window win;
    win.Register(&b1); win.Register(&b2); win.Register(&b3);
    win.Register(&p1); win.Register(&p2); win.Register(&p3);

    CHECK(win.GetNumRegisteredGroups() == 2);
    CHECK(win.GetNumRegisteredTypes<bullets>() == 3);
    CHECK(win.GetNumRegisteredTypes<particles>() == 3);

    win.CallC1(); win.CallC2(); win.CallC3();
    CHECK(b1.m_c1 == 1); CHECK(b1.m_c2 == 1); CHECK(b1.m_c3 == 1);
    CHECK(b2.m_c1 == 1); CHECK(b2.m_c2 == 1); CHECK(b2.m_c3 == 1);
    CHECK(b3.m_c1 == 1); CHECK(b3.m_c2 == 1); CHECK(b3.m_c3 == 1);

    CHECK(p1.m_c1 == 1); CHECK(p1.m_c2 == 1); CHECK(p1.m_c3 == 1);
    CHECK(p2.m_c1 == 1); CHECK(p2.m_c2 == 1); CHECK(p2.m_c3 == 1);
    CHECK(p3.m_c1 == 1); CHECK(p3.m_c2 == 1); CHECK(p3.m_c3 == 1);

    win.UnRegister(&p1); win.UnRegister(&p2); win.UnRegister(&p3);

    CHECK(win.GetNumRegisteredGroups() == 2);
    CHECK(win.GetNumRegisteredTypes<bullets>() == 3);
    CHECK(win.GetNumRegisteredTypes<particles>() == 0);

    win.CallC1(); win.CallC2(); win.CallC3();
    CHECK(b1.m_c1 == 2); CHECK(b1.m_c2 == 2); CHECK(b1.m_c3 == 2);
    CHECK(b2.m_c1 == 2); CHECK(b2.m_c2 == 2); CHECK(b2.m_c3 == 2);
    CHECK(b3.m_c1 == 2); CHECK(b3.m_c2 == 2); CHECK(b3.m_c3 == 2);

    CHECK(p1.m_c1 == 1); CHECK(p1.m_c2 == 1); CHECK(p1.m_c3 == 1);
    CHECK(p2.m_c1 == 1); CHECK(p2.m_c2 == 1); CHECK(p2.m_c3 == 1);
    CHECK(p3.m_c1 == 1); CHECK(p3.m_c2 == 1); CHECK(p3.m_c3 == 1);
  }
};
