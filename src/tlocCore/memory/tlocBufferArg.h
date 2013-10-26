#ifndef TLOC_CORE_MEMORY_BUFFER_ARG_H
#define TLOC_CORE_MEMORY_BUFFER_ARG_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/string/tlocString.h>

namespace tloc { namespace core { namespace memory {

  ///-------------------------------------------------------------------------
  /// @brief Meant to be used only as a function argument.
  ///-------------------------------------------------------------------------
  template <typename T_Char = char8>
  class BufferArg_T
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_Char, char8>::value ||
      Loki::IsSameType<T_Char, char32>::value),
      Buffer_arg_only_supports_char_types);

  public:
    typedef T_Char            value_type;
    typedef value_type        char_type;
    typedef tl_size           size_type;

    typedef string::StringBase<char_type> string_type;

  public:

    ///-------------------------------------------------------------------------
    /// @brief
    /// Assumes a_buffer is NULL terminated. Call IsValid() to check if
    /// it is.
    ///-------------------------------------------------------------------------
    BufferArg_T(const char_type* a_buffer);
    BufferArg_T(const char_type* a_buffer, size_type a_end);

    BufferArg_T(const string_type& a_string);

    ///-------------------------------------------------------------------------
    /// @brief
    /// A buffer is valid if doesn't exceed a_maximumValidBufferSize iff
    /// m_size == 0. If m_size != 0, buffer is always valid.
    ///-------------------------------------------------------------------------
    bool IsValid() const;

    ///-------------------------------------------------------------------------
    /// @brief Same as IsValid() except with a user specified maximum size
    ///-------------------------------------------------------------------------
    bool IsValid(size_type a_maximumSize) const;

    const char_type operator[](tl_int a_index) const;

    operator char_type const *() const;

    const char_type*  GetPtr() const;
    size_type         GetSize() const;

    static size_type   GetMaxAllowedBuffSize();

  private:
    const char_type* m_buffer;
    const char_type* m_end;
  };

};};};

namespace tloc
{
  typedef core::memory::BufferArg_T<>       BufferArg;
  typedef core::memory::BufferArg_T<char32> BufferArgW;
};

namespace tloc { namespace core { namespace memory {

  // Added these overloaded functions because implicit template type conversion
  // is not allowed for template functions

  TL_I tl_size StrLen(BufferArg a_charBuff)
  { return core_str::StrLen(a_charBuff.GetPtr()); }

  template <typename T_Char>
  tl_int StrCmp(const T_Char* a_ptr, BufferArg a_charBuff)
  { return core_str::StrCmp(a_ptr, a_charBuff.GetPtr()); }

  template <typename T_Char>
  tl_int StrCmp(BufferArg a_charBuff, const T_Char* a_ptr)
  { return core_str::StrCmp(a_charBuff.GetPtr(), a_ptr); }

  TL_I tl_int StrCmp(BufferArg a_charBuff1, BufferArg a_charBuff2)
  { return core_str::StrCmp(a_charBuff1.GetPtr(), a_charBuff2.GetPtr()); }

};};};


#endif