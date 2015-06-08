#include "tlocFreeType.h"

#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/tlocAlgorithms.h>

#include <tlocMath/tlocRange.h>
#include <tlocMath/utilities/tlocScale.h>

#include <tlocGraphics/error/tlocErrorTypes.h>

namespace {

  using namespace tloc;

  // ///////////////////////////////////////////////////////////////////////
  // FreeTypeErrors

  struct FreeTypeErrors
  {
    FreeTypeErrors()
      : m_string("Invalid Error In FreeTypeErrors")
    { }

    FreeTypeErrors(BufferArg a_string)
      : m_string(a_string)
    { }

    core_str::String    m_string;
  };

  // -----------------------------------------------------------------------

  core_conts::Array<FreeTypeErrors> g_freeTypeErrors;

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  tl_int
    DoAddFreeTypeError(tl_int a_number, BufferArg a_string)
  {
    g_freeTypeErrors.resize(a_number + 1);
    g_freeTypeErrors[a_number].m_string = a_string;
    return a_number;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BufferArg
    DoGetFreeTypeError(tl_int a_number)
  {
    return g_freeTypeErrors[a_number].m_string.c_str();
  }
};

#define FT_NOERRORDEF_(_type_, _number_, _str_)
#define FT_ERRORDEF_(_type_, _number_, _str_) \
  tl_int _type_ = DoAddFreeTypeError(_number_, _str_);

#include <FreeType/fterrdef.h>

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

  FreeType::
    ~FreeType()
  {
    base_type::Destroy();
  }

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
        << "Unable to set current font size to " << a_charSize
        << "- FreeType: " << DoGetFreeTypeError(err);

      return err == 0;
    }
    else
    { return true; }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FreeType::ft_vec
    FreeType::
    GetKerning(ft_ulong a_leftCharCode, ft_ulong a_charCode)
  {
    ft_vec delta;
    delta.x = 0;
    delta.y = 0;

    if (FT_HAS_KERNING(m_face))
    {
      ft_uint leftIndex = FT_Get_Char_Index(m_face, a_leftCharCode);
      ft_uint index = FT_Get_Char_Index(m_face, a_charCode);

      FT_Error err = FT_Get_Kerning(m_face, leftIndex, index,
                                    FT_KERNING_DEFAULT, &delta);

      TLOC_LOG_GFX_WARN_IF(err != 0)
        << "Could not get kerning for characters (" << a_leftCharCode
        << ", " << a_charCode << ") - FreeType: " << DoGetFreeTypeError(err);
    }

    return delta;
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
      TLOC_LOG_GFX_WARN_IF( err != 0 )
        << "Could not load glyph for character (" << a_charCode << ") or ("
        << core_str::StringW(1, core_utils::CastNumber<char32>(a_charCode))
        << ")- FreeType(" << err << "): "
        << DoGetFreeTypeError(err);

      return FreeTypeGlyph();
    }

    return FreeTypeGlyph(m_face->glyph);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FreeType::image_ptr
    FreeType::
    GetGlyphImage(ft_ulong a_charCode, 
                  gfx_t::Color a_fontColor,
                  gfx_t::Color a_backgroundColor) const
  {
    AssertIsInitialized();

    // scaling setup
    math::range_s32 r0to256 = math::Range0to256<s32, math::p_range::Inclusive>();
    math::range_f32 r0to1 = math::Range0to1<f32, math::p_range::Inclusive>();
    math_utils::scale_f32_s32 scale(r0to1, r0to256);

    FreeTypeGlyph g = LoadGlyph(a_charCode);

    FT_Bitmap bmp = g.GetGlyphSlot()->bitmap;
    Image::const_color_ptr bmpBuff(bmp.buffer);

    Image::pixel_container_type pixelCont;
    for (tl_int i = 0; i < bmp.width * bmp.rows; ++i)
    {
      uchar8 gc = bmpBuff.get()[i];

      const f32 fontMulti = scale.ScaleDown(gc);
      const f32 bgMulti = 1 - fontMulti;

      const gfx_t::Color finalFontColor = a_fontColor * fontMulti;
      const gfx_t::Color finalBgColor = a_backgroundColor * bgMulti;

      const gfx_t::Color finalColor = finalFontColor + finalBgColor;

      pixelCont.push_back(finalColor);
    }

    image_ptr fontImg = core_sptr::MakeShared<image_ptr::value_type>();
    fontImg->Load(pixelCont, core_ds::MakeTuple(bmp.width, bmp.rows));

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
      TLOC_LOG_GFX_ERR() 
        << "Failed to initialize FreeType"
        << " - FreeType(" << error << "): "
        << DoGetFreeTypeError(error);
      return TLOC_ERROR( gfx_err::error_free_type_initialize );
    }

    // FT_New_Memory_Face expects us to not deallocate the raw data, so we
    // need to make a copy of it.
    m_rawData = a_data;
    const FT_Byte* rawData =
      reinterpret_cast<const FT_Byte*>( m_rawData.begin() );

    error = FT_New_Memory_Face( m_library, rawData, a_data.size(), 0, &m_face );

    if ( error )
    {
      TLOC_LOG_GFX_ERR() 
        << "Failed to load font from memory"
        << " - FreeType(" << error << "): "
        << DoGetFreeTypeError(error);
      return TLOC_ERROR( gfx_err::error_free_type_error_loading_font );
    }

    error = FT_Set_Char_Size(m_face, 0, 150*64, 300, 300);

    if ( error )
    {
      TLOC_LOG_GFX_ERR() 
        << "Failed to set character size"
        << " - FreeType(" << error << "): "
        << DoGetFreeTypeError(error);
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