#ifndef TLOC_GRAPHICS_ERROR_TYPES_H
#define TLOC_GRAPHICS_ERROR_TYPES_H

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace error {

  enum Type
  {
    error_texture_load = core::error::error_groups::error_graphics,
    error_image_decoding,

    // Shaders
    error_shader_source,
    error_shader_compile,
    error_shader_program_link,

  };

};};};

#endif