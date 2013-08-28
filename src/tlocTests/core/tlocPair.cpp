#include "tlocTestCommon.h"

#include <tlocCore/tlocPair.h>
#include <tlocCore/tlocPair.inl.h>


namespace TestingPair
{
  using namespace tloc;
  using namespace core;

  struct PairFixture
  {

  };

  TEST_CASE("Core/Pair/Ctors", "")
  {
    Pair<s32, f32> p1;
    Pair<s32, f32> p2(1, 1.0f);

    CHECK(p2.first == 1); CHECK(p2.second == Approx(1.0f)); //-V550

    Pair<s32, f32> p3(p2);
    CHECK(p3.first == 1); CHECK(p3.second == Approx(1.0f)); //-V550

    Pair<s32, f32> p4(2, 0.5f);
  }

  TEST_CASE("Core/Pair/MakePair()", "")
  {
    Pair<s32, f32> p1 = MakePair(1, 1.0f);
    Pair<s32, f32> p2(p1);

    CHECK(p1.first == 1); CHECK(p1.second == Approx(1.0f)); //-V550
    CHECK(p2.first == 1); CHECK(p2.second == Approx(1.0f)); //-V550
  }

  TEST_CASE("Core/Pair/Operators", "")
  {
    Pair<s32, f32> p1 = MakePair(1, 1.0f);
    Pair<s32, f32> p2(p1);

    CHECK(p1.first == 1); CHECK(p1.second == Approx(1.0f)); //-V550
    CHECK(p2.first == 1); CHECK(p2.second == Approx(1.0f)); //-V550

    CHECK(p1 == p2);

    Pair<s32, f32> p3(1, 0.5f);
    CHECK( (p1 > p3) == true);
    CHECK( (p3 < p1) == true);
    CHECK( p1 != p3);

    Pair<s32, f32> p4(2, 0.5f);
    CHECK( (p4 < p3) == false);
    CHECK( (p3 > p4) == false);
    CHECK( (p4 >= p3) == true);
    CHECK( (p3 <= p4) == true);
  }
}
