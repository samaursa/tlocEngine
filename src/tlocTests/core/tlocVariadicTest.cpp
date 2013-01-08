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
    Variadic11i k(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
    Variadic12i l(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
    Variadic13i m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13);
    Variadic14i n(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
    Variadic15i o(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    Variadic16i p(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

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
    Variadic11i k(array11);
    Variadic12i l(array12);
    Variadic13i m(array13);
    Variadic14i n(array14);
    Variadic15i o(array15);
    Variadic16i p(array16);

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