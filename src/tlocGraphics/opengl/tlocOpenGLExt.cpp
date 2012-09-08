#include "tlocOpenGLExt.h"
#include "3rdParty/Graphics/GLEW/glew.h"

namespace tloc { namespace graphics {

  bool    OpenGLExt::m_initialized = false;
  tl_int  OpenGLExt::m_error       = error_none;

  OpenGLExt::OpenGLExt()
  {
  }

  OpenGLExt::error_type OpenGLExt::Initialize()
  {
    TLOC_ASSERT(m_initialized == false, "OpenGL Extensions already loaded!");

    if (!m_initialized)
    {
      GLenum err = glewInit();
      if (GLEW_OK != err)
      {
        // LOG: glewInit failed (log which GLEW error it was
        m_initialized = false;
        m_error = error_init;

        return GetLastError();
      }
      else
      {
        m_initialized = true;
        m_error = error_none;

        // LOG: OpenGL version, vendor, renderer, and number of supported
        //      extensions (use glGetString, glGetIntegerv etc.)

        return GetLastError();
      }
    }

    m_error = error_already_init;
    return GetLastError();
  }

  bool OpenGLExt::IsInitialized()
  {
    return m_initialized;
  }

  OpenGLExt::error_type OpenGLExt::GetLastError()
  {
    return m_error;
  }

};};