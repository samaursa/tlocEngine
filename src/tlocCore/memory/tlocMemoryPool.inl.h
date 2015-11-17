#ifndef TLOC_MEMORY_POOL_INL
#define TLOC_MEMORY_POOL_INL

#ifndef TLOC_MEMORY_POOL_H
#error "Must include header before including the inline file"
#endif

#include "tlocMemoryPool.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/containers/tlocContainers.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>
#include <tloCCore/utilities/tlocType.h>

#include <tlocCore/memory/tlocMemoryPoolIndexedWrapper.inl.h>

namespace tloc { namespace core { namespace memory {

  namespace p_memory_pool_index {

    tl_int GetInvalidIndex()
    { return -1; }

  };

  // ///////////////////////////////////////////////////////////////////////
  // MemoryPoolIndexed

#define MEMORY_POOL_INDEX_TEMP    class T, tl_uint T_Capacity, class T_PolicyIndexing
#define MEMORY_POOL_INDEX_PARAMS  T, T_Capacity, T_PolicyIndexing
#define MEMORY_POOL_INDEX_TYPE    typename MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>

  //------------------------------------------------------------------------
  // Helper functions

  namespace {

    typedef std::false_type                        fixed_container_selected;
    typedef std::true_type                         dynamic_container_selected;

    typedef p_memory_pool_index::allocation::On_Stack  allocation_on_stack;
    typedef p_memory_pool_index::allocation::On_Heap   allocation_on_heap;

    typedef tl_size                           size_type;
    typedef tl_int                            index_type;

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
    template <typename T_WrapperType>
    index_type&
      DoGetIndexRef(T_WrapperType& a_element, allocation_on_stack)
    {
      return (index_type&)a_element->DoGetIndexRef();
    }
    
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
    template <typename T_WrapperType>
    index_type&
      DoGetIndexRef(T_WrapperType a_element, allocation_on_heap)
    {
      return (index_type&)a_element->DoGetIndexRef();
    }
    
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
    template <typename T_WrapperType>
    index_type
      DoGetIndex(const T_WrapperType& a_element, allocation_on_stack)
    {
      return (index_type)a_element->GetIndex();
    }
    
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
    template <typename T_WrapperType>
    index_type
      DoGetIndex(const T_WrapperType& a_element, allocation_on_heap)
    {
      return (index_type)a_element->GetIndex();
    }
    
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
    template <typename T_Iterator, typename T_SelectedValueType>
    void
      DoNewElement(T_Iterator, allocation_on_stack, T_SelectedValueType)
    {
      // Intentionally empty
    }
    
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
    template <typename T_Iterator, typename T_SelectedValueType>
    void
      DoNewElement(T_Iterator& a_pos, allocation_on_heap, T_SelectedValueType)
    {
      a_pos->reset(new T_SelectedValueType());
    }
    
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
    template <typename T_Container>
    void
      DoCleanup(T_Container&, allocation_on_stack)
    {
      // Intentionally empty
    }
    
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
    template <typename T_Container>
    void
      DoCleanup(T_Container& m_allElements, allocation_on_heap)
    {
      for_each_all(m_allElements,
                   core_sptr::algos::virtual_ptr::DeleteAndReset());
    }
    
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
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
                          core_utils::cast_number<index_type>(prevSize),
                          a_allocPolicy, a_selValueType);

        return true;
      }

      return false;
    }
    
    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    
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
                        core_utils::cast_number<index_type>(prevSize),
                        a_allocPolicy, a_selValueType);
      return true;
    }
  };

  // ///////////////////////////////////////////////////////////////////////
  // Memory Pool Index

  static const tl_size g_initialStartSize = 1;

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
        core_utils::cast_number<index_type>(m_allElements.size() - m_numRemaining);
    }
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::iterator
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    GetNext()
  {
    TLOC_ASSERT_LOW_LEVEL(m_numAvail >= 0, "Serious logical error!");

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
      m_numAvail = core_utils::cast_number<index_type>(GetTotal() - prevSize);

      return GetNext();
    }

    return m_allElements.end();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::final_value_type&
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    GetNextValue()
  { return *GetNext(); }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::iterator
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    Find(const final_value_type& a_returnedElement)
  {
    iterator itr = m_allElements.begin();
    advance(itr, DoGetIndex(a_returnedElement, policy_allocation_type()));
    return itr;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::iterator
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::
    RecycleElement(iterator a_retElem)
  {
    if (m_numAvail >= (index_type)m_allElements.size())
    {
      TLOC_ASSERT_LOW_LEVEL_FALSE
        ("Trying to recycle more elements than we have!");
      return end();
    }

    // TODO: Store the element as used (as per the policy)

    // Swap the recycled element with the last element in our array. We swap
    // to ensure wrapper index remains consistent
    const size_type lastUsedElem = DoGetAvailIndex() - 1;
    final_value_type& toSwap = this->operator[](DoGetIndex(*a_retElem, policy_allocation_type()) );
    core::swap(toSwap, m_allElements[lastUsedElem]);

    // swap 'back' the indexes because they are permanent
    core::swap(DoGetIndexRef(toSwap, policy_allocation_type()),
               DoGetIndexRef(m_allElements[lastUsedElem], policy_allocation_type()) );
    m_numAvail++;

    iterator itr = begin();
    core::advance(itr, DoGetIndex(toSwap, policy_allocation_type()) );

    return itr;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::RecycleAtIndex(index_type a_index)
  {
    TLOC_ASSERT_LOW_LEVEL(a_index < (index_type)m_allElements.size(),
                                  "Index out of bounds!");

    iterator itr = m_allElements.begin();
    advance(itr, a_index);
    RecycleElement( itr );
  }

  template <MEMORY_POOL_INDEX_TEMP>
  void MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::RecycleAll()
  {
    while (GetUsed() > 0)
    {
      RecycleElement(begin());
    }
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::final_value_type&
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::operator [](index_type a_index)
  {
    TLOC_ASSERT_LOW_LEVEL((size_type)a_index < GetTotal() - GetAvail(),
      "Index trying to access unavailable element!");

    return m_allElements[a_index];
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::final_value_type const &
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::operator [](index_type a_index) const
  {
    TLOC_ASSERT_LOW_LEVEL
      (a_index < core_utils::cast_number<index_type>(GetTotal() - GetAvail()),
       "Index trying to access unavailable element!");

    return m_allElements[a_index];
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::size_type
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::GetTotal() const
  {
    TLOC_ASSERT_LOW_LEVEL(m_allElements.size() > 0,
      "m_allElements.size() should never be 0 as g_initialStartSize is > 0");
    return m_allElements.size();
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::size_type
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::GetAvail() const
  {
    return m_numAvail != p_memory_pool_index::GetInvalidIndex() ? m_numAvail : 0;
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::size_type
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::GetUsed() const
  {
    return m_numAvail != p_memory_pool_index::GetInvalidIndex() ?
      (m_allElements.size() - GetAvail()) : 0;
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
    using p_memory_pool_index::GetInvalidIndex;

    return (m_numAvail != GetInvalidIndex()) &&
           (a_element != m_allElements.end()) &&
           (DoGetIndex(*a_element, policy_allocation_type()) != GetInvalidIndex()) &&
           (DoGetIndex(*a_element, policy_allocation_type()) < (index_type)GetUsed());
  }

  // -----------------------------------------------------------------------
  // Helper methods

  template <MEMORY_POOL_INDEX_TEMP>
  bool MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::DoIsInitialized() const
  {
    // TODO: Change this function to use a conditional bool type to determine
    // initialization
    return !(m_numAvail == p_memory_pool_index::GetInvalidIndex());
  }

  template <MEMORY_POOL_INDEX_TEMP>
  MEMORY_POOL_INDEX_TYPE::index_type
    MemoryPoolIndexed<MEMORY_POOL_INDEX_PARAMS>::DoGetAvailIndex() const
  {
    return core_utils::cast_number<index_type>(m_allElements.size() - m_numAvail);
  }

};};};

// -----------------------------------------------------------------------
// explicit instantiation macros

#define TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL(_type_, _capacity_, _policyIndexing_)\
  TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(_type_);\
  TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(_type_);\
  template class tloc::core_mem::MemoryPoolIndexed<_type_, _capacity_, _policyIndexing_>

#define TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_DYN(_type_, _policyIndexing_)\
  TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(_type_);\
  TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(_type_);\
  template class tloc::core_mem::MemoryPoolIndexed<_type_, 0, _policyIndexing_>

// -----------------------------------------------------------------------
// fixed memory pools

#define TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_USING_WRAPPER(_type_, _capacity_)\
  TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL(_type_, _capacity_, \
    tloc::core_mem::p_memory_pool_index::indexing::Wrapper);\
  template class tloc::core_mem::priv::MemoryPoolIndexedWrapper<_type_>;\
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(tloc::core_mem::priv::MemoryPoolIndexedWrapper<_type_>)

#define TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_ON_STACK_USER(_type_, _capacity_)\
  TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL(_type_, _capacity_, \
    tloc::core_mem::p_memory_pool_index::allocation::On_Stack, \
    tloc::core_mem::p_memory_pool_index::indexing::User)

// -----------------------------------------------------------------------
// dynamic memory pools

#define TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_DYN_USING_WRAPPER(_type_)\
  TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_DYN(_type_, \
    tloc::core_mem::p_memory_pool_index::indexing::Wrapper);\
  template class tloc::core_mem::priv::MemoryPoolIndexedWrapper<_type_>;\
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(tloc::core_mem::priv::MemoryPoolIndexedWrapper<_type_>)

#define TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_DYN_USER(_type_)\
  TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_DYN(_type_, _capacity_, \
    tloc::core_mem::p_memory_pool_index::indexing::User)



#endif
