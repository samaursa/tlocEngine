#include "tlocTestCommon.h"

#include <tlocCore/tlocArgs.h>

namespace TestingTemplateArgs
{
  using namespace tloc;
  using namespace core;

  struct OneArg
  {
    OneArg(tl_int a)
      : m_a(a)
    { }

    tl_int m_a;
  };

  struct TwoArgs
  {
    TwoArgs(tl_int a, tl_int b)
      : m_a(a), m_b(b)
    { }

    tl_int m_a, m_b;
  };

  struct ThreeArgs
  {
    ThreeArgs(tl_int a, tl_int b, tl_int c)
      : m_a(a), m_b(b), m_c(c)
    { }

    tl_int m_a, m_b, m_c;
  };

  struct FourArgs
  {
    FourArgs(tl_int a, tl_int b, tl_int c, tl_int d)
      : m_a(a), m_b(b), m_c(c), m_d(d)
    { }

    tl_int m_a, m_b, m_c, m_d;
  };

  struct FiveArgs
  {
    FiveArgs(tl_int a, tl_int b, tl_int c, tl_int d, tl_int e)
      : m_a(a), m_b(b), m_c(c), m_d(d), m_e(e)
    { }

    tl_int m_a, m_b, m_c, m_d, m_e;
  };

  struct SixArgs
  {
    SixArgs(tl_int a, tl_int b, tl_int c, tl_int d, tl_int e,
              tl_int f)
      : m_a(a), m_b(b), m_c(c), m_d(d), m_e(e)
      , m_f(f)
    { }

    tl_int m_a, m_b, m_c, m_d, m_e,
           m_f;
  };

  struct SevenArgs
  {
    SevenArgs(tl_int a, tl_int b, tl_int c, tl_int d, tl_int e,
                tl_int f, tl_int g)
      : m_a(a), m_b(b), m_c(c), m_d(d), m_e(e)
      , m_f(f), m_g(g)
    { }

    tl_int m_a, m_b, m_c, m_d, m_e,
           m_f, m_g;
  };

  struct EightArgs
  {
    EightArgs(tl_int a, tl_int b, tl_int c, tl_int d, tl_int e,
                tl_int f, tl_int g, tl_int h)
      : m_a(a), m_b(b), m_c(c), m_d(d), m_e(e)
      , m_f(f), m_g(g), m_h(h)
    { }

    tl_int m_a, m_b, m_c, m_d, m_e,
           m_f, m_g, m_h;
  };

  struct NineArgs
  {
    NineArgs(tl_int a, tl_int b, tl_int c, tl_int d, tl_int e,
               tl_int f, tl_int g, tl_int h, tl_int i)
      : m_a(a), m_b(b), m_c(c), m_d(d), m_e(e)
      , m_f(f), m_g(g), m_h(h), m_i(i)
    { }

    tl_int m_a, m_b, m_c, m_d, m_e,
           m_f, m_g, m_h, m_i;
  };

  struct TenArgs
  {
    TenArgs(tl_int a, tl_int b, tl_int c, tl_int d, tl_int e,
              tl_int f, tl_int g, tl_int h, tl_int i, tl_int j)
      : m_a(a), m_b(b), m_c(c), m_d(d), m_e(e)
      , m_f(f), m_g(g), m_h(h), m_i(i), m_j(j)
    { }

    tl_int m_a, m_b, m_c, m_d, m_e,
           m_f, m_g, m_h, m_i, m_j;
  };

  TEST_CASE("core/types/ArgList", "")
  {
    SECTION("OneArg", "")
    {
      SECTION("New", "")
      {
        OneArg* p = New<OneArg>( MakeArgs(1) );
        CHECK(p->m_a == 1);
        delete p;
      }

      OneArg p = MakeOnStack<OneArg>( MakeArgs(1) );
      CHECK(p.m_a == 1);
    }

    SECTION("TwoArgs", "")
    {
      SECTION("New", "")
      {
        TwoArgs* p = New<TwoArgs>( MakeArgs(1, 2) );
        CHECK(p->m_a == 1); CHECK(p->m_b == 2);
        delete p;
      }

      TwoArgs p = MakeOnStack<TwoArgs>( MakeArgs(1, 2) );
      CHECK(p.m_a == 1); CHECK(p.m_b == 2);
    }

    SECTION("ThreeArgs", "")
    {
      SECTION("New", "")
      {
        ThreeArgs* p = New<ThreeArgs>( MakeArgs(1, 2, 3) );
        CHECK(p->m_a == 1); CHECK(p->m_b == 2); CHECK(p->m_c == 3);
        delete p;
      }

      ThreeArgs p = MakeOnStack<ThreeArgs>( MakeArgs(1, 2, 3) );
      CHECK(p.m_a == 1); CHECK(p.m_b == 2); CHECK(p.m_c == 3);
    }

    SECTION("FourArgs", "")
    {
      SECTION("New", "")
      {
        FourArgs* p = New<FourArgs>( MakeArgs(1, 2, 3, 4) );
        CHECK(p->m_a == 1); CHECK(p->m_b == 2); CHECK(p->m_c == 3);
        CHECK(p->m_d == 4); 
        delete p;
      }

      FourArgs p = MakeOnStack<FourArgs>( MakeArgs(1, 2, 3, 4) );
      CHECK(p.m_a == 1); CHECK(p.m_b == 2); CHECK(p.m_c == 3);
      CHECK(p.m_d == 4); 
    }

    SECTION("FiveArgs", "")
    {
      SECTION("New", "")
      {
        FiveArgs* p = New<FiveArgs>( 
          MakeArgs(1, 2, 3, 4, 5) );

        CHECK(p->m_a == 1); CHECK(p->m_b == 2); CHECK(p->m_c == 3);
        CHECK(p->m_d == 4); CHECK(p->m_e == 5);
        delete p;
      }

      FiveArgs p = MakeOnStack<FiveArgs>( 
        MakeArgs(1, 2, 3, 4, 5) );

      CHECK(p.m_a == 1); CHECK(p.m_b == 2); CHECK(p.m_c == 3);
      CHECK(p.m_d == 4); CHECK(p.m_e == 5);
    }

    SECTION("SixArgs", "")
    {
      SECTION("New", "")
      {
        SixArgs* p = New<SixArgs>( 
          MakeArgs(1, 2, 3, 4, 5, 6) );

        CHECK(p->m_a == 1); CHECK(p->m_b == 2); CHECK(p->m_c == 3);
        CHECK(p->m_d == 4); CHECK(p->m_e == 5); CHECK(p->m_f == 6);
        delete p;
      }

      SixArgs p = MakeOnStack<SixArgs>( 
        MakeArgs(1, 2, 3, 4, 5, 6) );

      CHECK(p.m_a == 1); CHECK(p.m_b == 2); CHECK(p.m_c == 3);
      CHECK(p.m_d == 4); CHECK(p.m_e == 5); CHECK(p.m_f == 6);
    }

    SECTION("SevenArgs", "")
    {
      SECTION("New", "")
      {
        SevenArgs* p = New<SevenArgs>( 
          MakeArgs(1, 2, 3, 4, 5, 6, 7) );

        CHECK(p->m_a == 1); CHECK(p->m_b == 2); CHECK(p->m_c == 3);
        CHECK(p->m_d == 4); CHECK(p->m_e == 5); CHECK(p->m_f == 6);
        CHECK(p->m_g == 7);
        delete p;
      }

      SevenArgs p = MakeOnStack<SevenArgs>( 
        MakeArgs(1, 2, 3, 4, 5, 6, 7) );

      CHECK(p.m_a == 1); CHECK(p.m_b == 2); CHECK(p.m_c == 3);
      CHECK(p.m_d == 4); CHECK(p.m_e == 5); CHECK(p.m_f == 6);
      CHECK(p.m_g == 7);
    }
    
    SECTION("EightArgs", "")
    {
      SECTION("New", "")
      {
        EightArgs* p = New<EightArgs>( 
          MakeArgs(1, 2, 3, 4, 5, 6, 7, 8) );

        CHECK(p->m_a == 1); CHECK(p->m_b == 2); CHECK(p->m_c == 3);
        CHECK(p->m_d == 4); CHECK(p->m_e == 5); CHECK(p->m_f == 6);
        CHECK(p->m_g == 7); CHECK(p->m_h == 8);
        delete p;
      }

      EightArgs p = MakeOnStack<EightArgs>( 
        MakeArgs(1, 2, 3, 4, 5, 6, 7, 8) );

      CHECK(p.m_a == 1); CHECK(p.m_b == 2); CHECK(p.m_c == 3);
      CHECK(p.m_d == 4); CHECK(p.m_e == 5); CHECK(p.m_f == 6);
      CHECK(p.m_g == 7); CHECK(p.m_h == 8);
    }

    SECTION("NineArgs", "")
    {
      SECTION("New", "")
      {
        NineArgs* p = New<NineArgs>( 
          MakeArgs(1, 2, 3, 4, 5, 6, 7, 8, 9) );

        CHECK(p->m_a == 1); CHECK(p->m_b == 2); CHECK(p->m_c == 3);
        CHECK(p->m_d == 4); CHECK(p->m_e == 5); CHECK(p->m_f == 6);
        CHECK(p->m_g == 7); CHECK(p->m_h == 8); CHECK(p->m_i == 9);
        delete p;
      }

      NineArgs p = MakeOnStack<NineArgs>( 
        MakeArgs(1, 2, 3, 4, 5, 6, 7, 8, 9) );

      CHECK(p.m_a == 1); CHECK(p.m_b == 2); CHECK(p.m_c == 3);
      CHECK(p.m_d == 4); CHECK(p.m_e == 5); CHECK(p.m_f == 6);
      CHECK(p.m_g == 7); CHECK(p.m_h == 8); CHECK(p.m_i == 9);
    }

    SECTION("TenArgs", "")
    {
      SECTION("New", "")
      {
        TenArgs* p = New<TenArgs>( 
          MakeArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) );

        CHECK(p->m_a == 1); CHECK(p->m_b == 2); CHECK(p->m_c == 3);
        CHECK(p->m_d == 4); CHECK(p->m_e == 5); CHECK(p->m_f == 6);
        CHECK(p->m_g == 7); CHECK(p->m_h == 8); CHECK(p->m_i == 9);
        CHECK(p->m_j == 10);
        delete p;
      }

      TenArgs p = MakeOnStack<TenArgs>( 
        MakeArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) );

      CHECK(p.m_a == 1); CHECK(p.m_b == 2); CHECK(p.m_c == 3);
      CHECK(p.m_d == 4); CHECK(p.m_e == 5); CHECK(p.m_f == 6);
      CHECK(p.m_g == 7); CHECK(p.m_h == 8); CHECK(p.m_i == 9);
      CHECK(p.m_j == 10);
    }
  }
};