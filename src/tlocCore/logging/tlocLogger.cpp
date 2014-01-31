#include "tlocLogger.h"

#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/time/tlocTime.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/platform/tlocPlatformSpecificIncludes.h>

namespace {
  // -----------------------------------------------------------------------
  // platform specific fast console output

  template <typename T_Platform>
  void DoWriteOutput(tloc::BufferArg a_formattedLog, T_Platform)
  { printf("%s", a_formattedLog.GetPtr()); }

#if defined(TLOC_OS_WIN)
  void DoWriteOutput(tloc::BufferArg a_formattedLog,
                     tloc::core_plat::p_platform_info::win)
  {
    static bool idp = IsDebuggerPresent() != 0;
    if (idp)
    { OutputDebugString(a_formattedLog); }
    else
    { printf(a_formattedLog); }
  }
#endif
  
};

namespace tloc { namespace core { namespace logging {

  // ///////////////////////////////////////////////////////////////////////
  // Log

#define TLOC_LOG_TEMPS    typename T_Logger
#define TLOC_LOG_PARAMS   T_Logger
#define TLOC_LOG_TYPE     typename Log_T<TLOC_LOG_PARAMS>

  template <TLOC_LOG_TEMPS>
  Log_T<TLOC_LOG_PARAMS>::
    Log_T(T_Logger* a_logger, severity_type a_severity,
          BufferArg a_fileName, const tl_ulong a_lineNumber)
    : base_type(a_severity, a_fileName, a_lineNumber)
    , m_logger(a_logger)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  Log_T<TLOC_LOG_PARAMS>::
    ~Log_T()
  {
    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { m_logger->AddLog(*this); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type&
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(BufferArg a_string)
  {
    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_string); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type&
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(tl_int a_value)
  {
    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type&
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(tl_long a_value)
  {
    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type&
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(tl_uint a_value)
  {
    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type&
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(tl_ulong a_value)
  {
    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type&
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(tl_float a_value)
  {
    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type&
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(tl_double a_value)
  {
    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // ///////////////////////////////////////////////////////////////////////
  // write_policy

  namespace p_logger {
    namespace write_policy {

      // ///////////////////////////////////////////////////////////////////////
      // console

      Console::
        Console(BufferArg)
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void
        Console::
        DoWrite(BufferArg a_formattedLog)
      {
        printf("%s", a_formattedLog.GetPtr());
      }

      // ///////////////////////////////////////////////////////////////////////
      // Output

      Output::
        Output(BufferArg)
      { }

      void
        Output::
        DoWrite(BufferArg a_formattedLog)
      {
        DoWriteOutput(a_formattedLog, core_plat::PlatformInfo::platform_type());
      }

      // ///////////////////////////////////////////////////////////////////////
      // file

      File::
        File(BufferArg a_fileName)
        : m_file(core_io::Path(a_fileName))
      {
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void
        File::
        DoWrite(BufferArg a_formattedLog)
      {
        m_file.Open();
        m_file.Write(a_formattedLog);
        m_file.Close();
      }
    };

    namespace format_policy {

      // ///////////////////////////////////////////////////////////////////////
      // Default

      Default::
        Default(BufferArg a_loggerName)
        : m_loggerName(a_loggerName)
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      Default::str_type
        Default::
        DoFormat(const Log_I& a_log) const
      {
        if (a_log.GetLineNumber() != 0)
        {
          return
            core_str::Format("\n[%s] %s | %07.2f | %s | %s(%lu)",
            Log_I::s_severityStrShort[a_log.GetSeverity()],
            m_loggerName.c_str(), a_log.GetTime(), a_log.GetLog().c_str(),
            a_log.GetFileName(),
            a_log.GetLineNumber());
        }
        else
        {
          return
            core_str::Format("\n[%s] %s | %07.2f | %s ",
            Log_I::s_severityStrShort[a_log.GetSeverity()],
            m_loggerName.c_str(), a_log.GetTime(), a_log.GetLog().c_str() );
        }
      }

    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // logger

  enum
  {
    k_logger_disabled,
    k_count
  };

#define TLOC_LOGGER_TEMPS   typename T_WritePolicy, typename T_UpdatePolicy, typename T_FormatPolicy
#define TLOC_LOGGER_PARAMS  T_WritePolicy, T_UpdatePolicy, T_FormatPolicy
#define TLOC_LOGGER_TYPE    typename Logger_T<TLOC_LOGGER_PARAMS>

  template <TLOC_LOGGER_TEMPS>
  Logger_T<TLOC_LOGGER_PARAMS>::
    Logger_T(const str_type& a_name)
    : write_base_type(a_name)
    , format_base_type(a_name)
    , m_name(a_name)
    , m_flags(k_count)
    , m_severity(log_type::k_info)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  TLOC_LOGGER_TYPE::this_type&
    Logger_T<TLOC_LOGGER_PARAMS>::
    AddLog(const Log_I& a_log)
  {
    if (IsDisabled() == false)
    { DoAddLog(a_log, update_policy()); }
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  TLOC_LOGGER_TYPE::this_type&
    Logger_T<TLOC_LOGGER_PARAMS>::
    Flush()
  {
    DoFlush(update_policy());
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  void
    Logger_T<TLOC_LOGGER_PARAMS>::
    SetDisable(bool a_disable)
  { m_flags[k_logger_disabled] = a_disable; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  bool
    Logger_T<TLOC_LOGGER_PARAMS>::
    IsDisabled() const
  {
    return m_flags[k_logger_disabled];
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  bool
    Logger_T<TLOC_LOGGER_PARAMS>::
    CanDisplaySeverity(severity_type a_severity) const
  {
    return a_severity >= m_severity;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  void
    Logger_T<TLOC_LOGGER_PARAMS>::
    DoAddLog(const Log_I& a_log, p_logger::update_policy::Immediate)
  {
    str_type log = format_base_type::DoFormat(a_log);
    write_base_type::DoWrite(log);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  void
    Logger_T<TLOC_LOGGER_PARAMS>::
    DoAddLog(const Log_I& a_log, p_logger::update_policy::OnFlush)
  { m_logs.push_back(a_log); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  void
    Logger_T<TLOC_LOGGER_PARAMS>::
    DoFlush(p_logger::update_policy::Immediate)
  { /* do nothing */ }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  void
    Logger_T<TLOC_LOGGER_PARAMS>::
    DoFlush(p_logger::update_policy::OnFlush)
  {
    core_str::String allLogs;

    for (log_cont::iterator itr = m_logs.begin(), itrEnd = m_logs.end();
          itr != itrEnd; ++itr)
    {
      allLogs += format_base_type::DoFormat(*itr);
    }

    write_base_type::DoWrite(allLogs);
  }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class Logger_T<p_logger::write_policy::Console,
                          p_logger::update_policy::Immediate,
                          p_logger::format_policy::Default>;
  template class Logger_T<p_logger::write_policy::Console,
                          p_logger::update_policy::OnFlush,
                          p_logger::format_policy::Default>;

  template class Logger_T<p_logger::write_policy::Output,
                          p_logger::update_policy::Immediate,
                          p_logger::format_policy::Default>;
  template class Logger_T<p_logger::write_policy::Output,
                          p_logger::update_policy::OnFlush,
                          p_logger::format_policy::Default>;

  template class Logger_T<p_logger::write_policy::File,
                          p_logger::update_policy::Immediate,
                          p_logger::format_policy::Default>;
  template class Logger_T<p_logger::write_policy::File,
                          p_logger::update_policy::OnFlush,
                          p_logger::format_policy::Default>;

  template class Log_T<LoggerConsoleImmediate>;
  template class Log_T<LoggerConsoleOnFlush>;
  template class Log_T<LoggerOutputImmediate>;
  template class Log_T<LoggerOutputOnFlush>;
  template class Log_T<LoggerFileImmediate>;
  template class Log_T<LoggerFileOnFlush>;

};};};

#include <tlocCore/containers/tlocArray.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(tloc::core::logging::Log_I);