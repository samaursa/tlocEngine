#include "tlocTestCommon.h"

#include "tlocCore/tlocForwardList.h"
#include "tlocCore/tlocForwardList.inl"
#include "tlocCore/tlocArray.inl"

namespace TestingForwardList
{
  USING_TLOC;
  using namespace core;

#define CHECK_CONTENTS_OF_FORWARD_LIST_MATCHES_VALUE(forwardListBegin, \
                                                     forwardListEnd, \
                                                     value) \
  for (/* */; forwardListBegin != forwardListEnd; ++forwardListBegin)\
  {\
  CHECK((*forwardListBegin) == value);\
  }

#define FILL_FORWARD_LIST_BY_PUSH(forwardListName, nFrom, nTo) \
  for (s32 i = nTo; i >= nFrom; --i)\
  {\
    forwardListName.push_front(i);\
  }

#define CHECK_FORWARD_LIST_BY_ITERATOR(forwardListBegin, forwardListEnd, nFrom)\
  for (u32 i = nFrom; forwardListBegin != forwardListEnd; ++forwardListBegin, ++i)\
  {\
    CHECK((*forwardListBegin) == (s32)i);\
  }

  struct ForwardListFixture
  {
    typedef ForwardList<s32>::type intForwardList;
    typedef ForwardList<f32>::type floatForwardList;
    typedef ArrayForwardList<s32>::type arrayIntForwardList;
  };

  template <typename T_ForwardListType>
  void testCtors()
  {
    T_ForwardListType first;
    T_ForwardListType second(10,20);
    T_ForwardListType third (second.begin(), second.end());
    T_ForwardListType fourth (third);

    T_ForwardListType::iterator itr = second.begin();
    T_ForwardListType::iterator itrEnd = second.end();
    CHECK_CONTENTS_OF_FORWARD_LIST_MATCHES_VALUE(itr, itrEnd, 20);

    itr = third.begin();
    itrEnd = third.end();
    CHECK_CONTENTS_OF_FORWARD_LIST_MATCHES_VALUE(itr, itrEnd, 20);

    itr = fourth.begin();
    itrEnd = fourth.end();
    CHECK_CONTENTS_OF_FORWARD_LIST_MATCHES_VALUE(itr, itrEnd, 20);

    s32 myInts[] = {37, 14, 94, 100};
    T_ForwardListType fifth (myInts, myInts + sizeof(myInts) / sizeof(s32));

    itr = fifth.begin();

    CHECK(*itr++ == 37);
    CHECK(*itr++ == 14);
    CHECK(*itr++ == 94);
    CHECK(*itr++ == 100);
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/Ctors" , "")
  {
    testCtors<intForwardList>();
    testCtors<arrayIntForwardList>();
  }

  template <typename T_ForwardListType>
  void testGetContainer()
  {
    const s32 myInts[] = {78, 52, 38, 46};
    T_ForwardListType myForwardList(myInts, myInts+4);

    T_ForwardListType::container_type myContainer = myForwardList._Get_container();
    T_ForwardListType::container_type::iterator itr;

    itr = myContainer.begin();

    CHECK(*itr == 78); ++itr;
    CHECK(*itr == 52); ++itr;
    CHECK(*itr == 38); ++itr;
    CHECK(*itr == 46); ++itr;

    CHECK(itr == myContainer.end());
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/_Get_container", "")
  {
    testGetContainer<intForwardList>();
    testGetContainer<arrayIntForwardList>();
  }

  template <typename T_ForwardListType>
  void testOperatorEqual()
  {
    T_ForwardListType first(21, 10);
    T_ForwardListType second(42, 30);

    second = first;

    T_ForwardListType::iterator itr = second.begin();
    T_ForwardListType::iterator itrEnd = second.end();
    CHECK_CONTENTS_OF_FORWARD_LIST_MATCHES_VALUE(itr, itrEnd, 10);
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/operator=", "")
  {
    testOperatorEqual<intForwardList>();
    testOperatorEqual<arrayIntForwardList>();
  }

  template <typename T_ForwardListType>
  void testAssign()
  {
    T_ForwardListType firstList;
    s32 myInts[] = {87, 49, 26, 72};

    firstList.assign(myInts, myInts+4);

    T_ForwardListType::iterator itr;
    itr = firstList.begin();

    CHECK(*itr == 87); ++itr;
    CHECK(*itr == 49); ++itr;
    CHECK(*itr == 26); ++itr;
    CHECK(*itr == 72); ++itr;

    T_ForwardListType secondList;
    secondList.assign(firstList.begin(), firstList.end());

    itr = secondList.begin();

    CHECK(*itr == 87); ++itr;
    CHECK(*itr == 49); ++itr;
    CHECK(*itr == 26); ++itr;
    CHECK(*itr == 72); ++itr;

    T_ForwardListType thirdList;
    thirdList.assign(4, 88);

    itr = thirdList.begin();

    CHECK_CONTENTS_OF_FORWARD_LIST_MATCHES_VALUE(itr, thirdList.end(), 88);

  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/assign", "")
  {
    testAssign<intForwardList>();
    testAssign<arrayIntForwardList>();
  }

  template <typename T_ForwardListType>
  void testFront()
  {
    const s32 myInts[] = {74, 28, 95, 42};
    T_ForwardListType myForwardList(myInts, myInts+4);

    CHECK(myForwardList.front() == 74);
    myForwardList.pop_front();
    CHECK(myForwardList.front() == 28);
    myForwardList.pop_front();
    CHECK(myForwardList.front() == 95);
    myForwardList.pop_front();
    CHECK(myForwardList.front() == 42);
    myForwardList.pop_front();
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/front", "")
  {
    testFront<intForwardList>();
  }

  template <typename T_ForwardListType, typename T_ForwardListIterator>
  void testBeforeBeginIteratorAccessor()
  {
    T_ForwardListType myForwardList(1, 22);
    T_ForwardListIterator itr = myForwardList.before_begin();

    CHECK((*++itr) == 22);
  }

  TEST_CASE_METHOD(ForwardListFixture,
    "Core/Containers/ForwardList/before_begin", "")
  {
    testBeforeBeginIteratorAccessor<intForwardList, intForwardList::iterator>();
    testBeforeBeginIteratorAccessor<intForwardList, intForwardList::const_iterator>();
  }

  template <typename T_ForwardListType>
  void testCBeforeBeginIteratorAccessor()
  {
    T_ForwardListType myForwardList(1, 14);
    T_ForwardListType::const_iterator itr = myForwardList.cbefore_begin();

    CHECK((*++itr) == 14);
  }

  TEST_CASE_METHOD(ForwardListFixture,
    "Core/Containers/ForwardList/cbefore_begin", "")
  {
    testCBeforeBeginIteratorAccessor<intForwardList>();
  }

  template <typename T_ForwardListType, typename T_ForwardListIterator>
  void testBeginEndIteratorAccessors()
  {
    const s32 myInts[] = {32,28,71,54};

    T_ForwardListType myForwardList(myInts, myInts+4);
    CHECK((*myForwardList.begin()) == 32);

    T_ForwardListIterator itr = myForwardList.begin();

    CHECK(*itr == 32); ++itr;
    CHECK(*itr == 28); ++itr;
    CHECK(*itr == 71); ++itr;
    CHECK(*itr == 54); ++itr;

    CHECK(itr == myForwardList.end());
  }

  TEST_CASE_METHOD(ForwardListFixture,
                   "Core/Containers/ForwardList/beginEndIteratorAccessors", "")
  {
    testBeginEndIteratorAccessors<intForwardList, intForwardList::iterator>();
    testBeginEndIteratorAccessors<intForwardList, intForwardList::const_iterator>();
    testBeginEndIteratorAccessors<arrayIntForwardList, arrayIntForwardList::iterator>();
    testBeginEndIteratorAccessors<arrayIntForwardList, arrayIntForwardList::const_iterator>();
  }

  template <typename T_ForwardListType>
  void testCBeginCEndIteratorAccessors()
  {
    const s32 myInts[] = {11,22,60,41};

    T_ForwardListType myForwardList(myInts, myInts+4);
    CHECK((*myForwardList.cbegin()) == 11);

    T_ForwardListType::const_iterator itr = myForwardList.cbegin();

    CHECK(*itr == 11); ++itr;
    CHECK(*itr == 22); ++itr;
    CHECK(*itr == 60); ++itr;
    CHECK(*itr == 41); ++itr;

    CHECK(itr == myForwardList.cend());
  }


  TEST_CASE_METHOD(ForwardListFixture,
    "Core/Containers/ForwardList/cbeginCendIteratorAccessors", "")
  {
    testCBeginCEndIteratorAccessors<intForwardList>();
    testCBeginCEndIteratorAccessors<arrayIntForwardList>();
  }

  template <typename T_ForwardListType>
  void testEmpty()
  {
    T_ForwardListType myForwardList;
    CHECK(myForwardList.empty() == true);

    const s32 myInts[] = {54, 94, 20, 32};
    myForwardList.assign(myInts, myInts+4);
    CHECK(myForwardList.empty() == false);

    myForwardList.clear();
    CHECK(myForwardList.empty() == true);
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/empty", "")
  {
    testEmpty<intForwardList>();
    testEmpty<arrayIntForwardList>();
  }

  template <typename T_ForwardListType>
  void testMaxSize()
  {
    T_ForwardListType myForwardList;
    CHECK(myForwardList.max_size() > 0);
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/max_size", "")
  {
    testMaxSize<intForwardList>();
  }

  template <typename T_ForwardListType>
  void testClear()
  {
    const s32 myFirstInts[] = {98, 57, 62, 35};
    T_ForwardListType myForwardList(myFirstInts, myFirstInts+4);

    T_ForwardListType::iterator itr = myForwardList.begin();

    REQUIRE(*itr == 98); ++itr;
    REQUIRE(*itr == 57); ++itr;
    REQUIRE(*itr == 62); ++itr;
    REQUIRE(*itr == 35); ++itr;

    myForwardList.clear();
    CHECK(myForwardList.empty());
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/clear", "")
  {
    testClear<intForwardList>();
    testClear<arrayIntForwardList>();
  }

  template <typename T_ForwardListType>
  void testInsertAfter()
  {
    T_ForwardListType myForwardList;
    T_ForwardListType::iterator itr, retItr;

    FILL_FORWARD_LIST_BY_PUSH(myForwardList, 0, 5);

    itr = myForwardList.begin();
    advance(itr, 3);
    REQUIRE(*itr == 3);

    retItr = myForwardList.insert_after(itr, 42);
    CHECK(*retItr == 42);

    itr = myForwardList.begin();
    CHECK(*itr == 0);  ++itr;
    CHECK(*itr == 1);  ++itr;
    CHECK(*itr == 2);  ++itr;
    CHECK(*itr == 3);  ++itr;
    CHECK(*itr == 42); ++itr;
    CHECK(*itr == 4);  ++itr;
    CHECK(*itr == 5);  ++itr;

    itr = myForwardList.begin();
    advance(itr, 2);
    REQUIRE(*itr == 2);

    myForwardList.insert_after(itr, 3, 12);

    itr = myForwardList.begin();
    CHECK(*itr == 0);  ++itr;
    CHECK(*itr == 1);  ++itr;
    CHECK(*itr == 2);  ++itr; //-V525
    CHECK(*itr == 12); ++itr;
    CHECK(*itr == 12); ++itr;
    CHECK(*itr == 12); ++itr;
    CHECK(*itr == 3);  ++itr;
    CHECK(*itr == 42); ++itr;
    CHECK(*itr == 4);  ++itr;
    CHECK(*itr == 5);  ++itr;

    itr = myForwardList.begin();
    advance(itr, 5);
    REQUIRE(*itr == 12);

    T_ForwardListType insertionForwardList(4, 85);
    myForwardList.insert_after(itr,
                               insertionForwardList.begin(),
                               insertionForwardList.end());

    itr = myForwardList.begin();
    CHECK(*itr == 0);  ++itr;
    CHECK(*itr == 1);  ++itr;
    CHECK(*itr == 2);  ++itr; //-V525
    CHECK(*itr == 12); ++itr;
    CHECK(*itr == 12); ++itr;
    CHECK(*itr == 12); ++itr;
    CHECK(*itr == 85); ++itr;
    CHECK(*itr == 85); ++itr;
    CHECK(*itr == 85); ++itr;
    CHECK(*itr == 85); ++itr;
    CHECK(*itr == 3);  ++itr;
    CHECK(*itr == 42); ++itr;
    CHECK(*itr == 4);  ++itr;
    CHECK(*itr == 5);  ++itr;
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/insert_after", "")
  {
    testInsertAfter<intForwardList>();
  }

  template <typename T_ForwardListType>
  void testEraseAfter()
  {
    T_ForwardListType myForwardList;
    FILL_FORWARD_LIST_BY_PUSH(myForwardList, 0, 5);

    T_ForwardListType::iterator itr1, itr2;
    itr1 = myForwardList.begin();

    advance(itr1, 3);
    CHECK(*itr1 == 3);

    itr1 = myForwardList.erase_after(itr1);
    CHECK(*itr1 == 5);

    itr1 = myForwardList.begin();
    CHECK(*itr1 == 0); ++itr1;
    CHECK(*itr1 == 1); ++itr1;
    CHECK(*itr1 == 2); ++itr1;
    CHECK(*itr1 == 3); ++itr1;
    CHECK(*itr1 == 5); ++itr1;

    itr1 = itr2 = myForwardList.begin();
    advance(itr2, 4);

    itr1 = myForwardList.erase_after(itr1, itr2);
    CHECK(*itr1 == 5);

    itr1 = myForwardList.begin();
    CHECK(*itr1 == 0); ++itr1;
    CHECK(*itr1 == 5); ++itr1;
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/erase_after", "")
  {
    testEraseAfter<intForwardList>();
  }

  template <typename T_ForwardListType>
  void testPushFront()
  {
    T_ForwardListType myForwardList(3, 1);
    myForwardList.push_front(2);
    myForwardList.push_front(3);
    myForwardList.push_front(4);

    T_ForwardListType::iterator itr = myForwardList.begin();

    CHECK(*itr == 4); ++itr;
    CHECK(*itr == 3); ++itr;
    CHECK(*itr == 2); ++itr; //-V525
    CHECK(*itr == 1); ++itr;
    CHECK(*itr == 1); ++itr;
    CHECK(*itr == 1); ++itr;

  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/push_front", "")
  {
    testPushFront<intForwardList>();
  }

  template <typename T_ForwardListType>
  void testPopFront()
  {
    T_ForwardListType myForwardList(3, 1);
    myForwardList.push_front(2);
    myForwardList.push_front(3);
    myForwardList.push_front(4);

    CHECK(myForwardList.front() == 4);
    myForwardList.pop_front();
    CHECK(myForwardList.front() == 3);
    myForwardList.pop_front();
    CHECK(myForwardList.front() == 2); //-V525
    myForwardList.pop_front();
    CHECK(myForwardList.front() == 1);
    myForwardList.pop_front();
    CHECK(myForwardList.front() == 1);
    myForwardList.pop_front();
    CHECK(myForwardList.front() == 1);
    myForwardList.pop_front();

    CHECK(myForwardList.empty());
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/pop_back", "")
  {
    testPopFront<intForwardList>();
  }

  template <typename T_ForwardListType>
  void testSwap()
  {
    const s32 myInts1[] = {54, 27, 68, 49, 52};
    const s32 myInts2[] = {44, 32, 29};
    T_ForwardListType myForwardList1(myInts1, myInts1+5);
    T_ForwardListType myForwardList2(myInts2, myInts2+3);
    T_ForwardListType::iterator itr1, itr2;

    myForwardList1.swap(myForwardList2);

    itr1 = myForwardList1.begin();
    CHECK(*itr1 == 44); ++itr1;
    CHECK(*itr1 == 32); ++itr1;
    CHECK(*itr1 == 29); ++itr1;

    itr2 = myForwardList2.begin();
    CHECK(*itr2 == 54); ++itr2;
    CHECK(*itr2 == 27); ++itr2;
    CHECK(*itr2 == 68); ++itr2;
    CHECK(*itr2 == 49); ++itr2;
    CHECK(*itr2 == 52); ++itr2;
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/swap", "")
  {
    testSwap<intForwardList>();
    testSwap<arrayIntForwardList>();
  }

  bool myComparison(s32 external, s32 original)
  {
    return ((external + 100) < original);
  }

  template <typename T_ForwardListType>
  void testMerge()
  {
    T_ForwardListType firstForwardList, secondForwardList;

    firstForwardList.push_front(37);
    firstForwardList.push_front(10);
    firstForwardList.push_front(3);

    secondForwardList.push_front(89);
    secondForwardList.push_front(28);
    secondForwardList.push_front(15);

    firstForwardList.merge(secondForwardList);

    T_ForwardListType::iterator itr;
    itr = firstForwardList.begin();

    CHECK(*itr == 3); ++itr;
    CHECK(*itr == 10); ++itr;
    CHECK(*itr == 15); ++itr;
    CHECK(*itr == 28); ++itr;
    CHECK(*itr == 37); ++itr;
    CHECK(*itr == 89); ++itr;

    T_ForwardListType thirdForwardList, fourthForwardList;

    thirdForwardList.push_front(37);
    thirdForwardList.push_front(10);
    thirdForwardList.push_front(3);

    fourthForwardList.push_front(89);
    fourthForwardList.push_front(28);
    fourthForwardList.push_front(15);

    thirdForwardList.merge(fourthForwardList, myComparison);
    itr = thirdForwardList.begin();

    CHECK(*itr == 3); ++itr;
    CHECK(*itr == 10); ++itr;
    CHECK(*itr == 37); ++itr;
    CHECK(*itr == 15); ++itr;
    CHECK(*itr == 28); ++itr;
    CHECK(*itr == 89); ++itr;
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/merge", "")
  {
    testMerge<intForwardList>();
  }

  template <typename T_ForwardListType>
  void testSpliceAfter()
  {
    T_ForwardListType myForwardList1, myForwardList2;
    T_ForwardListType::iterator itr, itrRangeBegin, itrRangeEnd;

    FILL_FORWARD_LIST_BY_PUSH(myForwardList1, 0, 5);

    myForwardList2.assign(5, 20);

    itr = myForwardList1.begin();
    advance(itr, 2); // Points to 2 (myForwardList1)
    CHECK(*itr == 2);

    // Default Splice after. Copy myForwardList2 into myForwardList1 at itr
    myForwardList1.splice_after(itr, myForwardList2);

    itr = myForwardList1.begin();
    CHECK(*itr == 0);  ++itr;
    CHECK(*itr == 1);  ++itr;
    CHECK(*itr == 2);  ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 3);  ++itr;
    CHECK(*itr == 4);  ++itr;
    CHECK(*itr == 5);  ++itr;

    CHECK(myForwardList2.empty());

    itr = myForwardList1.begin();
    advance(itr, 8); // Points to the 3 (myForwardList1)
    CHECK(*itr == 3);

    const s32 myInts1[] = {33, 11, 22, 44, 66};
    myForwardList2.assign(myInts1, myInts1+5);
    itrRangeBegin = myForwardList2.begin();
    advance(itrRangeBegin, 2); // Points to 22 (myForwardList2)
    CHECK(*itrRangeBegin == 22);

    // Second variation of splice after. Copy an element in myForwardList2
    // at itrRangeBegin, to myForardList1 at itr
    myForwardList1.splice_after(itr, myForwardList2, itrRangeBegin);

    itr = myForwardList1.begin();
    CHECK(*itr == 0);  ++itr;
    CHECK(*itr == 1);  ++itr;
    CHECK(*itr == 2);  ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 3);  ++itr;
    CHECK(*itr == 22); ++itr;
    CHECK(*itr == 4);  ++itr;
    CHECK(*itr == 5);  ++itr;

    itr = myForwardList2.begin();
    CHECK(*itr == 33); ++itr;
    CHECK(*itr == 11); ++itr;
    CHECK(*itr == 44); ++itr;
    CHECK(*itr == 66); ++itr;

    itr = myForwardList1.begin();
    advance(itr, 1); // Points to the 1 (myForwardList1)
    CHECK(*itr == 1);

    const s32 myInts2[] = {11, 6, 22, 14, 8};
    myForwardList2.assign(myInts2, myInts2+5);
    itrRangeBegin = itrRangeEnd = myForwardList2.begin();
    advance(itrRangeBegin, 1); // Points to 6 (myForwardList2)
    CHECK(*itrRangeBegin == 6);
    advance(itrRangeEnd, 4);
    CHECK(*itrRangeEnd == 8);

    // Third variation of splice after. Copy a range of elements from
    // myForwardList2, indicated by itrRangeBegin and itrRangeEnd, to
    // myForwardList1 at itr
    myForwardList1.splice_after(itr, myForwardList2, itrRangeBegin, itrRangeEnd);

    itr = myForwardList1.begin();
    CHECK(*itr == 0);  ++itr;
    CHECK(*itr == 1);  ++itr;
    CHECK(*itr == 22); ++itr;
    CHECK(*itr == 14); ++itr;
    CHECK(*itr == 2);  ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 20); ++itr;
    CHECK(*itr == 3);  ++itr;
    CHECK(*itr == 22); ++itr;
    CHECK(*itr == 4);  ++itr;
    CHECK(*itr == 5);  ++itr;

    itr = myForwardList2.begin();
    CHECK(*itr == 11); ++itr;
    CHECK(*itr == 6);  ++itr;
    CHECK(*itr == 8);  ++itr;


  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/splice_after", "")
  {
    testSpliceAfter<intForwardList>();
  }

  bool isSecondDigitOdd(const s32& value) { return !((value/10)%2 == 0); }

  class isNotDivisibleByThree
  {
  public:
    bool operator() (const s32& value) { return !((value%3)==0); }
  };

  template <typename T_ForwardListType>
  void testRemoveIf()
  {
    T_ForwardListType myForwardList;
    FILL_FORWARD_LIST_BY_PUSH(myForwardList, 0, 40);

    myForwardList.remove_if(isSecondDigitOdd);

    myForwardList.remove_if(isNotDivisibleByThree());

    T_ForwardListType::iterator itr;
    itr = myForwardList.begin();

    CHECK(*itr == 0);  ++itr;
    CHECK(*itr == 3);  ++itr;
    CHECK(*itr == 6);  ++itr;
    CHECK(*itr == 9);  ++itr;
    CHECK(*itr == 21); ++itr;
    CHECK(*itr == 24); ++itr;
    CHECK(*itr == 27); ++itr;

    CHECK(itr == myForwardList.end());
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/remove_if", "")
  {
    testRemoveIf<intForwardList>();
  }

  template <typename T_ForwardListType>
  void testReverse()
  {
    T_ForwardListType myForwardList;

    FILL_FORWARD_LIST_BY_PUSH(myForwardList, 0, 9);

    myForwardList.reverse();

    T_ForwardListType::iterator itr;
    itr = myForwardList.begin();

    CHECK(*itr == 9); ++itr;
    CHECK(*itr == 8); ++itr;
    CHECK(*itr == 7); ++itr;
    CHECK(*itr == 6); ++itr;
    CHECK(*itr == 5); ++itr;
    CHECK(*itr == 4); ++itr;
    CHECK(*itr == 3); ++itr;
    CHECK(*itr == 2); ++itr;
    CHECK(*itr == 1); ++itr;
    CHECK(*itr == 0); ++itr;
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/reverse", "")
  {
    testReverse<intForwardList>();
  }

  bool integerCastComparison (f32 first, f32 second)
  {
    return ((s32)first == (s32)second);
  }

  class isNear
  {
  public:
    bool operator() (f32 first, f32 second)
    {
      f32 diff = first - second;
      return (diff > -10.f && diff < 10.f);
    }
  };

  template <typename T_ForwardListType>
  void testUnique()
  {
    const f32 myFloats[] = { 0.f , 2.5f , 10.23f, 18.0f, 18.0f,
                             36.f, 45.7f, 45.9f , 50.f , 64.f};
    T_ForwardListType myForwardList(myFloats, myFloats+10);

    myForwardList.unique();

    T_ForwardListType::iterator itr;
    itr = myForwardList.begin();

    CHECK(*itr == 0.f);    ++itr;
    CHECK(*itr == 2.5f);   ++itr;
    CHECK(*itr == 10.23f); ++itr;
    CHECK(*itr == 18.f);   ++itr;
    CHECK(*itr == 36.f);   ++itr;
    CHECK(*itr == 45.7f);  ++itr;
    CHECK(*itr == 45.9f);  ++itr;
    CHECK(*itr == 50.f);   ++itr;
    CHECK(*itr == 64.f);   ++itr;

    CHECK(itr == myForwardList.end());

    myForwardList.unique(integerCastComparison);
    itr = myForwardList.begin();

    CHECK(*itr == 0.f);    ++itr;
    CHECK(*itr == 2.5f);   ++itr;
    CHECK(*itr == 10.23f); ++itr;
    CHECK(*itr == 18.f);   ++itr;
    CHECK(*itr == 36.f);   ++itr;
    CHECK(*itr == 45.7f);  ++itr;
    CHECK(*itr == 50.f);   ++itr;
    CHECK(*itr == 64.f);   ++itr;

    CHECK(itr == myForwardList.end());

    myForwardList.unique(isNear());
    itr = myForwardList.begin();

    CHECK(*itr == 0.f);    ++itr;
    CHECK(*itr == 10.23f); ++itr;
    CHECK(*itr == 36.f);   ++itr;
    CHECK(*itr == 50.f);   ++itr;
    CHECK(*itr == 64.f);   ++itr;

    CHECK(itr == myForwardList.end());
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/unique", "")
  {
    testUnique<floatForwardList>();
  }

  template <typename T_ForwardListType>
  void testSort()
  {
    const s32 myInts[] = {45, 38, 59, 11, 62, 36, 7};
    T_ForwardListType myForwardList(myInts, myInts+7);

    myForwardList.sort();

    CHECK(*itr == 7); ++itr;
    CHECK(*itr == 11); ++itr;
    CHECK(*itr == 36); ++itr;
    CHECK(*itr == 38); ++itr;
    CHECK(*itr == 45); ++itr;
    CHECK(*itr == 59); ++itr;
    CHECK(*itr == 62); ++itr;
  }

  TEST_CASE_METHOD(ForwardListFixture, "Core/Containers/ForwardList/sort", "")
  {
    /* Intentionally blank until sort is implemented into a container */
  }





};