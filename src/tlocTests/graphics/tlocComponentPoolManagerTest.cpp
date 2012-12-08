#include "tlocTestCommon.h"

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntity.inl>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocCore/memory/tlocMemoryPool.inl>

#include <tlocCore/smart_ptr/tlocSmartPtr.h>
#include <tlocCore/smart_ptr/tlocSmartPtr.inl>

namespace TestingComponentPoolManager
{
  using namespace tloc;
  using namespace core;
  using namespace component_system;

  enum
  {
    k_int = 0,
    k_float = 1,
  };

  class IntComponent
    : public core::component_system::Component_T<IntComponent>
  {
  public:
    typedef core::component_system::Component_T<IntComponent>   base_type;

  public:
    IntComponent() : base_type(k_int)
    { }

    tl_int m_value;
  };
  typedef core::smart_ptr::SharedPtr<IntComponent>   IntComponentPtr;

  class FloatComponent
    : public core::component_system::Component_T<FloatComponent>
  {
  public:
    typedef core::component_system::Component_T<FloatComponent>   base_type;

  public:
    FloatComponent() : base_type(k_float)
    { }

    tl_float m_value;
  };
  typedef core::smart_ptr::SharedPtr<IntComponent>   FloatComponentPtr;

  TEST_CASE("Core/component_system/ComponentPoolManager/Pools", "")
  {
    typedef ComponentPool_TI<IntComponentPtr>   IntComponentPtrPool;
    typedef ComponentPool_TI<FloatComponentPtr> FloatComponentPtrPool;

    const tl_int elementsToPool = 10;

    ComponentPoolManager mgr;

    {
      ComponentPoolManager::iterator compPool =
        mgr.CreateNewPool<IntComponentPtr>(k_int);


      IntComponentPtrPool* intCompPool =
        (*compPool)->GetAs<IntComponentPtrPool>();

      IntComponentPtrPool::iterator itr = intCompPool->GetNext();

      {
        IntComponentPtr& myPtr = itr->GetElement();
        myPtr = new IntComponent();
        myPtr->m_value = 0;
      }

      CHECK(itr->GetElement().GetRefCount() == 1);

      for (tl_int i = 1; i < 10; ++i)
      {
        itr = intCompPool->GetNext();
        IntComponentPtr& myPtr = itr->GetElement();
        myPtr = new IntComponent();
        myPtr->m_value = i;
      }
    }

    {
      ComponentPoolManager::iterator compPool = mgr.GetPool(k_int);

      IntComponentPtrPool* intCompPool = (*compPool)->GetAs<IntComponentPtrPool>();

      IntComponentPtrPool::iterator itr = intCompPool->begin();
      IntComponentPtrPool::iterator itrEnd = intCompPool->end();

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
};