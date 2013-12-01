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
    : public core_bclass::NonCopyable_I
  {
  public:
    typedef f32                             time_type;
    typedef core_str::String                str_type;

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (str_type, GetFinalString, m_finalString);

  protected:

    BaseLog_I(BufferArg a_fileName, const tl_ulong a_lineNumber);

    str_type          m_finalString;
    time_type         m_time;
    const char*       m_fileName;
    const tl_ulong    m_lineNumber;
  };

  class Log
    : public BaseLog_I
  {
  public:
    typedef BaseLog_I                                   base_type;
    typedef Log                                       this_type;

  public:
    Log(BufferArg a_fileName, const tl_ulong a_lineNumber);

    this_type& operator << (BufferArg a_string);
    this_type& operator << (tl_int    a_value);
    this_type& operator << (tl_long   a_value);
    this_type& operator << (tl_uint   a_value);
    this_type& operator << (tl_ulong  a_value);
    this_type& operator << (tl_float  a_value);
    this_type& operator << (tl_double a_value);
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

    namespace update
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

        str_type DoFormat(const BaseLog_I& a_log) const;
      };
    };
  };

  template <typename T_WritePolicy = p_logger::write_policy::Console,
            typename T_UpdatePolicy = p_logger::update::Immediately,
            typename T_FormatPolicy = p_logger::format_policy::Default>
  class Logger_T
    : public T_WritePolicy
    , public T_FormatPolicy
    , public core_bclass::NonCopyable_I
  {
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

    void AddLog(const BaseLog_I& a_log);
    void Flush();

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(str_type, GetName, m_name);
  private:
    void DoAddLog(const BaseLog_I& a_log, p_logger::update::Immediately);
    void DoAddLog(const BaseLog_I& a_log, p_logger::update::OnFlush);

    void DoFlush(p_logger::update::Immediately);
    void DoFlush(p_logger::update::OnFlush);

  private:
    str_type    m_name;
    log_cont    m_logs;
  };



};};};

#endif