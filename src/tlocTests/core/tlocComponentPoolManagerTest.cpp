#include "tlocTestCommon.h"

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

#include <tlocCore/memory/tlocMemoryPool.inl.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

namespace TestingComponentPoolManager
{
  using namespace tloc;
  using namespace core;
  using namespace component_system;

  enum
  {
    k_int = 0,
    k_uint = 1,
  };

  //////////////////////////////////////////////////////////////////////////
  // test components

  class IntComponent
    : public core_cs::Component_T<IntComponent, k_int>
  {
  public:
    typedef core_cs::Component_T
      <IntComponent, k_int>                     base_type;

  public:
    typedef tl_int         value_type;

  public:
    IntComponent() : base_type(k_component_type)
    { m_ctorCount++; }

    IntComponent(const IntComponent& a_other)
      : base_type(k_component_type)
      , m_value(a_other.m_value)
    { m_ctorCount++; }

    void* operator new(size_t a_size)
    {
      return ::new char[a_size];
    }

    ~IntComponent()
    { m_dtorCount++; }

    tl_int m_value;
    static tl_int m_dtorCount;
    static tl_int m_ctorCount;
  };
  typedef core::smart_ptr::VirtualPtr<IntComponent>   IntComponentPtr;

  tl_int IntComponent::m_dtorCount;
  tl_int IntComponent::m_ctorCount;

  //------------------------------------------------------------------------

  class UIntComponent
    : public core_cs::Component_T<UIntComponent, k_uint>
  {
  public:
    typedef core_cs::Component_T
      <UIntComponent, k_uint>                   base_type;

  public:
    typedef tl_uint         value_type;

  public:
    UIntComponent() : base_type(k_component_type)
    { m_ctorCount++; }

    UIntComponent(const UIntComponent& a_other)
      : base_type(k_component_type)
      , m_value(a_other.m_value)
    { m_ctorCount++; }

    ~UIntComponent()
    { m_dtorCount++; }

    tl_uint m_value;
    static tl_int m_dtorCount;
    static tl_int m_ctorCount;
  };
  typedef core::smart_ptr::VirtualPtr<UIntComponent>   UIntComponentPtr;

  tl_int UIntComponent::m_dtorCount;
  tl_int UIntComponent::m_ctorCount;

  //////////////////////////////////////////////////////////////////////////
  // tests

    // Reset macro
#define RESET_CTOR_AND_DTOR_COUNT()\
    IntComponent::m_dtorCount = 0;\
    IntComponent::m_ctorCount = 0;\
    UIntComponent::m_dtorCount = 0;\
    UIntComponent::m_ctorCount = 0

  template <typename T_PoolType>
  void TestWithManager(ComponentPoolManager& a_mgr, tl_int a_compType)
  {
    const tl_int elementsToPool = 10;

    typedef T_PoolType                                pool_type;
    typedef ComponentPoolManager::component_pool_ptr  comp_pool_ptr;
    // iterator of ComponentPool
    typedef typename pool_type::value_type          value_type;

    RESET_CTOR_AND_DTOR_COUNT();
    {
      // BUGFIX: Component pool sanity check was faulty
      ComponentPoolManager a_tempMgr;
      core_sptr::VirtualPtr<T_PoolType> tpool =
        a_tempMgr.CreateNewPool<value_type>();

      for (tl_int i = 0; i < elementsToPool; ++i)
      {
        tpool->GetNext();
      }

      tpool->GetNextValue()->SetValue(value_type()); // do nothing with it
    }

    CHECK(value_type::m_dtorCount == value_type::m_ctorCount);

    RESET_CTOR_AND_DTOR_COUNT();
    {
      core_sptr::VirtualPtr<T_PoolType> tpool =
        a_mgr.CreateNewPool<value_type>();
      typename pool_type::iterator itr = tpool->GetNext();
      TLOC_UNUSED(itr);

      {
        (*itr)->SetValue(value_type());
        (*itr)->GetValue()->m_value = 0;
      }

      // one original use count, and one for the returned vptr. In release,
      // the count will be 1
      CHECK( core_sptr::GetUseCount((*itr)->GetValue()) > 0); // release
      CHECK( core_sptr::GetUseCount((*itr)->GetValue()) <= 2); // debug

      for (tl_int i = 1; i < elementsToPool; ++i)
      {
        itr = tpool->GetNext();
        (*itr)->SetValue(value_type());
        (*itr)->GetValue()->m_value = i;
      }
    }

    {
      comp_pool_ptr compPool = a_mgr.GetPool(a_compType);

      pool_type* intCompPool = compPool->GetAs<pool_type>();

      typename pool_type::iterator itr = intCompPool->begin();
      typename pool_type::iterator itrEnd = intCompPool->end();

      REQUIRE( (distance(itr, itrEnd) == elementsToPool) );

      typename value_type::value_type counter = 0;
      bool testPassed = true;
      for (; itr != itrEnd; ++itr)
      {
        if( (*itr)->GetValue()->m_value != counter)
        { testPassed = false; break; }

        ++counter;
      }
      CHECK(testPassed);
    }
  }

  TEST_CASE("Core/component_system/ComponentPoolManager/Pools", "")
  {
    typedef ComponentPool_TI<IntComponent>   IntComponentPool;
    typedef ComponentPool_TI<UIntComponent>  UIntComponentPool;

    {
      ComponentPoolManager mgr;

      CHECK_FALSE(mgr.Exists(k_int));
      TestWithManager<IntComponentPool>(mgr, k_int);
      CHECK(mgr.size() == 1);
      CHECK(mgr.GetNumActivePools() == 1);
      CHECK(mgr.Exists(k_int));

      mgr.DestroyPool(k_int);
      CHECK(mgr.GetNumActivePools() == 0);
      CHECK(mgr.size() == 1); // size never goes down
      CHECK_FALSE(mgr.Exists(k_int));
    }
    CHECK(IntComponent::m_ctorCount > 0);
    CHECK(IntComponent::m_dtorCount ==
          IntComponent::m_ctorCount);

    {
      ComponentPoolManager mgr;

      CHECK_FALSE(mgr.Exists(k_uint));
      TestWithManager<UIntComponentPool>(mgr, k_uint);
      CHECK(mgr.size() == 2); // even though one pool was created, k_uint
                              // has an index of 1, thus the pool container
                              // size must be 2 to accomodate a k_uint pool
      CHECK(mgr.GetNumActivePools() == 1);

      CHECK(mgr.Exists(k_uint));

      mgr.DestroyPool(k_uint);
      CHECK(mgr.size() == 2); // size never goes down
      CHECK(mgr.GetNumActivePools() == 0);
      CHECK_FALSE(mgr.Exists(k_int));
    }
    CHECK(UIntComponent::m_ctorCount > 0);
    CHECK(UIntComponent::m_dtorCount ==
          UIntComponent::m_ctorCount);

    {
      ComponentPoolManager mgr;
      TestWithManager<IntComponentPool>(mgr, k_int);
      TestWithManager<UIntComponentPool>(mgr, k_uint);
      CHECK(mgr.GetNumActivePools() == 2);
      mgr.DestroyPool(k_int);
      mgr.DestroyPool(k_uint);
      CHECK(mgr.GetNumActivePools() == 0);
    }
  }
};