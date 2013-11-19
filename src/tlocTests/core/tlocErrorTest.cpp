#include "tlocTestCommon.h"

#include <tlocCore/error/tlocError.h>
#include <tlocCore/error/tlocErrorTypes.h>

#include <tlocCore/string/tlocString.h>

namespace TestingPair
{
  using namespace tloc;
  using namespace core;

  error::Error ReturnError()
  {
    return TLOC_ERROR(common_error_types::error_already_initialized);
  }

  template <typename T_Config>
  void CheckExtraInfo(const error::Error& a_error, tl_int a_line,
                      const char* a_file)
  {
    CHECK(a_error.GetLineNumber() == a_line);
    CHECK(core_str::StrCmp(a_error.GetFileName(), a_file) == 0);
  }

  template <>
  void CheckExtraInfo<core_cfg::p_build_config::Release>
    (const error::Error& , tl_int, const char*)
  {
    // Release configuration does not store this information
  }

  TEST_CASE("Core/error/Error", "")
  {
    {
      error::Error err = TLOC_ERROR(common_error_types::error_success);
      // Should not crash on destruction
    }

    {
      error::Error err = TLOC_ERROR(common_error_types::error_failure);
      bool result = err == ErrorFailure; // We checked the error
      TLOC_UNUSED_2(err, result);
      // Should not crash on destruction

      // Should crash if uncommented
      // err = common_error_types::error_failure;
    }

    {
      error::Error err = TLOC_ERROR(common_error_types::error_success);
      err = TLOC_ERROR(common_error_types::error_failure);

      // Will crash unless we choose to ignore
      err.Ignore();
    }

    {
      error::Error err = TLOC_ERROR(common_error_types::error_success);
      err.Check(); // immediately check whether err code is 'success'

      // Should crash if uncommented
      // err = TLOC_ERROR(common_error_types::error_failure);
      // err.Check(); // immediately check whether err code is 'success'
    }

    {
      error::Error err = TLOC_ERROR(common_error_types::error_success);
      error::Error err2 = TLOC_ERROR(common_error_types::error_failure);

      err.swap(err2);

      CHECK(err  == common_error_types::error_failure);
      CHECK(err2 == common_error_types::error_success);

      swap(err2, err);
      CHECK(err2 == common_error_types::error_failure);
      CHECK(err  == common_error_types::error_success);
    }

    {
      error::Error err = ErrorSuccess;
      err = ReturnError();

      err.Ignore();
    }

    {
      tl_int line = 0;
      const char* file = nullptr;
      error::Error err = ErrorSuccess; line = __LINE__; file = __FILE__;
      CheckExtraInfo<core_cfg::BuildConfig::build_config_type>(err, line, file);
    }
  }
}
