#include "tlocOpenGL.h"

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

#include <tlocGraphics/opengl/tlocError.h>

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
    const GLint MaxVertexAttribs::s_glParamName
      = GL_MAX_VERTEX_ATTRIBS;
  };

  //------------------------------------------------------------------------
  // Texture units

  namespace
  {
    typedef core_conts::tl_array<GLint>::type   gl_int_array;

    typedef core_conts::tl_array<GLint>::type   gl_int_array;

    GLint         g_maxTextureUnits = -1;
    GLint         g_currentActiveTextureUnit = 0;
    gl_int_array  g_availableTextureUnits;
    gl_int_array  g_usedTextureUnits;

    void DoSetMaxTextureUnits()
    {
      g_maxTextureUnits = Get<p_get::MaxCombinedTextureImageUnits>();

      // Prepare our array
      g_availableTextureUnits.reserve(g_maxTextureUnits);

      // Fill it backwards so that the first available texture unit is
      // GL_TEXTURE0
      for (int i = g_maxTextureUnits - 1; i >= 0; --i)
      {
        g_availableTextureUnits.push_back(GL_TEXTURE0 + i);
      }
    }
  }

  // ///////////////////////////////////////////////////////////////////////
  // Texture image unit functions
  // For clarification on Texture image units and Texture units:
  // http://www.opengl.org/wiki/Sampler_(GLSL)

  GLint
    GetActiveTextureImageUnit()
  { return g_currentActiveTextureUnit; }

  core_err::Error
    GetNextAvailableTextureImageUnit(GLint& a_texImgUnitOut)
  {
    if (g_maxTextureUnits != -1)
    {
      if (g_maxTextureUnits == 0)
      { return TLOC_ERROR(error::error_no_texture_units_available); }

      // You will want to disable some textures to get back texture units
      if (g_availableTextureUnits.size() == 0)
      { return TLOC_ERROR(error::error_texture_unit_limit_reached); }

      g_availableTextureUnits.pop_back(a_texImgUnitOut);
      g_usedTextureUnits.push_back(a_texImgUnitOut);

      TLOC_ASSERT(IsValidTextureImageUnit(a_texImgUnitOut),
        "Unable to get a correct texture unit");

      return ErrorSuccess;
    }

    DoSetMaxTextureUnits();
    return GetNextAvailableTextureImageUnit(a_texImgUnitOut);
  }

  void
    RecycleTextureImageUnit(GLint a_texImgUnit)
  {
    TLOC_ASSERT_LOW_LEVEL(IsValidTextureImageUnit(a_texImgUnit), "Invalid texture unit");

    gl_int_array::iterator itr =
      core::find_all(g_usedTextureUnits, a_texImgUnit);

    TLOC_ASSERT(itr != g_usedTextureUnits.end(),
      "Texture unit was not used and cannot be recycled");

    g_availableTextureUnits.push_back(*itr);
    g_usedTextureUnits.erase(itr);
  }

  void
    ActivateTextureImageUnit(GLint a_texImgUnit)
  {
    if (g_maxTextureUnits != -1)
    {
      TLOC_ASSERT_LOW_LEVEL(IsValidTextureImageUnit(a_texImgUnit), "Invalid texture unit");

      if (g_currentActiveTextureUnit != a_texImgUnit)
      {
        g_currentActiveTextureUnit = a_texImgUnit;
        glActiveTexture(a_texImgUnit);

        gl::Error err; TLOC_UNUSED(err);
        TLOC_ASSERT(err.Succeeded(), "glActiveTexture() failed");
      }
      return;
    }

    DoSetMaxTextureUnits();
    ActivateTextureImageUnit(a_texImgUnit);
  }

  bool
    IsValidTextureImageUnit(GLint a_texImgUnit)
  {
    return a_texImgUnit >= GL_TEXTURE0 &&
           a_texImgUnit < GL_TEXTURE0 + g_maxTextureUnits;
  }

  // ///////////////////////////////////////////////////////////////////////
  // Texture Unit functions

  bool
    IsValidTextureUnit(GLint a_texUnit)
  {
    return a_texUnit < g_maxTextureUnits;
  }

  GLint
    GetTextureUnitFromTextureImageUnit(GLint a_texImgUnit)
  {
    TLOC_ASSERT(IsValidTextureImageUnit(a_texImgUnit), "Invalid texture image unit");

    return a_texImgUnit - GL_TEXTURE0;
  }

};};};