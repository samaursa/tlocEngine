#ifndef TLOC_STRING_INL
#define TLOC_STRING_INL

#ifndef TLOC_STRING_H
#error "Must include header before including the inline file"
#endif

#include "tlocString.h"
#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/utilities/tlocTemplateUtils.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <string.h>
#include <ctype.h>

#include <cstdlib>

namespace tloc { namespace core { namespace string {

  // ///////////////////////////////////////////////////////////////////////
  // StringBase<T>

  template <typename T>
  template <typename T_InputIterator>
  StringBase<typename T>::
    StringBase(const T_InputIterator aPtrBegin,
               const T_InputIterator aPtrEnd)
  {
    RangeInitialize(aPtrBegin, aPtrEnd);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  template <typename T_InputIterator>
  void StringBase<T>::
    insert( const_iterator aPos, T_InputIterator aBegin, T_InputIterator aEnd )
  {
    TLOC_ASSERT_STRING(aBegin <= aEnd, "Input range is invalid!");
    TLOC_ASSERT_STRING(aPos >= m_begin && aPos <= m_end,
      "Iterator position is out of range!");

    const size_type startIndex = aPos - m_begin;
    const size_type currCap = m_capacity - m_begin;
    const size_type rangeSize = aEnd - aBegin;
    const size_type newCap = size() + rangeSize + 1; // +1 for the NULL char

    // Check if we have enough capacity
    if (currCap < newCap)
    {
      DoReAllocateAndAdjust(newCap);
    }

    iterator pos = m_begin + startIndex;

    // +1 for the NULL character
    memmove(pos + rangeSize, pos, (size_type )((m_end - (pos) + 1) * sizeof(T)) );
    memmove(pos, aBegin, (size_type )(rangeSize * sizeof(T)) );

    m_end = m_end + rangeSize;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  template <typename T_InputIterator>
  typename StringBase<T>::this_type& 
    StringBase<T>::
    append( T_InputIterator aBegin, T_InputIterator aEnd )
  {
    if (aBegin != aEnd)
    {
      const size_type oldSize = size();
      const size_type oldCapacity = m_capacity - m_begin;
      const size_type rangeSize = (size_type )(aEnd - aBegin);

      if ( (oldSize + rangeSize) > (oldCapacity - 1) ) // -1 because of /0
      {
        DoReAllocateAndAdjust(oldSize + rangeSize + 1);
      }

      m_end = tloc::core::copy(aBegin, aEnd, m_end);
      *m_end = 0;
    }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  template <typename T_InputIterator>
  typename StringBase<T>::this_type& 
    StringBase<T>::
    assign(const T_InputIterator aBegin, const T_InputIterator aEnd)
  {
    const size_type ourSize = size();
    const size_type rangeSize = aEnd - aBegin;
    if (rangeSize <= ourSize)
    {
      memmove(m_begin, aBegin, (size_type )(rangeSize * sizeof(T)) );
      erase(m_begin + rangeSize, m_end);
    }
    else
    {
      memmove(m_begin, aBegin, (size_type )(ourSize) * sizeof(T) );
      append(aBegin + (size_type )(ourSize), aEnd);
    }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  template <typename T_InputIterator>
  typename StringBase<T>::this_type&
    StringBase<T>::
    replace(iterator aDestBegin, iterator aDestEnd,
            T_InputIterator aBegin, T_InputIterator aEnd)
  {
    TLOC_ASSERT_STRING(aDestBegin >= m_begin && aDestBegin <= m_end,
      "Destination begin iterator is out of range!");
    TLOC_ASSERT_STRING(aDestEnd >= m_begin && aDestEnd <= m_end,
      "Destination end iterator is out of range!");
    TLOC_ASSERT_STRING(aDestBegin <= aDestEnd, "Destination range is invalid!");
    TLOC_ASSERT_STRING(aBegin <= aEnd, "Invalid input range!");

    // TODO: Make this function work without a temporary
    // In EASTL the function is relatively complicated, taking care of all the
    // possible outcomes. I went the easy way, even though in this case a
    // temp is necessary. If this function is used in a sensitive area and slowing
    // things down, it may be worth removing the temporary.
    StringBase<T> temp(aBegin, aEnd);

    erase(aDestBegin, aDestEnd);
    insert(aDestBegin - m_begin, temp);

    return *this;
  }

  //////////////////////////////////////////////////////////////////////////
  // Global functions

  template <typename T>
  const T*
    StrChr(const T* a_string, T a_charToLocate)
  {
    const T* currChar = a_string;

    while(*currChar != 0)
    {
      if (*currChar == a_charToLocate)
      { return currChar; }

      ++currChar;
    }

    if (*currChar == a_charToLocate)
    { return currChar; }

    return nullptr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  T*
    StrChr(T* a_string, T a_charToLocate)
  {
    return const_cast<T*>
      (StrChr(const_cast<const T*>(a_string), a_charToLocate) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  const T*
    StrRChr(const T* a_string, T a_charToLocate)
  {
    const T* currChar = a_string;
    const T* charToRet = nullptr;

    while(*currChar != 0)
    {
      if (*currChar == a_charToLocate)
      { charToRet = currChar; }

      ++currChar;
    }

    if (*currChar == a_charToLocate)
    { charToRet = currChar; }

    return charToRet;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  T*
    StrRChr(T* a_string, T a_charToLocate)
  {
    return const_cast<T*>
      (StrChr(const_cast<const T*>(a_string), a_charToLocate) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  tl_size
    StrLen( const T* aCharStr )
  {
    const T* lTemp = aCharStr;

    while (*lTemp) { ++lTemp; }

    return (tl_size)(lTemp - aCharStr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  tl_int
    StrCmp( const T* aPtr1, const T* aPtr2 )
  {
    while (*aPtr1 != 0 && *aPtr2 != 0)
    {
      if (*aPtr1 != *aPtr2)
      {
        return *aPtr1 > *aPtr2 ? 1 : -1;
      }

      ++aPtr1; ++aPtr2;
    }

    if (*aPtr1 != 0 || *aPtr2 != 0)
    {
      return *aPtr1 > *aPtr2 ? 1 : -1;
    }

    return 0;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  tl_int
    StrCmp( const T* aPtr1, const T* aPtr2, const tl_size& aNumChars )
  {
    tl_int ret = 0;

    for (tl_size i = aNumChars; i > 0; --i)
    {
      if (*aPtr1 != *aPtr2)
      {
        ret = *aPtr1 > *aPtr2 ? 1 : -1;
      }
    }

    return ret;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  T
    CharToLower( const T& aChar )
  {
    TLOC_ASSERT_STRING(aChar <= NumericLimits_T<char8>::max(),
      "Character is out of range for this function!");
    return (T)tolower((char8)aChar);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  T
    CharToUpper( const T& aChar)
  {
    TLOC_ASSERT_STRING(aChar <= NumericLimits_T<char8>::max(),
      "Character is out of range for this function!");
    return (T)toupper((char8)aChar);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, typename T_StringContainer>
  void
    Tokenize(const T* a_string, T a_delim, T_StringContainer& a_out)
  {
    typedef const T*        iterator;

    iterator itr      = a_string;
    iterator itrCurr  = itr;
    iterator itrEnd   = a_string + StrLen(a_string);

    while (itrCurr != itrEnd)
    {
      if (*itrCurr == a_delim)
      {
        if (itr != itrCurr)
        {
          a_out.push_back(StringBase<T>(itr, itrCurr));
        }

        while(*itrCurr == a_delim)
        {
          ++itrCurr;
        }

        itr = itrCurr;
      }
      else
      {
        ++itrCurr;
      }
    }

    if (itr != itrCurr)
    {
      a_out.push_back(StringBase<T>(itr, itrCurr));
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, typename T_StringContainer>
  void
    Tokenize(const T* a_string, const T* a_delims, T_StringContainer& a_out)
  {
    typedef const T*        iterator;

    iterator itr      = a_string;
    iterator itrCurr  = itr;
    iterator itrEnd   = a_string + StrLen(a_string);

    StringBase<T> delims(a_delims);

    while (itrCurr != itrEnd)
    {
      if (delims.find(*itrCurr) != delims.npos)
      {
        if (itr != itrCurr)
        {
          a_out.push_back(StringBase<T>(itr, itrCurr));
        }

        while(delims.find(*itrCurr) != delims.npos)
        {
          ++itrCurr;
        }

        itr = itrCurr;
      }
      else
      {
        ++itrCurr;
      }
    }

    if (itr != itrCurr)
    {
      a_out.push_back(StringBase<T>(itr, itrCurr));
    }
  }

  //````````````````````````````````````````````````````````````````````````
  // Global operators

  template <typename T>
  bool
    operator==( const StringBase<T>& a, const StringBase<T>& b )
  {
    const tl_size sizeA = a.size();
    return ( (sizeA == b.size()) && (memcmp(a.c_str(), b.c_str(),
             sizeA * sizeof(typename StringBase<T>::value_type)) == 0) );

  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  bool
    operator==( const T* a, const StringBase<T>& b )
  {
    const tl_size charStrSize = StrLen(a);
    return ( (charStrSize == b.size()) && (memcmp(a, b.c_str(),
              charStrSize * sizeof(T)) == 0) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  bool
    operator==( const StringBase<T>& a, const T* b )
  {
    const tl_size charStrSize = StrLen(b);
    return ( (charStrSize == a.size()) && (memcmp(b, a.c_str(),
              charStrSize * sizeof(T)) == 0) );
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  bool
    operator!=( const StringBase<T>& a, const StringBase<T>& b )
  {
    return !(a == b);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  bool
    operator!=( const T* a, const StringBase<T>& b )
  {
    return !(a == b);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  bool
    operator!=( const StringBase<T>& a, const T* b )
  {
    return !(a == b);
  }

};};};

#endif
