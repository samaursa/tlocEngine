#ifndef _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_INL_
#define _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_INL_

#ifndef _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_H_
#error "Must include header before including the inline file"
#endif

#include "tlocComponentPoolManager.h"
#include <tlocCore/memory/tlocMemoryPool.inl>
#include <tlocCore/configs/tlocBuildConfig.h>

namespace tloc { namespace core { namespace component_system {

  namespace
  {
    template <typename T_Iterator, typename T_BuildConfig>
    void DoAssertElementsNotInUse(T_Iterator a_begin, T_Iterator a_end,
                                  T_BuildConfig)
    {
      for (; a_begin != a_end; ++a_begin)
      {
        TLOC_ASSERT(a_begin->GetElement().use_count() == 1,
                    "Element still in use!");
      }
    }

    template <typename T_Iterator>
    void DoAssertElementsNotInUse(T_Iterator, T_Iterator, 
                                  p_build_config::Release)
    { /* Intentioanlly Empty */ }
  }

#define COMPONENT_POOL_TEMPS  typename T_Component
#define COMPONENT_POOL_PARAMS T_Component
#define COMPONENT_POOL_TYPE   typename ComponentPool_TI<COMPONENT_POOL_PARAMS>

  template <COMPONENT_POOL_TEMPS>
  ComponentPool_TI<COMPONENT_POOL_PARAMS>::
    ComponentPool_TI()
  { /* Intentionally empty */ }

  template <COMPONENT_POOL_TEMPS>
  ComponentPool_TI<COMPONENT_POOL_PARAMS>::
    ~ComponentPool_TI()
  {
    DoAssertElementsNotInUse(begin(), end(), 
                             BuildConfig<>::GetBuildConfigType());
  }

  template <COMPONENT_POOL_TEMPS>
  COMPONENT_POOL_TYPE::iterator ComponentPool_TI<COMPONENT_POOL_PARAMS>::
    GetNext()
  { return m_pool.GetNext(); }

  template <COMPONENT_POOL_TEMPS>
  COMPONENT_POOL_TYPE::iterator ComponentPool_TI<COMPONENT_POOL_PARAMS>::
    begin()
  { return m_pool.begin(); }

  template <COMPONENT_POOL_TEMPS>
  COMPONENT_POOL_TYPE::const_iterator ComponentPool_TI<COMPONENT_POOL_PARAMS>::
    begin() const 
  { return m_pool.begin(); }

  template <COMPONENT_POOL_TEMPS>
  COMPONENT_POOL_TYPE::iterator ComponentPool_TI<COMPONENT_POOL_PARAMS>::
    end()
  { return m_pool.end(); }

  template <COMPONENT_POOL_TEMPS>
  COMPONENT_POOL_TYPE::const_iterator ComponentPool_TI<COMPONENT_POOL_PARAMS>::
    end() const 
  { return m_pool.end(); }

  template <COMPONENT_POOL_TEMPS>
  void ComponentPool_TI<COMPONENT_POOL_PARAMS>::
    RecycleAllUnused()
  {
    iterator itr    = begin();
    iterator itrEnd = end();

    for (; itr != itrEnd; ++itr)
    {
      if (itr->GetElement().use_count() == 1)
      {
        m_pool.RecycleElement(itr);
      }
    }
  }

  template <COMPONENT_POOL_TEMPS>
  COMPONENT_POOL_TYPE::size_type ComponentPool_TI<COMPONENT_POOL_PARAMS>::
    GetUsed() const
  { return m_pool.GetUsed(); }
  
};};};

#endif