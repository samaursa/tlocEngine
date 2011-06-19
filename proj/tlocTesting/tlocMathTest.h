namespace TestingTlocMath
{
  using namespace tloc;

  TEST_CASE("Math/CeilFloor", "")
  {
    float aValue = 1.5;
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
    float b = sqrt(-1.0f);
    CHECK(Mathf::IsNaN(b) == true);
  }

  TEST_CASE("Math/Approx", "")
  {
    float a = 1.0f, b = 1.0f;
    CHECK(Mathf::Approx(a, b));
    a = 1.000001f;
    CHECK(Mathf::Approx(a, b));
  }

  TEST_CASE("Math/DegreeRadian", "")
  {
    float degree = 1.0f;
    CHECK( Mathf::Radian(degree) == Approx(0.0174532925f) );
  }
};