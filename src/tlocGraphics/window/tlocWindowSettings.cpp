#include "tlocWindowSettings.h"

namespace tloc { namespace graphics { namespace win {

  // ///////////////////////////////////////////////////////////////////////
  // p_window_settings

  namespace p_window_settings {

    namespace style {
      const value_type None::s_glParamName       = 0;
      const value_type TitleBar::s_glParamName   = 1 << 0;
      const value_type Resize::s_glParamName     = 1 << 1;
      const value_type Close::s_glParamName      = 1 << 2;
      const value_type FullScreen::s_glParamName = 1 << 3;
    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // WindowSettings

  WindowSettings::
    WindowSettings(string_type a_title)
    : m_title(a_title)
    , m_styleBits(0)
  {
    using namespace p_window_settings::style;
    AddStyle<TitleBar>().AddStyle<Resize>().AddStyle<Close>();
    SetDepthBits(24);
    SetStencilBits(8);
    SetAntiAlias(0);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  WindowSettings::this_type&
    WindowSettings::ClearStyles()
  {
    m_styleBits = 0;
    return *this;
  }

};};};