#ifndef TLOC_STRING_H
#define TLOC_STRING_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/types/tlocTypeTraits.h>

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

namespace tloc { namespace core {
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

    typedef T               value_type;
    typedef T*              pointer;
    typedef const T*        const_pointer;
    typedef T&              reference;
    typedef const T&        const_reference;
    typedef T*              iterator;
    typedef const T*        const_iterator;
    typedef tl_size         size_type;

    typedef StringBase<value_type>  this_type;

    //------------------------------------------------------------------------
    // Constants

    static const tl_size npos;

    //------------------------------------------------------------------------
    // Modifiers

    //------------------------------------------------------------------------
    // Ctor / Dtor

    TL_I StringBase();
    TL_I StringBase(const this_type& aOther);
    TL_I StringBase(const this_type& aOther, size_type aPosition,
                    size_type aNumChars = npos);
    TL_I StringBase(const_pointer aPtr, size_type aNumChars);
    TL_I StringBase(const_pointer aPtr);
    TL_I StringBase(size_type aNumChars, value_type aChar);

    template <typename T_InputIterator>
    TL_I StringBase(const T_InputIterator aPtrBegin, const T_InputIterator aPtrEnd);

    TL_I StringBase(StringNoInitialize, size_type aN);
    TL_I StringBase(StringSprintf, const size_type aFormat, ...);

    TL_I ~StringBase();

    //------------------------------------------------------------------------
    // Iterators

    TL_I iterator        begin();
    TL_I const_iterator  begin() const;

    TL_I iterator        end();
    TL_I const_iterator  end() const;

    //------------------------------------------------------------------------
    // Element access

    TL_I const T&   operator [] (size_type aPos) const;
    TL_I T&         operator [] (size_type aPos);

    TL_I const T&   at(size_type aPos) const;
    TL_I T&         at(size_type aPos);

    //------------------------------------------------------------------------
    // Capacity

    TL_I tl_size    size() const;
    TL_I tl_size    length() const;
    TL_I tl_size    max_size() const;
    TL_I void       resize(const size_type& newSize);
    TL_I void       resize(const size_type& newSize, const value_type charToFill);
    TL_I tl_size    capacity() const;
    TL_I void       set_capacity(const size_type& newCapacity = npos);
    TL_I void       reserve(const size_type& newSize);
    TL_I void       clear();
    TL_I bool       empty();

    //------------------------------------------------------------------------
    // Modifiers

    TL_I this_type& operator+= (const this_type& aStr);
    TL_I this_type& operator+= (const_pointer aCharStr);
    TL_I this_type& operator+= (const_reference aChar);

    TL_I this_type& operator = (const this_type& aStr);
    TL_I this_type& operator = (const_pointer aCharStr);
    TL_I this_type& operator = (value_type aChar);

    TL_I void         swap(this_type& aX);

    //````````````````````````````````````````````````````````````````````````
    // Append

    TL_I this_type& append(const this_type& aStr);
    TL_I this_type& append(const this_type& aStr, const size_type& aPos,
                             const size_type& aNumChars);
    TL_I this_type& append(const_pointer aCharArray, const size_type& aNumChars);
    TL_I this_type& append(const_pointer aCharStr);
    TL_I this_type& append(const size_type& aNumChars, const_reference aChar);
    template <typename T_InputIterator>
    TL_I this_type& append(T_InputIterator aBegin, T_InputIterator aEnd);

    TL_I void         push_back(const T& aChar);

    //````````````````````````````````````````````````````````````````````````
    // Assign

    TL_I this_type& assign(const this_type& aStr);
    TL_I this_type& assign(const this_type& aStr, const tl_size& aPos,
                             const tl_size& aNumChars);
    TL_I this_type& assign(const_pointer aCharStr, const tl_size& aNumChars);
    TL_I this_type& assign(const_pointer aCharStr);
    TL_I this_type& assign(const tl_size& aNumChars, const T& aChar);
    template <typename T_InputIterator>
    TL_I this_type& assign(const T_InputIterator aBegin,
                             const T_InputIterator aEnd);

    //````````````````````````````````````````````````````````````````````````
    // Insert

    TL_I this_type& insert(tl_size aIndex, const this_type& aStr);
    TL_I this_type& insert(tl_size aIndexDestination, const this_type& aStr,
                           tl_size aIndexSource, tl_size aNumChars);
    TL_I this_type& insert(tl_size aIndex, const_pointer aCharArray, tl_size aNumChars);
    TL_I this_type& insert(tl_size aIndex, const_pointer aCharStr);
    TL_I this_type& insert(tl_size aIndex, tl_size aNumChars, T aChar);
    TL_I iterator   insert(const_iterator aPos, const T& aChar);
    TL_I void       insert(const_iterator aPos, tl_size aNumChars, T aChar);

    template <typename T_InputIterator>
    TL_I void         insert(const_iterator aPos, T_InputIterator aBegin,
                             T_InputIterator aEnd);

    //````````````````````````````````````````````````````````````````````````
    // Replace

    TL_I this_type& erase(const tl_size& aPos = 0,
                          const tl_size& aNumChars = npos);
    TL_I iterator     erase(iterator aPos);
    TL_I iterator     erase(iterator aFirst, iterator aLast);

    //````````````````````````````````````````````````````````````````````````
    // Replace

    TL_I this_type& replace(tl_size aPos, tl_size aNumCharsToReplace,
                            const this_type& aStr);
    TL_I this_type& replace(iterator aDestBegin, iterator aDestEnd,
                            const this_type& aStr);

    TL_I this_type& replace(tl_size aDestPos, tl_size aNumCharsToReplace,
                            const this_type& aStr, tl_size aSourcePos,
                            tl_size aNumCharsToCopy);

    TL_I this_type& replace(tl_size aPos, tl_size aNumCharsToReplace,
                            const_pointer aCharArray, tl_size aNumCharsToCopy);
    TL_I this_type& replace(iterator aDestBegin, iterator aDestEnd,
                            const_pointer aCharArray, tl_size aNumCharsToCopy);

    TL_I this_type& replace(tl_size aPos, tl_size aNumCharsToReplace,
                            const_pointer aCharStr);
    TL_I this_type& replace(iterator aDestBegin, iterator aDestEnd,
                            const_pointer aCharStr);

    TL_I this_type& replace(tl_size aPos, tl_size aNumCharsToReplace,
                            tl_size aNumOfCharsToCopy, const T aChar);
    TL_I this_type& replace(iterator aDestBegin, iterator aDestEnd,
                            tl_size aNumOfCharsToCopy, const T aChar);

    template <typename T_InputIterator>
    TL_I this_type& replace(iterator aDestBegin, iterator aDestEnd,
                            T_InputIterator aBegin, T_InputIterator aEnd);

    //````````````````````````````````````````````````````````````````````````
    // Lower and Upper case

    TL_I this_type   to_upper();
    TL_I void        to_upper(this_type& aStrOut);

    TL_I this_type   to_lower();
    TL_I void        to_lower(this_type& aStrOut);

    TL_I void        make_upper();
    TL_I void        make_lower();

    //------------------------------------------------------------------------
    // String Operations

    TL_I const_pointer     c_str();
    TL_I const_pointer     c_str() const;
    TL_I const_pointer     data();
    TL_I const_pointer     data() const;
    TL_I tl_size      copy(pointer aDestArray, const tl_size& aNumCharsToCopy,
                           const tl_size& aBegin = 0);

    //````````````````````````````````````````````````````````````````````````
    // Find functions

    TL_I tl_size      find(const this_type& aStrToCompare,
                           const tl_size& aBeginIndex = 0) const;
    TL_I tl_size      find(const_pointer aCharStr, const tl_size& aBeginIndex,
                           const tl_size& aNumCharsToCompare) const;
    TL_I tl_size      find(const_pointer aCharStr,
                           const tl_size& aBeginIndex = 0) const;
    TL_I tl_size      find(T aChar, const tl_size& aBeginIndex = 0) const;

    TL_I tl_size      rfind(const this_type& aStrToCompare,
                            const tl_size& aBeginIndex = 0) const;
    TL_I tl_size      rfind(const_pointer aCharStr, const tl_size& aBeginIndex,
                            const tl_size& aNumCharsToCompare) const;
    TL_I tl_size      rfind(const_pointer aCharStr,
                            const tl_size& aBeginIndex = 0) const;
    TL_I tl_size      rfind(T aChar, const tl_size& aBeginIndex = 0) const;

    TL_I tl_size      find_first_of(const this_type& aStrToCompare,
                                    const tl_size& aBeginIndex = 0) const;
    TL_I tl_size      find_first_of(const_pointer aCharStr, const tl_size& aBeginIndex,
                                    const tl_size& aNumCharsToCompare) const;
    TL_I tl_size      find_first_of(const_pointer aCharStr,
                                    const tl_size& aBeginIndex = 0) const;
    TL_I tl_size      find_first_of(T aChar, const tl_size& aBeginIndex = 0) const;

    TL_I tl_size      find_last_of(const this_type& aStrToCompare,
                                   const tl_size& aBeginIndex = 0) const;
    TL_I tl_size      find_last_of(const_pointer aCharStr, const tl_size& aBeginIndex,
                                   const tl_size& aNumCharsToCompare) const;
    TL_I tl_size      find_last_of(const_pointer aCharStr,
                                   const tl_size& aBeginIndex = 0) const;
    TL_I tl_size      find_last_of(T aChar, const tl_size& aBeginIndex = 0) const;

    TL_I tl_size      find_first_not_of(const this_type& aStrToCompare,
                                        tl_size aBeginIndex = 0) const;
    TL_I tl_size      find_first_not_of(const_pointer aCharStr,
                                        const tl_size& aBeginIndex,
                                        tl_size aNumCharsToCompare) const;
    TL_I tl_size      find_first_not_of(const_pointer aCharStr,
                                        const tl_size& aBeginIndex = 0) const;
    TL_I tl_size      find_first_not_of(T aChar, const tl_size& aBeginIndex = 0) const;

    TL_I tl_size      find_last_not_of(const this_type& aStrToCompare,
                                       tl_size aBeginIndex = 0) const;
    TL_I tl_size      find_last_not_of(const_pointer aCharStr, const tl_size& aBeginIndex,
                                       tl_size aNumCharsToCompare) const;
    TL_I tl_size      find_last_not_of(const_pointer aCharStr,
                                       const tl_size& aBeginIndex = 0) const;
    TL_I tl_size      find_last_not_of(T aChar,
                                       const tl_size& aBeginIndex = 0) const;

    //````````````````````````````````````````````````````````````````````````
    // Substring

    TL_I this_type substr(const tl_size& aBeginIndex,
                          const tl_size& aNumCharsToCopy = npos);
    TL_I void              substr(const tl_size& aBeginIndex,
                                  const tl_size& aNumCharsToCopy,
                                  this_type&   aSubStrOut);

    //````````````````````````````````````````````````````````````````````````
    // Compare

    TL_I s32 compare ( const this_type& aStr ) const;
    TL_I s32 compare ( const_pointer aCharStr ) const;
    TL_I s32 compare ( const tl_size& aThisPos, const tl_size& aThisLength,
                       const this_type& aOtherStr ) const;
    TL_I s32 compare ( const tl_size& aThisPos, const tl_size& aThisLength,
                       const_pointer aOtherStr) const;
    TL_I s32 compare ( const tl_size& aThisPos, const tl_size& aThisLength,
                       const this_type& aOtherStr, const tl_size& aOtherPos,
                       const tl_size& aOtherLength ) const;
    TL_I s32 compare ( const tl_size& aThisPos, const tl_size& aThisLength,
                       const_pointer aOtherCharStr, const tl_size& aOtherLength) const;

  protected:
    pointer  m_begin;
    pointer  m_end;
    pointer  m_capacity;

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

    TL_I pointer          DoAllocate(const size_type& aSize);
    TL_I pointer          DoReAllocate(const size_type& aSize);
    TL_I void             DoReAllocateAndAdjust(const size_type& aSize);
    TL_I void             DoReAllocateAndAdjust();
    TL_I void             DoFree(pointer aPtr);

    TL_I void             DoAllocateSelf();
    TL_I void             DoAllocateSelf(const size_type& aSize);
    TL_I void             DoDeallocateSelf();

    TL_I void             RangeInitialize(const_pointer aPtrBegin,
                                          const_pointer aPtrEnd);
    TL_I void             RangeInitialize(const_pointer aPtrBegin);

    TL_I tl_int           DoCompare(const_pointer aBegin1, const_pointer aEnd1,
                                    const_pointer aBegin2, const_pointer aEnd2) const;

    //------------------------------------------------------------------------
    // Constants

    static const tl_size m_MaxSize;
    static const tl_size sm_defaultCapacity;
  };

  template <typename T>
  const tl_size StringBase<T>::npos = (tl_size) - 1;

  //////////////////////////////////////////////////////////////////////////
  // Global functions

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

  template <typename T>
  TL_I T          CharToLower(const T& aChar);

  template <typename T>
  TL_I T          CharToUpper(const T& aChar);
  TL_I tl_int     CharAsciiToWide(char32* a_out, const char8* a_in, tl_int a_inSize);
  TL_I tl_int     CharWideToAscii(char8* a_out, const char32* a_in, tl_int a_inSize);

  //````````````````````````````````````````````````````````````````````````
  // Global operators (not providing <, > as they can be confusing/error-prone
  // use StrCmp() for those operations

  template <typename T>
  TL_I bool       operator==(const StringBase<T>& a, const StringBase<T>& b);
  template <typename T>
  TL_I bool       operator==(const T* a, const StringBase<T>& b);
  template <typename T>
  TL_I bool       operator==(const StringBase<T>& a, const T* b);

  template <typename T>
  TL_I bool       operator!=(const StringBase<T>& a, const StringBase<T>& b);
  template <typename T>
  TL_I bool       operator!=(const T* a, const StringBase<T>& b);
  template <typename T>
  TL_I bool       operator!=(const StringBase<T>& a, const T* b);

  typedef StringBase<char8>   String;
  typedef StringBase<char32>  StringW;

};};

#endif
