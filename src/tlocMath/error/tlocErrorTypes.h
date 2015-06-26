#ifndef TLOC_MATH_ERROR_TYPES_H
#define TLOC_MATH_ERROR_TYPES_H

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/error/tlocErrorTypes.h>

namespace tloc { namespace math { namespace error {

  enum Type
  {
    error_exceeded_size_limit = core::error::error_groups::error_math,
  };

};};};

#endif
