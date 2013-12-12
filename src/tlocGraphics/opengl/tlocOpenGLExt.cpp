#include "tlocOpenGLExt.h"
#include "3rdParty/Graphics/GLEW/glew.h"
#include <tlocCore/logging/tlocLogger.h>

namespace tloc { namespace graphics { namespace gl {

  bool                  OpenGLExt::m_initialized = false;
  OpenGLExt::error_type OpenGLExt::m_error =
    TLOC_ERROR(common_error_types::error_success);

  OpenGLExt::OpenGLExt()
  { }

  OpenGLExt::error_type OpenGLExt::Initialize()
  {
    if (!m_initialized)
    {
      GLenum err = glewInit();
      if (GLEW_OK != err)
      {
        TLOC_LOG_GFX_ERR() << "glewInit failed: " << err;
        m_initialized = false;
        m_error = TLOC_ERROR(common_error_types::error_initialize);

        return GetLastError();
      }
      else
      {
        m_initialized = true;
        m_error = TLOC_ERROR(common_error_types::error_success);

        return GetLastError();
      }
    }

    TLOC_LOG_GFX_WARN() << "GLEW already initialized";
    m_error = TLOC_ERROR(common_error_types::error_already_initialized);
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

};};};