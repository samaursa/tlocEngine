// ignore behavior change warning
#pragma warning(disable:4345)

#include "tlocTestCommon.h"

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/string/tlocString.h>

namespace TestingAlgorithms
{
  USING_TLOC;
  using namespace core;

  struct AlgorithmFixture
  {
    AlgorithmFixture() {}

    static const int  testString[];
    static const int* testStringEnd;
    static const int  testNumString[];
    static const int* testNumStringEnd;

    struct simpleStruct
    {
      int a;
      int b;
    };
  };

  const int AlgorithmFixture::testString[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
  const int* AlgorithmFixture::testStringEnd = testString + 22;
  const int AlgorithmFixture::testNumString[] = {1,2,3,4,5,6,7,8,9,0};
  const int* AlgorithmFixture::testNumStringEnd = testNumString + 10;

  const tl_size g_testArraySize = 100; // array size used for loops etc.

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

  TEST_CASE("Core/Algorithms/Fill", "Test the fill() functions")
  {
    { // fill char (fill has specialization for fill<char>() )
      int testArray[g_testArraySize] = {0};

      fill(testArray, testArray + g_testArraySize, 'T');

      for (u32 i = 0; i < g_testArraySize; ++i)
      {
        CHECK(testArray[i] == 'T');
      }
    }

    { // fill other types
      u64 testArray[g_testArraySize] = {0};

      fill(testArray, testArray + g_testArraySize, 50);

      for (u32 i = 0; i < g_testArraySize; ++i)
      {
        CHECK(testArray[i] == 50);
      }
    }

    {// fill using an iterator for an Array<tl_int>
      Array<tl_int> testArray(100, 10);

      fill(testArray.begin(), testArray.end(), 12);

      for (tl_size i = 0; i < 100; ++i)
      {
        CHECK(testArray[i] == 12);
      }
    }

    {// fill filling up a portion of the array
      tl_int testArray[100] = {0};

      fill(testArray, testArray + 50, 6);
      fill(testArray + 50, testArray + 100, 5);

      for (tl_size i = 0; i < 50; ++i)
      {
        CHECK(testArray[i] == 6);
      }

      for (tl_size i = 50; i < 100; ++i)
      {
        CHECK(testArray[i] == 5);
      }
    }
  }

  TEST_CASE("Core/Algorithms/FillN", "Test the fill_n() functions")
  {
    {// fill_n with char (fill has specialization for fill<char>() )
      char8 testArray[100] = {0};

      fill_n(testArray, 100, 'U');

      for (tl_size i = 0; i < 100; ++i)
      {
        CHECK(testArray[i] == 'U');
      }
    }

    {// fill_n with another POD type
      tl_int testArray[100] = {0};

      fill_n(testArray, 100, 73);

      for (tl_size i = 0; i < 100; ++i)
      {
        CHECK(testArray[i] == 73);
      }
    }

    {// fill_n using an iterator for an Array<tl_uint>
      Array<tl_uint> testArray(100, 0);

      fill_n(testArray.begin(), 100, 8);

      for (tl_size i = 0; i < 100; ++i)
      {
        CHECK(testArray[i] == 8);
      }
    }

    {// fill_n using an iterator from a List<tl_int>
      List<tl_int> testList(100, 0);

      fill_n(testList.begin(), 100, 65);

      List<tl_int>::iterator itr = testList.begin();
      List<tl_int>::const_iterator itrEnd = testList.end();

      for (/* */; itr != itrEnd; ++itr)
      {
        CHECK(*itr == 65);
      }
    }

    {// fill_n filling up a portion of the array
      tl_int testArray[100] = {0};

      fill_n(testArray, 50, 22);
      fill_n(testArray + 50, 50, 14);

      for (tl_size i = 0; i < 50; ++i)
      {
        CHECK(testArray[i] == 22);
      }

      for (tl_size i = 50; i < 100; ++i)
      {
        CHECK(testArray[i] == 14);
      }
    }
  }

  template <typename T_Itr>
  void TestCopyArithmetic(T_Itr a_itr)
  {
    const int* testString = AlgorithmFixture::testString;
    const int* testStringEnd = AlgorithmFixture::testStringEnd;

    T_Itr itrBegin = a_itr;
    copy(testString, testStringEnd, a_itr);

    bool hasFailed = false;
    for (u32 i = 0; i < (u32)(testStringEnd - testString); ++i)
    {
      if ( *(itrBegin++) == testString[i] == false)
      {
        hasFailed = true; break;
      }
    }
    CHECK(hasFailed == false);
  }

  template <typename T_Itr>
  void TestCopyComplexTypes(T_Itr a_itr)
  {
    AlgorithmFixture::simpleStruct arrayStructs[g_testArraySize];

    for (u32 i = 0; i < g_testArraySize; ++i)
    {
      arrayStructs[i].a = i;
      arrayStructs[i].b = (i + 1) * 5;
    }

    T_Itr itrBegin = a_itr;

    copy(arrayStructs, arrayStructs + g_testArraySize, a_itr);

    bool hasFailed = false;
    for (u32 i = 0; i < g_testArraySize; ++i)
    {
      if ( (*itrBegin).a != arrayStructs[i].a)
      {
        hasFailed = true; break;
      }
      if ( (*itrBegin).b != arrayStructs[i].b)
      {
        hasFailed = true; break;
      }
      ++itrBegin;
    }
    CHECK(hasFailed == false);
  }

  template <typename T_Itr>
  void TestCopyBackward(T_Itr a_itr)
  {
    const int* testNumString		= AlgorithmFixture::testNumString;
    const int* testNumStringEnd	= AlgorithmFixture::testNumStringEnd;

    T_Itr itrCopy = a_itr;
    T_Itr itrEnd = copy(testNumString, testNumStringEnd, itrCopy);

    copy_backward(testNumString, testNumStringEnd, itrEnd);

    bool hasFailed = false;
    for (u32 i = 0; i < 10; ++i)
    {
      if ((*a_itr) != testNumString[i])
      {
        hasFailed = true;
      }
      ++a_itr;
    }
    CHECK(hasFailed == false);
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Copy",
    "Test the copy() functions")
  {
    { // copy arithmetic types
      int* copiedString = new int[testStringEnd - testString];

      Array<int> copiedStringArray;
      copiedStringArray.resize(testStringEnd - testString);

      List<int> copiedStringList;
      copiedStringList.resize(testStringEnd - testString);

      TestCopyArithmetic(copiedString);
      TestCopyArithmetic(copiedStringArray.begin());
      TestCopyArithmetic(copiedStringArray.begin());
    }

    { // copy complex types
      simpleStruct copiedStructs[g_testArraySize];
      Array<simpleStruct> copiedArray; copiedArray.resize(g_testArraySize);
      List<simpleStruct> copiedList; copiedList.resize(g_testArraySize);

      TestCopyComplexTypes(copiedStructs);
      TestCopyComplexTypes(copiedArray.begin());
      TestCopyComplexTypes(copiedList.begin());
    }

    {
      const int arraySize = 10;
      int copiedString[arraySize];
      Array<s32> copiedArray; copiedArray.resize(arraySize);
      List<s32> copiedList; copiedList.resize(arraySize);

      TestCopyBackward(copiedString);
      TestCopyBackward(copiedArray.begin());
      TestCopyBackward(copiedList.begin());
    }
  }

  void ForEachFunc(u32*& element)
  {
    *element = ++(*element);
  }

  template <typename T_Itr>
  void TestForEach(T_Itr a_itr)
  {
    T_Itr itrEnd = a_itr;
    advance(itrEnd, g_testArraySize);
    for_each(a_itr, itrEnd, ForEachFunc);

    bool hasFailed = false;
    for (u32 i = 0; i < g_testArraySize; ++i)
    {
      if( **a_itr != i + 1)
      {
        hasFailed = true;
      }
      ++a_itr;
    }
    CHECK(hasFailed == false);
  }

  TEST_CASE("Core/Algorithms/ForEach", "")
  {
    u32* intArray[g_testArraySize];
    Array<u32*> intDynArray;
    List<u32*> intList;

    for (u32 i = 0; i < g_testArraySize; ++i)
    {
      intArray[i] = new u32(i); //-V508
      intDynArray.push_back(new u32(i)); //-V508
      intList.push_back(new u32(i)); //-V508
    }

    TestForEach(intArray);
    TestForEach(intDynArray.begin());
    TestForEach(intList.begin());

    for_each_all(intDynArray, ForEachFunc);
    for_each_all(intList, ForEachFunc);
  }

  template <typename T_Itr>
  void TestFind(T_Itr a_itr)
  {
    T_Itr itrCopy = a_itr;

    for (u32 i = 0; i < g_testArraySize; ++i)
    {
      *(itrCopy++) = i;
    }

    T_Itr itrEnd = a_itr;
    advance(itrEnd, g_testArraySize);

    T_Itr itrFind = find(a_itr, itrEnd, g_testArraySize / 2);
    T_Itr itrFindP = itrFind;
    advance(itrFindP, 1);

    CHECK(*itrFind == (*itrFindP) - 1);
    CHECK(*itrFind == (g_testArraySize / 2));
  }

  TEST_CASE("Core/Algorithms/Find", "")
  {
    u32 myInts[g_testArraySize];
    Array<u32> intArray; intArray.resize(g_testArraySize);
    List<u32> intList; intList.resize(g_testArraySize);
    TestFind(myInts);
    TestFind(intArray.begin());
    TestFind(intList.begin());

    find_all(intArray, 0u);
    find_all(intList, 0u);
  }

  bool IsOdd (s32 i)
  {
    return ((i%2)==1);
  }

  TEST_CASE("Core/Algorithms/FindIf", "")
  {
    core::List<s32> myvector;
    core::List<s32>::iterator it;

    myvector.push_back(10);
    myvector.push_back(25);
    myvector.push_back(40);
    myvector.push_back(55);

    it = find_if(myvector.begin(), myvector.end(), IsOdd);
    CHECK(*it == 25);
  }

  bool myfunction (s32 i, s32 j)
  {
    return (i==j);
  }

  TEST_CASE("Core/Algorithms/FindEnd", "")
  {
    s32 myints[] = {1,2,3,4,5,1,2,3,4,5};
    core::Array<s32> myvector (myints,myints+10);
    core::Array<s32>::iterator it;

    s32 match1[] = {1,2,3};

    // using default comparison:
    it = find_end (myvector.begin(), myvector.end(), match1, match1+3);

    CHECK( (s32)(it - myvector.begin()) == 5); // pos

    s32 match2[] = {4,5,1};

    // using predicate comparison:
    it = find_end (myvector.begin(), myvector.end(), match2, match2+3, myfunction);

    CHECK( (s32)(it - myvector.begin()) == 3); // pos

    s32 match3[] = {1,2,3,4,5,6,6,7,8,8,5,4,3,23,2,2,1,2,3,4};
    it = find_end(myvector.begin(), myvector.end(), match3, match3 + 20);
    CHECK(it == myvector.end());
  }

  bool comp_case_insensitive (int c1, int c2)
  {
    return (tolower(c1)==tolower(c2));
  }

  TEST_CASE("Core/Algorithms/FindFirstOf", "")
  {
    {
      int mychars[] = {'a','b','c','A','B','C'};
      core::Array<int> myvector (mychars,mychars+6);
      core::Array<int>::iterator it;

      int match[] = {'A','B','C'};

      // using default comparison:
      it = find_first_of (myvector.begin(), myvector.end(), match, match+3);

      CHECK(*it == 'A');

      // using predicate comparison:
      it = find_first_of (myvector.begin(), myvector.end(),
        match, match+3, comp_case_insensitive);

      CHECK(*it == 'a');
    }
    {
      int mychars[] = {'t','i','s','9','i','s'};
      core::Array<int> myvector (mychars, mychars + 6);
      core::Array<int>::iterator it;

      int match[] = {'a','b','c','s','9'};

      it = find_first_of (myvector.begin(), myvector.end(), match, match + 5);
      CHECK(*it == 's');

      it = find_first_of (it + 1, myvector.end(), match, match + 5);
      CHECK(*it == '9');
    }

  }

  TEST_CASE("Core/Algorithms/FindFirstNotOf", "")
  {
    s32 myInts[] = {1,23,3,41,5,6,7,8,9,10};
    s32 allowed[] = {1,2,3,4,5,6,7,8,9};

    core::Array<s32> myvector(myInts, myInts + 10);
    core::Array<s32>::iterator itr;

    itr = find_first_not_of(myvector.begin(), myvector.end(), allowed, allowed + 9);
    CHECK(*itr == 23);

    itr = find_first_not_of(itr + 1, myvector.end(), allowed, allowed + 9);
    CHECK(*itr == 41);

    itr = find_first_not_of(itr + 1, myvector.end(), allowed, allowed + 9);
    CHECK(*itr == 10);
  }

  TEST_CASE("Core/Algorithms/FindLastNotOf", "")
  {
    s32 myInts[] = {1,23,3,41,5,6,7,8,9,10};
    s32 allowed[] = {1,2,3,4,5,6,7,8,9};

    core::Array<s32> myvector(myInts, myInts + 10);
    core::Array<s32>::iterator itr;

    itr = find_last_not_of(myvector.begin(), myvector.end(), allowed, allowed + 9);
    CHECK(*itr == 10);

    itr = find_last_not_of(myvector.begin(), itr, allowed, allowed + 9);
    CHECK(*itr == 41);

    itr = find_last_not_of(myvector.begin(), itr, allowed, allowed + 9);
    CHECK(*itr == 23);
  }

  TEST_CASE("Core/Algorithms/Count", "Count and CountIf")
  {
    {//count
      s32 mycount;

      // counting elements in array:
      s32 myints[] = {10,20,30,30,20,10,10,20};   // 8 elements
      mycount = (s32) count (myints, myints+8, 10);
      CHECK(mycount == 3);

      // counting elements in container:
      core::Array<s32> myvector (myints, myints+8);
      mycount = (s32) count (myvector.begin(), myvector.end(), 20);
      CHECK(mycount == 3);

      mycount = (s32) count_all(myvector, 20);
      CHECK(mycount == 3);
    }

    {//count_if
      s32 mycount;

      core::Array<s32> myvector;
      for (s32 i=1; i<10; i++) myvector.push_back(i); // myvector: 1 2 3 4 5 6 7 8 9

      mycount = (s32) count_if (myvector.begin(), myvector.end(), IsOdd);
      CHECK(mycount == 5);

      mycount = (s32) count_if_all(myvector, IsOdd);
      CHECK(mycount == 5);
    }
  }

  bool mypredicate (s32 i, s32 j)
  {
    return (i==j);
  }

  TEST_CASE("Core/Algorithms/Mismatch", "")
  {
    core::Array<s32> myvector;
    for (s32 i=1; i<6; i++) myvector.push_back (i*10); // myvector: 10 20 30 40 50

    s32 myints[] = {10,20,80,320,1024};                //   myints: 10 20 80 320 1024

    Pair<core::Array<s32>::iterator,s32*> mypair;

    // using default comparison:
    mypair = mismatch (myvector.begin(), myvector.end(), myints);

    CHECK(*mypair.first == 30);
    CHECK(*mypair.second == 80);

    mypair.first++; mypair.second++;

    // using predicate comparison:
    mypair = mismatch (mypair.first, myvector.end(), mypair.second, mypredicate);

    CHECK(*mypair.first == 40);
    CHECK(*mypair.second == 320);
  }

  TEST_CASE("Core/Algorithms/Equal", "")
  {
    bool retValue = false;
    s32 myints[] = {20,40,60,80,100};          //   myints: 20 40 60 80 100
    core::Array<s32>myvector (myints,myints+5);     // myvector: 20 40 60 80 100

    retValue = equal(myvector.begin(), myvector.end(), myints);
    CHECK(retValue == true);

    myvector[3]=81;

    retValue = equal(myvector.begin(), myvector.end(), myints, mypredicate);
    CHECK(retValue == false);
  }

  TEST_CASE("Core/Algorithms/RandomShuffle", "")
  {
    TL_NESTED_FUNC_BEGIN(getRandom) tl_size getRandom(tl_size a_num)
    {
      return static_cast<u32>
        (g_defaultRNG.GetRandomInteger(static_cast<u32>(a_num)));
    }
    TL_NESTED_FUNC_END();

    tl_array<tl_int>::type  myVec;

    {
      // set some values
      for (tl_int i = 0; i < 10; ++i) myVec.push_back(i);

      random_shuffle(myVec.begin(), myVec.end());

      // not the best test, relies on the rng to be tested thoroughly
      bool notShuffled = true;
      for (tl_int i = 0; i < 10; ++i)
      {
        if (myVec[i] != i) { notShuffled = false; break; }
      }
      CHECK(notShuffled == false);
    }

    myVec.clear();

    {
      for (tl_int i = 0; i < 10; ++i) myVec.push_back(i);

      random_shuffle(myVec.begin(), myVec.end(), TL_NESTED_CALL(getRandom));

      bool notShuffled = true;
      for (tl_int i = 0; i < 10; ++i)
      {
        if (myVec[i] != i) { notShuffled = false; break; }
      }
      CHECK(notShuffled == false);
    }

  }

  TEST_CASE("Core/Algorithms/Search", "")
  {
    core::Array<s32> myvector;
    core::Array<s32>::iterator it;

    // set some values:        myvector: 10 20 30 40 50 60 70 80 90
    for (s32 i=1; i<10; i++) myvector.push_back(i*10);


    // using default comparison:
    s32 match1[] = {40,50,60,70};
    it = search (myvector.begin(), myvector.end(), match1, match1+4);

    CHECK((s32)(it - myvector.begin()) == 3);

    // using predicate comparison:
    s32 match2[] = {20,30,50};
    it = search (myvector.begin(), myvector.end(), match2, match2+3, mypredicate);

    CHECK(it == myvector.end());
  }

  TEST_CASE("Core/Algorithms/SearchN", "")
  {
    s32 myints[]={10,20,30,30,20,10,10,20};
    core::Array<s32> myvector (myints,myints+8);

    core::Array<s32>::iterator it;

    // using default comparison:
    it = search_n (myvector.begin(), myvector.end(), 2, 30);

    CHECK(s32(it-myvector.begin()) == 2);

    // using predicate comparison:
    it = search_n (myvector.begin(), myvector.end(), 2, 10, mypredicate);

    CHECK(s32(it-myvector.begin()) == 5);
  }

  template <typename T_Container>
  void Remove()
  {
    typedef typename T_Container::value_type value_type;
    typedef typename T_Container::iterator itr_type;

    value_type myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };

    T_Container myCont;

    value_type* pbegin = myints;
    value_type* pend = myints + utils::ArraySize(myints);

    myCont.assign(pbegin, pend);

    itr_type itrEnd = core::remove_all(myCont, 20);
    myCont.erase(itrEnd, myCont.end());
    CHECK(myCont.size() == 5);

    itr_type itr = myCont.begin();
    CHECK(*itr == 10); ++itr;
    CHECK(*itr == 30); ++itr;
    CHECK(*itr == 30); ++itr;
    CHECK(*itr == 10); ++itr;
    CHECK(*itr == 10); ++itr;
  }

  TEST_CASE("Core/Algorithms/Remove", "")
  {
    Remove<core::Array<tl_int> >();
    Remove<core::List<tl_int> >();
    Remove<core::Array<tl_int> >();
    Remove<core::List<tl_int> >();
  }

  template <typename T_Container>
  void RemoveCopy()
  {
    typedef typename T_Container::value_type value_type;
    typedef typename T_Container::iterator itr_type;

    value_type myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };

    value_type* pbegin = myints;
    value_type* pend = myints + utils::ArraySize(myints);

    T_Container myvector (8);
    core::remove_copy(pbegin, pend, myvector.begin(), 20);

    itr_type itr = myvector.begin();
    CHECK(*itr == 10); ++itr;
    CHECK(*itr == 30); ++itr;
    CHECK(*itr == 30); ++itr;
    CHECK(*itr == 10); ++itr;
    CHECK(*itr == 10); ++itr;
    CHECK(*itr == 0); ++itr;
    CHECK(*itr == 0); ++itr;
    CHECK(*itr == 0); ++itr;
  }

  TEST_CASE("Core/Algorithms/RemoveCopy", "")
  {
    RemoveCopy<core::Array<tl_int> >();
    RemoveCopy<core::List<tl_int> >();
  }

  template <typename T_Container>
  void ReplaceCopy()
  {
    typedef typename T_Container::value_type value_type;
    typedef typename T_Container::iterator itr_type;

    value_type myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };
    T_Container myIntsVec;
    myIntsVec.assign(myints, myints+ 8);
    T_Container myvector;
    core::replace_copy_all(myIntsVec, back_inserter(myvector), 20, 99);

    itr_type itr = myvector.begin();
    REQUIRE(myvector.size() == 8);
    CHECK(*itr == 10); ++itr;
    CHECK(*itr == 99); ++itr;
    CHECK(*itr == 30); ++itr;
    CHECK(*itr == 30); ++itr;
    CHECK(*itr == 99); ++itr;
    CHECK(*itr == 10); ++itr;
    CHECK(*itr == 10); ++itr;
    CHECK(*itr == 99); ++itr;
  }

  TEST_CASE("Core/Algorithms/ReplaceCopy", "")
  {
    ReplaceCopy<core::Array<tl_int> >();
    ReplaceCopy<core::List<tl_int> >();
  }

  template <typename T_Container>
  void Replace()
  {
    typedef typename T_Container::value_type value_type;
    typedef typename T_Container::iterator itr_type;

    value_type myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };
    T_Container myvector (myints, myints+8);            // 10 20 30 30 20 10 10 20

    core::replace_all(myvector, (value_type)20, (value_type)99); // 10 99 30 30 99 10 10 99

    itr_type itr = myvector.begin();
    REQUIRE(myvector.size() == 8);
    CHECK(*itr == 10); ++itr;
    CHECK(*itr == 99); ++itr;
    CHECK(*itr == 30); ++itr;
    CHECK(*itr == 30); ++itr;
    CHECK(*itr == 99); ++itr;
    CHECK(*itr == 10); ++itr;
    CHECK(*itr == 10); ++itr;
    CHECK(*itr == 99); ++itr;
  }

  TEST_CASE("Core/Algorithms/Replace", "")
  {
    Replace<core::Array<tl_int> >();
    Replace<core::List<tl_int> >();
    Replace<core::String>();
  }

  template <typename T_Container1, typename T_Container2>
  void UniqueAll()
  {
    typedef T_Container1::value_type  value_type_1;
    typedef T_Container2::iterator    itr_type_2;

    value_type_1 myValues[] = { 1, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 8, 8, 9, 10, 10};

    T_Container1 myVec(myValues, myValues + utils::ArraySize(myValues));
    T_Container2 myNewVec;

    unique_copy_all(myVec, myNewVec);

    bool testPassed = true;
    value_type_1 counter = 1;
    for (itr_type_2 itr = myNewVec.begin(), itrEnd = myNewVec.end();
         itr != itrEnd; ++itr)
    {
      if(*itr != (value_type_1)counter++)
      { testPassed = false; break; }
    }
    CHECK(testPassed);
  }

  TEST_CASE("Core/Algorithms/UniqueAll", "")
  {
    UniqueAll<core::Array<tl_int>, core::Array<tl_int> >();
    UniqueAll<core::List<tl_int>, core::Array<tl_int> >();
    UniqueAll<core::Array<tl_int>, core::List<tl_int> >();
    UniqueAll<core::List<tl_int>, core::List<tl_int> >();
    UniqueAll<core::String, core::String>();

    String somePath("..//..//somePath.txt");
    String fixedPath;
    String toMatch = "/";
    core::unique_copy_only_all(somePath, fixedPath, toMatch);
    CHECK(fixedPath.compare("../../somePath.txt") == 0);
    toMatch += ".";
    somePath.clear();
    core::unique_copy_only_all(fixedPath, somePath, toMatch);
    CHECK(somePath.compare("././somePath.txt") == 0);
  }

  template <typename T_Container1, typename T_Container2>
  void UniqueOnly()
  {
    typedef T_Container1::value_type  value_type_1;
    typedef T_Container2::iterator    itr_type_2;

    value_type_1 myValues[] = { 0, 0, 1, 1, 0, 0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 1, 1};

    T_Container1 myVec(myValues, myValues + utils::ArraySize(myValues));
    T_Container2 myNewVec;

    T_Container1 matchingVec;
    matchingVec.push_back(1);
    matchingVec.push_back(2);

    unique_copy_only_all(myVec, myNewVec, matchingVec);

    Array<value_type_1> newContainer;
    newContainer.assign(myNewVec.begin(), myNewVec.end());

    CHECK(newContainer.size() == 15);
    if (newContainer.size() == 15)
    {
      bool testPassed = true;
      if ( (newContainer[0]	 == 0 &&
            newContainer[1]	 == 0 &&
            newContainer[2]	 == 1 &&
            newContainer[3]	 == 0 &&
            newContainer[4]	 == 0 &&
            newContainer[5]	 == 1 &&
            newContainer[6]	 == 2 &&
            newContainer[7]	 == 3 &&
            newContainer[8]	 == 4 &&
            newContainer[9]	 == 5 &&
            newContainer[10] == 6 &&
            newContainer[11] == 7 &&
            newContainer[12] == 8 &&
            newContainer[13] == 9 &&
            newContainer[14] == 1) == false)
      {
        testPassed = false;
      }
      CHECK(testPassed);
    }
  }

  TEST_CASE("Core/Algorithms/UniqueOnlyAll", "")
  {
    UniqueOnly<core::Array<tl_int>, core::Array<tl_int> >();
    UniqueOnly<core::List<tl_int>, core::Array<tl_int> >();
    UniqueOnly<core::Array<tl_int>, core::List<tl_int> >();
    UniqueOnly<core::List<tl_int>, core::List<tl_int> >();
    UniqueOnly<core::String, core::String>();
  }

  TEST_CASE("Core/Algorithsm/lower_bound", "")
  {
    s32 intArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    s32* result = lower_bound( intArray, intArray + 15, 9);
    CHECK(*result == 9);

    s32 myints[] = {10,20,30,30,20,10,10,20};
    Array<s32> v(myints,myints+8);           // 10 20 30 30 20 10 10 20
    Array<s32>::iterator low;

    sort (v.begin(), v.end());                // 10 10 10 20 20 20 30 30

    low = lower_bound (v.begin(), v.end(), 20); //          ^

    CHECK( distance(v.begin(), low) == 3);
  }

  template <typename T_SortType>
  void SortDetailsTests()
  {
    const s32 k_arraySize = 26;
    const s32 rawArray[k_arraySize] =
    {5,6,3,4,7,1,2,3,8,9,4,2,3,6,9,6,7,8,3,2,7,6,5,2,8,5};

    const s32 sortedRawArray[k_arraySize] =
    {1,2,2,2,2,3,3,3,3,4,4,5,5,5,6,6,6,6,7,7,7,8,8,8,9,9};

    s32 myints[26] = {0};
    copy(rawArray, rawArray + k_arraySize, myints);

    s32* itrBegin = myints;
    s32* itrEnd   = myints + k_arraySize;

    Array<s32> myIntsArray(itrBegin, itrEnd);
    List<s32>  myIntsList(itrBegin, itrEnd);
    List<s32, ListNode<s32, singly_linked_tag> >  myIntsListSinglyLinked(itrBegin, itrEnd);

    tloc::core::detail::DoSort(itrBegin, itrEnd, T_SortType() );

    for (u32 i = 1; i < 26; ++i)
    {
      CHECK( myints[i] >= myints[i - 1]);
    }

    for (u32 i = 1; i < 26; ++i)
    {
      CHECK( myints[i] == sortedRawArray[i]);
    }

    tloc::core::detail::DoSort(myIntsArray.begin(), myIntsArray.end(),
                                  T_SortType() );

    for (u32 i = 1; i < 26; ++i)
    {
      CHECK( myIntsArray[i] >= myIntsArray[i - 1]);
    }

    for (u32 i = 1; i < 26; ++i)
    {
      CHECK( myIntsArray[i] == sortedRawArray[i]);
    }

    tloc::core::detail::DoSort(myIntsList.begin(), myIntsList.end(),
                                  T_SortType() );

    List<s32>::iterator listItr, listItr2, listItrEnd;
    listItr2 = myIntsList.begin();
    listItr = listItr2++;
    listItrEnd = myIntsList.end();

    while (listItr2 != listItrEnd)
    {
      CHECK(*listItr2 >= *listItr);

      ++listItr2;
      ++listItr;
    }


    listItr = myIntsList.begin();
    listItrEnd = myIntsList.end();
    const s32 *sortedItr = sortedRawArray;

    while (listItr != listItrEnd)
    {
      CHECK(*listItr == *sortedItr);

      ++listItr;
      ++sortedItr;
    }

    tloc::core::detail::DoSort(myIntsListSinglyLinked.begin(),
                               myIntsListSinglyLinked.end(),
                               T_SortType());

    List<s32, ListNode<s32, singly_linked_tag> >::iterator singleListItr,
                                                           singleListItr2,
                                                           singleListItrEnd;
    singleListItr2 = myIntsListSinglyLinked.begin();
    singleListItr = singleListItr2++;
    singleListItrEnd = myIntsListSinglyLinked.end();

    while (singleListItr2 != singleListItrEnd)
    {
      CHECK(*singleListItr2 >= *singleListItr);

      ++singleListItr2;
      ++singleListItr;
    }


    singleListItr = myIntsListSinglyLinked.begin();
    singleListItrEnd = myIntsListSinglyLinked.end();
    sortedItr = sortedRawArray;

    while (singleListItr != singleListItrEnd)
    {
      CHECK(*singleListItr == *sortedItr);

      ++singleListItr;
      ++sortedItr;
    }
  }

  TEST_CASE("Core/Algorithms/QuicksortDetail", "")
  {
    SortDetailsTests<sort_quicksort_leftpivot>();
    SortDetailsTests<sort_quicksort_rightpivot>();
    SortDetailsTests<sort_quicksort_middlepivot>();
    SortDetailsTests<sort_quicksort_randompivot>();
  }

  TEST_CASE("Core/Algorithms/InsertionsortDetail", "")
  {
    SortDetailsTests<sort_insertionsort>();
  }

  TEST_CASE("Core/Algorithms/MergesortDetail", "")
  {
    SortDetailsTests<sort_mergesort>();
    SortDetailsTests<sort_merge_insertionsort>();
  }

  TEST_CASE("Core/Algorithms/BubblesortDetail", "")
  {
    SortDetailsTests<sort_bubblesort>();
  }

  TEST_CASE("Core/Algorithms/Sort", "")
  {
    const s32 k_arraySize = 26;
    const s32 rawArray[k_arraySize] =
    {5,6,3,4,7,1,2,3,8,9,4,2,3,6,9,6,7,8,3,2,7,6,5,2,8,5};

    s32 myints[26] = {0};
    copy(rawArray, rawArray + k_arraySize, myints);

    s32* itrBegin = myints;
    s32* itrEnd   = myints + k_arraySize;

    Array<s32> myIntsArray(itrBegin, itrEnd);
    List<s32>  myIntsList(itrBegin, itrEnd);

    tloc::core::sort(itrBegin, itrEnd);

    for (u32 i = 1; i < 26; ++i)
    {
      CHECK( myints[i] >= myints[i - 1]);
    }

    tloc::core::sort(myIntsArray.begin(), myIntsArray.end());

    for (u32 i = 1; i < 26; ++i)
    {
      CHECK( myIntsArray[i] >= myIntsArray[i - 1]);
    }

    tloc::core::sort(myIntsList.begin(), myIntsList.end());

    List<s32>::iterator listItr, listItr2, listItrEnd;
    listItr2 = myIntsList.begin();
    listItr = listItr2++;
    listItrEnd = myIntsList.end();

    while (listItr2 != listItrEnd)
    {
      CHECK(*listItr2 >= *listItr);

      ++listItr2;
      ++listItr;
    }
  }

  struct CountDestruction
  {
    CountDestruction()
    {
      ++m_ctorCount;
    }

    ~CountDestruction()
    {
      ++m_dtorCount;
    }

    static tl_size m_ctorCount;
    static tl_size m_dtorCount;
  };

  tl_size CountDestruction::m_ctorCount = 0;
  tl_size CountDestruction::m_dtorCount = 0;

  TEST_CASE("Core/Algorithms/delete_ptrs", "")
  {
    Array<CountDestruction*> myArray;
    List<CountDestruction*>  myList;

    const tl_size numElements = 10;

    for (tl_size i = 0; i < numElements; ++i)
    {
      myArray.push_back(new CountDestruction()); //-V508
      myList.push_back(new CountDestruction()); //-V508
    }

    CHECK(CountDestruction::m_ctorCount == numElements * 2);
    CHECK(CountDestruction::m_dtorCount == 0);
    CHECK(myArray.size() == numElements);
    CHECK(myList.size() == numElements);

    delete_ptrs(myArray.begin(), myArray.end());
    CHECK(CountDestruction::m_dtorCount == numElements);
    delete_ptrs(myList.begin(), myList.end());
    CHECK(CountDestruction::m_dtorCount == numElements * 2);
  }
};
