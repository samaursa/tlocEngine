#include "tlocTestCommon.h"

#include <tlocCore/smart_ptr/tlocUniquePtr.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.inl.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/memory/tlocMemoryPool.inl.h>

#include <tlocCore/types/tlocTypeTraits.h>

namespace TestingUniquePtr
{
  using namespace tloc;
  using namespace core;
  using namespace core::containers;

  using smart_ptr::UniquePtr;

  struct UniqueStruct
  {
    UniqueStruct(tl_int a_value) : m_value(a_value)
    { ++m_numCtors; }

    ~UniqueStruct()
    { ++m_numDtors; }

    tl_int m_value;

    static tl_int m_numCtors;
    static tl_int m_numDtors;
  };

  tl_int UniqueStruct::m_numCtors;
  tl_int UniqueStruct::m_numDtors;

  void ResetUniqueStructStaticVars()
  {
    UniqueStruct::m_numCtors = 0;
    UniqueStruct::m_numDtors = 0;
  }

  struct base
  {
    base() : m_value(0)
    {
      m_ctorCount++;
    }

    virtual ~base()
    {
      m_dtorCount++;
    }

    bool operator ==(const base& a_other)
    { return m_value == a_other.m_value; }

    bool operator <(const base& a_other)
    { return m_value < a_other.m_value; }

    //TLOC_DECLARE_OPERATORS(base);

    virtual void foo(tl_int) = 0;
    tl_int m_value;

    static tl_int m_ctorCount;
    static tl_int m_dtorCount;
  };

  tl_int base::m_ctorCount;
  tl_int base::m_dtorCount;

  struct derived : public base
  {
    virtual void foo(tl_int a_num)
    {
      m_value = a_num;
    }
  };

#define CHECK_CTOR_DTOR_COUNT(_ctorCount_, _dtorCount_)\
  CHECK(UniqueStruct::m_numCtors == _ctorCount_);\
  CHECK(UniqueStruct::m_numDtors == _dtorCount_)

  TEST_CASE("core/smart_ptr/unique_ptr", "")
  {
    {
      smart_ptr::UniquePtr<UniqueStruct> up = nullptr;
      CHECK_FALSE(up);
    }

    {
      smart_ptr::UniquePtr<UniqueStruct> up;
      CHECK_CTOR_DTOR_COUNT(0, 0);
    }
    CHECK_CTOR_DTOR_COUNT(0, 0);

    {
      ResetUniqueStructStaticVars();

      UniqueStruct* u = new UniqueStruct(1);
      smart_ptr::UniquePtr<UniqueStruct> up(u);
      CHECK_CTOR_DTOR_COUNT(1, 0);
    }
    CHECK_CTOR_DTOR_COUNT(1, 1);

    {
      ResetUniqueStructStaticVars();

      UniqueStruct* u = new UniqueStruct(1);
      smart_ptr::UniquePtr<UniqueStruct> up(u);
      up.reset();
      CHECK_CTOR_DTOR_COUNT(1, 1);
    }

    {
      ResetUniqueStructStaticVars();

      CHECK_CTOR_DTOR_COUNT(0, 0);
      smart_ptr::UniquePtr<UniqueStruct>  up = 
        core_sptr::MakeUnique<UniqueStruct>(5);
      CHECK(up);
      CHECK_CTOR_DTOR_COUNT(1, 0);
    }
    CHECK(UniqueStruct::m_numDtors == 1);

    {
      ResetUniqueStructStaticVars();

      smart_ptr::UniquePtr<UniqueStruct>  up = 
        core_sptr::MakeUnique<UniqueStruct>(5);
      CHECK(up);
      smart_ptr::UniquePtr<UniqueStruct>  up2(Move(up));
      CHECK(up2);
      CHECK_FALSE(up);

      CHECK_CTOR_DTOR_COUNT(1, 0);
      up2.reset();
      CHECK_CTOR_DTOR_COUNT(1, 1);
    }

    {
      ResetUniqueStructStaticVars();

      auto up = core_sptr::MakeUnique<UniqueStruct>(10);
      CHECK(up->m_value == 10);
      auto up2 = core_sptr::MakeUnique<UniqueStruct>(5);
      CHECK(up2->m_value == 5);

      // This should NOT compile
      //smart_ptr::UniquePtr<UniqueStruct> up3 = up2;

      CHECK( (*up).m_value == 10);
      CHECK(up.get() == &(*up));

      up.swap(up2);
      CHECK(up->m_value == 5);
      CHECK(up2->m_value == 10);
    }
  }

  TEST_CASE("core/smart_ptr/unique_ptr/const", "")
  {
    {
      smart_ptr::UniquePtr<const UniqueStruct> sp(nullptr);
      CHECK_FALSE(sp);
    }

    {
      smart_ptr::UniquePtr<const UniqueStruct> sp = 
        core_sptr::MakeUnique<UniqueStruct>(10);
      CHECK(sp);
    }
  }

  template <typename T_ContainerType>
  void TestContainers()
  {
    ResetUniqueStructStaticVars();

    typedef smart_ptr::UniquePtr<UniqueStruct>      unique_ptr_type;
    typedef T_ContainerType                         shared_array_type;

    const tl_int count = 2;

    {
      shared_array_type sa;
      for (int i = 0; i < count; ++i)
      { 
        sa.push_back( core_sptr::MakeUnique<UniqueStruct>(i) );
      }

      CHECK(UniqueStruct::m_numCtors == count);

      bool testsPassed = true;
      tl_int counter = 0;
      for (typename shared_array_type::iterator itr = sa.begin(),
           itrEnd = sa.end(); itr != itrEnd; ++itr)
      {
        if ( (*itr)->m_value != counter)
        { testsPassed = false; break; }

        ++counter;
      }
      CHECK(testsPassed);
      CHECK_CTOR_DTOR_COUNT(count, 0);
    }

    CHECK_CTOR_DTOR_COUNT(count, count);
  }

  TEST_CASE("core/smart_ptr/unique_ptr/with containers", "")
  {
    TestContainers<tl_array<smart_ptr::UniquePtr<UniqueStruct> >::type>();
    TestContainers<tl_singly_list<smart_ptr::UniquePtr<UniqueStruct> >::type>();
    TestContainers<tl_doubly_list<smart_ptr::UniquePtr<UniqueStruct> >::type>();
  }

  TEST_CASE("core/smart_ptr/unique_ptr/global operators", "")
  {
    using tloc::core::smart_ptr::UniquePtr;

    UniquePtr<base> basePtr = core_sptr::MakeUnique<derived>();
    basePtr->foo(5);

    UniquePtr<derived> derPtr = core_sptr::MakeUnique<derived>();
    derPtr->foo(10);

    CHECK( (basePtr == basePtr) );
    CHECK_FALSE( (basePtr != basePtr) );
    CHECK_FALSE( (basePtr == derPtr) );
    CHECK( (basePtr != derPtr) );
    CHECK_FALSE( (basePtr < basePtr) );

    bool baseSmallerThanDerived = basePtr.get() < derPtr.get();
    bool baseGreaterThanDerived = basePtr.get() > derPtr.get();
    bool baseSmallerEqualThanDerived = basePtr.get() <= derPtr.get();
    bool baseGreaterEqualThanDerived = basePtr.get() >= derPtr.get();

    CHECK( (basePtr < derPtr) == baseSmallerThanDerived );
    CHECK_FALSE( (basePtr > derPtr) == baseSmallerThanDerived );
    CHECK( (basePtr > derPtr) == baseGreaterThanDerived);

    CHECK( (basePtr <= derPtr) == baseSmallerEqualThanDerived);
    CHECK( (basePtr >= derPtr) == baseGreaterEqualThanDerived);

    CHECK_FALSE( (basePtr == nullptr));
    CHECK_FALSE( (nullptr == basePtr));
    CHECK( (basePtr != nullptr) );
    CHECK( (nullptr != basePtr) );

    CHECK_FALSE( (basePtr < nullptr) );
    CHECK_FALSE( (basePtr < nullptr) );
    CHECK( (nullptr < basePtr) );
    CHECK( (basePtr > nullptr) );
    CHECK( (nullptr > basePtr) );

    CHECK_FALSE( (basePtr <= nullptr) );
    CHECK( (nullptr <= basePtr) );
    CHECK( (basePtr >= nullptr) );
    CHECK_FALSE( (nullptr >= basePtr) );

  }

  using namespace core_mem::tracking::priv;

  template <typename T_BuildConfig>
  void DoDebugTest(T_BuildConfig)
  {
    derived* d1 = new derived();
    derived* d2 = new derived();
    derived* d3 = new derived();

    UniquePtr<derived> derPtr(d1);
    CHECK(DoIsMemoryAddressTracked( (void*)d1));
    CHECK(DoGetNumberOfPointersToMemoryAddress( (void*)d1) == 0);
    CHECK_FALSE(DoIsMemoryAddressTracked( (void*)d2));
    CHECK_FALSE(DoIsMemoryAddressTracked( (void*)d3));

    UniquePtr<derived> derPtrS(Move(derPtr));
    CHECK(DoGetNumberOfPointersToMemoryAddress( (void*)d1) == 0);

    // This SHOULD fail
    // TODO: Turn this into a real test once we have a throwing assertion
    // UniquePtr<derived> derPtrSS(d1);

    derPtr.swap(derPtrS);
    derPtr.reset();
    CHECK(DoGetNumberOfPointersToMemoryAddress( (void*)d1) == 0);

    derPtr.reset(d2);
    UniquePtr<derived> derPtr2(d3);
    CHECK(DoIsMemoryAddressTracked( (void*)d2));
    CHECK(DoIsMemoryAddressTracked( (void*)d3));
  }

  void DoDebugTest(core_cfg::p_build_config::Release)
  { /* intentionally empty */}

  TEST_CASE("core/smart_ptr/unique_ptr/debug test", "")
  {
    DoDebugTest(core_cfg::BuildConfig::build_config_type());
  }

  TEST_CASE("core/smart_ptr/unique_ptr/GetUseCount", "")
  {
    UniquePtr<tl_int> up;
    CHECK(GetUseCount(up) == 0);

    up.reset(new tl_int(10));
    CHECK(GetUseCount(up) == 1);
  }

  template <typename T_BuildConfig>
  void CheckMemAddressIsTracked(void* a_memAddress, bool a_tracked, T_BuildConfig)
  {
    CHECK(DoIsMemoryAddressTracked(a_memAddress) == a_tracked);
  }

  void CheckMemAddressIsTracked(void* , bool , core_cfg::p_build_config::Release)
  { /* intentionally empty */}

  TEST_CASE("core/smart_ptr/unique_ptr/Release", "")
  {
    //SECTION("Basic functionality", "")
    {
      auto up = core_sptr::MakeUnique<derived>();
      CHECK(up);

      CheckMemAddressIsTracked( (void*) up.get(), true,
                                core_cfg::BuildConfig::build_config_type() );

      UniquePtr<derived> up2(Move(up));
      CHECK_FALSE(up);
      CHECK(up2);

      CheckMemAddressIsTracked( (void*) up2.get(), true,
                                core_cfg::BuildConfig::build_config_type() );

      UniquePtr<base> up3(Move(up2));
      CHECK_FALSE(up2);
      CHECK(up3);

      CheckMemAddressIsTracked( (void*) up3.get(), true,
                                core_cfg::BuildConfig::build_config_type() );
    }

    //SECTION("Basic functionality", "Also tests whether release is untracking "
             //"the memory address it started tracking on construction.")
    {
      auto up = core_sptr::MakeUnique<tl_int>(50);
      CHECK(up);

      CheckMemAddressIsTracked( (void*) up.get(), true,
                                core_cfg::BuildConfig::build_config_type() );

      tl_int* rawPtr = up.release();
      CHECK_FALSE(up);

      CheckMemAddressIsTracked( (void*) up.get(), false,
                                core_cfg::BuildConfig::build_config_type() );

      delete rawPtr;
    }
  }

  TEST_CASE("core/smart_ptr/unique_ptr/polymorphic_behavior", "")
  {
    base::m_ctorCount = 0; base::m_dtorCount = 0;
    derived::m_ctorCount = 0; derived::m_dtorCount = 0;

    {
      CHECK(base::m_ctorCount == 0);
      UniquePtr<base> basePtr = core_sptr::MakeUnique<derived>();
      CHECK(base::m_ctorCount == 1);
    }
    CHECK(base::m_dtorCount == 1);

    {
      UniquePtr<base> basePtr = core_sptr::MakeUnique<derived>();
      CHECK(basePtr->m_value == 0);
      basePtr->foo(5);
      CHECK(basePtr->m_value == 5);

      auto derPtr = core_sptr::MakeUnique<derived>();
      derPtr->foo(10);
      basePtr = Move(derPtr);
      CHECK(base::m_dtorCount == 2);
      CHECK(basePtr->m_value == 10);

      UniquePtr<base> basePtr2(Move(basePtr));

      UniquePtr<derived> convToDer;
      CHECK(base::m_ctorCount == 3);
      CHECK(base::m_dtorCount == 2);

      convToDer = core_sptr::static_pointer_cast<derived>(basePtr2);
      CHECK(convToDer->m_value == 10);

      //TODO: Do const_pointer_cast checks
    }
    CHECK(base::m_ctorCount == 3);
    CHECK(base::m_dtorCount == 3);
  }

  struct BaseClass
  {
    tl_int m_int;
  };

  struct DerivedClass : public BaseClass
  {
    DerivedClass()
    { }
    DerivedClass(tl_float a_float)
      : m_float(a_float)
    { }

    tl_float m_float;
  };

  TEST_CASE("core/smart_ptr/unique_ptr/static_pointer_cast", "")
  {
    auto dc = core_sptr::MakeUnique<DerivedClass>();
    dc->m_float = 10.0f;
    dc->m_int = 5;

    UniquePtr<BaseClass> bc(Move(dc));
    CHECK_FALSE(dc);

    UniquePtr<DerivedClass> dcCopy =
      core_sptr::static_pointer_cast<DerivedClass>(bc);
    CHECK_FALSE(bc);

    CHECK(dcCopy->m_float == Approx(10.0f));
    CHECK(dcCopy->m_int == 5);
  }

  TEST_CASE("core/smart_ptr/unique_ptr/const_pointer_cast", "")
  {
    const auto dcConst = core_sptr::MakeUnique<DerivedClass>(5.0f);

    UniquePtr<DerivedClass> dc =
      core_sptr::const_pointer_cast<DerivedClass>(dcConst);
    CHECK_FALSE(dcConst);

    CHECK(dc->m_float == Approx(5.0f));
  }

  struct FiveParams
  {
    FiveParams(tl_int a, tl_int b, tl_int c, tl_int d, tl_int e)
      : m_a(a), m_b(b), m_c(c), m_d(d), m_e(e)
    { }

    tl_int m_a, m_b, m_c, m_d, m_e;
  };

  TEST_CASE("core/smart_ptr/unique_ptr/MakeUnique", "")
  {
    {
      auto sp = core_sptr::MakeUnique<UniqueStruct>(13);
      CHECK(sp->m_value == 13);
    }
    {
      auto sp = core_sptr::MakeUnique<FiveParams>(1, 2, 3, 4, 5);
      CHECK(sp->m_a == 1);
      CHECK(sp->m_b == 2);
      CHECK(sp->m_c == 3);
      CHECK(sp->m_d == 4);
      CHECK(sp->m_e == 5);
    }
  }

  struct LargeObject
  {
    int m_largeArray[100];
  };
}