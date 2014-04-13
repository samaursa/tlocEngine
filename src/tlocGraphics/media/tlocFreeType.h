#ifndef _TLOC_GRAPHICS_MEDIA_FREE_TYPE_H_
#define _TLOC_GRAPHICS_MEDIA_FREE_TYPE_H_

#include <FreeType/ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H
#include FT_MODULE_ERRORS_H

#include <tlocCore/base_classes/tlocInitializeAndDestroy.h>
#include <tlocCore/string/tlocString.h>
#include <tlocGraphics/media/tlocImage.h>

namespace tloc { namespace graphics { namespace media { namespace free_type {

  class FreeTypeGlyph
  {
    public:
      typedef FT_GlyphSlot                        ft_glyph_type;
      typedef FreeTypeGlyph                       this_type;

    public:
      FreeTypeGlyph();
      explicit FreeTypeGlyph(ft_glyph_type a_glyphToCopy);
      FreeTypeGlyph(const this_type& a_other);

      this_type& operator=(this_type a_other);

      void swap(this_type& a_other);

      TLOC_DECL_AND_DEF_GETTER(ft_glyph_type, GetGlyphSlot, m_glyph);

    private:
      ft_glyph_type   m_glyph;
  };

  class FreeType
    : core_bclass::InitializeAndDestroy_TI<FreeType,
        core_bclass::p_initialize_and_destroy::OneParam>
  {
    TLOC_DECLARE_FRIEND_INITIALIZE_AND_DESTROY_ONE_PARAM(FreeType);

  public:
    typedef FreeType                              this_type;
    typedef core_bclass::
            InitializeAndDestroy_TI<this_type,
            core_bclass::p_initialize_and_destroy::
            OneParam>                             base_type;
    typedef base_type::error_type                 error_type;

    typedef FT_Library                            ft_library_type;
    typedef FT_Face                               ft_face_type;
    typedef FT_Glyph                              ft_glyph_type;
    typedef FT_UInt                               ft_index_type;
    typedef FT_UShort                             ft_ushort;
    typedef FT_ULong                              ft_ulong;

    typedef core_str::String                      data_type;
    typedef image_sptr                            image_ptr;

  public:
    FreeType();

    bool          SetCurrentSize(ft_ushort a_charSize) const;
    FreeTypeGlyph LoadGlyph(ft_ulong a_charCode) const;

    image_ptr     GetGlyphImage(ft_ulong a_charCode, 
                                gfx_t::Color a_fontColor = gfx_t::Color::COLOR_WHITE, 
                                gfx_t::Color a_backgroundColor = gfx_t::Color::COLOR_BLACK) const;

    TLOC_USING_INITIALIZE_AND_DESTROY_METHODS();

  protected:

    error_type    DoInitialize(const data_type& a_data);
    error_type    DoDestroy();

  private:
    error_type    Destroy(); // intentionally not defined

  private:
    ft_library_type m_library;
    ft_face_type    m_face;
  };

};};};};

#endif