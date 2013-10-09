#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>
#include <tlocCore/memory/tlocMemory.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTypes.inl.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl.h>

namespace TestingArray
{
  using namespace tloc;
  using namespace core;
  using namespace core::containers;

  class SomeClass
  {
  public:
    int dummy;
  };

  struct ArrayFixture
  {
    Array<SomeClass> someClass, someClass2, someClass3;
    Array<s32> ints, ints2, ints3;
  };

#define FILL_INT_ARRAY_BY_PUSH(arrayName, nFrom, nTo) \
  for (u32 i = nFrom; i < nTo; ++i)\
  {\
  arrayName.push_back(i);\
  }\

#define FILL_INT_ARRAY_BY_INDEX(arrayName, nFrom, nTo) \
  for (u32 i = nFrom; i < nTo; ++i)\
  {\
  arrayName[i] = i;\
  }\

#define FILL_TEST_CLASS_ARRAY_BY_PUSH(arrayName, nFrom, nTo) \
  for (u32 i = nFrom; i < nTo; ++i)\
  {\
  SomeClass test;\
  test.dummy = i;\
  arrayName.push_back(test);\
  }\

#define CHECK_ARRAY_BY_INDEX(arrayName, nFrom, nTo) \
  for (u32 i = nFrom; i < nTo; ++i)\
  {\
  CHECK(arrayName[i] == (s32)i);\
  }

#define CHECK_TEST_CLASS_ARRAY_BY_INDEX(arrayName, nFrom, nTo) \
  for (int i = nFrom; i < nTo; ++i)\
  {\
  CHECK(arrayName[i].dummy == i);\
  }\

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Ctors", "")
  {
    Array<s32> first;                                // empty vector of ints
    Array<s32> second (4,100);                       // four ints with value 100
    CHECK(second[0] == 100); CHECK(second[1] == 100);
    CHECK(second[2] == 100); CHECK(second[3] == 100);
    Array<s32> third (second.begin(),second.end());  // iterating through second
    CHECK(third[0] == 100); CHECK(third[1] == 100);
    CHECK(third[2] == 100); CHECK(third[3] == 100);
    Array<s32> fourth (third);                       // a copy of third
    CHECK(fourth[0] == 100); CHECK(fourth[1] == 100);
    CHECK(fourth[2] == 100); CHECK(fourth[3] == 100);

    SomeClass fooClass;
    fooClass.dummy = 50;
    Array<SomeClass> fifth(4, fooClass);
    CHECK(fifth[0].dummy == 50); CHECK(fifth[1].dummy == 50);
    CHECK(fifth[2].dummy == 50); CHECK(fifth[3].dummy == 50);

    Array<s32> sixth (10);
    CHECK(sixth.size() == 10);
    CHECK(sixth.capacity() == 10);

    // the iterator constructor can also be used to construct from arrays:
    s32 myints[] = {16,2,77,29};
    Array<s32> seventh (myints, myints + sizeof(myints) / sizeof(s32) );

    CHECK(seventh[0] == 16); CHECK(seventh[1] == 2);
    CHECK(seventh[2] == 77); CHECK(seventh[3] == 29);
  }


  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Push_back",
    "Test push_back functionality")
  {
    int a, b = 0;

    ints.push_back(5);
    a = ints[0];
    CHECK(a == 5);

    ints.push_back(10);
    a = ints[0];
    CHECK(a == 5);
    b = ints[1];
    CHECK(b == 10);
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Pop_back",
    "Test pop_back functionality")
  {
    FILL_INT_ARRAY_BY_PUSH(ints, 0, 100);

    REQUIRE(ints.size() == 100);

    ints.pop_back();

    CHECK(ints.size() == 99);

    s32 toSave;
    ints.pop_back(toSave);

    CHECK(toSave == 98);

    u32 arraySize = (u32)ints.size();
    for (u32 i = 0; i < arraySize; ++i)
    {
      ints.pop_back();
    }

    CHECK(ints.size() == 0);
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/AssignmentOperator",
    "Test assigning an array to another")
  {
    /*Array<u32> copyFromSmallArray, copyFromMedArray, copyFromLargeArray;
    Array<u32> copyToSmallArray, copyToMedArray, copyToLargeArray;
    FILL_INT_ARRAY_BY_PUSH(copyFromSmallArray, 0, 10);
    FILL_INT_ARRAY_BY_PUSH(copyFromMedArray, 0, 20);
    FILL_INT_ARRAY_BY_PUSH(copyFromLargeArray, 0, 30);*/

    Array<u32> copyToTestArray;
    FILL_INT_ARRAY_BY_PUSH(copyToTestArray, 0, 5);

    REQUIRE(copyToTestArray.capacity() == 8);
    REQUIRE(copyToTestArray.size() == 5);

    Array<u32> copyFromTestArray;

    FILL_INT_ARRAY_BY_PUSH(copyFromTestArray, 0, 20);

    copyToTestArray = copyFromTestArray;

    CHECK_ARRAY_BY_INDEX(copyToTestArray, 0, 20);

    REQUIRE(copyToTestArray.capacity() == 20);
    REQUIRE(copyToTestArray.size() == 20);

    copyFromTestArray.clear();
    FILL_INT_ARRAY_BY_PUSH(copyFromTestArray, 0, 10);

    copyToTestArray = copyFromTestArray;

    CHECK_ARRAY_BY_INDEX(copyToTestArray, 0, 10);

    REQUIRE(copyToTestArray.capacity() == 20);
    REQUIRE(copyToTestArray.size() == 10);

    copyFromTestArray.clear();
    FILL_INT_ARRAY_BY_PUSH(copyFromTestArray, 0, 15);

    copyToTestArray = copyFromTestArray;

    CHECK_ARRAY_BY_INDEX(copyToTestArray, 0, 15);

    REQUIRE(copyToTestArray.capacity() == 20);
    REQUIRE(copyToTestArray.size() == 15);

    //TODO: Turn into function later

    Array<SomeClass> copyToTestClassArray;
    FILL_TEST_CLASS_ARRAY_BY_PUSH(copyToTestClassArray, 0, 5);

    REQUIRE(copyToTestClassArray.capacity() == 8);
    REQUIRE(copyToTestClassArray.size() == 5);

    Array<SomeClass> copyFromTestClassArray;

    FILL_TEST_CLASS_ARRAY_BY_PUSH(copyFromTestClassArray, 0, 20);

    copyToTestClassArray = copyFromTestClassArray;

    CHECK_TEST_CLASS_ARRAY_BY_INDEX(copyToTestClassArray, 0, 20);

    REQUIRE(copyToTestClassArray.capacity() == 20);
    REQUIRE(copyToTestClassArray.size() == 20);

    copyFromTestClassArray.clear();
    FILL_TEST_CLASS_ARRAY_BY_PUSH(copyFromTestClassArray, 0, 10);

    copyToTestClassArray = copyFromTestClassArray;

    CHECK_TEST_CLASS_ARRAY_BY_INDEX(copyToTestClassArray, 0, 10);

    REQUIRE(copyToTestClassArray.capacity() == 20);
    REQUIRE(copyToTestClassArray.size() == 10);

    copyFromTestClassArray.clear();
    FILL_TEST_CLASS_ARRAY_BY_PUSH(copyFromTestClassArray, 0, 15);

    copyToTestClassArray = copyFromTestClassArray;

    CHECK_TEST_CLASS_ARRAY_BY_INDEX(copyToTestClassArray, 0, 15);

    REQUIRE(copyToTestClassArray.capacity() == 20);
    REQUIRE(copyToTestClassArray.size() == 15);

    /*smallArray = largeArray;

    CHECK_ARRAY_BY_INDEX(smallArray, 0, 30);*/
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/ElementAccess",
    "Test element access functionality")
  {
    u32 startElement = 0;
    u32 amountToPush = 4;
    FILL_INT_ARRAY_BY_PUSH(ints, startElement, amountToPush);
    CHECK(ints.size() == amountToPush);

    for (u32 i = startElement; i < ints.size(); ++i)
    {
      CHECK(ints[i] == (s32)i);
      CHECK(ints.at(i) == (s32)i);
    }
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Accessors",
    "Test accessors")
  {
    FILL_INT_ARRAY_BY_PUSH(ints, 0, 100);

    {
      Array<s32>::iterator itr = ints.begin();
      Array<s32>::iterator itrEnd = ints.end();

      s32 count = 0;
      while (itr != itrEnd)
      {
        CHECK(count == *itr);
        ++count;
        ++itr;
      }
    }

    CHECK(ints.size() == 100);

    {
      Array<s32>::reverse_iterator  rItr    = ints.rbegin();
      Array<s32>::reverse_iterator  rItrEnd = ints.rend();

      s32 count = 100;
      while (rItr != rItrEnd)
      {
        --count;
        CHECK(count == *rItr);
        ++rItr;
      }
    }

    CHECK(ints.size() == 100);

  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Erase",
    "Test all erase functions")
  {
    //------------------------------------------------------------------------
    // Erase at position

    FILL_INT_ARRAY_BY_PUSH(ints, 0, 10);

    CHECK(ints.size() == 10);
    Array<s32>::iterator itr = ints.erase(ints.begin() + 4);
    CHECK(ints.size() == 9);
    CHECK(*itr == 5);

    for (u32 i = 4; i < 9; ++i)
    {
      CHECK(ints[i] == (s32)i + 1);
    }

    //------------------------------------------------------------------------
    // Erase range

    ints.push_back(0); // Make the array size 10
    FILL_INT_ARRAY_BY_INDEX(ints, 0, 10);

    CHECK(ints.size() == 10);
    u32 currCapacity = (u32)ints.capacity();
    itr = ints.erase(ints.begin(), ints.end());
    CHECK(ints.size() == 0);
    CHECK(ints.capacity() == currCapacity);
    itr = ints.end();

    FILL_INT_ARRAY_BY_PUSH(ints, 0, 10);
    itr = ints.erase(ints.begin(), ints.begin() + 4);
    CHECK(*itr == 4);
    CHECK(ints.size() == 6);

    //------------------------------------------------------------------------
    // Check that correct erase is being called on an object

    someClass.push_back(SomeClass());
    someClass.push_back(SomeClass());
    someClass.push_back(SomeClass());

    someClass.erase(someClass.begin());
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/UnorderedErase",
    "Test the unordered erase function")
  {
    Array<tl_int, Array_Unordered> unorderedInts;

    FILL_INT_ARRAY_BY_PUSH(unorderedInts, 0, 10);

    unorderedInts.erase(unorderedInts.begin() + 5);

    CHECK((unorderedInts.begin() + 9) == unorderedInts.end());
    CHECK(unorderedInts.size() == 9);

    CHECK(unorderedInts[0] == 0);
    CHECK(unorderedInts[1] == 1);
    CHECK(unorderedInts[2] == 2);
    CHECK(unorderedInts[3] == 3);
    CHECK(unorderedInts[4] == 4);
    CHECK(unorderedInts[5] == 9);
    CHECK(unorderedInts[6] == 6);
    CHECK(unorderedInts[7] == 7);
    CHECK(unorderedInts[8] == 8);
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Clear",
    "Test the clear function")
  {
    u32 sizeOfInts = 1000;
    FILL_INT_ARRAY_BY_PUSH(ints, 0, sizeOfInts);

    u32 currCapacity = (u32)ints.capacity();
    CHECK(ints.size() == sizeOfInts);
    ints.clear();
    CHECK(ints.size() == 0);
    CHECK(ints.capacity() == currCapacity);
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Reserve",
    "Test the reserve function")
  {
    u32 newCapacity = 1000;
    ints.reserve(newCapacity);

    CHECK(ints.capacity() == newCapacity);
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Insert",
    "Test the insert methods")
  {
    //------------------------------------------------------------------------
    // Insert single values

    FILL_INT_ARRAY_BY_PUSH(ints, 0, 10);

    for (u32 i = 10; i < 20; ++i)
    {
      ints.insert(ints.end(), i);
    }

    CHECK(ints.size() == 20);

    for (u32 i = 0; i < 20; ++i)
    {
      CHECK(ints[i] == (s32)i);
    }

    CHECK(ints.capacity() == 32);

    ints.insert(ints.begin() + 2, 90);
    CHECK(ints.size() == 21);
    CHECK(ints[0] == 0);
    CHECK(ints[1] == 1);
    CHECK(ints[2] == 90);
    CHECK(ints[3] == 2);

    CHECK(ints.capacity() == 32);

    //------------------------------------------------------------------------
    // Insert several values

    FILL_INT_ARRAY_BY_PUSH(ints2, 0, 10);

    CHECK(ints2.size() == 10);

    ints2.insert(ints2.begin() + 2, 10, 90);

    CHECK(ints2[0] == 0);
    CHECK(ints2[1] == 1);

    for (u32 i = 2; i < 10 + 2; ++i)
    {
      CHECK(ints2[i] == 90);
    }

    CHECK(ints2[12] == 2);
    CHECK(ints2.size() == 20);

    const tl_size sizeOfNums = 10;
    s32 nums[sizeOfNums]     = {1,2,3,4,5,6,7,8,9,10};

    // Will result in reallocation
    ints2.insert(ints2.begin() + 2, (nums), (nums + sizeOfNums) );

    CHECK(ints2.size() == 30);
    for (u32 i = 2; i < 10 + 2; ++i)
    {
      CHECK(ints2[i] == s32(i - 1));
    }
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Container/Array/FrontBackAccess",
    "Test front and back access")
  {
    FILL_INT_ARRAY_BY_PUSH(ints, 0 , 4);

    CHECK(ints.front() == 0);
    CHECK(ints.back() == 3);

    ints.erase(ints.begin());
    ints.erase(ints.end() - 1);

    CHECK(ints.front() == 1);
    CHECK(ints.back() == 2);
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Resize",
    "Test the resize methods")
  {
    ints.resize(0); // should not crash or do anything
    CHECK(ints.size() == 0);
    ints.resize(2); // should not crash
    CHECK(ints.size() == 2);
    ints.clear();

    u32 firstElement = 0;
    u32 arraySize = 10;
    FILL_INT_ARRAY_BY_PUSH(ints, firstElement, arraySize);
    CHECK(ints.size() == arraySize);
    CHECK_ARRAY_BY_INDEX(ints, firstElement, arraySize);

    u32 resizeSize = 5;
    ints.resize(resizeSize);
    CHECK(ints.size() == resizeSize);
    CHECK_ARRAY_BY_INDEX(ints, firstElement, resizeSize);

    resizeSize = 150;
    ints.resize(resizeSize);
    CHECK(ints.size() == resizeSize);
    CHECK_ARRAY_BY_INDEX(ints, firstElement, 5);

    // Check that all 'resizeSize' elements have been allocated properly
    for (u32 i = 0; i < resizeSize; ++i)
    {
      ints[i] = i;
    }
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Assign",
    "Test the assign function")
  {
    s32 someArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    s32* itrBegin = someArray;
    s32* itrEnd = someArray + 10; // past the end, but that is ok, because it is
    // not going to be assigned
    ints.assign(itrBegin, itrEnd);
    CHECK(ints.size() == 10);

    ints.reserve(20);

    s32 anotherArray[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    itrBegin = anotherArray;
    itrEnd = anotherArray + 15;

    ints.assign(itrBegin, itrEnd);
    CHECK(ints.size() == 15);

    for (u32 i = 1; i <= 15; ++i)
    {
      CHECK(ints[i-1] == (s32)i);
    }

    ints.reserve(50);

    // Assign 10, 20 times
    ints.assign(20, 10);
    CHECK(ints.size() == 20);

    for (u32 i = 1; i <= 20; ++i)
    {
      CHECK(ints[i-1] == 10);
    }
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Capacity",
    "Test the reserve function")
  {
    ints.reserve(100);

    REQUIRE(ints.capacity() == 100);

    FILL_INT_ARRAY_BY_PUSH(ints, 0, 100);

    CHECK(ints.capacity() == 100);
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Shrink",
    "Test the shrink function")
  {
    FILL_INT_ARRAY_BY_PUSH(ints, 0, 100);

    REQUIRE(ints.size() == 100);

    ints.shrink(50);

    CHECK(ints.capacity() == 50);
    CHECK(ints.size() == 50);

    ints.reserve(200);

    CHECK(ints.capacity() == 200);
    CHECK(ints.size() == 50);

    ints.shrink_to_fit();

    CHECK(ints.capacity() == 50);
    CHECK(ints.size() == 50);
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Swap",
    "Test the swap function")
  {
    FILL_INT_ARRAY_BY_PUSH(ints, 0, 100);
    FILL_INT_ARRAY_BY_PUSH(ints2, 0, 200);

    REQUIRE(ints.size() == 100);
    REQUIRE(ints2.size() == 200);

    tl_size intsCap = ints.capacity();
    tl_size ints2Cap = ints2.capacity();

    ints.swap(ints2);

    CHECK(ints.size() == 200);
    CHECK(ints2.size() == 100);
    CHECK(ints.capacity() == ints2Cap);
    CHECK(ints2.capacity() == intsCap);
  }

#undef FILL_INT_ARRAY_BY_PUSH
#undef FILL_INT_ARRAY_BY_INDEX
#undef CHECK_ARRAY_BY_INDEX
};
