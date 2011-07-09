namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Macros

#define TLOC_ASSERT_ARRAY_RANGE_BEGIN(rangeBegin) \
  TLOC_ASSERT_ARRAY(rangeBegin >= m_begin && rangeBegin < m_end,\
# rangeBegin _CRT_WIDE(" is out of range! (") _CRT_WIDE(__FUNCTION__) L")" )

#define TLOC_ASSERT_ARRAY_RANGE_END(rangeEnd) \
  TLOC_ASSERT_ARRAY(rangeEnd <= m_end,\
# rangeEnd _CRT_WIDE(" is out of range! (") _CRT_WIDE(__FUNCTION__) L")")

#define TLOC_ASSERT_ARRAY_RANGE_BEGIN_END(aRangeBegin, aRangeEnd) \
  TLOC_ASSERT_ARRAY_RANGE_BEGIN(aRangeBegin);\
  TLOC_ASSERT_ARRAY_RANGE_END(aRangeEnd);\
  TLOC_ASSERT_ARRAY(aRangeBegin < aRangeEnd,\
# aRangeBegin _CRT_WIDE(" must be smaller than ") _CRT_WIDE(# aRangeEnd)\
  L"! (" _CRT_WIDE(__FUNCTION__) L")")

  //////////////////////////////////////////////////////////////////////////
  // Constants

  template <typename T>
  const tl_sizet ArrayBase<T>::sm_defaultCapacity = 2;

  //////////////////////////////////////////////////////////////////////////
  // ArrayBase<T>

  template <typename T>
  ArrayBase<T>::ArrayBase()
    : m_begin(NULL)
    , m_end(NULL)
    , m_capacity(NULL)
  {
  }

  template <typename T>
  ArrayBase<T>::ArrayBase( tl_sizet aSize )
  {
    m_begin = DoAllocate(aSize);
    TLOC_ASSERT_CONTAINERS(m_begin != NULL,
                            "Could not allocate Array! (ArrayBase::ArrayBase)");
    m_end = m_begin;
    m_capacity = m_begin + aSize;
  }

  //------------------------------------------------------------------------
  // Element access

  template <typename T>
  TL_I T& ArrayBase<T>::at( tl_sizet aIndex )
  {
    TLOC_ASSERT_ARRAY(aIndex < size(), "Index out of bounds! (ArrayBase::at)");
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I const T& ArrayBase<T>::at( tl_sizet aIndex ) const
  {
    TLOC_ASSERT_ARRAY(aIndex < size(), "Index out of bounds! (ArrayBase::at)");
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I T& ArrayBase<T>::operator[]( tl_sizet aIndex )
  {
    TLOC_ASSERT(aIndex < size(), "Index out of bounds! (ArrayBase::[])");
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I const T& ArrayBase<T>::operator[]( tl_sizet aIndex ) const
  {
    TLOC_ASSERT_ARRAY(aIndex < size(), "Index out of bounds! (ArrayBase::[])");
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I T& ArrayBase<T>::front()
  {
    TLOC_ASSERT_ARRAY(size() > 0, "Array is empty! (ArrayBase::front)");
    return m_begin;
  }

  template <typename T>
  TL_I const T& ArrayBase<T>::front() const
  {
    TLOC_ASSERT_ARRAY(size() > 0, "Array is empty! (ArrayBase::front)");
    return m_begin;
  }

  template <typename T>
  TL_I T& ArrayBase<T>::back()
  {
    TLOC_ASSERT_ARRAY(size() > 0, "Array is empty! (ArrayBase::front)");
    return m_end;
  }

  template <typename T>
  TL_I const T& ArrayBase<T>::back() const
  {
    TLOC_ASSERT_ARRAY(m_size() > 0, "Array is empty! (ArrayBase::front)");
    return m_end;
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
  TL_I tl_sizet ArrayBase<T>::size() const
  {
    return (m_end - m_begin);
  }

  template <typename T>
  TL_I tl_sizet ArrayBase<T>::capacity() const
  {
    return (m_capacity - m_begin);
  }

  template <typename T>
  TL_I bool ArrayBase<T>::empty() const
  {
    return size() > 0 ? true : false;
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
    --m_end;
    m_end->~T();
  }

  template <typename T>
  TL_I void ArrayBase<T>::pop_back( T& aOut )
  {
    aOut = *(m_end);
    --m_end;
  }

  template <typename T>
  TL_I void tloc::ArrayBase<T>::erase( iterator aPosition )
  {
    TLOC_ASSERT_ARRAY_RANGE_BEGIN(aPosition);

    aPosition->~T();
    Copy(aPosition + 1, m_end, aPosition);
    --m_end;
  }

  template <typename T>
  TL_I void tloc::ArrayBase<T>::erase( iterator aRangeBegin, iterator aRangeEnd )
  {
    TLOC_ASSERT_ARRAY_RANGE_BEGIN_END(aRangeBegin, aRangeEnd);

    iterator copyRemainingTo = aRangeBegin;

    while (aRangeBegin != aRangeEnd)
    {
      aRangeBegin->~T();
      ++aRangeBegin;
    }

    Copy(aRangeEnd, m_end, copyRemainingTo);

    m_end = m_begin;
  }

  template <typename T>
  TL_I void tloc::ArrayBase<T>::clear()
  {
    erase(m_begin, m_end);
  }

  //------------------------------------------------------------------------
  // Internal functions

  template <typename T>
  TL_I T* ArrayBase<T>::DoAllocate( tl_sizet aSize )
  {
    return aSize ? (T*)TL_MALLOC(aSize * sizeof(T)) : NULL;
  }

  template <typename T>
  TL_I T* ArrayBase<T>::DoReAllocate( tl_sizet aSize )
  {
    return (T*)TL_REALLOC(m_begin, sizeof(T) * aSize);
  }

  template <typename T>
  TL_I void ArrayBase<T>::DoFree( T* aPtr, tl_sizet aSize )
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
    TLOC_ASSERT_ARRAY(full() == false, "Array is full! (ArrayBase::AddToEnd)");

    new(m_end) T(aValueToCopy); // placement new
    ++m_end;
  }

  template <typename T>
  TL_I void ArrayBase<T>::DoReAllocate()
  {
    tl_sizet prevSize = size();
    tl_sizet prevCap  = capacity();
    tl_sizet newCap  = prevCap ? (2 * prevCap) : sm_defaultCapacity;
    T* ptr;

    // DoReallocate may malloc or realloc depending on the initial size
    ptr = DoReAllocate(newCap);

    TLOC_ASSERT_ARRAY(ptr != NULL, "Could not allocate/re-allocate! (ArrayBase::push_back)");

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
  Array<T>::Array() : ArrayBase()
  {
  }

  template <typename T>
  Array<T>::Array( tl_sizet aSize ) : ArrayBase(aSize)
  {
    Allocate(aSize);
  }

  //------------------------------------------------------------------------
  // Capacity

  template <typename T>
  TL_I void Array<T>::resize( tl_sizet aNewSize )
  {

  }

  //------------------------------------------------------------------------
  // Modifiers

  template <typename T>
  TL_I void Array<T>::assign( tl_sizet aRepetitionNum, const T& aElemToCopy )
  {
    if (capacity() < aRepetitionNum)
    {
      resize(aRepetitionNum);
    }

    Fill(m_begin, m_begin + aRepetitionNum, aElemToCopy);
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_I void Array<T>::assign( T_InputIterator aRangeBegin,
                              T_InputIterator aRangeEnd )
  {
    TLOC_ASSERT_ARRAY_RANGE_BEGIN_END(aRangeBegin, aRangeEnd);

    tl_sizet projectedSize = aRangeEnd - aRangeBegin;
    if (capacity() < aRangeEnd - aRangeBegin)
    {

    }
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
}