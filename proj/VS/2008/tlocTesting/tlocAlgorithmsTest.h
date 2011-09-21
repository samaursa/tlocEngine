#include <algorithm>

namespace TestingAlgorithms
{
  struct AlgorithmFixture
  {

  };

  TEST_CASE("Core/Algorithms/Swap", "Test the min() functions")
  {
    u32 i = 10, j = 15;
    u32 minimum = tlMin(i, j);
    CHECK(minimum == i);
  }

  TEST_CASE("Core/Algorithms/Swap", "Test the swap() functions")
  {
    u32 i = 10, j = 15;
    tlSwap(i, j);
    CHECK(i == 15);
    CHECK(j == 10);
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Copy",
    "Test the copy() functions")
  {
    { // tlCopy arithmetic types
      const char8* testString = "This is a test string"; // 21 chars including /0
      const char8* stringEnd = testString + 22; // copy does not include stringEnd
      char8* copiedString = new char8[stringEnd - testString];

      tlCopy(testString, stringEnd, copiedString);

      for (u32 i = 0; i < (u32)(stringEnd - testString); ++i)
      {
        CHECK(copiedString[i] == testString[i]);
      }
    }

    { // tlCopy complex types
      typedef struct copyTest
      {
        int a;
        int b;
      }copyTest;

      copyTest testStruct = {1, 5};
      copyTest arrayStructs[5];
      copyTest copiedStructs[5];

      for (u32 i = 0; i < 5; ++i)
      {
        arrayStructs[i] = testStruct;
      }

      tlCopy(arrayStructs, arrayStructs + 5, copiedStructs);

      for (u32 i = 0; i < 5; ++i)
      {
        CHECK(copiedStructs[i].a == testStruct.a);
        CHECK(copiedStructs[i].b == testStruct.b);
      }
    }

    {// tlCopyBackward
      char8 testString[] = "0123456789"; // 10 chars including /0

      tlCopy_Backward(testString, testString + 6, testString + 10);

      CHECK( testString[0] == '0');
      CHECK( testString[1] == '1');
      CHECK( testString[2] == '2');
      CHECK( testString[3] == '3');
      CHECK( testString[4] == '0');
      CHECK( testString[5] == '1');
      CHECK( testString[6] == '2');
      CHECK( testString[7] == '3');
      CHECK( testString[8] == '4');
      CHECK( testString[9] == '5');
    }
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Fill",
    "Test the fill() functions")
  {
    { // tlFill char (tlFill has specialization for tlFill<char>() )
      char8 testArray[100] = {0};

      tlFill(testArray, testArray + 100, 'T');

      for (u32 i = 0; i < 100; ++i)
      {
        CHECK(testArray[i] == 'T');
      }
    }

    { // tlFill other types
      u64 testArray[100] = {0};

      tlFill(testArray, testArray + 100, 50);

      for (u32 i = 0; i < 100; ++i)
      {
        CHECK(testArray[i] == 50);
      }
    }
  }

  void ForEachFunc(u32*& element)
  {
    *element = ++(*element);
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/ForEach", "")
  {
    const tl_size arraySize = 5;
    u32* intArray[arraySize];

    for (u32 i = 0; i < arraySize; ++i)
    {
      intArray[i] = new u32(i);
    }

    tlForEach(intArray, intArray + arraySize, ForEachFunc);

    for (u32 i = 0; i < arraySize; ++i)
    {
      CHECK( *(intArray[i]) == i + 1);
    }
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Find", "")
  {
    u32 myints[] = { 10, 20, 30 ,40 };
    u32 * p;

    // pointer to array element:
    p = tlFind(myints,myints+4, (u32)30);
    ++p;

    CHECK(*p == 40);

    Array<u32> myvector (myints,myints+4);
    Array<u32>::iterator it;

    //iterator to vector element:
    it = tlFind (myvector.begin(), myvector.end(), (u32)30);
    ++it;

    CHECK(*it == 40);
  }

  bool IsOdd (s32 i)
  {
    return ((i%2)==1);
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/FindIf", "")
  {
    Array<s32> myvector;
    Array<s32>::iterator it;

    myvector.push_back(10);
    myvector.push_back(25);
    myvector.push_back(40);
    myvector.push_back(55);

    it = tlFindIf(myvector.begin(), myvector.end(), IsOdd);
    CHECK(*it == 25);
  }

  bool myfunction (s32 i, s32 j)
  {
    return (i==j);
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/FindEnd", "")
  {
    s32 myints[] = {1,2,3,4,5,1,2,3,4,5};
    Array<s32> myvector (myints,myints+10);
    Array<s32>::iterator it;

    s32 match1[] = {1,2,3};

    // using default comparison:
    it = tlFindEnd (myvector.begin(), myvector.end(), match1, match1+3);

    CHECK( (s32)(it - myvector.begin()) == 5); // pos

    s32 match2[] = {4,5,1};

    // using predicate comparison:
    it = tlFindEnd (myvector.begin(), myvector.end(), match2, match2+3, myfunction);

    CHECK( (s32)(it - myvector.begin()) == 3); // pos
  }

  bool comp_case_insensitive (char8 c1, char8 c2)
  {
    return (tolower(c1)==tolower(c2));
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/FindFirstOf", "")
  {
    char8 mychars[] = {'a','b','c','A','B','C'};
    Array<char8> myvector (mychars,mychars+6);
    Array<char8>::iterator it;

    char8 match[] = {'A','B','C'};

    // using default comparison:
    it = tlFindFirstOf (myvector.begin(), myvector.end(), match, match+3);

    CHECK(*it == 'A');

    // using predicate comparison:
    it = tlFindFirstOf (myvector.begin(), myvector.end(),
      match, match+3, comp_case_insensitive);

    CHECK(*it == 'a');
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Count", "Count and CountIf")
  {
    {//tlCount
      s32 mycount;

      // counting elements in array:
      s32 myints[] = {10,20,30,30,20,10,10,20};   // 8 elements
      mycount = (s32) tlCount (myints, myints+8, 10);
      CHECK(mycount == 3);

      // counting elements in container:
      Array<s32> myvector (myints, myints+8);
      mycount = (s32) tlCount (myvector.begin(), myvector.end(), 20);
      CHECK(mycount == 3);
    }

    {//tlCountIf
      s32 mycount;

      Array<s32> myvector;
      for (s32 i=1; i<10; i++) myvector.push_back(i); // myvector: 1 2 3 4 5 6 7 8 9

      mycount = (s32) tlCountIf (myvector.begin(), myvector.end(), IsOdd);
      CHECK(mycount == 5);
    }
  }

  bool mypredicate (s32 i, s32 j)
  {
    return (i==j);
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Mismatch", "")
  {
    Array<s32> myvector;
    for (s32 i=1; i<6; i++) myvector.push_back (i*10); // myvector: 10 20 30 40 50

    s32 myints[] = {10,20,80,320,1024};                //   myints: 10 20 80 320 1024

    Pair<Array<s32>::iterator,s32*> mypair;

    // using default comparison:
    mypair = tlMismatch (myvector.begin(), myvector.end(), myints);

    CHECK(*mypair.first == 30);
    CHECK(*mypair.second == 80);

    mypair.first++; mypair.second++;

    // using predicate comparison:
    mypair = tlMismatch (mypair.first, myvector.end(), mypair.second, mypredicate);

    CHECK(*mypair.first == 40);
    CHECK(*mypair.second == 320);
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Equal", "")
  {
    bool retValue = false;
    s32 myints[] = {20,40,60,80,100};          //   myints: 20 40 60 80 100
    Array<s32>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

    retValue = tlEqual(myvector.begin(), myvector.end(), myints);
    CHECK(retValue == true);

    myvector[3]=81;

    retValue = tlEqual(myvector.begin(), myvector.end(), myints, mypredicate);
    CHECK(retValue == false);
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Search", "")
  {
    Array<s32> myvector;
    Array<s32>::iterator it;

    // set some values:        myvector: 10 20 30 40 50 60 70 80 90
    for (s32 i=1; i<10; i++) myvector.push_back(i*10);


    // using default comparison:
    s32 match1[] = {40,50,60,70};
    it = tlSearch (myvector.begin(), myvector.end(), match1, match1+4);

    CHECK((s32)(it - myvector.begin()) == 3);

    // using predicate comparison:
    s32 match2[] = {20,30,50};
    it = tlSearch (myvector.begin(), myvector.end(), match2, match2+3, mypredicate);

    CHECK(it == myvector.end());
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/SearchN", "")
  {
    s32 myints[]={10,20,30,30,20,10,10,20};
    Array<s32> myvector (myints,myints+8);

    Array<s32>::iterator it;

    // using default comparison:
    it = tlSearchN (myvector.begin(), myvector.end(), 2, 30);

    CHECK(s32(it-myvector.begin()) == 2);

    // using predicate comparison:
    it = tlSearchN (myvector.begin(), myvector.end(), 2, 10, mypredicate);

    CHECK(s32(it-myvector.begin()) == 5);
  }
};
