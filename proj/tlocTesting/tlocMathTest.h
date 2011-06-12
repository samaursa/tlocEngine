namespace TestingTlocMath
{
  using namespace tloc::Math;

  TEST_CASE("Math/CeilFloor", "")
  {
    float aValue = 1.5;
    CHECK(Ceil(aValue) == 2);
    CHECK(Ceil(1.1) == 2);

    CHECK(Floor(aValue) == 1);
    CHECK(Floor(1.9) == 1);
  }

  TEST_CASE("Math/Abs", "")
  {
    CHECK(Abs(-2) == 2);
    CHECK(Abs(-2.756f) == Approxf(2.756f));
  }

  TEST_CASE("Math/AtanAtan2", "")
  {
    CHECK(ATan(5.0f) == Approxf(1.37340076f));
    CHECK(ATan2(-862.42f, 78.5149f) == Approxf(-1.4800063f));
  }

  TEST_CASE("Math/IsNaN", "")
  {
    float b = sqrt(-1.0f);
    CHECK(IsNaN(b) == true);
  }

  TEST_CASE("Math/Approx", "")
  {
    float a = 1.0f, b = 1.0f;
    CHECK(tloc::Math::Approx(a, b));
    a = 1.000001f;
    CHECK(tloc::Math::Approx(a, b));
  }

  TEST_CASE("Math/DegreeRadian", "")
  {
    float degree = 1.0f;
    CHECK( Radian(degree) == Approxf(0.0174532925f) );
  }
};