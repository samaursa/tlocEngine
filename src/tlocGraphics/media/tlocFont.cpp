#include "tlocFont.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/tlocAlgorithms.h>

#include <tlocGraphics/media/tlocFreeType.h>
#include <tlocMath/optimize/tlocBin.h>
#include <tlocMath/optimize/tlocBinPacker2D.h>

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
    : m_cachedParams( FontSize(FontSize::pixels(0)) )
    , m_flags(k_count)
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
    m_ft->SetCurrentSize(a_params.m_fontSize.GetHeightInPixels());
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

    m_cachedParams = a_params;

    StringW str = a_characters.GetPtr();
    const StringW::size_type strLength = str.length();

    core_conts::Array<image_sptr>                      charImages;
    sprite_sheet_ul_uptr::value_type::sprite_info_cont spriteInfo;

    charImages.reserve(strLength);
    spriteInfo.reserve(strLength);

    for (size_type i = 0; i < strLength; ++i)
    {
      DoCacheGlyphMetrics(str.at(i), m_cachedParams);
      charImages.push_back(GetCharImage(str.at(i), m_cachedParams) );
      charImages.back()->AddPadding(m_cachedParams.m_paddingDim, 
                                    m_cachedParams.m_paddingColor);
    }

    TLOC_ASSERT(charImages.size() == strLength && 
                charImages.size() == m_metrics.size(), 
                "Expected container sizes to match");

    // prepare bins from the glyphs
    TLOC_EXPOSE_TYPEDEFS_2(math_opt::Bin, case_type, rect_type);
    TLOC_EXPOSE_TYPEDEFS_2(rect_type, width, height);

    math_opt::bin_vso glyphBin(MakeArgs(core_ds::MakeTuple(32, 32)));
    glyphBin->SetAutoExpand(true).SetPowerOfTwo(true);

    core::for_each_all(charImages, [&] (const image_sptr& a_charImg)
    {
      rect_type r(width(a_charImg->GetWidth()), height(a_charImg->GetHeight()));
      glyphBin->push_back(case_type(r).SetData(a_charImg));
    });

    math_opt::BinPacker2D bp(glyphBin.get());
    {
      // has to succeed due to auto expansion
      bp.Process<math_opt::GuillotineBinPack>();
    }

    auto spriteSheet = core_sptr::MakeShared<Image>();
    spriteSheet->Create(glyphBin->GetBinDimensions());

    core::for_each(glyphBin->begin_packed(), glyphBin->end_packed(), 
                   [&](const case_type& a_case)
    {
      auto imgData = a_case.GetData().Cast<image_sptr>();
      const auto& pos     = a_case.GetRectangle().GetPosition();
      const auto& dim     = a_case.GetRectangle().GetDimensions();
      
      sprite_info_ul si(imgData, pos, dim);
      spriteInfo.push_back(si);
      spriteSheet->SetImage(pos, *imgData);
    });

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
    m_ft = core_sptr::MakeUnique<ft_ptr::value_type>();
    return m_ft->Initialize(a_data);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::error_type
    Font::
    DoDestroy()
  {
    m_ft.reset();
    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Font::
    DoCacheGlyphMetrics(tl_ulong a_char, const Params& a_params)
  {
    m_ft->SetCurrentSize(a_params.m_fontSize.GetHeightInPixels());
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
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(free_type::FreeType);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Font);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(Font);

#include <tlocCore/containers/tlocArray.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(Font::glyph_metrics);