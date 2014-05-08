// the following macro will declare a function with the correct logger type
// that can then be defined to return a static logger (see existing usage
// in tlocCoreBase.h)

// -----------------------------------------------------------------------
// Internal use macros

#define TLOC_FORWARD_DECLARE_LOGGER(_writePolicy_, _updatePolicy_, _formatPolicy_)\
namespace tloc { namespace core {\
\
  /* unfortunately, some forward declaration is needed to avoid including */ \
  /* the Logger header */ \
  namespace logging {\
\
    namespace p_logger {\
      namespace write_policy  { class _writePolicy_; }\
      namespace update_policy { class _updatePolicy_; }\
      namespace format_policy { class _formatPolicy_; }\
    }\
\
    template <typename T_WritePolicy, \
              typename T_UpdatePolicy, \
              typename T_FormatPolicy> \
              class Logger_T;\
  };\
};}

#define TLOC_FORWARD_DECLARE_LOGGER_FUNC(_writePolicy_, _updatePolicy_, _formatPolicy_, _funcName_)\
  /* use macros instead of this function for logging */ \
  tloc::core::logging::Logger_T\
    <tloc::core::logging::p_logger::write_policy::_writePolicy_,\
     tloc::core::logging::p_logger::update_policy::_updatePolicy_,\
     tloc::core::logging::p_logger::format_policy::_formatPolicy_>&\
     _funcName_()

// -----------------------------------------------------------------------
// OUTPUT IMMEDIATE DEFAULT

// this macro MUST be used in a global namespace and MUST be used before
#define TLOC_FORWARD_DECLARE_LOGGER_OUTPUT_IMMEDIATE_DEFAULT()\
  TLOC_FORWARD_DECLARE_LOGGER(Output, Immediate, Default);
#define TLOC_LOGGER_DECLARE_LOGGER_FUNC_OUTPUT_IMMEDIATE_DEFAULT(_funcName_)\
  TLOC_FORWARD_DECLARE_LOGGER_FUNC(Output, Immediate, Default, _funcName_);
#define TLOC_LOGGER_DEFINE_LOGGER_FUNC_OUTPUT_IMMEDIATE_DEFAULT(_funcName_, _name_)\
  tloc::core::logging::LoggerOutputImmediate&\
    _funcName_()\
  {\
    static tloc::core::logging::LoggerOutputImmediate s_coreDefaultLogger( (#_name_) );\
    return s_coreDefaultLogger;\
  }

// -----------------------------------------------------------------------
// OUTPUT ONFLUSH DEFAULT

// this macro MUST be used in a global namespace and MUST be used before
#define TLOC_FORWARD_DECLARE_LOGGER_OUTPUT_ONFLUSH_DEFAULT()\
  TLOC_FORWARD_DECLARE_LOGGER(Output, OnFlush, Default);
#define TLOC_LOGGER_DECLARE_LOGGER_FUNC_OUTPUT_ONFLUSH_DEFAULT(_funcName_)\
  TLOC_FORWARD_DECLARE_LOGGER_FUNC(Output, OnFlush, Default, _funcName_);
#define TLOC_LOGGER_DEFINE_LOGGER_FUNC_OUTPUT_ONFLUSH_DEFAULT(_funcName_, _name_)\
  tloc::core::logging::LoggerOutputOnFlush&\
    _funcName_()\
  {\
    static tloc::core::logging::LoggerOutputOnFlush s_coreDefaultLogger( (#_name_) );\
    return s_coreDefaultLogger;\
  }

// -----------------------------------------------------------------------
// CONSOLE IMMEDIATE DEFAULT

// this macro MUST be used in a global namespace and MUST be used before
#define TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT()\
  TLOC_FORWARD_DECLARE_LOGGER(Console, Immediate, Default);
#define TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(_funcName_)\
  TLOC_FORWARD_DECLARE_LOGGER_FUNC(Console, Immediate, Default, _funcName_);
#define TLOC_LOGGER_DEFINE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(_funcName_, _name_)\
  tloc::core::logging::LoggerConsoleImmediate&\
    _funcName_()\
  {\
    static tloc::core::logging::LoggerConsoleImmediate s_coreDefaultLogger( (_name_) );\
    return s_coreDefaultLogger;\
  }

// -----------------------------------------------------------------------
// CONSOLE ONFLUSH DEFAULT

// this macro MUST be used in a global namespace and MUST be used before
#define TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_ONFLUSH_DEFAULT()\
  TLOC_FORWARD_DECLARE_LOGGER(Console, OnFlush, Default);
#define TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_ONFLUSH_DEFAULT(_funcName_)\
  TLOC_FORWARD_DECLARE_LOGGER_FUNC(Console, OnFlush, Default, _funcName_);
#define TLOC_LOGGER_DEFINE_LOGGER_FUNC_CONSOLE_ONFLUSH_DEFAULT(_funcName_, _name_)\
  tloc::core::logging::LoggerConsoleOnFlush&\
    _funcName_()\
  {\
    static tloc::core::logging::LoggerConsoleOnFlush s_coreDefaultLogger( (#_name_) );\
    return s_coreDefaultLogger;\
  }

// -----------------------------------------------------------------------
// FILE IMMEDIATE DEFAULT

// this macro MUST be used in a global namespace and MUST be used before
#define TLOC_FORWARD_DECLARE_LOGGER_FILE_IMMEDIATE_DEFAULT()\
  TLOC_FORWARD_DECLARE_LOGGER(File, Immediate, Default);
#define TLOC_LOGGER_DECLARE_LOGGER_FUNC_FILE_IMMEDIATE_DEFAULT(_funcName_)\
  TLOC_FORWARD_DECLARE_LOGGER_FUNC(File, Immediate, Default, _funcName_);
#define TLOC_LOGGER_DEFINE_LOGGER_FUNC_FILE_IMMEDIATE_DEFAULT(_funcName_, _name_)\
  tloc::core::logging::LoggerFileImmediate&\
    _funcName_()\
  {\
    static tloc::core::logging::LoggerFileImmediate s_coreDefaultLogger( (#_name_) );\
    return s_coreDefaultLogger;\
  }

// -----------------------------------------------------------------------
// FILE ONFLUSH DEFAULT

// this macro MUST be used in a global namespace and MUST be used before
#define TLOC_FORWARD_DECLARE_LOGGER_FILE_ONFLUSH_DEFAULT()\
  TLOC_FORWARD_DECLARE_LOGGER(File, OnFlush, Default);
#define TLOC_LOGGER_DECLARE_LOGGER_FUNC_FILE_ONFLUSH_DEFAULT(_funcName_)\
  TLOC_FORWARD_DECLARE_LOGGER_FUNC(File, OnFlush, Default, _funcName_);
#define TLOC_LOGGER_DEFINE_LOGGER_FUNC_FILE_ONFLUSH_DEFAULT(_funcName_, _name_)\
  tloc::core::logging::LoggerFileOnFlush&\
    _funcName_()\
  {\
    static tloc::core::logging::LoggerFileOnFlush s_coreDefaultLogger( (#_name_) );\
    return s_coreDefaultLogger;\
  }