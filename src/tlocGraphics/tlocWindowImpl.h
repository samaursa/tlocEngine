#ifndef TLOC_WINDOW_IMPL_H
#define TLOC_WINDOW_IMPL_H

#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocNonCopyable.h"
#include "tlocCore/tlocPlatform.h"

#include "tlocGraphicsModes.h"
#include "tlocWindowSettings.h"

namespace tloc { namespace graphics { namespace priv {

  ///-------------------------------------------------------------------------
  /// Window implementation that must be specialized for each platform
  ///-------------------------------------------------------------------------
  template <typename T_Platform> class WindowImpl;

  ///-------------------------------------------------------------------------
  /// Platform independant window code
  ///-------------------------------------------------------------------------
  template <typename T_Platform = core::PlatformInfo<>::platform_type>
  class WindowImplBase : public core::NonCopyable
  {
  public:
    typedef T_Platform                    platformt_type;
    typedef tl_size                       size_type;
    typedef GraphicsMode<platformt_type>  graphics_mode;

  public:
    WindowImplBase()
      : m_graphicsMode(graphics_mode::Properties(0, 0))
      , m_windowSettings("TLOC Window")
    {
    }

    size_type GetWidth() { return m_graphicsMode.GetProperties().m_width; }
    size_type GetHeight() { return m_graphicsMode.GetProperties().m_height; }

    const graphics_mode&   GetGraphicsMode() { return m_graphicsMode; }
    const WindowSettings&  GetWindowSettings() { return m_windowSettings; }

  protected:

    graphics_mode               m_graphicsMode;
    WindowSettings              m_windowSettings;
  };

};};};

#endif