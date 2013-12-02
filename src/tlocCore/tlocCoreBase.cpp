#include "tlocCoreBase.h"

#include <tlocCore/logger/tlocLogger.h>

TLOC_FORWARD_DECLARE_LOGGER_CONSOLE_IMMEDIATE_DEFAULT();

namespace tloc { namespace core {

  // -----------------------------------------------------------------------
  // free functions

  using namespace logger;

  LoggerConsoleImmediate&
    GetLogger()
  {
    static logger::LoggerConsoleImmediate s_coreDefaultLogger( ("core") );
    return s_coreDefaultLogger;
  }

};};