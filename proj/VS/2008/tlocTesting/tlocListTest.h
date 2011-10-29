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
    List<s32, ListNode<s32, doubly_linked_tag>, List_Dynamic(), false>       intList;
    List<SomeClass> classList;
  };

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/Ctors", "")
  {
  }
  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/insert", "")
  {
    intList.insert(intList.begin(), 5);

    List<s32>::iterator itr = intList.begin();
    CHECK( *itr == 5);

    intList.insert(itr, 2, 10);
    itr = intList.begin();
    CHECK( *itr++ == 10);
    CHECK( *itr++ == 10);
    CHECK( *itr == 5);

    s32 rawArray[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    intList.insert(itr, rawArray, rawArray + 10);

    itr = intList.begin();
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

    CHECK(intList.size() == 13);
  }
};
