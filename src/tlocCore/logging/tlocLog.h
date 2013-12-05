#ifndef _TLOC_CORE_LOGGER_LOG_H_
#define _TLOC_CORE_LOGGER_LOG_H_

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/memory/tlocBufferArg.h>

namespace tloc { namespace core { namespace logging {

  namespace p_log
  {
    namespace severity
    {
      class Info    { static const tl_int s_value = 0; };
      class Debug   { static const tl_int s_value = 1; };
      class Warning { static const tl_int s_value = 2; };
      class Error   { static const tl_int s_value = 3; };
    };
  };

  template <typename T_Severity = p_log::severity::Info>
  class Log_TI
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_Severity, p_log::severity::Info>::value ||
       Loki::IsSameType<T_Severity, p_log::severity::Debug>::value ||
       Loki::IsSameType<T_Severity, p_log::severity::Warning>::value ||
       Loki::IsSameType<T_Severity, p_log::severity::Error>::value),
       Unsupported_severity_type);

  public:
    typedef Log_TI                          this_type;
    typedef f32                             time_type;
    typedef core_str::String                str_type;
    typedef T_Severity                      severity;

  public:
    Log_TI();
    Log_TI(const this_type& a_other);

    this_type& operator << (BufferArg a_string);
    this_type& operator << (tl_int    a_value);
    this_type& operator << (tl_long   a_value);
    this_type& operator << (tl_uint   a_value);
    this_type& operator << (tl_ulong  a_value);
    this_type& operator << (tl_float  a_value);
    this_type& operator << (tl_double a_value);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (str_type, GetFinalString, m_finalString);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(str_type, GetLog, m_finalString);
    TLOC_DECL_AND_DEF_GETTER(time_type, GetTime, m_time);
    TLOC_DECL_AND_DEF_GETTER(char*, GetFileName, m_fileName);
    TLOC_DECL_AND_DEF_GETTER(tl_ulong, GetLineNumber, m_lineNumber);

    this_type& operator=(this_type a_other);
    void       swap(this_type& a_other);

  protected:
    Log_TI(BufferArg a_fileName, const tl_ulong a_lineNumber);

    str_type          m_finalString;
    time_type         m_time;
    const char*       m_fileName;
    tl_ulong          m_lineNumber;
  };

  // -----------------------------------------------------------------------
  // swap

  template <typename T_Severity>
  void swap(Log_TI<T_Severity>& a, Log_TI<T_Severity>& b)
  {
    a.swap(b);
  }

};};};

#endif