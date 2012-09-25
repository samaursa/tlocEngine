#include "tlocTestCommon.h"

#include <tlocCore/data_structures/tlocVariadic.h>

namespace TestingVariadic
{
  USING_TLOC;
  using namespace core;

  template <tl_int T_Size>
  void CheckVariadic(const Variadic<tl_int, T_Size>& a_variableArgs)
  {
    bool testPassed = true;
    for (tl_uint i = 0; i < a_variableArgs.GetSize(); ++i)
    {
      if (a_variableArgs[i] != (tl_int)(i + 1))
      {
        testPassed = false;
        break;
      }
    }

    CHECK(testPassed);
  }

  TEST_CASE("Core/DataStructures/Variadic", "Construction")
  {
    Variadic<tl_int, 1>  a(1);
    Variadic<tl_int, 2>  b(1, 2);
    Variadic<tl_int, 3>  c(1, 2, 3);
    Variadic<tl_int, 4>  d(1, 2, 3, 4);
    Variadic<tl_int, 5>  e(1, 2, 3, 4, 5);
    Variadic<tl_int, 6>  f(1, 2, 3, 4, 5, 6);
    Variadic<tl_int, 7>  g(1, 2, 3, 4, 5, 6, 7);
    Variadic<tl_int, 8>  h(1, 2, 3, 4, 5, 6, 7, 8);
    Variadic<tl_int, 9>  i(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Variadic<tl_int, 10> j(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    CheckVariadic(a);
    CheckVariadic(b);
    CheckVariadic(c);
    CheckVariadic(d);
    CheckVariadic(e);
    CheckVariadic(f);
    CheckVariadic(g);
    CheckVariadic(h);
    CheckVariadic(i);
    CheckVariadic(j);
  }
};