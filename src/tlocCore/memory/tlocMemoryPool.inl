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

#define MEMORY_POOL_INDEX_TEMP    class T, tl_uint T_Capacity, class T_PolicyAllocation, class T_PolicyIndexing
#define MEMORY_POOL_INDEX_PARAMS  T, T_Capacity, T_PolicyAllocation, T_PolicyIndexing
#define MEMORY_POOL_INDEX_TYPE    typename MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>

  //------------------------------------------------------------------------
  // Memory Pool Index Wrapper

#define MEMORY_POOL_INDEX_WRAPPER_TEMP    typename T_Elem, typename T_SizeType
#define MEMORY_POOL_INDEX_WRAPPER_PARAMS  T_Elem, T_SizeType
#define MEMORY_POOL_INDEX_WRAPPER_TYPE    typename MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::template Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>

  template <MEMORY_POOL_INDEX_TEMP>
  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::Wrapper() 
    : m_index(parent_type::sm_invalidIndex)
  {
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>:: 
    Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::Wrapper(const wrapper_type& a_rhs)
  {
    m_element = a_rhs.m_element;
    m_index = a_rhs.m_index;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  MEMORY_POOL_INDEX_WRAPPER_TYPE::wrapper_value_type& 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>:: 
    Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::GetElement()
  {
    TLOC_ASSERT_LOW_LEVEL(m_index != parent_type::sm_invalidIndex, 
      "Accessing an invalid element (see pool wrapper)"); 
    return m_element;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  MEMORY_POOL_INDEX_WRAPPER_TYPE::index_type 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>:: 
    Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::GetIndex() const
  {
    return m_index;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  bool MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::operator ==(wrapper_type& a_rhs)
  {
    return (m_element == a_rhs.m_element) && (m_index == a_rhs.m_index);
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::DoSwap(wrapper_type& a_rhs)
  {
    tlSwap(m_element, a_rhs.m_element);
    // The indexes are permanent, we don't swap those
  }

  //------------------------------------------------------------------------
  // Memory Pool Index

#define TLOC_ASSERT_MEMORY_POOL_INITIALIZED()\
  TLOC_ASSERT_MEMORY_POOL_INDEX(DoIsInitialized(), "Memory pool not initialized!");

  template <MEMORY_POOL_INDEX_TEMP> MEMORY_POOL_INDEX_TYPE::wrapper_type  
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::npos;

  template <MEMORY_POOL_INDEX_TEMP> MEMORY_POOL_INDEX_TYPE::index_type
    const MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::sm_invalidIndex = -1;

  template <MEMORY_POOL_INDEX_TEMP>
  MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::MemoryPoolIndex()
    : m_numAvail(sm_invalidIndex)
  {
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::~MemoryPoolIndex()
  {
    DoCleanup(policy_allocation_type());
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::Initialize(size_type a_initialSize)
  {
    TLOC_ASSERT_MEMORY_POOL_INDEX(a_initialSize > 0, "Invalid # of elements!");

    m_allElements.resize(a_initialSize);
    DoInitializeRange(m_allElements.begin(), m_allElements.end(), 0);
    m_numAvail = static_cast<index_type>(a_initialSize);
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::wrapper_type& 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::GetNext()
  {
    TLOC_ASSERT_MEMORY_POOL_INITIALIZED();
    TLOC_ASSERT_MEMORY_POOL_INDEX(m_numAvail >= 0, "Serious logical error!");

    if (m_numAvail != 0)
    {
      // TODO: Store the element as used (as per the policy)
      const size_type index = DoGetAvailIndex();
      m_numAvail--;
      return m_allElements[ index ];
    }

    const size_type prevSize = GetTotal();
    if (DoExpand(container_dynamic_type()) )
    {
      m_numAvail = GetTotal() - prevSize;
      return GetNext();
    }

    return MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::npos;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    RecycleElement(const wrapper_type& a_retElem)
  {
    TLOC_ASSERT_MEMORY_POOL_INITIALIZED();

    if (m_numAvail >= (index_type)m_allElements.size())
    {
      TLOC_ASSERT_MEMORY_POOL_INDEX(false, 
        "Trying to recycle more elements than we have!");
      return;
    }

    // TODO: Store the element as used (as per the policy)

    // Swap the recycled element with the last element in our array. We swap
    // to ensure wrapper index remains consistent
    const size_type lastUsedElem = DoGetAvailIndex() - 1;
    wrapper_type& toSwap = this->operator[]( DoGetIndex(a_retElem, policy_allocation_type()) );
    tlSwap(toSwap, m_allElements[lastUsedElem]);
    tlSwap(DoGetIndex(toSwap, policy_allocation_type()), 
           DoGetIndex(m_allElements[lastUsedElem], policy_allocation_type()) );
    m_numAvail++;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::RecycleAtIndex(index_type a_index)
  {
    TLOC_ASSERT_MEMORY_POOL_INDEX(a_index < (index_type)m_allElements.size(),
                                  "Index out of bounds!");
    RecycleElement(m_allElements[a_index]);
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::RecycleAll()
  {
    for (index_type i = 0; i < m_numAvail; ++i)
    {
      RecycleElement(m_allElements[i]);
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
    return m_numAvail != -1 ? m_numAvail : 0;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::size_type 
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::GetUsed() const
  {
    return m_numAvail != -1 ? (m_allElements.size() - GetAvail()) : 0;
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
    return (m_numAvail != sm_invalidIndex) &&
           (&a_element != &npos) && 
           (DoGetIndex(a_element, policy_allocation_type()) != sm_invalidIndex) &&
           (DoGetIndex(a_element, policy_allocation_type()) < (index_type)GetUsed());
  }

  //------------------------------------------------------------------------
  // Helper functions

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoResize(size_type, fixed_container_selected)
  {
    return;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoResize(size_type a_newSize, dynamic_container_selected)
  {
    m_allElements.resize(a_newSize);
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoInitializeRange(iterator a_begin, iterator a_end, 
                      index_type a_startingIndex)
  {
    for ( ; a_begin != a_end; ++a_begin)
    {
      DoNewElement(a_begin, policy_allocation_type());
      DoGetIndex(*a_begin, policy_allocation_type()) = a_startingIndex;
      ++a_startingIndex;
    }
  }

  template <MEMORY_POOL_INDEX_TEMP>
  bool MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoExpand(fixed_container_selected)
  {
    return false;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  bool MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoExpand(dynamic_container_selected)
  {
    const size_type prevSize = m_allElements.size();

    m_allElements.resize(m_allElements.size() * 2);

    iterator startingPos = m_allElements.begin();
    advance(startingPos, prevSize);

    DoInitializeRange(startingPos, m_allElements.end(), prevSize);
    return true;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  bool MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::DoIsInitialized() const
  {
    // TODO: Change this function to use a conditional bool type to determine
    // initialization
    return !(m_numAvail == sm_invalidIndex);
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::index_type  
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::DoGetAvailIndex() const
  {
    return m_allElements.size() - m_numAvail;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::index_type&
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoGetIndex(wrapper_type& a_element, allocation_on_stack)
  {
    return (index_type&)a_element.m_index;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::index_type&
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoGetIndex(wrapper_type& a_element, allocation_on_heap)
  {
    return (index_type&)a_element->m_index;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::index_type  
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoGetIndex(const wrapper_type& a_element, allocation_on_stack) const
  {
    return (index_type)a_element.m_index;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::index_type  
    MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoGetIndex(const wrapper_type& a_element, allocation_on_heap) const
  {
    return (index_type)a_element->m_index;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoNewElement(iterator, allocation_on_stack)
  {
    // Intentionally empty
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::
    DoNewElement(iterator a_pos, allocation_on_heap)
  {
    *a_pos = new selected_value_type();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::DoCleanup(allocation_on_stack)
  {
    // Intentionally empty
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndex<MEMORY_POOL_INDEX_PARAMS>::DoCleanup(allocation_on_heap)
  {
    for (typename container_type::iterator itr = m_allElements.begin(), 
      itrEnd = m_allElements.end(); itr != itrEnd; ++itr)
    {
      delete (*itr);
    }
  }

};};

#endif
