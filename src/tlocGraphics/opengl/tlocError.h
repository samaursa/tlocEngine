#ifndef TLOC_GL_ERROR_H
#define TLOC_GL_ERROR_H

#include <tlocCore/string/tlocString.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace gl {

  class Error
  {
  public:
    bool Succeeded();
    bool Failed();

    GLenum GetError();
    void   GetErrorAsString(core::String& a_out);

  private:
    GLenum m_lastError;
  };

};};};

#endif