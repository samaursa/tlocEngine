#include "tlocTestCommon.h"

#include <tlocCore/types/tlocBasicTypes.h>
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
    Variadic1i  a(1);
    Variadic2i  b(1, 2);
    Variadic3i  c(1, 2, 3);
    Variadic4i  d(1, 2, 3, 4);
    Variadic5i  e(1, 2, 3, 4, 5);
    Variadic6i  f(1, 2, 3, 4, 5, 6);
    Variadic7i  g(1, 2, 3, 4, 5, 6, 7);
    Variadic8i  h(1, 2, 3, 4, 5, 6, 7, 8);
    Variadic9i  i(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Variadic10i j(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

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

  TEST_CASE("Core/DataStructures/VariadicArray", "Array Construction")
  {
    tl_int array1[]   = {1};
    tl_int array2[]   = {1, 2};
    tl_int array3[]   = {1, 2, 3};
    tl_int array4[]   = {1, 2, 3, 4};
    tl_int array5[]   = {1, 2, 3, 4, 5};
    tl_int array6[]   = {1, 2, 3, 4, 5, 6};
    tl_int array7[]   = {1, 2, 3, 4, 5, 6, 7};
    tl_int array8[]   = {1, 2, 3, 4, 5, 6, 7, 8};
    tl_int array9[]   = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    tl_int array10[]  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    Variadic1i  a(array1);
    Variadic2i  b(array2);
    Variadic3i  c(array3);
    Variadic4i  d(array4);
    Variadic5i  e(array5);
    Variadic6i  f(array6);
    Variadic7i  g(array7);
    Variadic8i  h(array8);
    Variadic9i  i(array9);
    Variadic10i j(array10);

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