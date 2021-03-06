#include "tlocTestCommon.h"

#include <tlocMath/tlocMath.h>
#include <tlocMath/tlocMath.inl.h>

namespace TestingTlocMath
{
  using namespace tloc;

  TEST_CASE("Math/CeilFloor", "")
  {
    f32 aValue = 1.5;
    CHECK(math::Ceil(aValue) == 2);
    CHECK(math::Ceil(1.1f) == 2);

    CHECK(math::Floor(aValue) == 1);
    CHECK(math::Floor(1.9f) == 1);
  }

  TEST_CASE("Math/Abs", "")
  {
    CHECK(math::Abs(-2) == 2);
    CHECK(math::Abs(-2.756f) == Approx(2.756f));
  }

  TEST_CASE("Math/AtanAtan2", "")
  {
    CHECK(math::ATan(5.0f).Get() == Approx(1.37340076f));
    CHECK(math::ATan2(-862.42f, 78.5149f).Get() == Approx(-1.4800063f));
  }

  TEST_CASE("Math/IsNaN", "")
  {
    f32 b = sqrt(-1.0f);
    CHECK(math::IsNaN(b) == true);
  }

  TEST_CASE("Math/Approx", "")
  {
    f32 a = 1.0f, b = 1.0f;
    CHECK(math::Approx(a, b, 1));
    a = 1.23456789f;
    b = 1.23456789f;
    CHECK(math::Approx(a, b, 1));
  }

  TEST_CASE("Math/IsPowerOfTwo", "")
  {
    tl_uint tempVal = 8;
    CHECK(math::IsPowerOfTwo(tempVal) == true);

    tempVal = 9;
    CHECK(math::IsPowerOfTwo(tempVal) == false);
  }

  TEST_CASE("Math/FastPowerOfTwo", "")
  {
    tl_uint val = math::FastPowOfTwo(8);
    CHECK(val == 256);
    val = math::FastPowOfTwo(16);
    CHECK(val == 65536);
  }

  TEST_CASE("Math/FastSignInt", "")
  {
    s32 val = math::FastSignInt(1.5f);
    CHECK(val == 1);
    val = math::FastSignInt(-50.9f);
    CHECK(val == -1);
    val = math::FastSignInt(0.0f);
    CHECK(val == 0);
  }

  TEST_CASE("Math/RoundUpPowerOfTwo", "")
  {
    CHECK(math::RoundUpPowOfTwo(0) == 2);
    CHECK(math::RoundUpPowOfTwo(1) == 2);
    CHECK(math::RoundUpPowOfTwo(7) == 8);
    CHECK(math::RoundUpPowOfTwo(99) == 128);
    CHECK(math::RoundUpPowOfTwo(2047) == 2048);
  }

  TEST_CASE("Math/Lerp", "")
  {
    f32 value1 = 0.0f;
    f32 value2 = 1.0f;
    CHECK(math::Lerp(value1, value2) == Approx(0.5f));
  }

  TEST_CASE("Math/Remainder", "")
  {
    {
      tl_float num1 = 6.0f;
      tl_float num2 = 2.0f;
      tl_float rem = math::Remainder(num1, num2);
      CHECK(rem == Approx(0.0f));

      num1 = 5.0f;
      rem = math::Remainder(num1, num2);
      CHECK(rem == Approx(1.0f));
    }

    {
      tl_float num1 = 1.0f;
      tl_float num2 = 0.1f;
      tl_float rem = math::Remainder(num1, num2);
      CHECK(rem == Approx(0.0f));
    }

    {
      tl_int num1 = 6;
      tl_int num2 = 2;
      tl_int rem = math::Remainder(num1, num2);
      CHECK(rem == 0);

      num1 = 5;
      rem = math::Remainder(num1, num2);
      CHECK(rem == 1);
    }
  }

  TEST_CASE("math/Abs", "")
  {
    SECTION("floats", "")
    {
      CHECK(math::Abs(-5.0f) == Approx(5.0f));
      CHECK(math::Abs(5.0f) == Approx(5.0f));
    }

    SECTION("non floats", "")
    {
      CHECK(math::Abs(-5) == 5);
      CHECK(math::Abs(5) == 5);
    }
  }

  TEST_CASE("math/Approx", "")
  {
    SECTION("floats", "")
    {
      CHECK(math::Approx(1.0f, 1.0f, 1) );
      CHECK_FALSE(math::Approx(1.0f, 1.0001f, 1) );
    }

    SECTION("non floats", "")
    {
      CHECK(math::Approx(1, 1, 0) );
      CHECK(math::Approx(1.0f, 1.0f, 1) );
      CHECK(math::Approx(0.0f, 0.0f, 1) );
      CHECK(math::Approx(-0.0f, +0.0f, 1) );

      const auto f32_eps = NumericLimits_T<f32>::epsilon();
      const auto s32_eps = NumericLimits_T<s32>::epsilon();

      CHECK(math::ApproxAbsolute(1, 1, s32_eps) );
      CHECK(math::ApproxAbsolute(1.0f, 1.0f, f32_eps) );
      CHECK(math::ApproxAbsolute(0.0f, 0.0f, f32_eps) );
      CHECK(math::ApproxAbsolute(-0.0f, +0.0f, f32_eps) );

      CHECK(math::ApproxRelative(1, 1, s32_eps) );
      CHECK(math::ApproxRelative(1.0f, 1.0f, f32_eps) );
      CHECK(math::ApproxRelative(0.0f, 0.0f, f32_eps) );
      CHECK(math::ApproxRelative(-0.0f, +0.0f, f32_eps) );

      CHECK_FALSE(math::Approx(f32_eps, f32_eps + f32_eps, 1) );

      CHECK(math::ApproxRelative(1.0f, 2.0f, 0.5f) );
      CHECK_FALSE(math::ApproxRelative(1, 2, math::Epsilon<tl_int>()) );
    }
  }

  TEST_CASE("math/IsEqual", "")
  {
    SECTION("floats", "")
    {
      CHECK(math::IsEqual(1.0f, 1.0f) );
      CHECK(math::IsEqualToZero(0.0f) );
      CHECK(math::IsEqualToOne(1.0f) );

      CHECK_FALSE(math::IsEqual(1.0f, 1.0001f) );
      CHECK_FALSE(math::IsEqualToZero(0.1f) );
      CHECK_FALSE(math::IsEqualToOne(1.1f) );
    }

    SECTION("non floats", "")
    {
      CHECK(math::IsEqual(1, 1) );
      CHECK(math::IsEqualToZero(0) );
      CHECK(math::IsEqualToOne(1) );

      CHECK_FALSE(math::IsEqual(1, 2) );
      CHECK_FALSE(math::IsEqualToZero(1) );
      CHECK_FALSE(math::IsEqualToOne(2) );
    }
  }
};