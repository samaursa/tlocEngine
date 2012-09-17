#ifndef TLOC_GRAPHICS_ERROR_TYPES_H
#define TLOC_GRAPHICS_ERROR_TYPES_H

#include <tlocCore/types/tlocBasicTypes.h>

namespace tloc { namespace graphics { namespace error {

  enum Type
  {
    error_texture_load = core::error::error_groups::error_graphics;
  };

};};};

#endif