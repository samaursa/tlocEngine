#include "tlocBufferArg.h"

#include <tlocCore/tlocAssert.h>

namespace tloc { namespace core { namespace memory {

#define TLOC_BUFFER_ARG_TEMPS   typename T_Char
#define TLOC_BUFFER_ARG_PARAMS  T_Char
#define TLOC_BUFFER_ARG_TYPE    typename BufferArg_T<TLOC_BUFFER_ARG_PARAMS>

  tloc::BufferArg::size_type const s_maximumValidBufferSize = 2048;

  // ///////////////////////////////////////////////////////////////////////
  // BufferArg

  template <TLOC_BUFFER_ARG_TEMPS>
  BufferArg_T<TLOC_BUFFER_ARG_PARAMS>::
    BufferArg_T(const char_type* a_buffer)
    : m_buffer(a_buffer), m_end(nullptr)
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  BufferArg_T<TLOC_BUFFER_ARG_PARAMS>::
    BufferArg_T(const char_type* a_buffer, size_type a_end)
    : m_buffer(a_buffer), m_end(a_buffer + a_end)
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  BufferArg_T<TLOC_BUFFER_ARG_PARAMS>::
    BufferArg_T(const string_type& a_string)
    : m_buffer(a_string.begin()), m_end(a_string.end())
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  bool
    BufferArg_T<TLOC_BUFFER_ARG_PARAMS>::
    IsValid() const
  {
    return IsValid(s_maximumValidBufferSize);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  bool
    BufferArg_T<TLOC_BUFFER_ARG_PARAMS>::
    IsValid(size_type a_maximumSize) const
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
  BufferArg_T<TLOC_BUFFER_ARG_PARAMS>::
    operator const TLOC_BUFFER_ARG_TYPE::char_type *() const
  {
    return m_buffer;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  const TLOC_BUFFER_ARG_TYPE::char_type
    BufferArg_T<TLOC_BUFFER_ARG_PARAMS>::
    operator [](tl_int a_index) const
  {
    TLOC_ASSERT_LOW_LEVEL(IsValid(), "Index out of bounds!");
    return m_buffer[a_index];
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  const TLOC_BUFFER_ARG_TYPE::char_type*
    BufferArg_T<TLOC_BUFFER_ARG_PARAMS>::
    GetPtr() const
  {
    TLOC_ASSERT(m_end == TLOC_NULL || *m_end == '\0', "BufferArg::m_end is not NULL nor is it '\0'"); // if m_end is not NULL, then GetPtr() is undefined
    return m_buffer;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  TLOC_BUFFER_ARG_TYPE::size_type
    BufferArg_T<TLOC_BUFFER_ARG_PARAMS>::
    GetSize() const
  {
    return m_end - m_buffer;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_BUFFER_ARG_TEMPS>
  TLOC_BUFFER_ARG_TYPE::size_type
    BufferArg_T<TLOC_BUFFER_ARG_PARAMS>::
    GetMaxAllowedBuffSize()
  {
    return s_maximumValidBufferSize;
  }

  //------------------------------------------------------------------------
  // Explicit Instantiations

  template class BufferArg_T<char8>;
  template class BufferArg_T<char32>;
};};};