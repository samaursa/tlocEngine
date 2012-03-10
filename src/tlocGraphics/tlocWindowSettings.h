#ifndef TLOC_WINDOW_SETTINGS_H
#define TLOC_WINDOW_SETTINGS_H

#include "tlocCore/tlocString.h"

namespace tloc { namespace graphics {

  struct WindowSettings
  {
    enum { style_none       = 0x00,
           style_titlebar   = 0x01,
           style_resize     = 0x02,
           style_close      = 0x04,
           style_fullscreen = 0x08  }; typedef u32 style_type;

    WindowSettings
      (core::String a_title,
       style_type a_style = style_titlebar | style_resize | style_close,
       u32 a_depthBits = 24, u32 a_stencilBits = 8,
       u32 a_antiAlias = 0)
       : m_title(a_title)
       , m_style(a_style)
       , m_depthBits(a_depthBits)
       , m_stencilBits(a_stencilBits)
       , m_antiAlias(a_antiAlias) {}

    core::String  m_title;
    style_type    m_style;

    u32           m_depthBits;
    u32           m_stencilBits;
    u32           m_antiAlias;
  };

};};

#endif