#include "tlocLog.h"

#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/time/tlocTime.h>
#include <tlocCore/tlocAlgorithms.inl.h>

namespace {

  static const tloc::tl_int   g_initialBufferSize = 128;
  static const tloc::tl_ulong s_invalidLoggerLineNumber = 0;

};

namespace tloc { namespace core { namespace logging {

  // ///////////////////////////////////////////////////////////////////////
  // BaseLog

  BaseLog_I::
    BaseLog_I()
    : m_fileName("Invalid log")
    , m_lineNumber(s_invalidLoggerLineNumber)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BaseLog_I::
    BaseLog_I(const this_type& a_other)
    : m_finalString(a_other.m_finalString)
    , m_time(a_other.m_time)
    , m_fileName(a_other.m_fileName)
    , m_lineNumber(a_other.m_lineNumber)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BaseLog_I::
    BaseLog_I(BufferArg a_fileName, const tl_ulong a_lineNumber)
    : m_fileName(a_fileName)
    , m_lineNumber(a_lineNumber)
  {
    m_finalString.reserve(g_initialBufferSize);

    using namespace core_time;
    m_time = core_utils::CastNumber<time_type>
      (GetProgramTime().ElapsedSeconds());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BaseLog_I::this_type&
    BaseLog_I::
    operator<<(BufferArg a_string)
  {
    m_finalString += a_string;
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BaseLog_I::this_type&
    BaseLog_I::
    operator<<(tl_int a_value)
  {
    m_finalString += core_str::Format("%i", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BaseLog_I::this_type&
    BaseLog_I::
    operator<<(tl_long a_value)
  {
    m_finalString += core_str::Format("%il", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BaseLog_I::this_type&
    BaseLog_I::
    operator<<(tl_uint a_value)
  {
    m_finalString += core_str::Format("%u", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BaseLog_I::this_type&
    BaseLog_I::
    operator<<(tl_ulong a_value)
  {
    m_finalString += core_str::Format("%ul", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BaseLog_I::this_type&
    BaseLog_I::
    operator<<(tl_float a_value)
  {
    m_finalString += core_str::Format("%f", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BaseLog_I::this_type&
    BaseLog_I::
    operator<<(tl_double a_value)
  {
    m_finalString += core_str::Format("%f", a_value);
    return *this;
  }


  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BaseLog_I::this_type&
    BaseLog_I::
    operator=(this_type a_other)
  {
    swap(a_other);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    BaseLog_I::
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

  void swap(BaseLog_I& a, BaseLog_I& b)
  { a.swap(b); }


};};};