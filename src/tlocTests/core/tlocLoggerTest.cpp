#include "tlocTestCommon.h"

#include <tlocCore/logging/tlocLogger.h>

namespace TestingLogging
{
  using namespace tloc;
  using namespace core::logging;

  LoggerOutputImmediate lcfi("testLogger");

  TEST_CASE("core/logger", "")
  {
    TLOC_LOG_INFO(&lcfi) << "Info log";
    TLOC_LOG_DEBUG(&lcfi) << "Debug log";
    TLOC_LOG_WARN(&lcfi) << "Warning log";
    TLOC_LOG_ERR(&lcfi) << "Error log";

    lcfi.SetDisable(true);

    TLOC_LOG_INFO(&lcfi) << "SHOULD NOT DISPLAY";
    TLOC_LOG_DEBUG(&lcfi) << "SHOULD NOT DISPLAY";
    TLOC_LOG_WARN(&lcfi) << "SHOULD NOT DISPLAY";
    TLOC_LOG_ERR(&lcfi) << "SHOULD NOT DISPLAY";
  }
};