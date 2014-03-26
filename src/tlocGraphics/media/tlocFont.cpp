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

    Image::pixel_container_type pixelCont;
    for (tl_int i = 0; i < bmp.width * bmp.rows; ++i)
    {
      uchar8 gc = bmpBuff.get()[i];
      gfx_t::Color c(gc, gc, gc, gc);
      pixelCont.push_back(c);
    }

    fontImg.LoadFromMemory(pixelCont, core_ds::MakeTuple(bmp.width, bmp.rows));

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