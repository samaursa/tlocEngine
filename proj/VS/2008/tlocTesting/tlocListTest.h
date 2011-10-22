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
    List<s32>       intList;
    List<SomeClass> classList;
  };

  TEST_CASE_METHOD(ListFixture, "Core/Containers/List/Ctors", "")
  {
    intList.insert(intList.begin(), 5);

    List<s32>::iterator itr = intList.begin();
    CHECK( *intList.begin() == 5);
  }
};
