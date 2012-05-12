#ifndef TLOC_STACK_ARRAY_INL
#define TLOC_STACK_ARRAY_INL

#ifndef TLOC_STACK_ARRAY_H
#error "Must include header before including the inline file"
#endif

#include "tlocAlgorithms.inl"

namespace tloc { namespace core{

  //////////////////////////////////////////////////////////////////////////
  // Assertion macros

#define TLOC_PRINT_STACK_ARRAY_INDEX_OUT_OF_RANGE(a_index) \
#a_index _CRT_WIDE(" is out of range!")

#define TLOC_ASSERT_STACK_ARRAY_INDEX(a_index) \
  TLOC_ASSERT_STACK_ARRAY(a_index >= 0 && a_index < size() , "Index out of bounds")

#define TLOC_ASSERT_STACK_ARRAY_NOT_EMPTY() \
  TLOC_ASSERT_STACK_ARRAY(size() > 0, "Stack Array is empty!")

#define TLOC_ASSERT_STACK_ARRAY_NOT_FULL() \
  TLOC_ASSERT_STACK_ARRAY(full() == false, "Stack Array is full!")

#define TLOC_ASSERT_STACK_ARRAY_POSITION_END_EXCLUSIVE(a_position) \
  TLOC_ASSERT_STACK_ARRAY(a_position >= m_values && a_position <= m_end, \
TLOC_PRINT_STACK_ARRAY_INDEX_OUT_OF_RANGE(position) )

#define TLOC_ASSERT_STACK_ARRAY_POSITION_END_INCLUSIVE(a_position) \
  TLOC_ASSERT_STACK_ARRAY(a_position >= m_values && a_position < m_end, \
  TLOC_PRINT_STACK_ARRAY_INDEX_OUT_OF_RANGE(position) )

#define TLOC_ASSERT_STACK_ARRAY_RANGE_BEGIN(a_rangeBegin) \
  TLOC_ASSERT_STACK_ARRAY(a_rangeBegin >= m_begin, \
TLOC_PRINT_STACK_ARRAY_INDEX_OUT_OF_RANGE(a_rangeBegin) )

#define TLOC_ASSERT_STACK_ARRAY_RANGE_END(a_rangeEnd) \
  TLOC_ASSERT_STACK_ARRAY(a_rangeEnd <= m_end, \
TLOC_PRINT_STACK_ARRAY_INDEX_OUT_OF_RANGE(a_rangeEnd) )

#define TLOC_ASSERT_STACK_ARRAY_RANGE(a_rangeBegin, a_rangeEnd) \
  TLOC_ASSERT_STACK_ARRAY(a_rangeBegin <= a_rangeEnd, \
# a_rangeBegin _CRT_WIDE(" must be smaller than ") _CRT_WIDE(# a_rangeEnd) L"!")

#define TLOC_ASSERT_STACK_ARRAY_RANGE_BEGIN_END(a_rangeBegin, a_rangeEnd) \
  TLOC_ASSERT_STACK_ARRAY_RANGE_BEGIN(a_rangeBegin); \
  TLOC_ASSERT_STACK_ARRAY_RANGE_END(a_rangeEnd); \
  TLOC_ASSERT_ARRAY_RANGE(a_rangeBegin, a_rangeEnd)

#define TLOC_ASSERT_STACK_ARRAY_NEW_SIZE(a_size) \
  TLOC_ASSERT_STACK_ARRAY(a_size <= capacity(), "New size is larger than capacity!")

#define TLOC_STATIC_ASSERT_STACK_ARRAY_CAPACITY_GREATER_THAN_ZERO() \
  TLOC_STATIC_ASSERT(capacity() > 0, Capacity_of_Stack_Array_must_be_more_than_0)

  //////////////////////////////////////////////////////////////////////////
  // Template macros

#define STACK_ARRAY_TYPES typename T, tl_size T_Capacity
#define STACK_ARRAY_PARAMS T, T_Capacity

  //------------------------------------------------------------------------
  // Ctors

  template <STACK_ARRAY_TYPES>
  TL_FI StackArray<STACK_ARRAY_PARAMS>::StackArray()
    : m_values()
    : m_end(m_values)
  {
    TLOC_STATIC_ASSERT_STACK_ARRAY_CAPACITY_GREATER_THAN_ZERO();
  }

  template <STACK_ARRAY_TYPES>
  TL_FI StackArray<STACK_ARRAY_PARAMS>::StackArray(const this_type& a_toCopy)
    : m_values(a_toCopy.m_values)
  {
    TLOC_STATIC_ASSERT_STACK_ARRAY_CAPACITY_GREATER_THAN_ZERO();
    TLOC_ASSERT_STACK_ARRAY_NEW_SIZE(a_toCopy.size());

    m_end = m_values + a_toCopy.size();
  }

  template <STACK_ARRAY_TYPES>
  template <tl_size T_OtherCapacity>
  TL_FI StackArray<STACK_ARRAY_PARAMS>::StackArray(
    const StackArray<value_type, T_OtherCapacity>& a_toCopy)
  {
    TLOC_STATIC_ASSERT_STACK_ARRAY_CAPACITY_GREATER_THAN_ZERO();
    TLOC_ASSERT_STACK_ARRAY_NEW_SIZE(a_toCopy.size());

    *this = a_toCopy;
  }

  template <STACK_ARRAY_TYPES>
  TL_FI StackArray<STACK_ARRAY_PARAMS>::StackArray(size_type a_numElemsToInsert, 
                                                   const value_type& a_valueToCopy)
                                                   : m_values()
  {
    TLOC_STATIC_ASSERT_STACK_ARRAY_CAPACITY_GREATER_THAN_ZERO();
    TLOC_ASSERT_STACK_ARRAY_NEW_SIZE(a_numElemsToInsert);

    fill_n(m_values, a_numElemsToInsert, a_valueToCopy);
    m_end = m_values + a_numElemsToInsert;
  }

  template <STACK_ARRAY_TYPES>
  TL_FI StackArray<STACK_ARRAY_PARAMS>::StackArray(size_type a_count)
    : m_values()
  {
    TLOC_STATIC_ASSERT_STACK_ARRAY_CAPACITY_GREATER_THAN_ZERO();
    TLOC_ASSERT_STACK_ARRAY_NEW_SIZE(a_count);

    m_end = m_values + a_count;
  }

  template <STACK_ARRAY_TYPES>
  template <typename T_InputIterator>
  TL_FI StackArray<STACK_ARRAY_PARAMS>::StackArray(T_InputIterator a_rangeBegin, 
                                                   T_InputIterator a_rangeEnd)
                                                   : m_values()
                                                   : m_end(NULL)
  {
    TLOC_STATIC_ASSERT_STACK_ARRAY_CAPACITY_GREATER_THAN_ZERO();
    TLOC_ASSERT_STACK_ARRAY_NEW_SIZE(distance(a_rangeBegin, a_rangeEnd));

    insert(m_values, a_rangeBegin, a_rangeEnd);
  }

  //------------------------------------------------------------------------
  // Assignment

  template <STACK_ARRAY_TYPES>
  template <tl_size T_OtherCapacity>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::this_type& 
    StackArray<STACK_ARRAY_PARAMS>::operator= (
    const StackArray<value_type, T_OtherCapacity>& a_toCopy)
  {
    TLOC_ASSERT_STACK_ARRAY_NEW_SIZE(a_toCopy.size());

    m_end = m_values;
    advance(m_end, a_toCopy.size());
    copy(a_toCopy.m_values, a_toCopy.m_end, m_values);
    
    return *this;
  }

  //------------------------------------------------------------------------
  // Element access

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::reference
    StackArray<STACK_ARRAY_PARAMS>::at(size_type a_index)
  {
    TLOC_ASSERT_STACK_ARRAY_INDEX(a_index);
    return m_values.Get(a_index);
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::const_reference
    StackArray<STACK_ARRAY_PARAMS>::at(size_type a_index) const
  {
    TLOC_ASSERT_STACK_ARRAY_INDEX(a_index);
    return m_values.Get(a_index);
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::reference
    StackArray<STACK_ARRAY_PARAMS>::operator[] (size_type a_index)
  {
    TLOC_ASSERT_STACK_ARRAY_INDEX(a_index);
    return m_values.Get(a_index);
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::const_reference
    StackArray<STACK_ARRAY_PARAMS>::operator[] (size_type a_index) const
  {
    TLOC_ASSERT_STACK_ARRAY_INDEX(a_index);
    return m_values.Get(a_index);
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::reference
    StackArray<STACK_ARRAY_PARAMS>::front()
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return *m_values;
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::const_reference
    StackArray<STACK_ARRAY_PARAMS>::front() const
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return *m_values;
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::reference
    StackArray<STACK_ARRAY_PARAMS>::back()
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return *(m_end - 1);
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::const_reference
    StackArray<STACK_ARRAY_PARAMS>::back() const
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
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

  template <STACK_ARRAY_TYPES>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::resize(size_type a_newSize)
  {
    DoResize(a_newSize, value_type());
  }

  template <STACK_ARRAY_TYPES>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::resize(size_type a_newSize, 
                                                   value_type& a_value)
  {
    DoResize(a_newSize, a_value);
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <STACK_ARRAY_TYPES>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::assign(size_type a_repetitionNum,
                                                   const value_type & a_elemToCopy)
  {
    TLOC_ASSERT_STACK_ARRAY_NEW_SIZE(a_repetitionNum);

    m_end = m_values;
    advance(m_end, a_repetitionNum);

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
    TLOC_ASSERT_ARRAY_NOT_FULL();
    DoAddToEnd(a_valueToCopy);
  }

  template <STACK_ARRAY_TYPES>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::pop_back()
  {
    TLOC_ASSERT_STACK_ARRAY_NOT_EMPTY();
    --m_end;
  }

  template <STACK_ARRAY_TYPES>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::pop_back(value_type& a_out)
  {
    TLOC_ASSERT_STACK_ARRAY_NOT_EMPTY();
    a_out = *(m_end - 1);
    pop_back();
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::iterator
    StackArray<STACK_ARRAY_PARAMS>::insert(iterator a_position, 
                                           const value_type& a_valueToCopy)
  {
    TLOC_ASSERT_STACK_ARRAY_POSITION_END_EXCLUSIVE(a_position);

    if (a_position != m_end)
    {
      DoInsertValue(a_position, a_valueToCopy);
    }
    else
    {
      TLOC_ASSERT_STACK_ARRAY_NOT_FULL();

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

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::iterator
    StackArray<STACK_ARRAY_PARAMS>::erase(iterator a_position)
  {
    TLOC_ASSERT_STACK_ARRAY_NOT_EMPTY();
    TLOC_ASSERT_STACK_ARRAY_POSITION_END_INCLUSIVE(a_position);

    copy(a_position + 1, m_end, a_position);
    --m_end;

    return a_position;
  }

  template <STACK_ARRAY_TYPES>
  TL_I typename StackArray<STACK_ARRAY_PARAMS>::iterator
    StackArray<STACK_ARRAY_PARAMS>::erase(iterator a_rangeBegin, 
                                          iterator a_rangeEnd)
  {
    TLOC_ASSERT_STACK_ARRAY_NOT_EMPTY();
    TLOC_ASSERT_STACK_ARRAY_RANGE_BEGIN_END(a_rangeBegin, a_rangeEnd);

    copy(a_rangeEnd, m_end, a_rangeBegin);
    m_end -= distance(a_rangeBegin, a_rangeEnd);
    
    return a_rangeBegin;
  }

  template <STACK_ARRAY_TYPES>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::clear()
  {
    m_end = m_values;
  }

  template <STACK_ARRAY_TYPES>
  template <tl_size T_OtherCapacity>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::swap (
    StackArray<value_type, T_OtherCapacity>& a_vec)
  {
    StackArray<value_type, T_Capacity> temp(*this);
    *this = a_vec;
    a_vec = temp;
  }

  //------------------------------------------------------------------------
  // resize() Helper

  template <STACK_ARRAY_TYPES>
  TL_I void StackArray<STACK_ARRAY_PARAMS>::DoResize(size_type a_newSize, 
                                                     value_type& a_value)
  {
    TLOC_ASSERT_STACK_ARRAY_NEW_SIZE(a_newSize);

    size_type currSize = size();
    if (a_newSize > currSize)
    {
      insert(m_end, a_newSize - currSize, a_value);
    }
    else
    {
      erase(m_begin + a_newSize, m_end);
    }
  }

  //------------------------------------------------------------------------
  // push_back() Helpers

  template <STACK_ARRAY_TYPES>
  TL_I void 
    StackArray<STACK_ARRAY_PARAMS>::DoAddToEnd(const value_type& a_valueToCopy)
  {
    TLOC_ASSERT_STACK_ARRAY_NOT_FULL();

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
    TLOC_ASSERT_STACK_ARRAY_NOT_FULL();
    TLOC_ASSERT_STACK_ARRAY_POSITION_END_INCLUSIVE(a_position);

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
    TLOC_ASSERT_STACK_ARRAY_NEW_SIZE(size() + a_numElemsToInsert);
    TLOC_ASSERT_STACK_ARRAY_POSITION_END_INCLUSIVE(a_position);
    TLOC_ASSERT_ARRAY(a_numElemsToInsert > 0, "Inserting 0 elements!");

    // Value may be from within the range of the array, in which case, we grab
    // a pointer to the value and increment it by one to where it will be
    // located once everything is moved over. 
    const value_type* valuePtr = &a_value;
    if (valuePtr >= a_position && valuePtr < m_end)
    {
      tloc::core::advance(a_value, a_numElemsToInsert);
    }

    tloc::core::advance(m_end, a_numElemsToInsert);
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
    TLOC_ASSERT_STACK_ARRAY_NEW_SIZE(size() + tloc::core::distance(a_first, a_last));
    TLOC_ASSERT_STACK_ARRAY_RANGE(a_first, a_last);
    
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
    TLOC_ASSERT_STACK_ARRAY_RANGE(a_rangeBegin, a_rangeEnd);

    size_type projectedSize = tloc::core::distance(a_rangeBegin, a_rangeEnd);
    TLOC_ASSERT_STACK_ARRAY_NEW_SIZE(projectedSize);
    
    m_end = m_values;
    tloc::core::advance(m_end, projectedSize);

    copy(a_rangeBegin, a_rangeEnd, m_values);
  }

};};

#endif