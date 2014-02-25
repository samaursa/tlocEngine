#include "tlocComponentPoolManager.h"
#include "tlocComponentPoolManager.inl.h"

#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.inl.h>

namespace tloc { namespace core { namespace component_system {

  //////////////////////////////////////////////////////////////////////////
  // ComponentPool_I

  ComponentPool_I::
    ComponentPool_I()
  { /* Intentionally empty */ }

  ComponentPool_I::
    ~ComponentPool_I()
  { /* Intentionally empty */ }

  //////////////////////////////////////////////////////////////////////////
  // ComponentPoolManager

  ComponentPoolManager::
    ComponentPoolManager()
    : m_numActivePools(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ComponentPool_I::
    ComponentPool_I(const this_type& )
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ComponentPoolManager::
    ~ComponentPoolManager()
  { }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ComponentPoolManager::
    DestroyPool(component_type a_number)
  {
    const size_type index = a_number;
    TLOC_ASSERT(index < m_pools.size(),
      "Pool not allocated for passed component type");

    m_pools[index] = nullptr;
    --m_numActivePools;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  component_pool_vptr
    ComponentPoolManager::
    GetPool(component_type a_number)
  {
    TLOC_ASSERT( (size_type)a_number < m_pools.size(),
      "Pool not allocated for passed component type");

    iterator itr = m_pools.begin();
    core::advance(itr, a_number);

    return *itr;
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

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(tloc::core::component_system::ComponentPoolManager);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(tloc::core::component_system::ComponentPool_I);

TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(tloc::core::component_system::ComponentPoolManager);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(tloc::core::component_system::ComponentPool_I);