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
    : public core::component_system::Component_T<IntComponent, k_int>
  {
  public:
    typedef core::component_system::Component_T
      <IntComponent, k_int>                     base_type;

  public:
    typedef tl_int         value_type;

  public:
    IntComponent() : base_type(k_component_type)
    { m_ctorCount++; }

    ~IntComponent()
    { m_dtorCount++; }

    tl_int m_value;
    static tl_int m_dtorCount;
    static tl_int m_ctorCount;
  };
  typedef core::smart_ptr::SharedPtr<IntComponent>   IntComponentPtr;

  tl_int IntComponent::m_dtorCount;
  tl_int IntComponent::m_ctorCount;

  //------------------------------------------------------------------------

  class UIntComponent
    : public core::component_system::Component_T<UIntComponent, k_uint>
  {
  public:
    typedef core::component_system::Component_T
      <UIntComponent, k_uint>                   base_type;

  public:
    typedef tl_uint         value_type;

  public:
    UIntComponent() : base_type(k_component_type)
    { m_ctorCount++; }

    ~UIntComponent()
    { m_dtorCount++; }

    tl_uint m_value;
    static tl_int m_dtorCount;
    static tl_int m_ctorCount;
  };
  typedef core::smart_ptr::SharedPtr<UIntComponent>   UIntComponentPtr;

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

    typedef T_PoolType                        pool_type;
    // iterator of ComponentPool
    typedef typename pool_type::value_type         smart_ptr_type;
    typedef typename smart_ptr_type::value_type    smart_ptr_value_type;

    // this is tl_uint or tl_int in the above components
    typedef typename smart_ptr_value_type::value_type value_type;

    RESET_CTOR_AND_DTOR_COUNT();
    {
      // BUGFIX: Component pool sanity check was faulty
      ComponentPoolManager a_tempMgr;
      core_sptr::SharedPtr<T_PoolType> tpool =
        a_tempMgr.CreateNewPool<smart_ptr_type>();

      core_sptr::SharedPtr<smart_ptr_value_type> spt(new smart_ptr_value_type());
      tpool->GetNext()->SetValue(spt); // do nothing with it
    }
    CHECK(smart_ptr_value_type::m_dtorCount ==
          smart_ptr_value_type::m_ctorCount);

    RESET_CTOR_AND_DTOR_COUNT();
    {
      core_sptr::SharedPtr<T_PoolType> tpool =
        a_mgr.CreateNewPool<smart_ptr_type>();
      typename pool_type::iterator itr = tpool->GetNext();

      {
        itr->SetValue(smart_ptr_type(new smart_ptr_value_type()) );
        itr->GetValue()->m_value = 0;
      }

      CHECK(itr->GetValue().use_count() == 1);

      for (tl_int i = 1; i < 10; ++i)
      {
        itr = tpool->GetNext();
        itr->SetValue(smart_ptr_type(new smart_ptr_value_type()) );
        itr->GetValue()->m_value = i;
      }
    }

    {
      component_pool_sptr compPool = a_mgr.GetPool(a_compType);

      pool_type* intCompPool = compPool->GetAs<pool_type>();

      typename pool_type::iterator itr = intCompPool->begin();
      typename pool_type::iterator itrEnd = intCompPool->end();

      REQUIRE(distance(itr, itrEnd) == elementsToPool);

      value_type counter = 0;
      bool testPassed = true;
      for (; itr != itrEnd; ++itr)
      {
        if(itr->GetValue()->m_value != counter)
        { testPassed = false; break; }

        ++counter;
      }
      CHECK(testPassed);
    }
  }

  TEST_CASE("Core/component_system/ComponentPoolManager/Pools", "")
  {
    typedef ComponentPool_TI<IntComponentPtr>   IntComponentPtrPool;
    typedef ComponentPool_TI<UIntComponentPtr>  UIntComponentPtrPool;

    {
      ComponentPoolManager mgr;

      CHECK_FALSE(mgr.Exists(k_int));
      TestWithManager<IntComponentPtrPool>(mgr, k_int);
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
      printf("%lu", mgr.size());
      TestWithManager<UIntComponentPtrPool>(mgr, k_uint);
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
      TestWithManager<IntComponentPtrPool>(mgr, k_int);
      TestWithManager<UIntComponentPtrPool>(mgr, k_uint);
      CHECK(mgr.GetNumActivePools() == 2);
      mgr.DestroyPool(k_int);
      mgr.DestroyPool(k_uint);
      CHECK(mgr.GetNumActivePools() == 0);
    }
  }
};