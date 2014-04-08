#include "tlocFont.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/utilities/tlocContainerUtils.h>

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

    core_conts::Array<image_sptr>    charImages;
    charImages.reserve(strLength);

    Image::dimension_type maxDim(0);

    for (size_type i = 0; i < strLength; ++i)
    {
      charImages.push_back(GetCharImage(str.at(i), a_size) );
      charImages.back()->AddPadding(core_ds::MakeTuple(1, 1), gfx_t::Color::COLOR_BLACK);
      Image::dimension_type currDim = charImages.back()->GetDimensions();

      maxDim[0] = core::tlMax(maxDim[0], currDim[0]);
      maxDim[1] = core::tlMax(maxDim[1], currDim[1]);
    }

    TLOC_ASSERT(charImages.size() <= numRows * numCols,
      "Number of character images must not exceed number of rows/cols available");

    image_sptr spriteSheet(new Image());
    spriteSheet->
      Create(core_ds::MakeTuple(maxDim[0] * numCols, maxDim[1] * numRows),
             gfx_t::Color::COLOR_BLACK);

    for (size_type i = 0; i < charImages.size(); ++i)
    {
      core_ds::Tuple2u coord =
        core_utils::GetCoord(core_ds::MakeTuple(numCols, numRows), i);

      spriteSheet->SetImage(maxDim[0] * coord[0], maxDim[1] * coord[1], *charImages[i]);
    }

    //for (size_type cols = 0; cols < numCols; ++cols)
    //{
    //  for (size_type rows = 0; rows < numRows; ++rows)
    //  {
    //    tl_int index = core_utils::GetIndex(core_ds::MakeTuple(numRows, numCols),
    //                                        core_ds::MakeTuple(rows, cols));

    //    spriteSheet->SetImage(rows * maxDim[0], cols * maxDim[1],
    //                          *charImages[index]);
    //  }
    //}

    sprite_sheet_ul_sptr::value_type::sprite_info_cont empty;

    sprite_sheet_ul_sptr ss(new sprite_sheet_ul_sptr::value_type(spriteSheet, empty));

    return ss;
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