#include "tlocFreeType.h"

#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/tlocAlgorithms.h>

#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace media { namespace free_type {

  // ///////////////////////////////////////////////////////////////////////
  // FreeTypeGlyph

  FreeTypeGlyph::
    FreeTypeGlyph()
    : m_glyph(nullptr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FreeTypeGlyph::
    FreeTypeGlyph(ft_glyph_type a_glyphToCopy)
    : m_glyph(a_glyphToCopy)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FreeTypeGlyph::
    FreeTypeGlyph(const this_type& a_other)
    : m_glyph(a_other.m_glyph)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FreeTypeGlyph::this_type&
    FreeTypeGlyph::
    operator=(this_type a_other)
  {
    swap(a_other);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    FreeTypeGlyph::
    swap(this_type& a_other)
  {
    using core::swap;
    swap(m_glyph, a_other.m_glyph);
  }

  // ///////////////////////////////////////////////////////////////////////
  // FreeType

  FreeType::
    FreeType()
    : m_library(nullptr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    FreeType::
    SetCurrentSize(ft_ushort a_charSize) const
  {
    AssertIsInitialized();

    const ft_ushort currentSize = m_face->size->metrics.x_ppem;

    if (currentSize != a_charSize)
    {
      FT_Error err = FT_Set_Pixel_Sizes(m_face, 0, a_charSize);

      TLOC_LOG_GFX_WARN_IF(err != 0)
        << "Unable to set current font size to: " << a_charSize;

      return err == 0;
    }
    else
    { return true; }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FreeTypeGlyph
    FreeType::
    LoadGlyph(ft_ulong a_charCode) const
  {
    AssertIsInitialized();

    FT_Error err = FT_Load_Char(m_face, a_charCode, FT_LOAD_RENDER);

    if (err)
    {
      TLOC_LOG_GFX_ERR_IF( err != 0 )
        << "Could not load glyph for character: " << a_charCode;

      return FreeTypeGlyph();
    }

    return FreeTypeGlyph(m_face->glyph);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FreeType::image_ptr
    FreeType::
    GetGlyphImage(ft_ulong a_charCode) const
  {
    AssertIsInitialized();

    FreeTypeGlyph g = LoadGlyph(a_charCode);

    FT_Bitmap bmp = g.GetGlyphSlot()->bitmap;
    Image::const_uchar8_ptr bmpBuff(bmp.buffer);

    Image::pixel_container_type pixelCont;
    for (tl_int i = 0; i < bmp.width * bmp.rows; ++i)
    {
      uchar8 gc = bmpBuff.get()[i];
      gfx_t::Color c(gc, gc, gc, gc);
      pixelCont.push_back(c);
    }

    image_ptr fontImg(new image_ptr::value_type());
    fontImg->LoadFromMemory(pixelCont, core_ds::MakeTuple(bmp.width, bmp.rows));

    return fontImg;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FreeType::error_type
    FreeType::
    DoInitialize(const data_type& a_data)
  {
    FT_Error error = FT_Init_FreeType( &m_library );
    if ( error )
    {
      TLOC_LOG_GFX_ERR() <<
        "Failed to initialize FreeType - FreeType error code: " << error;
      return TLOC_ERROR( gfx_err::error_free_type_initialize );
    }

    const FT_Byte* rawData =
      reinterpret_cast<const FT_Byte*>( a_data.begin() );

    error = FT_New_Memory_Face( m_library, rawData, a_data.size(), 0, &m_face );

    if ( error )
    {
      TLOC_LOG_GFX_ERR() <<
        "Failed to load font from memory - FreeType error code: " << error;
      return TLOC_ERROR( gfx_err::error_free_type_error_loading_font );
    }

    error = FT_Set_Char_Size(m_face, 0, 150*64, 300, 300);

    if ( error )
    {
      TLOC_LOG_GFX_ERR() <<
        "Failed to set character size - FreeType error code: " << error;
      return TLOC_ERROR( gfx_err::error_free_type_error_setting_size);
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FreeType::error_type
    FreeType::
    DoDestroy()
  {
    if (m_library)
    { FT_Done_FreeType(m_library); }

    return ErrorSuccess;
  }

};};};};

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(tloc::char8);