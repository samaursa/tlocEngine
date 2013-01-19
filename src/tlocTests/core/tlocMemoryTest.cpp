#include "tlocTestCommon.h"

#include <tlocCore/memory/tlocMemory.h>
#include <tlocCore/memory/tlocMemory.inl>

namespace TestingMemory
{
  using namespace tloc;
  using namespace tloc::core;

#define FILL_ARRAY_BY_INDEX(arrayName, nFrom, nTo) \
  for (tl_size i = nFrom; i < nTo; ++i) \
  { \
  arrayName[i] = (tl_int)i; \
  }

#define CHECK_ARRAY_BY_INDEX(arrayName, nFrom, nTo) \
  for (tl_size i = nFrom; i < nTo; ++i) \
  { \
  CHECK(arrayName[i] == (tl_int)i); \
  }

#define CHECK_ARRAY_FILL(arrayName, nFrom, nTo, fillValue) \
  for (tl_size i = nFrom; i < nTo; ++i) \
  { \
  CHECK(arrayName[i] == fillValue); \
  }

  template <typename T>
  class ComplexType
  {
  public:
    typedef T value_type;
  public:
    ComplexType() {dummy = 0;}

    ComplexType(const value_type& a_dummy)
    {
      (*this) = a_dummy;
    }

    tl_int operator= (const value_type& a_dummy)
    {
      dummy = a_dummy;
      return dummy;
    }

    bool operator== (const value_type& a_dummy) const
    {
      return a_dummy == dummy;
    }

  public:
    value_type dummy;
  };

  TEST_CASE("Core/Memory", "Testing memory allocators")
  {
    tl_int* a = new tl_int();
    REQUIRE(a != NULL);
    delete a;
  }

  template <typename T_IntegralType>
  void TestUninitializedCopy()
  {
    const tl_size numToCopy = 10;
    T_IntegralType arraySource[numToCopy];

    FILL_ARRAY_BY_INDEX(arraySource, 0, numToCopy);

    T_IntegralType* arrayDestination =
      (T_IntegralType*)TL_MALLOC(numToCopy * sizeof(T_IntegralType));

    uninitialized_copy(arraySource, arraySource + numToCopy, arrayDestination);

    CHECK_ARRAY_BY_INDEX(arrayDestination, 0, numToCopy);
  }

  TEST_CASE("Core/Memory/uninitialized_copy", "Testing uninitialized_copy")
  {
    TestUninitializedCopy<tl_int>();
    TestUninitializedCopy<ComplexType<tl_int> >();
  }

  template <typename T_IntegralType>
  void TestUninitializedFillN()
  {
    const tl_size numToFill = 10;
    const tl_int fillValue = 12;

    T_IntegralType* arrayDestination =
      (T_IntegralType*)TL_MALLOC(numToFill * sizeof(T_IntegralType));

    uninitialized_fill_n(arrayDestination, numToFill, fillValue);

    CHECK_ARRAY_FILL(arrayDestination, 0, numToFill, fillValue);
  }

  TEST_CASE("Core/Memory/uninitialized_fill_n", "Testing uninitialized_fill_n")
  {
    TestUninitializedFillN<tl_int>();
    TestUninitializedFillN<ComplexType<tl_int> >();
  }

};