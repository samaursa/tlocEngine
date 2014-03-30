#include "tlocTestCommon.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/memory/tlocMemoryPool.inl.h>

namespace TestingSharedPtr
{
  using namespace tloc;
  using namespace core;
  using namespace core::containers;

  using tloc::core::smart_ptr::SharedPtr;

  struct SharedStruct
  {
    SharedStruct(tl_int a_value) : m_value(a_value)
    { ++m_numCtors; }

    ~SharedStruct()
    { ++m_numDtors; }

    tl_int m_value;

    static tl_int m_numCtors;
    static tl_int m_numDtors;
  };

  tl_int SharedStruct::m_numCtors;
  tl_int SharedStruct::m_numDtors;

  void ResetSharedStructStaticVars()
  {
    SharedStruct::m_numCtors = 0;
    SharedStruct::m_numDtors = 0;
  }

  void PassSharedPtr(const SharedPtr<SharedStruct>& a_other)
  {
    tl_int currCount = a_other.use_count();
    SharedPtr<SharedStruct> localPtr = a_other;
    CHECK(localPtr.use_count() == currCount + 1);
  }

#define CHECK_CTOR_DTOR_COUNT(_ctorCount_, _dtorCount_)\
  CHECK(SharedStruct::m_numCtors == _ctorCount_);\
  CHECK(SharedStruct::m_numDtors == _dtorCount_)

  TEST_CASE("core/smart_ptr/shared_ptr", "")
  {
    {
      SharedPtr<SharedStruct> sp(nullptr);
      CHECK_FALSE(sp);
    }

    {
      SharedPtr<SharedStruct> sp( new SharedStruct(5) );
      CHECK(sp);
      CHECK_CTOR_DTOR_COUNT(1, 0);
      CHECK(sp.use_count() == 1);
      SharedPtr<SharedStruct> sp2 = sp;
      CHECK_CTOR_DTOR_COUNT(1, 0);
      CHECK(sp.use_count() == 2);

      CHECK(sp->m_value == 5);
      CHECK(sp2->m_value == 5);

      CHECK( (*sp).m_value == 5);
      CHECK( (*sp2).m_value == 5);

      CHECK_CTOR_DTOR_COUNT(1, 0);
      PassSharedPtr(sp);
      CHECK_CTOR_DTOR_COUNT(1, 0);
    }
    CHECK_CTOR_DTOR_COUNT(1, 1);

    {
      SharedPtr<SharedStruct> sp;
      CHECK_FALSE(sp);
      // This SHOULD fire an assertion - because null copy is disabled
      // SharedPtr<Shared> sp2 = sp;
      CHECK(sp.use_count() == 0);
      //CHECK(sp2.use_count() == 0);

    } // Should not crash when being destroyed

    {
      using tloc::core::smart_ptr::p_shared_ptr::null_copy::Allow;

      typedef SharedPtr<SharedStruct, Allow> shared_ptr_type;

      shared_ptr_type sp;
      shared_ptr_type sp2 = sp; // Should NOT fire an assertion

      CHECK(sp.use_count() == 0);
      CHECK(sp2.use_count() == 0);

    } // Should not crash when being destroyed

    {
      ResetSharedStructStaticVars();

      SharedPtr<SharedStruct> sp(new SharedStruct(10));
      SharedPtr<SharedStruct> sp2 = sp;
      CHECK(sp.use_count() == 2);

      SharedPtr<SharedStruct> sp3(new SharedStruct(50));
      sp2 = sp3;
      CHECK(sp.use_count() == 1);
      CHECK(sp3.use_count() == 2);

      CHECK_CTOR_DTOR_COUNT(2, 0);
      sp = sp3;
      CHECK_CTOR_DTOR_COUNT(2, 1);
      CHECK(sp3.use_count() == 3);
    }
    CHECK_CTOR_DTOR_COUNT(2, 2);

    {
      ResetSharedStructStaticVars();

      SharedPtr<SharedStruct> sp(new SharedStruct(10));
      SharedPtr<SharedStruct> sp2(new SharedStruct(5));

      CHECK(sp->m_value == 10);
      CHECK(sp2->m_value == 5);

      sp.swap(sp2);

      CHECK(sp->m_value == 5);
      CHECK(sp2->m_value == 10);

      swap(sp2, sp);
      CHECK(sp->m_value == 10);
      CHECK(sp2->m_value == 5);

      CHECK_CTOR_DTOR_COUNT(2, 0);
    }
    CHECK_CTOR_DTOR_COUNT(2, 2);
  }

  TEST_CASE("core/smart_ptr/shared_ptr/const", "")
  {
    {
      SharedPtr<const SharedStruct> sp(nullptr);
      CHECK_FALSE(sp);
    }

    {
      SharedPtr<const SharedStruct> sp(new SharedStruct(10));
      CHECK(sp);
    }
  }

  TEST_CASE("core/smart_ptr/shared_ptr/reset", "")
  {
    {
      ResetSharedStructStaticVars();

      SharedPtr<SharedStruct> sp(new SharedStruct(50));
      CHECK_CTOR_DTOR_COUNT(1, 0);
      sp.reset();
      CHECK_CTOR_DTOR_COUNT(1, 1);
      CHECK(sp.use_count() == 0);
    }

    {
      ResetSharedStructStaticVars();

      SharedPtr<SharedStruct> sp(new SharedStruct(50));
      SharedPtr<SharedStruct> sp2(sp);
      sp.reset();
      CHECK_CTOR_DTOR_COUNT(1, 0);
      CHECK(sp2.use_count() == 1);
    }

    {
      ResetSharedStructStaticVars();

      SharedPtr<SharedStruct> sp(new SharedStruct(50));
      SharedPtr<SharedStruct> sp3(sp);
      CHECK_CTOR_DTOR_COUNT(1, 0);
      sp.reset(new SharedStruct(10));
      CHECK(sp3);
      sp3.reset();
      CHECK_CTOR_DTOR_COUNT(2, 1);

      CHECK(sp.use_count() == 1);

      SharedPtr<SharedStruct> sp2(sp);
      CHECK(sp.use_count() == 2);
      sp.reset();
      CHECK_CTOR_DTOR_COUNT(2, 1);
      sp2.reset();
      CHECK_CTOR_DTOR_COUNT(2, 2);
    }
  }

  template <typename T_ContainerType>
  void TestContainers()
  {
    ResetSharedStructStaticVars();

    typedef SharedPtr<SharedStruct>      shared_ptr_type;
    typedef T_ContainerType                   shared_array_type;

    const tl_int count = 2;

    {
      shared_array_type sa;
      for (int i = 0; i < count; ++i)
      { sa.push_back( shared_ptr_type(new SharedStruct(i)) ); }

      CHECK(SharedStruct::m_numCtors == count);

      bool testsPassed = true;
      tl_int counter = 0;
      for (typename shared_array_type::iterator itr = sa.begin(),
           itrEnd = sa.end(); itr != itrEnd; ++itr)
      {
        shared_ptr_type localPtr = *itr;
        if ( (*localPtr).m_value != counter)
        { testsPassed = false; break; }

        ++counter;
      }
      CHECK(testsPassed);
      CHECK_CTOR_DTOR_COUNT(count, 0);
    }
    CHECK_CTOR_DTOR_COUNT(count, count);
  }

  TEST_CASE("core/smart_ptr/shared_ptr/with_containers", "")
  {
    TestContainers<tl_array<SharedPtr<SharedStruct> >::type>();
    TestContainers<tl_singly_list<SharedPtr<SharedStruct> >::type>();
    TestContainers<tl_doubly_list<SharedPtr<SharedStruct> >::type>();
  }

  struct MyComponent
  {
    MyComponent()
    {
      m_ctorCount++;
    }

    MyComponent(tl_int x, tl_int y, tl_int z)
      : x(x), y(y), z(z)
    {
      m_ctorCount++;
    }

    ~MyComponent()
    {
      m_dtorCount++;
    }

    tl_int x, y, z;

    static tl_int m_ctorCount;
    static tl_int m_dtorCount;
  };

  tl_int MyComponent::m_ctorCount;
  tl_int MyComponent::m_dtorCount;

  TEST_CASE("core/smart_ptr/shared_ptr/with_memory_pools", "")
  {
    const tl_int poolSize = 100;
    {
      typedef SharedPtr<MyComponent>                        my_comp_ptr;
      typedef memory::MemoryPoolIndexed<my_comp_ptr>        my_mem_pool;
      typedef my_mem_pool::iterator                         pool_type;

      my_mem_pool memPool(poolSize);
      (*memPool.GetNext())->SetValue(my_comp_ptr(new MyComponent(0, 1, 2)) );
      (*memPool.GetNext())->SetValue(my_comp_ptr(new MyComponent(1, 2, 3)) );

      for (tl_int i = 2; i < poolSize; ++i)
      {
        (*memPool.GetNext())->SetValue(
          my_comp_ptr(new MyComponent(i, i + 1, i + 2)) );
      }

      CHECK(MyComponent::m_ctorCount == poolSize);

      my_mem_pool::iterator itr = memPool.begin();
      my_mem_pool::iterator itrEnd = memPool.end();

      bool testPassed = true;
      tl_int counter = 0;
      for (; itr != itrEnd; ++itr)
      {
        if ( (*(*itr)->GetValue())->x != counter &&
          (*(*itr)->GetValue())->y != counter + 1 &&
          (*(*itr)->GetValue())->z != counter + 2)
        {
          testPassed = false;
          break;
        }
        ++counter;
      }
      CHECK(testPassed);
    }
    CHECK(MyComponent::m_dtorCount == poolSize);
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

  TEST_CASE("core/smart_ptr/shared_ptr/polymorphic_behavior", "")
  {
    {
      CHECK(base::m_ctorCount == 0);
      SharedPtr<base> basePtr(new derived());
      CHECK(base::m_ctorCount == 1);
    }
    CHECK(base::m_dtorCount == 1);

    {
      SharedPtr<base> basePtr(new derived());
      CHECK(basePtr->m_value == 0);
      basePtr->foo(5);
      CHECK(basePtr->m_value == 5);

      SharedPtr<derived> derPtr(new derived());
      derPtr->foo(10);
      basePtr = derPtr;
      CHECK(base::m_dtorCount == 2);
      CHECK(basePtr->m_value == 10);

      SharedPtr<base> basePtr2(derPtr);

      // This should fail to compile - so don't uncomment :)
      //SharedPtr<derived> d(basePtr2);

      SharedPtr<derived> convToDer;
      CHECK(base::m_ctorCount == 3);
      CHECK(base::m_dtorCount == 2);


      convToDer = core_sptr::static_pointer_cast<derived>(basePtr2);
      CHECK(convToDer->m_value == 10);

      //TODO: Do const_pointer_cast checks
    }
    CHECK(base::m_ctorCount == 3);
    CHECK(base::m_dtorCount == 3);
  }

  TEST_CASE("core/smart_ptr/shared_ptr/global operators", "")
  {
      SharedPtr<base> basePtr(new derived());
      basePtr->foo(5);

      SharedPtr<derived> derPtr(new derived());
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

    SharedPtr<derived> derPtr(d1);
    SharedPtr<derived> derPtrS(derPtr);

    // This SHOULD fail
    // TODO: Turn this into a real test once we have a throwing assertion
    // SharedPtr<derived> derPtrSS(d1);

    CHECK(DoIsMemoryAddressTracked( (void*)d1));
    CHECK(DoGetNumberOfPointersToMemoryAddress( (void*)d1) == 0);
    CHECK_FALSE(DoIsMemoryAddressTracked( (void*)d2));

    CHECK(DoIsMemoryAddressTracked( (void*)d1));

    // derPtrS and derPtr are the same SharedPtr essentially and count
    // as one pointer reference
    CHECK(DoGetNumberOfPointersToMemoryAddress( (void*)d1) == 0);
    CHECK_FALSE(DoIsMemoryAddressTracked( (void*)d2));
    CHECK_FALSE(DoIsMemoryAddressTracked( (void*)d3));

    derPtrS.reset();
    CHECK(DoGetNumberOfPointersToMemoryAddress( (void*)d1) == 0);

    derPtr.reset();
    CHECK(DoGetNumberOfPointersToMemoryAddress( (void*)d1) == 0);

    derPtr.reset(d2);
    SharedPtr<derived> derPtr2(d3);
    CHECK(DoIsMemoryAddressTracked( (void*)d2));
    CHECK(DoIsMemoryAddressTracked( (void*)d3));
    CHECK(DoGetNumberOfPointersToMemoryAddress( (void*)d2) == 0);
    CHECK(DoGetNumberOfPointersToMemoryAddress( (void*)d3) == 0);
  }

  void DoDebugTest(core_cfg::p_build_config::Release)
  { /* intentionally empty */}

  TEST_CASE("core/smart_ptr/shared_ptr/debug test", "")
  {
    DoDebugTest(core_cfg::BuildConfig::build_config_type());
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

  template <typename T_PtrPolicyType>
  void CastTest()
  {
    SharedPtr<DerivedClass, T_PtrPolicyType> dc(new DerivedClass());
    dc->m_float = 10.0f;
    dc->m_int = 5;

    SharedPtr<BaseClass, T_PtrPolicyType> bc(dc);

    CHECK(dc->m_float == Approx(10.0f));
    CHECK(dc->m_int == 5);

    SharedPtr<DerivedClass, T_PtrPolicyType> dcCopy =
      core_sptr::static_pointer_cast<DerivedClass, T_PtrPolicyType>(bc);

    CHECK(bc->m_int == 5);
    CHECK(dc->m_float == Approx(10.0f));
    CHECK(dc->m_int == 5);
    CHECK(dcCopy->m_float == Approx(10.0f));
    CHECK(dcCopy->m_int == 5);

    CHECK(dcCopy.use_count() == 3);
  }

  TEST_CASE("core/smart_ptr/shared_ptr/static_pointer_cast", "")
  {
    CastTest<core_sptr::p_shared_ptr::null_copy::Allow>();
    CastTest<core_sptr::p_shared_ptr::null_copy::Disallow>();
  }

  template <typename T_PtrPolicyType>
  void ConstTest()
  {
    const SharedPtr<DerivedClass, T_PtrPolicyType>
      dcConst(new DerivedClass(5.0f));

    SharedPtr<DerivedClass, T_PtrPolicyType> dc =
      core_sptr::const_pointer_cast<DerivedClass, T_PtrPolicyType>(dcConst);

    CHECK(dc->m_float == Approx(5.0f));
    CHECK(dcConst->m_float == Approx(5.0f));

    CHECK(dcConst.use_count() == 2);
  }

  TEST_CASE("core/smart_ptr/shared_ptr/const_pointer_cast", "")
  {
    ConstTest<core_sptr::p_shared_ptr::null_copy::Allow>();
    ConstTest<core_sptr::p_shared_ptr::null_copy::Disallow>();
  }

  TEST_CASE("core/smart_ptr/shared_ptr/GetUseCount", "")
  {
    SharedPtr<tl_int> sp;
    CHECK(GetUseCount(sp) == 0);

    sp.reset(new tl_int(10));
    CHECK(GetUseCount(sp) == 1);
  }
}
