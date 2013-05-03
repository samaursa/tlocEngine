#include "tlocComponentPoolManager.h"
#include "tlocComponentPoolManager.inl"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

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
    ~ComponentPoolManager()
  {
    delete_ptrs(m_pools.begin(), m_pools.end());
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void ComponentPoolManager::
    DestroyPool(component_type a_number)
  {
    const size_type index = a_number;
    TLOC_ASSERT(index < m_pools.size(),
      "Pool not allocated for passed component type");

    delete m_pools[index];

    iterator itr = m_pools.begin();
    advance(itr, index);
    m_pools.erase(itr);
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ComponentPoolManager::iterator ComponentPoolManager::
    GetPool(component_type a_number)
  {
    TLOC_ASSERT( (size_type)a_number < m_pools.size(),
      "Pool not allocated for passed component type");

    iterator itr = m_pools.begin();
    core::advance(itr, a_number);

    return itr;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool ComponentPoolManager::
    Exists(component_type a_number)
  {
    if (core::utils::CastNumber<size_type, component_type>(a_number) >= size())
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

  void ComponentPoolManager::
    DoResize(size_type a_index)
  {
    if (a_index >= m_pools.size())
    { m_pools.resize(a_index, nullptr); }
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  template class core_sptr::SharedPtr<ComponentPoolManager>;

};};};