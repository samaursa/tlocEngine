#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTypes.inl>
#include <tlocCore/containers/tlocArrayFixed.h>
#include <tlocCore/containers/tlocArrayFixed.inl>

namespace TestingStackArray
{
  using namespace tloc;
  using namespace core;
  using namespace core::containers;

  class SomeClass
  {
  public:
    tl_int dummy;
  };

  struct StackArrayFixture
  {
    ArrayFixed<SomeClass, 100> someClass, someClass2, someClass3;
    ArrayFixed<tl_int, 100> ints, ints2, ints3;
  };

#define FILL_INT_STACK_ARRAY_BY_PUSH(a_arrayName, a_nTimes) \
  for (tl_size i = 0; i < a_nTimes; ++i) \
  { \
  a_arrayName.push_back((tl_int)i); \
  }

#define CHECK_STACK_ARRAY_BY_INDEX(a_type, a_arrayName, a_nTimes) \
  for (tl_size i = 0; i < a_nTimes; ++i) \
  { \
  CHECK(a_arrayName[i] == static_cast<a_type>(i)); \
  CHECK(a_arrayName.at(i) == static_cast<a_type>(i)); \
  }

#define CHECK_STACK_ARRAY_BY_POP_BACK(a_type, a_arrayName, a_nTimes) \
  a_type poppedOut; \
  for (tl_int i = a_nTimes - 1; i >= 0; --i) \
  { \
  a_arrayName.pop_back(poppedOut); \
  CHECK(poppedOut == static_cast<a_type>(i)); \
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Container/StackArray/Ctors", "")
  {
    // Empty Vector of ints
    ArrayFixed<tl_int, 4> first;

    // Four ints with value 50
    ArrayFixed<tl_int, 4> second(4, 50);
    CHECK(second[0] == 50); CHECK(second[1] == 50);
    CHECK(second[2] == 50); CHECK(second[3] == 50);

    // Iterator copy through second
    ArrayFixed<tl_int, 4> third(second.begin(), second.end());
    CHECK(third[0] == 50); CHECK(third[1] == 50);
    CHECK(third[2] == 50); CHECK(third[3] == 50);

    // A direct copy of third (while our capacity matches its capacity)
    ArrayFixed<tl_int, 4> fourth (third);
    CHECK(fourth[0] == 50); CHECK(fourth[1] == 50);
    CHECK(fourth[2] == 50); CHECK(fourth[3] == 50);

    // A copy of fourth (while our capacity is larger than it)
    ArrayFixed<tl_int, 10> fifth (fourth);
    CHECK(fifth[0] == 50); CHECK(fifth[1] == 50);
    CHECK(fifth[2] == 50); CHECK(fifth[3] == 50);

    // A copy of fifth (while our capacity is smaller than it)
    ArrayFixed<tl_int, 5> sixth (fifth);
    CHECK(sixth[0] == 50); CHECK(sixth[1] == 50);
    CHECK(sixth[2] == 50); CHECK(sixth[3] == 50);

    // Four classes of dummy clases
    SomeClass fooClass;
    fooClass.dummy = 50;
    ArrayFixed<SomeClass, 4> eighth(4, fooClass);
    CHECK(eighth[0].dummy == 50); CHECK(eighth[1].dummy == 50);
    CHECK(eighth[2].dummy == 50); CHECK(eighth[3].dummy == 50);

    // Empty Stack Array with a default size of two
    ArrayFixed<tl_int, 4> seventh (2);
    CHECK(seventh.size() == 2);
    CHECK(seventh.capacity() == 4);

    // The iterator constructor can also be used to construct from arrays:
    tl_int myints[] = {11,6,22,14};
    ArrayFixed<tl_int, 4> ninth(myints, myints + sizeof(myints) / sizeof(tl_int));

    CHECK(ninth[0] == 11);CHECK(ninth[1] == 6);
    CHECK(ninth[2] == 22);CHECK(ninth[3] == 14);
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Containers/StackArray/Push_back",
    "Test push_back functionality")
  {
    ints.push_back(7);
    CHECK(ints[0] == 7);

    ints.push_back(3);
    CHECK(ints[0] == 7);
    CHECK(ints[1] == 3);

    FILL_INT_STACK_ARRAY_BY_PUSH(ints2, 100);
    CHECK_STACK_ARRAY_BY_INDEX(tl_int, ints2, 100);
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Containers/StackArray/Pop_back",
    "Test pop_back functionality")
  {
    FILL_INT_STACK_ARRAY_BY_PUSH(ints, 100);

    REQUIRE(ints.size() == 100);

    ints.pop_back();

    CHECK(ints.size() == 99);

    tl_int toSave;
    ints.pop_back(toSave);

    CHECK(toSave == 98);

    CHECK_STACK_ARRAY_BY_POP_BACK(tl_int, ints, 98);

    CHECK(ints.empty());
  }

  template <typename T_StackArray1, typename T_StackArray2>
  void TestAssignmentOperator()
  {
    typedef T_StackArray1 stack_array_type1;
    typedef T_StackArray2 stack_array_type2;

    stack_array_type1 copyToTestArray;
    FILL_INT_STACK_ARRAY_BY_PUSH(copyToTestArray, 20);

    REQUIRE(copyToTestArray.size() == 20);

    stack_array_type2 copyFromTestArray;
    FILL_INT_STACK_ARRAY_BY_PUSH(copyFromTestArray, 30);

    copyToTestArray = copyFromTestArray;

    REQUIRE(copyToTestArray.size() == 30);
    CHECK_STACK_ARRAY_BY_INDEX(tl_int, copyToTestArray, 30);

    copyFromTestArray.clear();
    FILL_INT_STACK_ARRAY_BY_PUSH(copyFromTestArray, 10);

    copyToTestArray = copyFromTestArray;

    REQUIRE(copyToTestArray.size() == 10);
    CHECK_STACK_ARRAY_BY_INDEX(tl_int, copyToTestArray, 10);

    copyFromTestArray.clear();

    copyToTestArray = copyFromTestArray;

    REQUIRE(copyToTestArray.size() == 0);
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Container/StackArray/AssignmentOperator",
    "Test assigning a StackArray to another")
  {
    typedef ArrayFixed<tl_int, 30>      stack_array_30;
    typedef ArrayFixed<tl_int, 50>      stack_array_50;

    TestAssignmentOperator<stack_array_30, stack_array_30>();
    TestAssignmentOperator<stack_array_30, stack_array_50>();
    TestAssignmentOperator<stack_array_50, stack_array_30>();
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Containers/StackArray/ElementAccess",
    "Test element access functionality")
  {
    FILL_INT_STACK_ARRAY_BY_PUSH(ints, 4);
    CHECK(ints.size() == 4);

    CHECK_STACK_ARRAY_BY_INDEX(tl_int, ints, 4);
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Containers/StackArray/Accessors",
    "Test accessors")
  {
    FILL_INT_STACK_ARRAY_BY_PUSH(ints, 100);

    ArrayFixed<tl_int, 100>::iterator itr = ints.begin();
    ArrayFixed<tl_int, 100>::iterator itrEnd = ints.end();

    tl_size count = 0;
    while (itr != itrEnd)
    {
      CHECK(static_cast<tl_int>(count++) == *itr);
      ++itr;
    }

    CHECK(ints.size() == 100);
  }

  template <typename T_StackArray>
  void TestEraseAtPosition(tl_size a_index,
                           tl_size a_newSizeOfArray)
  {
    T_StackArray theStackArray;
    theStackArray.clear();
    FILL_INT_STACK_ARRAY_BY_PUSH(theStackArray, a_newSizeOfArray);

    CHECK(theStackArray.size() == a_newSizeOfArray);

    typename T_StackArray::iterator itr;
    itr = theStackArray.erase(theStackArray.begin() + a_index);
    if (itr != theStackArray.end())
    {
      CHECK(*itr == static_cast<tl_int>(a_index + 1));
    }

    typename T_StackArray::iterator itrEnd;
    itr = theStackArray.begin();
    itrEnd = theStackArray.end();

    for (tl_size count = 0; itr != itrEnd; ++itr, ++count)
    {
      if (count == a_index)
      {
        ++count;
      }
      CHECK(*itr == static_cast<tl_int>(count));
    }
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Containers/StackArray/Erase",
    "Test all erase functions")
  {
    //------------------------------------------------------------------------
    // Erase at position

    // Creates a new StackArray each iteration with the same capacity and size
    // and erases a single element in an iterative fashion.
    const tl_size sizeOfArray = 10;
    for (tl_size i = 0; i < sizeOfArray; ++i)
    {
      TestEraseAtPosition<ArrayFixed<tl_int, sizeOfArray> >(i, sizeOfArray);
    }

    //------------------------------------------------------------------------
    // Erase range

    FILL_INT_STACK_ARRAY_BY_PUSH(ints, 10);
    CHECK(ints.size() == 10);

    ArrayFixed<tl_int, 100>::iterator itr;
    itr = ints.erase(ints.begin(), ints.end());
    CHECK(ints.empty());

    FILL_INT_STACK_ARRAY_BY_PUSH(ints, 20);
    CHECK(ints.size() == 20);
    itr = ints.erase(ints.begin(), ints.begin() + 10);
    CHECK(*itr == 10);
    CHECK(itr == ints.begin());
    CHECK(ints.size() == 10);

    ArrayFixed<tl_int, 100>::iterator itrEnd;
    itrEnd = ints.end();
    for (tl_size count = 10; itr != itrEnd; ++itr, ++count)
    {
      CHECK(*itr == static_cast<tl_int>(count));
    }
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Containers/StackArray/Clear",
    "Test the clear function")
  {
    ArrayFixed<tl_size, 9001> theStackArray;
    tl_size sizeOfStackArray = 9001;
    FILL_INT_STACK_ARRAY_BY_PUSH(theStackArray, sizeOfStackArray);

    CHECK(theStackArray.size() == sizeOfStackArray);
    theStackArray.clear();
    CHECK(theStackArray.size() == 0);
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Containers/StackArray/Insert",
    "Test the insert methods")
  {
    //------------------------------------------------------------------------
    // Insert single values

    FILL_INT_STACK_ARRAY_BY_PUSH(ints, 15);

    // Inserting to the end of the array
    for (tl_size i = 15; i < 30; ++i)
    {
      ints.insert(ints.end(), (tl_int)i);
    }

    CHECK(ints.size() == 30);

    CHECK_STACK_ARRAY_BY_INDEX(tl_int, ints, 30);

    // Inserting to the middle of the array
    ints.insert(ints.begin() + 4, 70);
    CHECK(ints.size() == 31);
    CHECK(ints[0] == 0);
    CHECK(ints[1] == 1);
    CHECK(ints[2] == 2);
    CHECK(ints[3] == 3);
    CHECK(ints[4] == 70);
    CHECK(ints[5] == 4);

    // Taking a value from the middle of the array and reinserting it
    ints.insert(ints.begin() + 2, ints[4]);
    CHECK(ints.size() == 32);
    CHECK(ints[0] == 0);
    CHECK(ints[1] == 1);
    CHECK(ints[2] == 70);
    CHECK(ints[3] == 2);
    CHECK(ints[4] == 3);
    CHECK(ints[5] == 70);
    CHECK(ints[6] == 4);

    //------------------------------------------------------------------------
    // Insert several values

    FILL_INT_STACK_ARRAY_BY_PUSH(ints2, 4);

    CHECK(ints2.size() == 4);

    ints2.insert(ints2.begin() + 2, 10, 40);

    CHECK(ints2[0] == 0);
    CHECK(ints2[1] == 1);

    for (tl_size i = 2; i < 10 +2; ++i)
    {
      CHECK(ints2[i] == 40);
    }

    CHECK(ints2[12] == 2);
    CHECK(ints2[13] == 3);
    CHECK(ints2.size() == 14);

    ints2.clear();
    ints2.push_back(0);
    ints2.insert(ints2.end(), 5, 80);

    CHECK(ints2[0] == 0);

    for (tl_size i = 1; i < 5 + 1; ++i)
    {
      CHECK(ints2[i] == 80);
    }

    //------------------------------------------------------------------------
    // Insert with iterator

    const tl_size sizeOfNums = 10;
    tl_int nums[sizeOfNums]  = {0,1,2,3,4,5,6,7,8,9};

    ints2.insert(ints2.begin(), nums, nums + sizeOfNums);

    CHECK_STACK_ARRAY_BY_INDEX(tl_int, ints2, sizeOfNums);
    CHECK(ints2[10] == 0);
    CHECK(ints2[11] == 80);
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Container/StackArray/FrontBackAccess",
    "Test front and back access")
  {
    FILL_INT_STACK_ARRAY_BY_PUSH(ints, 4);

    CHECK(ints.front() == 0);
    CHECK(ints.back() == 3);

    ints.erase(ints.begin());
    ints.erase(ints.end() - 1);

    CHECK(ints.front() == 1);
    CHECK(ints.back() == 2);
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Container/StackArray/Resize",
    "Test the resize methods")
  {
    tl_size arraySize = 10;
    FILL_INT_STACK_ARRAY_BY_PUSH(ints, arraySize);
    CHECK(ints.size() == arraySize);
    CHECK_STACK_ARRAY_BY_INDEX(tl_int, ints, arraySize);

    tl_size resizeSize = 5;
    ints.resize(resizeSize);
    CHECK(ints.size() == resizeSize);
    CHECK_STACK_ARRAY_BY_INDEX(tl_int, ints, resizeSize);

    resizeSize = 100;
    ints.resize(resizeSize);
    CHECK(ints.size() == resizeSize);
    CHECK_STACK_ARRAY_BY_INDEX(tl_int, ints, 5);
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Container/StackArray/Assign",
    "Test the assign function")
  {
    tl_int someArray[10] = {0,1,2,3,4,5,6,7,8,9};
    tl_int* itrBegin = someArray;
    tl_int* itrEnd = someArray + 10;

    ints.assign(itrBegin, itrEnd);
    CHECK(ints.size() == 10);

    CHECK_STACK_ARRAY_BY_INDEX(tl_int, ints, 10);
  }

  TEST_CASE_METHOD(StackArrayFixture, "Core/Container/StackArray/Swap",
    "Test the swap function")
  {
    ArrayFixed<tl_int, 50>  array50;
    ArrayFixed<tl_int, 50>  array50_2; array50_2.resize(50);
    ArrayFixed<tl_int, 70>  array70; array70.resize(50);

    FILL_INT_STACK_ARRAY_BY_PUSH(array50, 50);
    fill(array50_2.begin(), array50_2.end(), 15);

    fill(array70.begin(), array70.end(), 9);

    ArrayFixed<tl_int, 50>::iterator itr50 = array50.begin();
    ArrayFixed<tl_int, 50>::iterator itr50End = array50.end();
    array50.swap(array50_2);

    CHECK(array50.begin() == itr50);
    CHECK(array50.end() == itr50End);

    for (tl_int i = 0; i < 50; ++i)
    {
      CHECK(array50[i] == 15);
      CHECK(array50_2[i] == i);
    }

    array50.swap(array70);

    for (tl_int i = 0; i < 50; ++i)
    {
      CHECK(array50[i] == 9);
    }
  }

};