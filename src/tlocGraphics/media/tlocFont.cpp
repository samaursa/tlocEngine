#include "tlocFont.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/utilities/tlocType.h>

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

  Font::sprite_sheet_ul_vso
    Font::
    GenerateSpriteSheet(BufferArgW a_characters, Params_Font a_params) const
  {
    using core_str::StringW;

    typedef Image::size_type          size_type;
    typedef Image::dimension_type     dim_type;
    typedef sprite_info_ul::pos_type  pos_type;

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

    core_conts::Array<image_sptr>                      charImages;
    sprite_sheet_ul_uptr::value_type::sprite_info_cont spriteInfo;

    charImages.reserve(strLength);
    spriteInfo.reserve(strLength);

    dim_type maxDim(0);

    for (size_type i = 0; i < strLength; ++i)
    {
      charImages.push_back(GetCharImage(str.at(i), a_params) );
      charImages.back()->AddPadding(a_params.m_paddingDim, a_params.m_paddingColor);
      dim_type currDim = charImages.back()->GetDimensions();

      maxDim[0] = core::tlMax(maxDim[0], currDim[0]);
      maxDim[1] = core::tlMax(maxDim[1], currDim[1]);
    }

    TLOC_ASSERT(charImages.size() == strLength, 
                "Unexpected size of the charImages container");
    TLOC_ASSERT(charImages.size() <= numRows * numCols, 
                "Number of character images must not exceed number of rows/cols "
                "available");

    image_sptr spriteSheet(new Image());
    spriteSheet->
      Create(core_ds::MakeTuple(maxDim[0] * numCols, maxDim[1] * numRows),
             a_params.m_bgColor);

    for (size_type i = 0; i < charImages.size(); ++i)
    {
      core_ds::Tuple2u coord =
        core_utils::GetCoord(core_ds::MakeTuple(numCols, numRows), i);

      const pos_type imgCoord = 
        core_ds::MakeTuple(maxDim[0] * coord[0], maxDim[1] * coord[1]);

      sprite_info_ul si
        (a_characters[i], imgCoord, charImages[i]->GetDimensions());
      spriteInfo.push_back(si);

      spriteSheet->SetImage(imgCoord[0], imgCoord[1], *charImages[i]);
    }

    core::for_each_all(spriteInfo, 
                       algos::transform::sprite_info::
                       ComputeTexCoords(spriteSheet->GetDimensions()) );

    TLOC_ASSERT(spriteInfo.size() == charImages.size(), 
                "Container size mismatch - expected container sizes to be the "
                "same");

    sprite_sheet_ul_vso ss(sprite_sheet_ul_vso::value_type(spriteSheet, spriteInfo));

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