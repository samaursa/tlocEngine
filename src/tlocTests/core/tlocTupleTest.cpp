#include "tlocTestCommon.h"

#include <tlocCore/tlocAlgorithms.h>
#include "tlocCore/tlocAlgorithms.inl"

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/data_structures/tlocTuple.inl>

#include <tlocCore/data_structures/tlocVariadic.h>

namespace TestingTuple
{
  USING_TLOC;
  using namespace core::data_structs;

#define CHECK_TUP(tup,x,y,z,w)   CHECK(tup[0] == x); \
  CHECK(tup[1] == y); \
  CHECK(tup[2] == z); \
  CHECK(tup[3] == w);

  TEST_CASE("Core/DataStructures/Tuple", "Testing the Tuple<T, size> class")
  {
    Tuple<tl_int, 4> p(0);
    CHECK_TUP(p, 0, 0, 0, 0);

    p[0] = 0; p[1] = 1; p[2] = 2; p[3] = 3;
    CHECK_TUP(p, 0, 1, 2, 3);

    CHECK(p.Get(0) == 0);
    CHECK(p.Get(1) == 1);
    CHECK(p.Get(2) == 2);
    CHECK(p.Get(3) == 3);

    // Direct access
    CHECK( *(p.data() + 0) == 0);
    CHECK( *(p.data() + 1) == 1);
    CHECK( *(p.data() + 2) == 2);
    CHECK( *(p.data() + 3) == 3);

    p.Set(5);
    CHECK_TUP(p, 5, 5, 5, 5);

    // Check Size
    CHECK(p.GetSize() == 4);

    Tuple<tl_int, 4> q(8);
    p.Swap(q);

    CHECK_TUP(p, 8, 8, 8, 8);
    CHECK_TUP(q, 5, 5, 5, 5);

    tl_int numberSet[4] = {1, 2, 3, 4};
    p.Set(numberSet);
    CHECK_TUP(p, 1, 2, 3, 4);

    // Check Size
    CHECK(q.GetSize() == 4);

    Tuple<tl_int, 4> r(numberSet);
    CHECK_TUP(r, 1, 2, 3, 4);

    r.Set(0);
    CHECK_TUP(r, 0, 0, 0, 0);
    r = numberSet;
    CHECK_TUP(r, 1, 2, 3, 4);

    // Check Size
    CHECK(r.GetSize() == 4);

    Tuple<tl_int, 4> s(r);
    CHECK_TUP(s, 1, 2, 3, 4);

    s.Set(0);
    CHECK_TUP(s, 0, 0, 0, 0);
    s = r;
    CHECK_TUP(s, 1, 2, 3, 4);

    // Check Size
    CHECK (q.GetSize() == 4);
  }

  TEST_CASE("Core/DataStructures/Tuple/VariadicCtor",
    "Test the Tuple ctor with varadic")
  {
    Tuple<tl_int, 4> p(Variadic4i(1, 2, 3, 4));

    CHECK(p.GetSize() == 4);
    CHECK(p[0] == 1);
    CHECK(p[1] == 2);
    CHECK(p[2] == 3);
    CHECK(p[3] == 4);
  }

  TEST_CASE("Core/DataStructures/Tuple/Operators",
    "Testing the operator functions")
  {
    Tuple<s32, 4> p(0), q(1);
    CHECK( (p == q) == false);
    CHECK( (p != q) == true);

    p = q;
    CHECK( (p == q) == true);
    CHECK( (p != q) == false);
  }

  TEST_CASE("Core/DataStructures/Tuple/ConvertFrom",
    "Conversion from different sized tuples")
  {
    Tuple<tl_int, 3> a3(0);
    Tuple<tl_int, 4> a4_same(10), a4_one(20), a4_zero(30);
    Tuple<tl_int, 5> a5(2);

    a4_same.ConvertFrom(a3, p_tuple::overflow_same() );
    CHECK_TUP(a4_same, 0, 0, 0, 10);
    a4_one.ConvertFrom(a3, p_tuple::overflow_one() );
    CHECK_TUP(a4_one, 0, 0, 0, 1);
    a4_one.ConvertFrom(a3, p_tuple::overflow_zero() );
    CHECK_TUP(a4_one, 0, 0, 0, 0);

    a4_same.ConvertFrom(a5);
    CHECK_TUP(a4_same, 2, 2, 2, 2);
    a4_same.ConvertFrom(a3); // default overflow policy is overflow_one
    CHECK_TUP(a4_same, 0, 0, 0, 1);
  }

  TEST_CASE("Core/DataStructures/Tuple/ConvertTo",
    "Conversion from different sized tuples")
  {
    Tuple<tl_int, 3> a3(0);
    Tuple<tl_int, 4> a4_same(10), a4_one(20), a4_zero(30);
    Tuple<tl_int, 5> a5(2);

    a4_one = a3.ConvertTo<Tuple<int, 4>, p_tuple::overflow_one>();
    CHECK_TUP(a4_one, 0, 0, 0, 1);
    a4_one = a3.ConvertTo<Tuple<int, 4>, p_tuple::overflow_zero>();
    CHECK_TUP(a4_one, 0, 0, 0, 0);

    a4_same = a5.ConvertTo<Tuple<int, 4> >();
    CHECK_TUP(a4_same, 2, 2, 2, 2);
    a4_same = a3.ConvertTo<Tuple<int, 4> >(); // default overflow policy is overflow_one
    CHECK_TUP(a4_same, 0, 0, 0, 1);
  }
};