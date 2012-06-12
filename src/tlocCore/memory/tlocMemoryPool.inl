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
  MEMORY_POOL_INDEX_TYPE::wrapper_type  
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::npos;

  template <MEMORY_POOL_INDEX_TEMP>
  MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::MemoryPoolIndex()
    : m_numAvail(-1)
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
    TLOC_ASSERT_MEMORY_POOL_INDEX(a_maxElements > 0, "Invalid # of elements!");

    m_allElements.resize(a_maxElements);
    size_type currentIndex = 0;
    for (iterator itr = m_allElements.begin(), itrEnd = m_allElements.end();
         itr != itrEnd; ++itr)
    {
      DoNewElement(itr, policy_allocation_type());
      DoSetIndex(*itr, currentIndex, policy_allocation_type());
      ++currentIndex;
    }

    m_numAvail = static_cast<tl_int>(a_maxElements);
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::wrapper_type& 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::GetNext()
  {
    TLOC_ASSERT_MEMORY_POOL_INITIALIZED();

    TLOC_ASSERT_MEMORY_POOL_INDEX(m_numAvail >= 0, "Serious logical error!");
    if (m_numAvail == 0)
    {
      return MEMORY_POOL_INDEX_TYPE::npos;
    }

    // TODO: Store the element as used (as per the policy)
    const size_type index = DoGetAvailIndex();
    m_numAvail--;
    return m_allElements[ index ];
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    Recycle(const wrapper_type& a_retElem)
  {
    TLOC_ASSERT_MEMORY_POOL_INITIALIZED();

    if (m_numAvail >= (tl_int)m_allElements.size())
    {
      TLOC_ASSERT_MEMORY_POOL_INDEX(false, 
        "Trying to recycle more elements than we have!");
      return;
    }

    // TODO: Store the element as used (as per the policy)

    // Swap the recycled element with the last element in our array. We swap
    // to ensure wrapper index remains consistent
    const size_type lastUsedElem = DoGetAvailIndex() - 1;
    wrapper_type& toSwap = 
      this->operator[](static_cast<tl_int>(a_retElem.m_index));
    toSwap.DoSwap(m_allElements[lastUsedElem]);
    m_numAvail++;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::Recycle(tl_int a_index)
  {
    TLOC_ASSERT_MEMORY_POOL_INDEX(a_index < (tl_int)m_allElements.size(),
                                  "Index out of bounds!");
    Recycle(m_allElements[a_index]);
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::RecycleAll()
  {
    for (tl_int i = 0; i < m_numAvail; ++i)
    {
      Recycle(m_allElements[i]);
    }
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::wrapper_type& 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::operator [](tl_int a_index)
  {
    TLOC_ASSERT_MEMORY_POOL_INDEX((size_type)a_index < GetTotal() - GetAvail(),
      "Index trying to access unavailable element!");

    return m_allElements[a_index];
  }

  template <MEMORY_POOL_INDEX_TEMP>
  const MEMORY_POOL_INDEX_TYPE::wrapper_type& 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::operator [](tl_int a_index) const
  {
    TLOC_ASSERT_MEMORY_POOL_INDEX(a_index < GetTotal() - GetAvail(),
      "Index trying to access unavailable element!");

    return m_allElements[a_index];
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::size_type 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::GetTotal() const
  {
    return m_allElements.size();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::size_type 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::GetAvail() const
  {
    return m_numAvail;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::size_type 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::GetUsed() const
  {
    return m_allElements.size() - (m_numAvail);
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
    return m_allElements.end() - GetAvail();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::const_iterator
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::end() const
  {
    return m_allElements.end() - GetAvail();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  bool MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    IsValid(const wrapper_type& a_element) const
  {
    return &a_element != &npos;
  }

  //------------------------------------------------------------------------
  // Helper functions

  template <MEMORY_POOL_INDEX_TEMP>
  bool MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::DoIsInitialized()
  {
    // TODO: Change this function to use a conditional bool type to determine
    // initialization
    return !(m_numAvail == -1);
  }

  template <MEMORY_POOL_INDEX_TEMP>
  tl_int  MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::DoGetAvailIndex() const
  {
    return static_cast<tl_int>(m_allElements.size()) - m_numAvail;
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