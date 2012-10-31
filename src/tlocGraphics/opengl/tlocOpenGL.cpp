#include "tlocOpenGL.h"

namespace tloc { namespace graphics { namespace gl {

  namespace p_any
  {
    namespace priv
    {
      void DoGet(GLint& a_out, tl_int a_paramName)
      {
        glGetIntegerv(a_paramName, &a_out);
      }

      void DoGet(GLint*& a_out, tl_int a_paramName)
      {
        glGetIntegerv(a_paramName, a_out);
      }

      void DoGet(GLfloat&		a_out, tl_int a_paramName)
      {
        glGetFloatv(a_paramName, &a_out);
      }

      void DoGet(GLfloat*&	a_out, tl_int a_paramName)
      {
        glGetFloatv(a_paramName, a_out);
      }

      void DoGet(GLdouble&	a_out, tl_int a_paramName)
      {
        glGetDoublev(a_paramName, &a_out);
      }

      void DoGet(GLdouble*&	a_out, tl_int a_paramName)
      {
        glGetDoublev(a_paramName, a_out);
      }
    };

    const tl_int CurrentProgram::s_glParamName = GL_CURRENT_PROGRAM;
  };

  //------------------------------------------------------------------------
  // Explicit Any instantiations

};};};