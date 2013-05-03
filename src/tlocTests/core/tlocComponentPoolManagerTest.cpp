#include "tlocTestCommon.h"

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntity.inl>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

#include <tlocCore/memory/tlocMemoryPool.inl>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

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

  class IntComponent
    : public core::component_system::Component_T<IntComponent, k_int>
  {
  public:
    typedef core::component_system::Component_T
      <IntComponent, k_int>                     base_type;

  public:
    IntComponent() : base_type(k_component_type)
    { }

    tl_int m_value;
  };
  typedef core::smart_ptr::SharedPtr<IntComponent>   IntComponentPtr;

  class UIntComponent
    : public core::component_system::Component_T<UIntComponent, k_uint>
  {
  public:
    typedef core::component_system::Component_T
      <UIntComponent, k_uint>                   base_type;

  public:
    UIntComponent() : base_type(k_component_type)
    { }

    tl_uint m_value;
  };
  typedef core::smart_ptr::SharedPtr<IntComponent>   UIntComponentPtr;

  template <typename T_PoolType>
  void TestWithManager(ComponentPoolManager& a_mgr, tl_int a_compType)
  {
    const tl_int elementsToPool = 10;

    typedef T_PoolType                        pool_type;
    // iterator of ComponentPool
    typedef typename pool_type::value_type    smart_ptr_value_type;

    {
      // BUGFIX: Component pool sanity check was faulty
      ComponentPoolManager a_tempMgr;
      ComponentPoolManager::iterator itr =
        a_tempMgr.CreateNewPool<smart_ptr_value_type>(a_compType);
      (*itr)->GetAs<T_PoolType>()->GetNext(); // do nothing with it
    }

    {
      ComponentPoolManager::iterator compPool =
        a_mgr.CreateNewPool<smart_ptr_value_type>(a_compType);


      pool_type* intCompPool =
        (*compPool)->GetAs<T_PoolType>();

      typename pool_type::iterator itr = intCompPool->GetNext();

      {
        itr->SetElement(smart_ptr_value_type
          (new typename smart_ptr_value_type::value_type) );
        itr->GetElement()->m_value = 0;
      }

      CHECK(itr->GetElement().use_count() == 1);

      for (tl_int i = 1; i < 10; ++i)
      {
        itr = intCompPool->GetNext();
        itr->SetElement(smart_ptr_value_type
          (new typename smart_ptr_value_type::value_type) );
        itr->GetElement()->m_value = i;
      }
    }

    {
      ComponentPoolManager::iterator compPool = a_mgr.GetPool(a_compType);

      pool_type* intCompPool = (*compPool)->GetAs<pool_type>();

      typename pool_type::iterator itr = intCompPool->begin();
      typename pool_type::iterator itrEnd = intCompPool->end();

      REQUIRE(distance(itr, itrEnd) == elementsToPool);

      tl_int counter = 0;
      bool testPassed = true;
      for (; itr != itrEnd; ++itr)
      {
        if(itr->GetElement()->m_value != counter)
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

    ComponentPoolManager mgr;

    CHECK_FALSE(mgr.Exists(k_int));
    TestWithManager<IntComponentPtrPool>(mgr, k_int);
    CHECK(mgr.size() == 1);
    CHECK(mgr.Exists(k_int));

    CHECK_FALSE(mgr.Exists(k_uint));
    TestWithManager<UIntComponentPtrPool>(mgr, k_uint);
    CHECK(mgr.size() == 2);
    CHECK(mgr.Exists(k_uint));
  }

};