#ifndef TLOC_WINDOW_SETTINGS_H
#define TLOC_WINDOW_SETTINGS_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/utilities/tlocUtils.h>

namespace tloc { namespace graphics { namespace win {

  namespace p_window_settings
  {
    namespace style
    {
      typedef tl_int                    value_type;

      struct None       { static const value_type s_glParamName; };
      struct TitleBar   { static const value_type s_glParamName; };
      struct Resize     { static const value_type s_glParamName; };
      struct Close      { static const value_type s_glParamName; };
      struct FullScreen { static const value_type s_glParamName; };
    };
  };

  struct WindowSettings
  {
  public:
    typedef WindowSettings                        this_type;
    typedef core::string::String                  string_type;
    typedef p_window_settings::style::value_type  style_type;
    typedef u32                                   depth_bits_type;
    typedef u32                                   stencil_bits_type;
    typedef u32                                   anti_alias_type;

  public:
    WindowSettings(string_type a_title);

    template <typename T_Style>
    this_type& AddStyle();
    this_type& ClearStyles();
    TLOC_DECL_AND_DEF_GETTER(style_type, GetStyleBits, m_styleBits);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetTitle, m_title);
    TLOC_DECL_AND_DEF_SETTER_CHAIN(string_type, SetTitle, m_title);

    TLOC_DECL_AND_DEF_GETTER(depth_bits_type, GetDepthBits, m_depthBits);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(depth_bits_type, SetDepthBits, m_depthBits);

    TLOC_DECL_AND_DEF_GETTER (stencil_bits_type, GetStencilBits, m_stencilBits);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN
      (stencil_bits_type, SetStencilBits, m_stencilBits);

    TLOC_DECL_AND_DEF_GETTER(anti_alias_type, GetAntiAlias, m_antiAlias);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(anti_alias_type, SetAntiAlias, m_antiAlias);

  private:
    string_type         m_title;
    style_type          m_styleBits;

    depth_bits_type     m_depthBits;
    stencil_bits_type   m_stencilBits;
    anti_alias_type     m_antiAlias;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_Style>
  WindowSettings::this_type&
    WindowSettings::
    AddStyle()
  {
    using namespace p_window_settings::style;

    tloc::type_traits::AssertTypeIsSupported
      <T_Style, None, TitleBar, Resize, Close, FullScreen>();

    m_styleBits |= T_Style::s_glParamName;
    return *this;
  }

};};};

#endif