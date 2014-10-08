#ifndef _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_INL_
#define _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_INL_

#ifndef _TLOC_CORE_COMPONENT_SYSTEM_COMPONENT_POOL_MANAGER_H_
#error "Must include header before including the inline file"
#endif

#include "tlocComponentPoolManager.h"
#include <tlocCore/memory/tlocMemoryPool.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/configs/tlocBuildConfig.h>
#include <tlocCore/logging/tlocLogger.h>

namespace tloc { namespace core { namespace component_system {

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
  { }

  template <COMPONENT_POOL_TEMPS>
  COMPONENT_POOL_TYPE::iterator ComponentPool_TI<COMPONENT_POOL_PARAMS>::
    GetNext()
  { return m_pool.GetNext(); }

  template <COMPONENT_POOL_TEMPS>
  COMPONENT_POOL_TYPE::final_value_type&
    ComponentPool_TI<COMPONENT_POOL_PARAMS>::
    GetNextValue()
  { return m_pool.GetNextValue(); }

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
  COMPONENT_POOL_TYPE::size_type
    ComponentPool_TI<COMPONENT_POOL_PARAMS>::
    RecycleAllUnused()
  {
    iterator itr    = begin();
    iterator itrEnd = end();

    size_type count = 0;

    for (; itr != itrEnd; )
    {
      pointer ptr = *(*itr)->GetValuePtr();
      // count of 2 == 1 above + 1 in memory pool == unused
      if ( ptr.use_count() == 2)
      {
        itr = m_pool.RecycleElement(itr);
        itrEnd = m_pool.end();

        ++count;
      }
      else
      { ++itr; }
    }

    return count;
  }

  template <COMPONENT_POOL_TEMPS>
  COMPONENT_POOL_TYPE::size_type ComponentPool_TI<COMPONENT_POOL_PARAMS>::
    GetUsed() const
  { return m_pool.GetUsed(); }

};};};


//------------------------------------------------------------------------
// explicit instantiation helpers

#define TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(_type_)\
template class tloc::core_cs::ComponentPool_TI<_type_>;\
TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_DYN_USING_WRAPPER(tloc::core_sptr::SharedPtr<_type_>);\
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(tloc::core_cs::ComponentPool_TI<_type_>);\

#endif