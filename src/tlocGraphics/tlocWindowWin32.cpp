#include "tlocWindowWin32.h"

namespace tloc { namespace graphics { namespace priv {

  WindowImpl<core::Platform_win32>::WindowImpl()
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