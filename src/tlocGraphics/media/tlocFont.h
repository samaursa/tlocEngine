#ifndef _TLOC_GRAPHICS_MEDIA_FONT_H_
#define _TLOC_GRAPHICS_MEDIA_FONT_H_

#include <tlocCore/base_classes/tlocInitializeAndDestroy.h>
#include <tlocCore/string/tlocString.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocGraphics/media/tlocImage.h>
#include <tlocGraphics/media/tlocSprite.h>

namespace tloc { namespace graphics { namespace media {

  // ///////////////////////////////////////////////////////////////////////
  // FreeType forward declaration

  namespace free_type
  { class FreeType; };

  // ///////////////////////////////////////////////////////////////////////
  // GlyphMetrics

  struct GlyphMetrics
  {
    typedef GlyphMetrics                            this_type;
    typedef tl_float                                value_type;
    typedef tl_ulong                                char_code;
    typedef core_ds::Tuple<value_type, 2>           dim_type;

    TLOC_DECL_PARAM_VAR(char_code, CharCode, m_charCode);
    TLOC_DECL_PARAM_VAR(dim_type, Dimensions, m_dim);

    TLOC_DECL_PARAM_VAR(dim_type, HoriBearing, m_horizontalBearing);
    TLOC_DECL_PARAM_VAR(dim_type, VertBearing, m_verticalBearing);

    TLOC_DECL_PARAM_VAR(value_type, HoriAdvance, m_horizontalAdvance);
    TLOC_DECL_PARAM_VAR(value_type, VertAdvance, m_verticalAdvance);

    static const value_type s_pointToPixelScale;
  };

  namespace algos { namespace compare { namespace glyph_metrics {

    struct CharCode
    {
      typedef GlyphMetrics::char_code                 value_type;

      CharCode(value_type a_charCode)
        : m_charCode(a_charCode)
      { }

      bool operator()(const GlyphMetrics& a_other)
      { return m_charCode == a_other.m_charCode; }

      value_type m_charCode;
    };

  };};};

  // ///////////////////////////////////////////////////////////////////////
  // Font

  class Font
    : public core_bclass::InitializeAndDestroy_TI<Font,
             core_bclass::p_initialize_and_destroy::OneParam>
    , core_bclass::NonCopyable_I
  {
    TLOC_DECLARE_FRIEND_INITIALIZE_AND_DESTROY_ONE_PARAM(Font);

  public:
    typedef Font                                          this_type;
    typedef core_bclass::
      InitializeAndDestroy_TI<this_type,
      core_bclass::p_initialize_and_destroy::OneParam>    base_type;

    typedef core_sptr::VirtualPtr<free_type::FreeType>    ft_ptr;
    typedef core_str::String                              data_type;
    typedef core_ds::Tuple2f                              pos_type;

    typedef image_sptr                                    image_ptr;
    typedef sprite_sheet_ul_vso                           sprite_sheet_type;
    typedef const_sprite_sheet_ul_vptr                    const_sprite_sheet_ptr;

    typedef GlyphMetrics                                  glyph_metrics;
    typedef core_conts::Array<glyph_metrics>              glyph_metrics_cont;
    typedef glyph_metrics_cont::iterator                  glyph_metrics_iterator;
    typedef glyph_metrics_cont::const_iterator            const_glyph_metrics_iterator;

  public:
    struct Params
    {
      typedef Params                                      this_type;
      typedef ushort                                      font_size_type;
      typedef Image::dimension_type                       dim_type;

      explicit Params(font_size_type a_fontSize);

      TLOC_DECL_PARAM_VAR(font_size_type, FontSize, m_fontSize);
      TLOC_DECL_PARAM_VAR(gfx_t::Color, FontColor, m_fontColor);
      TLOC_DECL_PARAM_VAR(gfx_t::Color, BgColor, m_bgColor);
      TLOC_DECL_PARAM_VAR(dim_type, PaddingDim, m_paddingDim);
      TLOC_DECL_PARAM_VAR(gfx_t::Color, PaddingColor, m_paddingColor);
    };

  public:
    Font();
    ~Font();

    image_ptr               GetCharImage(tl_ulong a_char, 
                                         const Params& a_params) const;
    const_sprite_sheet_ptr  GenerateGlyphCache(BufferArgW a_characters,
                                               const Params& a_params);

    pos_type                GetKerning(tl_ulong a_leftChar, tl_ulong a_char) const;

    const_glyph_metrics_iterator  GetGlyphMetric(tl_ulong a_char) const;
    const_glyph_metrics_iterator  begin_glyph_metrics() const;
    const_glyph_metrics_iterator  end_glyph_metrics() const;

    bool                          IsCached() const;

    TLOC_DECL_AND_DEF_GETTER(const_sprite_sheet_ptr, GetSpriteSheetPtr, 
                             m_spriteSheet.get());

    TLOC_USING_INITIALIZE_AND_DESTROY_METHODS();

  protected:

    error_type    DoInitialize(const data_type& a_data);
    error_type    DoDestroy();

  private:
    error_type    Destroy(); // intentionally not defined

    void          DoCacheGlyphMetrics(tl_ulong a_char, 
                                      const Params& a_params);

  private:
    ft_ptr                    m_ft;
    glyph_metrics_cont        m_metrics;
    sprite_sheet_ul_vso       m_spriteSheet;
    core_utils::Checkpoints   m_flags;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(Font, font);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(Font, font);

};};};

#endif