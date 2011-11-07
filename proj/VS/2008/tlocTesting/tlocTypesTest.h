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
    ConditionalType<s32, true> a2;
  };

  struct ConditionalFixtureFalse
  {
    ConditionalType<s32, false> a;
    ConditionalType<s32, false> a2;
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

    a2 = a;
    CHECK(a.value() == 25);
    CHECK(a2.value() == 25);

    a2 = a - a2;
    CHECK(a2.value() == 0);
    CHECK(a.value() == 25);

    a2 = a + a;
    CHECK(a2.value() == 50);
    CHECK(a.value() == 25);

    a2 = a2 / a;
    CHECK(a2.value() == 2);
    CHECK(a.value() == 25);

    a2 = a2 * a;
    CHECK(a2.value() == 50);
    CHECK(a.value() == 25);

    CHECK( (a == 25) == true);
    CHECK( (a2 == 50) == true);
    CHECK( (a < a2) == true);
    CHECK( (a < 50) == true);
    CHECK( (a2 > a) == true);
    CHECK( (a2 > 25) == true);
    CHECK( (a == 25) == true);
    CHECK( (a2 == 50) == true);

    a = a2;
    CHECK( (a == a2) == true);

    a = 5;
    CHECK( (5 - a) == 0);
    CHECK( (5 + a) == 10);
    CHECK( (5 * a) == 25);
    CHECK( (10 / a) == 2);
    CHECK( (10 < a) == false);
    CHECK( (10 > a) == true);
    CHECK( (5 >= a) == true);
    CHECK( (6 >= a) == true);
    CHECK( (5 <= a) == true);
    CHECK( (2 <= a) == true);
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

    ConditionalType<s32, false> b = a++;
    CHECK(a.value() == a.g_conditional_type_invalid_value );
    CHECK(b.value() == b.g_conditional_type_invalid_value );

    b = a--;
    CHECK(a.value() == a.g_conditional_type_invalid_value );
    CHECK(b.value() == b.g_conditional_type_invalid_value );

    a2 = a;
    CHECK(a.value() == a.g_conditional_type_invalid_value );
    CHECK(a2.value() == a2.g_conditional_type_invalid_value );

    a2 = a - a2;
    CHECK(a2.value() == a2.g_conditional_type_invalid_value );
    CHECK(a.value() == a.g_conditional_type_invalid_value );

    a2 = a + a;
    CHECK(a2.value() == a2.g_conditional_type_invalid_value );
    CHECK(a.value() == a.g_conditional_type_invalid_value );

    a2 = a2 / a;
    CHECK(a2.value() == a2.g_conditional_type_invalid_value );
    CHECK(a.value() == a.g_conditional_type_invalid_value );

    a2 = a2 * a;
    CHECK(a2.value() == a2.g_conditional_type_invalid_value );
    CHECK(a.value() == a.g_conditional_type_invalid_value );

    CHECK( (a == 25) == false);
    CHECK( (a2 == 50) == false);
    CHECK( (a < a2) == false);
    CHECK( (a < 50) == false);
    CHECK( (a2 > a) == false);
    CHECK( (a2 > 25) == false);
    CHECK( (a == 25) == false);
    CHECK( (a2 == 50) == false);

    a = a2;
    CHECK( (a == a2) == false);
  }
};
