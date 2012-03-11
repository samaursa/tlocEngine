#include "tlocWindowWin32.h"

namespace tloc { namespace graphics { namespace priv {

#ifdef TLOC_WIN64
#define WINDOW_IMPL_PARAMS core::Platform_win64
#else
#define WINDOW_IMPL_PARAMS core::Platform_win32
#endif

  WindowImpl<WINDOW_IMPL_PARAMS>::WindowImpl()
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