#ifndef _TLOC_CORE_LOGGER_LOG_H_
#define _TLOC_CORE_LOGGER_LOG_H_

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/configs/tlocBuildConfig.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/utilities/tlocPointerUtils.h>

namespace tloc { namespace core { namespace logging {

  namespace p_log
  {
    namespace severity
    {
      struct Info    { enum {k_value = 0}; };
      struct Success { enum {k_value = 1}; };
      struct Debug   { enum {k_value = 2}; };
      struct Warning { enum {k_value = 3}; };
      struct Error   { enum {k_value = 4}; };
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
      k_info = p_log::severity::Info::k_value,
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
    this_type& operator << (core_utils::MemoryAddress a_memAddress);

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

  // ///////////////////////////////////////////////////////////////////////
  // Log

  template <typename T_Logger, 
            typename T_BuildConfig = core_cfg::BuildConfig::build_config_type>
  class Log_T
    : public Log_I
  {
  public:
    typedef Log_I                                     base_type;
    typedef Log_T<T_Logger, T_BuildConfig>            this_type;
    typedef base_type::severity_type                  severity_type;

  public:
    Log_T(T_Logger* a_logger, severity_type a_severity,
          BufferArg a_fileName, const tl_ulong a_lineNumber);
    ~Log_T();

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
    this_type& operator << (core_utils::MemoryAddress a_memAddress);

  private:
    T_Logger* m_logger;
  };

  // -----------------------------------------------------------------------
  // helper functions

  template <typename T_Logger>
  Log_T<T_Logger>
    MakeLog(T_Logger* a_logger, Log_I::severity_type a_severity,
            BufferArg a_fileName, const tl_ulong a_lineNumber)
  {
    return Log_T<T_Logger>(a_logger, a_severity, a_fileName, a_lineNumber);
  }

  // ///////////////////////////////////////////////////////////////////////
  // Log_T<Release>

  template <typename T_Logger>
  class Log_T<T_Logger, core_cfg::p_build_config::Release>
  {
  public:
    typedef Log_I                                     base_type;
    typedef Log_T<T_Logger, 
                  core_cfg::p_build_config::Release>  this_type;
    typedef base_type::severity_type                  severity_type;

  public:
    Log_T(T_Logger* , severity_type ,
          BufferArg , const tl_ulong ) {}
    ~Log_T() {}

    this_type& operator << (BufferArg  )  { return *this; }
    this_type& operator << (BufferArgW )  { return *this; }
    this_type& operator << (char8      )  { return *this; }
    this_type& operator << (char32     )  { return *this; }
    this_type& operator << (tl_int     )  { return *this; }
    this_type& operator << (tl_long    )  { return *this; }
    this_type& operator << (tl_uint    )  { return *this; }
    this_type& operator << (tl_ulong   )  { return *this; }
    this_type& operator << (tl_float   )  { return *this; }
    this_type& operator << (tl_double  )  { return *this; }
  };

};};};

#endif