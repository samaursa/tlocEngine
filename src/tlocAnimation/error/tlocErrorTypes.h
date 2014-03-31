#pragma once // make VS happy (if header is not included in any cpp, VS complains)

#ifndef TLOC_ANIMATION_ERROR_TYPES_H
#define TLOC_ANIMATION_ERROR_TYPES_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/error/tlocErrorTypes.h>

namespace tloc { namespace animation { namespace error {

  enum Type
  {
    error_animation_generic = core::error::error_groups::error_animation
  };

};};};

#endif