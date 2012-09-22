#include "tlocOpenGLExt.h"
#include "3rdParty/Graphics/GLEW/glew.h"

namespace tloc { namespace graphics {

  bool                  OpenGLExt::m_initialized = false;
  OpenGLExt::error_type OpenGLExt::m_error = common_error_types::error_success;

  OpenGLExt::OpenGLExt()
  {
  }

  OpenGLExt::error_type OpenGLExt::Initialize()
  {
    if (!m_initialized)
    {
      GLenum err = glewInit();
      if (GLEW_OK != err)
      {
        // LOG: glewInit failed (log which GLEW error it was
        m_initialized = false;
        m_error = common_error_types::error_initialize;

        return GetLastError();
      }
      else
      {
        m_initialized = true;
        m_error = common_error_types::error_success;

        // LOG: OpenGL version, vendor, renderer, and number of supported
        //      extensions (use glGetString, glGetIntegerv etc.)

        return GetLastError();
      }
    }

    // LOG: GLEW already initialized
    m_error = common_error_types::error_already_initialized;
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