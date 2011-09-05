namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Macros (mostly for assertions)

#define TLOC_ASSERT_STRING_EMPTY_STRING() \
  TLOC_ASSERT_STRING( GetEmptyString(char32()) == 0, \
  "EmptyString is corrupted! (no longer empty)");

#define TLOC_ASSERT_STRING_INDEX(_index) \
  TLOC_ASSERT_STRING( _index < length(), "Invalid index!")

# define TLOC_ASSERT_STRING_RANGE(_RangeBegin, _RangeEnd) \
  TLOC_ASSERT(_RangeBegin <= _RangeEnd, \
  # _RangeBegin _CRT_WIDE(" must be smaller than ") _CRT_WIDE(# _RangeEnd) L"!")

  //////////////////////////////////////////////////////////////////////////
  // StringBase<T>

  //------------------------------------------------------------------------
  // Constants

  template <typename T>
  const typename StringBase<T>::EmptyString StringBase<T>::sm_emptyString = { 0 };

  //------------------------------------------------------------------------
  // Ctors

  template <typename T>
  StringBase<T>::StringBase()
    : m_begin(NULL)
    , m_end(NULL)
    , m_capacity(NULL)
  {
    DoAllocateSelf();
  }

  template <typename T>
  StringBase<T>::StringBase(const StringBase<T>& aOther, tl_size aPosition,
                            tl_size aN /* = npos */)
    : m_begin(NULL)
    , m_end(NULL)
    , m_capacity(NULL)
  {
    TLOC_ASSERT_STRING(aPosition <= aOther.length(), "aPosition is out out range!");

    if (aN == npos)
    {
      RangeInitialize(aOther.m_begin + aPosition, aOther.m_end);
    }
    else
    {
      RangeInitialize(aOther.m_begin + aPosition, aOther.m_begin + aPosition + aN);
    }
  }

  template <typename T>
  StringBase<T>::~StringBase()
  {
    DoDeallocateSelf();
  }

  //------------------------------------------------------------------------
  // Empty Strings

  template <typename T>
  TL_I const char8* StringBase<T>::GetEmptyString( char8 )
  {
    return sm_emptyString.m_Empty8;
  }

  template <typename T>
  TL_I const uchar8* StringBase<T>::GetEmptyString( uchar8 )
  {
    return sm_emptyString.m_EmptyU8;
  }

  template <typename T>
  TL_I const char32* StringBase<T>::GetEmptyString( char32 )
  {
    return sm_emptyString.m_Empty32;
  }

  //------------------------------------------------------------------------
  // Element access

  template <typename T>
  TL_I const T& StringBase<T>::operator[]( tl_size aPos ) const
  {
    TLOC_ASSERT_STRING_INDEX(aPos);
    return *(m_begin + aPos);
  }

  template <typename T>
  TL_I T& StringBase<T>::operator[]( tl_size aPos )
  {
    TLOC_ASSERT_STRING_INDEX(aPos);
    return *(m_begin + aPos);
  }

  template <typename T>
  TL_I const T& StringBase<T>::at( tl_size aPos ) const
  {
    TLOC_ASSERT_STRING_INDEX(aPos);
    return *(m_begin + aPos);
  }

  template <typename T>
  TL_I T& StringBase<T>::at( tl_size aPos )
  {
    TLOC_ASSERT_STRING_INDEX(aPos);
    return *(m_begin + aPos);
  }

  //------------------------------------------------------------------------
  // Capacity

  template <typename T>
  TL_I tl_size StringBase<T>::size() const
  {
    return (tl_size)(m_end - m_begin);
  }

  template <typename T>
  TL_I tl_size StringBase<T>::length() const
  {
    return (tl_size)(m_end - m_begin);
  }

  template <typename T>
  TL_I tl_size StringBase<T>::max_size() const
  {
    return m_MaxSize;
  }

  template <typename T>
  TL_I void StringBase<T>::resize()
  {

  }

  template <typename T>
  TL_I tl_size StringBase<T>::capacity() const
  {
    // Do not report the memory allocated for the null terminator
    return (tl_size)(m_capacity - m_begin - 1);
  }

  template <typename T>
  TL_I void StringBase<T>::reserve()
  {

  }

  template <typename T>
  TL_I void StringBase<T>::clear()
  {

  }

  template <typename T>
  TL_I bool StringBase<T>::empty()
  {
    return (m_begin == m_end);
  }

  //------------------------------------------------------------------------
  // Internal functions

  template <typename T>
  TL_I T* StringBase<T>::DoAllocate( tl_size aSize )
  {
    TLOC_ASSERT_STRING(aSize > 1,
      "Allocation size must be greater than 1 for the null terminator");

    return (T*)TL_MALLOC(aSize * sizeof(T));
  }

  template <typename T>
  TL_I T* StringBase<T>::DoReAllocate( tl_size aSize )
  {
    TLOC_ASSERT_STRING(aSize > 1,
      "Allocation size must be greater than 1 for the null terminator");

    return (T*)TL_REALLOC(m_begin, sizeof(T) * aSize);
  }

  template <typename T>
  TL_I void StringBase<T>::DoFree( T* aPtr )
  {
    TL_FREE(aPtr);
  }

  template <typename T>
  TL_I void StringBase<T>::DoAllocateSelf()
  {
    TLOC_ASSERT_STRING_EMPTY_STRING();

    m_begin     = const_cast<T*>( GetEmptyString(T()) );
    m_end       = m_begin;
    m_capacity  = m_begin + 1;
  }

  template <typename T>
  TL_I void StringBase<T>::DoAllocateSelf( tl_size aSize )
  {
    TLOC_ASSERT_STRING(aSize <= (tl_size)std::numeric_limits<tl_size>::max,
      "Allocating too large a value!");

    if (aSize > 1)
    {
      m_begin     = DoAllocate(aSize);
      m_end       = m_begin;
      m_capacity  = m_begin + aSize;
    }
    else
    {
      DoAllocateSelf();
    }
  }

  template <typename T>
  TL_I void StringBase<T>::DoDeallocateSelf()
  {
    if (m_begin == GetEmptyString(T()))
    {
      DoFree(m_begin);
    }
  }

  template <typename T>
  void StringBase<T>::RangeInitialize( const T* aPtrBegin )
  {
    TLOC_ASSERT_STRING(aPtrBegin, "aPtrBegin cannot be NULL!");

    RangeInitialize(aPtrBegin, StrLen(aPtrBegin));
  }

  template <typename T>
  void StringBase<T>::RangeInitialize( const T* aPtrBegin, const T* aPtrEnd )
  {
    TLOC_ASSERT_STRING_RANGE(aPtrBegin, aPtrEnd);

    DoAllocateSelf( (tl_size)(aPtrEnd - aPtrBegin + 1));

    m_end = tlCopy(aPtrBegin, aPtrEnd, m_begin);
    *m_end = 0; // Null terminator
  }

  //////////////////////////////////////////////////////////////////////////
  // Free functions


  template <typename T>
  TL_I tl_size StrLen( const T* aCharStr )
  {
    const T* lTemp = aCharStr;

    while (*lTemp) { ++lTemp; }

    return (tl_size)(lTemp - aCharStr);
  }

  template <>
  TL_I tl_size StrLen( const char8* aCharStr)
  {
    return (tl_size)strlen(aCharStr);
  }


};