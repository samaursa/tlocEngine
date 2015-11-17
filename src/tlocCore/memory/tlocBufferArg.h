#ifndef TLOC_CORE_MEMORY_BUFFER_ARG_H
#define TLOC_CORE_MEMORY_BUFFER_ARG_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <string>

namespace tloc { namespace core { namespace memory {

  ///-------------------------------------------------------------------------
  /// @brief Meant to be used only as a function argument.
  ///-------------------------------------------------------------------------
  template <typename T_Char = char8>
  class buffer_arg_t
  {
    TLOC_STATIC_ASSERT_SUPPORTED(T_Char, char8, char32);

  public:
    typedef T_Char                        value_type;
    typedef value_type                    char_type;
    typedef tl_size                       size_type;

    typedef std::basic_string<char_type>  string_type;

  public:

    ///-------------------------------------------------------------------------
    /// @brief
    /// Assumes a_buffer is NULL terminated. Call IsValid() to check if
    /// it is.
    ///-------------------------------------------------------------------------
    buffer_arg_t(const char_type* a_buffer);
    buffer_arg_t(const char_type* a_buffer, size_type a_end);

    buffer_arg_t(const string_type& a_string);

    ///-------------------------------------------------------------------------
    /// @brief
    /// A buffer is valid if doesn't exceed a_maximumValidBufferSize iff
    /// m_size == 0. If m_size != 0, buffer is always valid.
    ///-------------------------------------------------------------------------
    bool is_valid() const;

    ///-------------------------------------------------------------------------
    /// @brief Same as IsValid() except with a user specified maximum size
    ///-------------------------------------------------------------------------
    bool is_valid(size_type a_maximumSize) const;

    const char_type operator[](tl_int a_index) const;

    operator char_type const *() const;

    const char_type*  get_ptr() const;
    size_type         get_size() const;

    static size_type   get_max_allowed_buff_size();

  private:
    const char_type* m_buffer;
    const char_type* m_end;
  };

};};};

namespace tloc
{
  typedef core::memory::buffer_arg_t<>       buffer_arg;
  typedef core::memory::buffer_arg_t<char32> BufferArgW;
};

namespace tloc { namespace core { namespace memory {

  // Added these overloaded functions because implicit template type conversion
  // is not allowed for template functions

  TL_I tl_size strlen(buffer_arg a_charBuff)
  { return std::strlen(a_charBuff.get_ptr()); }

  template <typename T_Char>
  tl_int strcmp(const T_Char* a_ptr, buffer_arg a_charBuff)
  { return std::strcmp(a_ptr, a_charBuff.get_ptr()); }

  template <typename T_Char>
  tl_int strcmp(buffer_arg a_charBuff, const T_Char* a_ptr)
  { return std::strcmp(a_charBuff.get_ptr(), a_ptr); }

  TL_I tl_int strcmp(buffer_arg a_charBuff1, buffer_arg a_charBuff2)
  { return std::strcmp(a_charBuff1.get_ptr(), a_charBuff2.get_ptr()); }

};};};


#endif