#include "tlocFont.h"

namespace tloc { namespace graphics { namespace media {

  ///
  // Font

  Font::
    Font()
    : m_ft(new FreeType())
  { }

  gfx_med::Image
    Font::
    GetCharImage(wchar_t a_char)
  {
    AssertIsInitialized();

    FreeTypeGlyph g = m_ft->LoadGlyph(a_char);

    gfx_med::Image fontImg;
    FT_Bitmap bmp = g.GetGlyphSlot()->bitmap;
    Image::const_uchar8_ptr bmpBuff(bmp.buffer);

    fontImg.LoadFromMemory(bmpBuff, core_ds::MakeTuple(bmp.width, bmp.rows), 4);

    return fontImg;
  }

  //xx

  Font::error_type
    Font::
    DoInitialize(const data_type& a_data)
  {
    return m_ft->Initialize(a_data);
  }

  Font::error_type
    Font::
    DoDestroy()
  {
    return ErrorSuccess;
  }

};};};

#include <tlocCore/smart_ptr/tlocUniquePtr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(tloc::graphics::media::FreeType);