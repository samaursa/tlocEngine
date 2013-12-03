#include "tlocTestCommon.h"

#include <tlocCore/logger/tlocLogger.h>

namespace TestingLogging
{
  using namespace tloc;
  using namespace core::logger;

  LoggerOutputImmediate lcfi("testLogger");

  TEST_CASE("core/logger", "")
  {
    TLOC_LOG_INFO(&lcfi) << "Testing";

    TLOC_LOG_CORE_INFO() << "Testing logger: " << 1 << ", " << 1.0f;
    TLOC_LOG_CORE_INFO() << "Testing logger: " << 2 << ", " << 2.0f;
    TLOC_LOG_CORE_INFO() << "Testing logger: " << 3 << ", " << 3.0f;
  }
};