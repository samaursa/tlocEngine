#ifndef TLOC_ERROR_TYPES_H
#define TLOC_ERROR_TYPES_H

#include <tlocCore/types/tlocBasicTypes.h>

namespace tloc { namespace core { namespace error {

  namespace error_groups
  {
    enum Type
    {
      error_common    = 0,
      error_core      = 1000,
      error_math      = 2000,
      error_graphics  = 3000,
      error_input     = 4000,
    };
  };

  // error codes type
  typedef tl_int  error_code_type;

};};};

namespace tloc {

  namespace common_error_types
  {
    enum Type
    {
      error_success                     = core::error::error_groups::error_common,
      error_failure,
      error_no_data,                    // used for NULL
      error_size_mismatch,
    };
  };

};

#endif