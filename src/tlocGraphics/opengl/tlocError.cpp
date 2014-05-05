#include "tlocError.h"
#include <tlocCore/string/tlocString.h>
#include <tlocCore/configs/tlocBuildConfig.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace gl {

#if !defined(__glu_h__) && !defined(__GLU_h__)

  //------------------------------------------------------------------------
  // Free defines

  // Newer OpenGL will not have a built in stack
#ifndef GL_STACK_OVERFLOW
#define GL_STACK_OVERFLOW                  GL_NO_ERROR
#endif

#ifndef GL_STACK_UNDERFLOW
#define GL_STACK_UNDERFLOW                 GL_NO_ERROR
#endif

  /* ErrorCode */
#define GLU_INVALID_ENUM                   100900
#define GLU_INVALID_VALUE                  100901
#define GLU_OUT_OF_MEMORY                  100902
#define GLU_INCOMPATIBLE_GL_VERSION        100903
#define GLU_INVALID_OPERATION              100904

  /* TessError */
#define GLU_TESS_ERROR1                    100151
#define GLU_TESS_ERROR2                    100152
#define GLU_TESS_ERROR3                    100153
#define GLU_TESS_ERROR4                    100154
#define GLU_TESS_ERROR5                    100155
#define GLU_TESS_ERROR6                    100156
#define GLU_TESS_ERROR7                    100157
#define GLU_TESS_ERROR8                    100158
#define GLU_TESS_MISSING_BEGIN_POLYGON     100151
#define GLU_TESS_MISSING_BEGIN_CONTOUR     100152
#define GLU_TESS_MISSING_END_POLYGON       100153
#define GLU_TESS_MISSING_END_CONTOUR       100154
#define GLU_TESS_COORD_TOO_LARGE           100155
#define GLU_TESS_NEED_COMBINE_CALLBACK     100156

  /* NurbsError */
#define GLU_NURBS_ERROR1                   100251
#define GLU_NURBS_ERROR2                   100252
#define GLU_NURBS_ERROR3                   100253
#define GLU_NURBS_ERROR4                   100254
#define GLU_NURBS_ERROR5                   100255
#define GLU_NURBS_ERROR6                   100256
#define GLU_NURBS_ERROR7                   100257
#define GLU_NURBS_ERROR8                   100258
#define GLU_NURBS_ERROR9                   100259
#define GLU_NURBS_ERROR10                  100260
#define GLU_NURBS_ERROR11                  100261
#define GLU_NURBS_ERROR12                  100262
#define GLU_NURBS_ERROR13                  100263
#define GLU_NURBS_ERROR14                  100264
#define GLU_NURBS_ERROR15                  100265
#define GLU_NURBS_ERROR16                  100266
#define GLU_NURBS_ERROR17                  100267
#define GLU_NURBS_ERROR18                  100268
#define GLU_NURBS_ERROR19                  100269
#define GLU_NURBS_ERROR20                  100270
#define GLU_NURBS_ERROR21                  100271
#define GLU_NURBS_ERROR22                  100272
#define GLU_NURBS_ERROR23                  100273
#define GLU_NURBS_ERROR24                  100274
#define GLU_NURBS_ERROR25                  100275
#define GLU_NURBS_ERROR26                  100276
#define GLU_NURBS_ERROR27                  100277
#define GLU_NURBS_ERROR28                  100278
#define GLU_NURBS_ERROR29                  100279
#define GLU_NURBS_ERROR30                  100280
#define GLU_NURBS_ERROR31                  100281
#define GLU_NURBS_ERROR32                  100282
#define GLU_NURBS_ERROR33                  100283
#define GLU_NURBS_ERROR34                  100284
#define GLU_NURBS_ERROR35                  100285
#define GLU_NURBS_ERROR36                  100286
#define GLU_NURBS_ERROR37                  100287

  static const char8* gluNurbsErrors[]=
  {
    " ",
    "spline order un-supported",
    "too few knots",
    "valid knot range is empty",
    "decreasing knot sequence knot",
    "knot multiplicity greater than order of spline",
    "gluEndCurve() must follow gluBeginCurve()",
    "gluBeginCurve() must precede gluEndCurve()",
    "missing or extra geometric data",
    "can't draw piecewise linear trimming curves",
    "missing or extra domain data",
    "missing or extra domain data",
    "gluEndTrim() must precede gluEndSurface()",
    "gluBeginSurface() must precede gluEndSurface()",
    "curve of improper type passed as trim curve",
    "gluBeginSurface() must precede gluBeginTrim()",
    "gluEndTrim() must follow gluBeginTrim()",
    "gluBeginTrim() must precede gluEndTrim()",
    "invalid or missing trim curve",
    "gluBeginTrim() must precede gluPwlCurve()",
    "piecewise linear trimming curve referenced twice",
    "piecewise linear trimming curve and nurbs curve mixed",
    "improper usage of trim data type",
    "nurbs curve referenced twice",
    "nurbs curve and piecewise linear trimming curve mixed",
    "nurbs surface referenced twice",
    "invalid property",
    "gluEndSurface() must follow gluBeginSurface()",
    "intersecting or misoriented trim curves",
    "intersecting trim curves",
    "UNUSED",
    "unconnected trim curves",
    "unknown knot error",
    "negative vertex count encountered",
    "negative byte-stride encounteed",
    "unknown type descriptor",
    "null control point reference",
    "duplicate point on piecewise linear trimming curve",
  };

  static const char8* gluTessErrors[]=
  {
    " ",
    "gluTessBeginPolygon() must precede a gluTessEndPolygon()",
    "gluTessBeginContour() must precede a gluTessEndContour()",
    "gluTessEndPolygon() must follow a gluTessBeginPolygon()",
    "gluTessEndContour() must follow a gluTessBeginContour()",
    "a coordinate is too large",
    "need combine callback",
  };

  struct ErrorCodeAndString
  {
    gfx_t::gl_uint  m_errorCode;
    const char8*    m_errorString;
  };

  static const ErrorCodeAndString errors[]=
  {
    /* GL */
    {GL_NO_ERROR, "no error"},
    {GL_INVALID_ENUM, "invalid enumerant"},
    {GL_INVALID_VALUE, "invalid value"},
    {GL_INVALID_OPERATION, "invalid operation"},
    {GL_STACK_OVERFLOW, "stack overflow"},
    {GL_STACK_UNDERFLOW, "stack underflow"},
    {GL_OUT_OF_MEMORY, "out of memory"},

    /* GLU */
    { GLU_INVALID_ENUM, "invalid enumerant"},
    { GLU_INVALID_VALUE, "invalid value"},
    { GLU_OUT_OF_MEMORY, "out of memory"},
    { GLU_INCOMPATIBLE_GL_VERSION, "incompatible gl version"},
    { GLU_INVALID_OPERATION, "invalid operation"},
    { TLOC_NULL, TLOC_NULL} /* end of list indicator */
  };

  //------------------------------------------------------------------------
  // Free functions

  const char8* GetErrorString(GLenum a_errorCode)
  {
    for (tl_size i = 0; errors[i].m_errorString; ++i)
    {
      if (errors[i].m_errorCode == a_errorCode)
      {
        return errors[i].m_errorString;
      }
    }

    if ((a_errorCode >= GLU_NURBS_ERROR1) && (a_errorCode <= GLU_NURBS_ERROR37))
    {
      return gluNurbsErrors[a_errorCode];
    }

    if ((a_errorCode >= GLU_TESS_ERROR1) && (a_errorCode <= GLU_TESS_ERROR6))
    {
      return gluTessErrors[a_errorCode];
    }

    return "\0";
  }

#else

const char8* GetErrorString(GLenum a_errorCode)
{
  return reinterpret_cast<const char*>(gluErrorString(a_errorCode));
}

#endif

  template <typename T_BuildConfig>
  Error::value_type
    DoGetOpenGLError(T_BuildConfig)
  { 
    if (Error::IsIgnoreAllErrors())
    { return GL_NO_ERROR; }
    else
    { return glGetError(); }
  }

  Error::value_type
    DoGetOpenGLError(core_cfg::p_build_config::Release)
  { return GL_NO_ERROR; }

  //------------------------------------------------------------------------
  // Error

  const char*       Error::s_lastErrorDesc = "None";
  Error::value_type Error::s_lastError     = GL_NO_ERROR;
  bool              Error::s_ignoreAllErrors = false;

  bool Error::Succeeded()
  {
    return GetError() == GL_NO_ERROR;
  }

  bool Error::Failed()
  {
    return !Succeeded();
  }

  Error::value_type Error::GetError()
  {
    m_lastError = DoGetOpenGLError(core_cfg::BuildConfig::build_config_type());

    if (m_lastError != GL_NO_ERROR)
    {
      s_lastError = m_lastError;
      GetLastErrorAsString(s_lastErrorDesc);
    }

    return m_lastError;
  }

  template <typename T_String>
  void Error::GetLastErrorAsString(T_String& a_out)
  {
    const char* myError = GetErrorString(m_lastError);
    if (myError) { a_out = myError; }
  }

  void
    Error::
    IgnoreAllErrors(bool a_ignoreAllErrors)
  { s_ignoreAllErrors = a_ignoreAllErrors; }

  //------------------------------------------------------------------------
  // Explicit Instantiation

  template void Error::GetLastErrorAsString(core::string::String&);
  template void Error::GetLastErrorAsString(const char*&);

};};};