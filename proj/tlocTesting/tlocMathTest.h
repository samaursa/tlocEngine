namespace TestingTlocMath
{
  using namespace tloc::Math;

  TEST_CASE("Math/CeilFloor", "")
  {
    float aValue = 1.5;
    REQUIRE(Ceil(aValue) == 2);
    REQUIRE(Ceil(1.1) == 2);

    REQUIRE(Floor(aValue) == 1);
    REQUIRE(Floor(1.9) == 1);
  }

  TEST_CASE("Math/Abs", "")
  {
    REQUIRE(Abs(-2) == 2);
    REQUIRE(Abs(-2.756f) == Approxf(2.756f));
  }

  TEST_CASE("Math/AtanAtan2", "")
  {
    REQUIRE(ATan(5.0f) == Approxf(1.37340076f));
    REQUIRE(ATan2(-862.42f, 78.5149f) == Approxf(-1.4800063f));
  }

  TEST_CASE("Math/IsNaN", "")
  {
    float b = sqrt(-1.0f);
    REQUIRE(IsNaN(b) == true);
  }

  TEST_CASE("Math/Approx", "")
  {
    float a = 1.0f, b = 1.0f;
    REQUIRE(tloc::Math::Approx(a, b));
    a = 1.000001f;
    REQUIRE(tloc::Math::Approx(a, b));
  }

  TEST_CASE("Math/DegreeRadian", "")
  {
    float degree = 1.0f;
    REQUIRE( Radian(degree) == Approxf(0.0174532925f) );
  }
};