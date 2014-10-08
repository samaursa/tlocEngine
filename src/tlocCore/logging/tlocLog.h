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
      struct Info    { static const tl_int s_value = 0; };
      struct Success { static const tl_int s_value = 1; };
      struct Debug   { static const tl_int s_value = 2; };
      struct Warning { static const tl_int s_value = 3; };
      struct Error   { static const tl_int s_value = 4; };
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Log_I

  class Log_I
  {
  public:
    typedef Log_I                                   this_type;
    typedef f32                                     time_type;
    typedef core_str::String                        str_type;

    enum
    {
      k_info,
      k_success,
      k_debug,
      k_warning,
      k_error,
      k_count
    }; typedef tl_int                               severity_type;

    static const char* s_severityStr[k_count];
    static const char* s_severityStrShort[k_count];

  public:
    Log_I();
    Log_I(const this_type& a_other);

    this_type& operator << (BufferArg  a_string);
    this_type& operator << (BufferArgW a_string);
    this_type& operator << (char8     a_value);
    this_type& operator << (char32    a_value);
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
    TLOC_DECL_AND_DEF_GETTER(const char*, GetFileName, m_fileName);
    TLOC_DECL_AND_DEF_GETTER(tl_ulong, GetLineNumber, m_lineNumber);
    TLOC_DECL_AND_DEF_GETTER(severity_type, GetSeverity, m_severity);

    this_type& operator=(this_type a_other);
    void       swap(this_type& a_other);

  protected:
    Log_I(severity_type a_severity, BufferArg a_fileName,
          const tl_ulong a_lineNumber);

  protected:
    str_type          m_finalString;
    time_type         m_time;
    const char*       m_fileName;
    tl_ulong          m_lineNumber;
    severity_type     m_severity;
  };

  // -----------------------------------------------------------------------
  // swap

  TL_I void swap(Log_I& a, Log_I& b);

  // -----------------------------------------------------------------------
  // typedefs

  typedef Log_I               Log;

};};};

#endif