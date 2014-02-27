#pragma once
#ifndef _TLOC_CORE_MEMORY_MEMORY_POOL_INDEXED_WRAPPER_INL_H_
#define _TLOC_CORE_MEMORY_MEMORY_POOL_INDEXED_WRAPPER_INL_H_

#ifndef _TLOC_CORE_MEMORY_MEMORY_POOL_INDEXED_WRAPPER_H_
#error "Must include header before including the inline file"
#endif

#include "tlocMemoryPoolIndexedWrapper.h"
#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>

namespace tloc { namespace core { namespace memory { namespace priv {

  //------------------------------------------------------------------------
  // Memory Pool Index Wrapper

#define MEMORY_POOL_INDEX_WRAPPER_TEMP    typename T_Elem
#define MEMORY_POOL_INDEX_WRAPPER_PARAMS  T_Elem
#define MEMORY_POOL_INDEX_WRAPPER_TYPE    typename MemoryPoolIndexedWrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>

  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  MemoryPoolIndexedWrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::
    MemoryPoolIndexedWrapper()
    : m_index(p_memory_pool_index::GetInvalidIndex())
  { }

  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  MemoryPoolIndexedWrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::
    MemoryPoolIndexedWrapper(const wrapper_type& a_rhs)
    : m_element(a_rhs.m_element)
    , m_index(a_rhs.m_index)
  { }

  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  void
    MemoryPoolIndexedWrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::
    SetValue(const value_type& a_value)
  {
    TLOC_ASSERT_LOW_LEVEL(m_index != p_memory_pool_index::GetInvalidIndex(),
      "Accessing an invalid value (see pool wrapper)");
    m_element = a_value;
  }

  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  void
    MemoryPoolIndexedWrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::
    SetValue(const_pointer a_value)
  {
    TLOC_ASSERT_LOW_LEVEL(m_index != p_memory_pool_index::GetInvalidIndex(),
      "Accessing an invalid value (see pool wrapper)");
    m_element = *a_value;
  }

  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  MEMORY_POOL_INDEX_WRAPPER_TYPE::pointer
    MemoryPoolIndexedWrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::
    GetValue()
  {
    TLOC_ASSERT_LOW_LEVEL(m_index != p_memory_pool_index::GetInvalidIndex(),
                          "Accessing an invalid value (see pool wrapper)");
    return m_element.get();
  }

  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  MEMORY_POOL_INDEX_WRAPPER_TYPE::const_pointer
    MemoryPoolIndexedWrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::
    GetValue() const
  {
    TLOC_ASSERT_LOW_LEVEL(m_index != p_memory_pool_index::GetInvalidIndex(),
                          "Accessing an invalid value (see pool wrapper)");
    return m_element.get();
  }

  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  MEMORY_POOL_INDEX_WRAPPER_TYPE::wrapper_type&
    MemoryPoolIndexedWrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::
    operator=(wrapper_type a_other)
  {
    a_other.swap(*this);
    return *this;
  }

  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  bool
    MemoryPoolIndexedWrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::
    operator==(const wrapper_type& a_rhs)
  {
    return (m_element == a_rhs.m_element) && (m_index == a_rhs.m_index);
  }

  template <MEMORY_POOL_INDEX_WRAPPER_TEMP>
  void
    MemoryPoolIndexedWrapper<MEMORY_POOL_INDEX_WRAPPER_PARAMS>::
    swap(wrapper_type& a_rhs)
  {
    core::swap(m_element, a_rhs.m_element);
    core::swap(m_index, a_rhs.m_index);
  }


};};};};

#endif