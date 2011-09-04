namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Macros (mostly for assertions)

#define TLOC_ASSERT_STRING_EMPTY_STRING() \
  TLOC_ASSERT_STRING(GetEmptyString(char32()), \
  "EmptyString is corrupted! (no longer empty)");

  //////////////////////////////////////////////////////////////////////////
  // StringBase<T>

  //------------------------------------------------------------------------
  // Empty Strings

  template <typename T>
  const typename StringBase<T>::EmptyString StringBase<T>::sm_emptyString = { 0 };

  template <typename T>
  TL_STATIC_I const char8* StringBase<T>::GetEmptyString( char8 )
  {
    return sm_emptyString.m_Empty8;
  }

  template <typename T>
  TL_STATIC_I const uchar8* StringBase<T>::GetEmptyString( uchar8 )
  {
    return sm_emptyString.m_EmptyU8;
  }

  template <typename T>
  TL_STATIC_I const char32* StringBase<T>::GetEmptyString( char32 )
  {
    return sm_emptyString.m_Empty32;
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
  TL_I void tloc::StringBase<T>::DoAllocateSelf()
  {
    TLOC_ASSERT_STRING_EMPTY_STRING();
    m_begin =
  }

  template <typename T>
  TL_I void tloc::StringBase<T>::DoAllocateSelt( tl_size aSize )
  {

  }

};