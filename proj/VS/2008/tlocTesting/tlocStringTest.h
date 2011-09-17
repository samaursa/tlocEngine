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

    {// char append
      b.append(100, 'a');

      for (u32 i = 0; i < 100; ++i)
      {
        CHECK(b[i] == 'a');
      }

      b.push_back('b');

      CHECK(b[100] == 'b');
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

  TEST_CASE_METHOD(StringFixture, "Core/Strings/Erase", "")
  {
    const char8* testString = "This is a test string.";
    StringBase<char8> d(testString);
    d.erase(d.end() - 1);

    CHECK(StrCmp(d.c_str(), "This is a test string") == 0);

    d.erase(10, 5);

    CHECK(StrCmp(d.c_str(), "This is a string") == 0);

    d.erase(d.begin(), d.begin() + 5);

    CHECK(StrCmp(d.c_str(), "is a string") == 0);

    d.erase();

    CHECK(d.length() == 0);
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/Assign", "")
  {
    const char8* testString = "This is a test string.";
    a.assign(testString, testString + 14);

    CHECK(StrCmp(a.c_str(), "This is a test") == 0);

    a.assign(testString, testString + 7);

    CHECK(StrCmp(a.c_str(), "This is") == 0);

    a.assign(testString, testString + StrLen(testString));

    CHECK(StrCmp(a.c_str(), testString) == 0);

    a.assign(10, '!');

    CHECK(StrCmp(a.c_str(), "!!!!!!!!!!") == 0);

    b.assign(a);

    CHECK(StrCmp(b.c_str(), "!!!!!!!!!!") == 0);

    c.assign("Testing String assign()");

    CHECK(StrCmp(c.c_str(), "Testing String assign()") == 0 );

    b.assign(c, 8, c.size());

    CHECK(StrCmp(b.c_str(), "String assign()") == 0);

    b.assign("Can be very useful. Assign().", 19);

    CHECK(StrCmp(b.c_str(), "Can be very useful.") == 0);

    b = a;

    CHECK(StrCmp(b.c_str(), "!!!!!!!!!!") == 0);

    b = "This is a test string.";

    CHECK(StrCmp(b.c_str(), "This is a test string.") == 0);

    b = 'a';

    CHECK(StrCmp(b.c_str(), "a") == 0);
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/Insert", "")
  {
    {
      const char* testString = "This is a very very very very very very very very "
        "very very very very very very very very very very very very very very very "
        "very very very very very very very very long test";

      a = "string";

      b = testString;
      b.append(a);

      a.insert(a.begin(), testString, testString + StrLen(testString));

      CHECK(a.capacity() == StrLen(testString) + StrLen("string") );
      CHECK(StrCmp(a.c_str(), b.c_str()) == 0);

      c = "Testing insert character:  (10 a chars)";

      c.insert(c.begin() + 26, 10, 'a');

      CHECK(StrCmp(c.c_str(), "Testing insert character: aaaaaaaaaa (10 a chars)") == 0);

      a = testString;
      b = testString;
      b += c;

      c.insert(0, a, 0, a.length());

      CHECK(StrCmp(c.c_str(), b.c_str()) == 0);

      b = "indestructible";
      c = "This fragile glass will never break.";

      c.erase(c.begin() + 5, c.begin() + 12);
      c.insert(5, b);

      CHECK(StrCmp(c.c_str(), "This indestructible glass will never break.") == 0);
    }

    {// tests from cplusplus.com
      a = "to be question";
      b = "the ";
      c = "or not to be";
      StringBase<char8>::iterator it;

      // used in the same order as described above:
      a.insert(6,b);                 // to be (the )question
      CHECK(StrCmp(a.c_str(), "to be the question") == 0);
      a.insert(6,c,3,4);             // to be (not )the question
      CHECK(StrCmp(a.c_str(), "to be not the question") == 0);
      a.insert(10,"that is cool",8);    // to be not (that is )the question
      CHECK(StrCmp(a.c_str(), "to be not that is the question") == 0);
      a.insert(10,"to be ");            // to be not (to be )that is the question
      CHECK(StrCmp(a.c_str(), "to be not to be that is the question") == 0);
      a.insert(15,1,':');               // to be not to be(:) that is the question
      CHECK(StrCmp(a.c_str(), "to be not to be: that is the question") == 0);
      it = a.insert(a.begin()+5,','); // to be(,) not to be: that is the question
      CHECK(StrCmp(a.c_str(), "to be, not to be: that is the question") == 0);
      a.insert (a.end(),3,'.');       // to be, not to be: that is the question(...)
      CHECK(StrCmp(a.c_str(), "to be, not to be: that is the question...") == 0);
      a.insert (it+2,c.begin(),c.begin()+3); // (or )
      CHECK(StrCmp(a.c_str(), "to be, or not to be: that is the question...") == 0);
    }
  }
};
