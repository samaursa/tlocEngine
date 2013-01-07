#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTypes.inl>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl>

#include <tlocCore/containers/tlocStack.h>
#include <tlocCore/containers/tlocStack.inl>

namespace TestingStack
{
  USING_TLOC;
  using namespace core;
  using namespace core::containers;

  class SomeClass
  {
  public:
    int dummy;
  };

  struct StackFixture
  {
    typedef Stack<s32> int_list_stack;
    typedef Stack<s32, Array<s32> > int_array_stack;

    Stack<SomeClass> someClassListStack;
  };

#define FILL_INT_STACK_BY_AMOUNT(stackName, nTimes)\
  for (s32 i = 0; i < nTimes; ++i)\
  {\
  stackName.push(i);\
  }

#define EMPTY_STACK_BY_AMOUNT(stackName, nTimes)\
  for (s32 i = 0; i < nTimes; ++i)\
  {\
  stackName.pop();\
  }

#define CHECK_TOP_WHILE_FILLING_INT_STACK_BY_AMOUNT(stackName, nTimes)\
  for (s32 i = 0; i < nTimes; ++i)\
  {\
  stackName.push(i);\
  CHECK(stackName.top() == i);\
  }

#define CHECK_TOP_WHILE_EMPTYING_STACK_BY_AMOUNT(stackName, nTimes)\
  for (s32 i = nTimes - 1; i >= 0; --i)\
  {\
  CHECK(stackName.top() == i);\
  stackName.pop();\
  }


  template <typename T_StackType>
  void testCtors()
  {
    T_StackType first;              // empty stack constructor test
    T_StackType second(first);      // copy constructor with empty stack test

    T_StackType tmp;                // copy constructor with a loaded stack test
    FILL_INT_STACK_BY_AMOUNT(tmp, 4);
    T_StackType third(tmp);
    CHECK_TOP_WHILE_EMPTYING_STACK_BY_AMOUNT(third, 4);
  }

  TEST_CASE_METHOD(StackFixture, "Core/Containers/Stack/Ctors",
    "Test default and copy constructor functionality")
  {
    testCtors<int_list_stack>();
    testCtors<int_array_stack>();
  }

  template <typename T_StackType>
  void testPush()
  {
    T_StackType myStack;
    CHECK_TOP_WHILE_FILLING_INT_STACK_BY_AMOUNT(myStack, 4);
    CHECK(myStack.size() == 4);
  }

  TEST_CASE_METHOD(StackFixture, "Core/Containers/Stack/Push",
    "Test push functionality")
  {
    testPush<int_list_stack>();
    testPush<int_array_stack>();
  }

  template <typename T_StackType>
  void testPop()
  {
    T_StackType myStack;
    FILL_INT_STACK_BY_AMOUNT(myStack, 4);
    REQUIRE(myStack.size() == 4);
    CHECK_TOP_WHILE_EMPTYING_STACK_BY_AMOUNT(myStack, 4);
    CHECK(myStack.empty());
  }

  TEST_CASE_METHOD(StackFixture, "Core/Containers/Stack/Pop",
    "Test pop functionality")
  {
    testPop<int_list_stack>();
    testPop<int_array_stack>();
  }

  template <typename T_StackType>
  void testGetContainer()
  {
    T_StackType myStack;
    FILL_INT_STACK_BY_AMOUNT(myStack, 4);

    typename T_StackType::container_type myContainer
      = myStack._Get_container();
    typename T_StackType::container_type::iterator itr
      = myContainer.begin();

    CHECK(*itr++ == 0);
    CHECK(*itr++ == 1);
    CHECK(*itr++ == 2);
    CHECK(*itr++ == 3);
  }

  /*template <>
  void testGetContainer<StackFixture::int_list_stack>()
  {
    StackFixture::int_list_stack myStack;
    FILL_INT_STACK_BY_AMOUNT(myStack, 4);

    List<s32> myList = myStack._Get_container();

    List<s32>::iterator itr = myList.begin();

    CHECK(*itr++ == 0);
    CHECK(*itr++ == 1);
    CHECK(*itr++ == 2);
    CHECK(*itr++ == 3);
  }

  template <>
  void testGetContainer<StackFixture::int_array_stack>()
  {
    StackFixture::int_array_stack myStack;
    FILL_INT_STACK_BY_AMOUNT(myStack, 4);

    Array<s32> myArray = myStack._Get_container();

    CHECK(myArray[0] == 0);
    CHECK(myArray[1] == 1);
    CHECK(myArray[2] == 2);
    CHECK(myArray[3] == 3);
  }*/

  TEST_CASE_METHOD(StackFixture, "Core/Containers/Stack/GetContainer",
    "Test grabbing container from stack and container contents")
  {
    testGetContainer<int_list_stack>();
    testGetContainer<int_array_stack>();
  }

#undef FILL_INT_STACK_BY_AMOUNT
#undef EMPTY_STACK_BY_AMOUNT
#undef CHECK_TOP_WHILE_FILLING_INT_STACK_BY_AMOUNT
#undef CHECK_TOP_WHILE_EMPTYING_STACK_BY_AMOUNT

};