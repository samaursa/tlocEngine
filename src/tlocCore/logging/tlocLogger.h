#ifndef _TLOC_CORE_LOGGER_LOGGER_H_
#define _TLOC_CORE_LOGGER_LOGGER_H_

#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/io/tlocFileIO.h>

#include <tlocCore/logging/tlocLog.h>
#include <tlocCore/utilities/tlocCheckpoints.h>

namespace tloc { namespace core { namespace logging {

  namespace p_logger
  {
    namespace update_policy
    {
      class Immediate   { };
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

        str_type DoFormat(const Log_I& a_log) const;

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
      (Loki::IsSameType<T_UpdatePolicy, p_logger::update_policy::Immediate>::value ||
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

    typedef Log_I                                     log_type;
    typedef core_conts::Array<log_type>               log_cont;
    typedef log_type::severity_type                   severity_type;

  public:
    Logger_T(const str_type& a_name);

    this_type& AddLog(const Log_I& a_log);
    this_type& Flush();

    void       SetDisable(bool a_disable);
    bool       IsDisabled() const;

    bool       CanDisplaySeverity(severity_type a_severity) const;

    TLOC_DECL_AND_DEF_GETTER(severity_type, GetSeverity, m_severity);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(severity_type, SetSeverity, m_severity);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(str_type, GetName, m_name);

  private:
    void DoAddLog(const Log_I& a_log, p_logger::update_policy::Immediate);
    void DoAddLog(const Log_I& a_log, p_logger::update_policy::OnFlush);

    void DoFlush(p_logger::update_policy::Immediate);
    void DoFlush(p_logger::update_policy::OnFlush);

  private:
    str_type                  m_name;
    log_cont                  m_logs;
    core_utils::Checkpoints   m_flags;
    severity_type             m_severity;
  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef Logger_T<p_logger::write_policy::Console,
                   p_logger::update_policy::Immediate,
                   p_logger::format_policy::Default>      LoggerConsoleImmediate;
  typedef Logger_T<p_logger::write_policy::Console,
                   p_logger::update_policy::OnFlush,
                   p_logger::format_policy::Default>      LoggerConsoleOnFlush;

  typedef Logger_T<p_logger::write_policy::Output,
                   p_logger::update_policy::Immediate,
                   p_logger::format_policy::Default>      LoggerOutputImmediate;
  typedef Logger_T<p_logger::write_policy::Output,
                   p_logger::update_policy::OnFlush,
                   p_logger::format_policy::Default>      LoggerOutputOnFlush;

  typedef Logger_T<p_logger::write_policy::File,
                   p_logger::update_policy::Immediate,
                   p_logger::format_policy::Default>      LoggerFileImmediate;
  typedef Logger_T<p_logger::write_policy::File,
                   p_logger::update_policy::OnFlush,
                   p_logger::format_policy::Default>      LoggerFileOnFlush;

  // ///////////////////////////////////////////////////////////////////////
  // Log

  template <typename T_Logger>
  class Log_T
    : public Log_I
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
    typedef Log_I                                     base_type;
    typedef Log_T                                     this_type;
    typedef base_type::severity_type                  severity_type;

  public:
    Log_T(T_Logger* a_logger, severity_type a_severity,
          BufferArg a_fileName, const tl_ulong a_lineNumber);
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
    MakeLog(T_Logger* a_logger, Log_I::severity_type a_severity,
            BufferArg a_fileName, const tl_ulong a_lineNumber)
  {
    return Log_T<T_Logger>(a_logger, a_severity, a_fileName, a_lineNumber);
  }

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
  tloc::core::logging::MakeLog(_logger_, _severity_, __FILE__, __LINE__)
#define TLOC_LOG_FILENAME_ONLY(_logger_, _severity_) \
  tloc::core::logging::MakeLog(_logger_, _severity_, TLOC_THIS_FILE_NAME, __LINE__)
#define TLOC_LOG_NO_FILENAME(_logger_, _severity_) \
  tloc::core::logging::MakeLog(_logger_, _severity_, "", 0)

#define TLOC_LOG_IF(_expr_, _logger_, _severity_) \
  if (_expr_) TLOC_LOG(_logger_, _severity_)
#define TLOC_LOG_FILENAME_ONLY_IF(_expr_, _logger_, _severity_) \
  if (_expr_) TLOC_LOG_FILENAME_ONLY(_logger_, _severity_)
#define TLOC_LOG_NO_FILENAME_IF(_logger_, _severity_) \
  if (_expr_) TLOC_LOG_NO_FILENAME(_logger_, _severity_)

#define TLOC_LOG_INFO(_logger_)\
  TLOC_LOG(_logger_, tloc::core::logging::Log_I::k_info)
#define TLOC_LOG_DEBUG(_logger_)\
  TLOC_LOG(_logger_, tloc::core::logging::Log_I::k_debug)
#define TLOC_LOG_WARN(_logger_)\
  TLOC_LOG(_logger_, tloc::core::logging::Log_I::k_warning)
#define TLOC_LOG_ERR(_logger_)\
  TLOC_LOG(_logger_, tloc::core::logging::Log_I::k_error)

#define TLOC_LOG_INFO_IF(_expr_, _logger_)\
  TLOC_LOG_IF(_expr_, _logger_, tloc::core::logging::Log_I::k_info)
#define TLOC_LOG_DEBUG_IF(_expr_, _logger_)\
  TLOC_LOG_IF(_expr_, _logger_, tloc::core::logging::Log_I::k_debug)
#define TLOC_LOG_WARN_IF(_expr_, _logger_)\
  TLOC_LOG_IF(_expr_, _logger_, tloc::core::logging::Log_I::k_warning)
#define TLOC_LOG_ERR_IF(_expr_, _logger_)\
  TLOC_LOG_IF(_expr_, _logger_, tloc::core::logging::Log_I::k_error)

#define TLOC_LOG_INFO_FILENAME_ONLY(_logger_)\
  TLOC_LOG_FILENAME_ONLY(_logger_, tloc::core::logging::Log_I::k_info)
#define TLOC_LOG_DEBUG_FILENAME_ONLY(_logger_)\
  TLOC_LOG_FILENAME_ONLY(_logger_, tloc::core::logging::Log_I::k_debug)
#define TLOC_LOG_WARN_FILENAME_ONLY(_logger_)\
  TLOC_LOG_FILENAME_ONLY(_logger_, tloc::core::logging::Log_I::k_warning)
#define TLOC_LOG_ERR_FILENAME_ONLY(_logger_)\
  TLOC_LOG_FILENAME_ONLY(_logger_, tloc::core::logging::Log_I::k_error)

#define TLOC_LOG_INFO_FILENAME_ONLY_IF(_expr_, _logger_)\
  TLOC_LOG_FILENAME_ONLY_IF(_expr_, _logger_, tloc::core::logging::Log_I::k_info)
#define TLOC_LOG_DEBUG_FILENAME_ONLY_IF(_logger_)\
  TLOC_LOG_FILENAME_ONLY_IF(_expr_, _logger_, tloc::core::logging::Log_I::k_debug)
#define TLOC_LOG_WARN_FILENAME_ONLY_IF(_logger_)\
  TLOC_LOG_FILENAME_ONLY_IF(_expr_, _logger_, tloc::core::logging::Log_I::k_warning)
#define TLOC_LOG_ERR_FILENAME_ONLY_IF(_logger_)\
  TLOC_LOG_FILENAME_ONLY_IF(_expr_, _logger_, tloc::core::logging::Log_I::k_error)

#define TLOC_LOG_INFO_NO_FILENAME(_logger_)\
  TLOC_LOG_NO_FILENAME(_logger_, tloc::core::logging::Log_I::k_info)
#define TLOC_LOG_DEBUG_NO_FILENAME(_logger_)\
  TLOC_LOG_NO_FILENAME(_logger_, tloc::core::logging::Log_I::k_debug)
#define TLOC_LOG_WARN_NO_FILENAME(_logger_)\
  TLOC_LOG_NO_FILENAME(_logger_, tloc::core::logging::Log_I::k_warning)
#define TLOC_LOG_ERR_NO_FILENAME(_logger_)\
  TLOC_LOG_NO_FILENAME(_logger_, tloc::core::logging::Log_I::k_error)

#define TLOC_LOG_INFO_NO_FILENAME_IF(_expr_, _logger_)\
  TLOC_LOG_NO_FILENAME_IF(_expr_, _logger_, tloc::core::logging::Log_I::k_info)
#define TLOC_LOG_DEBUG_NO_FILENAME_IF(_expr_, _logger_)\
  TLOC_LOG_NO_FILENAME_IF(_expr_, _logger_, tloc::core::logging::Log_I::k_debug)
#define TLOC_LOG_WARN_NO_FILENAME_IF(_expr_, _logger_)\
  TLOC_LOG_NO_FILENAME_IF(_expr_, _logger_, tloc::core::logging::Log_I::k_warning)
#define TLOC_LOG_ERR_NO_FILENAME_IF(_expr_, _logger_)\
  TLOC_LOG_NO_FILENAME_IF(_expr_, _logger_, tloc::core::logging::Log_I::k_error)

#endif