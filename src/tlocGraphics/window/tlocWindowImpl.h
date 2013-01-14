#ifndef TLOC_WINDOW_IMPL_H
#define TLOC_WINDOW_IMPL_H

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/platform/tlocPlatform.h>

#include <tlocGraphics/window/tlocGraphicsModes.h>
#include <tlocGraphics/window/tlocWindowSettings.h>

namespace tloc { namespace graphics { namespace win { namespace priv {

  ///-------------------------------------------------------------------------
  /// Window implementation that must be specialized for each platform
  ///-------------------------------------------------------------------------
  template <class T_ParentWindow> class WindowImpl;

  ///-------------------------------------------------------------------------
  /// Platform independant window code
  ///-------------------------------------------------------------------------
  template <class T_ParentWindow>
  class WindowImplBase : public core::NonCopyable
  {
  public:
    typedef T_ParentWindow                             parent_window_type;
    typedef typename parent_window_type::platform_type platform_type;
    typedef tl_size                                    size_type;
    typedef GraphicsMode<platform_type>                graphics_mode;

  public:
    WindowImplBase(parent_window_type* a_parent)
      : m_graphicsMode(typename graphics_mode::Properties(0, 0))
      , m_windowSettings("TLOC Window")
      , m_parentWindow(a_parent)
    {
    }

    size_type GetWidth() { return m_graphicsMode.GetProperties().m_width; }
    size_type GetHeight() { return m_graphicsMode.GetProperties().m_height; }

    const graphics_mode&   GetGraphicsMode() const { return m_graphicsMode; }
    const WindowSettings&  GetWindowSettings() const { return m_windowSettings; }

  protected:

    graphics_mode               m_graphicsMode;
    WindowSettings              m_windowSettings;
    parent_window_type*         m_parentWindow;
  };

};};};};

#endif