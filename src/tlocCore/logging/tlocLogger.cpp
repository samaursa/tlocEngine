#include "tlocLogger.h"

#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/time/tlocTime.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/platform/tlocPlatformSpecificIncludes.h>
#include <tlocCore/tlocConsole.h>

namespace {
  // -----------------------------------------------------------------------

  using namespace tloc::core_log;

  typedef Log_I::severity_type                          severity_type;

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void DoWrite(tloc::buffer_arg a_formattedLog, severity_type a_severity)
  {
    using namespace tloc::console;

    switch(a_severity)
    {
    case Log_I::k_info:
      set_console_color(p_color::gray, p_color::black);
      break;
    case Log_I::k_success:
      set_console_color(p_color::green, p_color::black);
      break;
    case Log_I::k_debug:
      set_console_color(p_color::white, p_color::black);
      break;
    case Log_I::k_warning:
      set_console_color(p_color::yellow, p_color::black);
      break;
    case Log_I::k_error:
      set_console_color(p_color::red, p_color::black);
      break;
    default:
      set_console_color(p_color::dark_white, p_color::black);
      break;
    }

    WriteToConsole(a_formattedLog);

    // reset the color (although we don't know what the original colors were)
    set_console_color(p_color::dark_white, p_color::black);
  }
  
};

namespace tloc { namespace core { namespace logging {

  // -----------------------------------------------------------------------

  void
    WriteToConsole(tloc::buffer_arg a_formattedLog, severity_type a_severity)
  { DoWrite(a_formattedLog, a_severity); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Log, typename T_Logger, typename T_BuildConfig>
  void
    DoBreakOnSeverity(const T_Log& a_log, const T_Logger& a_logger, T_BuildConfig)
  {
    if (a_log.GetSeverity() >= a_logger.GetBreakOnSeverity())
    { TLOC_DEBUG_BREAK(); }
  }

  template <typename T_Log, typename T_Logger>
  void
    DoBreakOnSeverity(const T_Log& , const T_Logger& , 
                      core_cfg::p_build_config::Release)
  { }

  // ///////////////////////////////////////////////////////////////////////
  // Log

#define TLOC_LOG_TEMPS    typename T_Logger, typename T_BuildConfig
#define TLOC_LOG_PARAMS   T_Logger, T_BuildConfig
#define TLOC_LOG_TYPE     typename Log_T<TLOC_LOG_PARAMS>

  template <TLOC_LOG_TEMPS>
  Log_T<TLOC_LOG_PARAMS>::
    Log_T(T_Logger* a_logger, severity_type a_severity,
          buffer_arg a_fileName, const tl_ulong a_lineNumber)
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
  TLOC_LOG_TYPE::this_type_cref
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(buffer_arg a_string) const
  {
    DoBreakOnSeverity(*this, *m_logger, 
                      core_cfg::BuildConfig::build_config_type());

    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_string); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type_cref
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(BufferArgW a_string) const
  {
    DoBreakOnSeverity(*this, *m_logger, 
                      core_cfg::BuildConfig::build_config_type());

    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_string); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type_cref
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(tl_int a_value) const
  {
    DoBreakOnSeverity(*this, *m_logger, 
                      core_cfg::BuildConfig::build_config_type());

    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type_cref
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(tl_long a_value) const
  {
    DoBreakOnSeverity(*this, *m_logger, 
                      core_cfg::BuildConfig::build_config_type());
    
    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type_cref
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(char8 a_value) const
  {
    DoBreakOnSeverity(*this, *m_logger, 
                      core_cfg::BuildConfig::build_config_type());

    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type_cref
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(char32 a_value) const
  {
    DoBreakOnSeverity(*this, *m_logger, 
                      core_cfg::BuildConfig::build_config_type());

    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type_cref
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(tl_uint a_value) const
  {
    DoBreakOnSeverity(*this, *m_logger, 
                      core_cfg::BuildConfig::build_config_type());

    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type_cref
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(tl_ulong a_value) const
  {
    DoBreakOnSeverity(*this, *m_logger, 
                      core_cfg::BuildConfig::build_config_type());

    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type_cref
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(tl_float a_value) const
  {
    DoBreakOnSeverity(*this, *m_logger, 
                      core_cfg::BuildConfig::build_config_type());

    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type_cref
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(tl_double a_value) const
  {
    DoBreakOnSeverity(*this, *m_logger, 
                      core_cfg::BuildConfig::build_config_type());

    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type_cref
    Log_T<TLOC_LOG_PARAMS>::
    operator<<(core_utils::MemoryAddress a_memAddress) const
  {
    DoBreakOnSeverity(*this, *m_logger, 
                      core_cfg::BuildConfig::build_config_type());

    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::operator<<(a_memAddress); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type_cref
    Log_T<TLOC_LOG_PARAMS>::
    put(char8 a_value) const
  {
    DoBreakOnSeverity(*this, *m_logger, 
                      core_cfg::BuildConfig::build_config_type());

    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::put(a_value); }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOG_TEMPS>
  TLOC_LOG_TYPE::this_type_cref
    Log_T<TLOC_LOG_PARAMS>::
    write(const char8* a_string, tl_int a_size) const
  {
    DoBreakOnSeverity(*this, *m_logger, 
                      core_cfg::BuildConfig::build_config_type());

    if (m_logger->IsDisabled() == false &&
        m_logger->CanDisplaySeverity(GetSeverity()) )
    { base_type::write(a_string, a_size); }

    return *this;
  }

  // ///////////////////////////////////////////////////////////////////////
  // write_policy

  namespace p_logger {
    namespace write_policy {

      // ///////////////////////////////////////////////////////////////////////
      // console

      Console::
        Console(buffer_arg)
      { }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void
        Console::
        DoWrite(buffer_arg a_formattedLog, severity_type a_severity) const
      {
        ::DoWrite(a_formattedLog, a_severity);
      }

      // ///////////////////////////////////////////////////////////////////////
      // Output

      Output::
        Output(buffer_arg)
      { }

      void
        Output::
        DoWrite(buffer_arg a_formattedLog, severity_type a_severity) const
      {
        if (console::write_to_ide_console(a_formattedLog) == false)
        { ::DoWrite(a_formattedLog, a_severity); }
      }

      // ///////////////////////////////////////////////////////////////////////
      // file

      File::
        File(buffer_arg a_fileName)
        : m_file(core_io::path(a_fileName))
      {
      }

      // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

      void
        File::
        DoWrite(buffer_arg a_formattedLog, severity_type ) const
      {
        m_file.open();
        m_file.write(a_formattedLog);
        m_file.close();
      }
    };

    namespace format_policy {

      // ///////////////////////////////////////////////////////////////////////
      // Default

      Default::
        Default(buffer_arg a_loggerName)
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
    , m_breakOnSeverity(log_type::k_count)
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
    ResetBreakOnSeverity()
  { m_severity = log_type::k_count; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  void
    Logger_T<TLOC_LOGGER_PARAMS>::
    DoAddLog(const Log_I& a_log, p_logger::update_policy::Immediate)
  {
    str_type log = format_base_type::DoFormat(a_log);
    write_base_type::DoWrite(log, a_log.GetSeverity());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  void
    Logger_T<TLOC_LOGGER_PARAMS>::
    DoAddLog(const Log_I& a_log, p_logger::update_policy::OnFlush)
  { 
    m_logs.push_back(a_log);
  }

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

    // the logs are already formatted - not possible to clarify severity so 
    // it is going to be 'info'
    write_base_type::DoWrite(allLogs, log_type::k_info);
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