#include "tlocBufferArg.h"

#include <tlocCore/tlocAssert.h>

namespace tloc { namespace core { namespace memory {

#define TLOC_BUFFER_ARG_TEMPS   typename T_Char
#define TLOC_BUFFER_ARG_PARAMS  T_Char
#define TLOC_BUFFER_ARG_TYPE    typename BufferArg_T<TLOC_BUFFER_ARG_PARAMS>

  tloc::buffer_arg::size_type const s_maximumValidBufferSize = 2048;

  // ///////////////////////////////////////////////////////////////////////
  // BufferArg

  template <TLOC_BUFFER_ARG_TEMPS>
  buffer_arg_t<TLOC_BUFFER_ARG_PARAMS>::
    buffer_arg_t(const char_type* a_buffer)
    : m_buffer(a_buffer), m_end(nullptr)
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  buffer_arg_t<TLOC_BUFFER_ARG_PARAMS>::
    buffer_arg_t(const char_type* a_buffer, size_type a_end)
    : m_buffer(a_buffer), m_end(a_buffer + a_end)
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  buffer_arg_t<TLOC_BUFFER_ARG_PARAMS>::
    buffer_arg_t(const string_type& a_string)
    : m_buffer(a_string.begin()), m_end(a_string.end())
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  bool
    buffer_arg_t<TLOC_BUFFER_ARG_PARAMS>::
    is_valid() const
  {
    return is_valid(s_maximumValidBufferSize);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  bool
    buffer_arg_t<TLOC_BUFFER_ARG_PARAMS>::
    is_valid(size_type a_maximumSize) const
  {
    if (m_end)
    { return true; }

    for (size_type i = 0; i < a_maximumSize; ++i)
    {
      if (m_buffer[i] == '\0')
      { return true; }
    }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  buffer_arg_t<TLOC_BUFFER_ARG_PARAMS>::
    operator const TLOC_BUFFER_ARG_TYPE::char_type *() const
  {
    return m_buffer;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  const TLOC_BUFFER_ARG_TYPE::char_type
    buffer_arg_t<TLOC_BUFFER_ARG_PARAMS>::
    operator [](tl_int a_index) const
  {
    TLOC_ASSERT_LOW_LEVEL(is_valid(), "Index out of bounds!");
    return m_buffer[a_index];
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  const TLOC_BUFFER_ARG_TYPE::char_type*
    buffer_arg_t<TLOC_BUFFER_ARG_PARAMS>::
    get_ptr() const
  {
    TLOC_ASSERT(m_end == TLOC_NULL || *m_end == '\0', "BufferArg::m_end is not NULL nor is it '\0'"); // if m_end is not NULL, then GetPtr() is undefined
    return m_buffer;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  TLOC_BUFFER_ARG_TYPE::size_type
    buffer_arg_t<TLOC_BUFFER_ARG_PARAMS>::
    get_size() const
  {
    return m_end - m_buffer;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  TLOC_BUFFER_ARG_TYPE::size_type
    buffer_arg_t<TLOC_BUFFER_ARG_PARAMS>::
    get_max_allowed_buff_size()
  {
    return s_maximumValidBufferSize;
  }

  //------------------------------------------------------------------------
  // Explicit Instantiations

  template class buffer_arg_t<char8>;
  template class buffer_arg_t<char32>;
};};};