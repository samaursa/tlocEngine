#ifndef TLOC_GL_ERROR_H
#define TLOC_GL_ERROR_H

#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics {

  class GlError
  {
  public:
    bool Succeeded();
    bool Failed();

    GLenum GetError();

  private:
    GLenum m_lastError;
  };

};};

#endif