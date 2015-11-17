#include "tlocLog.h"

#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/time/tlocTime.h>
#include <tlocCore/tlocAlgorithms.inl.h>

namespace {

  static const tl_int   g_initialBufferSize = 128;
  static const tl_ulong s_invalidLoggerLineNumber = 0;

};

namespace tloc { namespace core { namespace logging {

  const char* Log_I::s_severityStr[Log_I::k_count] =
  {
    "Info",
    "Success",
    "Debug",
    "Warning",
    "Error"
  };

  const char* Log_I::s_severityStrShort[Log_I::k_count] =
  {
    "I",
    "S",
    "D",
    "W",
    "E"
  };

  // ///////////////////////////////////////////////////////////////////////
  // BaseLog

  Log_I::
    Log_I()
    : m_fileName("Invalid log")
    , m_lineNumber(s_invalidLoggerLineNumber)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::
    Log_I(const this_type& a_other)
    : m_finalString(a_other.m_finalString)
    , m_time(a_other.m_time)
    , m_fileName(a_other.m_fileName)
    , m_lineNumber(a_other.m_lineNumber)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::
    Log_I(severity_type a_severity, buffer_arg a_fileName,
          const tl_ulong a_lineNumber)
    : m_fileName(a_fileName)
    , m_lineNumber(a_lineNumber)
    , m_severity(a_severity)
  {
    m_finalString.reserve(g_initialBufferSize);

    using namespace core_time;
    m_time = core_utils::cast_number<time_type>
      (GetProgramTime().ElapsedSeconds());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type_cref
    Log_I::
    operator<<(buffer_arg a_string) const
  {
    m_finalString += a_string;
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type_cref
    Log_I::
    operator<<(BufferArgW a_string) const
  {
    m_finalString += core_str::CharWideToAscii(a_string.GetPtr());
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type_cref
    Log_I::
    operator<<(char8 a_char) const
  {
    m_finalString += a_char;
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type_cref
    Log_I::
    operator<<(char32 a_wchar) const
  {
    m_finalString += core_str::CharWideToAscii(a_wchar);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type_cref
    Log_I::
    operator<<(tl_int a_value) const
  {
    m_finalString += core_str::Format("%i", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type_cref
    Log_I::
    operator<<(tl_long a_value) const
  {
    m_finalString += core_str::Format("%il", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type_cref
    Log_I::
    operator<<(tl_uint a_value) const
  {
    m_finalString += core_str::Format("%u", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type_cref
    Log_I::
    operator<<(tl_ulong a_value) const
  {
    m_finalString += core_str::Format("%ul", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type_cref
    Log_I::
    operator<<(tl_float a_value) const
  {
    m_finalString += core_str::Format("%f", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type_cref
    Log_I::
    operator<<(tl_double a_value) const
  {
    m_finalString += core_str::Format("%f", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type_cref
    Log_I::
    operator<<(core_utils::MemoryAddress a_memAddress) const
  {
    m_finalString += core_str::Format("%p", a_memAddress);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type_cref
    Log_I::
    put(char8 a_value) const
  { return operator << (a_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type_cref
    Log_I::
    write(const char8* a_string, tl_int a_size) const
  { 
    m_finalString.append(a_string, a_size);
    return *this; 
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log_I::this_type&
    Log_I::
    operator=(this_type a_other)
  {
    swap(a_other);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Log_I::
    swap(this_type& a_other)
  {
    using core::swap;

    swap(m_finalString, a_other.m_finalString);
    swap(m_time, a_other.m_time);
    swap(m_fileName, a_other.m_fileName);
    swap(m_lineNumber, a_other.m_lineNumber);
  }

  // -----------------------------------------------------------------------
  // swap

  void swap(Log_I& a, Log_I& b)
  { a.swap(b); }

};};};