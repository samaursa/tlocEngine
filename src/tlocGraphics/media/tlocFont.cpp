#include "tlocFont.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/utilities/tlocType.h>
#include <tlocCore/tlocAlgorithms.h>

#include <tlocGraphics/media/tlocFreeType.h>
#include <tlocMath/optimize/tlocBin.h>
#include <tlocMath/optimize/tlocBinPacker2D.h>

TLOC_DEFINE_THIS_FILE_NAME();

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    Font::Params::PaddingDim(const dim_type& a_dim)
    -> this_type&
  {
    TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(a_dim[0] == 0 || a_dim[1] == 0)
      << "Padding dimension a_dim(" << a_dim << ") cannot be 0 in x or y";

    m_paddingDim = a_dim;

    if (m_paddingDim[0] == 0) { m_paddingDim[0] = 1; }
    if (m_paddingDim[1] == 0) { m_paddingDim[1] = 1; }

    return *this;
  }

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
    m_ft->SetCurrentSize(a_params.FontSize().GetHeightInPixels());
    return m_ft->GetGlyphImage(a_char, a_params.FontColor(), a_params.BgColor());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Font::const_sprite_sheet_ptr
    Font::
    GenerateGlyphCache(BufferArgW a_characters, const Params& a_params)
  {
    struct GlyphData
    {
      image_sptr              m_img;
      BufferArgW::value_type  m_char;
    };

    TLOC_ASSERT(m_flags.IsUnMarked(k_font_cache_generated), 
                "Font cache already generated for this Font");

    using core_str::StringW;

    typedef Image::size_type          size_type;
    typedef Image::dimension_type     dim_type;

    m_cachedParams = a_params;

    StringW str = a_characters.GetPtr();
    const StringW::size_type strLength = str.length();

    sprite_sheet_ul_uptr::value_type::sprite_info_cont spriteInfo;

    spriteInfo.reserve(strLength);

    // prepare bins from the glyphs
    math_opt::bin_vso glyphBin(MakeArgs(core_ds::MakeTuple(32, 32)));
    glyphBin->SetAutoExpand(true).SetPowerOfTwo(true);

    TLOC_EXPOSE_TYPEDEFS_2(math_opt::Bin, case_type, rect_type);
    TLOC_EXPOSE_TYPEDEFS_2(rect_type, width, height);

    for (size_type i = 0; i < strLength; ++i)
    {
      DoCacheGlyphMetrics(str.at(i), m_cachedParams);

      GlyphData gd;
      gd.m_img = GetCharImage(str.at(i), m_cachedParams);

      gd.m_img->AddPadding(m_cachedParams.PaddingDim(), 
                          m_cachedParams.PaddingColor());
      gd.m_char = a_characters[i];

      rect_type r(width(gd.m_img->GetWidth()), height(gd.m_img->GetHeight()));
      glyphBin->push_back(case_type(r).SetData(gd));
    }

    TLOC_ASSERT(glyphBin->size() == strLength && glyphBin->size() == m_metrics.size(), 
                "Expected container sizes to match");

    math_opt::BinPacker2D bp(glyphBin.get());
    {
      // has to succeed due to auto expansion
      bp.Process<math_opt::GuillotineBinPack>();
    }

    auto spriteSheet = core_sptr::MakeShared<Image>();
    spriteSheet->Create(glyphBin->GetBinDimensions(), m_cachedParams.BgColor());

    tl_int counter = 0;
    core::for_each(glyphBin->begin_packed(), glyphBin->end_packed(), 
                   [&](const case_type& a_case)
    {
      auto gd   = a_case.GetData().Cast<GlyphData>();
      auto pos  = a_case.GetRectangle().GetPosition();
      auto dim  = a_case.GetRectangle().GetDimensions();
      
      sprite_info_ul si(gd.m_char, pos, dim);
      spriteInfo.push_back(si);
      spriteSheet->SetImage(pos, *gd.m_img);
      ++counter;
    });

    core::for_each_all(spriteInfo,
                       algos::transform::sprite_info::
                       ComputeTexCoords(spriteSheet->GetDimensions()));

    TLOC_ASSERT(spriteInfo.size() == glyphBin->size_packed(), 
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
    m_ft->SetCurrentSize(a_params.FontSize().GetHeightInPixels());
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