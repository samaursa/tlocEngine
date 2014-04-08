#include "tlocFont.h"

#include <tlocGraphics/media/tlocFreeType.h>

namespace tloc { namespace graphics { namespace media {

  namespace {
    const tl_int g_maxCharactersCache = 512;
  }

  // ///////////////////////////////////////////////////////////////////////
  // Font

  Font::
    Font()
    : m_ft(new ft_ptr::value_type())
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::
    ~Font()
  {
    core_sptr::algos::virtual_ptr::DeleteAndReset()(m_ft);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::image_ptr
    Font::
    GetCharImage(tl_ulong a_char, ushort a_size) const
  {
    AssertIsInitialized();
    m_ft->SetCurrentSize(a_size);
    return m_ft->GetGlyphImage(a_char);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::sprite_sheet_ul_sptr
    Font::
    GenerateSpriteSheet(BufferArgW a_characters, ushort a_size) const
  {
    TLOC_UNUSED(a_size);
    using core_str::StringW;

    typedef Image::size_type        size_type;

    StringW str = a_characters.GetPtr();
    const StringW::size_type strLength = str.length();

    // minimum cells, in RECTANGULAR formation, required to store these
    // characters
    size_type numRows = 1;
    size_type numCols = 1;
    for (size_type i = 1; i < g_maxCharactersCache; ++i)
    {
      if ( (i * i) > strLength )
      {
        numRows = i;
        for (size_type j = i; j > 0; --j)
        {
          if ( (i * j) < strLength )
          { break; }
          else
          { numCols = j; }
        }

        break;
      }
    }

    Image::dimension_type dim = core_ds::MakeTuple(numRows, numCols);

    for (size_type cols = 0; cols < dim[1]; ++cols)
    {
      for (size_type rows = 0; rows < dim[0]; ++rows)
      {
      }
    }

    return sprite_sheet_ul_sptr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::error_type
    Font::
    DoInitialize(const data_type& a_data)
  {
    return m_ft->Initialize(a_data);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::error_type
    Font::
    DoDestroy()
  {
    return ErrorSuccess;
  }

};};};

#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(tloc::graphics::media::free_type::FreeType);