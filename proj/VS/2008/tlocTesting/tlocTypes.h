namespace TESTING_TYPES
{
  USING_TLOC;

  struct ConditionalFixture
  {
    ConditionalType<s32, true> a;
  };

  TEST_CASE_METHOD(ConditionalFixture, "Core/Types/ConditionalType", "")
  {
    a = 5;
    CHECK(a.value() == 5);

    a *= 10;
    CHECK(a.value() == 50);

    a /= 2;
    CHECK(a.value() == 25);

    a += 25;
    CHECK(a.value() == 50);

    a -= 25;
    CHECK(a.value() == 25);

    a = a + 25;
    CHECK(a.value() == 50);

    a = a - 25;
    CHECK(a.value() == 25);

    a = a * 2;
    CHECK(a.value() == 50);

    a = a / 2;
    CHECK(a.value() == 25);
  }
};
