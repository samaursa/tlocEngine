// the following macro will declare a function with the correct logger type
// that can then be defined to return a static logger (see existing usage
// in tlocCoreBase.h)

// this macro MUST be used in a global namespace and MUST be used before
#define TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT()\
namespace tloc { namespace core {\
\
  /* unfortunately, some forward declaration is needed to avoid including */ \
  /* the Logger header */ \
  namespace logger {\
\
    namespace p_logger {\
      namespace write_policy  { class Console; }\
      namespace update        { class Immediately; }\
      namespace format_policy { class Default; }\
    }\
\
    template <typename T_WritePolicy, \
              typename T_UpdatePolicy, \
              typename T_FormatPolicy> \
              class Logger_T;\
  };\
};}

#define TLOC_LOGGER_DECLARE_LOGGER_FUNC_CONSOLE_IMMEDIATE_DEFAULT(_funcName_)\
  /* use macros instead of this function for logging */ \
  tloc::core::logger::Logger_T\
    <tloc::core::logger::p_logger::write_policy::Console,\
     tloc::core::logger::p_logger::update::Immediately,\
     tloc::core::logger::p_logger::format_policy::Default>&\
     _funcName_()