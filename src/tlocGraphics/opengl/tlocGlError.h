#ifndef TLOC_GL_ERROR_H
#define TLOC_GL_ERROR_H

#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace gl {

  class GlError
  {
  public:
    bool Succeeded();
    bool Failed();

    GLenum GetError();
    void   GetErrorAsString();

  private:
    GLenum m_lastError;
  };

};};};

#endif