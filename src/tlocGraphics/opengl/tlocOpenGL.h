#ifndef TLOC_OPENGL_H
#define TLOC_OPENGL_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocTypes.h>

// Taken from SFML (we will trust the paths they chose for diff. platforms

#if defined(TLOC_WIN32) || defined(TLOC_WIN64)

# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <3rdParty/Graphics/GLEW/glew.h>
# include <GL/gl.h>
# include <GL/glu.h>

#elif defined(TLOC_LINUX)

# include <GL/gl.h>
# include <GL/glu.h>

#elif defined(TLOC_OS_MAC)

# include <OpenGL/gl.h>
# include <OpenGl/glu.h>

#elif defined(TLOC_OS_IPHONE)

# include <OpenGLES/ES2/gl.h>

#endif

namespace tloc { namespace graphics { namespace gl {

  namespace p_get
  {
    namespace priv
    {
      extern void DoGet(GLint&     a_out, const GLint a_paramName);
      extern void DoGet(GLint*&    a_out, const GLint a_paramName);
      extern void DoGet(GLfloat&   a_out, const GLint a_paramName);
      extern void DoGet(GLfloat*&  a_out, const GLint a_paramName);
      extern void DoGet(GLdouble&  a_out, const GLint a_paramName);
      extern void DoGet(GLdouble*& a_out, const GLint a_paramName);
    };

    typedef GLint value_type;

    struct CurrentProgram { static const value_type s_glParamName; };
  };

  template <typename T_GlPName>
  p_get::value_type Get()
  {
    typedef p_get::value_type  ret_type;

    ret_type toRet;
    p_get::priv::DoGet(toRet, T_GlPName::s_glParamName);

    return toRet;
  }


};};};

#endif