#ifndef TLOC_STRING_H
#define TLOC_STRING_H

#include "tlocBase.h"
#include "tlocAlgorithms.h"
#include "tlocTypeTraits.h"

#include <string.h>

//------------------------------------------------------------------------
// Fine grain control to enable/disable assertions in Strings

#ifndef TLOC_DISABLE_ASSERT_STRING
# define TLOC_ASSERT_STRING(_Expression, _Msg) TLOC_ASSERT_CONTAINERS(_Expression, _Msg)

#   ifndef TLOC_DISABLE_ASSERT_STRING_WARN
#     define TLOC_ASSERT_STRING_WARN(_Expression, _Msg) TLOC_ASSERT_WARN(_Expression, _Msg)
#   else
#     define TLOC_ASSERT_STRING_WARN(_Expression, _Msg)
#   endif

#else
# define TLOC_ASSERT_STRING(_Expression, _Msg)
# define TLOC_ASSERT_STRING_WARN(_Expression, _Msg)
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
  class StringBase
  {
  public:

    //------------------------------------------------------------------------
    // typedefs

    typedef StringBase<T>   StringBaseT;
    typedef T               value_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef T*              iterator;
    typedef const T*        const_iterator;

    //------------------------------------------------------------------------
    // Constants

    static const tl_size npos     = (tl_size) - 1;

    //------------------------------------------------------------------------
    // Modifiers

    //------------------------------------------------------------------------
    // Ctor / Dtor

    TL_I StringBase();
    TL_I StringBase(const StringBase<T>& aOther);
    TL_I StringBase(const StringBase<T>& aOther, tl_size aPosition,
                    tl_size aNumChars = npos);
    TL_I StringBase(const T* aPtr, tl_size aNumChars);
    TL_I explicit StringBase(const T* aPtr);
    TL_I StringBase(tl_size aNumChars, T aChar);
    TL_I StringBase(const T* aPtrBegin, const T* aPtrEnd);
    TL_I StringBase(StringNoInitialize, tl_size aN);
    TL_I StringBase(StringSprintf, const tl_size aFormat, ...);

    TL_I ~StringBase();

    //------------------------------------------------------------------------
    // Iterators

    TL_I iterator        begin();
    TL_I const_iterator  begin() const;

    TL_I iterator        end();
    TL_I const_iterator  end() const;

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
    TL_I void       resize(const tl_size& newSize);
    TL_I void       resize(const tl_size& newSize, const T charToFill);
    TL_I tl_size    capacity() const;
    TL_I void       set_capacity(const tl_size& newCapacity = npos);
    TL_I void       reserve(const tl_size& newSize);
    TL_I void       clear();
    TL_I bool       empty();

    //------------------------------------------------------------------------
    // Modifiers

    TL_I StringBaseT& operator+= (const StringBaseT& aStr);
    TL_I StringBaseT& operator+= (const T* aCharStr);
    TL_I StringBaseT& operator+= (const T& aChar);

    TL_I StringBaseT& operator = (const StringBaseT& aStr);
    TL_I StringBaseT& operator = (const T* aCharStr);
    TL_I StringBaseT& operator = (T aChar);

    TL_I void         swap(T& aX);

    TL_I StringBaseT& append(const StringBaseT& aStr);
    TL_I StringBaseT& append(const StringBaseT& aStr, const tl_size& aPos,
                             const tl_size& aNumChars);
    TL_I StringBaseT& append(const T* aCharArray, const tl_size& aNumChars);
    TL_I StringBaseT& append(const T* aCharStr);
    TL_I StringBaseT& append(const tl_size& aNumChars, const T& aChar);
    template <typename T_InputIterator>
    TL_I StringBaseT& append(T_InputIterator aBegin, T_InputIterator aEnd);

    TL_I void         push_back(const T& aChar);

    TL_I StringBaseT& assign(const StringBaseT& aStr);
    TL_I StringBaseT& assign(const StringBaseT& aStr, const tl_size& aPos,
                             const tl_size& aNumChars);
    TL_I StringBaseT& assign(const T* aCharStr, const tl_size& aNumChars);
    TL_I StringBaseT& assign(const T* aCharStr);
    TL_I StringBaseT& assign(const tl_size& aNumChars, const T& aChar);
    template <typename T_InputIterator>
    TL_I StringBaseT& assign(const T_InputIterator aBegin,
                             const T_InputIterator aEnd);

    TL_I StringBaseT& insert(tl_size aIndex, const StringBaseT& aStr);
    TL_I StringBaseT& insert(tl_size aIndexDestination, const StringBaseT& aStr,
                             tl_size aIndexSource, tl_size aNumChars);
    TL_I StringBaseT& insert(tl_size aIndex, const T* aCharArray, tl_size aNumChars);
    TL_I StringBaseT& insert(tl_size aIndex, const T* aCharStr);
    TL_I StringBaseT& insert(tl_size aIndex, tl_size aNumChars, const T& aChar);
    TL_I iterator     insert(const T* aPos, const T& aChar);
    TL_I void         insert(const T* aPos, tl_size aNumChars, const T& aChar);
    template <typename T_InputIterator>
    TL_I void         insert(const T* aPos, T_InputIterator aBegin,
                             T_InputIterator aEnd);

    TL_I StringBaseT& erase(const tl_size& aPos = 0,
                            const tl_size& aNumChars = npos);
    TL_I iterator     erase(iterator aPos);
    TL_I iterator     erase(iterator aFirst, iterator aLast);

    TL_I StringBaseT& replace(tl_size aPos, tl_size aNumCharsToReplace,
                              const StringBaseT& aStr);
    TL_I StringBaseT& replace(iterator aDestBegin, iterator aDestEnd,
                              const StringBaseT& aStr);

    TL_I StringBaseT& replace(tl_size aDestPos, tl_size aNumCharsToReplace,
                              const StringBaseT& aStr, tl_size aSourcePos,
                              tl_size aNumCharsToCopy);

    TL_I StringBaseT& replace(tl_size aPos, tl_size aNumCharsToReplace,
                              const T* aCharArray, tl_size aNumCharsToCopy);
    TL_I StringBaseT& replace(iterator aDestBegin, iterator aDestEnd,
                              const T* aCharArray, tl_size aNumCharsToCopy);

    TL_I StringBaseT& replace(tl_size aPos, tl_size aNumCharsToReplace,
                              const T* aCharStr);
    TL_I StringBaseT& replace(iterator aDestBegin, iterator aDestEnd,
                              const T* aCharStr);

    TL_I StringBaseT& replace(tl_size aPos, tl_size aNumCharsToReplace,
                              tl_size aNumOfCharsToCopy, const T& aChar);
    TL_I StringBaseT& replace(iterator aDestBegin, iterator aDestEnd,
                              tl_size aNumOfCharsToCopy, const T& aChar);

    /*template <typename T_InputIterator>
    TL_I StringBaseT& replace(iterator*/



    //------------------------------------------------------------------------
    // Operations
    TL_I const T*     c_str();

  protected:
    T*              m_begin;
    T*              m_end;
    T*              m_capacity;

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
    // Internal functions

    TL_I T*               DoAllocate(const tl_size& aSize);
    TL_I T*               DoReAllocate(const tl_size& aSize);
    TL_I void             DoReAllocateAndAdjust(const tl_size& aSize);
    TL_I void             DoReAllocateAndAdjust();
    TL_I void             DoFree(T* aPtr);

    TL_I void             DoAllocateSelf();
    TL_I void             DoAllocateSelf(const tl_size& aSize);
    TL_I void             DoDeallocateSelf();

    void                  RangeInitialize(const T* aPtrBegin, const T* aPtrEnd);
    void                  RangeInitialize(const T* aPtrBegin);

    //------------------------------------------------------------------------
    // Constants

    static const tl_size m_MaxSize  = (tl_size) - 2;
    static const tl_size sm_defaultCapacity;
  };

  //////////////////////////////////////////////////////////////////////////
  // Free functions

  template <typename T>
  TL_I tl_size    StrLen(const T* aCharStr);
  template <>
  TL_I tl_size    StrLen(const char8* aCharStr);

  template <typename T>
  TL_I s32        StrCmp(const T* aPtr1, const T* aPtr2);
  template <typename T>
  TL_I s32        StrCmp(const T* aPtr1, const T* aPtr2, const tl_size& aNumChars);
  template <>
  TL_I s32        StrCmp(const char8* aPtr1, const char8* aPtr2, const tl_size& aNumChars);

  TL_I void       CharToLower();
  TL_I void       CharToUpper();


  TL_I void Find();
};

#include "tlocString.inl"

#endif