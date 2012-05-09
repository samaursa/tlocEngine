#ifndef TLOC_STACK_ARRAY_INL
#define TLOC_STACK_ARRAY_INL

#ifndef TLOC_STACK_ARRAY_H
#error "Must include header before including the inline file"
#endif

#include "tlocAlgorithms.inl"

namespace tloc { namespace core{

  //////////////////////////////////////////////////////////////////////////
  // Assertion macros

#define STACK_ARRAY_TYPES typename T, tl_size T_Capacity
#define STACK_ARRAY_PARAMS T, T_Capacity

  //------------------------------------------------------------------------
  // Ctors

  template <STACK_ARRAY_TYPES>
  TL_FI StackArray<STACK_ARRAY_PARAMS>::StackArray()
    : m_values()
    : m_end(NULL)
  {
  }

  template <STACK_ARRAY_TYPES>
  TL_FI StackArray<STACK_ARRAY_PARAMS>::StackArray(const this_type& a_toCopy)
    : m_values(a_toCopy.m_values)
  {
    m_end = m_values + a_toCopy.Size();
  }

  template <STACK_ARRAY_TYPES>
  TL_FI StackArray<STACK_ARRAY_PARAMS>::StackArray(size_type a_numElemsToInsert, 
                                                   const value_type& a_valueToCopy)
                                                   : m_values()

  {
    fill_n(m_values, a_numElemsToInsert, a_valueToCopy);
    m_end = m_values + a_numElemsToInsert;
  }

  template <STACK_ARRAY_TYPES>
  TL_FI StackArray<STACK_ARRAY_PARAMS>::StackArray(size_type a_count)
    : m_values()
  {
    fill_n(m_values, a_count, value_type());
    m_end = m_values + a_count;
  }

  template <STACK_ARRAY_TYPES>
  template <typename T_InputIterator>
  TL_FI StackArray<STACK_ARRAY_PARAMS>::StackArray(T_InputIterator a_rangeBegin, 
                                                   T_InputIterator a_rangeEnd)
                                                   : m_values()
  {
    insert(m_values, a_rangeBegin, a_rangeEnd);
  }

  //------------------------------------------------------------------------
  // Assignment

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::this_type& 
    StackArray<STACK_ARRAY_PARAMS>::operator= (const this_type& a_toCopy)
  {
    copy(a_toCopy.m_values, a_toCopy.m_end, m_values);
    return *this;
  }

  //------------------------------------------------------------------------
  // Element access

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::reference
    StackArray<STACK_ARRAY_PARAMS>::at(size_type a_index)
  {
    return m_values.Get(a_index);
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::const_reference
    StackArray<STACK_ARRAY_PARAMS>::at(size_type a_index) const
  {
    return m_values.Get(a_index);
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::reference
    StackArray<STACK_ARRAY_PARAMS>::operator[] (size_type a_index)
  {
    return m_values.Get(a_index);
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::const_reference
    StackArray<STACK_ARRAY_PARAMS>::operator[] (size_type a_index) const
  {
    return m_values.Get(a_index);
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::reference
    StackArray<STACK_ARRAY_PARAMS>::front()
  {
    return *m_values;
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::const_reference
    StackArray<STACK_ARRAY_PARAMS>::front() const
  {
    return *m_values;
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::reference
    StackArray<STACK_ARRAY_PARAMS>::back()
  {
    return *(m_end - 1);
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::const_reference
    StackArray<STACK_ARRAY_PARAMS>::back() const
  {
    return *(m_end - 1);
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::pointer
    StackArray<STACK_ARRAY_PARAMS>::data()
  {
    return m_values;
  }

  //------------------------------------------------------------------------
  // Iterator access

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::iterator
    StackArray<STACK_ARRAY_PARAMS>::begin()
  {
    return m_values;
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::const_iterator
    StackArray<STACK_ARRAY_PARAMS>::begin() const
  {
    return m_values;
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::iterator
    StackArray<STACK_ARRAY_PARAMS>::end()
  {
    return m_end;
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::const_iterator
    StackArray<STACK_ARRAY_PARAMS>::end() const
  {
    return m_end;
  }

  //------------------------------------------------------------------------
  // Capacity

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::size_type
    StackArray<STACK_ARRAY_PARAMS>::size() const
  {
    return (m_end - m_values);
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::size_type
    StackArray<STACK_ARRAY_PARAMS>::capacity() const
  {
    return m_values.GetSize();
  }

  template <STACK_ARRAY_TYPES>
  TL_I bool StackArray<STACK_ARRAY_PARAMS>::empty() const
  {
    return size() == 0;
  }

  template <STACK_ARRAY_TYPES>
  TL_I bool StackArray<STACK_ARRAY_PARAMS>::full() const
  {
    return (size() == capacity());
  }

  //------------------------------------------------------------------------
  // Modifiers

};};

#endif