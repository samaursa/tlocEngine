#include "tlocTestCommon.h"

#include <tlocCore/error/tlocError.h>
#include <tlocCore/error/tlocErrorTypes.h>

namespace TestingPair
{
  using namespace tloc;
  using namespace core;

  error::Error ReturnError()
  {
    return common_error_types::error_already_initialized;
  }

  TEST_CASE("Core/error/Error", "")
  {
    {
      error::Error err(common_error_types::error_success);
      // Should not crash on destruction
    }

    {
      error::Error err(common_error_types::error_failure);
      err == ErrorFailure; // We checked the error
      TLOC_UNUSED(err);
      // Should not crash on destruction

      // Should crash if uncommented
      // err = common_error_types::error_failure;
    }

    {
      error::Error err(common_error_types::error_success);
       err = common_error_types::error_failure;

       // Will crash but unless we choose to ignore
       err.Ignore();
    }

    {
      error::Error err = ErrorSuccess;
      err = ReturnError();

      err.Ignore();
    }
  }
}
