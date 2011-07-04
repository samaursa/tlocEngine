namespace tloc
{

  //////////////////////////////////////////////////////////////////////////
  // ArrayBase<T>

  template <typename T>
  tloc::ArrayBase<T>::ArrayBase() : m_begin(NULL), m_end(NULL), m_capacity(NULL)
  {
  }

  template <typename T>
  tloc::ArrayBase<T>::ArrayBase( tl_sizet aSize )
  {
    m_begin = Allocate(aSize);
    TLOC_ASSERT_CONTAINERS(m_begin != NULL,
                            "Could not allocate Array! (ArrayBase::ArrayBase)");
    m_end = m_begin;
    m_capacity = m_begin + aSize;
  }

  //------------------------------------------------------------------------
  // Element access

  template <typename T>
  TL_I T& tloc::ArrayBase<T>::at( tl_sizet aIndex )
  {
    TLOC_ASSERT_ARRAY(aIndex < size(), "Index out of bounds! (ArrayBase::at)");
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I const T& tloc::ArrayBase<T>::at( tl_sizet aIndex ) const
  {
    TLOC_ASSERT_ARRAY(aIndex < size(), "Index out of bounds! (ArrayBase::at)");
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I T& tloc::ArrayBase<T>::operator[]( tl_sizet aIndex )
  {
    tl_sizet mySize = size();
    TLOC_ASSERT(false, "Bla bla");
    TLOC_ASSERT(aIndex < size(), "Index out of bounds! (ArrayBase::[])");
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I const T& tloc::ArrayBase<T>::operator[]( tl_sizet aIndex ) const
  {
    TLOC_ASSERT_ARRAY(aIndex < size(), "Index out of bounds! (ArrayBase::[])");
    return *(m_begin + aIndex);
  }

  template <typename T>
  TL_I T& tloc::ArrayBase<T>::front()
  {
    TLOC_ASSERT_ARRAY(size() > 0, "Array is empty! (ArrayBase::front)");
    return m_begin;
  }

  template <typename T>
  TL_I const T& tloc::ArrayBase<T>::front() const
  {
    TLOC_ASSERT_ARRAY(size() > 0, "Array is empty! (ArrayBase::front)");
    return m_begin;
  }

  template <typename T>
  TL_I T& tloc::ArrayBase<T>::back()
  {
    TLOC_ASSERT_ARRAY(size() > 0, "Array is empty! (ArrayBase::front)");
    return m_end;
  }

  template <typename T>
  TL_I const T& tloc::ArrayBase<T>::back() const
  {
    TLOC_ASSERT_ARRAY(m_size() > 0, "Array is empty! (ArrayBase::front)");
    return m_end;
  }

  template <typename T>
  TL_I T* tloc::ArrayBase<T>::data()
  {
    return m_begin;
  }

  //------------------------------------------------------------------------
  // Iterator access

  template <typename T>
  TL_I T* tloc::ArrayBase<T>::begin()
  {
    return m_begin;
  }

  template <typename T>
  TL_I const T* tloc::ArrayBase<T>::begin() const
  {
    return m_begin;
  }

  template <typename T>
  TL_I T* tloc::ArrayBase<T>::end()
  {
    return m_end;
  }

  template <typename T>
  TL_I const T* tloc::ArrayBase<T>::end() const
  {
    return m_end;
  }

  //------------------------------------------------------------------------
  // Capacity

  template <typename T>
  TL_I tl_sizet tloc::ArrayBase<T>::size() const
  {
    return (m_end - m_begin);
  }

  template <typename T>
  TL_I tl_sizet tloc::ArrayBase<T>::capacity() const
  {
    return (m_capacity - m_begin);
  }

  template <typename T>
  TL_I bool tloc::ArrayBase<T>::empty() const
  {
    return size() > 0 ? true : false;
  }

  template <typename T>
  TL_I bool tloc::ArrayBase<T>::full() const
  {
    return (m_end == m_capacity);
  }

  //------------------------------------------------------------------------
  // Internal functions

  template <typename T>
  TL_I T* tloc::ArrayBase<T>::Allocate( tl_sizet aSize )
  {
    return size() ? (T*)TL_MALLOC(aSize * sizeof(t));
  }

  template <typename T>
  TL_I T* tloc::ArrayBase<T>::ReAllocate( tl_sizet aSize )
  {
    return (T*)TL_REALLOC(m_begin, aSize);
  }

  template <typename T>
  TL_I void tloc::ArrayBase<T>::Free( T* aPtr, tl_sizet aSize )
  {
    TL_FREE(aPtr);
  }

  template <typename T>
  TL_I void tloc::ArrayBase<T>::DestroyValues( size_t aStartIndex, size_t aEndIndex )
  {
    TLOC_ASSERT_ARRAY(aStartIndex < size(),
      "Start index out of bounds! (ArrayBase::DestroyValues)");
    TLOC_ASSERT_ARRAY(aEndIndex < size(),
      "End index out of bounds! (ArrayBase::DestroyValues)");
    TLOC_ASSERT_ARRAY(aStartIndex <= aEndIndex,
      "Start index > End index! (ArrayBase::DestroyValues)");

    for (tl_sizet i = aStartIndex; i < aEndIndex; ++i)
    {
      (m_begin + i)->~T();
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // Array<T>

  //------------------------------------------------------------------------
  // Constructors

  template <typename T>
  tloc::Array<T>::Array() : ArrayBase()
  {
  }

  template <typename T>
  tloc::Array<T>::Array( tl_sizet aSize ) : ArrayBase(aSize)
  {
    Allocate(aSize);
  }

  //------------------------------------------------------------------------
  // Modifiers

  template <typename T>
  TL_I void tloc::Array<T>::assign( T* rangeBegin, T* rangeEnd )
  {
  }

  template <typename T>
  TL_I void tloc::Array<T>::assign( tl_sizet aRepetitionNum, const T& aElemToCopy )
  {
  }

  template <typename T>
  void tloc::Array<T>::push_back( const T& aValueToCopy )
  {
    if (m_end < m_capacity)
    {
      new(m_end) T(aValueToCopy); // placement new
      ++m_end;
    }
    else
    {
      tl_sizet currSize = size();
      T* ptr = currSize ? ReAllocate( size() * 2 ) : ReAllocate(1);
      TLOC_ASSERT_ARRAY(ptr != NULL, "Could not re-allocate! (Array::ReAllocate)");
      m_end = ptr + size();
      m_capacity = ptr + capacity();
      m_begin = ptr;
      *m_begin = aValueToCopy;
    }
  }

  template <typename T>
  void tloc::Array<T>::pop_back()
  {
    --m_end;
    m_end->~T();
  }

  template <typename T>
  void tloc::Array<T>::pop_back( T& aOut )
  {
    aOut = *(m_end);
    --m_end;
  }
};