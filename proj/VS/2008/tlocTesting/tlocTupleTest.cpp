#include "tlocTestCommon.h"

#include "tlocCore/tlocAlgorithms.h"
#include "tlocCore/tlocAlgorithms.inl"

#include "tlocCore/tlocTuple.h"
#include "tlocCore/tlocTuple.inl"

namespace TestingTuple
{
  USING_TLOC;

#define CHECK_TUP(tup,x,y,z,w)   CHECK(tup[0] == x); \
  CHECK(tup[1] == y); \
  CHECK(tup[2] == z); \
  CHECK(tup[3] == w);

  TEST_CASE("Core/DataStructures/Tuple", "Testing the Tuple<T, size> class")
  {
    core::Tuple<s32, 4> p(0);
    CHECK_TUP(p, 0, 0, 0, 0);

    p[0] = 0; p[1] = 1; p[2] = 2; p[3] = 3;
    CHECK_TUP(p, 0, 1, 2, 3);

    CHECK(p.Get(0) == 0);
    CHECK(p.Get(1) == 1);
    CHECK(p.Get(2) == 2);
    CHECK(p.Get(3) == 3);

    // Direct access
    CHECK( *(p + 0) == 0);
    CHECK( *(p + 1) == 1);
    CHECK( *(p + 2) == 2);
    CHECK( *(p + 3) == 3);

    p.Set(5);
    CHECK_TUP(p, 5, 5, 5, 5);

    core::Tuple<s32, 4> q(8);
    p.Swap(q);

    CHECK_TUP(p, 8, 8, 8, 8);
    CHECK_TUP(q, 5, 5, 5, 5);

    u32 numberSet[4] = {1, 2, 3, 4};
    p.Set(numberSet);
    CHECK_TUP(p, 1, 2, 3, 4);

    core::Tuple<s32, 4> r(numberSet);
    CHECK_TUP(r, 1, 2, 3, 4);

    r.Set(0);
    CHECK_TUP(r, 0, 0, 0, 0);
    r = numberSet;
    CHECK_TUP(r, 1, 2, 3, 4);

    core::Tuple<s32, 4> s(r);
    CHECK_TUP(s, 1, 2, 3, 4);

    s.Set(0);
    CHECK_TUP(s, 0, 0, 0, 0);
    s = r;
    CHECK_TUP(s, 1, 2, 3, 4);
  }

  TEST_CASE("Core/DataStructures/Tuple/Operators",
    "Testing the operator functions")
  {
    core::Tuple<s32, 4> p(0), q(1);
    CHECK( (p == q) == false);
    CHECK( (p != q) == true);

    p = q;
    CHECK( (p == q) == true);
    CHECK( (p != q) == false);
  }
};