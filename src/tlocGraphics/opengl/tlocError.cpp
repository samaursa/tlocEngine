#include "tlocError.h"

namespace tloc { namespace graphics { namespace gl {

  bool Error::Succeeded()
  {
    return GetError() == GL_NO_ERROR;
  }

  bool Error::Failed()
  {
    return !Succeeded();
  }

  GLenum Error::GetError()
  {
    m_lastError = glGetError();
    return m_lastError;
  }

  void Error::GetErrorAsString(core::String& a_out)
  {
    GetError();
    const char* myError = reinterpret_cast<const char*>(gluErrorString(m_lastError));
    if (myError) { a_out = myError; }
  }

};};};