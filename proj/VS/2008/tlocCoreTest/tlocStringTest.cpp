#include "tlocTestCommon.h"

#include <tlocCore/memory/tlocLinkMe.cpp>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/string/tlocString.inl>

namespace TestingStrings
{
  USING_TLOC;
  using namespace core;

  struct StringFixture
  {
    String a, b, c;
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
    String d(a, 0);

    const char* text = "Hello";
    String e(text, 5);

    for (u32 i = 0; i < 5; ++i)
    {
      CHECK(e[i] == *(text + i));
    }

    {
      String f(e);
      CHECK(StrCmp(f.c_str(), "Hello") == 0);
    }

    {
      String f(e, 3);
      CHECK(StrCmp(f.c_str(), "lo") == 0);
    }

    {
      String f("Hello world!", 5);
      CHECK(StrCmp(f.c_str(), "Hello") == 0);
    }

    {
      String f("Hello world!");
      CHECK(StrCmp(f.c_str(), "Hello world!") == 0);
    }

    {
      String f(10, 'a');
      CHECK(StrCmp(f.c_str(), "aaaaaaaaaa") == 0);
    }

    {
      String f(StringNoInitialize(), 10);
      CHECK(f.capacity() == 10);
    }

    {// tests from cplusplus.com
      String s0 ("Initial string");
      CHECK(StrCmp(s0.c_str(), "Initial string") == 0);

      // constructors used in the same order as described above:
      String s1;
      String s2 (s0);
      CHECK(StrCmp(s2.c_str(), "Initial string") == 0);
      String s3 (s0, 8, 3);
      CHECK(StrCmp(s3.c_str(), "str") == 0);
      String s4 ("A character sequence", 6);
      CHECK(StrCmp(s4.c_str(), "A char") == 0);
      String s5 ("Another character sequence");
      CHECK(StrCmp(s5.c_str(), "Another character sequence") == 0);
      String s6 (10, 'x');
      CHECK(StrCmp(s6.c_str(), "xxxxxxxxxx") == 0);
      String s7a (10, (char8)42);
      CHECK(StrCmp(s7a.c_str(), "**********") == 0);
      /*tlString s7b (s0.begin(), s0.begin()+7);
      CHECK(StrCmp(s7b.c_str(), "Initial") == 0);*/
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

    {// tests from cplusplus.com
      String str;
      String str2="Writing ";
      String str3="print 10 and then 5 more";

      // used in the same order as described above:
      str.append(str2);                       // "Writing "
      CHECK(StrCmp(str.c_str(), "Writing ") == 0);
      str.append(str3,6,3);                   // "10 "
      CHECK(StrCmp(str.c_str(), "Writing 10 ") == 0);
      str.append("dots are cool",5);          // "dots "
      CHECK(StrCmp(str.c_str(), "Writing 10 dots ") == 0);
      str.append("here: ");                   // "here: "
      CHECK(StrCmp(str.c_str(), "Writing 10 dots here: ") == 0);
      str.append(10,'.');                     // ".........."
      CHECK(StrCmp(str.c_str(), "Writing 10 dots here: ..........") == 0);
      str.append(str3.begin()+8,str3.end());  // " and then 5 more"
      CHECK(StrCmp(str.c_str(), "Writing 10 dots here: .......... and then 5 more") == 0);
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
    String d("This is interesting.");

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
    String d(testString);
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

    {// tests from cplusplus.com
      String str;
      String base="The quick brown fox jumps over a lazy dog.";

      // used in the same order as described above:

      str.assign(base);

      str.assign(base,10,9);
      CHECK(StrCmp(str.c_str(), "brown fox") == 0);

      str.assign("pangrams are cool",7);
      CHECK(StrCmp(str.c_str(), "pangram") == 0);

      str.assign("c-string");
      CHECK(StrCmp(str.c_str(), "c-string") == 0);

      str.assign(10,'*');
      CHECK(StrCmp(str.c_str(), "**********") == 0);

      str.assign(base.begin()+16,base.end()-12);
      CHECK(StrCmp(str.c_str(), "fox jumps over") == 0);
    }
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

      a = "This is interesting.";
      c.insert(c.end(), a.begin(), a.end());

      CHECK(StrCmp(c.c_str(), "This indestructible glass will never break."
        "This is interesting.") == 0);

      a = c;
      a.insert((tl_size)0, 10, 'T');
      c.insert((tl_size)0, 10, c[0]); // Checks whether we are not messing up the pointers
      CHECK(StrCmp(a.c_str(), c.c_str()) == 0);
    }

    {// tests from cplusplus.com
      a = "to be question";
      b = "the ";
      c = "or not to be";
      String::iterator it;

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

  TEST_CASE_METHOD(StringFixture, "Core/Strings/Replace", "")
  {
    {
      a = "This is a string.";
      b = "test";

      a.replace(a.begin() + 10, a.begin() + 16, b.begin(), b.end());
      CHECK(StrCmp(a.c_str(), "This is a test.") == 0);

      a.replace(a.end() - 1, a.end(), 3, '!');
      CHECK(StrCmp(a.c_str(), "This is a test!!!") == 0);
    }

    {//tests from cplusplus.com
      String base = "this is a test string.";
      String str2 = "n example";
      String str3 = "sample phrase";
      String str4 = "useful.";

      // function versions used in the same order as described above:

      // Using positions:                 0123456789*123456789*12345
      String str=base;                // "this is a test string."
      CHECK(StrCmp(str.c_str(), "this is a test string.") == 0);
      str.replace(9,5,str2);          // "this is an example string."
      CHECK(StrCmp(str.c_str(), "this is an example string.") == 0);
      str.replace(19,6,str3,7,6);     // "this is an example phrase."
      CHECK(StrCmp(str.c_str(), "this is an example phrase.") == 0);
      str.replace(8,10,"just all",6); // "this is just a phrase."
      CHECK(StrCmp(str.c_str(), "this is just a phrase.") == 0);
      str.replace(8,6,"a short");     // "this is a short phrase."
      CHECK(StrCmp(str.c_str(), "this is a short phrase.") == 0);
      str.replace(22,1,3,'!');        // "this is a short phrase!!!"
      CHECK(StrCmp(str.c_str(), "this is a short phrase!!!") == 0);

      // Using iterators:                      0123456789*123456789*
      String::iterator it = str.begin();   //  ^
      str.replace(it,str.end()-3,str3);    // "sample phrase!!!"
      CHECK(StrCmp(str.c_str(), "sample phrase!!!") == 0);
      str.replace(it,it+6,"replace it",7); // "replace phrase!!!"
      CHECK(StrCmp(str.c_str(), "replace phrase!!!") == 0);
      it+=8;                               //          ^
      str.replace(it,it+6,"is cool");      // "replace is cool!!!"
      CHECK(StrCmp(str.c_str(), "replace is cool!!!") == 0);
      str.replace(it+4,str.end()-4,4,'o'); // "replace is cooool!!!"
      CHECK(StrCmp(str.c_str(), "replace is cooool!!!") == 0);
      it+=3;                               //             ^
      str.replace(it,str.end(),str4.begin(),str4.end()); // "replace is useful."
      CHECK(StrCmp(str.c_str(), "replace is useful.") == 0);
    }
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/Copy", "")
  {
    tl_size length;
    char8 buffer[20];
    String str ("Test string...");
    REQUIRE(StrCmp(str.c_str(), "Test string...") == 0);

    length = str.copy(buffer,6,5);
    buffer[length] = '\0';

    CHECK(StrCmp(buffer, "string") == 0);
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/Find", "")
  {
    String str ("There are two needles in this haystack with needles.");
    String str2 ("needle");
    tl_size found;

    // different member versions of find in the same order as above:
    found = str.find(str2);
    CHECK(found == 14);

    found = str.find("needles are small",found+1,6);
    CHECK(found == 44);

    found = str.find("haystack");
    CHECK(found == 30);

    found = str.find('.');
    CHECK(found == 51);

    // let's replace the first needle:
    str.replace(str.find(str2),str2.length(),"preposition");

    CHECK(StrCmp(str.c_str(), "There are two prepositions in this haystack "
          "with needles.") == 0);

    found = str.find("Pixar");
    CHECK(found == String::npos);
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/rFind", "")
  {
    String str ("The sixth sick sheik's sixth sheep's sick.");
    String key ("sixth");
    tl_size found;

    found = str.rfind(key);
    REQUIRE(found != String::npos);

    str.replace (found,key.length(),"seventh");
    CHECK(StrCmp(str.c_str(), "The sixth sick sheik's seventh sheep's sick.") == 0);

    found = str.rfind("sick.");
    CHECK(StrCmp(str.begin() + found, "sick.") == 0);

    found = str.rfind("'");
    CHECK(*(str.begin() + found) == '\'');

    found = str.rfind('.');
    CHECK(*(str.begin() + found) == '.');
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/FindFirstOf", "")
  {
    String str ("Replace the vowels in this sentence by asterisks.");
    tl_size found;

    found = str.find_first_of("aeiou");
    while (found!=String::npos)
    {
      str[found]='*';
      found=str.find_first_of("aeiou",found+1);
    }

    CHECK(StrCmp(str.c_str(), "R*pl*c* th* v*w*ls *n th*s s*nt*nc* by *st*r*sks.") == 0);

    found = str.find_first_of('c');
    CHECK(found == 5);
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/FindFirstNotOf", "")
  {
    String str ("look for non-alphabetic characters...");
    tl_size found;

    found = str.find_first_not_of("abcdefghijklmnopqrstuvwxyz ");
    if (found!=String::npos)
    {
      CHECK(str[found] == '-');
      CHECK(found == (tl_size)12);
    }
    else
    {
      CHECK(StrCmp("FindFirstOf test failed", "Check above") == 0);
    }
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/FindLastNotOf", "")
  {
    String str ("erase trailing white-spaces   \n");
    String whitespaces (" \t\f\v\n\r");
    tl_size found;

    found = str.find_last_not_of(whitespaces);
    if (found != String::npos)
    {
      str.erase(found+1);
      CHECK(StrCmp(str.c_str(), "erase trailing white-spaces") == 0);
    }
    else
    {
      CHECK(StrCmp("FindLastNotOf test failed", "Check above") == 0);
    }
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/substr", "")
  {
    String str="We think in generalities, but we live in details.";
    // quoting Alfred N. Whitehead
    String str2, str3;

    str2 = str.substr (12,12); // "generalities"
    CHECK(StrCmp(str2.c_str(), "generalities") == 0);

    // TODO: Test when find() is complete
    tl_size pos;
    pos = str.find("live");    // position of "live" in str
    str3 = str.substr (pos);   // get from "live" to the end

    CHECK(StrCmp(str3.c_str(), "live in details.") == 0);
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/compare", "")
  {
    String str1 ("green apple");
    String str2 ("red apple");

    CHECK(str1.compare(str2) != 0);
    CHECK(str1.compare(6, 5, "apple") == 0);
    CHECK(str2.compare(str2.size() - 5, 5, "apple") == 0);
    CHECK(str1.compare(6, 5, str2, 4, 5) == 0);
    CHECK(str2.compare(0, 3, "red") == 0);
    CHECK(str2.compare("green apple") != 0);

    // Empty string test
    str2.clear();
    CHECK(str2.compare("green apple") != 0);
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/UpperLower", "")
  {
    const char8* testString      = "This Is A Test STRING";
    const char8* testStringUpper = "THIS IS A TEST STRING";
    const char8* testStringLower = "this is a test string";

    String str(testString);
    String str2;

    str.make_lower();
    CHECK(StrCmp(str.c_str(), testStringLower) == 0);

    str = testString;
    str.make_upper();
    CHECK(StrCmp(str.c_str(), testStringUpper) == 0);

    str = testString;
    str.to_upper(str2);
    CHECK(StrCmp(str2.c_str(), testStringUpper) == 0);

    str.to_lower(str2);
    CHECK(StrCmp(str2.c_str(), testStringLower) == 0);

    str2 = str.to_upper();
    CHECK(StrCmp(str2.c_str(), testStringUpper) == 0);

    str2 = str.to_lower();
    CHECK(StrCmp(str2.c_str(), testStringLower) == 0);

  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/FreeFunctions/UpperLower", "")
  {
    CHECK(CharToUpper('a') == 'A');
    CHECK(CharToUpper(L'a') == L'A');
    CHECK(CharToUpper('A') == 'A');

    CHECK(CharToLower('A') == 'a');
    CHECK(CharToLower(L'A') == L'a');
    CHECK(CharToLower('a') == 'a');
  }

  TEST_CASE_METHOD(StringFixture, "Core/Strings/FreeFunctions/Operators", "")
  {
    String str("This is a test");
    String str2 = str;

    CHECK( (str == str2) == true);
    str += "a";
    CHECK( (str != str2) == true);
    str.erase(str.end() - 1, str.end());
    CHECK( (str == str2) == true);

    const char* testStr = "This is another test";
    const char* testStr3 = "This is another test.";

    str = testStr;
    str2 = testStr3;

    CHECK( (str == testStr) == true);
    CHECK( (testStr == str) == true);
    CHECK( (str2 != testStr) == true);
    CHECK( (testStr != str2) == true);

    str2 = str2 + " Test 1...2...3...";
    CHECK(str2.compare("This is another test. Test 1...2...3...") == 0);

    str2 = "==> " + str;
    CHECK(str2.compare("==> This is another test") == 0);

    str2 = '>' + str;
    CHECK(str2.compare(">This is another test") == 0);

    str2 = str + '.';
    CHECK(str2.compare("This is another test.") == 0);

  }

  TEST_CASE("Core/Strings/FreeFunctions/AsciiWideConversion", "")
  {
    char32 sentence1[] = L"This is a sentence.";
    char8  sentence2[] = "This is a sentence.";

    {
      char8 s1[256];
      tl_int retIndex = CharWideToAscii(s1, sentence1, 256);
      CHECK(StrCmp(sentence2, s1) == 0);
      CHECK(retIndex == 19);
    }

    {
      char32 s2[256];
      tl_int retIndex = CharAsciiToWide(s2, sentence2, 256);
      CHECK(StrCmp(sentence1, s2) == 0);
      CHECK(retIndex == 19);
    }
  }
};
