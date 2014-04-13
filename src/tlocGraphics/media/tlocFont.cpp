#include "tlocFont.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/utilities/tlocContainerUtils.h>

#include <tlocGraphics/media/tlocFreeType.h>

namespace tloc { namespace graphics { namespace media {

  namespace {
    const tl_int g_maxCharactersCache = 512;
  }

  // ///////////////////////////////////////////////////////////////////////
  // Params_Font

  Font::Params_Font::
    Params_Font(font_size_type a_fontSize) 
    : m_fontSize(a_fontSize)
    , m_fontColor(gfx_t::Color::COLOR_WHITE)
    , m_bgColor(gfx_t::Color::COLOR_BLACK)
    , m_paddingDim(core_ds::MakeTuple(2, 2))
    , m_paddingColor(gfx_t::Color::COLOR_BLACK)
  { }

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
    GetCharImage(tl_ulong a_char, Params_Font a_params) const
  {
    AssertIsInitialized();
    m_ft->SetCurrentSize(a_params.m_fontSize);
    return m_ft->GetGlyphImage(a_char, a_params.m_fontColor, a_params.m_bgColor);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::sprite_sheet_ul_sptr
    Font::
    GenerateSpriteSheet(BufferArgW a_characters, Params_Font a_params) const
  {
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
      charImages.push_back(GetCharImage(str.at(i), a_params) );
      charImages.back()->AddPadding(a_params.m_paddingDim, a_params.m_paddingColor);
      Image::dimension_type currDim = charImages.back()->GetDimensions();

      maxDim[0] = core::tlMax(maxDim[0], currDim[0]);
      maxDim[1] = core::tlMax(maxDim[1], currDim[1]);
    }

    TLOC_ASSERT(charImages.size() <= numRows * numCols,
      "Number of character images must not exceed number of rows/cols available");

    image_sptr spriteSheet(new Image());
    spriteSheet->
      Create(core_ds::MakeTuple(maxDim[0] * numCols, maxDim[1] * numRows),
             a_params.m_bgColor);

    sprite_sheet_ul_sptr::value_type::sprite_info_cont spriteInfo;

    for (size_type i = 0; i < charImages.size(); ++i)
    {
      core_ds::Tuple2u coord =
        core_utils::GetCoord(core_ds::MakeTuple(numCols, numRows), i);

      spriteSheet->SetImage(maxDim[0] * coord[0], 
                            maxDim[1] * coord[1], 
                            *charImages[i]);
    }

    sprite_sheet_ul_sptr 
      ss(new sprite_sheet_ul_sptr::value_type(spriteSheet, spriteInfo));

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