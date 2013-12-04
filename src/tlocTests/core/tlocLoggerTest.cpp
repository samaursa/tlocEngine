#include "tlocTestCommon.h"

#include <tlocCore/logger/tlocLogger.h>

namespace TestingLogging
{
  using namespace tloc;
  using namespace core::logger;

  LoggerOutputImmediate lcfi("testLogger");

  TEST_CASE("core/logger", "")
  {
    TLOC_LOG_INFO(&lcfi) << "Info log";
    TLOC_LOG_DEBUG(&lcfi) << "Debug log";
    TLOC_LOG_WARN(&lcfi) << "Warning log";
    TLOC_LOG_ERR(&lcfi) << "Error log";
  }
};