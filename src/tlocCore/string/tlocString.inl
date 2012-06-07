#ifndef TLOC_STRING_INL
#define TLOC_STRING_INL

#ifndef TLOC_STRING_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocAlgorithms.inl>
#include <tlocCore/utilities/tlocTemplateUtils.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <string.h>

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
# define WIN32_LEAN_AND_MEAN
# include <Windows.h>
#endif

namespace tloc { namespace core {
  //////////////////////////////////////////////////////////////////////////
  // Macros (mostly for assertions)

#define TLOC_ASSERT_STRING_EMPTY_STRING() \
  TLOC_ASSERT_STRING( *(GetEmptyString(char32())) == 0, \
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

  template <typename T>
  const tl_size StringBase<T>::m_MaxSize = (tl_size) - 2;

  template <typename T>
  const tl_size StringBase<T>::sm_defaultCapacity = 2;

  //------------------------------------------------------------------------
  // Ctors

  template <typename T>
  TL_I StringBase<T>::StringBase()
    : m_begin(NULL)
    , m_end(NULL)
    , m_capacity(NULL)
  {
    DoAllocateSelf();
  }

  template <typename T>
  TL_I StringBase<T>::StringBase(const StringBase<T>& aOther)
    : m_begin(NULL)
    , m_end(NULL)
    , m_capacity(NULL)
  {
    RangeInitialize(aOther.begin(), aOther.end());
  }

  template <typename T>
  TL_I StringBase<T>::StringBase(const StringBase<T>& aOther, tl_size aPosition,
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
  TL_I StringBase<T>::StringBase(const T* aPtr, tl_size aNumChars)
  {
    RangeInitialize(aPtr, aPtr + aNumChars);
  }

  template <typename T>
  TL_I StringBase<T>::StringBase(const T* aPtr)
  {
    RangeInitialize(aPtr);
  }

  template <typename T>
  TL_I StringBase<T>::StringBase(tl_size aNumChars, T aChar)
  {
    DoAllocateSelf();
    append(aNumChars, aChar);
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_I StringBase<T>::StringBase(const T_InputIterator aPtrBegin,
                                 const T_InputIterator aPtrEnd)
  {
    RangeInitialize(aPtrBegin, aPtrEnd);
  }

  template <typename T>
  TL_I StringBase<T>::StringBase(StringNoInitialize, tl_size aN)
  {
    DoAllocateSelf(aN + 1);
    *m_end = 0;
  }

  template <typename T>
  TL_I StringBase<T>::StringBase(StringSprintf, const tl_size aFormat, ...)
  {
    TLOC_STATIC_ASSERT_WIP();
    // TODO: Implement this string ctor
  }

  template <typename T>
  TL_I  StringBase<T>::~StringBase()
  {
    DoDeallocateSelf();
  }

  //------------------------------------------------------------------------
  // Iterators

  template <typename T>
  TL_I typename StringBase<T>::iterator StringBase<T>::begin()
  {
    return m_begin;
  }

  template <typename T>
  TL_I typename StringBase<T>::const_iterator StringBase<T>::begin() const
  {
    return m_begin;
  }

  template <typename T>
  TL_I typename StringBase<T>::iterator StringBase<T>::end()
  {
    return m_end;
  }

  template <typename T>
  TL_I typename StringBase<T>::const_iterator StringBase<T>::end() const
  {
    return m_end;
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
  TL_I void StringBase<T>::resize(const tl_size& newSize)
  {
    TLOC_STATIC_ASSERT_WIP();
  }

  template <typename T>
  TL_I void StringBase<T>::resize(const tl_size& newSize, const T charToFill)
  {
    TLOC_STATIC_ASSERT_WIP();
  }

  template <typename T>
  TL_I tl_size StringBase<T>::capacity() const
  {
    // Do not report the memory allocated for the null terminator
    return (tl_size)(m_capacity - m_begin - 1);
  }

  /*!
   * \brief Sets the capacity of the string to the specified capacity.
   *
   * The capacity may increase or shrink. This may result in some of the string
   * being stripped off. Setting the new capacity to 'npos' will ensure that
   * the capacity == size.
   *
   * \param const tl_size & newCapacity
   * \return tl_size
   * \sa resize(), reserve()
   */
  template <typename T>
  TL_I void StringBase<T>::set_capacity(const tl_size& newCapacity)
  {
    if (newCapacity != capacity())
    {
      const tl_size oldSize = length();
      const tl_size cap = (newCapacity == npos) ? oldSize : newCapacity;

      if (cap > 0)
      {
        const tl_size oldSize = size();

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
   * \param const tl_size & newSize
   * \return void
   * \sa set_capacity(), resize()
   * \note The function can only increase capacity. Call resize() to decrease capacity.
   * \warning
   */
  template <typename T>
  TL_I void StringBase<T>::reserve(const tl_size& newSize)
  {
    TLOC_ASSERT_STRING(newSize < m_MaxSize, "Reserve request is too large!");
    TLOC_ASSERT_STRING_WARN(newSize > capacity(), "Reserve request is smaller "
      L"than the current capacity. Call resize() for shrinking.");

    if (newSize > capacity()) // Exclude /0
    {
      set_capacity(newSize);
    }
  }

  template <typename T>
  TL_I void StringBase<T>::clear()
  {
    *m_begin = T(0);
    m_end   = m_begin;
  }

  template <typename T>
  TL_I bool StringBase<T>::empty()
  {
    return (m_begin == m_end);
  }

  //------------------------------------------------------------------------
  // Modifiers


  //````````````````````````````````````````````````````````````````````````
  // Operators

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::operator+=( const StringBase<T>& aStr )
  {
    return append(aStr);
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::operator+=( const T* charStr )
  {
    return append(charStr);
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::operator+=( const T& character )
  {
    return *this;
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::operator=( const StringBase<T>& aStr )
  {
    TLOC_ASSERT_STRING_WARN(&aStr != this, "Assigning the same string!");

    return assign(aStr.m_begin, aStr.m_end);
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::operator=( const T* aCharStr )
  {
    return assign(aCharStr, aCharStr + StrLen(aCharStr));
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::operator=( T aChar )
  {
    return assign(1, aChar);
  }

  template <typename T>
  TL_I void StringBase<T>::swap( T& aX )
  {
    TLOC_ASSERT_STRING_WARN(this != &aX, "Swap called on self (redundant).");

    swap(aX.m_begin, m_begin);
    swap(aX.m_end, m_end);
    swap(aX.m_capacity, m_capacity);
  }

  //````````````````````````````````````````````````````````````````````````
  // Append

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::append( const StringBaseT& aStr )
  {
    return append(aStr.m_begin, aStr.m_end);
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::append( const StringBaseT& aStr,
                                             const tl_size& aPos,
                                             const tl_size& aNumChars )
  {
    TLOC_ASSERT_STRING(aPos < aStr.size(),
      "Position passed is outside of string's range!");
    TLOC_ASSERT_STRING_WARN( (aPos + aNumChars) < aStr.size(),
      "Number of characters to copy passes the string's range.");

    tl_size maxCharsLeft = (aStr.m_end - aStr.m_begin) - aPos;
    return append(aStr.begin() + aPos, aStr.begin() + aPos +
      (aNumChars > maxCharsLeft ? maxCharsLeft : aNumChars) );
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::append( const T* charArray,
                                             const tl_size& aNumChars )
  {
    TLOC_ASSERT_STRING(StrLen(charArray) >= aNumChars,
      "Number of characters to copy exceeds the range of the character array!");

    return append(charArray, charArray + aNumChars);
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::append( const T* charStr )
  {
    return append(charStr, charStr + StrLen(charStr));
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::append( const tl_size& aNumChars,
                                             const T& aChar )
  {
    if (aNumChars > 0)
    {
      const tl_size currSize = size();

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

  template <typename T>
  template <typename T_InputIterator>
  TL_I StringBase<T>& StringBase<T>::append( T_InputIterator aBegin,
                                             T_InputIterator aEnd )
  {
    if (aBegin != aEnd)
    {
      const tl_size oldSize = size();
      const tl_size oldCapacity = m_capacity - m_begin;
      const tl_size rangeSize = (tl_size)(aEnd - aBegin);

      if ( (oldSize + rangeSize) > (oldCapacity - 1) ) // -1 because of /0
      {
        DoReAllocateAndAdjust(oldSize + rangeSize + 1);
      }

      m_end = tloc::core::copy(aBegin, aEnd, m_end);
      *m_end = 0;
    }

    return *this;
  }

  template <typename T>
  TL_I void StringBase<T>::push_back(const T& aChar)
  {
    append(1, aChar);
  }

  //````````````````````````````````````````````````````````````````````````
  // Assign

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::assign( const StringBaseT& aStr )
  {
    return assign(aStr.begin(), aStr.end());
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::assign( const StringBaseT& aStr,
                                             const tl_size& aPos,
                                             const tl_size& aNumChars )
  {
    TLOC_ASSERT_STRING(aPos <= aStr.size(), "Position is out of range!");

    const T* endItr = aStr.begin() + aPos + aNumChars;
    return assign(aStr.begin() + aPos, (aStr.end() > endItr) ? endItr : aStr.end() );
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::assign( const T* aCharStr,
                                             const tl_size& aNumChars )
  {
    TLOC_ASSERT_STRING(aNumChars <= StrLen(aCharStr),
      "Length of char string is smaller than number of chars to copy");

    return assign(aCharStr, aCharStr + aNumChars);
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::assign( const T* aCharStr )
  {
    return assign(aCharStr, aCharStr + StrLen(aCharStr));
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::assign( const tl_size& aNumChars,
                                             const T& aChar )
  {
    const tl_size ourSize = size();
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

  template <typename T>
  template <typename T_InputIterator>
  TL_I StringBase<T>& StringBase<T>::assign(const T_InputIterator aBegin,
                                            const T_InputIterator aEnd)
  {
    const tl_size ourSize = size();
    const tl_size rangeSize = aEnd - aBegin;
    if (rangeSize <= ourSize)
    {
      memmove(m_begin, aBegin, (tl_size)(rangeSize * sizeof(T)) );
      erase(m_begin + rangeSize, m_end);
    }
    else
    {
      memmove(m_begin, aBegin, (tl_size)(ourSize) * sizeof(T) );
      append(aBegin + (tl_size)(ourSize), aEnd);
    }

    return *this;
  }

  //````````````````````````````````````````````````````````````````````````
  // Insert

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::insert( tl_size aIndex, const StringBaseT& aStr )
  {
    insert(m_begin + aIndex, aStr.begin(), aStr.end());
    return *this;
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::insert( tl_size aIndexDestination,
                                             const StringBaseT& aStr,
                                             tl_size aIndexSource,
                                             tl_size aNumChars )
  {
    const_iterator endItr = aStr.begin() + aIndexSource + aNumChars;
    insert(m_begin + aIndexDestination, aStr.begin() + aIndexSource,
                                  (aStr.end() > endItr) ? endItr : aStr.end() );
    return *this;
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::insert( tl_size aIndex, const T* aCharArray,
                                             tl_size aNumChars )
  {
    insert(m_begin + aIndex, aCharArray, aCharArray + aNumChars);
    return *this;
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::insert( tl_size aIndex, const T* aCharStr )
  {
    insert(m_begin + aIndex, aCharStr, aCharStr + StrLen(aCharStr));
    return *this;
  }

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::insert( tl_size aIndex, tl_size aNumChars,
                                             T aChar )
  {
    insert(m_begin + aIndex, aNumChars, aChar);
    return *this;
  }

  template <typename T>
  TL_I typename StringBase<T>::iterator StringBase<T>::insert( const_iterator aPos,
                                                               const T& aChar )
  {
    // Save the position index because it may be invalid by the time insert()
    // is complete
    const tl_size posIndex = aPos - m_begin;
    insert(aPos, 1, aChar);
    return m_begin + posIndex;
  }

  template <typename T>
  TL_I void StringBase<T>::insert( const_iterator aPos, tl_size aNumChars,
                                   T aChar )
  {
    TLOC_ASSERT_STRING(aPos >= m_begin && aPos <= m_end,
      "Iterator position is out of range!");

    const tl_size currCap = m_capacity - m_begin;
    const tl_size startIndex = aPos - m_begin;
    const tl_size newCap = size() + aNumChars + 1;

    if (currCap < newCap)
    {
      DoReAllocateAndAdjust(newCap);
    }

    iterator pos = m_begin + startIndex;

    memmove(pos + aNumChars, pos, (tl_size)( (m_end - (pos) + 1) * sizeof(T)) );
    fill(pos, pos + aNumChars, aChar);

    m_end = m_end + aNumChars;
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_I void StringBase<T>::insert( const_iterator aPos, T_InputIterator aBegin,
                                                        T_InputIterator aEnd )
  {
    TLOC_ASSERT_STRING(aBegin <= aEnd, "Input range is invalid!");
    TLOC_ASSERT_STRING(aPos >= m_begin && aPos <= m_end,
      "Iterator position is out of range!");

    const tl_size startIndex = aPos - m_begin;
    const tl_size currCap = m_capacity - m_begin;
    const tl_size rangeSize = aEnd - aBegin;
    const tl_size newCap = size() + rangeSize + 1; // +1 for the NULL char

    // Check if we have enough capacity
    if (currCap < newCap)
    {
      DoReAllocateAndAdjust(newCap);
    }

    iterator pos = m_begin + startIndex;

    // +1 for the NULL character
    memmove(pos + rangeSize, pos, (tl_size)((m_end - (pos) + 1) * sizeof(T)) );
    memmove(pos, aBegin, (tl_size)(rangeSize * sizeof(T)) );

    m_end = m_end + rangeSize;
  }

  //````````````````````````````````````````````````````````````````````````
  // Erase

  template <typename T>
  TL_I StringBase<T>& StringBase<T>::erase( const tl_size& aPos /*= 0*/,
                                            const tl_size& aNumChars /*= npos*/ )
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

  template <typename T>
  TL_I typename StringBase<T>::iterator StringBase<T>::erase( iterator aPos )
  {
    TLOC_ASSERT_STRING(aPos >= m_begin && aPos < m_end,
      "Position is out of range!");

    return erase(aPos, aPos + 1);
  }

  template <typename T>
  TL_I typename StringBase<T>::iterator StringBase<T>::erase( iterator aFirst,
                                                              iterator aLast )
  {
    TLOC_ASSERT_STRING(aFirst >= m_begin && aFirst <= m_end ,
      "Iterator aFirst is out of range!");
    TLOC_ASSERT_STRING(aLast >= m_begin || aLast <= m_end,
      "Iterator aLast is out of range!");
    TLOC_ASSERT_STRING(aFirst <= aLast, "Invalid iterator range (aFirst > aLast)!");

    if (aFirst != aLast)
    {
      const tl_size rangeSize = aLast - aFirst;

      // Move the remaining string into place including the /0
      memmove( aFirst, aLast, (tl_size)((m_end - aLast) + 1) * sizeof(T) );
      m_end -= rangeSize;
    }

    return aFirst;
  }

  //````````````````````````````````````````````````````````````````````````
  // Replace

  template <typename T>
  TL_I StringBase<T>&
    StringBase<T>::replace( tl_size aPos, tl_size aNumCharsToReplace,
                            const StringBase<T>& aStr )
  {
    return replace(m_begin + aPos, m_begin + aPos + aNumCharsToReplace,
      aStr.begin(), aStr.end());
  }

  template <typename T>
  TL_I StringBase<T>&
    StringBase<T>::replace( iterator aDestBegin, iterator aDestEnd,
                            const StringBase<T>& aStr )
  {
    return replace(aDestBegin, aDestEnd, aStr.begin(), aStr.end());
  }

  template <typename T>
  TL_I StringBase<T>&
    StringBase<T>::replace( tl_size aDestPos, tl_size aNumCharsToReplace,
                            const StringBase<T>& aStr, tl_size aSourcePos,
                            tl_size aNumCharsToCopy )
  {
    const_iterator itrSourceEnd = aStr.begin() + aSourcePos + aNumCharsToCopy;

    return replace(m_begin + aDestPos, m_begin + aDestPos + aNumCharsToReplace,
      aStr.begin() + aSourcePos, (itrSourceEnd > aStr.end()) ? aStr.end() : itrSourceEnd);
  }

  template <typename T>
  TL_I StringBase<T>&
    StringBase<T>::replace( tl_size   aPos, tl_size   aNumCharsToReplace,
                            const T*  aCharArray, tl_size   aNumCharsToCopy )
  {
    return replace(m_begin + aPos, m_begin + aPos + aNumCharsToReplace,
                   aCharArray, aCharArray + aNumCharsToCopy);
  }

  template <typename T>
  TL_I StringBase<T>&
    StringBase<T>::replace( iterator  aDestBegin, iterator  aDestEnd,
                            const T*  aCharArray, tl_size   aNumCharsToCopy )
  {
    return replace(aDestBegin, aDestEnd, aCharArray, aCharArray + aNumCharsToCopy);
  }

  template <typename T>
  TL_I StringBase<T>&
    StringBase<T>::replace( tl_size   aPos, tl_size   aNumCharsToReplace,
                            const T*  aCharStr )
  {
    return replace(m_begin + aPos, m_begin + aPos + aNumCharsToReplace,
                   aCharStr, aCharStr + StrLen(aCharStr));
  }

  template <typename T>
  TL_I StringBase<T>&
    StringBase<T>::replace( iterator aDestBegin, iterator aDestEnd,
                            const T* aCharStr )
  {
    return replace(aDestBegin, aDestEnd, aCharStr, aCharStr + StrLen(aCharStr));
  }

  template <typename T>
  TL_I StringBase<T>&
    StringBase<T>::replace( tl_size   aPos, tl_size   aNumCharsToReplace,
                            tl_size   aNumOfCharsToCopy, const T  aChar )
  {
    return replace(m_begin + aPos, m_begin + aPos + aNumCharsToReplace,
                   aNumOfCharsToCopy, aChar);
  }

  template <typename T>
  TL_I StringBase<T>&
    StringBase<T>::replace( iterator  aDestBegin, iterator  aDestEnd,
                            tl_size   aNumOfCharsToCopy, const T  aChar )
  {
    TLOC_ASSERT_STRING(aDestBegin >= m_begin && aDestBegin <= m_end,
      "Destination begin iterator is out of range!");
    TLOC_ASSERT_STRING(aDestEnd >= m_begin && aDestEnd <= m_end,
      "Destination end iterator is out of range!");

    erase(aDestBegin, aDestEnd);
    insert(aDestBegin, aNumOfCharsToCopy, aChar);

    return *this;
  }

  template <typename T>
  template <typename T_InputIterator>
  TL_I StringBase<T>&
    StringBase<T>::replace(iterator aDestBegin, iterator aDestEnd,
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

  template <typename T>
  TL_I const T* StringBase<T>::c_str()
  {
    return m_begin;
  }

  template <typename T>
  TL_I const T* StringBase<T>::c_str()const
  {
    return m_begin;
  }

  template <typename T>
  TL_I const T* StringBase<T>::data()
  {
    return m_begin;
  }

  template <typename T>
  TL_I const T* StringBase<T>::data() const
  {
    return m_begin;
  }

  template <typename T>
  TL_I tl_size StringBase<T>::copy( T* aDestArray,
                                    const tl_size& aNumCharsToCopy,
                                    const tl_size& aBegin )
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

  template <typename T>
  TL_I tl_size StringBase<T>::find( const StringBaseT& aStrToCompare,
                                    const tl_size& aBeginIndex /*= 0*/ ) const
  {
    return find(aStrToCompare.begin(), aBeginIndex, aStrToCompare.length());
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find( const T* aCharStr, const tl_size& aBeginIndex,
                                    const tl_size& aNumCharsToCompare ) const
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

  template <typename T>
  TL_I tl_size StringBase<T>::find( const T* aCharStr,
                                    const tl_size& aBeginIndex /*= 0*/ ) const
  {
    return find(aCharStr, aBeginIndex, StrLen(aCharStr));
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find( T aChar, const tl_size& aBeginIndex /*= 0*/ ) const
  {
    iterator itrBegin = m_begin + aBeginIndex;

    TLOC_ASSERT_STRING(itrBegin <= m_end, "Index is out of range!");

    const T* const findItr = tloc::core::find(itrBegin, m_end, aChar);

    if (findItr != m_end) { return (tl_size)(findItr - m_begin); }
    else { return npos; }
  }

  template <typename T>
  TL_I tl_size StringBase<T>::rfind( const StringBaseT& aStrToCompare,
                                     const tl_size& aBeginIndex ) const
  {
    return rfind(aStrToCompare.begin(), aBeginIndex, aStrToCompare.length());
  }

  template <typename T>
  TL_I tl_size StringBase<T>::rfind( const T* aCharStr,
                                     const tl_size& aBeginIndex,
                                     const tl_size& aNumCharsToCompare ) const
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

  template <typename T>
  TL_I tl_size StringBase<T>::rfind( const T* aCharStr,
                                     const tl_size& aBeginIndex ) const
  {
    return rfind(aCharStr, aBeginIndex, StrLen(aCharStr));
  }

  template <typename T>
  TL_I tl_size StringBase<T>::rfind( T aChar, const tl_size& aBeginIndex ) const
  {
    return rfind(&aChar, aBeginIndex, 1);
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find_first_of( const StringBaseT& aStrToCompare,
                                             const tl_size& aBeginIndex ) const
  {
    return find_first_of(aStrToCompare.begin(), aBeginIndex, aStrToCompare.length());
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find_first_of( const T* aCharStr,
                                             const tl_size& aBeginIndex,
                                             const tl_size& aNumCharsToCompare ) const
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

  template <typename T>
  TL_I tl_size StringBase<T>::find_first_of( const T* aCharStr,
                                             const tl_size& aBeginIndex ) const
  {
    return find_first_of(aCharStr, aBeginIndex, StrLen(aCharStr));
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find_first_of( T aChar,
                                             const tl_size& aBeginIndex ) const
  {
    return find_first_of(&aChar, aBeginIndex, (tl_size)1);
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find_last_of( const StringBaseT& aStrToCompare,
                                            const tl_size& aBeginIndex ) const
  {
    return find_last_of(aStrToCompare.begin(), aBeginIndex, aStrToCompare.length());
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find_last_of( const T* aCharStr,
                                            const tl_size& aBeginIndex,
                                            const tl_size& aNumCharsToCompare ) const
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

  template <typename T>
  TL_I tl_size StringBase<T>::find_last_of( const T* aCharStr,
                                            const tl_size& aBeginIndex ) const
  {
    return find_last_of(aCharStr, aBeginIndex, StrLen(aCharStr));
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find_last_of( T aChar,
                                            const tl_size& aBeginIndex ) const
  {
    return find_last_of(&aChar, aBeginIndex, 1);
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find_first_not_of( const StringBaseT& aStrToCompare,
                                                 tl_size aBeginIndex ) const
  {
    return find_first_not_of(aStrToCompare.begin(), aBeginIndex, aStrToCompare.length());
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find_first_not_of( const T* aCharStr,
                                                 const tl_size& aBeginIndex,
                                                 tl_size aNumCharsToCompare ) const
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

  template <typename T>
  TL_I tl_size StringBase<T>::find_first_not_of( const T* aCharStr,
                                                 const tl_size& aBeginIndex ) const
  {
    return find_first_not_of(aCharStr, aBeginIndex, StrLen(aCharStr));
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find_first_not_of( T aChar,
                                                 const tl_size& aBeginIndex ) const
  {
    return find_first_not_of(&aChar, aBeginIndex, 1);
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find_last_not_of( const StringBaseT& aStrToCompare,
                                                tl_size aBeginIndex ) const
  {
    return find_last_not_of(aStrToCompare.begin(), aBeginIndex, aStrToCompare.length());
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find_last_not_of( const T* aCharStr,
                                                const tl_size& aBeginIndex,
                                                tl_size aNumCharsToCompare ) const
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

  template <typename T>
  TL_I tl_size StringBase<T>::find_last_not_of( const T* aCharStr,
                                                const tl_size& aBeginIndex ) const
  {
    return find_last_not_of(aCharStr, aBeginIndex, StrLen(aCharStr));
  }

  template <typename T>
  TL_I tl_size StringBase<T>::find_last_not_of( T aChar,
                                                const tl_size& aBeginIndex ) const
  {
    return find_last_not_of(&aChar, aBeginIndex, 1);
  }

  //````````````````````````````````````````````````````````````````````````
  // Substr

  template <typename T>
  TL_I StringBase<T> StringBase<T>::substr( const tl_size& aBeginIndex,
                                            const tl_size& aNumCharsToCopy )
  {
    StringBase<T> temp;
    substr(aBeginIndex, aNumCharsToCopy, temp);
    return temp;
  }

  template <typename T>
  TL_I void StringBase<T>::substr( const tl_size& aBeginIndex,
                                   const tl_size& aNumCharsToCopy,
                                   StringBaseT& aSubStrOut )
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

  template <typename T>
  TL_I StringBase<T> StringBase<T>::to_upper()
  {
    StringBase<T> newString = *this;
    newString.make_upper();
    return newString;
  }
  template <typename T>
  TL_I void StringBase<T>::to_upper( StringBaseT& aStrOut )
  {
    aStrOut = *this;
    aStrOut.make_upper();
  }
  template <typename T>
  TL_I StringBase<T> StringBase<T>::to_lower()
  {
    StringBase<T> newString = *this;
    newString.make_lower();
    return newString;
  }
  template <typename T>
  TL_I void StringBase<T>::to_lower( StringBaseT& aStrOut )
  {
    aStrOut = *this;
    aStrOut.make_lower();
  }
  template <typename T>
  TL_I void StringBase<T>::make_upper()
  {
    tl_size sizeOfString = length();
    for (tl_size i = 0; i < sizeOfString; ++i)
    {
      *(m_begin + i) = CharToUpper(*(m_begin + i));
    }
  }
  template <typename T>
  TL_I void StringBase<T>::make_lower()
  {
    tl_size sizeOfString = length();
    for (tl_size i = 0; i < sizeOfString; ++i)
    {
      *(m_begin + i) = CharToLower(*(m_begin + i));
    }
  }

  //````````````````````````````````````````````````````````````````````````
  // Compare

  template <typename T>
  TL_I s32 StringBase<T>::compare( const StringBaseT& aStr ) const
  {
    return compare(0, length(), aStr.c_str(), 0, aStr.length());
  }
  template <typename T>
  TL_I s32 StringBase<T>::compare( const T* aCharStr ) const
  {
    return compare(0, length(), aCharStr, 0, StrLen(aCharStr));
  }
  template <typename T>
  TL_I s32 StringBase<T>::compare( const tl_size& aThisPos,
                                   const tl_size& aThisLength,
                                   const StringBaseT& aOtherStr ) const
  {
    TLOC_ASSERT_STRING(length() >= aThisPos + aThisLength,
      "Begin index + number of chars is out of range!");
    return DoCompare(m_begin + aThisPos, m_begin + aThisPos + aThisLength,
                     aOtherStr.begin(), aOtherStr.end());
  }
  template <typename T>
  TL_I s32 StringBase<T>::compare( const tl_size& aThisPos,
                                   const tl_size& aThisLength,
                                   const T* aOtherCharStr ) const
  {
    TLOC_ASSERT_STRING(length() >= aThisPos + aThisLength,
      "Begin index + number of chars is out of range!");

    return DoCompare(m_begin + aThisPos, m_begin + aThisPos + aThisLength,
                     aOtherCharStr, aOtherCharStr + StrLen(aOtherCharStr));
  }
  template <typename T>
  TL_I s32 StringBase<T>::compare( const tl_size& aThisPos,
                                   const tl_size& aThisLength,
                                   const StringBaseT& aOtherStr,
                                   const tl_size& aOtherPos,
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
  template <typename T>
  TL_I s32 StringBase<T>::compare( const tl_size& aThisPos,
                                   const tl_size& aThisNumChars,
                                   const T* aOtherCharStr,
                                   const tl_size& aOtherPos ) const
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

  template <typename T>
  TL_I T* StringBase<T>::DoAllocate( const tl_size& aSize )
  {
    TLOC_ASSERT_STRING(aSize > 1,
      "Allocation size must be greater than 1 for the null terminator");

    return (T*)TL_MALLOC(aSize * sizeof(T));
  }

  template <typename T>
  TL_I T* StringBase<T>::DoReAllocate( const tl_size& aSize )
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
  template <typename T>
  TL_I void StringBase<T>::DoReAllocateAndAdjust( const tl_size& aSize )
  {
    TLOC_ASSERT_STRING(aSize > capacity(),
      "This function can only increase the storage capacity! (passed size is "
      L"smaller than the current capacity)");

    const tl_size prevSize = size();
    const tl_size newCap   = aSize;

    T* ptr = DoReAllocate(aSize);

    TLOC_ASSERT_STRING(ptr != NULL, "Could not allocate/re-allocate!");

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
  template <typename T>
  TL_I void StringBase<T>::DoReAllocateAndAdjust()
  {
    const tl_size prevCap  = capacity();
    const tl_size newCap   = prevCap ? (2 * prevCap) : sm_defaultCapacity;

    DoReAllocateAndAdjust(newCap);
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
  TL_I void StringBase<T>::DoAllocateSelf( const tl_size& aSize )
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

  template <typename T>
  TL_I void StringBase<T>::DoDeallocateSelf()
  {
    if (m_begin != GetEmptyString(T()))
    {
      DoFree(m_begin);
    }
  }

  template <typename T>
  TL_I void StringBase<T>::RangeInitialize( const T* aPtrBegin )
  {
    TLOC_ASSERT_STRING(aPtrBegin, "aPtrBegin cannot be NULL!");

    RangeInitialize(aPtrBegin, aPtrBegin + StrLen(aPtrBegin));
  }

  template <typename T>
  TL_I void StringBase<T>::RangeInitialize( const T* aPtrBegin, const T* aPtrEnd )
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

  template <typename T>
  TL_I s32 StringBase<T>::DoCompare( const T* aBegin1, const T* aEnd1,
                                     const T* aBegin2, const T* aEnd2 ) const
  {
    TLOC_ASSERT_STRING_RANGE(aBegin1, aEnd1);
    TLOC_ASSERT_STRING_RANGE(aBegin2, aEnd2);

    const tl_size size1 = aEnd1 - aBegin1;
    const tl_size size2 = aEnd2 - aBegin2;
    const tl_size sizeMin = tlMin(size1, size2);

    return StrCmp(aBegin1, aBegin2, sizeMin);
  }

  //////////////////////////////////////////////////////////////////////////
  // Global functions

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
    return (tl_size)strlen(aCharStr); // According to EASTL, this should call intrinsics
  }

  template <typename T>
  TL_I s32 StrCmp( const T* aPtr1, const T* aPtr2 )
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

  template <typename T>
  TL_I s32 StrCmp( const T* aPtr1, const T* aPtr2, const tl_size& aNumChars )
  {
    for (tl_size i = aNumChars; i > 0; --i)
    {
      if (*aPtr1 != aPtr2)
      {
        return *aPtr1 > *aPtr2 ? 1 : -1;
      }
    }

    return 0;
  }

  template <>
  TL_I s32 StrCmp( const char8* aPtr1, const char8* aPtr2, const tl_size& aNumChars )
  {
    return memcmp(aPtr1, aPtr2, aNumChars);
  }

  template <typename T>
  TL_I T CharToLower( const T& aChar )
  {
    TLOC_ASSERT_STRING(aChar <= 0xFF,
      "Character is out of range for this function!");
    return (T)tolower((char8)aChar);
  }

  template <typename T>
  TL_I T CharToUpper( const T& aChar)
  {
    TLOC_ASSERT_STRING(aChar <= 0xFF,
      "Character is out of range for this function!");
    return (T)toupper((char8)aChar);
  }

  namespace priv
  {
    //------------------------------------------------------------------------
    // Windows specific
#if defined (TLOC_WIN32) || defined (TLOC_WIN64)
    TL_I s32 CharAsciiToWide(const char8* a_in, s32 a_inSize, char32* a_out, 
                             s32 a_outSize) 
    {
      return (s32)MultiByteToWideChar
        (CP_ACP, MB_PRECOMPOSED, a_in, (int)a_inSize, a_out, (int)a_outSize);
    }
    
    TL_I s32 CharWideToAscii(const char32* a_in, s32 a_inSize, char8* a_out, 
                             s32 a_outSize) 
    {
      int defaultUsed = 0;
      s32 retIndex = 0;
      retIndex = WideCharToMultiByte
        (CP_ACP, 0, a_in, (int)a_inSize, a_out, (int)a_outSize, 
         "?", &defaultUsed);
      
      TLOC_ASSERT_STRING(defaultUsed == 0, 
                         "Wide string has incompatible characters");
      return retIndex;
    }
#endif    

    //------------------------------------------------------------------------
    // Mac specific
    
#if defined (TLOC_OS_MAC) || defined (TLOC_OS_IPHONE)
    TL_I s32 CharAsciiToWide(const char8* a_in, s32 a_inSize, char32* a_out, 
                             s32 a_outSize) 
    {
      TLOC_UNUSED_4(a_in, a_inSize, a_out, a_outSize);
      return 0;
    }
    
    TL_I s32 CharWideToAscii(const char32* a_in, s32 a_inSize, char8* a_out, 
                             s32 a_outSize) 
    {
      TLOC_UNUSED_4(a_in, a_inSize, a_out, a_outSize);
      return 0;
    }
#endif
       
  }


  TL_I s32 CharAsciiToWide(const char8* a_in, s32 a_inSize, 
                               char32* a_out, s32 a_outSize)
  {
    return priv::CharAsciiToWide(a_in, a_inSize, a_out, a_outSize);
  }

  TL_I s32 CharWideToAscii(const char32* a_in, s32 a_inSize, 
                               char8* a_out, s32 a_outSize)
  {
    return priv::CharWideToAscii(a_in, a_inSize, a_out, a_outSize);
  }

  //````````````````````````````````````````````````````````````````````````
  // Global operators

  template <typename T>
  TL_I bool operator==( const StringBase<T>& a, const StringBase<T>& b )
  {
    const tl_size sizeA = a.size();
    return ( (sizeA == b.size()) && (memcmp(a.c_str(), b.c_str(),
             sizeA * sizeof(typename StringBase<T>::value_type)) == 0) );

  }

  template <typename T>
  TL_I bool operator==( const T* a, const StringBase<T>& b )
  {
    const tl_size charStrSize = StrLen(a);
    return ( (charStrSize == b.size()) && (memcmp(a, b.c_str(),
              charStrSize * sizeof(T)) == 0) );
  }

  template <typename T>
  TL_I bool operator==( const StringBase<T>& a, const T* b )
  {
    const tl_size charStrSize = StrLen(b);
    return ( (charStrSize == a.size()) && (memcmp(b, a.c_str(),
              charStrSize * sizeof(T)) == 0) );
  }

  template <typename T>
  TL_I bool operator!=( const StringBase<T>& a, const StringBase<T>& b )
  {
    return !(a == b);
  }

  template <typename T>
  TL_I bool operator!=( const T* a, const StringBase<T>& b )
  {
    return !(a == b);
  }

  template <typename T>
  TL_I bool operator!=( const StringBase<T>& a, const T* b )
  {
    return !(a == b);
  }

};};

#endif
