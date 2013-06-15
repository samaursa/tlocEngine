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
  //////////////////////////////////////////////////////////////////////////
  // Macros

#define TLOC_ASSERT_STRING_EMPTY_STRING() \
  TLOC_ASSERT_STRING( *(GetEmptyString(char32())) == 0, \
  "EmptyString is corrupted! (no longer empty)");

#define TLOC_ASSERT_STRING_INDEX(_index) \
  TLOC_ASSERT_STRING( _index < length(), "Invalid index!")

# define TLOC_ASSERT_STRING_RANGE(_RangeBegin, _RangeEnd) \
  TLOC_ASSERT(_RangeBegin <= _RangeEnd, \
  #_RangeBegin " must be smaller than " #_RangeEnd)

#define STRING_BASE_TYPES typename T
#define STRING_BASE_PARAMS T
#define STRING_BASE_TYPE typename StringBase<STRING_BASE_PARAMS>
  //////////////////////////////////////////////////////////////////////////
  // StringBase<T>

  //------------------------------------------------------------------------
  // Constants

  template <typename T>
  const tl_size StringBase<STRING_BASE_PARAMS>::m_MaxSize = (tl_size) - 2;

  template <STRING_BASE_TYPES>
  const tl_size StringBase<STRING_BASE_PARAMS>::sm_defaultCapacity = 2;

  //------------------------------------------------------------------------
  // Ctors

  template <STRING_BASE_TYPES>
  StringBase<STRING_BASE_PARAMS>::
    StringBase()
    : m_begin(nullptr)
    , m_end(nullptr)
    , m_capacity(nullptr)
  {
    DoAllocateSelf();
  }

  template <STRING_BASE_TYPES>
  StringBase<STRING_BASE_PARAMS>::StringBase(const this_type& aOther)
    : m_begin(nullptr)
    , m_end(nullptr)
    , m_capacity(nullptr)
  {
    RangeInitialize(aOther.begin(), aOther.end());
  }

  template <STRING_BASE_TYPES>
  StringBase<STRING_BASE_PARAMS>::
    StringBase(const this_type& aOther, size_type aPosition, size_type aN)
    : m_begin(nullptr)
    , m_end(nullptr)
    , m_capacity(nullptr)
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

  template <STRING_BASE_TYPES>
  StringBase<STRING_BASE_PARAMS>::
    StringBase(const T* aPtr, size_type aNumChars)
  {
    RangeInitialize(aPtr, aPtr + aNumChars);
  }

  template <STRING_BASE_TYPES>
  StringBase<STRING_BASE_PARAMS>::
    StringBase(const T* aPtr)
  {
    RangeInitialize(aPtr);
  }

  template <STRING_BASE_TYPES>
  StringBase<STRING_BASE_PARAMS>::
    StringBase(size_type aNumChars, T aChar)
  {
    DoAllocateSelf();
    append(aNumChars, aChar);
  }

  template <STRING_BASE_TYPES>
  template <typename T_InputIterator>
  StringBase<STRING_BASE_PARAMS>::
    StringBase(const T_InputIterator aPtrBegin,
               const T_InputIterator aPtrEnd)
  {
    RangeInitialize(aPtrBegin, aPtrEnd);
  }

  template <STRING_BASE_TYPES>
  StringBase<STRING_BASE_PARAMS>::
    StringBase(StringNoInitialize, size_type aN)
  {
    DoAllocateSelf(aN + 1);
    *m_end = 0;
  }

  template <STRING_BASE_TYPES>
  StringBase<STRING_BASE_PARAMS>::
    StringBase(StringSprintf, const size_type aFormat, ...)
  {
    TLOC_UNUSED(aFormat);
    //TLOC_STATIC_ASSERT_WIP();
    // TODO: Implement this string ctor
  }

  template <STRING_BASE_TYPES>
  StringBase<STRING_BASE_PARAMS>::
    ~StringBase()
  {
    DoDeallocateSelf();
  }

  //------------------------------------------------------------------------
  // Iterators

  template <STRING_BASE_TYPES>
  typename StringBase<T>::iterator
    StringBase<STRING_BASE_PARAMS>::
    begin()
  {
    return m_begin;
  }

  template <STRING_BASE_TYPES>
  typename StringBase<T>::const_iterator
    StringBase<STRING_BASE_PARAMS>::
    begin() const
  {
    return m_begin;
  }

  template <STRING_BASE_TYPES>
  typename StringBase<T>::iterator
    StringBase<STRING_BASE_PARAMS>::
    end()
  {
    return m_end;
  }

  template <STRING_BASE_TYPES>
  typename StringBase<T>::const_iterator
    StringBase<STRING_BASE_PARAMS>::
    end() const
  {
    return m_end;
  }

  //------------------------------------------------------------------------
  // Empty Strings - not visible outside of this file

  namespace
  {
    const char8* GetEmptyString( char8 )
    {
      static const char8 address[] = {0};
      return address;
    }

    const uchar8* GetEmptyString( uchar8 )
    {
      static const uchar8 address[] = {0};
      return address;
    }

    const char32* GetEmptyString( char32 )
    {
      static const char32 address[] = {0};
      return address;
    }
  }

  //------------------------------------------------------------------------
  // Element access

  template <STRING_BASE_TYPES>
  const T& StringBase<STRING_BASE_PARAMS>::
    operator[]( size_type aPos ) const
  {
    TLOC_ASSERT_STRING_INDEX(aPos);
    return *(m_begin + aPos);
  }

  template <STRING_BASE_TYPES>
  T& StringBase<STRING_BASE_PARAMS>::
    operator[]( size_type aPos )
  {
    TLOC_ASSERT_STRING_INDEX(aPos);
    return *(m_begin + aPos);
  }

  template <STRING_BASE_TYPES>
  const T& StringBase<STRING_BASE_PARAMS>::
    at( size_type aPos ) const
  {
    TLOC_ASSERT_STRING_INDEX(aPos);
    return *(m_begin + aPos);
  }

  template <STRING_BASE_TYPES>
  T& StringBase<STRING_BASE_PARAMS>::
    at( size_type aPos )
  {
    TLOC_ASSERT_STRING_INDEX(aPos);
    return *(m_begin + aPos);
  }

  //------------------------------------------------------------------------
  // Capacity

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<STRING_BASE_PARAMS>::
    size() const
  {
    return (size_type )(m_end - m_begin);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<STRING_BASE_PARAMS>::
    length() const
  {
    return (size_type )(m_end - m_begin);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<STRING_BASE_PARAMS>::
    max_size() const
  {
    return m_MaxSize;
  }

  template <STRING_BASE_TYPES>
  void StringBase<STRING_BASE_PARAMS>::
    resize(const size_type & newSize)
  {
    TLOC_UNUSED(newSize);
    //TLOC_STATIC_ASSERT_WIP();
  }

  template <STRING_BASE_TYPES>
  void StringBase<STRING_BASE_PARAMS>::
    resize(const size_type & newSize, const T charToFill)
  {
    TLOC_UNUSED_2(newSize, charToFill);
    //TLOC_STATIC_ASSERT_WIP();
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<STRING_BASE_PARAMS>::
    capacity() const
  {
    // Do not report the memory allocated for the null terminator
    return (size_type )(m_capacity - m_begin - 1);
  }

  /*!
   * \brief Sets the capacity of the string to the specified capacity.
   *
   * The capacity may increase or shrink. This may result in some of the string
   * being stripped off. Setting the new capacity to 'npos' will ensure that
   * the capacity == size.
   *
   * \param const size_type & newCapacity
   * \returnsize_type
   * \sa resize(), reserve()
   */
  template <STRING_BASE_TYPES>
  void StringBase<STRING_BASE_PARAMS>::
    set_capacity(const size_type & newCapacity)
  {
    if (newCapacity != capacity())
    {
      const size_type oldSize = length();
      const size_type cap = (newCapacity == npos) ? oldSize : newCapacity;

      if (cap > 0)
      {
        const size_type oldSize = size();

        m_begin = DoReAllocate(cap + 1); // +1 for the trailing 0

        if (cap < oldSize)
        {
          m_end = m_begin + cap; // cap is an index and capacity starts from 0
                                 // so no +1 here
        }
        else
        {
          m_end = m_begin + oldSize;
        }

        *m_end = 0;
        m_capacity = m_begin + cap + 1;
      }
      else
      {
        DoDeallocateSelf();
        DoAllocateSelf();
      }
    }
  }

  /*!
   * \brief Reserves a specific amount of memory for the string.
   *
   * \param const size_type & newSize
   * \return void
   * \sa set_capacity(), resize()
   * \note The function can only increase capacity. Call resize() to decrease capacity.
   * \warning
   */
  template <STRING_BASE_TYPES>
  void StringBase<STRING_BASE_PARAMS>::
    reserve(const size_type & newSize)
  {
    TLOC_ASSERT_STRING(newSize < m_MaxSize, "Reserve request is too large!");
    TLOC_ASSERT_STRING_WARN(newSize > capacity(), "Reserve request is smaller "
      "than the current capacity. Call resize() for shrinking.");

    if (newSize > capacity()) // Exclude /0
    {
      set_capacity(newSize);
    }
  }

  template <STRING_BASE_TYPES>
  void StringBase<STRING_BASE_PARAMS>::
    clear()
  {
    if (!empty())
    {
      *m_begin = T(0);
      m_end   = m_begin;
    }
  }

  template <STRING_BASE_TYPES>
  bool StringBase<STRING_BASE_PARAMS>::
    empty()
  {
    return (m_begin == m_end);
  }

  //------------------------------------------------------------------------
  // Modifiers


  //````````````````````````````````````````````````````````````````````````
  // Operators

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<STRING_BASE_PARAMS>::
    operator+=( const StringBase<T>& aStr )
  {
    return append(aStr);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<STRING_BASE_PARAMS>::
    operator+=( const T* charStr )
  {
    return append(charStr);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<STRING_BASE_PARAMS>::
    operator+=( const T& character )
  {
    append(1, character);
    return *this;
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<STRING_BASE_PARAMS>::
    operator=(this_type aStr )
  {
    TLOC_ASSERT_STRING_WARN(&aStr != this, "Assigning the same string!");
    aStr.swap(*this);
    return *this;
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<STRING_BASE_PARAMS>::
    operator=( const T* aCharStr )
  {
    return assign(aCharStr, aCharStr + StrLen(aCharStr));
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<STRING_BASE_PARAMS>::
    operator=( T aChar )
  {
    return assign(1, aChar);
  }

  template <STRING_BASE_TYPES>
  void StringBase<STRING_BASE_PARAMS>::
    swap(this_type& aX )
  {
    TLOC_ASSERT_STRING_WARN(this != &aX, "Swap called on self (redundant).");

    core::swap(aX.m_begin, m_begin);
    core::swap(aX.m_end, m_end);
    core::swap(aX.m_capacity, m_capacity);
  }

  //````````````````````````````````````````````````````````````````````````
  // Append

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type& StringBase<T>::
    append( const this_type& aStr )
  {
    return append(aStr.m_begin, aStr.m_end);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type& StringBase<T>::
    append( const this_type& aStr, const size_type & aPos,
            const size_type & aNumChars )
  {
    TLOC_ASSERT_STRING(aPos < aStr.size(),
      "Position passed is outside of string's range!");
    TLOC_ASSERT_STRING_WARN( (aPos + aNumChars) < aStr.size(),
      "Number of characters to copy passes the string's range.");

    size_type maxCharsLeft = (aStr.m_end - aStr.m_begin) - aPos;
    return append(aStr.begin() + aPos, aStr.begin() + aPos +
      (aNumChars > maxCharsLeft ? maxCharsLeft : aNumChars) );
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type& StringBase<T>::
    append( const T* charArray, const size_type & aNumChars )
  {
    TLOC_ASSERT_STRING(StrLen(charArray) >= aNumChars,
      "Number of characters to copy exceeds the range of the character array!");

    return append(charArray, charArray + aNumChars);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type& StringBase<T>::
    append( const T* charStr )
  {
    return append(charStr, charStr + StrLen(charStr));
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type& StringBase<T>::
    append( const size_type & aNumChars, const T& aChar )
  {
    if (aNumChars > 0)
    {
      const size_type currSize = size();

      if ( (currSize  + aNumChars) > capacity() ) // Exclude /0
      {
        reserve(currSize + aNumChars);
      }

      fill(m_end, m_end + aNumChars, aChar);
      m_end += aNumChars;
      *m_end = 0;
    }

    return *this;
  }

  template <STRING_BASE_TYPES>
  template <typename T_InputIterator>
  STRING_BASE_TYPE::this_type& StringBase<T>::
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

  template <STRING_BASE_TYPES>
  void StringBase<T>::
    push_back(const T& aChar)
  {
    append(1, aChar);
  }

  //````````````````````````````````````````````````````````````````````````
  // Assign

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type& StringBase<T>::
    assign( const this_type& aStr )
  {
    return assign(aStr.begin(), aStr.end());
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type& StringBase<T>::
    assign( const this_type& aStr, const size_type & aPos,
            const size_type & aNumChars )
  {
    TLOC_ASSERT_STRING(aPos <= aStr.size(), "Position is out of range!");

    const T* endItr = aStr.begin() + aPos + aNumChars;
    return assign(aStr.begin() + aPos, (aStr.end() > endItr) ? endItr : aStr.end() );
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type& StringBase<T>::
    assign( const T* aCharStr, const size_type & aNumChars )
  {
    TLOC_ASSERT_STRING(aNumChars <= StrLen(aCharStr),
      "Length of char string is smaller than number of chars to copy");

    return assign(aCharStr, aCharStr + aNumChars);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type& StringBase<T>::
    assign( const T* aCharStr )
  {
    return assign(aCharStr, aCharStr + StrLen(aCharStr));
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type& StringBase<T>::
    assign( const size_type & aNumChars, const T& aChar )
  {
    const size_type ourSize = size();
    if (aNumChars <= ourSize)
    {
      fill(m_begin, m_begin + aNumChars, aChar);
      erase(m_begin + aNumChars, m_end);
    }
    else
    {
      fill(m_begin, m_begin + ourSize, aChar);
      append(aNumChars - ourSize, aChar);
    }

    return *this;
  }

  template <STRING_BASE_TYPES>
  template <typename T_InputIterator>
  STRING_BASE_TYPE::this_type& StringBase<T>::
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

  //````````````````````````````````````````````````````````````````````````
  // Insert

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    insert( size_type aIndex, const this_type& aStr )
  {
    insert(m_begin + aIndex, aStr.begin(), aStr.end());
    return *this;
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    insert( size_type aIndexDestination, const this_type& aStr,
            size_type aIndexSource, size_type aNumChars )
  {
    const_iterator endItr = aStr.begin() + aIndexSource + aNumChars;
    insert(m_begin + aIndexDestination, aStr.begin() + aIndexSource,
                                  (aStr.end() > endItr) ? endItr : aStr.end() );
    return *this;
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    insert( size_type aIndex, const T* aCharArray, size_type aNumChars )
  {
    insert(m_begin + aIndex, aCharArray, aCharArray + aNumChars);
    return *this;
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    insert( size_type aIndex, const T* aCharStr )
  {
    insert(m_begin + aIndex, aCharStr, aCharStr + StrLen(aCharStr));
    return *this;
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    insert( size_type aIndex, size_type aNumChars, T aChar )
  {
    insert(m_begin + aIndex, aNumChars, aChar);
    return *this;
  }

  template <STRING_BASE_TYPES>
  typename StringBase<T>::iterator
    StringBase<T>::
    insert( const_iterator aPos, const T& aChar )
  {
    // Save the position index because it may be invalid by the time insert()
    // is complete
    const size_type posIndex = aPos - m_begin;
    insert(aPos, 1, aChar);
    return m_begin + posIndex;
  }

  template <STRING_BASE_TYPES>
  void StringBase<T>::
    insert( const_iterator aPos, size_type aNumChars, T aChar )
  {
    TLOC_ASSERT_STRING(aPos >= m_begin && aPos <= m_end,
      "Iterator position is out of range!");

    const size_type currCap = m_capacity - m_begin;
    const size_type startIndex = aPos - m_begin;
    const size_type newCap = size() + aNumChars + 1;

    if (currCap < newCap)
    {
      DoReAllocateAndAdjust(newCap);
    }

    iterator pos = m_begin + startIndex;

    memmove(pos + aNumChars, pos, (size_type )( (m_end - (pos) + 1) * sizeof(T)) );
    fill(pos, pos + aNumChars, aChar);

    m_end = m_end + aNumChars;
  }

  template <STRING_BASE_TYPES>
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

  //````````````````````````````````````````````````````````````````````````
  // Erase

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    erase( const size_type & aPos, const size_type & aNumChars )
  {
    iterator rangeBegin = m_begin + aPos;
    iterator rangeEnd = aNumChars == npos ? m_end : rangeBegin + aNumChars;

    TLOC_ASSERT_STRING( rangeBegin >= m_begin && rangeBegin < m_end,
      "Position is out of range!");
    TLOC_ASSERT_STRING( rangeEnd <= m_end,
      "Position plus number of chars is past the end (out of range)!");

    erase( rangeBegin, rangeEnd );
    return *this;
  }

  template <STRING_BASE_TYPES>
  typename StringBase<T>::iterator StringBase<T>::
    erase( iterator aPos )
  {
    TLOC_ASSERT_STRING(aPos >= m_begin && aPos < m_end,
      "Position is out of range!");

    return erase(aPos, aPos + 1);
  }

  template <STRING_BASE_TYPES>
  typename StringBase<T>::iterator StringBase<T>::
    erase( iterator aFirst, iterator aLast )
  {
    TLOC_ASSERT_STRING(aFirst >= m_begin && aFirst <= m_end ,
      "Iterator aFirst is out of range!");
    TLOC_ASSERT_STRING(aLast >= m_begin || aLast <= m_end,
      "Iterator aLast is out of range!");
    TLOC_ASSERT_STRING(aFirst <= aLast, "Invalid iterator range (aFirst > aLast)!");

    if (aFirst != aLast)
    {
      const size_type rangeSize = aLast - aFirst;

      // Move the remaining string into place including the /0
      memmove( aFirst, aLast, (size_type )((m_end - aLast) + 1) * sizeof(T) );
      m_end -= rangeSize;
    }

    return aFirst;
  }

  //````````````````````````````````````````````````````````````````````````
  // Replace

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    replace( size_type aPos, size_type aNumCharsToReplace,
             const this_type& aStr )
  {
    return replace(m_begin + aPos, m_begin + aPos + aNumCharsToReplace,
      aStr.begin(), aStr.end());
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    replace( iterator aDestBegin, iterator aDestEnd, const this_type& aStr )
  {
    return replace(aDestBegin, aDestEnd, aStr.begin(), aStr.end());
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    replace( size_type aDestPos, size_type aNumCharsToReplace,
             const this_type& aStr, size_type aSourcePos,
             size_type aNumCharsToCopy )
  {
    const_iterator itrSourceEnd = aStr.begin() + aSourcePos + aNumCharsToCopy;

    return replace(m_begin + aDestPos, m_begin + aDestPos + aNumCharsToReplace,
      aStr.begin() + aSourcePos, (itrSourceEnd > aStr.end()) ? aStr.end() : itrSourceEnd);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    replace( size_type aPos, size_type aNumCharsToReplace,
             const T*  aCharArray, size_type aNumCharsToCopy )
  {
    return replace(m_begin + aPos, m_begin + aPos + aNumCharsToReplace,
                   aCharArray, aCharArray + aNumCharsToCopy);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    replace( iterator  aDestBegin, iterator  aDestEnd,
             const T*  aCharArray, size_type aNumCharsToCopy )
  {
    return replace(aDestBegin, aDestEnd, aCharArray, aCharArray + aNumCharsToCopy);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    replace( size_type aPos, size_type aNumCharsToReplace,
             const T*  aCharStr )
  {
    return replace(m_begin + aPos, m_begin + aPos + aNumCharsToReplace,
                   aCharStr, aCharStr + StrLen(aCharStr));
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    replace( iterator aDestBegin, iterator aDestEnd, const T* aCharStr )
  {
    return replace(aDestBegin, aDestEnd, aCharStr, aCharStr + StrLen(aCharStr));
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    replace( size_type aPos, size_type aNumCharsToReplace,
             size_type aNumOfCharsToCopy, const T  aChar )
  {
    return replace(m_begin + aPos, m_begin + aPos + aNumCharsToReplace,
                   aNumOfCharsToCopy, aChar);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::this_type&
    StringBase<T>::
    replace( iterator  aDestBegin, iterator  aDestEnd,
             size_type aNumOfCharsToCopy, const T  aChar )
  {
    TLOC_ASSERT_STRING(aDestBegin >= m_begin && aDestBegin <= m_end,
      "Destination begin iterator is out of range!");
    TLOC_ASSERT_STRING(aDestEnd >= m_begin && aDestEnd <= m_end,
      "Destination end iterator is out of range!");

    erase(aDestBegin, aDestEnd);
    insert(aDestBegin, aNumOfCharsToCopy, aChar);

    return *this;
  }

  template <STRING_BASE_TYPES>
  template <typename T_InputIterator>
  STRING_BASE_TYPE::this_type&
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

  //------------------------------------------------------------------------
  // Operations

  template <STRING_BASE_TYPES>
  const T* StringBase<T>::
    c_str()
  {
    return m_begin;
  }

  template <STRING_BASE_TYPES>
  const T* StringBase<T>::
    c_str()const
  {
    return m_begin;
  }

  template <STRING_BASE_TYPES>
  const T* StringBase<T>::
    data()
  {
    return m_begin;
  }

  template <STRING_BASE_TYPES>
  const T* StringBase<T>::
    data() const
  {
    return m_begin;
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    copy( T* aDestArray, const size_type & aNumCharsToCopy,
          const size_type & aBegin )
  {
    TLOC_ASSERT_STRING(aBegin <= length(), "Begin is out of range!");
    TLOC_ASSERT_STRING_WARN( (aBegin + aNumCharsToCopy) <= length(),
      "Begin + number of chars is out of range.");

    const_iterator itrBegin = m_begin + aBegin;
    const_iterator itrEnd = (itrBegin + aNumCharsToCopy) > m_end
                                          ? m_end : itrBegin + aNumCharsToCopy;
    tloc::core::copy(itrBegin, itrEnd, aDestArray);
    return itrEnd - itrBegin;
  }

  //````````````````````````````````````````````````````````````````````````
  // Find

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find( const this_type& aStrToCompare, const size_type & aBeginIndex) const
  {
    return find(aStrToCompare.begin(), aBeginIndex, aStrToCompare.length());
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find( const T* aCharStr, const size_type & aBeginIndex,
          const size_type & aNumCharsToCompare ) const
  {
    iterator itrBegin = m_begin + aBeginIndex;

    TLOC_ASSERT_STRING(itrBegin <= m_end, "Index is out of range!");
    TLOC_ASSERT_STRING(StrLen(aCharStr) >= aNumCharsToCompare,
      "Number of characters to compare exceeds the input string length!");

    if (aNumCharsToCompare > 0)
    {
      const T* const findItr = search(itrBegin, m_end, aCharStr,
                                        aCharStr + aNumCharsToCompare);

      if (findItr != m_end) { return (size_t)(findItr - m_begin); }
    }

    return npos;
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find( const T* aCharStr, const size_type & aBeginIndex) const
  {
    return find(aCharStr, aBeginIndex, StrLen(aCharStr));
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find( T aChar, const size_type & aBeginIndex) const
  {
    iterator itrBegin = m_begin + aBeginIndex;

    TLOC_ASSERT_STRING(itrBegin <= m_end, "Index is out of range!");

    const T* const findItr = tloc::core::find(itrBegin, m_end, aChar);

    if (findItr != m_end) { return (size_type )(findItr - m_begin); }
    else { return npos; }
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    rfind( const this_type& aStrToCompare,
           const size_type & aBeginIndex ) const
  {
    return rfind(aStrToCompare.begin(), aBeginIndex, aStrToCompare.length());
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    rfind( const T* aCharStr, const size_type & aBeginIndex,
           const size_type & aNumCharsToCompare ) const
  {
    iterator itrBegin = m_begin + aBeginIndex;

    TLOC_ASSERT_STRING(itrBegin <= m_end, "Index is out of range!");
    TLOC_ASSERT_STRING(StrLen(aCharStr) >= aNumCharsToCompare,
      "Number of characters to compare exceeds the input string length!");

    if (aNumCharsToCompare > 0)
    {
      const T* const findItr = tloc::core::find_end(itrBegin, m_end, aCharStr,
                                                    aCharStr + aNumCharsToCompare);

      if (findItr != m_end) { return (size_t)(findItr - m_begin); }
    }

    return npos;
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    rfind( const T* aCharStr, const size_type & aBeginIndex ) const
  {
    return rfind(aCharStr, aBeginIndex, StrLen(aCharStr));
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    rfind( T aChar, const size_type & aBeginIndex ) const
  {
    return rfind(&aChar, aBeginIndex, 1);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_first_of( const this_type& aStrToCompare,
                   const size_type & aBeginIndex ) const
  {
    return find_first_of(aStrToCompare.begin(), aBeginIndex, aStrToCompare.length());
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_first_of( const T* aCharStr, const size_type & aBeginIndex,
                   const size_type & aNumCharsToCompare ) const
  {
    iterator itrBegin = m_begin + aBeginIndex;

    TLOC_ASSERT_STRING(itrBegin <= m_end, "Index is out of range!");
    TLOC_ASSERT_STRING(StrLen(aCharStr) >= aNumCharsToCompare,
      "Number of characters to compare exceeds the input string length!");

    if (aNumCharsToCompare > 0)
    {
      const T* const findItr =
        tloc::core::find_first_of(itrBegin, m_end, aCharStr,
                                  aCharStr + aNumCharsToCompare);

      if (findItr != m_end) { return (size_t)(findItr - m_begin); }
    }

    return npos;
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_first_of( const T* aCharStr, const size_type & aBeginIndex ) const
  {
    return find_first_of(aCharStr, aBeginIndex, StrLen(aCharStr));
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::find_first_of( T aChar, const size_type & aBeginIndex ) const
  {
    return find_first_of(&aChar, aBeginIndex, (size_type )1);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_last_of( const this_type& aStrToCompare,
                  const size_type & aBeginIndex ) const
  {
    return find_last_of(aStrToCompare.begin(), aBeginIndex, aStrToCompare.length());
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_last_of( const T* aCharStr, const size_type & aBeginIndex,
                  const size_type & aNumCharsToCompare ) const
  {
    iterator itrBegin = m_begin + aBeginIndex;

    TLOC_ASSERT_STRING(itrBegin <= m_end, "Index is out of range!");
    TLOC_ASSERT_STRING(StrLen(aCharStr) >= aNumCharsToCompare,
      "Number of characters to compare exceeds the input string length!");

    if (aNumCharsToCompare > 0)
    {
      const T* const findItr = find_end(itrBegin, m_end, aCharStr,
                                         aCharStr + aNumCharsToCompare);

      if (findItr != m_end) { return (size_t)(findItr - m_begin); }
    }

    return npos;
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_last_of( const T* aCharStr, const size_type & aBeginIndex ) const
  {
    return find_last_of(aCharStr, aBeginIndex, StrLen(aCharStr));
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_last_of( T aChar, const size_type & aBeginIndex ) const
  {
    return find_last_of(&aChar, aBeginIndex, 1);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_first_not_of( const this_type& aStrToCompare,
                       size_type aBeginIndex ) const
  {
    return find_first_not_of(aStrToCompare.begin(), aBeginIndex, aStrToCompare.length());
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_first_not_of( const T* aCharStr, const size_type & aBeginIndex,
                       size_type aNumCharsToCompare ) const
  {
    iterator itrBegin = m_begin + aBeginIndex;

    TLOC_ASSERT_STRING(itrBegin <= m_end, "Index is out of range!");
    TLOC_ASSERT_STRING(StrLen(aCharStr) >= aNumCharsToCompare,
      "Number of characters to compare exceeds the input string length!");

    if (aNumCharsToCompare > 0)
    {
      const T* const findItr =
        tloc::core::find_first_not_of(itrBegin, m_end, aCharStr,
                                      aCharStr + aNumCharsToCompare);

      if (findItr != m_end) { return (size_t)(findItr - m_begin); }
    }

    return npos;
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_first_not_of( const T* aCharStr, const size_type & aBeginIndex ) const
  {
    return find_first_not_of(aCharStr, aBeginIndex, StrLen(aCharStr));
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_first_not_of( T aChar, const size_type & aBeginIndex ) const
  {
    return find_first_not_of(&aChar, aBeginIndex, 1);
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_last_not_of( const this_type& aStrToCompare,
                      size_type aBeginIndex ) const
  {
    return find_last_not_of(aStrToCompare.begin(), aBeginIndex, aStrToCompare.length());
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_last_not_of( const T* aCharStr, const size_type & aBeginIndex,
                      size_type aNumCharsToCompare ) const
  {
    iterator itrBegin = m_begin + aBeginIndex;

    TLOC_ASSERT_STRING(itrBegin <= m_end, "Index is out of range!");
    TLOC_ASSERT_STRING(StrLen(aCharStr) >= aNumCharsToCompare,
      "Number of characters to compare exceeds the input string length!");

    if (aNumCharsToCompare > 0)
    {
      const T* const findItr =
        tloc::core::find_last_not_of(itrBegin, m_end, aCharStr,
                                     aCharStr + aNumCharsToCompare);

      if (findItr != m_end) { return (size_t)(findItr - m_begin); }
    }

    return npos;
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_last_not_of( const T* aCharStr, const size_type & aBeginIndex ) const
  {
    return find_last_not_of(aCharStr, aBeginIndex, StrLen(aCharStr));
  }

  template <STRING_BASE_TYPES>
  STRING_BASE_TYPE::size_type
    StringBase<T>::
    find_last_not_of( T aChar, const size_type & aBeginIndex ) const
  {
    return find_last_not_of(&aChar, aBeginIndex, 1);
  }

  //````````````````````````````````````````````````````````````````````````
  // Substr

  template <STRING_BASE_TYPES>
  StringBase<T> StringBase<T>::
    substr( size_type aBeginIndex, size_type aNumCharsToCopy ) const
  {
    StringBase<T> temp;
    substr(aBeginIndex, aNumCharsToCopy, temp);
    return temp;
  }

  template <STRING_BASE_TYPES>
  void StringBase<T>::
    substr( size_type aBeginIndex, size_type aNumCharsToCopy,
            this_type& aSubStrOut ) const
  {
    const_iterator itrBegin = m_begin + aBeginIndex;
    const_iterator itrBeginPlusN = itrBegin + aNumCharsToCopy;
    const_iterator itrEnd = aNumCharsToCopy == npos ? m_end :
                              ( itrBeginPlusN > m_end ? m_end : itrBeginPlusN);

    TLOC_ASSERT_STRING(itrBegin <= m_end, "Begin index is out of range!");
    TLOC_ASSERT_STRING_WARN(itrBeginPlusN <= m_end,
      "Begin + number of chars to copy is out of range.");

    aSubStrOut.assign(itrBegin, itrEnd);
  }

  //````````````````````````````````````````````````````````````````````````
  // Upper Lower

  template <STRING_BASE_TYPES>
  StringBase<T> StringBase<T>::
    to_upper()
  {
    StringBase<T> newString = *this;
    newString.make_upper();
    return newString;
  }

  template <STRING_BASE_TYPES>
  void StringBase<T>::
    to_upper( this_type& aStrOut )
  {
    aStrOut = *this;
    aStrOut.make_upper();
  }

  template <STRING_BASE_TYPES>
  StringBase<T> StringBase<T>::
    to_lower()
  {
    StringBase<T> newString = *this;
    newString.make_lower();
    return newString;
  }

  template <STRING_BASE_TYPES>
  void StringBase<T>::
    to_lower( this_type& aStrOut )
  {
    aStrOut = *this;
    aStrOut.make_lower();
  }

  template <STRING_BASE_TYPES>
  void StringBase<T>::
    make_upper()
  {
    size_type sizeOfString = length();
    for (tl_size i = 0; i < sizeOfString; ++i)
    {
      *(m_begin + i) = CharToUpper(*(m_begin + i));
    }
  }

  template <STRING_BASE_TYPES>
  void StringBase<T>::
    make_lower()
  {
    tl_size sizeOfString = length();
    for (tl_size i = 0; i < sizeOfString; ++i)
    {
      *(m_begin + i) = CharToLower(*(m_begin + i));
    }
  }

  //````````````````````````````````````````````````````````````````````````
  // Compare

  template <STRING_BASE_TYPES>
  tl_int StringBase<T>::
    compare( const this_type& aStr ) const
  {
    return StrCmp(c_str(), aStr.c_str());
  }
  template <STRING_BASE_TYPES>
  tl_int StringBase<T>::
    compare( const T* aCharStr ) const
  {
    return StrCmp(c_str(), aCharStr);
  }
  template <STRING_BASE_TYPES>
  tl_int StringBase<T>::
    compare( const tl_size& aThisPos, const tl_size& aThisLength,
             const this_type& aOtherStr ) const
  {
    TLOC_ASSERT_STRING(length() >= aThisPos + aThisLength,
      "Begin index + number of chars is out of range!");
    return DoCompare(m_begin + aThisPos, m_begin + aThisPos + aThisLength,
                     aOtherStr.begin(), aOtherStr.end());
  }
  template <STRING_BASE_TYPES>
  tl_int StringBase<T>::
    compare( const tl_size& aThisPos, const tl_size& aThisLength,
             const T* aOtherCharStr ) const
  {
    TLOC_ASSERT_STRING(length() >= aThisPos + aThisLength,
      "Begin index + number of chars is out of range!");

    return DoCompare(m_begin + aThisPos, m_begin + aThisPos + aThisLength,
                     aOtherCharStr, aOtherCharStr + StrLen(aOtherCharStr));
  }
  template <STRING_BASE_TYPES>
  tl_int StringBase<T>::
    compare( const tl_size& aThisPos, const tl_size& aThisLength,
             const this_type& aOtherStr, const tl_size& aOtherPos,
             const tl_size& aOtherLength ) const
  {
    TLOC_ASSERT_STRING(length() >= aThisPos + aThisLength,
      "Begin index + number of chars is out of range!");
    TLOC_ASSERT_STRING(aOtherStr.length() >= aOtherPos + aOtherLength,
      "Begin index + number of chars is out of range!");
    return DoCompare(m_begin + aThisPos, m_begin + aThisPos + aThisLength,
                     aOtherStr.begin() + aOtherPos,
                     aOtherStr.begin() + aOtherPos + aOtherLength);
  }
  template <STRING_BASE_TYPES>
  tl_int StringBase<T>::
    compare( const tl_size& aThisPos, const tl_size& aThisNumChars,
             const T* aOtherCharStr, const tl_size& aOtherPos ) const
  {
    TLOC_ASSERT_STRING(length() >= aThisPos + aThisNumChars,
      "Begin index + number of chars is out of range!");
    TLOC_ASSERT_STRING(StrLen(aOtherCharStr) >= aOtherPos,
      "Number of chars is out of range!");
    return DoCompare(m_begin + aThisPos, m_begin + aThisPos + aThisNumChars,
                     aOtherCharStr, aOtherCharStr + aOtherPos);
  }

  //------------------------------------------------------------------------
  // Internal functions

  template <STRING_BASE_TYPES>
  T* StringBase<T>::
    DoAllocate( const tl_size& aSize )
  {
    TLOC_ASSERT_STRING(aSize > 1,
      "Allocation size must be greater than 1 for the null terminator");

    return (T*)TL_MALLOC(aSize * sizeof(T));
  }

  template <STRING_BASE_TYPES>
  T* StringBase<T>::
    DoReAllocate( const tl_size& aSize )
  {
    TLOC_ASSERT_STRING(aSize > 1,
      "Allocation size must be greater than 1 for the null terminator");

    // Make sure that the size is not 0, otherwise we would trying to reallocate
    // the empty string
    if ( size() != 0) { return (T*)TL_REALLOC(m_begin, sizeof(T) * aSize); }
    else { return DoAllocate(aSize); }
  }

  /*!
   * \brief Reallocates to aSize
   *
   * Increases the storage capacity by reallocation. The function also readjusts
   * the iterators.
   *
   * \return void
   * \note Function does not do anything if ReAllocate() fails
   * \warning
   */
  template <STRING_BASE_TYPES>
  void StringBase<T>::
    DoReAllocateAndAdjust( const tl_size& aSize )
  {
    TLOC_ASSERT_STRING(aSize > capacity(),
      "This function can only increase the storage capacity! (passed size is "
      "smaller than the current capacity)");

    const tl_size prevSize = size();
    const tl_size newCap   = aSize;

    T* ptr = DoReAllocate(aSize);

    TLOC_ASSERT_STRING(ptr != nullptr, "Could not allocate/re-allocate!");

    if (ptr)
    {
      m_begin     = ptr;
      m_end       = m_begin + prevSize;
      m_capacity  = m_begin + newCap;
    }
  }

  /*!
   * \brief Reallocates automatically
   *
   * Increases the storage capacity by reallocation. This function automatically
   * resizes the array according to the formula:
   * \f[
   * newCapacity = m_capacity ? capacity() * 2 : sm_defaultCapacity;
   * \f]
   * and adjusts the iterators. If successful, old iterators are considered
   * invalid.
   *
   * \return void
   * \note Function does not do anything if ReAllocate() fails
   * \warning
   */
  template <STRING_BASE_TYPES>
  void StringBase<T>::
    DoReAllocateAndAdjust()
  {
    const tl_size prevCap  = capacity();
    const tl_size newCap   = prevCap ? (2 * prevCap) : sm_defaultCapacity;

    DoReAllocateAndAdjust(newCap);
  }

  template <STRING_BASE_TYPES>
  void StringBase<T>::
    DoFree( T* aPtr )
  {
    TL_FREE(aPtr);
  }

  template <STRING_BASE_TYPES>
  void StringBase<T>::
    DoAllocateSelf()
  {
    //TLOC_ASSERT_STRING_EMPTY_STRING();

    m_begin     = const_cast<T*>( GetEmptyString(T()) );
    m_end       = m_begin;
    m_capacity  = m_begin + 1;
  }

  template <STRING_BASE_TYPES>
  void StringBase<T>::
    DoAllocateSelf( const tl_size& aSize )
  {
    TLOC_ASSERT_STRING(aSize <= TL_ULONG_MAX, "Allocating too large a value!");

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

  template <STRING_BASE_TYPES>
  void StringBase<T>::
    DoDeallocateSelf()
  {
    if ( (m_capacity - m_begin) > 1)
    {
      DoFree(m_begin);
    }
  }

  template <STRING_BASE_TYPES>
  void StringBase<T>::
    RangeInitialize( const T* aPtrBegin )
  {
    TLOC_ASSERT_STRING(aPtrBegin, "aPtrBegin cannot be NULL!");

    RangeInitialize(aPtrBegin, aPtrBegin + StrLen(aPtrBegin));
  }

  template <STRING_BASE_TYPES>
  void StringBase<T>::
    RangeInitialize( const T* aPtrBegin, const T* aPtrEnd )
  {
    if (aPtrBegin != aPtrEnd)
    {
      TLOC_ASSERT_STRING_RANGE(aPtrBegin, aPtrEnd);

      DoAllocateSelf( (tl_size)(aPtrEnd - aPtrBegin + 1));

      m_end = tloc::core::copy(aPtrBegin, aPtrEnd, m_begin);
      *m_end = 0; // Null terminator
    }
    else
    {
      DoAllocateSelf();
    }
  }

  template <STRING_BASE_TYPES>
  tl_int StringBase<T>::
    DoCompare( const T* aBegin1, const T* aEnd1,
               const T* aBegin2, const T* aEnd2 ) const
  {
    TLOC_ASSERT_STRING_RANGE(aBegin1, aEnd1);
    TLOC_ASSERT_STRING_RANGE(aBegin2, aEnd2);

    const tl_size size1 = aEnd1 - aBegin1;
    const tl_size size2 = aEnd2 - aBegin2;
    const tl_size sizeMin = tlMin(size1, size2);

    const tl_int cmp = StrCmp(aBegin1, aBegin2, sizeMin);

    if (cmp != 0)
    { return cmp; }
    else
    {
      if (size1 < size2)
      { return -1; }
      else
      { return (size1 > size2) ? 1 : 0; }
    }
  }

  //////////////////////////////////////////////////////////////////////////
  // Plus operator global

  template <typename T>
  StringBase<T>
    operator+ (const StringBase<T>& a_lhs, const StringBase<T>& a_rhs)
  {
    StringBase<T> temp(a_lhs);
    temp += a_rhs;
    return temp;
  }

  template <typename T>
  StringBase<T>
    operator+ (const T* a_lhs, const StringBase<T>& a_rhs)
  {
    StringBase<T> temp(a_lhs);
    temp += a_rhs;
    return temp;
  }

  template <typename T>
  StringBase<T>
    operator+ (T a_lhs, const StringBase<T>& a_rhs)
  {
    StringBase<T> temp(1, a_lhs);
    temp += a_rhs;
    return temp;
  }

  template <typename T>
  StringBase<T>
    operator+ (const StringBase<T>& a_lhs, const T* a_rhs)
  {
    StringBase<T> temp(a_lhs);
    temp += a_rhs;
    return temp;
  }

  template <typename T>
  StringBase<T>
    operator+ (const StringBase<T>& a_lhs, T a_rhs)
  {
    StringBase<T> temp(a_lhs);
    temp += a_rhs;
    return temp;
  }

  // Explicitly instantiate the operators for our string types
  template String operator+ (const String& a_lhs, const String& a_rhs);
  template String operator+ (const char8* a_lhs, const String& a_rhs);
  template String operator+ (char8 a_lhs, const String& a_rhs);
  template String operator+ (const String& a_lhs, const char8* a_rhs);
  template String operator+ (const String& a_lhs, char8 a_rhs);

  template StringW operator+ (const StringW& a_lhs, const StringW& a_rhs);
  template StringW operator+ (const char32* a_lhs, const StringW& a_rhs);
  template StringW operator+ (char32 a_lhs, const StringW& a_rhs);
  template StringW operator+ (const StringW& a_lhs, const char32* a_rhs);
  template StringW operator+ (const StringW& a_lhs, char32 a_rhs);

  //////////////////////////////////////////////////////////////////////////
  // Global functions

  template <typename T>
  tl_size
    StrLen( const T* aCharStr )
  {
    const T* lTemp = aCharStr;

    while (*lTemp) { ++lTemp; }

    return (tl_size)(lTemp - aCharStr);
  }

  template <>
  TL_I tl_size
    StrLen( const char8* aCharStr)
  {
    // According to EASTL, this should call intrinsics
    return (tl_size)strlen(aCharStr);
  }

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

  TL_I tl_int
    StrCmp( const char8* src, const char8* dst)
  {
    // std implementation is faster
    return strcmp(src, dst);
  }

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

  template <>
  TL_I tl_int
    StrCmp( const char8* aPtr1, const char8* aPtr2,
            const tl_size& aNumChars )
  {
    return memcmp(aPtr1, aPtr2, aNumChars);
  }

  template <typename T>
  T
    CharToLower( const T& aChar )
  {
    TLOC_ASSERT_STRING(aChar <= 0xFF,
      "Character is out of range for this function!");
    return (T)tolower((char8)aChar);
  }

  template <typename T>
  T
    CharToUpper( const T& aChar)
  {
    TLOC_ASSERT_STRING(aChar <= 0xFF,
      "Character is out of range for this function!");
    return (T)toupper((char8)aChar);
  }

  TL_I tl_int
    CharAsciiToWide(char32* a_out, const char8* a_in, tl_int a_inSize)
  {
    return ::mbstowcs(a_out, a_in, a_inSize);
  }

  TL_I tl_int
    CharWideToAscii(char8* a_out, const char32* a_in, tl_int a_inSize)
  {
    return ::wcstombs(a_out, a_in, a_inSize);
  }

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

  TL_I bool
    IsCntrl(char8 a_char)
  {
    // We cannot test for NULL in g_controlStr because it is also the terminator
    if (a_char == NULL)
    { return true; }

    return g_controlsStr.find(a_char) != String::npos;
  }

  TL_I bool
    IsBlank(char8 a_char)
  { return g_blankStr.find(a_char) != String::npos; }

  TL_I bool
    IsSpace(char8 a_char)
  { return g_spaceStr.find(a_char) != String::npos; }

  TL_I bool
    IsUpper(char8 a_char)
  { return g_upperStr.find(a_char) != String::npos; }

  TL_I bool
    IsLower(char8 a_char)
  { return g_lowerStr.find(a_char) != String::npos; }

  TL_I bool
    IsAlpha(char8 a_char)
  { return g_alphaStr.find(a_char) != String::npos; }

  TL_I bool
    IsDigit(char8 a_char)
  { return g_digitStr.find(a_char) != String::npos; }

  TL_I bool
    IsNumber(const char8* a_char)
  {
    typedef const char8*    iterator;

    iterator itr    = a_char;
    iterator itrEnd = a_char + StrLen(a_char);

    // Starting with a minus sign? Continue...
    if (*itr == '-')
    {
      ++itr;

      // only a minus sign is not a number
      if (itr == itrEnd)
      { return false; }
    }

    while (itr != itrEnd)
    {
      if (IsDigit(*itr) == false)
      {
        return false;
      }
      ++itr;
    }

    return true;
  }

  TL_I bool
    IsRealNumber(const char8* a_char)
  {
    typedef const char8*    iterator;

    iterator itr = a_char;
    iterator itrEnd = a_char + StrLen(a_char);

    // Starting with a minus sign? Continue...
    if (*itr == '-')
    {
      ++itr;

      // only a minus sign is not a number
      if (itr == itrEnd)
      { return false; }
    }

    bool decimalPointFound = false;

    while (itr != itrEnd)
    {
      if (*itr == '.')
      {
        if (decimalPointFound)
        { return false; }

        decimalPointFound = true;
      }
      else
      {
        if (IsDigit(*itr) == false)
        { return false; }
      }

      ++itr;
    }

    return true;
  }

  TL_I bool
    IsXDigit(char8 a_char)
  { return g_xdigitStr.find(a_char) != String::npos; }

  TL_I bool
    IsAlNum(char8 a_char)
  { return g_alnumStr.find(a_char) != String::npos; }

  TL_I bool
    IsPunct(char8 a_char)
  { return g_punctStr.find(a_char) != String::npos; }


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

  template <typename T>
  bool
    operator==( const T* a, const StringBase<T>& b )
  {
    const tl_size charStrSize = StrLen(a);
    return ( (charStrSize == b.size()) && (memcmp(a, b.c_str(),
              charStrSize * sizeof(T)) == 0) );
  }

  template <typename T>
  bool
    operator==( const StringBase<T>& a, const T* b )
  {
    const tl_size charStrSize = StrLen(b);
    return ( (charStrSize == a.size()) && (memcmp(b, a.c_str(),
              charStrSize * sizeof(T)) == 0) );
  }

  template <typename T>
  bool
    operator!=( const StringBase<T>& a, const StringBase<T>& b )
  {
    return !(a == b);
  }

  template <typename T>
  bool
    operator!=( const T* a, const StringBase<T>& b )
  {
    return !(a == b);
  }

  template <typename T>
  bool
    operator!=( const StringBase<T>& a, const T* b )
  {
    return !(a == b);
  }

};};};

#endif
