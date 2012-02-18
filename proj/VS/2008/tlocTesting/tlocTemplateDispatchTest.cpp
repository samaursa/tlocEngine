#include "tlocTestCommon.h"

#include "tlocCore/tlocTemplateDispatchDefaults.h"

namespace ns
{
  struct pipes
  {
    void C1() {}
    void C2() {}
    void C3() {}
  };

  TLOC_DEF_TYPE(pipes);
};

namespace TestingTemplateDispatch
{
  USING_TLOC;
  using namespace core;

  struct bullets
  {
    bullets() : m_c1(0), m_c2(0), m_c3(0) {}

    void C1() { ++m_c1; }
    void C2() { ++m_c2; }
    void C3() { ++m_c3; }

    u32 m_c1, m_c2, m_c3;
  };

  TLOC_DEF_TYPE(bullets);

  struct particles
  {
    particles() : m_c1(0), m_c2(0), m_c3(0) {}

    void C1() { ++m_c1; }
    void C2() { ++m_c2; }
    void C3() { ++m_c3; }

    u32 m_c1, m_c2, m_c3;
  };

  TLOC_DEF_TYPE(particles);

  struct WindowCallbacks
  {
    virtual void C1() = 0;
    virtual void C2() = 0;
    virtual void C3() = 0;
  };

  template <typename T>
  struct WindowCallbackGroupT : public CallbackGroupTArray<T, WindowCallbacks>::type
  {
    virtual void C1()
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        m_observers[i]->C1();
      }
    }

    virtual void C2()
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        m_observers[i]->C2();
      }
    }

    virtual void C3()
    {
      for (u32 i = 0; i < m_observers.size(); ++i)
      {
        m_observers[i]->C3();
      }
    }
  };

  struct Window : public DispatcherBaseArray<WindowCallbacks,
                                             WindowCallbackGroupT>::type
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
