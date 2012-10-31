#ifndef TLOC_OPENGL_H
#define TLOC_OPENGL_H

#include <tlocCore/tlocBase.h>
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

  namespace p_any
  {
    namespace priv
    {
      extern void DoGet(GLint&     a_out, tl_int a_paramName);
      extern void DoGet(GLint*&    a_out, tl_int a_paramName);
      extern void DoGet(GLfloat&   a_out, tl_int a_paramName);
      extern void DoGet(GLfloat*&  a_out, tl_int a_paramName);
      extern void DoGet(GLdouble&  a_out, tl_int a_paramName);
      extern void DoGet(GLdouble*& a_out, tl_int a_paramName);
    };

    struct CurrentProgram
    {
      typedef GLint value_type;
      static const tl_int s_glParamName;
    };
  };

  template <typename T_GlPName>
  typename T_GlPName::value_type Get()
  {
    typedef typename T_GlPName::value_type  ret_type;

    ret_type toRet;
    DoGet(&toRet, T_GlPName::s_glParamName);

    return toRet;
  }


};};};

#endif