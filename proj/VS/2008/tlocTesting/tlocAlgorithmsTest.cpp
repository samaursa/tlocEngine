#include "tlocTestCommon.h"

#include "tlocCore/tlocAlgorithms.h"
#include "tlocCore/tlocAlgorithms.inl"

#include "tlocCore/tlocArray.h"
#include "tlocCore/tlocArray.inl"

#include "tlocCore/tlocList.h"
#include "tlocCore/tlocList.inl"

namespace TestingAlgorithms
{
  USING_TLOC;
  using namespace core;

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
    { // copy arithmetic types
      const char8* testString = "This is a test string"; // 21 chars including /0
      const char8* stringEnd = testString + 22; // copy does not include stringEnd
      char8* copiedString = new char8[stringEnd - testString];

      copy(testString, stringEnd, copiedString);

      for (u32 i = 0; i < (u32)(stringEnd - testString); ++i)
      {
        CHECK(copiedString[i] == testString[i]);
      }
    }

    { // copy complex types
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

      copy(arrayStructs, arrayStructs + 5, copiedStructs);

      for (u32 i = 0; i < 5; ++i)
      {
        CHECK(copiedStructs[i].a == testStruct.a);
        CHECK(copiedStructs[i].b == testStruct.b);
      }
    }

    {// tlCopyBackward
      char8 testString[] = "0123456789"; // 10 chars including /0

      copy_backward(testString, testString + 6, testString + 10);

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
    { // fill char (fill has specialization for fill<char>() )
      char8 testArray[100] = {0};

      fill(testArray, testArray + 100, 'T');

      for (u32 i = 0; i < 100; ++i)
      {
        CHECK(testArray[i] == 'T');
      }
    }

    { // fill other types
      u64 testArray[100] = {0};

      fill(testArray, testArray + 100, 50);

      for (u32 i = 0; i < 100; ++i)
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

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/FillN",
    "Test the fill_n() functions")
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

    for_each(intArray, intArray + arraySize, ForEachFunc);

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
    p = find(myints,myints+4, (u32)30);
    ++p;

    CHECK(*p == 40);

    core::Array<u32> myvector (myints,myints+4);
    core::Array<u32>::iterator it;

    //iterator to vector element:
    it = find (myvector.begin(), myvector.end(), (u32)30);
    ++it;

    CHECK(*it == 40);
  }

  bool IsOdd (s32 i)
  {
    return ((i%2)==1);
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/FindIf", "")
  {
    core::Array<s32> myvector;
    core::Array<s32>::iterator it;

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

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/FindEnd", "")
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

  bool comp_case_insensitive (char8 c1, char8 c2)
  {
    return (tolower(c1)==tolower(c2));
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/FindFirstOf", "")
  {
    {
      char8 mychars[] = {'a','b','c','A','B','C'};
      core::Array<char8> myvector (mychars,mychars+6);
      core::Array<char8>::iterator it;

      char8 match[] = {'A','B','C'};

      // using default comparison:
      it = find_first_of (myvector.begin(), myvector.end(), match, match+3);

      CHECK(*it == 'A');

      // using predicate comparison:
      it = find_first_of (myvector.begin(), myvector.end(),
        match, match+3, comp_case_insensitive);

      CHECK(*it == 'a');
    }
    {
      char8 mychars[] = {'t','i','s','9','i','s'};
      core::Array<char8> myvector (mychars, mychars + 6);
      core::Array<char8>::iterator it;

      char8 match[] = {'a','b','c','s','9'};

      it = find_first_of (myvector.begin(), myvector.end(), match, match + 5);
      CHECK(*it == 's');

      it = find_first_of (it + 1, myvector.end(), match, match + 5);
      CHECK(*it == '9');
    }

  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/FindFirstNotOf", "")
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

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/FindLastNotOf", "")
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

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Count", "Count and CountIf")
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
    }

    {//count_if
      s32 mycount;

      core::Array<s32> myvector;
      for (s32 i=1; i<10; i++) myvector.push_back(i); // myvector: 1 2 3 4 5 6 7 8 9

      mycount = (s32) count_if (myvector.begin(), myvector.end(), IsOdd);
      CHECK(mycount == 5);
    }
  }

  bool mypredicate (s32 i, s32 j)
  {
    return (i==j);
  }

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Mismatch", "")
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

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Equal", "")
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

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/Search", "")
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

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithms/SearchN", "")
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

  TEST_CASE_METHOD(AlgorithmFixture, "Core/Algorithsm/lower_bound", "")
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
};
