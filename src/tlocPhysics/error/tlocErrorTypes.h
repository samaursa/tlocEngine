#pragma once
#ifndef _TLOC_PHYSICS_ERROR_TYPES_H_
#define _TLOC_PHYSICS_ERROR_TYPES_H_

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/error/tlocErrorTypes.h>

namespace tloc { namespace physics { namespace error {

  enum Type
  {
    error_rigid_body_could_not_be_allocated = core::error::error_groups::error_physics,
    error_rigid_body_shape_could_not_be_created,
    error_rigid_body_not_attached,
  };

};};};

#endif