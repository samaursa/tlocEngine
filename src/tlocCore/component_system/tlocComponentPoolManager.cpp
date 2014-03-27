#include "tlocComponentPoolManager.h"
#include "tlocComponentPoolManager.inl.h"

#include <tlocCore/tlocAlgorithms.inl.h>

namespace tloc { namespace core { namespace component_system {

  //////////////////////////////////////////////////////////////////////////
  // ComponentPool_I

  ComponentPool_I::
    ComponentPool_I()
  { /* Intentionally empty */ }

  ComponentPool_I::
    ~ComponentPool_I()
  { }

  //////////////////////////////////////////////////////////////////////////
  // ComponentPoolManager

  ComponentPoolManager::
    ComponentPoolManager()
    : m_numActivePools(0)
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ComponentPoolManager::
    ~ComponentPoolManager()
  {
    core::for_each_all(m_pools, core_sptr::algos::virtual_ptr::DeleteAndReset());
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ComponentPoolManager::
    DestroyPool(component_type a_number)
  {
    const size_type index = a_number;
    TLOC_ASSERT(index < m_pools.size(),
      "Pool not allocated for passed component type");

    core_sptr::algos::virtual_ptr::DeleteAndReset()(m_pools[index]);
    --m_numActivePools;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ComponentPoolManager::component_pool_ptr
    ComponentPoolManager::
    GetPool(component_type a_number)
  {
    TLOC_ASSERT( (size_type)a_number < m_pools.size(),
      "Pool not allocated for passed component type");

    iterator itr = m_pools.begin();
    core::advance(itr, a_number);

    return component_pool_ptr(*itr);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool ComponentPoolManager::
    Exists(component_type a_number)
  {
    size_type cIndex =
      core_utils::CastNumber<size_type>(a_number);
    size_type s = size();

    if (s == 0 ||  cIndex >= s)
    { return false; }

    iterator itr = m_pools.begin();
    advance(itr, a_number);
    if (*itr == nullptr )
    { return false; }

    return true;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ComponentPoolManager::size_type ComponentPoolManager::
    size() const
  { return m_pools.size(); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ComponentPoolManager::size_type ComponentPoolManager::
    GetNumActivePools() const
  { return m_numActivePools; }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ComponentPoolManager::
    DoResize(size_type a_index)
  {
    if (a_index >= m_pools.size())
    { m_pools.resize(a_index, nullptr); }
  }

};};};


//////////////////////////////////////////////////////////////////////////
// Explicit instantiations


#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(tloc::core::component_system::ComponentPoolManager);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(tloc::core::component_system::ComponentPool_I);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(tloc::core::component_system::ComponentPoolManager);