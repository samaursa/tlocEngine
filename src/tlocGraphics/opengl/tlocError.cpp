#include "tlocError.h"

namespace tloc { namespace graphics { namespace gl {

  bool GlError::Succeeded()
  {
    return GetError() == GL_NO_ERROR;
  }

  bool GlError::Failed()
  {
    return !Succeeded();
  }

  GLenum GlError::GetError()
  {
    m_lastError = glGetError();
    return m_lastError;
  }

};};};