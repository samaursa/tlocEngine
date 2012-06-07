#ifndef TLOC_MEMORY_POOL_INL 
#define TLOC_MEMORY_POOL_INL 

#ifndef TLOC_MEMORY_POOL_H
#error "Must include header before including the inline file"
#endif

#include "tlocMemoryPool.h"
#include <tlocCore/containers/tlocContainers.inl>

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions

#ifndef TLOC_DISABLE_ASSERT_MEMORY_POOL_INDEX
# define TLOC_ASSERT_MEMORY_POOL_INDEX(_Expression, _Msg) TLOC_ASSERT_LOW_LEVEL(_Expression, _Msg)
#else
# define TLOC_ASSERT_MEMORY_POOL_INDEX(_Expression, _Msg)
#endif

namespace tloc { namespace core {

#define MEMORY_POOL_INDEX_TEMP    class T, class T_PolicyAllocation, class T_PolicyUsedElements
#define MEMORY_POOL_INDEX_PARAMS  T, T_PolicyAllocation, T_PolicyUsedElements
#define MEMORY_POOL_INDEX_TYPE    typename MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>

#define TLOC_ASSERT_MEMORY_POOL_INITIALIZED()\
  TLOC_ASSERT_MEMORY_POOL_INDEX(DoIsInitialized(), "Memory pool not initialized!");

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::value_type  
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::npos;

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

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::wrapper_type& 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::GetNext()
  {
    TLOC_ASSERT_MEMORY_POOL_INITIALIZED();

    tl_int availIndex = m_availIndex--;

    if (m_availIndex < 0)
    {
      ++m_availIndex;
      return MEMORY_POOL_INDEX_TYPE::npos;
    }

    // TODO: Store the element as used (as per the policy)
    return m_allElements[m_availElements[m_availIndex] ];
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    Recycle(const wrapper_type& a_retElem)
  {
    TLOC_ASSERT_MEMORY_POOL_INITIALIZED();

    tl_int availIndex = ++m_availIndex;

    if (availIndex >= (tl_int)m_allElements.size())
    {
      --m_availIndex;
      TLOC_ASSERT_MEMORY_POOL_INDEX(false, 
        "Trying to recycle more elements than we have!");
      return;
    }

    // TODO: Store the element as used (as per the policy)
    m_availElements[m_availIndex] = a_retElem
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::size_type 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::GetAvail() const
  {
    return m_allElements.size();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::size_type 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::GetUsed() const
  {
    return m_allElements.size() - (m_availIndex + 1);
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::iterator 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::begin()
  {
    return m_allElements.begin();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::const_iterator
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::begin() const
  {
    return m_allElements.begin();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::iterator 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::end() 
  {
    return m_allElements.end();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::const_iterator
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::end() const
  {
    return m_allElements.end();
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
    a_pos = new wrapper_type();
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