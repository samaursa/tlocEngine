#include "tlocTestCommon.h"

#include <tlocCore/tlocAlgorithms.h>
#include "tlocCore/tlocAlgorithms.inl.h"

#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/data_structures/tlocTuple.inl.h>

#include <tlocCore/data_structures/tlocVariadic.h>

namespace TestingTuple
{
  using namespace tloc;
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
    CHECK(p.size() == 4);

    Tuple<tl_int, 4> q(8);
    p.Swap(q);

    CHECK_TUP(p, 8, 8, 8, 8);
    CHECK_TUP(q, 5, 5, 5, 5);

    tl_int numberSet[4] = {1, 2, 3, 4};
    p.Set(numberSet);
    CHECK_TUP(p, 1, 2, 3, 4);

    // Check Size
    CHECK(q.size() == 4);

    Tuple<tl_int, 4> r(numberSet);
    CHECK_TUP(r, 1, 2, 3, 4);

    r.Set(0);
    CHECK_TUP(r, 0, 0, 0, 0);
    r = numberSet;
    CHECK_TUP(r, 1, 2, 3, 4);

    // Check Size
    CHECK(r.size() == 4);

    Tuple<tl_int, 4> s(r);
    CHECK_TUP(s, 1, 2, 3, 4);

    s.Set(0);
    CHECK_TUP(s, 0, 0, 0, 0);
    s = r;
    CHECK_TUP(s, 1, 2, 3, 4);

    // Check Size
    CHECK (q.size() == 4);
  }

  TEST_CASE("Core/DataStructures/Tuple/VariadicCtor",
    "Test the Tuple ctor with varadic")
  {
    Tuple<tl_int, 4> p(Variadic4s(1, 2, 3, 4));

    CHECK(p.size() == 4);
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

    Tuple<tl_uint, 4> u4(10);

    a4_one = a3.ConvertTo<Tuple<tl_int, 4>, p_tuple::overflow_one>();
    CHECK_TUP(a4_one, 0, 0, 0, 1);
    a4_one = a3.ConvertTo<Tuple<tl_int, 4>, p_tuple::overflow_zero>();
    CHECK_TUP(a4_one, 0, 0, 0, 0);

    a4_same = a5.ConvertTo<Tuple<tl_int, 4> >();
    CHECK_TUP(a4_same, 2, 2, 2, 2);
    a4_same = a3.ConvertTo<Tuple<tl_int, 4> >(); // default overflow policy is overflow_one
    CHECK_TUP(a4_same, 0, 0, 0, 1);

    u4 = a3.ConvertTo<Tuple<tl_uint, 4> >();
    CHECK_TUP(u4, 0, 0, 0, 1);
  }

  TEST_CASE("Core/DataStructures/Tuple/Implicit conversion",
    "Conversion from different tuple types")
  {
    Tuple<s64, 4> a3(core_ds::Variadic<s64, 4>(1, 2, 3, 9));
    Tuple<s32, 4> a4(0);

    a4 = a3.Cast<Tuple<s32, 4> >();
    CHECK_TUP(a4, 1, 2, 3, 9);

    a4 = a4.Cast<Tuple<s32, 4> >();
    CHECK_TUP(a4, 1, 2, 3, 9);
  }

  TEST_CASE("Core/DataStructures/Tuple/MakeTuple", "")
  {
    Tuple<s32, 1> tup1 = core_ds::MakeTuple(1);
    CHECK(tup1[0] == 1);

    Tuple<s32, 2> tup2 = core_ds::MakeTuple(1, 2);
    CHECK(tup2[0] == 1);
    CHECK(tup2[1] == 2);

    Tuple<s32, 3> tup3 = core_ds::MakeTuple(1, 2, 3);
    CHECK(tup3[0] == 1);
    CHECK(tup3[1] == 2);
    CHECK(tup3[2] == 3);

    Tuple<s32, 4> tup4 = core_ds::MakeTuple(1, 2, 3, 4);
    CHECK(tup4[0] == 1);
    CHECK(tup4[1] == 2);
    CHECK(tup4[2] == 3);
    CHECK(tup4[3] == 4);

    Tuple<s32, 5> tup5 = core_ds::MakeTuple(1, 2, 3, 4, 5);
    CHECK(tup5[0] == 1);
    CHECK(tup5[1] == 2);
    CHECK(tup5[2] == 3);
    CHECK(tup5[3] == 4);
    CHECK(tup5[4] == 5);
  }

  TEST_CASE("Core/DataStructures/Tuple/Simple Arithmetic", "")
  {
    Tuple4f tup   = core_ds::MakeTuple(1.0f, 3.0f, 5.0f, 1.0f);
    Tuple4f tup2  = core_ds::MakeTuple(5.0f, -2.0f, 8.0f, 2.0f);

    Tuple4f resAdd  = Add(tup, tup2);
    Tuple4f resSub  = Subtract(tup, tup2);
    Tuple4f resMul  = Multiply(3.0f, tup);
    Tuple4f resDiv  = Divide(1.0f, tup);
    Tuple4f resDiv2 = Divide(2.0f, tup2);

    CHECK_TUP(resAdd, 6.0f, 1.0f, 13.0f, 3.0f);
    CHECK_TUP(resSub, -4.0f, 5.0f, -3.0f, -1.0f);
    CHECK_TUP(resMul, 3.0f, 9.0f, 15.0f, 3.0f);
    CHECK_TUP(resDiv, 1.0f, 3.0f, 5.0f, 1.0f);
    CHECK_TUP(resDiv2, 5.0f / 2.0f, -2.0f / 2.0f, 8.0f / 2.0f, 2.0f / 2.0f);
  }

  TEST_CASE("Core/DataStructures/Tuple/Clamp", "")
  {
    Tuple4f tup   = core_ds::MakeTuple(-5.0f, 3.0f, 7.0f, 1.0f);
    auto tup2 = core::Clamp(tup, 0.0f, 5.0f);
    CHECK_TUP(tup2, 0.0f, 3.0f, 5.0f, 1.0f);
  }
};
