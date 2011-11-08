namespace TestingList
{
  USING_TLOC;

  class SomeClass
  {
  public:
    int dummy;
  };

  struct ListFixture
  {
    typedef List<s32, ListNode<s32, doubly_linked_tag>, List_Dynamic(), true> intListWithSize;
    typedef List<s32, ListNode<s32, doubly_linked_tag>, List_Dynamic(), false> intListWithoutSize;

    typedef List<s32, ListNode<u32, doubly_linked_tag>, List_Dynamic(), true> uintListWithSize;
    typedef List<s32, ListNode<u32, doubly_linked_tag>, List_Dynamic(), false> uintListWithoutSize;

    List<s32, ListNode<s32, doubly_linked_tag>, List_Dynamic(), true> intListSize;
    List<s32, ListNode<s32, doubly_linked_tag>, List_Dynamic(), false> intListNoSize;
    List<SomeClass> classList;
  };

  template <typename T_ListType>
  void testCtors()
  {
    // constructors used in the same order as described above:
    T_ListType first;                                // empty list of ints
    T_ListType second (4,100);                       // four ints with value 100
    T_ListType third (second.begin(),second.end());  // iterating through second
    T_ListType fourth (third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    s32 myints[] = {16,2,77,29};
    T_ListType fifth (myints, myints + sizeof(myints) / sizeof(s32) );

    T_ListType::iterator itr = fifth.begin(); itr != fifth.end();

    CHECK(*itr++ == 16);
    CHECK(*itr++ == 2);
    CHECK(*itr++ == 77);
    CHECK(*itr++ == 29);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/Ctors", "")
  {
    testCtors<intListWithSize>();
    testCtors<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testOperatorEqual()
  {
    T_ListType first (3);      // list of 3 zero-initialized ints
    T_ListType second (5);     // list of 5 zero-initialized ints

    second = first;
    first = T_ListType();
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/operator=", "")
  {
  }

  template <typename T_ListType>
  void testBegin()
  {
    s32 myints[] = {75,23,65,42,13};
    T_ListType mylist (myints,myints+5);
    CHECK(mylist.size() == 5);

    T_ListType::iterator itr = mylist.begin();

    CHECK(*itr++ == 75);
    CHECK(*itr++ == 23);
    CHECK(*itr++ == 65);
    CHECK(*itr++ == 42);
    CHECK(*itr++ == 13);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/begin", "")
  {
    testBegin<intListWithSize>();
    testBegin<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testEnd()
  {
    s32 myints[] = {75,23,65,42,13};
    T_ListType mylist (myints,myints+5);
    CHECK(mylist.size() == 5);

    T_ListType::iterator itr = mylist.end();

    CHECK(*--itr == 13);
    CHECK(*--itr == 42);
    CHECK(*--itr == 65);
    CHECK(*--itr == 23);
    CHECK(*--itr == 75);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/end", "")
  {
    testEnd<intListWithSize>();
    testEnd<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testRBegin()
  {
    T_ListType myList;
    for (s32 i = 1; i <= 5; ++i) { myList.push_back(i); }

    T_ListType::reverse_iterator itr = myList.rbegin();

    CHECK(*itr == 5); ++itr;
    CHECK(*itr == 4); ++itr;
    CHECK(*itr == 3); ++itr;
    CHECK(*itr == 2); ++itr;
    CHECK(*itr == 1); ++itr;
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/rBegin", "")
  {
    testRBegin<intListWithSize>();
    testRBegin<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testREnd()
  {
    T_ListType myList;
    for (s32 i = 1; i <= 5; ++i) { myList.push_back(i); }

    T_ListType::reverse_iterator itr = myList.rend();

     --itr; CHECK(*itr == 1);
     --itr; CHECK(*itr == 2);
     --itr; CHECK(*itr == 3);
     --itr; CHECK(*itr == 4);
     --itr; CHECK(*itr == 5);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/rEnd", "")
  {
    testREnd<intListWithSize>();
    testREnd<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testEmpty()
  {
    T_ListType mylist;
    s32 sum (0);

    for (s32 i=1;i<=10;i++) mylist.push_back(i);

    while (!mylist.empty())
    {
      sum += mylist.front();
      mylist.pop_front();
    }

    CHECK(sum == 55);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/empty", "")
  {
    testEmpty<intListWithSize>();
    testEmpty<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testSize()
  {    T_ListType myints;
    CHECK(myints.size() == 0);

    for (int i=0; i<10; i++) myints.push_back(i);
    CHECK(myints.size() == 10);

    myints.insert (myints.begin(),10,100);
    CHECK(myints.size() == 20);

    myints.pop_back();
    CHECK(myints.size() == 19);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/size", "")
  {
    testSize<intListWithSize>();
    testSize<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testResize()
  {
    T_ListType mylist;

    unsigned int i;

    // set some initial content:
    for (i=1;i<10;i++) mylist.push_back(i);

    mylist.resize(5);
    mylist.resize(8,100);
    mylist.resize(12);

    T_ListType::iterator itr = mylist.begin();
    CHECK(*itr++ == 1);
    CHECK(*itr++ == 2);
    CHECK(*itr++ == 3);
    CHECK(*itr++ == 4);
    CHECK(*itr++ == 5);
    CHECK(*itr++ == 100);
    CHECK(*itr++ == 100);
    CHECK(*itr++ == 100);
    CHECK(*itr++ == 0);
    CHECK(*itr++ == 0);
    CHECK(*itr++ == 0);
    CHECK(*itr++ == 0);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/resize", "")
  {
    testResize<intListWithSize>();
    testResize<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testFront()
  {
    T_ListType mylist;

    mylist.push_back(77);
    mylist.push_back(22);

    mylist.front() -= mylist.back();

    CHECK(mylist.front() == 55);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/front", "")
  {
    testFront<intListWithSize>();
    testFront<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testBack()
  {
    T_ListType mylist;

    mylist.push_back(10);

    while (mylist.back() != 0)
    {
      mylist.push_back(mylist.back() - 1);
    }

    T_ListType::iterator itr = mylist.begin();

    CHECK(*itr++ == 10);
    CHECK(*itr++ == 9);
    CHECK(*itr++ == 8);
    CHECK(*itr++ == 7);
    CHECK(*itr++ == 6);
    CHECK(*itr++ == 5);
    CHECK(*itr++ == 4);
    CHECK(*itr++ == 3);
    CHECK(*itr++ == 2);
    CHECK(*itr++ == 1);
    CHECK(*itr++ == 0);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/back", "")
  {
    testBack<intListWithSize>();
    testBack<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testAssign()
  {
    T_ListType first, second;

    first.assign(7, 100);
    second.assign(first.begin(), first.end());

    s32 myints[] = {1776, 7, 4};
    first.assign(myints, myints + 3);

    CHECK(first.size() == 3);
    CHECK(second.size() == 7);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/assign", "")
  {
    testAssign<intListWithSize>();
    testAssign<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testPushFront()
  {
    T_ListType mylist(2, 100);
    mylist.push_front(200);
    mylist.push_front(300);

    T_ListType::iterator itr = mylist.begin();

    CHECK(*itr++ == 300);
    CHECK(*itr++ == 200);
    CHECK(*itr++ == 100);
    CHECK(*itr++ == 100);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/push_front", "")
  {
    testPushFront<intListWithSize>();
    testPushFront<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testPopFront()
  {
    T_ListType mylist;
    mylist.push_back(100);
    mylist.push_back(200);
    mylist.push_back(300);

    CHECK(mylist.front() == 100);
    mylist.pop_front();
    CHECK(mylist.front() == 200);
    mylist.pop_front();
    CHECK(mylist.front() == 300);
    mylist.pop_front();

    CHECK(mylist.size() == 0);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/pop_front", "")
  {
    testPopFront<intListWithSize>();
    testPopFront<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testPushBack()
  {
    T_ListType mylist;

    mylist.push_back(5);
    mylist.push_back(10);
    mylist.push_back(50);
    mylist.push_back(2);

    CHECK(mylist.size() == 4);

    T_ListType::iterator itr = mylist.begin();

    CHECK(*itr++ == 5);
    CHECK(*itr++ == 10);
    CHECK(*itr++ == 50);
    CHECK(*itr++ == 2);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/push_back", "")
  {
    testPushBack<intListWithSize>();
    testPushBack<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testPopBack()
  {
    T_ListType mylist;
    s32 sum(0);

    mylist.push_back(100);
    mylist.push_back(200);
    mylist.push_back(300);

    while (!mylist.empty())
    {
      sum += mylist.back();
      mylist.pop_back();
    }

    CHECK(sum == 600);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/pop_back", "")
  {
    testPopBack<intListWithSize>();
    testPopBack<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testInsert()
  {
    T_ListType mylist;
    T_ListType::iterator itr;

    for (s32 i = 1; i <= 5; ++i) mylist.push_back(i);

    itr = mylist.begin();
    ++itr;
    CHECK(*itr == 2);

    mylist.insert(itr, 10);
    mylist.insert(itr, 2, 20);
    --itr;
    CHECK(*itr++ == 20);
    CHECK(*itr == 2);
    --itr;

    Array<s32> myvector(2, 30);
    mylist.insert(itr, myvector.begin(), myvector.end());

    itr = mylist.begin();
    CHECK(*itr++ == 1);
    CHECK(*itr++ == 10);
    CHECK(*itr++ == 20);
    CHECK(*itr++ == 30);
    CHECK(*itr++ == 30);
    CHECK(*itr++ == 20);
    CHECK(*itr++ == 2);
    CHECK(*itr++ == 3);
    CHECK(*itr++ == 4);
    CHECK(*itr++ == 5);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/testInsert", "")
  {
    testInsert<intListWithSize>();
    testInsert<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testErase()
  {
    u32 i;
    T_ListType mylist;
    T_ListType::iterator itr1, itr2;

    for (i = 1; i < 10; ++i) mylist.push_back(i * 10);

    itr1 = itr2 = mylist.begin();
    advance(itr2, 6);
    CHECK(*itr2 == 70);
    ++itr1;
    CHECK(*itr1 == 20);

    itr1 = mylist.erase(itr1);
    CHECK(*itr1 == 30);

    itr2 = mylist.erase(itr2);
    CHECK(*itr2 == 80);

    ++itr1;
    CHECK(*itr1 == 40);
    --itr2;
    CHECK(*itr2 == 60);

    itr1 = mylist.erase(itr1, itr2);
    CHECK(*itr1 == 60);
    CHECK(*itr1 == *itr2);

    itr1 = mylist.begin();
    CHECK(*itr1++ == 10);
    CHECK(*itr1++ == 30);
    CHECK(*itr1++ == 60);
    CHECK(*itr1++ == 80);
    CHECK(*itr1++ == 90);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/erase", "")
  {
    testErase<intListWithSize>();
    testErase<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testSwap()
  {
    T_ListType first(3, 100);
    T_ListType second(5, 200);
    T_ListType::iterator itr;

    first.swap(second);

    itr = first.begin();
    CHECK(*itr++ == 200);
    CHECK(*itr++ == 200);
    CHECK(*itr++ == 200);
    CHECK(*itr++ == 200);
    CHECK(*itr++ == 200);

    itr = second.begin();
    CHECK(*itr++ == 100);
    CHECK(*itr++ == 100);
    CHECK(*itr++ == 100);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/testSwap", "")
  {
    testSwap<intListWithSize>();
    testSwap<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testClear()
  {
    T_ListType mylist;
    T_ListType::iterator itr;

    mylist.push_back(100);
    mylist.push_back(200);
    mylist.push_back(300);

    itr = mylist.begin();
    CHECK(*itr++ == 100);
    CHECK(*itr++ == 200);
    CHECK(*itr++ == 300);

    mylist.clear();
    mylist.push_back(1101);
    mylist.push_back(2202);

    itr = mylist.begin();
    CHECK(*itr++ == 1101);
    CHECK(*itr++ == 2202);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/clear", "")
  {
    testClear<intListWithSize>();
    testClear<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testSplice()
  {
    T_ListType mylist1, mylist2;
    T_ListType::iterator it;

    // set some initial values:
    for (s32 i=1; i<=4; i++)
      mylist1.push_back(i);      // mylist1: 1 2 3 4

    for (s32 i=1; i<=3; i++)
      mylist2.push_back(i*10);   // mylist2: 10 20 30

    it = mylist1.begin();
    ++it;                         // points to 2

    mylist1.splice (it, mylist2); // mylist1: 1 10 20 30 2 3 4
    // mylist2 (empty)
    // "it" still points to 2 (the 5th element)

    mylist2.splice (mylist2.begin(),mylist1, it);
    // mylist1: 1 10 20 30 3 4
    // mylist2: 2
    // "it" is now invalid.
    CHECK(mylist2.size() == 1);
    it = mylist1.begin();
    tloc::advance(it,3);                // "it" points now to 30

    mylist1.splice ( mylist1.begin(), mylist1, it, mylist1.end());
    // mylist1: 30 3 4 1 10 20

    it = mylist1.begin();
    CHECK(mylist1.size() == 6);
    CHECK(*it++ == 30);
    CHECK(*it++ == 3);
    CHECK(*it++ == 4);
    CHECK(*it++ == 1);
    CHECK(*it++ == 10);
    CHECK(*it++ == 20);

    it = mylist2.begin();
    CHECK(mylist2.size() == 1);
    CHECK(*it++ == 2);
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/splice", "")
  {
    testSplice<intListWithSize>();
    testSplice<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testRemove()
  {
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/remove", "")
  {
    testRemove<intListWithSize>();
    testRemove<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testRemoveIf()
  {
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/removeif", "")
  {
    testRemoveIf<intListWithSize>();
    testRemoveIf<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testUnique()
  {
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/unique", "")
  {
    testUnique<intListWithSize>();
    testUnique<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testMerge()
  {
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/merge", "")
  {
    testMerge<intListWithSize>();
    testMerge<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testSort()
  {
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/sort", "")
  {
    testSort<intListWithSize>();
    testSort<intListWithoutSize>();
  }

  template <typename T_ListType>
  void testReverse()
  {
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/reverse", "")
  {
    testReverse<intListWithSize>();
    testReverse<intListWithoutSize>();
  }

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/insert", "")
  {
    intListNoSize.insert(intListNoSize.begin(), 5);

    List<s32>::iterator itr = intListNoSize.begin();
    CHECK( *itr == 5);

    intListNoSize.insert(itr, 2, 10);
    itr = intListNoSize.begin();
    CHECK( *itr++ == 10);
    CHECK( *itr++ == 10);
    CHECK( *itr == 5);

    s32 rawArray[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    intListNoSize.insert(itr, rawArray, rawArray + 10);

    itr = intListNoSize.begin();
    CHECK( *itr++ == 10);
    CHECK( *itr++ == 10);
    CHECK( *itr++ == 0);
    CHECK( *itr++ == 1);
    CHECK( *itr++ == 2);
    CHECK( *itr++ == 3);
    CHECK( *itr++ == 4);
    CHECK( *itr++ == 5);
    CHECK( *itr++ == 6);
    CHECK( *itr++ == 7);
    CHECK( *itr++ == 8);
    CHECK( *itr++ == 9);
    CHECK( *itr == 5);

    CHECK(intListNoSize.size() == 13);

    intListNoSize.clear();

    CHECK(intListNoSize.size() == 0);

    intListNoSize.push_front(99);
    CHECK(intListNoSize.size() == 1);
    CHECK(*(intListNoSize.begin()) == 99);
  }
};
