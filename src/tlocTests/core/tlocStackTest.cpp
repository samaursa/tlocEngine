#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTypes.inl.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl.h>

#include <tlocCore/containers/tlocStack.h>
#include <tlocCore/containers/tlocStack.inl.h>

namespace TestingStack
{
  using namespace tloc;
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

#undef FILL_INT_STACK_BY_AMOUNT
#undef EMPTY_STACK_BY_AMOUNT
#undef CHECK_TOP_WHILE_FILLING_INT_STACK_BY_AMOUNT
#undef CHECK_TOP_WHILE_EMPTYING_STACK_BY_AMOUNT

};