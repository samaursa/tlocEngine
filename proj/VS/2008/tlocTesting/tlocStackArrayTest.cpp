#include "tlocTestCommon.h"

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocTypes.inl"
#include "tlocCore/tlocStackArray.h"
#include "tlocCore/tlocStackArray.inl"

namespace TestingStackArray
{
  USING_TLOC;
  using namespace core;

  class SomeClass
  {
  public:
    tl_int dummy;
  };

  struct StackArrayFixture
  {
    StackArray<SomeClass, 10> someClass, someClass2, someClass3;
    StackArray<tl_int, 20> ints, ints2, ints3;
  };

  TEST_CASE_METHOD(StackArrayFixture, "Core/Container/StackArray/Ctors", "")
  {
    // Empty Vector of ints
    StackArray<tl_int, 4> first;

    // Four ints with value 50
    StackArray<tl_int, 4> second(4, 50);
    CHECK(second[0] == 50); CHECK(second[1] == 50);
    CHECK(second[2] == 50); CHECK(second[3] == 50);

    // Iterator copy through second
    StackArray<tl_int, 4> third(second.begin(), second.end());
    CHECK(third[0] == 50); CHECK(third[1] == 50);
    CHECK(third[2] == 50); CHECK(third[3] == 50);

    // A direct copy of third (while our capacity matches its capacity)
    StackArray<tl_int, 4> fourth (third);
    CHECK(fourth[0] == 50); CHECK(fourth[1] == 50);
    CHECK(fourth[2] == 50); CHECK(fourth[3] == 50);

    // A copy of fourth (while our capacity is larger than it)
    StackArray<tl_int, 10> fifth (fourth);
    CHECK(fifth[0] == 50); CHECK(fifth[1] == 50);
    CHECK(fifth[2] == 50); CHECK(fifth[3] == 50);

    // A copy of fifth (while our capacity is smaller than it)
    StackArray<tl_int, 5> sixth (fifth);
    CHECK(sixth[0] == 50); CHECK(sixth[1] == 50);
    CHECK(sixth[2] == 50); CHECK(sixth[3] == 50);

    // Four classes of dummy clases
    SomeClass fooClass;
    fooClass.dummy = 50;
    StackArray<SomeClass, 4> eighth(4, fooClass);
    CHECK(eighth[0].dummy == 50); CHECK(eighth[1].dummy == 50);
    CHECK(eighth[2].dummy == 50); CHECK(eighth[3].dummy == 50);

    // Empty Stack Array with a default size of two
    StackArray<tl_int, 4> seventh (2);
    CHECK(seventh.size() == 2);
    CHECK(seventh.capacity() == 4);

    // The iterator constructor can also be used to construct from arrays:
    tl_int myints[] = {11,6,22,14};
    StackArray<tl_int, 4> ninth(myints, myints + sizeof(myints) / sizeof(tl_int));

    CHECK(ninth[0] == 11);CHECK(ninth[1] == 6);
    CHECK(ninth[2] == 22);CHECK(ninth[3] == 14);
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Containers/StackArray/Push_back",
    "Test push_back functionality")
  {
  
  }

};