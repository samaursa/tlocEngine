#ifndef TLOC_OPENGL_H
#define TLOC_OPENGL_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/error/tlocError.h>

namespace tloc { namespace graphics { namespace types {

  typedef s32                     gl_int;
  typedef u32                     gl_enum;
  typedef s32                     gl_sizei;
  typedef f32                     gl_float;
  typedef f64                     gl_double;

};};};

namespace tloc { namespace graphics { namespace gl {

  // ///////////////////////////////////////////////////////////////////////
  // InitializePlatform()

  core_err::Error
    InitializePlatform();
  bool
    IsPlatformInitialized();

  // ///////////////////////////////////////////////////////////////////////
  // OpenGL get functions (safely wrapped)

  namespace p_get
  {
    using gfx_t::gl_int;
    using gfx_t::gl_float;
    using gfx_t::gl_double;

    namespace priv
    {
      void DoGet(gl_int&     a_out, const gl_int a_paramName);
      void DoGet(gl_int*&    a_out, const gl_int a_paramName);
      void DoGet(gl_float&   a_out, const gl_int a_paramName);
      void DoGet(gl_float*&  a_out, const gl_int a_paramName);

#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL
      extern void DoGet(gl_double&  a_out, const gl_int a_paramName);
      extern void DoGet(gl_double*& a_out, const gl_int a_paramName);
#endif
    };

    struct CurrentProgram
    {
      typedef gl_int      value_type;
      static const value_type s_glParamName;
    };
    struct MaxCombinedTextureImageUnits
    {
      typedef gl_int      value_type;
      static const value_type s_glParamName;
    };
    struct MaxVertexAttribs
    {
      typedef gl_int      value_type;
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

  // Texture image units start from GL_TEXTURE0 and go all the way to
  // GL_TEXTURE0 + max_units - 1
  gfx_t::gl_int        GetActiveTextureImageUnit();
  core_err::Error      GetNextAvailableTextureImageUnit(gfx_t::gl_int& a_texImgUnitOut);
  void                 RecycleTextureImageUnit(gfx_t::gl_int a_texImgUnit);
  void                 ActivateTextureImageUnit(gfx_t::gl_int a_texImgUnit);
  bool                 IsValidTextureImageUnit(gfx_t::gl_int a_texImgUnit);

  // Texture units start from 0 to max_units - 1
  bool                 IsValidTextureUnit(gfx_t::gl_int a_texUnit);
 gfx_t::gl_int         GetTextureUnitFromTextureImageUnit(gfx_t::gl_int a_texImgUnit);



};};};

#endif