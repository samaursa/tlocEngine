namespace TestingStrings
{
  struct StringFixture
  {
    StringBase<char8> a, b, c;
  };

  TEST_CASE("Core/Strings/StrLen", "Test StrLen()")
  {
    const char8* someStr = "01234567890123456789"; // 20 chars long
    tl_size strSize = StrLen(someStr);
    CHECK(strSize == 20);
  }

  TEST_CASE("Core/Strings/StrCmp", "Test StrCmp()")
  {
    const char8* someStr = "This is a test string.";
    const char8* someOtherStr = "This is a test string.";
    const char8* someDiffString = "This is a test string. Hmm.";
    const char8* someDiffString2 = "This is a test string";

    CHECK(StrCmp(someStr, someOtherStr) == 0);
    CHECK(StrCmp(someStr, someDiffString) == -1);
    CHECK(StrCmp(someStr, someDiffString2) == 1);

  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/Construction",
    "Test basic string construction")
  {
    StringBase<char8> d(a, 0);

    const char* text = "Hello";
    StringBase<char8> e(text, 5);

    for (u32 i = 0; i < 5; ++i)
    {
      CHECK(e[i] == *(text + i));
    }
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/Append",
    "Test the append() functions")
  {
    {// range append
      const char8* someString = "This is a test";
      a.append(someString, someString + StrLen(someString));

      CHECK(StrCmp(someString, a.c_str()) == 0);
    }
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/Operator+=", "")
  {
    a += "This is a test.";
    CHECK(StrCmp(a.c_str(), "This is a test.") == 0);

    b += "Second test.";
    CHECK(StrCmp(b.c_str(), "Second test.") == 0);

    a += b;
    CHECK(StrCmp(a.c_str(), "This is a test.Second test.") == 0);
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/Capacity", "")
  {
    StringBase<char8> d("This is interesting.");

    d.set_capacity(7);
    CHECK(StrCmp(d.c_str(), "This is") == 0);
    CHECK(d.size() == 7);
    CHECK(d.capacity() == 7);

    d.clear();
    CHECK(StrCmp(d.c_str(), "") == 0);

    d.append("This is interesting.");
    d.set_capacity(50);
    CHECK(d.capacity() == 50);
  }
};
