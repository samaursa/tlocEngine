#include "tlocBufferArg.h"

#include <tlocCore/string/tlocString.h>

namespace tloc { namespace core { namespace memory {

  BufferArg::size_type const s_maximumValidBufferSize = 2048;

  BufferArg::BufferArg(const char* a_buffer)
    : m_buffer(a_buffer), m_end(nullptr)
  {
  }

  BufferArg::BufferArg(const char* a_buffer, size_type a_end)
    : m_buffer(a_buffer), m_end(a_buffer + a_end)
  {
  }

  template <typename T_String>
  BufferArg::BufferArg(const T_String& a_string)
    : m_buffer(a_string.c_str()), m_end(a_string.end())
  {
  }

  bool BufferArg::IsValid() const
  {
    return IsValid(s_maximumValidBufferSize);
  }

  bool BufferArg::IsValid(size_type a_maximumSize) const
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

  const char BufferArg::operator [](tl_int a_index) const
  {
    TLOC_ASSERT_LOW_LEVEL(IsValid(), "Index out of bounds!");
    return m_buffer[a_index];
  }

  const char* BufferArg::GetPtr() const
  {
    return m_buffer;
  }

  BufferArg::size_type BufferArg::GetSize() const
  {
    return m_end - m_buffer;
  }

  BufferArg::size_type BufferArg::GetMaxAllowedBuffSize()
  {
    return s_maximumValidBufferSize;
  }

  //------------------------------------------------------------------------
  // Explicit Instantiations

  template BufferArg::BufferArg(const string::String& a_string);

};};};