#include "tlocWindowImplWin.h"

namespace tloc { namespace graphics { namespace priv {

#define WINDOW_IMPL_WIN_PARAMS core::PlatformInfo<>::platform_type
#define WINDOW_IMPL_WIN_TYPE typename WindowImpl<WINDOW_IMPL_WIN_PARAMS>

  WindowImpl<WINDOW_IMPL_WIN_PARAMS>::WindowImpl()
    : m_handle(NULL)
    , m_callbackPtr(0)
    , m_cursor(NULL)
    , m_icon(NULL)
    , m_isCursorIn(false)
    , m_deviceContext(NULL)
    , m_OpenGLContext(NULL)
  {
  }

};};};