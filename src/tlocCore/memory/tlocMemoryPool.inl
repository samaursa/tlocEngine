#ifndef TLOC_MEMORY_POOL_INL 
#define TLOC_MEMORY_POOL_INL 

#ifndef TLOC_MEMORY_POOL_H
#error "Must include header before including the inline file"
#endif

#include "tlocMemoryPool.h"
#include <tlocCore/containers/tlocContainers.inl>

namespace tloc { namespace core {

#define MEMORY_POOL_INDEX_TEMP    class T, class T_PolicyAllocation, class T_PolicyUsedElements
#define MEMORY_POOL_INDEX_PARAMS  T, T_PolicyAllocation, T_PolicyUsedElements
#define MEMORY_POOL_INDEX_TYPE    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>

  template <MEMORY_POOL_INDEX_TEMP>
  MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::MemoryPoolIndex()
    : m_availElements(0)
    , m_availIndex(-2)
  {
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::~MemoryPoolIndex()
  {
    DoCleanup(policy_allocation_type());
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::Initialize(size_type a_maxElements)
  {
    m_allElements.resize(a_maxElements);
    size_type currentIndex = 0;
    for (iterator itr = m_allElements.begin(), itrEnd = m_allElements.end();
         itr != itrEnd; ++itr)
    {
      DoNewElement(itr, policy_allocation_type());
      DoSetIndex(*itr, currentIndex, policy_allocation_type());
      m_availElements.push_back(currentIndex);
      ++currentIndex;
    }

    m_availIndex = a_maxElements - 1;
  }

  //------------------------------------------------------------------------
  // Helper functions

  template <MEMORY_POOL_INDEX_TEMP>
  bool MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::DoIsInitialized()
  {
    // TODO: Change this function to use a conditional bool type to determine
    // initialization
    return m_availIndex == -2;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoNewElement(iterator, memory_pool_policies::Allocate_On_Stack)
  {
    // Intentionally empty
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoNewElement(iterator a_pos, memory_pool_policies::Allocate_On_Heap)
  {
    a_pos = new element_wrapper_type();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <typename T_Element>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoSetElement(T_Element& a_elem, const value_type& a_value, 
                 memory_pool_policies::Allocate_On_Stack)
  {
    a_elem.m_value = a_value;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <typename T_Element>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoSetElement(T_Element& a_elem, const value_type& a_value, 
                 memory_pool_policies::Allocate_On_Heap)
  {
    a_elem->m_value = a_value;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <typename T_Element>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoSetIndex(T_Element& a_elem, size_type a_index,
               memory_pool_policies::Allocate_On_Stack)
  {
    a_elem.m_index = a_index;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <typename T_Element>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoSetIndex(T_Element& a_elem, size_type a_index,
               memory_pool_policies::Allocate_On_Heap)
  {
    a_elem->m_index = a_index;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoCleanup(memory_pool_policies::Allocate_On_Stack)
  {
    // Intentionally empty
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoCleanup(memory_pool_policies::Allocate_On_Heap)
  {
    delete_ptrs(m_allElements.begin(), m_allElements.end());
  }

};};

#endif