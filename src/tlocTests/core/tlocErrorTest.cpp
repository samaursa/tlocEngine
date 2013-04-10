#include "tlocTestCommon.h"

#include <tlocCore/error/tlocError.h>

namespace TestingPair
{
  using namespace tloc;
  using namespace core;

  TEST_CASE("Core/error/Error", "")
  {
    {
      error::Error err(common_error_types::error_success);
      // Should not crash on destruction
    }

    {
      error::Error err(common_error_types::error_failure);
      err == ErrorFailure; // We checked the error
      // Should not crash on destruction

      // Should crash if uncommented
      // err = common_error_types::error_failure;
    }

  }
}
