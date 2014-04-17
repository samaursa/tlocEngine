#include "tlocFont.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/utilities/tlocType.h>

#include <tlocGraphics/media/tlocFreeType.h>

namespace tloc { namespace graphics { namespace media {

  namespace {
    const tl_int g_maxCharactersCache = 512;

    enum
    {
      k_font_cache_generated = 0,
      k_count
    };
  }

  // ///////////////////////////////////////////////////////////////////////
  // GlyphMetrics

  const GlyphMetrics::value_type
    GlyphMetrics::s_pointToPixelScale = 1.0f / 64.0f;

  // ///////////////////////////////////////////////////////////////////////
  // Params_Font

  Font::Params::
    Params(font_size_type a_fontSize) 
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
    : m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::
    ~Font()
  { 
    base_type::Destroy();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::image_ptr
    Font::
    GetCharImage(tl_ulong a_char, const Params& a_params) const
  {
    AssertIsInitialized();
    m_ft->SetCurrentSize(a_params.m_fontSize);
    return m_ft->GetGlyphImage(a_char, a_params.m_fontColor, a_params.m_bgColor);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::const_sprite_sheet_ptr
    Font::
    GenerateGlyphCache(BufferArgW a_characters, const Params& a_params)
  {
    TLOC_ASSERT(m_flags.IsUnMarked(k_font_cache_generated), 
                "Font cache already generated for this Font");

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
      DoCacheGlyphMetrics(str.at(i), a_params);
      charImages.push_back(GetCharImage(str.at(i), a_params) );
      charImages.back()->AddPadding(a_params.m_paddingDim, a_params.m_paddingColor);
      dim_type currDim = charImages.back()->GetDimensions();

      maxDim[0] = core::tlMax(maxDim[0], currDim[0]);
      maxDim[1] = core::tlMax(maxDim[1], currDim[1]);
    }

    TLOC_ASSERT(charImages.size() == strLength && 
                charImages.size() == m_metrics.size(), 
                "Expected container sizes to match");
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

    sprite_sheet_ul_vso ss( MakeArgs(spriteSheet, spriteInfo) );
    m_spriteSheet = ss;

    m_flags.Mark(k_font_cache_generated);

    return m_spriteSheet.get();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::pos_type
    Font::
    GetKerning(tl_ulong a_leftChar, tl_ulong a_char) const
  {
    glyph_metrics::value_type s = glyph_metrics::s_pointToPixelScale;

    free_type::FreeType::ft_vec delta = m_ft->GetKerning(a_leftChar, a_char);
    return core_ds::MakeTuple( delta.x * s, delta.y * s);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::const_glyph_metrics_iterator
    Font::
    GetGlyphMetric(tl_ulong a_char) const
  {
    return core::find_if_all(m_metrics, 
                             algos::compare::glyph_metrics::CharCode(a_char));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::const_glyph_metrics_iterator
    Font::begin_glyph_metrics() const
  {
    return m_metrics.begin();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::const_glyph_metrics_iterator
    Font::end_glyph_metrics() const
  {
    return m_metrics.end();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Font::
    IsCached() const
  {
    return m_flags.IsMarked(k_font_cache_generated);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::error_type
    Font::
    DoInitialize(const data_type& a_data)
  {
    m_ft.reset(new ft_ptr::value_type());
    return m_ft->Initialize(a_data);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::error_type
    Font::
    DoDestroy()
  {
    if (m_ft)
    { core_sptr::algos::virtual_ptr::DeleteAndReset()(m_ft); }
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Font::
    DoCacheGlyphMetrics(tl_ulong a_char, const Params& a_params)
  {
    m_ft->SetCurrentSize(a_params.m_fontSize);
    free_type::FreeTypeGlyph ftg = m_ft->LoadGlyph(a_char);

    FT_Glyph_Metrics ftMetrics = ftg.GetGlyphSlot()->metrics;

    glyph_metrics::value_type s = glyph_metrics::s_pointToPixelScale;

    GlyphMetrics metrics;
    metrics.CharCode(a_char)
           .Dimensions(core_ds::MakeTuple( ftMetrics.width * s, ftMetrics.height * s))
           .HoriBearing(core_ds::MakeTuple( ftMetrics.horiBearingX * s, ftMetrics.horiBearingY * s))
           .VertBearing(core_ds::MakeTuple( ftMetrics.vertBearingX * s, ftMetrics.vertBearingY * s))
           .HoriAdvance( ftMetrics.horiAdvance * s )
           .VertAdvance( ftMetrics.vertAdvance * s );

    m_metrics.push_back(metrics);
  }

};};};

using namespace tloc::gfx_med;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(free_type::FreeType);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Font);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(Font);

#include <tlocCore/containers/tlocArray.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Font::glyph_metrics);