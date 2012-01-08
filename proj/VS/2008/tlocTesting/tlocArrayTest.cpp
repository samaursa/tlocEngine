#include "catch.hpp"

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocMemory.h"
#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocTypes.inl"
#include "tlocCore/tlocArray.h"
#include "tlocCore/tlocArray.inl"

namespace TestingArray
{
  USING_TLOC;

  class SomeClass
  {
  public:
    int dummy;
  };

  struct ArrayFixture
  {
    core::Array<SomeClass> someClass, someClass2, someClass3;
    core::Array<s32> ints, ints2, ints3;
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

#define CHECK_ARRAY_BY_INDEX(arrayName, nFrom, nTo) \
  for (u32 i = nFrom; i < nTo; ++i)\
  {\
  CHECK(arrayName[i] == (s32)i);\
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Ctors", "")
  {
    core::Array<s32> first;                                // empty vector of ints
    core::Array<s32> second (4,100);                       // four ints with value 100
    CHECK(second[0] == 100); CHECK(second[1] == 100);
    CHECK(second[2] == 100); CHECK(second[3] == 100);
    core::Array<s32> third (second.begin(),second.end());  // iterating through second
    CHECK(third[0] == 100); CHECK(third[1] == 100);
    CHECK(third[2] == 100); CHECK(third[3] == 100);
    core::Array<s32> fourth (third);                       // a copy of third
    CHECK(fourth[0] == 100); CHECK(fourth[1] == 100);
    CHECK(fourth[2] == 100); CHECK(fourth[3] == 100);

    // the iterator constructor can also be used to construct from arrays:
    s32 myints[] = {16,2,77,29};
    core::Array<s32> fifth (myints, myints + sizeof(myints) / sizeof(s32) );

    CHECK(fifth[0] == 16); CHECK(fifth[1] == 2);
    CHECK(fifth[2] == 77); CHECK(fifth[3] == 29);
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

    u32 arraySize = ints.size();
    for (u32 i = 0; i < arraySize; ++i)
    {
      ints.pop_back();
    }

    CHECK(ints.size() == 0);
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

    core::Array<s32>::iterator itr = ints.begin();
    core::Array<s32>::iterator itrEnd = ints.end();

    s32 count = 0;
    while (itr != itrEnd)
    {
      CHECK(count++ == *itr);
      ++itr;
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
    ints.erase(ints.begin() + 4);
    CHECK(ints.size() == 9);

    for (u32 i = 4; i < 9; ++i)
    {
      CHECK(ints[i] == (s32)i + 1);
    }

    //------------------------------------------------------------------------
    // Erase range

    ints.push_back(0); // Make the array size 10
    FILL_INT_ARRAY_BY_INDEX(ints, 0, 10);

    CHECK(ints.size() == 10);
    u32 currCapacity = ints.capacity();
    ints.erase(ints.begin(), ints.end());
    CHECK(ints.size() == 0);
    CHECK(ints.capacity() == currCapacity);

    //------------------------------------------------------------------------
    // Check that correct erase is being called on an object

    someClass.push_back(SomeClass());
    someClass.push_back(SomeClass());
    someClass.push_back(SomeClass());

    someClass.erase(someClass.begin());
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Clear",
    "Test the clear function")
  {
    u32 sizeOfInts = 1000;
    FILL_INT_ARRAY_BY_PUSH(ints, 0, sizeOfInts);

    u32 currCapacity = ints.capacity();
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

    s32 anotherArray[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    itrBegin = anotherArray;
    itrEnd = anotherArray + 15;

    ints.assign(itrBegin, itrEnd);
    CHECK(ints.size() == 15);

    for (u32 i = 1; i <= 15; ++i)
    {
      CHECK(ints[i-1] == (s32)i);
    }

    // Assign 10, 20 times
    ints.assign(20, 10);
    CHECK(ints.size() == 20);

    for (u32 i = 1; i <= 20; ++i)
    {
      CHECK(ints[i-1] == 10);
    }
  }

  TEST_CASE_METHOD(ArrayFixture, "Core/Containers/Array/Reserve",
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
