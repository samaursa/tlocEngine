#ifndef TLOC_STRING_H
#define TLOC_STRING_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocCore/tlocFunctional.h>

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

namespace tloc { namespace core { namespace string {
  //------------------------------------------------------------------------
  // Ctor Helpers

  struct StringNoInitialize {};

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

    StringBase();
    StringBase(const this_type& aOther);
    StringBase(const this_type& aOther, size_type aPosition,
                    size_type aNumChars = npos);
    StringBase(const_pointer aPtr, size_type aNumChars);
    StringBase(const_pointer aPtr);
    StringBase(size_type aNumChars, value_type aChar);

    template <typename T_InputIterator>
    StringBase(const T_InputIterator aPtrBegin, const T_InputIterator aPtrEnd);

    StringBase(StringNoInitialize, size_type aN);

    ~StringBase();

    //------------------------------------------------------------------------
    // Iterators

    iterator        begin();
    const_iterator  begin() const;

    iterator        end();
    const_iterator  end() const;

    //------------------------------------------------------------------------
    // Element access

    const T&   operator [] (size_type aPos) const;
    T&         operator [] (size_type aPos);

    const T&   at(size_type aPos) const;
    T&         at(size_type aPos);

    //------------------------------------------------------------------------
    // Capacity

    tl_size    size() const;
    tl_size    length() const;
    tl_size    max_size() const;
    void       resize(const size_type& newSize);
    void       resize(const size_type& newSize, const value_type charToFill);
    tl_size    capacity() const;
    void       set_capacity(const size_type& newCapacity = npos);
    void       reserve(const size_type& newSize);
    void       clear();
    bool       empty();

    //------------------------------------------------------------------------
    // Modifiers

    this_type& operator+= (const this_type& aStr);
    this_type& operator+= (const_pointer aCharStr);
    this_type& operator+= (const_reference aChar);

    this_type& operator = (this_type aStr);
    this_type& operator = (const_pointer aCharStr);
    this_type& operator = (value_type aChar);

    void         swap(this_type& aX);

    //````````````````````````````````````````````````````````````````````````
    // Append

    this_type& append(const this_type& aStr);
    this_type& append(const this_type& aStr, const size_type& aPos,
                             const size_type& aNumChars);
    this_type& append(const_pointer aCharArray, const size_type& aNumChars);
    this_type& append(const_pointer aCharStr);
    this_type& append(const size_type& aNumChars, const_reference aChar);
    template <typename T_InputIterator>
    this_type& append(T_InputIterator aBegin, T_InputIterator aEnd);

    void         push_back(const T& aChar);

    //````````````````````````````````````````````````````````````````````````
    // Assign

    this_type& assign(const this_type& aStr);
    this_type& assign(const this_type& aStr, const tl_size& aPos,
                             const tl_size& aNumChars);
    this_type& assign(const_pointer aCharStr, const tl_size& aNumChars);
    this_type& assign(const_pointer aCharStr);
    this_type& assign(const tl_size& aNumChars, const T& aChar);
    template <typename T_InputIterator>
    this_type& assign(const T_InputIterator aBegin,
                             const T_InputIterator aEnd);

    //````````````````````````````````````````````````````````````````````````
    // Insert

    this_type& insert(tl_size aIndex, const this_type& aStr);
    this_type& insert(tl_size aIndexDestination, const this_type& aStr,
                           tl_size aIndexSource, tl_size aNumChars);
    this_type& insert(tl_size aIndex, const_pointer aCharArray, tl_size aNumChars);
    this_type& insert(tl_size aIndex, const_pointer aCharStr);
    this_type& insert(tl_size aIndex, tl_size aNumChars, T aChar);
    iterator   insert(const_iterator aPos, const T& aChar);
    void       insert(const_iterator aPos, tl_size aNumChars, T aChar);

    template <typename T_InputIterator>
    void       insert(const_iterator aPos, T_InputIterator aBegin,
                      T_InputIterator aEnd);

    //````````````````````````````````````````````````````````````````````````
    // Replace

    this_type& erase(const tl_size& aPos = 0,
                     const tl_size& aNumChars = npos);
    iterator   erase(iterator aPos);
    iterator   erase(iterator aFirst, iterator aLast);

    //````````````````````````````````````````````````````````````````````````
    // Replace

    this_type& replace(tl_size aPos, tl_size aNumCharsToReplace,
                       const this_type& aStr);
    this_type& replace(iterator aDestBegin, iterator aDestEnd,
                       const this_type& aStr);
    this_type& replace(tl_size aDestPos, tl_size aNumCharsToReplace,
                       const this_type& aStr, tl_size aSourcePos,
                       tl_size aNumCharsToCopy);

    this_type& replace(tl_size aPos, tl_size aNumCharsToReplace,
                       const_pointer aCharArray, tl_size aNumCharsToCopy);
    this_type& replace(iterator aDestBegin, iterator aDestEnd,
                       const_pointer aCharArray, tl_size aNumCharsToCopy);
    this_type& replace(tl_size aPos, tl_size aNumCharsToReplace,
                       const_pointer aCharStr);
    this_type& replace(iterator aDestBegin, iterator aDestEnd,
                       const_pointer aCharStr);

    this_type& replace(tl_size aPos, tl_size aNumCharsToReplace,
                       tl_size aNumOfCharsToCopy, const T aChar);
    this_type& replace(iterator aDestBegin, iterator aDestEnd,
                       tl_size aNumOfCharsToCopy, const T aChar);

    template <typename T_InputIterator>
    this_type& replace(iterator aDestBegin, iterator aDestEnd,
                       T_InputIterator aBegin, T_InputIterator aEnd);

    //````````````````````````````````````````````````````````````````````````
    // Lower and Upper case

    this_type   to_upper();
    void        to_upper(this_type& aStrOut);

    this_type   to_lower();
    void        to_lower(this_type& aStrOut);

    void        make_upper();
    void        make_lower();

    //------------------------------------------------------------------------
    // String Operations

    const_pointer     c_str();
    const_pointer     c_str() const;
    const_pointer     data();
    const_pointer     data() const;
    tl_size           copy(pointer aDestArray, const tl_size& aNumCharsToCopy,
                           const tl_size& aBegin = 0);

    //````````````````````````````````````````````````````````````````````````
    // Find functions

    tl_size      find(const this_type& aStrToCompare,
                      const tl_size& aBeginIndex = 0) const;
    tl_size      find(const_pointer aCharStr, const tl_size& aBeginIndex,
                      const tl_size& aNumCharsToCompare) const;
    tl_size      find(const_pointer aCharStr,
                      const tl_size& aBeginIndex = 0) const;
    tl_size      find(T aChar, const tl_size& aBeginIndex = 0) const;

    tl_size      rfind(const this_type& aStrToCompare,
                       const tl_size& aBeginIndex = 0) const;
    tl_size      rfind(const_pointer aCharStr, const tl_size& aBeginIndex,
                       const tl_size& aNumCharsToCompare) const;
    tl_size      rfind(const_pointer aCharStr,
                       const tl_size& aBeginIndex = 0) const;
    tl_size      rfind(T aChar, const tl_size& aBeginIndex = 0) const;

    tl_size      find_first_of(const this_type& aStrToCompare,
                               const tl_size& aBeginIndex = 0) const;
    tl_size      find_first_of(const_pointer aCharStr, const tl_size& aBeginIndex,
                               const tl_size& aNumCharsToCompare) const;
    tl_size      find_first_of(const_pointer aCharStr,
                               const tl_size& aBeginIndex = 0) const;
    tl_size      find_first_of(T aChar, const tl_size& aBeginIndex = 0) const;

    tl_size      find_last_of(const this_type& aStrToCompare,
                              const tl_size& aBeginIndex = 0) const;
    tl_size      find_last_of(const_pointer aCharStr, const tl_size& aBeginIndex,
                              const tl_size& aNumCharsToCompare) const;
    tl_size      find_last_of(const_pointer aCharStr,
                              const tl_size& aBeginIndex = 0) const;
    tl_size      find_last_of(T aChar, const tl_size& aBeginIndex = 0) const;

    tl_size      find_first_not_of(const this_type& aStrToCompare,
                                   tl_size aBeginIndex = 0) const;
    tl_size      find_first_not_of(const_pointer aCharStr,
                                   const tl_size& aBeginIndex,
                                   tl_size aNumCharsToCompare) const;
    tl_size      find_first_not_of(const_pointer aCharStr,
                                   const tl_size& aBeginIndex = 0) const;
    tl_size      find_first_not_of(T aChar, const tl_size& aBeginIndex = 0) const;

    tl_size      find_last_not_of(const this_type& aStrToCompare,
                                  tl_size aBeginIndex = 0) const;
    tl_size      find_last_not_of(const_pointer aCharStr,
                                  const tl_size& aBeginIndex,
                                  tl_size aNumCharsToCompare) const;
    tl_size      find_last_not_of(const_pointer aCharStr,
                                  const tl_size& aBeginIndex = 0) const;
    tl_size      find_last_not_of(T aChar,
                                  const tl_size& aBeginIndex = 0) const;

    //````````````````````````````````````````````````````````````````````````
    // Substring

    this_type substr(tl_size aBeginIndex,
                     tl_size aNumCharsToCopy = npos) const;
    void      substr(tl_size aBeginIndex,
                     tl_size aNumCharsToCopy,
                     this_type&   aSubStrOut) const;

    //````````````````````````````````````````````````````````````````````````
    // Compare

    tl_int compare (const this_type& aStr ) const;
    tl_int compare (const_pointer aCharStr ) const;
    tl_int compare (const tl_size& aThisPos, const tl_size& aThisLength,
                    const this_type& aOtherStr ) const;
    tl_int compare (const tl_size& aThisPos, const tl_size& aThisLength,
                    const_pointer aOtherStr) const;
    tl_int compare (const tl_size& aThisPos, const tl_size& aThisLength,
                    const this_type& aOtherStr, const tl_size& aOtherPos,
                    const tl_size& aOtherLength ) const;
    tl_int compare (const tl_size& aThisPos, const tl_size& aThisLength,
                    const_pointer aOtherCharStr,
                    const tl_size& aOtherLength) const;

  protected:
    pointer  m_begin;
    pointer  m_end;
    pointer  m_capacity;

    //------------------------------------------------------------------------
    // Internal functions

    pointer  DoAllocate(const size_type& aSize);
    pointer  DoReAllocate(const size_type& aSize);
    void     DoReAllocateAndAdjust(const size_type& aSize);
    void     DoReAllocateAndAdjust();
    void     DoFree(pointer aPtr);

    void     DoAllocateSelf();
    void     DoAllocateSelf(const size_type& aSize);
    void     DoDeallocateSelf();

    void     RangeInitialize(const_pointer aPtrBegin, const_pointer aPtrEnd);
    void     RangeInitialize(const_pointer aPtrBegin);

    tl_int   DoCompare(const_pointer aBegin1, const_pointer aEnd1,
                       const_pointer aBegin2, const_pointer aEnd2) const;

    //------------------------------------------------------------------------
    // Constants

    static const tl_size m_MaxSize;
    static const tl_size sm_defaultCapacity;
  };

  template <typename T>
  const tl_size StringBase<T>::npos = (tl_size) - 1;

  // -----------------------------------------------------------------------
  // typedefs

  typedef StringBase<char8>   String;
  typedef StringBase<char32>  StringW;

  //////////////////////////////////////////////////////////////////////////
  // operator+ global

  template <typename T>
  StringBase<T>
    operator+ (const StringBase<T>& a_lhs, const StringBase<T>& a_rhs);

  template <typename T>
  StringBase<T>
    operator+ (const T* a_lhs, const StringBase<T>& a_rhs);

  template <typename T>
  StringBase<T>
    operator+ (T a_lhs, const StringBase<T>& a_rhs);

  template <typename T>
  StringBase<T>
    operator+ (const StringBase<T>& a_lhs, const T* a_rhs);

  template <typename T>
  StringBase<T>
    operator+ (const StringBase<T>& a_lhs, T a_rhs);

  //////////////////////////////////////////////////////////////////////////
  // Global functions

  template <typename T>
  const T* StrChr(const T* a_string, T a_charToLocate);

  template <>
  const char8* StrChr(const char8* a_string, char a_charToLocate);

  template <typename T>
  T* StrChr(T* a_string, T a_charToLocate);

  template <>
  char8* StrChr(char8* a_string, char a_charToLocate);

  template <typename T>
  const T* StrRChr(const T* a_string, T a_charToLocate);

  template <>
  const char8* StrRChr(const char8* a_string, char a_charToLocate);

  template <typename T>
  T* StrRChr(T* a_string, T a_charToLocate);

  template <>
  char8* StrRChr(char8* a_string, char a_charToLocate);

  template <typename T>
  tl_size
    StrLen(const T* aCharStr);

  template <>
  tl_size
    StrLen(const char8* aCharStr);

  template <typename T>
  tl_int
    StrCmp(const T* aPtr1, const T* aPtr2);
  template <>
  tl_int
    StrCmp(const char8* a_ptr1, const char8* a_ptr2);
  template <typename T>
  tl_int
    StrCmp(const T* aPtr1, const T* aPtr2, const tl_size& aNumChars);
  template <>
  tl_int
    StrCmp(const char8* aPtr1, const char8* aPtr2, const tl_size& aNumChars);

  template <typename T>
  T
    CharToLower(const T& aChar);

  template <typename T>
  T
    CharToUpper(const T& aChar);
  tl_size
    CharAsciiToWide(char32* a_out, const char8* a_in, tl_int a_inSize);
  tl_size
    CharWideToAscii(char8* a_out, const char32* a_in, tl_int a_inSize);

  template <typename T, typename T_StringContainer>
  void
    Tokenize(const T* a_string, T a_delim, T_StringContainer& a_out);

  template <typename T, typename T_StringContainer>
  void
    Tokenize(const T* a_string, const T* a_delims, T_StringContainer& a_out);

  bool
    IsCntrl(char8 a_char);

  bool
    IsBlank(char8 a_char);

  bool
    IsSpace(char8 a_char);

  bool
    IsUpper(char8 a_char);

  bool
    IsLower(char8 a_char);

  bool
    IsAlpha(char8 a_char);

  bool
    IsDigit(char8 a_char);

  bool
    IsNumber(const char8* a_char);

  bool
    IsRealNumber(const char8* a_char);

  bool
    IsNegNumber(const char8* a_char);

  bool
    IsNegRealNumber(const char8* a_char);

  bool
    IsPosNumber(const char8* a_char);

  bool
    IsPosRealNumber(const char8* a_char);

  bool
    IsXDigit(char8 a_char);

  bool
    IsAlNum(char8 a_char);

  bool
    IsPunct(char8 a_char);

  //````````````````````````````````````````````````````````````````````````
  // Global operators (not providing <, > as they can be confusing/error-prone
  // use StrCmp() for those operations

  template <typename T>
  bool
    operator==(const StringBase<T>& a, const StringBase<T>& b);

  template <typename T>
  bool
    operator==(const T* a, const StringBase<T>& b);

  template <typename T>
  bool
    operator==(const StringBase<T>& a, const T* b);

  template <typename T>
  bool
    operator!=(const StringBase<T>& a, const StringBase<T>& b);

  template <typename T>
  bool
    operator!=(const T* a, const StringBase<T>& b);

  template <typename T>
  bool
    operator!=(const StringBase<T>& a, const T* b);

  String
    Format(const char8* a_string, ...);

  //------------------------------------------------------------------------
  // global vars

  extern char8 g_controls[];
  extern String g_controlsStr;

  extern char8 g_blank[];
  extern String g_blankStr;

  extern char8 g_space[];
  extern String g_spaceStr;

  extern char8 g_upper[];
  extern String g_upperStr;

  extern char8 g_lower[];
  extern String g_lowerStr;

  extern char8 g_alpha[];
  extern String g_alphaStr;

  extern char8 g_digit[];
  extern String g_digitStr;

  extern char8 g_xdigit[];
  extern String g_xdigitStr;

  extern char8 g_alnum[];
  extern String g_alnumStr;

  extern char8 g_punct[];
  extern String g_punctStr;

};};};

namespace tloc { namespace core {

  //------------------------------------------------------------------------
  // swap

  template <typename T>
  void swap(core_str::StringBase<T>& a, core_str::StringBase<T>& b)
  { a.swap(b); }

  // -----------------------------------------------------------------------
  // binary functions for strings

  template <>
  struct equal_to<const char8*>
  {
    bool operator()(const char8* a_x, const char8* a_y) const
    { return core_str::StrCmp(a_x, a_y) == 0; }
  };

  template <>
  struct not_equal_to<const char8*>
  {
    bool operator()(const char8* a_x, const char8* a_y) const
    { return core_str::StrCmp(a_x, a_y) != 0; }
  };

  template <>
  struct greater<const char8*>
  {
    bool operator()(const char8* a_x, const char8* a_y) const
    { return core_str::StrCmp(a_x, a_y) > 0; }
  };

  template <>
  struct less<const char8*>
  {
    bool operator()(const char8* a_x, const char8* a_y) const
    { return core_str::StrCmp(a_x, a_y) < 0; }
  };

  template <>
  struct greater_equal<const char8*>
  {
    bool operator()(const char8* a_x, const char8* a_y) const
    { return core_str::StrCmp(a_x, a_y) >= 0; }
  };

  template <>
  struct less_equal<const char8*>
  {
    bool operator()(const char8* a_x, const char8* a_y) const
    { return core_str::StrCmp(a_x, a_y) <= 0; }
  };

  // -----------------------------------------------------------------------
  // same as above, for char32

  template <>
  struct equal_to<const char32*>
  {
    bool operator()(const char32* a_x, const char32* a_y) const
    { return core_str::StrCmp(a_x, a_y) == 0; }
  };

  template <>
  struct not_equal_to<const char32*>
  {
    bool operator()(const char32* a_x, const char32* a_y) const
    { return core_str::StrCmp(a_x, a_y) != 0; }
  };

  template <>
  struct greater<const char32*>
  {
    bool operator()(const char32* a_x, const char32* a_y) const
    { return core_str::StrCmp(a_x, a_y) > 0; }
  };

  template <>
  struct less<const char32*>
  {
    bool operator()(const char32* a_x, const char32* a_y) const
    { return core_str::StrCmp(a_x, a_y) < 0; }
  };

  template <>
  struct greater_equal<const char32*>
  {
    bool operator()(const char32* a_x, const char32* a_y) const
    { return core_str::StrCmp(a_x, a_y) >= 0; }
  };

  template <>
  struct less_equal<const char32*>
  {
    bool operator()(const char32* a_x, const char32* a_y) const
    { return core_str::StrCmp(a_x, a_y) <= 0; }
  };

};};

#endif
