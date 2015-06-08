#include "tlocTestCommon.h"

#include <tlocCore/memory/tlocMemory.h>
#include <tlocCore/memory/tlocMemory.inl.h>

// -----------------------------------------------------------------------
// ObjectCreator tester objects

struct ObjectDefaultCtor
{ };

struct Object1Param
{
  Object1Param(tl_int a)
    : m_a(a)
  { }

  tl_int m_a;
};

struct Object2Param
{
  Object2Param(tl_int a, tl_float b)
    : m_a(a)
    , m_b(b)
  { }

  tl_int    m_a;
  tl_float  m_b;
};

struct Object3Param
{
  Object3Param(tl_int a, tl_float b, tl_double c)
    : m_a(a)
    , m_b(b)
    , m_c(c)
  { }

  tl_int    m_a;
  tl_float  m_b;
  tl_double m_c;
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
    //SECTION("On Stack", "")
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

    //SECTION("On Heap", "")
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

  struct Complex
  {
    Complex()
    { m_num = new tl_int(0); }

    ~Complex()
    { delete m_num; }

    Complex(const Complex& a_other)
      : m_num(new tl_int(*a_other.m_num))
    { }

    Complex& operator=(Complex a_other)
    {
      swap(a_other);
      return *this;
    }

    void swap(Complex& a_other)
    {
      using core::swap;
      swap(m_num, a_other.m_num);
    }

    tl_int* m_num;
  };

  TEST_CASE("core/memory/MemCopy", "")
  {
    SECTION("Simple types", "")
    {
      tl_int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
      tl_int a2[10];

      tl_int* itr = core_mem::MemCopy(a2, a1, 10);
      CHECK(itr == a2);

      bool testPassed = true;
      for (tl_int i = 0; i < 10; ++i)
      { if (a1[i] != a2[i]) { testPassed = false; break; } }
      CHECK(testPassed);
    }

    SECTION("Complex types", "")
    {
      Complex a1[5];
      *a1[0].m_num = 0; *a1[1].m_num = 1; *a1[2].m_num = 2; *a1[3].m_num = 3;
      *a1[4].m_num = 4;

      Complex a2[5];

      Complex* itr = core_mem::MemCopy(a2, a1, 5);
      CHECK(itr == a2);

      for (tl_int i = 0; i < 5; ++i)
      { CHECK(a1[i].m_num != a2[i].m_num); } // pointer addresses should be diff.

      for (tl_int i = 0; i < 5; ++i)
      { CHECK(*a1[i].m_num == *a2[i].m_num); } // values should be same 
    }
  }

};

