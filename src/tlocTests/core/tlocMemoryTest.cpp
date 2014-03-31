#include "tlocTestCommon.h"

#include <tlocCore/memory/tlocMemory.h>
#include <tlocCore/memory/tlocMemory.inl.h>

// -----------------------------------------------------------------------
// ObjectCreator tester objects

struct ObjectDefaultCtor
{ };

struct Object1Param
{
  Object1Param(tloc::tl_int a)
    : m_a(a)
  { }

  tloc::tl_int m_a;
};

struct Object2Param
{
  Object2Param(tloc::tl_int a, tloc::tl_float b)
    : m_a(a)
    , m_b(b)
  { }

  tloc::tl_int    m_a;
  tloc::tl_float  m_b;
};

struct Object3Param
{
  Object3Param(tloc::tl_int a, tloc::tl_float b, tloc::tl_double c)
    : m_a(a)
    , m_b(b)
    , m_c(c)
  { }

  tloc::tl_int    m_a;
  tloc::tl_float  m_b;
  tloc::tl_double m_c;
};

#include <tlocCore/smart_ptr/tlocVirtualPtr.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>

TLOC_DECL_AND_DEF_CREATE_OBJECT_CTOR_DEF(ObjectDefaultCtor);
TLOC_DECL_AND_DEF_CREATE_OBJECT_CTOR_1PARAM(Object1Param, tl_int);
TLOC_DECL_AND_DEF_CREATE_OBJECT_CTOR_2PARAM(Object2Param, tl_int, tl_float);
TLOC_DECL_AND_DEF_CREATE_OBJECT_CTOR_3PARAM(Object3Param, tl_int, tl_float, tl_double);

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
    REQUIRE( (a != nullptr) );
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

  TEST_CASE("core/memory/ObjectCretor", "")
  {
    SECTION("On Stack", "")
    {
      core_mem::CreateObject<ObjectDefaultCtor>().OnStack();

      Object1Param o1 =
        core_mem::CreateObject<Object1Param>().OnStack(5);
      CHECK(o1.m_a == 5);

      Object2Param o2 =
        core_mem::CreateObject<Object2Param>().OnStack(5, 10.0f);
      CHECK(o2.m_a == 5);
      CHECK(o2.m_b == Approx(10.0f));

      Object3Param o3 =
        core_mem::CreateObject<Object3Param>().OnStack(5, 10.0f, 5.0);
      CHECK(o3.m_a == 5);
      CHECK(o3.m_b == Approx(10.0f));
      CHECK(o3.m_c == Approx(5.0));
    }

    SECTION("On Heap", "")
    {
      core_mem::CreateObject<ObjectDefaultCtor>().OnHeap();

      core_sptr::VirtualPtr<Object1Param> o1 =
        core_mem::CreateObject<Object1Param>().OnHeap(5);
      CHECK(o1->m_a == 5);

      core_sptr::VirtualPtr<Object2Param> o2 =
        core_mem::CreateObject<Object2Param>().OnHeap(5, 10.0f);
      CHECK(o2->m_a == 5);
      CHECK(o2->m_b == Approx(10.0f));

      core_sptr::VirtualPtr<Object3Param> o3 =
        core_mem::CreateObject<Object3Param>().OnHeap(5, 10.0f, 5.0);
      CHECK(o3->m_a == 5);
      CHECK(o3->m_b == Approx(10.0f));
      CHECK(o3->m_c == Approx(5.0));
    }
  }

};

