#include "tlocOpenGL.h"

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

      void DoGet(GLdouble&	a_out, const GLint a_paramName)
      {
        glGetDoublev(a_paramName, &a_out);
      }

      void DoGet(GLdouble*&	a_out, const GLint a_paramName)
      {
        glGetDoublev(a_paramName, a_out);
      }
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
    GLint g_maxTextureUnits = -1;
    GLint g_currentTextureUnit = 0;

    void DoSetMaxTextureUnits()
    { g_maxTextureUnits = Get<p_get::MaxCombinedTextureImageUnits>(); }
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
      { return error::error_no_texture_units_available; }

      if (g_currentTextureUnit < g_maxTextureUnits)
      {
        glActiveTexture(++g_currentTextureUnit);
        return ErrorSuccess();
      }
      else
      { return error::error_texture_unit_limit_reached; }
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