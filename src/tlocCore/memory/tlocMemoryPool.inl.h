#ifndef TLOC_MEMORY_POOL_INL
#define TLOC_MEMORY_POOL_INL

#ifndef TLOC_MEMORY_POOL_H
#error "Must include header before including the inline file"
#endif

#include "tlocMemoryPool.h"
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/types/tlocBasicTypes.h>

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions

#ifndef TLOC_DISABLE_ASSERT_MEMORY_POOL_INDEX
# define TLOC_ASSERT_MEMORY_POOL_INDEX(_Expression, _Msg) TLOC_ASSERT_LOW_LEVEL(_Expression, _Msg)
#else
# define TLOC_ASSERT_MEMORY_POOL_INDEX(_Expression, _Msg)
#endif

namespace tloc { namespace core { namespace memory {

#define MEMORY_POOL_INDEX_TEMP    class T, tl_uint T_Capacity, class T_PolicyAllocation, class T_PolicyIndexing
#define MEMORY_POOL_INDEX_PARAMS  T, T_Capacity, T_PolicyAllocation, T_PolicyIndexing
#define MEMORY_POOL_INDEX_TYPE    typename MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>

  //------------------------------------------------------------------------
  // Memory Pool Index Wrapper

#define MEMORY_POOL_INDEX_WRAPPER_TEMP    typename T_Elem
#define MEMORY_POOL_INDEX_WRAPPER_PARAMS  T_Elem
#define MEMORY_POOL_INDEX_WRAPPER_TYPE    typename MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::template Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>

  template <MEMORY_POOL_INDEX_TEMP>
  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::Wrapper()
    : m_index(parent_type::sm_invalidIndex)
  { }

  template <MEMORY_POOL_INDEX_TEMP>
  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::Wrapper(const wrapper_type& a_rhs)
  {
    m_element = a_rhs.m_element;
    m_index = a_rhs.m_index;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  void
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::
    SetValue(const wrapper_value_type& a_value)
  {
    TLOC_ASSERT_LOW_LEVEL(m_index != parent_type::sm_invalidIndex,
      "Accessing an invalid value (see pool wrapper)");
    m_element = a_value;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  const MEMORY_POOL_INDEX_WRAPPER_TYPE::wrapper_value_type&
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::GetValue() const
  {
    TLOC_ASSERT_LOW_LEVEL(m_index != parent_type::sm_invalidIndex,
                          "Accessing an invalid value (see pool wrapper)");
    return m_element;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  MEMORY_POOL_INDEX_WRAPPER_TYPE::wrapper_value_type&
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::GetValue()
  {
    TLOC_ASSERT_LOW_LEVEL(m_index != parent_type::sm_invalidIndex,
                          "Accessing an invalid value (see pool wrapper)");
    return m_element;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  bool MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::operator ==(wrapper_type& a_rhs)
  {
    return (m_element == a_rhs.m_element) && (m_index == a_rhs.m_index);
  }

  template <MEMORY_POOL_INDEX_TEMP>
  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  void MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    Wrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::DoSwap(wrapper_type& a_rhs)
  {
    core::swap(m_element, a_rhs.m_element);
    // The indexes are permanent, we don't swap those
  }

  //------------------------------------------------------------------------
  // Helper functions

  namespace {

    typedef type_false                        fixed_container_selected;
    typedef type_true                         dynamic_container_selected;

    typedef p_memory_pool_index::allocation::On_Stack  allocation_on_stack;
    typedef p_memory_pool_index::allocation::On_Heap   allocation_on_heap;

    typedef tl_size                           size_type;
    typedef tl_int                            index_type;

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Container>
    void
      DoResize(T_Container&, size_type, fixed_container_selected)
    {
      // intentionally empty
    }

    template <typename T_Container>
    void
      DoResize(T_Container& a_allElements,
               size_type a_newSize, dynamic_container_selected)
    {
      a_allElements.resize(a_newSize);
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Container, typename T_AllocationPolicy,
              typename T_SelectedValueType>
    bool
      DoExpand(T_Container& m_allElements, size_type a_size,
               fixed_container_selected, T_AllocationPolicy a_allocPolicy,
               T_SelectedValueType a_selValueType)
    {
      typedef typename T_Container::iterator        iterator;

      const size_type prevSize = m_allElements.size();
      const size_type maxSize = tlMin(a_size, m_allElements.capacity());

      if (prevSize != m_allElements.capacity())
      {
        m_allElements.resize(maxSize);

        iterator startingPos = m_allElements.begin();
        advance(startingPos, prevSize);

        DoInitializeRange(startingPos, m_allElements.end(),
                          core_utils::CastNumber<index_type>(prevSize),
                          a_allocPolicy, a_selValueType);

        return true;
      }

      return false;
    }

    template <typename T_Container, typename T_AllocationPolicy,
              typename T_SelectedValueType>
    bool
      DoExpand(T_Container& m_allElements, size_type a_size,
               dynamic_container_selected, T_AllocationPolicy a_allocPolicy,
               T_SelectedValueType a_selValueType)
    {
      typedef typename T_Container::iterator        iterator;

      const size_type prevSize = m_allElements.size();

      m_allElements.resize(a_size);

      iterator startingPos = m_allElements.begin();
      advance(startingPos, prevSize);

      DoInitializeRange(startingPos, m_allElements.end(),
                        core_utils::CastNumber<index_type>(prevSize),
                        a_allocPolicy, a_selValueType);
      return true;
    }

    template <typename T_Iterator, typename T_AllocationPolicy,
              typename T_SelectedValueType>
    void
      DoInitializeRange(T_Iterator a_begin, T_Iterator a_end,
                        index_type a_startingIndex,
                        T_AllocationPolicy a_allocPolicy,
                        T_SelectedValueType a_selValueType)
    {
      for ( ; a_begin != a_end; ++a_begin)
      {
        DoNewElement(a_begin, a_allocPolicy, a_selValueType);
        DoGetIndexRef(*a_begin, a_allocPolicy) = a_startingIndex;
        ++a_startingIndex;
      }
    }

    template <typename T_WrapperType>
    index_type&
      DoGetIndexRef(T_WrapperType& a_element, allocation_on_stack)
    {
      return (index_type&)a_element.DoGetIndexRef();
    }

    template <typename T_WrapperType>
    index_type&
      DoGetIndexRef(T_WrapperType& a_element, allocation_on_heap)
    {
      return (index_type&)a_element->DoGetIndexRef();
    }

    template <typename T_WrapperType>
    index_type
      DoGetIndex(const T_WrapperType& a_element, allocation_on_stack)
    {
      return (index_type)a_element.GetIndex();
    }

    template <typename T_WrapperType>
    index_type
      DoGetIndex(const T_WrapperType& a_element, allocation_on_heap)
    {
      return (index_type)a_element->GetIndex();
    }

    template <typename T_Iterator, typename T_SelectedValueType>
    void
      DoNewElement(T_Iterator, allocation_on_stack, T_SelectedValueType)
    {
      // Intentionally empty
    }

    template <typename T_Iterator, typename T_SelectedValueType>
    void
      DoNewElement(T_Iterator a_pos, allocation_on_heap, T_SelectedValueType)
    {
      *a_pos = new T_SelectedValueType();
    }

    template <typename T_Container>
    void
      DoCleanup(T_Container&, allocation_on_stack)
    {
      // Intentionally empty
    }

    template <typename T_Container>
    void
      DoCleanup(T_Container& m_allElements, allocation_on_heap)
    {
      delete_ptrs(m_allElements.begin(), m_allElements.end());
    }
  };

  // ///////////////////////////////////////////////////////////////////////
  // Memory Pool Index

  static const tl_size g_initialStartSize = 1;

#define TLOC_ASSERT_MEMORY_POOL_INITIALIZED()\
  TLOC_ASSERT_MEMORY_POOL_INDEX(DoIsInitialized(), "Memory pool not initialized!");

  template <MEMORY_POOL_INDEX_TEMP>
  const MEMORY_POOL_INDEX_TYPE::index_type
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::sm_invalidIndex = -1;

  template <MEMORY_POOL_INDEX_TEMP>
  MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::MemoryPoolIndexed()
    : m_numAvail(0)
  {
    Resize(g_initialStartSize); // Our default size
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    MemoryPoolIndexed(size_type a_initialSize)
    : m_numAvail(0)
  {
    Resize(a_initialSize);
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::~MemoryPoolIndexed()
  {
    DoCleanup(m_allElements, policy_allocation_type());
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::Resize(size_type a_size)
  {
    const size_type currSize = m_allElements.size();

    if (a_size > currSize)
    {
      const size_type m_numRemaining = currSize - m_numAvail;

      DoExpand(m_allElements, a_size, container_dynamic_type(),
        policy_allocation_type(), selected_value_type());
      m_numAvail =
        core_utils::CastNumber<index_type>(m_allElements.size() - m_numRemaining);
    }
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::iterator
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::GetNext()
  {
    TLOC_ASSERT_MEMORY_POOL_INDEX(m_numAvail >= 0, "Serious logical error!");

    if (m_numAvail != 0)
    {
      // TODO: Store the element as used (as per the policy)
      const size_type index = DoGetAvailIndex();
      m_numAvail--;
      iterator itr = m_allElements.begin();
      advance(itr, index);
      return itr;
    }

    const size_type prevSize = GetTotal();
    if (DoExpand(m_allElements, prevSize * 2, container_dynamic_type(),
                       policy_allocation_type(), selected_value_type()) )
    {
      m_numAvail = core_utils::CastNumber<index_type>(GetTotal() - prevSize);

      return GetNext();
    }

    return m_allElements.end();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::iterator
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    Find(const wrapper_type& a_returnedElement)
  {
    iterator itr = m_allElements.begin();
    advance(itr, DoGetIndex(a_returnedElement, policy_allocation_type()));
    return itr;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    RecycleElement(iterator a_retElem)
  {
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
    wrapper_type& toSwap = this->operator[](DoGetIndex(*a_retElem, policy_allocation_type()) );
    core::swap(toSwap, m_allElements[lastUsedElem]);
    core::swap(DoGetIndexRef(toSwap, policy_allocation_type()),
               DoGetIndexRef(m_allElements[lastUsedElem], policy_allocation_type()) );
    m_numAvail++;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::RecycleAtIndex(index_type a_index)
  {
    TLOC_ASSERT_MEMORY_POOL_INDEX(a_index < (index_type)m_allElements.size(),
                                  "Index out of bounds!");

    iterator itr = m_allElements.begin();
    advance(itr, a_index);
    RecycleElement( itr );
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::RecycleAll()
  {
    for (index_type i = 0; i < m_numAvail; ++i)
    {
      iterator itr = m_allElements.begin();
      advance(itr, i);
      RecycleElement(itr);
    }
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::wrapper_type&
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::operator [](index_type a_index)
  {
    TLOC_ASSERT_MEMORY_POOL_INDEX((size_type)a_index < GetTotal() - GetAvail(),
      "Index trying to access unavailable element!");

    return m_allElements[a_index];
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::wrapper_type const &
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::operator [](index_type a_index) const
  {
    TLOC_ASSERT_MEMORY_POOL_INDEX
      (a_index < core_utils::CastNumber<index_type>(GetTotal() - GetAvail()),
       "Index trying to access unavailable element!");

    return m_allElements[a_index];
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::size_type
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::GetTotal() const
  {
    TLOC_ASSERT_MEMORY_POOL_INDEX(m_allElements.size() > 0,
      "m_allElements.size() should never be 0 as g_initialStartSize is > 0");
    return m_allElements.size();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::size_type
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::GetAvail() const
  {
    return m_numAvail != sm_invalidIndex ? m_numAvail : 0;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::size_type
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::GetUsed() const
  {
    return m_numAvail != sm_invalidIndex ? (m_allElements.size() - GetAvail()) : 0;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::iterator
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::begin()
  {
    return m_allElements.begin();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::const_iterator
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::begin() const
  {
    return m_allElements.begin();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::iterator
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::end()
  {
    return m_allElements.end() - GetAvail();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::const_iterator
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::end() const
  {
    return m_allElements.end() - GetAvail();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  bool MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    IsValid(const iterator a_element) const
  {
    return (m_numAvail != sm_invalidIndex) &&
           (a_element != m_allElements.end()) &&
           (DoGetIndex(*a_element, policy_allocation_type()) != sm_invalidIndex) &&
           (DoGetIndex(*a_element, policy_allocation_type()) < (index_type)GetUsed());
  }

  // -----------------------------------------------------------------------
  // Helper methods

  template <MEMORY_POOL_INDEX_TEMP>
  bool MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::DoIsInitialized() const
  {
    // TODO: Change this function to use a conditional bool type to determine
    // initialization
    return !(m_numAvail == sm_invalidIndex);
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::index_type
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::DoGetAvailIndex() const
  {
    return core_utils::CastNumber<index_type>(m_allElements.size() - m_numAvail);
  }

};};};

#define TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL(_type_, _capacity_, _policyAllocation_, _policyIndexing_)\
  template class tloc::core_mem::MemoryPoolIndexed<_type_, _capacity_, _policyAllocation_, _policyIndexing_>

#define TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_ON_STACK_USING_WRAPPER(_type_, _capacity_)\
  template class tloc::core_mem::MemoryPoolIndexed<_type_, _capacity_, \
    tloc::core_mem::p_memory_pool_index::allocation::On_Stack, \
    tloc::core_mem::p_memory_pool_index::indexing::Wrapper>;\
  template class tloc::core_mem::MemoryPoolIndexed<_type_, _capacity_, \
    tloc::core_mem::p_memory_pool_index::allocation::On_Stack, \
    tloc::core_mem::p_memory_pool_index::indexing::Wrapper>::Wrapper<_type_>

#define TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_ON_HEAP_USING_WRAPPER(_type_, _capacity_)\
  template class tloc::core_mem::MemoryPoolIndexed<_type_, _capacity_, \
    tloc::core_mem::p_memory_pool_index::allocation::On_Heap, \
    tloc::core_mem::p_memory_pool_index::indexing::Wrapper>;\
  template class tloc::core_mem::MemoryPoolIndexed<_type_, _capacity_, \
    tloc::core_mem::p_memory_pool_index::allocation::On_Heap, \
    tloc::core_mem::p_memory_pool_index::indexing::Wrapper>::Wrapper<_type_>

#define TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_ON_STACK_USER(_type_, _capacity_)\
  template class tloc::core_mem::MemoryPoolIndexed<_type_, _capacity_, \
    tloc::core_mem::p_memory_pool_index::allocation::On_Stack, \
    tloc::core_mem::p_memory_pool_index::indexing::User>

#define TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_ON_HEAP_USER(_type_, _capacity_)\
  template class tloc::core_mem::MemoryPoolIndexed<_type_, _capacity_, \
    tloc::core_mem::p_memory_pool_index::allocation::On_Heap, \
    tloc::core_mem::p_memory_pool_index::indexing::User>

#define TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_ON_STACK_AND_HEAP_USING_WRAPPER(_type_, _capacity_)\
  TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_ON_STACK_USING_WRAPPER(_type_, _capacity_);\
  TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_ON_HEAP_USING_WRAPPER(_type_, _capacity_)\



#endif
