#ifndef TLOC_STRING_H
#define TLOC_STRING_H

#include "tlocArray.h"

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in Strings

#ifndef TLOC_DISABLE_ASSERT_STRING
# define TLOC_ASSERT_STRING(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)
#else
# define TLOC_ASSERT_STRING(_Expression, _Msg)
#endif

namespace tloc
{
  //------------------------------------------------------------------------
  // Ctor Helpers

  struct StringNoInitialize {};
  struct StringSprintf {};

  //------------------------------------------------------------------------
  // StringBase

  template <typename T>
  class StringBase : private Array<T>
  {
  public:

    //------------------------------------------------------------------------
    // typedefs

    typedef StringBase<T>                     this_type;
    typedef T                                 value_type;
    typedef T*                                pointer;
    typedef const T*                          const_pointer;
    typedef T&                                reference;
    typedef const T&                          const_reference;
    typedef T*                                iterator;
    typedef const T*                          const_iterator;

    //------------------------------------------------------------------------
    // Constants

    static const tl_size npos     = (tl_size) - 1;

    //------------------------------------------------------------------------
    // Modifiers

    //------------------------------------------------------------------------
    // Functions

    StringBase();
    StringBase(const T& aOther, tl_size aPosition, tl_size aN = npos);
    StringBase(const T* aPtr, tl_size aN);
    explicit StringBase(const T* aPtr);
    StringBase(tl_size aN, T aC);
    StringBase(const T& aOther);
    StringBase(const T* aPtrBegin, const T* aPtrEnd);
    StringBase(StringNoInitialize, tl_size aN);
    StringBase(StringSprintf, const tl_size aFormat, ...);

    ~StringBase();

    //------------------------------------------------------------------------
    // Assignment

    TL_I T&         operator = (const T& aX);
    TL_I T&         operator = (const T* aPtr);
    TL_I T&         operator = (T aC);

    TL_I void       swap(T& aX);

    //------------------------------------------------------------------------
    // Element access

    TL_I const T&   operator [] (tl_size aPos) const;
    TL_I T&         operator [] (tl_size aPos);

    TL_I const T&   at(tl_size aPos) const;
    TL_I T&         at(tl_size aPos);

    //------------------------------------------------------------------------
    // Capacity

    TL_I tl_size    size() const;
    TL_I tl_size    length() const;
    TL_I tl_size    max_size() const;
    TL_I void       resize();
    TL_I tl_size    capacity() const;
    TL_I void       reserve();
    TL_I void       clear();
    TL_I bool       empty();

  protected:
    TL_I T*         m_begin;
    TL_I T*         m_end;
    TL_I T*         m_capacity;

    //------------------------------------------------------------------------
    // Empty strings

    typedef union EmptyString
    {
      char8   m_Empty8[1];
      uchar8  m_EmptyU8[1];
      char32  m_Empty32[1];
    }EmptyString;

    static const EmptyString sm_emptyString;

    TL_STATIC_I const char8*      GetEmptyString(char8);
    TL_STATIC_I const uchar8*     GetEmptyString(uchar8);
    TL_STATIC_I const char32*     GetEmptyString(char32);

    //------------------------------------------------------------------------
    // Helper functions

    TL_I T*               DoAllocate(tl_size aSize);
    TL_I T*               DoReAllocate(tl_size aSize);
    TL_I void             DoFree(T* aPtr);

    TL_I void             DoAllocateSelf();
    TL_I void             DoAllocateSelt(tl_size aSize);
    TL_I void             DoDeallocateSelf();

    //------------------------------------------------------------------------
    // Constants

    static const tl_size m_MaxSize  = (tl_size) - 2;
  };

  //////////////////////////////////////////////////////////////////////////
  // Free functions

  TL_I void CharToLower();
  TL_I void CharToUpper();
  TL_I void StrLen();
  TL_I void Find();
};

#include "tlocString.inl"

#endif