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

  template <STACK_ARRAY_TYPES>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::assign(size_type a_repetitionNum,
                                                   const value_type & a_elemToCopy)
  {
    fill_n(m_values, a_repetitionNum, a_elemToCopy);
  }

  template <STACK_ARRAY_TYPES>
  template <typename T_InputIterator>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::assign(T_InputIterator a_rangeBegin, 
                                                   T_InputIterator a_rangeEnd)
  {
    typedef Loki::TypeTraits<T_InputIterator> inputUnknown;
    typedef Loki::Int2Type<inputUnknown::isArith> inputArith;

    // The correct DoInsert() will be called depending on whether inputIntegral
    // is Int2Type<true> or Int2Type<false>
    DoAssign(a_rangeBegin, a_rangeEnd, inputArith());
  }

  template <STACK_ARRAY_TYPES>
  TL_I void 
    StackArray<STACK_ARRAY_PARAMS>::push_back(const value_type& a_valueToCopy)
  {
    DoAddToEnd(a_valueToCopy);
  }

  template <STACK_ARRAY_TYPES>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::pop_back()
  {
    --m_end;
  }

  template <STACK_ARRAY_TYPES>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::pop_back(value_type& a_out)
  {
    a_out = *(m_end - 1);
    pop_back();
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::iterator
    StackArray<STACK_ARRAY_PARAMS>::insert(iterator a_position, 
                                           const value_type& a_valueToCopy)
  {
    if (a_position != m_end)
    {
      DoInsertValue(a_position, a_valueToCopy);
    }
    else
    {
      *m_end = a_valueToCopy;
      ++m_end;
    }
  }

  template <STACK_ARRAY_TYPES>
  TL_I void 
    StackArray<STACK_ARRAY_PARAMS>::insert(value_type* a_position, 
                                           size_type a_numElemsToInsert, 
                                           const value_type& a_valueToCopy)
  {
    DoInsertValues(a_position, a_numElemsToInsert, a_valueToCopy);
  }

  template <STACK_ARRAY_TYPES>
  template <typename T_InputIterator>
  TL_I void 
    StackArray<STACK_ARRAY_PARAMS>::insert(iterator a_position, 
                                           T_InputIterator a_rangeBegin, 
                                           T_InputIterator a_rangeEnd)
  {
    typedef Loki::TypeTraits<T_InputIterator> inputUnknown;
    typedef Loki::Int2Type<inputUnknown::isIntegral> inputIntegral;

    // The correct DoInsert() will be called depending on whether inputIntegral
    // is Int2Type<true> or Int2Type<false> 
    DoInsert(a_position, a_rangeBegin, a_rangeEnd, inputIntegral());
  }

  //------------------------------------------------------------------------
  // push_back() Helpers

  template <STACK_ARRAY_TYPES>
  TL_I void 
    StackArray<STACK_ARRAY_PARAMS>::DoAddToEnd(const value_type& a_valueToCopy)
  {
    *m_end = a_valueToCopy;
    ++m_end;
  }

  //------------------------------------------------------------------------
  // insert() Helpers

  template <STACK_ARRAY_TYPES>
  TL_I void 
    StackArray<STACK_ARRAY_PARAMS>::DoInsertValue(value_type* a_position, 
                                                  const value_type& a_value)
  {
    // Value may be from within the range of the array, in which case, we grab
    // a pointer to the value and increment it by one to where it will be
    // located once everything is moved over. 
    const value_type* valuePtr = &a_value;
    if (valuePtr >= a_position && valuePtr < m_end)
    {
      ++valuePtr;
    }

    // We directly assume that the value is not going to be inserted at m_end
    // at this point
    ++m_end;
    copy_backward(a_position, m_end - 1, m_end);
    *a_position = *valuePtr;
  }

  template <STACK_ARRAY_TYPES>
  TL_I void 
    StackArray<STACK_ARRAY_PARAMS>::DoInsertValues(value_type* a_position, 
                                                   size_type a_numElemsToInsert, 
                                                   const value_type& a_value)
  {
    // Value may be from within the range of the array, in which case, we grab
    // a pointer to the value and increment it by one to where it will be
    // located once everything is moved over. 
    const value_type* valuePtr = &a_value;
    if (valuePtr >= a_position && valuePtr < m_end)
    {
      valuePtr += a_numElemsToInsert;
    }

    m_end += a_numElemsToInsert;
    copy_backward(a_position, m_end - a_numElemsToInsert, m_end);
    fill_n(a_position, a_numElemsToInsert, a_value);
  }

  template <STACK_ARRAY_TYPES>
  template <typename T_Number>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::DoInsert(iterator a_position, 
                                                     T_Number a_n, 
                                                     T_Number a_value, 
                                                     is_integral_t)
  {
    insert(static_cast<size_type>(a_n), static_cast<value_type>(a_value));
  }

  template <STACK_ARRAY_TYPES>
  template <typename T_InputIterator>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::DoInsert(iterator a_position, 
                                                     T_InputIterator a_first, 
                                                     T_InputIterator a_last, 
                                                     is_not_integral_t)
  {
    DoInsertByIterator(a_position, a_first, a_last);
  }

  template <STACK_ARRAY_TYPES>
  template <typename T_InputIterator>
  TL_I void 
    StackArray<STACK_ARRAY_PARAMS>::DoInsertByIterator(iterator a_position, 
                                                       T_InputIterator a_first, 
                                                       T_InputIterator a_last)
  {
    while (a_first != a_last)
    {
      a_position = insert(a_position, *a_first);
      ++a_first;
      ++a_position;
    }
  }

  //------------------------------------------------------------------------
  // assign() helpers

  template <STACK_ARRAY_TYPES>
  template <typename T_Number>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::DoAssign(T_Number a_repetitionNum, 
                                                     T_Number a_elemToCopy, 
                                                     is_arith_t)
  {
    assign(static_cast<size_type>(a_repetitionNum), 
           static_cast<value_type>(a_elemToCopy));
  }

  template <STACK_ARRAY_TYPES>
  template <typename T_InputIterator>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::DoAssign(T_InputIterator a_rangeBegin, 
                                                     T_InputIterator a_rangeEnd, 
                                                     is_not_arith_t)
  {
    copy(a_rangeBegin, a_rangeEnd, m_values);
  }

};};

#endif