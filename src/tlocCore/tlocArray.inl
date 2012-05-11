#ifndef TLOC_ARRAY_INL
#define TLOC_ARRAY_INL

#ifndef TLOC_ARRAY_H
#error "Must include header before including the inline file"
#endif

#include "tlocAlgorithms.inl"
#include "tlocIterator.inl"
#include "tlocMemory.inl"

namespace tloc { namespace core {

  //////////////////////////////////////////////////////////////////////////
  // Macros (mostly for assertions)

#define TLOC_PRINT_ARRAY_INDEX_OUT_OF_RANGE(index) \
#index _CRT_WIDE(" is out of range!")

#define TLOC_ASSERT_ARRAY_INDEX(index) \
  TLOC_ASSERT_ARRAY(index < size(), "Index out of bounds!")

#define TLOC_ASSERT_ARRAY_NOT_EMPTY() \
  TLOC_ASSERT_ARRAY(size() > 0, "Array is empty!")

#define TLOC_ASSERT_ARRAY_NOT_FULL() \
  TLOC_ASSERT_ARRAY(full() == false, "Array is full!")

#define TLOC_ASSERT_ARRAY_POSITION(position) \
  TLOC_ASSERT_ARRAY(position >= m_begin && position <= m_end,\
TLOC_PRINT_ARRAY_INDEX_OUT_OF_RANGE(position) )

#define TLOC_ASSERT_ARRAY_RANGE_BEGIN(rangeBegin) \
  TLOC_ASSERT_ARRAY(rangeBegin >= m_begin && rangeBegin <= m_end,\
TLOC_PRINT_ARRAY_INDEX_OUT_OF_RANGE(rangeBegin) )

#define TLOC_ASSERT_ARRAY_RANGE_END(rangeEnd) \
  TLOC_ASSERT_ARRAY(rangeEnd <= m_end,\
TLOC_PRINT_ARRAY_INDEX_OUT_OF_RANGE(rangeEnd) )

#define TLOC_ASSERT_ARRAY_RANGE(aRangeBegin, aRangeEnd) \
  TLOC_ASSERT_ARRAY(aRangeBegin <= aRangeEnd, \
# aRangeBegin _CRT_WIDE(" must be smaller than ") _CRT_WIDE(# aRangeEnd) L"!")

#define TLOC_ASSERT_ARRAY_RANGE_BEGIN_END(aRangeBegin, aRangeEnd) \
  TLOC_ASSERT_ARRAY_RANGE_BEGIN(aRangeBegin);\
  TLOC_ASSERT_ARRAY_RANGE_END(aRangeEnd);\
  TLOC_ASSERT_ARRAY_RANGE(aRangeBegin, aRangeEnd);

  //////////////////////////////////////////////////////////////////////////
  // Constants

  template <typename T>
  const tl_size ArrayBase<T>::sm_defaultCapacity = 2;

  //////////////////////////////////////////////////////////////////////////
  // ArrayBase<T>

  template <typename T>
  TL_FI ArrayBase<T>::ArrayBase()
    : m_begin(NULL)
    , m_end(NULL)
    , m_capacity(NULL)
  {
  }

  template <typename T>
  TL_FI ArrayBase<T>::ArrayBase( tl_size aSize )
  {
    m_begin = DoAllocate(aSize);
    TLOC_ASSERT_CONTAINERS(m_begin != NULL || aSize == 0,
                            "Could not allocate Array!");
    m_end = m_begin;
    m_capacity = m_begin + aSize;
  }

  template <typename T>
  TL_FI ArrayBase<T>::~ArrayBase()
  {
    if (m_begin)
    {
      DoDestroyValues(m_begin, m_end);
      DoFree(m_begin);
    }
  }

  //------------------------------------------------------------------------
  // Assignment
  
  template <typename T>
  TL_I typename ArrayBase<T>::this_type& 
    ArrayBase<T>::operator= (const this_type& aToCopy)
  {
    TLOC_ASSERT_ARRAY(&aToCopy != this, "Assigning array to itself!");
    
    const ArrayBase<T>::size_type sizeOfOther = aToCopy.size();
    if (sizeOfOther > capacity())
    {
      m_begin    = DoReAllocate(sizeOfOther);
      m_end      = uninitialized_copy(aToCopy.begin(), 
                                      aToCopy.end(), 
                                      m_begin);
      m_capacity = m_end;
    }
    else if (sizeOfOther > size())
    {
      copy(aToCopy.begin(), aToCopy.begin() + (m_end - m_begin), m_begin);
      m_end = uninitialized_copy(aToCopy.begin() + (m_end - m_begin), 
                                 aToCopy.end(), 
                                 m_end);
    }
    else
    {
      const ArrayBase<T>::iterator itr = copy(aToCopy.begin(), aToCopy.end(), m_begin);
      erase(itr, m_end);
      m_end = itr;
    }
    return *this;
  }

  //------------------------------------------------------------------------
  // Element access

  template <typename T>
  TL_I T& ArrayBase<T>::at( tl_size aIndex )
  {
    TLOC_ASSERT_ARRAY_INDEX(aIndex);
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I const T& ArrayBase<T>::at( tl_size aIndex ) const
  {
    TLOC_ASSERT_ARRAY_INDEX(aIndex);
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I T& ArrayBase<T>::operator[]( tl_size aIndex )
  {
    TLOC_ASSERT_ARRAY_INDEX(aIndex);
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I const T& ArrayBase<T>::operator[]( tl_size aIndex ) const
  {
    TLOC_ASSERT_ARRAY_INDEX(aIndex);
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I T& ArrayBase<T>::front()
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return *m_begin;
  }

  template <typename T>
  TL_I const T& ArrayBase<T>::front() const
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return *m_begin;
  }

  template <typename T>
  TL_I T& ArrayBase<T>::back()
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return *(m_end - 1);
  }

  template <typename T>
  TL_I const T& ArrayBase<T>::back() const
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    return *(m_end - 1);
  }

  template <typename T>
  TL_I T* ArrayBase<T>::data()
  {
    return m_begin;
  }

  //------------------------------------------------------------------------
  // Iterator access

  template <typename T>
  TL_I T* ArrayBase<T>::begin()
  {
    return m_begin;
  }

  template <typename T>
  TL_I const T* ArrayBase<T>::begin() const
  {
    return m_begin;
  }

  template <typename T>
  TL_I T* ArrayBase<T>::end()
  {
    return m_end;
  }

  template <typename T>
  TL_I const T* ArrayBase<T>::end() const
  {
    return m_end;
  }

  //------------------------------------------------------------------------
  // Capacity

  template <typename T>
  TL_I tl_size ArrayBase<T>::size() const
  {
    return (m_end - m_begin);
  }

  template <typename T>
  TL_I tl_size ArrayBase<T>::capacity() const
  {
    return (m_capacity - m_begin);
  }

  template <typename T>
  TL_I bool ArrayBase<T>::empty() const
  {
    return size() == 0;
  }

  template <typename T>
  TL_I bool ArrayBase<T>::full() const
  {
    return (m_end == m_capacity);
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <typename T>
  TL_I void ArrayBase<T>::pop_back()
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    --m_end;
    m_end->~T();
  }

  template <typename T>
  TL_I void ArrayBase<T>::pop_back( T& aOut )
  {
    TLOC_ASSERT_ARRAY_NOT_EMPTY();
    aOut = *(m_end - 1);
    pop_back();
  }

  template <typename T>
  TL_I typename ArrayBase<T>::iterator ArrayBase<T>::erase(iterator aPosition)
  {
    TLOC_ASSERT_ARRAY_RANGE_BEGIN(aPosition);

    aPosition->~T();
    copy(aPosition + 1, m_end, aPosition);
    --m_end;

    return aPosition;
  }

  template <typename T>
  TL_I typename ArrayBase<T>::iterator ArrayBase<T>
    ::erase( iterator aRangeBegin, iterator aRangeEnd )
  {
    TLOC_ASSERT_ARRAY_RANGE_BEGIN_END(aRangeBegin, aRangeEnd);

    iterator const destroyFrom = copy(aRangeEnd, m_end, aRangeBegin);
    DoDestroyValues(destroyFrom, m_end);

    m_end = m_end - (aRangeEnd - aRangeBegin);

    return aRangeBegin;
  }

  template <typename T>
  TL_I void ArrayBase<T>::clear()
  {
    erase(m_begin, m_end);
  }

  //------------------------------------------------------------------------
  // Internal functions

  template <typename T>
  TL_I T* ArrayBase<T>::DoAllocate( const tl_size& aSize )
  {
    return aSize ? (T*)TL_MALLOC(aSize * sizeof(T)) : NULL;
  }

  template <typename T>
  TL_I T* ArrayBase<T>::DoReAllocate( const tl_size& aSize )
  {
    return (T*)TL_REALLOC(m_begin, sizeof(T) * aSize);
  }

  template <typename T>
  TL_I void ArrayBase<T>::DoFree( T* aPtr)
  {
    TL_FREE(aPtr);
  }

  template <typename T>
  TL_I void ArrayBase<T>::DoDestroyValues(T* aRangeBegin, T* aRangeEnd)
  {
    while (aRangeBegin != aRangeEnd)
    {
      aRangeBegin->~T();
      ++aRangeBegin;
    }
  }

  template <typename T>
  TL_I void ArrayBase<T>::DoAddToEnd( const T& aValueToCopy )
  {
    TLOC_ASSERT_ARRAY_NOT_FULL();

    new(m_end) T(aValueToCopy); // placement new
    ++m_end;
  }

  template <typename T>
  TL_I void ArrayBase<T>::DoReAllocate()
  {
    const tl_size prevSize = size();
    const tl_size prevCap  = capacity();
    const tl_size newCap   = prevCap ? (2 * prevCap) : sm_defaultCapacity;
    T* ptr;

    // DoReallocate may malloc or realloc depending on the initial size
    ptr = DoReAllocate(newCap);

    TLOC_ASSERT_ARRAY(ptr != NULL, "Could not allocate/re-allocate!");

    if (ptr)
    {
      m_begin = ptr;
      m_end = m_begin + prevSize;
      m_capacity = m_begin + newCap;
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // Array<T>

  //------------------------------------------------------------------------
  // Constructors

  template <typename T>
  TL_FI Array<T>::Array() : ArrayBase()
  {
  }

  template <typename T>
  TL_FI Array<T>::Array( const Array<T>& toCopy )
    : ArrayBase(toCopy.size())
  {
    /*insert(m_begin, toCopy.m_begin, toCopy.m_end);*/
    m_end = uninitialized_copy(toCopy.m_begin, toCopy.m_end, m_begin);
  }

  template <typename T>
  TL_FI Array<T>::Array(tl_size aNumElemsToInsert, const T& aValueToCopy) 
    : ArrayBase(aNumElemsToInsert)
  {
    /*insert(0, aNumElemsToInsert, aValueToCopy);*/
    uninitialized_fill_n(m_begin, aNumElemsToInsert, aValueToCopy);
    m_end = m_begin + aNumElemsToInsert;
  }

  template <typename T>
  TL_FI Array<T>::Array(tl_size aCount) : ArrayBase(aCount)
  {
    uninitialized_fill_n(m_begin, aCount, value_type());
    m_end = m_begin + aCount;
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_FI Array<T>::Array(T_InputIterator aRangeBegin, T_InputIterator aRangeEnd)
  {
    insert(m_begin, aRangeBegin, aRangeEnd);
  }

  //------------------------------------------------------------------------
  // Capacity

  template <typename T>
  TL_I void Array<T>::resize( tl_size aNewSize )
  {
    tl_size currSize = size();
    if (aNewSize > currSize)
    {
      insert(m_end, aNewSize - currSize, T());
    }
    else
    {
      erase(m_begin + aNewSize, m_end);
    }
  }

  template <typename T>
  TL_I void Array<T>::resize( tl_size aNewSize, const T& aValue )
  {
    tl_size currSize = size();
    if (aNewSize > currSize)
    {
      insert(m_end, aNewSize - currSize, aValue);
    }
    else
    {
      erase(m_begin + aNewSize, m_end);
    }
  }

  template <typename T>
  TL_I void Array<T>::reserve(tl_size aNewCapacity)
  {
    if (aNewCapacity > capacity())
    {
      T* ptr = DoReAllocate(aNewCapacity);

      TLOC_ASSERT_ARRAY(ptr, "Could not re-allocate!");

      if (ptr)
      {
        const tl_size prevSize = size();
        m_begin     = ptr;
        m_end       = ptr + prevSize;
        m_capacity  = ptr + aNewCapacity;
      }

    }
  }

  template <typename T>
  TL_I void Array<T>::shrink( tl_size aNewCapacity )
  {
    if (aNewCapacity < capacity())
    {
      tl_size newSize = size();

      // If the new capacity is smaller than the number of elements we are
      // currently, storing, we need to destroy those elements
      if (aNewCapacity < newSize)
      {
        newSize = aNewCapacity;
        erase(m_begin + aNewCapacity, m_end);
      }

      T* ptr = DoReAllocate(aNewCapacity);

      TLOC_ASSERT_ARRAY(ptr, "Could not re-allocate!");

      if (ptr)
      {
        m_begin = ptr;
        m_end = ptr + newSize;
        m_capacity = ptr + aNewCapacity;
      }
    }
  }

  template <typename T>
  TL_I void Array<T>::shrink_to_fit()
  {
    shrink(size());
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <typename T>
  TL_I void Array<T>::assign( tl_size aRepetitionNum, const T& aElemToCopy )
  {
    if (capacity() < aRepetitionNum)
    {
      resize(aRepetitionNum);
    }

    fill_n(m_begin, aRepetitionNum, aElemToCopy);
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_I void Array<T>::assign( T_InputIterator aRangeBegin,
                              T_InputIterator aRangeEnd )
  {
    typedef Loki::TypeTraits<T_InputIterator> inputUnknown;
    typedef Loki::Int2Type<inputUnknown::isArith> inputArith;

    // The correct DoInsert() will be called depending on whether inputIntegral
    // is Int2Type<true> or Int2Type<false>
    DoAssign(aRangeBegin, aRangeEnd, inputArith());
  }

  template <typename T>
  void Array<T>::push_back( const T& aValueToCopy )
  {
    if (m_end < m_capacity)
    {
      DoAddToEnd(aValueToCopy);
    }
    else
    {
      DoReAllocate();
      DoAddToEnd(aValueToCopy);
    }
  }

  template <typename T>
  TL_I typename Array<T>::iterator
    Array<T>::insert( iterator aPosition, const T& aValueToCopy )
  {
    TLOC_ASSERT_ARRAY_POSITION(aPosition);

    const tl_size posIndex = aPosition - m_begin;

    if (full() || aPosition != m_end)
    {
      DoInsertValue(aPosition, aValueToCopy);
    }
    else
    {
      ::new(m_end++) T(aValueToCopy);
    }

    return m_begin + posIndex;;
  }

  template <typename T>
  TL_I void Array<T>::insert( T* aPosition,
                              tl_size aNumElemsToInsert,
                              const T& aValueToCopy )
  {
    DoInsertValues(aPosition, aNumElemsToInsert, aValueToCopy);
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_I void Array<T>::insert( iterator aPosition, T_InputIterator aRangeBegin,
                              T_InputIterator aRangeEnd )
  {
    typedef Loki::TypeTraits<T_InputIterator> inputUnknown;
    typedef Loki::Int2Type<inputUnknown::isIntegral> inputIntegral;

    // The correct DoInsert() will be called depending on whether inputIntegral
    // is Int2Type<true> or Int2Type<false>
    DoInsert(aPosition, aRangeBegin, aRangeEnd, inputIntegral());
  }

  template <typename T>
  TL_I void Array<T>::swap( Array<T>& aVec )
  {
    tlSwap(m_begin, aVec.m_begin);
    tlSwap(m_end, aVec.m_end);
    tlSwap(m_capacity, aVec.m_capacity);
  }

  //------------------------------------------------------------------------
  // Internal functions

  template <typename T>
  TL_I void Array<T>::DoInsertValue( T* aPosition, const T& aValue )
  {
    TLOC_ASSERT_ARRAY_POSITION(aPosition);

    if (m_end != m_capacity)
    {
      // Value may be from within the range of the array, in which case, the
      // pointer will be moved by one to where it will be once everything is
      // moved over. 
      const T* valuePtr = &aValue;
      if (valuePtr >= aPosition && valuePtr < m_end)
      {
        ++valuePtr;
      }

      // We directly assume that the value is not going to be inserted at m_end
      // at this point. 
      ::new(m_end) T(*(m_end - 1)); // We need initialize and move the end value
      copy_backward(aPosition, m_end - 1, m_end);
      *aPosition = *valuePtr;
      ++m_end;
    }
    else
    {
      // Value may be from within the range of the array, in which case, it may
      // be destroyed, so make a copy
      const T valueCopy = aValue;
      tl_size posIndex = aPosition - m_begin;
      DoReAllocate();
      insert(m_begin + posIndex, valueCopy);
    }
  }

  template <typename T>
  TL_I void Array<T>::DoInsertValues( T* aPosition, tl_size aNumElemsToInsert, 
                                      const T& aValue )
  {
    TLOC_ASSERT_ARRAY_POSITION(aPosition);
    TLOC_ASSERT_ARRAY(aNumElemsToInsert > 0, "Inserting 0 elements!");

    // value may be from within the array, copy it
    const T valueCopy = aValue;

    // Check if we have enough capacity to store the elements
    if (aNumElemsToInsert <= tl_size(m_capacity - m_end) )
    {
      //OPT: Not the most optimized solution, may want to re-work it

      const tl_size elemsToMove = (tl_size)(m_end - aPosition);
      const tl_size spaceRequired = elemsToMove + aNumElemsToInsert;

      // Allocate all un-allocated space
      while (m_end != aPosition + spaceRequired)
      {
        ::new(m_end++) T();
      }

      copy_backward(aPosition, aPosition + elemsToMove, m_end);

      while (aPosition != m_end - elemsToMove)
      {
        *(aPosition++) = aValue;
      }
    }
    else
    {
      tl_size posIndex = aPosition - m_begin;

      // Reallocate
      // TODO: Replace with resize() once implemented
      tl_size prevSize = size();
      tl_size newCap  = capacity() + aNumElemsToInsert;
      T* ptr;

      // DoReallocate may malloc or realloc depending on the initial size
      ptr = DoReAllocate(newCap);

      TLOC_ASSERT_ARRAY(ptr != NULL, "Could not allocate/re-allocate!");

      if (ptr)
      {
        m_begin = ptr;
        m_end = m_begin + prevSize;
        m_capacity = m_begin + newCap;
      }

      insert(m_begin + posIndex, aNumElemsToInsert, valueCopy);
    }
  }

  template <typename T>
  template <typename T_Number>
  TL_I void Array<T>::DoAssign( T_Number aRepetitionNum, T_Number aElemToCopy, 
                                is_arith_t)
  {
    assign(static_cast<tl_size>(aRepetitionNum), static_cast<T>(aElemToCopy));
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_I void Array<T>::DoAssign( T_InputIterator aRangeBegin, 
                                T_InputIterator aRangeEnd, is_not_arith_t)
  {
    TLOC_ASSERT_ARRAY_RANGE(aRangeBegin, aRangeEnd);

    tl_size projectedSize = aRangeEnd - aRangeBegin;
    if (capacity() < projectedSize)
    {
      resize(projectedSize);
    }

    copy(aRangeBegin, aRangeEnd, m_begin);
  }

  template <typename T>
  template <typename T_Number>
  TL_I void Array<T>::DoInsert( iterator aPosition,
                                       T_Number aN,
                                       T_Number aValue,
                                       is_integral_t)
  {
    insert(aPosition, static_cast<tl_size>(aN), static_cast<T>(aValue));
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_I void Array<T>::DoInsert( iterator position,
                                T_InputIterator first,
                                T_InputIterator last,
                                is_not_integral_t)
  {
    DoInsertByIterator(position, first, last);
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_I void Array<T>::DoInsertByIterator( iterator position,
                                          T_InputIterator first,
                                          T_InputIterator last )
  {
    TLOC_ASSERT_ARRAY_RANGE(first, last);
    tl_size newSize = size() + (last - first);

    if (capacity() >= newSize)
    {
      while (first != last)
      {
        position = insert(position, *first++);
        ++position;
      }
    }
    else
    {
      const tl_size oldPosition = (tl_size)( position - m_begin);
      reserve(newSize); // 'position' is now invalid
      DoInsertByIterator(m_begin + oldPosition, first, last);
    }
  }

};};

#endif