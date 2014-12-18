#include "tlocTestCommon.h"

#include <tlocMath/tlocRange.h>

namespace TestingRange
{
  using namespace tloc;
  using namespace math;

  // Tests are taken from https://bitbucket.org/AraK/range and modified where
  // appropriate

  template <typename T_RangeType>
  void TestCtors()
  {
    typedef T_RangeType range_type;

    CHECK(range_type().empty());

    range_type r;
    r = range_type(0, 10);
    r = range_type(10, 10);
    r = range_type(0, 0);

    r = range_type(0, 10, typename range_type::step_size(1));
    r = range_type(0, 0, typename range_type::step_size(2));

    range_type r2(r);
    CHECK(r2 == r);
  }

  TEST_CASE("math/range/ctors", "")
  {
    TestCtors<range_s8>();
    TestCtors<range_u8>();
    TestCtors<Range>();
    TestCtors<Rangef>();
  }

  template <typename T_RangeType>
  void TestAccessors()
  {
    typedef T_RangeType range_type;

    range_type r(0, 10);
    CHECK(r.front() == 0);
    CHECK(r.back() == 9);

    r = range_type(0, 0);
    CHECK(r.front() == 0);
    CHECK(r.back() == 0);

    r = range_type(5, 10);
    CHECK(r.front() == 5);
    CHECK(r.back() == 9);

    r = range_type(0, 10, typename range_type::step_size(2));
    CHECK(r.front() == 0);
    CHECK(r.back() == 8);

    r = range_type(0, 10, typename range_type::step_size(3));
    CHECK(r.front() == 0);
    CHECK(r.back() == 9);

    r = range_type(0, 10, typename range_type::step_size(4));
    CHECK(r.front() == 0);
    CHECK(r.back() == 8);

    r = range_type(10, 50, typename range_type::step_size(10));
    CHECK(r.front() == 10);
    CHECK(r.back() == 40);

    r = range_type(10, 51, typename range_type::step_size(10));
    CHECK(r.front() == 10);
    CHECK(r.back() == 50);
  }

  TEST_CASE("math/range/accessors", "")
  {
    TestAccessors<range_s8>();
    TestAccessors<range_u8>();
    TestAccessors<Range>();
    TestAccessors<Rangef>();
  }

  template <typename T_RangeType>
  void TestSize()
  {
    typedef T_RangeType range_type;

    range_type r(0, 10);
    CHECK(r.size() == 10);
    r = range_type(0, 10, typename range_type::step_size(2));
    CHECK(r.size() == 5);
    r = range_type(0, 10, typename range_type::step_size(10));
    CHECK(r.size() == 1);
    r = range_type(0, 10, typename range_type::step_size(11));
    CHECK(r.size() == 1);
    r = range_type(5, 15);
    CHECK(r.size() == 10);
  }

  TEST_CASE("math/range/size", "")
  {
    TestSize<range_s8>();
    TestSize<range_u8>();
    TestSize<Range>();
    TestSize<Rangef>();
  }

  template <typename T_RangeType>
  void TestEmptyFull()
  {
    typedef T_RangeType range_type;

    CHECK(range_type().empty());
    range_type r(77, 127);
    CHECK_FALSE(r.empty());
    r = range_type(127, 127);
    CHECK(r.empty());
  }

  TEST_CASE("math/range/empty_full", "")
  {
    TestEmptyFull<range_s8>();
    TestEmptyFull<range_u8>();
    TestEmptyFull<Range>();
    TestEmptyFull<Rangef>();
  }

  template <typename T_RangeType>
  void TestIterators()
  {
    typedef T_RangeType range_type;

    range_type r(0, 10);
    typename range_type::iterator itr = r.begin();
    typename range_type::reverse_iterator rItr = r.rbegin();

    bool testPassed = true;
    for (tl_int i = 0; i < 10; ++i)
    {
      if (*(itr++) != i)
      { testPassed = false; break; }
    }
    CHECK(testPassed);

    testPassed = true;
    for (tl_int i = 10; i > 0; --i)
    {
      if (*(rItr++) != i-1)
      { testPassed = false; break; }
    }
    CHECK(testPassed);

    rItr -= 10; // we were at rend, so we can go rback 10 indices
    CHECK(*rItr == 9);
    rItr += 9; // we were at rbegin, we can go rforward 9 indices
    CHECK(*rItr == 0);

    CHECK(*rItr-- == 0);
    CHECK(*rItr   == 1);
    CHECK(*--rItr == 2);

    CHECK(*rItr++ == 2);
    CHECK(*rItr   == 1);
    CHECK(*++rItr == 0);

    CHECK( *(rItr - 9) == 9);
    CHECK( *( (--rItr) + 1) == 0);

    r = range_type(0, 10, typename range_type::step_size(2));
    itr = r.begin();
    testPassed = true;
    for (tl_int i = 0; i < 10; i = i+2)
    {
      if (*(itr++) != i)
      { testPassed = false; break; }
    }
    CHECK(testPassed);

    r = range_type(5, 6);
    itr = r.begin();
    testPassed = true;
    for (tl_int i = 5; i < 6; ++i)
    {
      if (*(itr++) != i)
      { testPassed = false; break; }
    }
    CHECK(testPassed);

    r = range_type(5, 6, typename range_type::step_size(10));
    itr = r.begin();
    testPassed = true;
    for (tl_int i = 5; i < 6; i = i + 10)
    {
      if (*(itr++) != i)
      { testPassed = false; break; }
    }
    CHECK(testPassed);

    r = range_type(0, 50, typename range_type::step_size(2));
    itr = r.begin();
    typename range_type::iterator itrEnd = r.end();
    tl_int count = 0;
    for (; itr < itrEnd; ++itr)
    {
      ++count;
    }
    CHECK(count == 50/2);

    itr -= 25;
    CHECK(*itr == 0);
    itr += 10;
    CHECK(*itr == 20);

    CHECK(*itr++ == 20);
    CHECK(*itr   == 22);
    CHECK(*++itr == 24);

    CHECK(*itr == 24);

    CHECK(*itr-- == 24);
    CHECK(*itr   == 22);
    CHECK(*--itr == 20);

    CHECK( *(itr - 10) == 0);
    CHECK( *( (--itr) + 1) == 20);
  }

  TEST_CASE("math/range/iterators", "")
  {
    TestIterators<range_s8>();
    TestIterators<range_u8>();
    TestIterators<Range>();
    TestIterators<Rangef>();
  }

  TEST_CASE("math/range/GetRange()", "")
  {
    CHECK(Range0to1<f32>().Get().front() == Approx(0.0f));
    CHECK(Range0to1<f32>().Get().back() == Approx(0.9f));

    CHECK( (Range0to1<f32, p_range::Inclusive>().Get().front()) == Approx(0.0f));
    CHECK( (Range0to1<f32, p_range::Inclusive>().Get().back()) == Approx(1.0f));

    CHECK(RangeNeg1to1<f32>().Get().front() == Approx(-1.0f));
    CHECK(RangeNeg1to1<f32>().Get().back() == Approx(0.9f));

    CHECK( (RangeNeg1to1<f32, p_range::Inclusive>().Get().front()) == Approx(-1.0f));
    CHECK( (RangeNeg1to1<f32, p_range::Inclusive>().Get().back()) == Approx(1.0f));

    CHECK(Range0to128<s16>().Get().front() == 0);
    CHECK(Range0to128<s16>().Get().back() == 127);

    CHECK( (Range0to128<s16, p_range::Inclusive>().Get().front()) == 0);
    CHECK( (Range0to128<s16, p_range::Inclusive>().Get().back()) == 128);

    CHECK(Range0to128<s32>().Get().front() == 0);
    CHECK(Range0to128<s32>().Get().back() == 127);

    CHECK( (Range0to128<s32, p_range::Inclusive>().Get().front()) == 0);
    CHECK( (Range0to128<s32, p_range::Inclusive>().Get().back()) == 128);

    CHECK(Range0to256<s16>().Get().front() == 0);
    CHECK(Range0to256<s16>().Get().back() == 255);

    CHECK( (Range0to256<s16, p_range::Inclusive>().Get().front()) == 0);
    CHECK( (Range0to256<s16, p_range::Inclusive>().Get().back()) == 256);

    CHECK(Range0to256<s32>().Get().front() == 0);
    CHECK(Range0to256<s32>().Get().back() == 255);

    CHECK( (Range0to256<s32, p_range::Inclusive>().Get().front()) == 0);
    CHECK( (Range0to256<s32, p_range::Inclusive>().Get().back()) == 256);
  }

  TEST_CASE("math/range/NegativeRange", "")
  {
    SECTION("range_s8", "Negative range")
    {
      range_s8 r(-5, 5);
      CHECK(r.size() == 10);
      CHECK(r.front() == -5);
      CHECK(r.back() == 4);

      CHECK(r.IsInRange(-5));
      CHECK(r.IsInRange(4));
      CHECK_FALSE(r.IsInRange(5));
      CHECK_FALSE(r.IsInRange(-6));
      CHECK_FALSE(r.IsInRange(6));
    }

    SECTION("range_f32", "Negative range")
    {
      range_f32 rf32(-1.0f, 1.2f, range_f32::step_size(0.1f));
      CHECK(rf32.front() == Approx(-1.0f));
      CHECK(rf32.back() == Approx(1.1f));

      CHECK(rf32.IsInRange(-1.0f));
      CHECK(rf32.IsInRange(1.1f));
      CHECK_FALSE(rf32.IsInRange(1.2f));
      CHECK_FALSE(rf32.IsInRange(-1.01f));
    }
  }
}
