#include "tlocTestCommon.h"

#include <tlocMath/tlocMath.h>
#include <tlocMath/tlocMath.inl>

namespace TestingTlocMath
{
  using namespace tloc;

  TEST_CASE("Math/CeilFloor", "")
  {
    f32 aValue = 1.5;
    CHECK(Mathf::Ceil(aValue) == 2);
    CHECK(Mathf::Ceil(1.1f) == 2);

    CHECK(Mathf::Floor(aValue) == 1);
    CHECK(Mathf::Floor(1.9f) == 1);
  }

  TEST_CASE("Math/Abs", "")
  {
    CHECK(Mathf::Abs(-2) == 2);
    CHECK(Mathf::Abs(-2.756f) == Approx(2.756f));
  }

  TEST_CASE("Math/AtanAtan2", "")
  {
    CHECK(Mathf::ATan(5.0f) == Approx(1.37340076f));
    CHECK(Mathf::ATan2(-862.42f, 78.5149f) == Approx(-1.4800063f));
  }

  TEST_CASE("Math/IsNaN", "")
  {
    f32 b = sqrt(-1.0f);
    CHECK(Mathf::IsNaN(b) == true);
  }

  TEST_CASE("Math/Approx", "")
  {
    f32 a = 1.0f, b = 1.0f;
    CHECK(Mathf::Approx(a, b));
    a = 1.23456789f;
    b = 1.23456789f;
    CHECK(Mathf::Approx(a, b));
  }

  TEST_CASE("Math/DegreeRadian", "")
  {
    f32 degree = 1.0f;
    CHECK( Mathf::Radian(degree) == Approx(0.0174532925f) );
  }

  TEST_CASE("Math/IsPowerOfTwo", "")
  {
    tl_uint tempVal = 8;
    CHECK(Mathu::IsPowerOfTwo(tempVal) == true);

    tempVal = 9;
    CHECK(Mathu::IsPowerOfTwo(tempVal) == false);
  }

  TEST_CASE("Math/FastPowerOfTwo", "")
  {
    tl_uint val = Mathu::FastPowOfTwo(8);
    CHECK(val == 256);
    val = Mathu::FastPowOfTwo(16);
    CHECK(val == 65536);
  }

  TEST_CASE("Math/FastSignInt", "")
  {
    s32 val = Mathf::FastSignInt(1.5f);
    CHECK(val == 1);
    val = Mathf::FastSignInt(-50.9f);
    CHECK(val == -1);
    val = Mathf::FastSignInt(0.0f);
    CHECK(val == 0);
  }

  TEST_CASE("Math/Lerp", "")
  {
    f32 value1 = 0.0f;
    f32 value2 = 1.0f;
    CHECK(Mathf::Lerp(value1, value2) == Approx(0.5f));
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
};