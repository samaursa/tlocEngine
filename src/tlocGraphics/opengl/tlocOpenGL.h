#ifndef TLOC_OPENGL_H
#define TLOC_OPENGL_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocTypes.h>

#include <tlocCore/error/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

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

#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL
      extern void DoGet(GLdouble&  a_out, const GLint a_paramName);
      extern void DoGet(GLdouble*& a_out, const GLint a_paramName);
#endif
    };

    struct CurrentProgram
    {
      typedef GLint value_type;
      static const value_type s_glParamName;
    };
    struct MaxCombinedTextureImageUnits
    {
      typedef GLint value_type;
      static const value_type s_glParamName;
    };
    struct MaxVertexAttribs
    {
      typedef GLint value_type;
      static const value_type s_glParamName;
    };
  };

  template <typename T_GlPName>
  typename T_GlPName::value_type
    Get()
  {
    typedef typename T_GlPName::value_type  ret_type;

    ret_type toRet;
    p_get::priv::DoGet(toRet, T_GlPName::s_glParamName);

    return toRet;
  }

  GLint                GetActiveTextureUnit();
  core_err::Error      ActivateNextAvailableTextureUnit();
  void                 ActivateTextureUnit(GLint a_texUnit);
  void                 ResetTextureUnits();

};};};

#endif