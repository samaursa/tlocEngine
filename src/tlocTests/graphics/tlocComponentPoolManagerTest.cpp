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
    ComponentPoolManager mgr;

    ComponentPoolManager::iterator itr =
      mgr.CreateNewPool<IntComponentPtr>(k_int);

    typedef ComponentPool_TI<IntComponentPtr> IntComponentPtrPool;

    IntComponentPtrPool::iterator itr2 =
      (*itr)->GetAs<IntComponentPtr>()->GetNext();

    IntComponentPtr& myPtr = itr2->GetElement();
    myPtr = new IntComponent();
    myPtr->m_value = 10;

    CHECK(itr2->GetElement().GetRefCount() == 1);
  }
};