#include "tlocTestCommon.h"

#include <tlocCore/logging/tlocLogger.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace TestingLogging
{
  using namespace tloc;
  using namespace core::logging;

  LoggerOutputImmediate lcfi("testLogger");

  TEST_CASE("core/logger", "")
  {
    TLOC_LOG_INFO(&lcfi) << "Info log";
    TLOC_LOG_SUCCESS(&lcfi) << "Success log";
    TLOC_LOG_DEBUG(&lcfi) << "Debug log";
    TLOC_LOG_WARN(&lcfi) << "Warning log";
    TLOC_LOG_ERR(&lcfi) << "Error log";

    lcfi.SetDisable(true);

    TLOC_LOG_INFO(&lcfi) << "SHOULD NOT DISPLAY";
    TLOC_LOG_DEBUG(&lcfi) << "SHOULD NOT DISPLAY";
    TLOC_LOG_WARN(&lcfi) << "SHOULD NOT DISPLAY";
    TLOC_LOG_ERR(&lcfi) << "SHOULD NOT DISPLAY";

    lcfi.SetDisable(false);
    lcfi.SetSeverity(Log::k_warning);

    TLOC_LOG_INFO(&lcfi) << "Should NOT display";
    TLOC_LOG_DEBUG(&lcfi) << "Should NOT display";
    TLOC_LOG_WARN(&lcfi) << "Should display";
    TLOC_LOG_ERR(&lcfi) << "Should display";

    TLOC_LOG_WARN_FILENAME_ONLY(&lcfi) << "only filename displayed";

    s32 i = 1;

    TLOC_LOG_SUCCESS_IF(i == 1, &lcfi) << "Should display";
    TLOC_LOG_SUCCESS_IF(i == 2, &lcfi) << "Should NOT display";

    TLOC_LOG_WARN_IF(i == 1, &lcfi) << "Should display";
    TLOC_LOG_WARN_IF(i == 2, &lcfi) << "SHOULD NOT display";

    TLOC_LOG_INFO_IF(i == 2, &lcfi) << "SHOULD NOT display";
    TLOC_LOG_DEBUG_IF(i == 2, &lcfi) << "SHOULD NOT display";
    TLOC_LOG_ERR_IF(i == 2, &lcfi) << "SHOULD NOT display";

    TLOC_LOG_INFO_FILENAME_ONLY_IF(i == 2, &lcfi) << "SHOULD NOT display";
    TLOC_LOG_DEBUG_FILENAME_ONLY_IF(i == 2, &lcfi) << "SHOULD NOT display";
    TLOC_LOG_WARN_FILENAME_ONLY_IF(i == 2, &lcfi) << "SHOULD NOT display";
    TLOC_LOG_ERR_FILENAME_ONLY_IF(i == 2, &lcfi) << "SHOULD NOT display";

    TLOC_LOG_INFO_NO_FILENAME_IF(i == 2, &lcfi) << "SHOULD NOT display";
    TLOC_LOG_DEBUG_NO_FILENAME_IF(i == 2, &lcfi) << "SHOULD NOT display";
    TLOC_LOG_WARN_NO_FILENAME_IF(i == 2, &lcfi) << "SHOULD NOT display";
    TLOC_LOG_ERR_NO_FILENAME_IF(i == 2, &lcfi) << "SHOULD NOT display";
  }
};

#include <tlocCore/logging/tlocDefaultLogger.h>

namespace TestDefaultLogging
{
  TEST_CASE("tloc/default_logger", "")
  {
    TLOC_LOG_DEFAULT_INFO() << "Default Logger test";
  }
};