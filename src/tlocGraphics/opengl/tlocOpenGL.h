#ifndef TLOC_OPENGL_H
#define TLOC_OPENGL_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/error/tlocError.h>

namespace tloc { namespace graphics { namespace types {

  typedef s32                     gl_int;
  typedef u32                     gl_uint;
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
  void
    AssertOpenGLContextExists();

  // ///////////////////////////////////////////////////////////////////////
  // OpenGL get functions (safely wrapped)

  namespace p_get
  {
    using gfx_t::gl_int;
    using gfx_t::gl_float;
    using gfx_t::gl_double;

    namespace priv
    {
      void DoGet(gl_int&     a_out, const gl_int s_glParamName);
      void DoGet(gl_int*&    a_out, const gl_int s_glParamName);
      void DoGet(gl_float&   a_out, const gl_int s_glParamName);
      void DoGet(gl_float*&  a_out, const gl_int s_glParamName);

#if defined (TLOC_OS_WIN) // TODO: Change to TLOC_GFX_PLATFORM_GL
      extern void DoGet(gl_double&  a_out, const gl_int s_glParamName);
      extern void DoGet(gl_double*& a_out, const gl_int s_glParamName);
#endif
    };

    struct CurrentProgram
    {
      typedef gl_int            value_type;
      static const value_type   s_glParamName;
    };
    struct MaxCombinedTextureImageUnits
    {
      typedef gl_int            value_type;
      static const value_type   s_glParamName;
    };
    struct MaxVertexAttribs
    {
      typedef gl_int            value_type;
      static const value_type   s_glParamName;
    };

#if defined (TLOC_OS_WIN)
    struct NumExtensions
    {
      typedef gl_int            value_type;
      static const value_type   s_glParamName;
    };
    struct NumShadingLanguageVersions
    {
      typedef gl_int            value_type;
      static const value_type   s_glParamName;
    };
#endif
  };

  template <typename T_GlPName>
  typename T_GlPName::value_type
    Get()
  {
    AssertOpenGLContextExists();
    typedef typename T_GlPName::value_type  ret_type;

    ret_type toRet;
    p_get::priv::DoGet(toRet, T_GlPName::s_glParamName);

    return toRet;
  }

  // ///////////////////////////////////////////////////////////////////////
  // VertexAttribArrays

  namespace vertex_attrib_array {

    bool Enable(gfx_t::gl_int a_index);
    bool EnableIfDisabled(gfx_t::gl_int a_index);
    bool IsEnabled(gfx_t::gl_int a_index);
    bool Disable(gfx_t::gl_int a_index);
    void DisableAll();

    // disables all attributes regardless of whether they were enabled or not
    // in the engine (useful when mixing OpenGL code with 3rd party libraries)
    void ForceDisableAll();

  }
  
  // ///////////////////////////////////////////////////////////////////////
  // VertexArrayObject
  
  namespace vertex_array_object {
    
    void            Bind(gfx_t::gl_uint a_name);
    void            UnBind();
    gfx_t::gl_uint  Generate();
    void            Destroy(gfx_t::gl_uint a_name);
    
  }

  // ///////////////////////////////////////////////////////////////////////
  // Texture Units

  // Texture image units start from GL_TEXTURE0 and go all the way to
  // GL_TEXTURE0 + max_units - 1
  core_err::Error      GetNextAvailableTextureImageUnit(gfx_t::gl_int& a_texImgUnitOut);
  void                 ActivateTextureImageUnit(gfx_t::gl_int a_texImgUnit);
  bool                 IsValidTextureImageUnit(gfx_t::gl_int a_texImgUnit);

  // Texture units start from 0 to max_units - 1
  bool                 IsValidTextureUnit(gfx_t::gl_int a_texUnit);
 gfx_t::gl_int         GetTextureUnitFromTextureImageUnit(gfx_t::gl_int a_texImgUnit);

};};};

#endif