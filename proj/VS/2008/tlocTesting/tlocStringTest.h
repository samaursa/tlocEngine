namespace TestingStrings
{
  struct StringFixture
  {
    StringBase<char8> a, b, c, d, e, f;
  };

  TEST_CASE_METHOD(StringFixture, "Core/Strings/Construction",
    "Test basic string construction")
  {
    StringBase<char8> g(a, 0);
  }
};
