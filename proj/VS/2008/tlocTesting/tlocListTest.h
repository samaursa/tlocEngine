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

    List<s32, ListNode<s32, doubly_linked_tag>, List_Dynamic(), true> intListSize;
    List<s32, ListNode<s32, doubly_linked_tag>, List_Dynamic(), false> intListNoSize;
    List<SomeClass> classList;
  };

  //template <T_List>
  //void testCtors(

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/Ctors", "")
  {
    // constructors used in the same order as described above:
    intListWithSize first;                                // empty list of ints
    intListWithSize second (4,100);                       // four ints with value 100
    intListWithSize third (second.begin(),second.end());  // iterating through second
    intListWithSize fourth (third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    s32 myints[] = {16,2,77,29};
    intListWithSize fifth (myints, myints + sizeof(myints) / sizeof(s32) );
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
