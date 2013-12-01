#include "tlocLogger.h"

#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/time/tlocTime.h>

namespace {

  static const tloc::tl_int g_initialBufferSize = 128;

};

namespace tloc { namespace core { namespace logger {

  //LOG_DEBUG(core_log) << "Whatever" << 1.0f << "float";

  // ///////////////////////////////////////////////////////////////////////
  // BaseLog

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

  // ///////////////////////////////////////////////////////////////////////
  // Log

  Log::
    Log(BufferArg a_fileName, const tl_ulong a_lineNumber)
    : base_type(a_fileName, a_lineNumber)
  {
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log::this_type&
    Log::
    operator<<(BufferArg a_string)
  {
    m_finalString += a_string;
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log::this_type&
    Log::
    operator<<(tl_int a_value)
  {
    m_finalString += core_str::Format("%i", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log::this_type&
    Log::
    operator<<(tl_long a_value)
  {
    m_finalString += core_str::Format("%il", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log::this_type&
    Log::
    operator<<(tl_uint a_value)
  {
    m_finalString += core_str::Format("%u", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log::this_type&
    Log::
    operator<<(tl_ulong a_value)
  {
    m_finalString += core_str::Format("%ul", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log::this_type&
    Log::
    operator<<(tl_float a_value)
  {
    m_finalString += core_str::Format("%f", a_value);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Log::this_type&
    Log::
    operator<<(tl_double a_value)
  {
    m_finalString += core_str::Format("%f", a_value);
    return *this;
  }

  // ///////////////////////////////////////////////////////////////////////
  // write_policy

  namespace p_logger { namespace write_policy {

    // ///////////////////////////////////////////////////////////////////////
    // console

    Console::
      Console(BufferArg)
    { }

    void
      Console::
      DoWrite(BufferArg a_formattedLog)
    {
      printf(a_formattedLog);
    }

    // ///////////////////////////////////////////////////////////////////////
    // file

    File::
      File(BufferArg a_fileName)
      : m_file(core_io::Path(a_fileName))
    {
    }

    void
      File::
      DoWrite(BufferArg a_formattedLog)
    {
      m_file.Open();
      m_file.Write(a_formattedLog);
      m_file.Close();
    }

  };};

  // ///////////////////////////////////////////////////////////////////////
  // logger

#define TLOC_LOGGER_TEMPS   typename T_WritePolicy, typename T_UpdatePolicy, typename T_FormatPolicy
#define TLOC_LOGGER_PARAMS  T_WritePolicy, T_UpdatePolicy, T_FormatPolicy
#define TLOC_LOGGER_TYPE    typename Logger_T<TLOC_LOGGER_PARAMS>

  template <TLOC_LOGGER_TEMPS>
  Logger_T<TLOC_LOGGER_PARAMS>::
    Logger_T(const str_type& a_name)
    : write_base_type(a_name)
    , m_name(a_name)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  void
    Logger_T<TLOC_LOGGER_PARAMS>::
    AddLog(const BaseLog_I& a_log)
  {
    DoAddLog(a_log, update_policy());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  void
    Logger_T<TLOC_LOGGER_PARAMS>::
    Flush()
  {
    DoFlush(update_policy());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  void
    Logger_T<TLOC_LOGGER_PARAMS>::
    DoAddLog(const BaseLog_I& a_log, p_logger::update::Immediately)
  {
    str_type log = format_base_type::DoFormat(a_log);
    write_base_type::DoWrite(log);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  void
    Logger_T<TLOC_LOGGER_PARAMS>::
    DoAddLog(const BaseLog_I& a_log, p_logger::update::OnFlush)
  { m_logs.push_back(a_log); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  void
    Logger_T<TLOC_LOGGER_PARAMS>::
    DoFlush(p_logger::update::Immediately)
  { /* do nothing */ }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_LOGGER_TEMPS>
  void
    Logger_T<TLOC_LOGGER_PARAMS>::
    DoFlush(p_logger::update::OnFlush)
  {
    core_str::String allLogs;

    for (log_cont::iterator itr = m_logs.begin(), itrEnd = m_logs.end();
          itr != itrEnd; ++itr)
    {
      allLogs += format_base_type::DoFormat(*itr);
    }

    write_base_type::DoWrite(allLogs);
  }

  template class Logger_T<>;

};};};