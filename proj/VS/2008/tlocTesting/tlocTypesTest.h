namespace tloc
{
  s32 ConditionalType<s32, false>::g_conditional_type_invalid_value = 0;
}

namespace TESTING_TYPES
{
  USING_TLOC;

  struct ConditionalFixtureTrue
  {
    ConditionalType<s32, true> a;
  };

  struct ConditionalFixtureFalse
  {
    ConditionalType<s32, false> a;
  };

  TEST_CASE_METHOD(ConditionalFixtureTrue, "Core/Types/ConditionalTypeTrue", "")
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

    ConditionalType<s32, true> b = a++;
    CHECK(a.value() == 26);
    CHECK(b.value() == 25);

    b = a--;
    CHECK(a.value() == 25);
    CHECK(b.value() == 26);
  }

  TEST_CASE_METHOD(ConditionalFixtureFalse, "Core/Types/ConditionalTypeFalse", "")
  {
    a = 5;
    CHECK(a.value() == a.g_conditional_type_invalid_value );

    a *= 10;
    CHECK(a.value() == a.g_conditional_type_invalid_value );

    a /= 2;
    CHECK(a.value() == a.g_conditional_type_invalid_value );

    a += 25;
    CHECK(a.value() == a.g_conditional_type_invalid_value );

    a -= 25;
    CHECK(a.value() == a.g_conditional_type_invalid_value );

    a = a + 25;
    CHECK(a.value() == a.g_conditional_type_invalid_value );

    a = a - 25;
    CHECK(a.value() == a.g_conditional_type_invalid_value );

    a = a * 2;
    CHECK(a.value() == a.g_conditional_type_invalid_value );

    a = a / 2;
    CHECK(a.value() == a.g_conditional_type_invalid_value );

  }
};
