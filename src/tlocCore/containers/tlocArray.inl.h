#ifndef TLOC_ARRAY_INL
#define TLOC_ARRAY_INL

#ifndef TLOC_ARRAY_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/iterators/tlocIterator.inl.h>
#include <tlocCore/memory/tlocMemory.inl.h>
#include <tlocCore/types/tlocTypeTraits.h>

namespace tloc { namespace core { namespace containers {

  //////////////////////////////////////////////////////////////////////////
  // Assertion macros

#define TLOC_PRINT_ARRAY_INDEX_OUT_OF_RANGE(index) \
#index " is out of range!"

#define TLOC_ASSERT_ARRAY_INDEX(index) \
  TLOC_ASSERT_ARRAY(index < size(), "Index out of bounds!")

#define TLOC_ASSERT_ARRAY_NOT_EMPTY() \
  TLOC_ASSERT_ARRAY(size() > 0, "Array is empty!")

#define TLOC_ASSERT_ARRAY_NOT_FULL() \
  TLOC_ASSERT_ARRAY(full() == false, "Array is full!")

#define TLOC_ASSERT_ARRAY_POSITION(_position_) \
  TLOC_ASSERT_ARRAY(_position_ >= m_begin && _position_ <= m_end,\
TLOC_PRINT_ARRAY_INDEX_OUT_OF_RANGE(_position_) )

#define TLOC_ASSERT_ARRAY_RANGE_BEGIN_AND_NOT_EQUAL_END(rangeBegin) \
  TLOC_ASSERT_ARRAY(rangeBegin >= m_begin && rangeBegin < m_end,\
TLOC_PRINT_ARRAY_INDEX_OUT_OF_RANGE(rangeBegin) )

#define TLOC_ASSERT_ARRAY_RANGE_BEGIN(rangeBegin) \
  TLOC_ASSERT_ARRAY(rangeBegin >= m_begin,\
TLOC_PRINT_ARRAY_INDEX_OUT_OF_RANGE(rangeBegin) )

#define TLOC_ASSERT_ARRAY_RANGE_END(rangeEnd) \
  TLOC_ASSERT_ARRAY(rangeEnd <= m_end,\
TLOC_PRINT_ARRAY_INDEX_OUT_OF_RANGE(rangeEnd) )

#define TLOC_ASSERT_ARRAY_RANGE(_rangeBegin_, _rangeEnd_) \
  TLOC_ASSERT_ARRAY(_rangeBegin_ <= _rangeEnd_, #_rangeBegin_\
                    " must be smaller than " #_rangeEnd_)

#define TLOC_ASSERT_ARRAY_RANGE_BEGIN_END(_rangeBegin_, _rangeEnd_) \
  TLOC_ASSERT_ARRAY_RANGE_BEGIN(_rangeBegin_);\
  TLOC_ASSERT_ARRAY_RANGE_END(_rangeEnd_);\
  TLOC_ASSERT_ARRAY_RANGE(_rangeBegin_, _rangeEnd_);

  //////////////////////////////////////////////////////////////////////////
  // Template macros

#define ARRAY_BASE_TYPES typename T, typename T_Policy
#define ARRAY_BASE_PARAMS T, T_Policy

#define ARRAY_TYPES typename T, typename T_Policy
#define ARRAY_PARAMS T, T_Policy

  //////////////////////////////////////////////////////////////////////////
  // Constants

  template <ARRAY_BASE_TYPES>
  const tl_size ArrayBase<ARRAY_BASE_PARAMS>::sm_defaultCapacity = 2;

  //////////////////////////////////////////////////////////////////////////
  // ArrayBase<T, T_Policy>

  template <ARRAY_BASE_TYPES>
  ArrayBase<ARRAY_BASE_PARAMS>::ArrayBase()
    : m_begin(nullptr)
    , m_end(nullptr)
    , m_capacity(nullptr)
  {
  }

  template <ARRAY_BASE_TYPES>
  ArrayBase<ARRAY_BASE_PARAMS>::ArrayBase(size_type a_size)
  {
    m_begin = DoAllocate(a_size);
    TLOC_ASSERT_CONTAINERS(m_begin != nullptr || a_size == 0,
                            "Could not allocate Array!");
    m_end = m_begin;
    m_capacity = m_begin + a_size;
  }

  template <ARRAY_BASE_TYPES>
  ArrayBase<ARRAY_BASE_PARAMS>::~ArrayBase()
  {
    if (m_begin)
    {
      DoDestroyValues(m_begin, m_end);
      DoFree(m_begin);
    }
  }

  //------------------------------------------------------------------------
  // General

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::size_type
    ArrayBase<ARRAY_BASE_PARAMS>::defaultCapacity()
  {
    return sm_defaultCapacity;
  }

  //------------------------------------------------------------------------
  // Assignment

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::this_type&
    ArrayBase<ARRAY_BASE_PARAMS>::operator= (const this_type& a_toCopy)
  {
    TLOC_ASSERT_ARRAY(&a_toCopy != this, "Assigning array to itself!");

    const ArrayBase<ARRAY_BASE_PARAMS>::size_type sizeOfOther = a_toCopy.size();
    if (sizeOfOther > capacity())
    {
      clear();
      m_begin    = DoReAllocate(sizeOfOther);
      m_end      = uninitialized_copy(a_toCopy.begin(),
                                      a_toCopy.end(),
                                      m_begin);
      m_capacity = m_end;
    }
    else if (sizeOfOther > size())
    {
      copy(a_toCopy.begin(), a_toCopy.begin() + (m_end - m_begin), m_begin);
      m_end = uninitialized_copy(a_toCopy.begin() + (m_end - m_begin),
                                 a_toCopy.end(),
                                 m_end);
    }
    else
    {
      const ArrayBase<ARRAY_BASE_PARAMS>::iterator itr =
        copy(a_toCopy.begin(), a_toCopy.end(), m_begin);
      if (itr != m_end)
      {
        erase(itr, m_end);
        m_end = itr;
      }
    }
    return *this;
  }

  //------------------------------------------------------------------------
  // Element access

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::reference
    ArrayBase<ARRAY_BASE_PARAMS>::at(size_type a_index)
  {
    TLOC_ASSERT_ARRAY_INDEX(a_index);
    return *(m_begin + a_index);
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::const_reference
    ArrayBase<ARRAY_BASE_PARAMS>::at(size_type a_index) const
  {
    TLOC_ASSERT_ARRAY_INDEX(a_index);
    return *(m_begin + a_index);
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::reference
    ArrayBase<ARRAY_BASE_PARAMS>::operator[](size_type a_index)
  {
    TLOC_ASSERT_ARRAY_INDEX(a_index);
    return *(m_begin + a_index);
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::const_reference
    ArrayBase<ARRAY_BASE_PARAMS>::operator[](size_type a_index) const
  {
    TLOC_ASSERT_ARRAY_INDEX(a_index);
    return *(m_begin + a_index);
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::reference
    ArrayBase<ARRAY_BASE_PARAMS>::front()
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return *m_begin;
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::const_reference
    ArrayBase<ARRAY_BASE_PARAMS>::front() const
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return *m_begin;
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::reference
    ArrayBase<ARRAY_BASE_PARAMS>::back()
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return *(m_end - 1);
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::const_reference
    ArrayBase<ARRAY_BASE_PARAMS>::back() const
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return *(m_end - 1);
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::pointer
    ArrayBase<ARRAY_BASE_PARAMS>::data()
  {
    return m_begin;
  }

  //------------------------------------------------------------------------
  // Iterator access

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::iterator
    ArrayBase<ARRAY_BASE_PARAMS>::begin()
  {
    return m_begin;
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::const_iterator
    ArrayBase<ARRAY_BASE_PARAMS>::begin() const
  {
    return m_begin;
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::iterator
    ArrayBase<ARRAY_BASE_PARAMS>::end()
  {
    return m_end;
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::const_iterator
    ArrayBase<ARRAY_BASE_PARAMS>::end() const
  {
    return m_end;
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::reverse_iterator
    ArrayBase<ARRAY_BASE_PARAMS>::rbegin()
  {
    return reverse_iterator(end());
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::const_reverse_iterator
    ArrayBase<ARRAY_BASE_PARAMS>::rbegin() const
  {
    return const_reverse_iterator(end());
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::reverse_iterator
    ArrayBase<ARRAY_BASE_PARAMS>::rend()
  {
    return reverse_iterator(begin());
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::const_reverse_iterator
    ArrayBase<ARRAY_BASE_PARAMS>::rend() const
  {
    return const_reverse_iterator(begin());
  }

  //------------------------------------------------------------------------
  // Capacity

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::size_type
    ArrayBase<ARRAY_BASE_PARAMS>::size() const
  {
    return (m_end - m_begin);
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::size_type
    ArrayBase<ARRAY_BASE_PARAMS>::capacity() const
  {
    return (m_capacity - m_begin);
  }

  template <ARRAY_BASE_TYPES>
  bool ArrayBase<ARRAY_BASE_PARAMS>::empty() const
  {
    return size() == 0;
  }

  template <ARRAY_BASE_TYPES>
  bool ArrayBase<ARRAY_BASE_PARAMS>::full() const
  {
    return (m_end == m_capacity);
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <ARRAY_BASE_TYPES>
  void ArrayBase<ARRAY_BASE_PARAMS>::pop_back()
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    --m_end;
    m_end->~value_type();
  }

  template <ARRAY_BASE_TYPES>
  void ArrayBase<ARRAY_BASE_PARAMS>::pop_back(reference a_out)
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    a_out = *(m_end - 1);
    pop_back();
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::iterator
    ArrayBase<ARRAY_BASE_PARAMS>::erase(iterator a_position)
  {
    return DoErase(a_position, policy_type());
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::iterator
    ArrayBase<ARRAY_BASE_PARAMS>::erase(iterator a_rangeBegin, iterator a_rangeEnd)
  {
    TLOC_ASSERT_ARRAY_RANGE_BEGIN_END(a_rangeBegin, a_rangeEnd);

    iterator const destroyFrom = copy(a_rangeEnd, m_end, a_rangeBegin);
    DoDestroyValues(destroyFrom, m_end);

    m_end = m_end - (a_rangeEnd - a_rangeBegin);

    return a_rangeBegin;
  }

  template <ARRAY_BASE_TYPES>
  void ArrayBase<ARRAY_BASE_PARAMS>::clear()
  {
    if (!empty())
    {
      erase(m_begin, m_end);
    }
  }

  template <ARRAY_BASE_TYPES>
  void ArrayBase<ARRAY_BASE_PARAMS>::swap(this_type& a_vec)
  {
    core::swap(m_begin, a_vec.m_begin);
    core::swap(m_end, a_vec.m_end);
    core::swap(m_capacity, a_vec.m_capacity);
  }

  //------------------------------------------------------------------------
  // Internal functions

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::pointer
    ArrayBase<ARRAY_BASE_PARAMS>::DoAllocate(const size_type& a_size)
  {
    return a_size ? (pointer)TL_MALLOC(a_size * sizeof(value_type)) : nullptr;
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::pointer
    ArrayBase<ARRAY_BASE_PARAMS>::DoReAllocate(const size_type& a_size)
  {
    typedef Loki::Int2Type<Loki::TypeTraits<value_type>::isFundamental ||
      Loki::TypeTraits<value_type>::isPointer>    simple_or_complex_type;

    return DoReallocateWithCopy(a_size, simple_or_complex_type());
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::pointer
    ArrayBase<ARRAY_BASE_PARAMS>::
    DoReallocateWithCopy(size_type a_size, array_simple_type)
  {
    return (pointer)TL_REALLOC(m_begin, sizeof(value_type) * a_size);
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::pointer
    ArrayBase<ARRAY_BASE_PARAMS>::
    DoReallocateWithCopy(size_type a_size, array_complex_type)
  {
    this_type temp(a_size);
    temp = *this;
    swap(temp);
    return (pointer)m_begin;
  }

  template <ARRAY_BASE_TYPES>
  void ArrayBase<ARRAY_BASE_PARAMS>::DoFree(pointer a_ptr)
  {
    TL_FREE(a_ptr);
  }

  template <ARRAY_BASE_TYPES>
  void ArrayBase<ARRAY_BASE_PARAMS>::DoDestroyValues(pointer a_rangeBegin,
                                                     pointer a_rangeEnd)
  {
    while (a_rangeBegin != a_rangeEnd)
    {
      a_rangeBegin->~T(); // not using value_type here to avoid ambiguities
      ++a_rangeBegin;
    }
  }

  template <ARRAY_BASE_TYPES>
  void ArrayBase<ARRAY_BASE_PARAMS>::DoAddToEnd(const_reference a_valueToCopy)
  {
    TLOC_ASSERT_ARRAY_NOT_FULL();

    new(m_end) value_type(a_valueToCopy); // placement new
    ++m_end;
  }

  template <ARRAY_BASE_TYPES>
  void ArrayBase<ARRAY_BASE_PARAMS>::DoReAllocate()
  {
    const size_type prevSize = size();
    const size_type prevCap  = capacity();
    const size_type newCap   = prevCap ? (2 * prevCap) : sm_defaultCapacity;
    pointer ptr;

    // DoReallocate may malloc or realloc depending on the initial size
    ptr = DoReAllocate(newCap);

    TLOC_ASSERT_ARRAY(ptr != nullptr, "Could not allocate/re-allocate!");

    if (ptr)
    {
      m_begin = ptr;
      m_end = m_begin + prevSize;
      m_capacity = m_begin + newCap;
    }
  }

  //------------------------------------------------------------------------
  // erase() helpers

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::iterator
    ArrayBase<ARRAY_BASE_PARAMS>::DoErase(iterator a_position, Array_Ordered)
  {
    TLOC_ASSERT_ARRAY_RANGE_BEGIN_AND_NOT_EQUAL_END(a_position);

    if ( (a_position + 1) < m_end)
    { copy(a_position + 1, m_end, a_position); }
    --m_end;
    m_end->~value_type();

    return a_position;
  }

  template <ARRAY_BASE_TYPES>
  typename ArrayBase<ARRAY_BASE_PARAMS>::iterator
    ArrayBase<ARRAY_BASE_PARAMS>::DoErase(iterator a_position, Array_Unordered)
  {
    TLOC_ASSERT_ARRAY_RANGE_BEGIN_AND_NOT_EQUAL_END(a_position);

    --m_end;
    *a_position = *m_end;
    m_end->~value_type();

    return a_position;
  }

  //////////////////////////////////////////////////////////////////////////
  // Array<T, T_Policy>

  //------------------------------------------------------------------------
  // Constructors

  template <ARRAY_TYPES>
  Array<ARRAY_PARAMS>::Array() : base_type()
  {
  }

  template <ARRAY_TYPES>
  Array<ARRAY_PARAMS>::Array(const this_type& a_toCopy)
    : base_type(a_toCopy.size())
  {
    /*insert(m_begin, toCopy.m_begin, toCopy.m_end);*/
    m_end = uninitialized_copy(a_toCopy.m_begin, a_toCopy.m_end, m_begin);
  }

  template <ARRAY_TYPES>
  Array<ARRAY_PARAMS>::Array(size_type a_numElemsToInsert,
                                   const_reference a_valueToCopy)
    : base_type(a_numElemsToInsert)
  {
    /*insert(0, aNumElemsToInsert, aValueToCopy);*/
    uninitialized_fill_n(m_begin, a_numElemsToInsert, a_valueToCopy);
    m_end = m_begin + a_numElemsToInsert;
  }

  template <ARRAY_TYPES>
  Array<ARRAY_PARAMS>::Array(size_type a_count) : base_type(a_count)
  {
    uninitialized_fill_n(m_begin, a_count, value_type());
    m_end = m_begin + a_count;
  }

  template <ARRAY_TYPES>
  template <typename T_InputIterator>
  Array<ARRAY_PARAMS>::Array(T_InputIterator a_rangeBegin,
                                   T_InputIterator a_rangeEnd)
    : base_type()
  {
    insert(m_begin, a_rangeBegin, a_rangeEnd);
  }

  //------------------------------------------------------------------------
  // Capacity

  template <ARRAY_TYPES>
  void Array<ARRAY_PARAMS>::resize(size_type a_newSize)
  {
    size_type currSize = size();
    if (a_newSize > currSize)
    {
      insert(m_end, a_newSize - currSize, value_type());
    }
    else
    {
      erase(m_begin + a_newSize, m_end);
    }
  }

  template <ARRAY_TYPES>
  void Array<ARRAY_PARAMS>::resize(size_type a_newSize,
                                        const_reference a_value)
  {
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

  template <ARRAY_TYPES>
  void Array<ARRAY_PARAMS>::reserve(size_type a_newCapacity)
  {
    if (a_newCapacity > capacity())
    {
      pointer ptr = DoReAllocate(a_newCapacity);

      TLOC_ASSERT_ARRAY(ptr, "Could not re-allocate!");

      if (ptr)
      {
        const size_type prevSize = size();
        m_begin     = ptr;
        m_end       = ptr + prevSize;
        m_capacity  = ptr + a_newCapacity;
      }

    }
  }

  template <ARRAY_TYPES>
  void Array<ARRAY_PARAMS>::shrink(size_type a_newCapacity)
  {
    if (a_newCapacity < capacity())
    {
      size_type newSize = size();

      // If the new capacity is smaller than the number of elements we are
      // currently, storing, we need to destroy those elements
      if (a_newCapacity < newSize)
      {
        newSize = a_newCapacity;
        erase(m_begin + a_newCapacity, m_end);
      }

      pointer ptr = DoReAllocate(a_newCapacity);

      TLOC_ASSERT_ARRAY(ptr, "Could not re-allocate!");

      if (ptr)
      {
        m_begin = ptr;
        m_end = ptr + newSize;
        m_capacity = ptr + a_newCapacity;
      }
    }
  }

  template <ARRAY_TYPES>
  void Array<ARRAY_PARAMS>::shrink_to_fit()
  {
    shrink(size());
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <ARRAY_TYPES>
  void Array<ARRAY_PARAMS>::assign(size_type a_repetitionNum,
                                        const_reference a_elemToCopy)
  {
    if (size() < a_repetitionNum)
    {
      resize(a_repetitionNum);
    }

    fill_n(m_begin, a_repetitionNum, a_elemToCopy);
  }

  template <ARRAY_TYPES>
  template <typename T_InputIterator>
  void Array<ARRAY_PARAMS>::assign(T_InputIterator a_rangeBegin,
                                        T_InputIterator a_rangeEnd)
  {
    typedef typename Loki::TypeTraits<T_InputIterator> inputUnknown;
    typedef typename Loki::Int2Type<inputUnknown::isArith> inputArith;

    // The correct DoInsert() will be called depending on whether inputIntegral
    // is Int2Type<true> or Int2Type<false>
    DoAssign(a_rangeBegin, a_rangeEnd, inputArith());
  }

  template <ARRAY_TYPES>
  void Array<ARRAY_PARAMS>::push_back(const_reference a_valueToCopy)
  {
    if (m_end < m_capacity)
    {
      DoAddToEnd(a_valueToCopy);
    }
    else
    {
      DoReAllocate();
      DoAddToEnd(a_valueToCopy);
    }
  }

  template <ARRAY_TYPES>
  typename Array<ARRAY_PARAMS>::iterator
    Array<ARRAY_PARAMS>::insert(iterator a_position, const_reference a_valueToCopy)
  {
    TLOC_ASSERT_ARRAY_POSITION(a_position);

    const size_type posIndex = a_position - m_begin;

    if (full() || a_position != m_end)
    {
      DoInsertValue(a_position, a_valueToCopy);
    }
    else
    {
      ::new(m_end++) value_type(a_valueToCopy);
    }

    return m_begin + posIndex;;
  }

  template <ARRAY_TYPES>
  void Array<ARRAY_PARAMS>::insert(iterator a_position,
                                        size_type a_numElemsToInsert,
                                        const_reference a_valueToCopy)
  {
    DoInsertValues(a_position, a_numElemsToInsert, a_valueToCopy);
  }

  template <ARRAY_TYPES>
  template <typename T_InputIterator>
  void Array<ARRAY_PARAMS>::insert(iterator a_position,
                                        T_InputIterator a_rangeBegin,
                                        T_InputIterator a_rangeEnd)
  {
    typedef typename Loki::TypeTraits<T_InputIterator> inputUnknown;
    typedef typename Loki::Int2Type<inputUnknown::isIntegral> inputIntegral;

    // The correct DoInsert() will be called depending on whether inputIntegral
    // is Int2Type<true> or Int2Type<false>
    DoInsert(a_position, a_rangeBegin, a_rangeEnd, inputIntegral());
  }

  template <ARRAY_TYPES>
  void Array<ARRAY_PARAMS>::swap(this_type& a_vec)
  {
    base_type::swap(a_vec);
  }

  //------------------------------------------------------------------------
  // Internal functions

  //------------------------------------------------------------------------
  // assign() helpers

  template <ARRAY_TYPES>
  template <typename T_Number>
  void Array<ARRAY_PARAMS>::DoAssign(T_Number a_repetitionNum,
                                          T_Number a_elemToCopy,
                                          is_arith_t)
  {
    assign(static_cast<size_type>(a_repetitionNum),
           static_cast<value_type>(a_elemToCopy));
  }

  template <ARRAY_TYPES>
  template <typename T_InputIterator>
  void Array<ARRAY_PARAMS>::DoAssign(T_InputIterator a_rangeBegin,
                                          T_InputIterator a_rangeEnd,
                                          is_not_arith_t)
  {
    size_type projectedSize = tloc::core::distance(a_rangeBegin, a_rangeEnd);
    if (size() < projectedSize)
    {
      resize(projectedSize);
    }

    copy(a_rangeBegin, a_rangeEnd, m_begin);
  }

  //------------------------------------------------------------------------
  // insert() helpers

  template <ARRAY_TYPES>
  void Array<ARRAY_PARAMS>::DoInsertValue(iterator a_position,
                                               const_reference a_value)
  {
    TLOC_ASSERT_ARRAY_POSITION(a_position);

    if (m_end != m_capacity)
    {
      // Value may be from within the range of the array, in which case, the
      // pointer will be moved by one to where it will be once everything is
      // moved over.
      const_pointer valuePtr = &a_value;
      if (valuePtr >= a_position && valuePtr < m_end)
      {
        ++valuePtr;
      }

      // We directly assume that the value is not going to be inserted at m_end
      // at this point.
      ::new(m_end) value_type(*(m_end - 1)); // We need initialize and move the end value
      copy_backward(a_position, m_end - 1, m_end);
      *a_position = *valuePtr;
      ++m_end;
    }
    else
    {
      // Value may be from within the range of the array, in which case, it may
      // be destroyed, so make a copy
      const value_type valueCopy = a_value;
      size_type posIndex = a_position - m_begin;
      DoReAllocate();
      insert(m_begin + posIndex, valueCopy);
    }
  }

  template <ARRAY_TYPES>
  void Array<ARRAY_PARAMS>::DoInsertValues(iterator a_position,
                                                size_type a_numElemsToInsert,
                                                const_reference a_value)
  {
    TLOC_ASSERT_ARRAY_POSITION(a_position);
    TLOC_ASSERT_ARRAY(a_numElemsToInsert > 0, "Inserting 0 elements!");

    // value may be from within the array, copy it
    const value_type valueCopy = a_value;

    // Check if we have enough capacity to store the elements
    if (a_numElemsToInsert <= size_type(m_capacity - m_end) )
    {
      //OPT: Not the most optimized solution, may want to re-work it

      const size_type elemsToMove = (size_type)(m_end - a_position);
      const size_type spaceRequired = elemsToMove + a_numElemsToInsert;

      // Allocate all un-allocated space
      while (m_end != a_position + spaceRequired)
      {
        ::new(m_end) value_type();
        ++m_end;
      }

      copy_backward(a_position, a_position + elemsToMove, m_end);

      while (a_position != m_end - elemsToMove)
      {
        *(a_position) = a_value;
        ++a_position;
      }
    }
    else
    {
      size_type posIndex = a_position - m_begin;

      // Reallocate
      // TODO: Replace with resize() once implemented
      size_type prevSize = size();
      size_type newCap  = capacity() + a_numElemsToInsert;
      pointer ptr;

      // DoReallocate may malloc or realloc depending on the initial size
      ptr = DoReAllocate(newCap);

      TLOC_ASSERT_ARRAY(ptr != nullptr, "Could not allocate/re-allocate!");

      if (ptr)
      {
        m_begin = ptr;
        m_end = m_begin + prevSize;
        m_capacity = m_begin + newCap;
      }

      insert(m_begin + posIndex, a_numElemsToInsert, valueCopy);
    }
  }

  template <ARRAY_TYPES>
  template <typename T_Number>
  void Array<ARRAY_PARAMS>::DoInsert(iterator a_position,
                                          T_Number a_n,
                                          T_Number a_value,
                                          is_integral_t)
  {
    insert(a_position, static_cast<size_type>(a_n),
           static_cast<value_type>(a_value));
  }

  template <ARRAY_TYPES>
  template <typename T_InputIterator>
  void Array<ARRAY_PARAMS>::DoInsert(iterator a_position,
                                          T_InputIterator a_first,
                                          T_InputIterator a_last,
                                          is_not_integral_t)
  {
    DoInsertByIterator(a_position, a_first, a_last);
  }

  template <ARRAY_TYPES>
  template <typename T_InputIterator>
  void Array<ARRAY_PARAMS>::DoInsertByIterator(iterator a_position,
                                                    T_InputIterator a_first,
                                                    T_InputIterator a_last)
  {
    TLOC_ASSERT_ARRAY_RANGE(a_first, a_last);
    size_type newSize = size() + static_cast<size_type>(tloc::core::distance(a_first, a_last));

    if (capacity() >= newSize)
    {
      while (a_first != a_last)
      {
        a_position = insert(a_position, *a_first++);
        ++a_position;
      }
    }
    else
    {
      const size_type oldPosition =
        static_cast<size_type>(tloc::core::distance(m_begin, a_position));
      reserve(newSize); // 'position' is now invalid
      DoInsertByIterator(m_begin + oldPosition, a_first, a_last);
    }
  }

};};};

#define TLOC_EXPLICITLY_INSTANTIATE_ARRAY(_type_)\
  template class tloc::core_conts::ArrayBase<_type_, tloc::core_conts::Array_Unordered>;\
  template class tloc::core_conts::ArrayBase<_type_, tloc::core_conts::Array_Ordered>;\
  template class tloc::core_conts::Array<_type_, tloc::core_conts::Array_Unordered>;\
  template class tloc::core_conts::Array<_type_, tloc::core_conts::Array_Ordered>

#endif
