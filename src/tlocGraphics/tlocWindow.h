#ifndef TLOC_WINDOW_H
#define TLOC_WINDOW_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocString.h"
#include "tlocCore/tlocPlatform.h"
#include "tlocCore/tlocNonCopyable.h"

#include "tlocGraphics/tlocGraphicsModes.h"

namespace tloc { namespace graphics {

  ///-------------------------------------------------------------------------
  /// Platform independent member variables
  ///-------------------------------------------------------------------------
  template <typename T_Platform> struct WindowMembers;

  ///-------------------------------------------------------------------------
  /// A window to render to.
  ///
  /// Notes: The initial implementation was influenced by SFML
  ///
  /// @sa tloc::core::NonCopyable
  ///-------------------------------------------------------------------------
  template <typename T_Platform = typename core::PlatformInfo<>::platform_type>
  class Window : public core::NonCopyable
  {
  public:
    typedef T_Platform                    platform_type;
    typedef GraphicsMode<T_Platform>      graphics_mode;
    typedef WindowMembers<T_Platform>     window_members_type;

    enum { style_none       = 0x00,
           style_titlebar   = 0x01,
           style_resize     = 0x02,
           style_close      = 0x04,
           style_fullscreen = 0x08  }; typedef u32 style_type;

    struct Properties
    {
      Properties(core::String a_title,
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

    Window();
    ~Window();

    ///-------------------------------------------------------------------------
    /// Create a window for a valid OpenGL context. This is needed when querying
    /// for OpenGL support without creating an actual window.
    ///-------------------------------------------------------------------------
    void Create();

    ///-------------------------------------------------------------------------
    /// Creates the actual window with the specified properties
    ///
    /// @param  a_mode The mode.
    /// @param  a_prop The property.
    ///-------------------------------------------------------------------------
    void Create(const graphics_mode& a_mode, const Properties& a_prop);

  protected:

    template <typename T>
    void DoCreate(core::Platform_win);
    template <typename T>
    void DoCreate(core::Platform_osx);

    //void DoCreate(core::Platform_win);
    //void DoCreate(core::Platform_osx);
    //void DoCreate(core::Platform_linux);

  protected:

    window_members_type*          m_members;
    Properties                    m_properties;
    graphics_mode                 m_graphicsMode;

  };

};};

#endif