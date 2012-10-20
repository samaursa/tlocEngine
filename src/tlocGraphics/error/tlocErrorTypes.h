#ifndef TLOC_GRAPHICS_ERROR_TYPES_H
#define TLOC_GRAPHICS_ERROR_TYPES_H

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace error {

  enum Type
  {
    error_texture_load = core::error::error_groups::error_graphics,
    error_image_decoding,

    // API (OpenGL for now)
    error_api_invalid_handle,

    // Shaders
    error_
  };

};};};

#endif