#ifndef TLOC_OPENGL_H
#define TLOC_OPENGL_H

#include <tlocGraphics/tlocGraphicsBase.h>
#include <tlocGraphics/opengl/tlocGLTypes.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/error/tlocError.h>

#define TLOC_GL_UNSUPPORTED  -1

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

    void Enable(gfx_t::gl_int a_index);
    void Disable(gfx_t::gl_int a_index);
    void DisableAll();

  }
  
  // ///////////////////////////////////////////////////////////////////////
  // VertexArrayObject
  
  namespace vertex_array_object {
    
    void            Bind(gfx_t::gl_uint a_name);
    void            UnBind();
    gfx_t::gl_uint  Generate();
    void            Destroy(gfx_t::gl_uint a_name);
    
  };

  // ///////////////////////////////////////////////////////////////////////
  // VertexBufferObject
  
  namespace vertex_buffer_object {
    
    void            Bind(gfx_t::gl_enum a_target, gfx_t::gl_uint a_name);
    void            UnBind(gfx_t::gl_enum a_target);
    gfx_t::gl_uint  Generate();
    void            Destroy(gfx_t::gl_uint a_name);
    
  };

  // ///////////////////////////////////////////////////////////////////////
  // Texture Units

  namespace texture_units {

    typedef tl_size               num_tex_img_units_used;

    namespace image_units { 

      // Texture image units start from GL_TEXTURE0 and go all the way to
      // GL_TEXTURE0 + max_units - 1
      core_err::Error         GetNext(gfx_t::gl_int& a_texImgUnitOut);
      void                    Activate(gfx_t::gl_int a_texImgUnit);
      bool                    IsValid(gfx_t::gl_int a_texImgUnit);
      num_tex_img_units_used  ResetCount();

      // A reserved texture image unit is not returned by GetNextAvailableTextureImageUnit()
      core_err::Error      Reserve(gfx_t::gl_int& a_texImgUnitOut);
      void                 Release(gfx_t::gl_int a_texImgUnit);
    };

    // Texture units start from 0 to max_units - 1
    bool                 IsValid(gfx_t::gl_int a_texUnit);
    gfx_t::gl_int        FromTextureImageUnit(gfx_t::gl_int a_texImgUnit);

  };

};};};

#endif
