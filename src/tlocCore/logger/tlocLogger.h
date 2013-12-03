#ifndef _TLOC_CORE_LOGGER_LOGGER_H_
#define _TLOC_CORE_LOGGER_LOGGER_H_

#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/io/tlocFileIO.h>

namespace tloc { namespace core { namespace logger {

  class BaseLog_I
  {
  public:
    typedef BaseLog_I                       this_type;
    typedef f32                             time_type;
    typedef core_str::String                str_type;

  public:
    BaseLog_I();
    BaseLog_I(const this_type& a_other);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (str_type, GetFinalString, m_finalString);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(str_type, GetLog, m_finalString);
    TLOC_DECL_AND_DEF_GETTER(time_type, GetTime, m_time);
    TLOC_DECL_AND_DEF_GETTER(char*, GetFileName, m_fileName);
    TLOC_DECL_AND_DEF_GETTER(tl_ulong, GetLineNumber, m_lineNumber);

    this_type& operator=(this_type a_other);
    void       swap(this_type& a_other);

  protected:
    BaseLog_I(BufferArg a_fileName, const tl_ulong a_lineNumber);

    str_type          m_finalString;
    time_type         m_time;
    const char*       m_fileName;
    tl_ulong          m_lineNumber;
  };

  namespace p_logger
  {
    namespace severity
    {
      class Info    { static const tl_int s_value = 0; };
      class Debug   { static const tl_int s_value = 1; };
      class Warning { static const tl_int s_value = 2; };
      class Error   { static const tl_int s_value = 3; };
    };

    namespace update_policy
    {
      class Immediately { };
      class OnFlush     { };
    };

    namespace write_policy
    {
      class Console
      {
      protected:
        Console(BufferArg a_loggerName);

        void DoWrite(BufferArg a_formattedLog);
      };

      // usually for outputting to a window other than the console
      class Output
      {
      protected:
        Output(BufferArg a_loggerName);

        void DoWrite(BufferArg a_formattedLog);
      };

      class File
      {
      protected:
        File(BufferArg a_fileName);

        void DoWrite(BufferArg a_formattedLog);

        core_io::FileIO_AppendA m_file;
      };
    };

    namespace format_policy
    {
      class Default
      {
      public:
        typedef core_str::String                      str_type;

      protected:
        Default(BufferArg a_loggerName);

        str_type DoFormat(const BaseLog_I& a_log) const;

      private:
        str_type m_loggerName;
      };
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Logger_T<>

  template <typename T_WritePolicy,
            typename T_UpdatePolicy,
            typename T_FormatPolicy>
  class Logger_T
    : public T_WritePolicy
    , public T_FormatPolicy
    , public core_bclass::NonCopyable_I
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_WritePolicy, p_logger::write_policy::Console>::value ||
       Loki::IsSameType<T_WritePolicy, p_logger::write_policy::Output>::value ||
       Loki::IsSameType<T_WritePolicy, p_logger::write_policy::File>::value),
       Invalid_write_policy_selected);

    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_UpdatePolicy, p_logger::update_policy::Immediately>::value ||
       Loki::IsSameType<T_UpdatePolicy, p_logger::update_policy::OnFlush>::value),
       Invalid_write_policy_selected);

    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_FormatPolicy, p_logger::format_policy::Default>::value),
       Invalid_write_policy_selected);

  public:
    typedef Logger_T                                  this_type;
    typedef T_WritePolicy                             write_policy;
    typedef T_UpdatePolicy                            update_policy;

    typedef T_WritePolicy                             write_base_type;
    typedef T_FormatPolicy                            format_base_type;
    typedef core_str::String                          str_type;

    typedef BaseLog_I                                 log_type;
    typedef core_conts::Array<log_type>               log_cont;

  public:
    Logger_T(const str_type& a_name);

    this_type& AddLog(const BaseLog_I& a_log);
    this_type& Flush();

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(str_type, GetName, m_name);
  private:
    void DoAddLog(const BaseLog_I& a_log, p_logger::update_policy::Immediately);
    void DoAddLog(const BaseLog_I& a_log, p_logger::update_policy::OnFlush);

    void DoFlush(p_logger::update_policy::Immediately);
    void DoFlush(p_logger::update_policy::OnFlush);

  private:
    str_type    m_name;
    log_cont    m_logs;
  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef Logger_T<p_logger::write_policy::Console,
                   p_logger::update_policy::Immediately,
                   p_logger::format_policy::Default>      LoggerConsoleImmediate;
  typedef Logger_T<p_logger::write_policy::Console,
                   p_logger::update_policy::OnFlush,
                   p_logger::format_policy::Default>      LoggerConsoleOnFlush;

  typedef Logger_T<p_logger::write_policy::Output,
                   p_logger::update_policy::Immediately,
                   p_logger::format_policy::Default>      LoggerOutputImmediate;
  typedef Logger_T<p_logger::write_policy::Output,
                   p_logger::update_policy::OnFlush,
                   p_logger::format_policy::Default>      LoggerOutputOnFlush;

  typedef Logger_T<p_logger::write_policy::File,
                   p_logger::update_policy::Immediately,
                   p_logger::format_policy::Default>      LoggerFileImmediate;
  typedef Logger_T<p_logger::write_policy::File,
                   p_logger::update_policy::OnFlush,
                   p_logger::format_policy::Default>      LoggerFileOnFlush;

  // ///////////////////////////////////////////////////////////////////////
  // Log

  template <typename T_Logger>
  class Log_T
    : public BaseLog_I
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_Logger, LoggerConsoleImmediate>::value ||
       Loki::IsSameType<T_Logger, LoggerConsoleOnFlush>::value ||
       Loki::IsSameType<T_Logger, LoggerOutputImmediate>::value ||
       Loki::IsSameType<T_Logger, LoggerOutputOnFlush>::value ||
       Loki::IsSameType<T_Logger, LoggerFileImmediate>::value ||
       Loki::IsSameType<T_Logger, LoggerFileOnFlush>::value),
       Unsupported_logger_type);

  public:
    typedef BaseLog_I                                 base_type;
    typedef Log_T                                     this_type;

  public:
    Log_T(T_Logger* a_logger, BufferArg a_fileName, const tl_ulong a_lineNumber);
    ~Log_T();

    this_type& operator << (BufferArg a_string);
    this_type& operator << (tl_int    a_value);
    this_type& operator << (tl_long   a_value);
    this_type& operator << (tl_uint   a_value);
    this_type& operator << (tl_ulong  a_value);
    this_type& operator << (tl_float  a_value);
    this_type& operator << (tl_double a_value);

  private:
    T_Logger* m_logger;
  };

  // -----------------------------------------------------------------------
  // helper functions

  template <typename T_Logger>
  Log_T<T_Logger>
    MakeLog(T_Logger* a_logger, BufferArg a_fileName, const tl_ulong a_lineNumber)
  { return Log_T<T_Logger>(a_logger, a_fileName, a_lineNumber); }

  // -----------------------------------------------------------------------
  // typedefs

  typedef Log_T<LoggerConsoleImmediate>                 LogConsoleImmediate;
  typedef Log_T<LoggerConsoleOnFlush>                   LogConsoleOnFlush;
  typedef Log_T<LoggerOutputImmediate>             LogOutputImmediate;
  typedef Log_T<LoggerOutputOnFlush>               LogOutputOnFlush;
  typedef Log_T<LoggerFileImmediate>                    LogFileImmediate;
  typedef Log_T<LoggerFileOnFlush>                      LogFileOnFlush;

};};};

#define TLOC_LOG(_logger_, _severity_) \
  tloc::core::logger::MakeLog(_logger_, __FILE__, __LINE__)
#define TLOC_LOG_INFO(_logger_)\
  tloc::core::logger::MakeLog(_logger_, __FILE__, __LINE__)
#define TLOC_LOG_DEBUG(_logger_)\
  tloc::core::logger::MakeLog(_logger_, __FILE__, __LINE__)
#define TLOC_LOG_WARN(_logger_)\
  tloc::core::logger::MakeLog(_logger_, __FILE__, __LINE__)
#define TLOC_LOG_ERR(_logger_)\
  tloc::core::logger::MakeLog(_logger_, __FILE__, __LINE__)

#endif