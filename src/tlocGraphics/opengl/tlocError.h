#ifndef TLOC_GL_ERROR_H
#define TLOC_GL_ERROR_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace gl {

  class Error
  {
  public:
    typedef GLenum      value_type;

  public:
    bool Succeeded();
    bool Failed();

    value_type GetError();
    template <typename T_String>
    void       GetErrorAsString(T_String& a_out);

  private:
    value_type m_lastError;
  };

};};};

#endif