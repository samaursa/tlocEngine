#include "tlocOpenGL.h"

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_get
  {
    namespace priv
    {
      void DoGet(GLint& a_out, const GLint a_paramName)
      {
        glGetIntegerv(a_paramName, &a_out);
      }

      void DoGet(GLint*& a_out, const GLint a_paramName)
      {
        glGetIntegerv(a_paramName, a_out);
      }

      void DoGet(GLfloat&		a_out, const GLint a_paramName)
      {
        glGetFloatv(a_paramName, &a_out);
      }

      void DoGet(GLfloat*&	a_out, const GLint a_paramName)
      {
        glGetFloatv(a_paramName, a_out);
      }

#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL
      void DoGet(GLdouble&	a_out, const GLint a_paramName)
      {
        glGetDoublev(a_paramName, &a_out);
      }

      void DoGet(GLdouble*&	a_out, const GLint a_paramName)
      {
        glGetDoublev(a_paramName, a_out);
      }
#endif
    };

    const GLint CurrentProgram::s_glParamName
      = GL_CURRENT_PROGRAM;
    const GLint MaxCombinedTextureImageUnits::s_glParamName
      = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
  };

  //------------------------------------------------------------------------
  // Texture units

  namespace
  {
    typedef core_conts::tl_array<GLint>::type   gl_int_array;

    typedef core_conts::tl_array<GLint>::type   gl_int_array;

    GLint         g_maxTextureUnits = -1;
    GLint         g_currentTextureUnit = 0;
    gl_int_array  g_availableTextureUnits;

    void DoSetMaxTextureUnits()
    {
      g_maxTextureUnits = Get<p_get::MaxCombinedTextureImageUnits>();

      // Prepare our array
      g_availableTextureUnits.reserve(g_maxTextureUnits);
      for (int i = 0; i < g_maxTextureUnits; ++i)
      {
        g_availableTextureUnits.push_back(GL_TEXTURE0 + i);
      }
    }
  }

  GLint
    GetActiveTextureUnit()
  { return g_currentTextureUnit; }

  core_err::Error
    ActivateNextAvailableTextureUnit()
  {
    if (g_maxTextureUnits != -1)
    {
      if (g_maxTextureUnits == 0)
      { return TLOC_ERROR(error::error_no_texture_units_available); }

      ++g_currentTextureUnit;
      if (g_currentTextureUnit < g_maxTextureUnits)
      {
        glActiveTexture( g_availableTextureUnits[g_currentTextureUnit] );
        return ErrorSuccess;
      }
      else
      { return TLOC_ERROR(error::error_texture_unit_limit_reached); }
    }

    DoSetMaxTextureUnits();
    return ActivateNextAvailableTextureUnit();
  }

  void
    ActivateTextureUnit(GLint a_texUnit)
  {
    if (g_maxTextureUnits != -1)
    {
      TLOC_ASSERT_LOW_LEVEL(a_texUnit < g_maxTextureUnits,
        "Exceeded maximum texture units available");
      glActiveTexture(a_texUnit);
      return;
    }

    DoSetMaxTextureUnits();
    ActivateTextureUnit(a_texUnit);
  }

  void
    ResetTextureUnits()
  { g_currentTextureUnit = 0; }

};};};