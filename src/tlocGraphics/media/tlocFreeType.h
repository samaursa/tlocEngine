#ifndef _TLOC_GRAPHICS_MEDIA_FREE_TYPE_H_
#define _TLOC_GRAPHICS_MEDIA_FREE_TYPE_H_

#include <FreeType/ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H
#include FT_MODULE_ERRORS_H

#include <tlocCore/base_classes/tlocInitializeAndDestroy.h>
#include <tlocCore/containers/tlocArray.h>

namespace tloc { namespace graphics { namespace media { 

  class FreeType
    : core_bclass::InitializeAndDestroy_TI<FreeType, 
        core_bclass::p_initialize_and_destroy::OneParam>
  {
    friend class core_bclass::InitializeAndDestroy_TI<FreeType>;

  public:
    typedef FreeType                              this_type;
    typedef core_bclass::
            InitializeAndDestroy_TI<this_type, 
            core_bclass::p_initialize_and_destroy::
            OneParam>                             base_type;
    typedef base_type::error_type                 error_type;

    typedef FT_Library                            ft_library_type;
    typedef FT_Face                               ft_face_type;

    typedef core_conts::Array<char8>              data_type;

  public:
    FreeType();

    TLOC_USING_INITIALIZE_AND_DESTROY_METHODS();

  protected:

    error_type  DoInitialize(const data_type& a_data);
    error_type  DoDestroy();

  private:
    ft_library_type m_library;
    ft_face_type    m_face;
  };

};};};

#endif