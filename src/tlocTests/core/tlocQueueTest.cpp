#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTypes.inl.h>

#include <tlocCore/containers/tlocQueue.h>
#include <tlocCore/containers/tlocQueue.inl.h>

namespace TestingQueue
{
  using namespace tloc;
  using namespace core;
  using namespace core::containers;

  class SomeClass
  {
  public:
    int dummy;
  };

  struct QueueFixture
  {
    typedef Queue<s32> int_list_queue;

    Queue<SomeClass> someClassListQueue;
  };

#define FILL_INT_QUEUE_BY_AMOUNT(queueName, nTimes)\
  for (s32 i = 0; i < nTimes; ++i)\
  {\
  queueName.push(i);\
  }

#define EMPTY_QUEUE_BY_AMOUNT(queueName, nTimes)\
  for (s32 i = 0; i < nTimes; ++i)\
  {\
  queueName.pop();\
  }

#define CHECK_BACK_AND_FRONT_WHILE_FILLING_QUEUE_BY_AMOUNT(queueName, nTimes)\
  for (s32 i = 0; i < nTimes; ++i)\
  {\
  queueName.push(i);\
  CHECK(queueName.back() == i);\
  CHECK(queueName.front() == 0);\
  }

#define CHECK_BACK_AND_FRONT_WHILE_EMPTYING_QUEUE_BY_AMOUNT(queueName, nTimes)\
  for (s32 i = 0; i < nTimes; ++i)\
  {\
  CHECK(queueName.back() == nTimes - 1);\
  CHECK(queueName.front() == i);\
  queueName.pop();\
  }

  template <typename T_QueueType>
  void testCtors()
  {
    T_QueueType first;            // Default Constructor test
    T_QueueType second(first);    // Copy constructor with empty queue test

    T_QueueType tmp;              // Copy Constructor with a loaded queue test
    FILL_INT_QUEUE_BY_AMOUNT(tmp, 4);
    T_QueueType third(tmp);
    CHECK_BACK_AND_FRONT_WHILE_EMPTYING_QUEUE_BY_AMOUNT(third, 4);
  }

  TEST_CASE_METHOD(QueueFixture, "Core/Containers/Queue/Ctors",
    "Test default and copy constructor functionality")
  {
     testCtors<int_list_queue>();
  }

  template <typename T_QueueType>
  void testPush()
  {
    T_QueueType myQueue;
    CHECK_BACK_AND_FRONT_WHILE_FILLING_QUEUE_BY_AMOUNT(myQueue, 4);
    CHECK(myQueue.size() == 4);
  }

  TEST_CASE_METHOD(QueueFixture, "Core/Container/Queue/Push",
    "Test push functionality")
  {
    testPush<int_list_queue>();
  }

  template <typename T_QueueType>
  void testPop()
  {
    T_QueueType myQueue;
    FILL_INT_QUEUE_BY_AMOUNT(myQueue, 4);
    REQUIRE(myQueue.size() == 4);
    CHECK_BACK_AND_FRONT_WHILE_EMPTYING_QUEUE_BY_AMOUNT(myQueue, 4);
    CHECK(myQueue.empty());
  }

  TEST_CASE_METHOD(QueueFixture, "Core/Container/Queue/Pop",
    "Test pop functionality")
  {
    testPop<int_list_queue>();
  }

#undef FILL_INT_QUEUE_BY_AMOUNT
#undef EMPTY_QUEUE_BY_AMOUNT
#undef CHECK_BACK_AND_FRONT_WHILE_FILLING_QUEUE_BY_AMOUNT
#undef CHECK_BACK_AND_FRONT_WHILE_EMPTYING_QUEUE_BY_AMOUNT

};