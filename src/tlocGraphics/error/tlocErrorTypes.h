#ifndef TLOC_GRAPHICS_ERROR_TYPES_H
#define TLOC_GRAPHICS_ERROR_TYPES_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace error {

  enum Type
  {
    error_texture_load = core::error::error_groups::error_graphics,
    error_image_decoding,
    error_image_invalid_channels,

    // Shaders
    error_shader,
    error_shader_source,
    error_shader_compile,
    error_shader_program_enable,
    error_shader_program_link,
    error_shader_uniform_name_not_found,
    error_shader_uniform_invalid_type,
    error_shader_uniform_not_attached,
    error_shader_attribute_not_attached,

    error_invalid_texture_unit,
    error_no_texture_units_available,
    error_texture_unit_limit_reached,
    error_texture_object_already_activated,
    error_texture_object_never_activated,

    error_unsupported_sprite_sheet_format,
    error_sprite_sheet_parse_error,

    error_obj_file_parse_error,
    error_obj_file_has_no_vertices,
    error_obj_file_face_vertex_has_more_than_three_indices,
    error_obj_file_invalid_vertex,
    error_obj_file_invalid_vertex_normal,
    error_obj_file_expecting_real_number_encountered_NAN,
    error_obj_file_invalid_vertex_texcoord,
    error_obj_file_face_indexing_non_existent_tex_coord,
    error_obj_corrupt_or_invalid,

    error_free_type_initialize,
    error_free_type_error_loading_font,
    error_free_type_error_setting_size,

    error_attribute_vbo_has_no_data,
    error_attribute_vbo_has_no_names,
    error_attribute_vbo_interleave_name_size_mismatch
  };

};};};

#endif