#include "tlocTestCommon.h"

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/data_structures/tlocVariadic.h>

namespace TestingVariadic
{
  using namespace tloc;
  using namespace core;
  using namespace core::data_structs;

  template <tl_size T_Size>
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
    Variadic1s  a(1);
    Variadic2s  b(1, 2);
    Variadic3s  c(1, 2, 3);
    Variadic4s  d(1, 2, 3, 4);
    Variadic5s  e(1, 2, 3, 4, 5);
    Variadic6s  f(1, 2, 3, 4, 5, 6);
    Variadic7s  g(1, 2, 3, 4, 5, 6, 7);
    Variadic8s  h(1, 2, 3, 4, 5, 6, 7, 8);
    Variadic9s  i(1, 2, 3, 4, 5, 6, 7, 8, 9);
    Variadic10s j(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    Variadic11s k(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
    Variadic12s l(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    Variadic13s m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13);
    Variadic14s n(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
    Variadic15s o(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    Variadic16s p(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

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
    CheckVariadic(k);
    CheckVariadic(l);
    CheckVariadic(m);
    CheckVariadic(n);
    CheckVariadic(o);
    CheckVariadic(p);
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
    tl_int array11[]  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    tl_int array12[]  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    tl_int array13[]  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    tl_int array14[]  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    tl_int array15[]  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    tl_int array16[]  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    Variadic1s  a(array1);
    Variadic2s  b(array2);
    Variadic3s  c(array3);
    Variadic4s  d(array4);
    Variadic5s  e(array5);
    Variadic6s  f(array6);
    Variadic7s  g(array7);
    Variadic8s  h(array8);
    Variadic9s  i(array9);
    Variadic10s j(array10);
    Variadic11s k(array11);
    Variadic12s l(array12);
    Variadic13s m(array13);
    Variadic14s n(array14);
    Variadic15s o(array15);
    Variadic16s p(array16);

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
    CheckVariadic(k);
    CheckVariadic(l);
    CheckVariadic(m);
    CheckVariadic(n);
    CheckVariadic(o);
    CheckVariadic(p);

  }
};