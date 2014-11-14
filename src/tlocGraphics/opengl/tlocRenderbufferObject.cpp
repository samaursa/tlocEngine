#include "tlocRenderbufferObject.h"

#include <tlocCore/tlocAssert.h>

#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_renderbuffer_object {
    namespace internal_format {

      const value_type RGBA4::s_glParamName = GL_RGBA4;
      const value_type RGB565::s_glParamName = GL_RGB565;
      const value_type RGB5_A1::s_glParamName = GL_RGB5_A1;
      const value_type DepthComponent16::s_glParamName = GL_DEPTH_COMPONENT16;
      const value_type StencilIndex8::s_glParamName = GL_STENCIL_INDEX8;

#if defined (TLOC_OS_WIN)
      const value_type DepthComponent24::s_glParamName = GL_DEPTH_COMPONENT24;
      const value_type Depth24Stencil8::s_glParamName = GL_DEPTH24_STENCIL8;
#elif defined (TLOC_OS_IPHONE)
      const value_type DepthComponent24::s_glParamName = GL_DEPTH_COMPONENT24_OES;
      const value_type Depth24Stencil8::s_glParamName = GL_DEPTH24_STENCIL8_OES;
#else
# error "WIP"
#endif

    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // RenderbufferObject::Params

  RenderbufferObject::Params::
    Params()
    : m_formatType(p_renderbuffer_object::internal_format::RGBA4::s_glParamName)
    , m_dimensions(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RenderbufferObject::Params::this_type&
    RenderbufferObject::Params::
    Dimensions(const dimension_type& a_dim)
  {
    m_dimensions = a_dim;
    return *this;
  }

  // ///////////////////////////////////////////////////////////////////////
  // RenderbufferObject

  RenderbufferObject::Bind::
    Bind(const RenderbufferObject* a_rbo)
  {
    object_handle handle = a_rbo->GetHandle();
    glBindRenderbuffer(GL_RENDERBUFFER, handle);

    TLOC_ASSERT(gl::Error().Succeeded(),
      "OpenGL: Error with glRenderbufferStorage");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  RenderbufferObject::Bind::
    ~Bind()
  {
    TLOC_ASSERT(gl::Error().Succeeded(),
      "OpenGL: Error with glRenderbufferStorage");
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
  }

  // ///////////////////////////////////////////////////////////////////////
  // RenderbufferObject

  RenderbufferObject::
    RenderbufferObject(const Params& a_params)
    : m_params(a_params)
  {
    object_handle handle;
    glGenRenderbuffers(1, &handle);
    SetHandle(handle);
  }

  RenderbufferObject::
    ~RenderbufferObject()
  {
    if (IsLastRef())
    {
      object_handle handle = GetHandle();
      glDeleteRenderbuffers(1, &handle);
    }
  }

  RenderbufferObject::error_type
    RenderbufferObject::
    Initialize()
  {
    Bind b(this);

    glRenderbufferStorage(GL_RENDERBUFFER, m_params.GetFormatType(),
      m_params.GetDimensions()[0], m_params.GetDimensions()[1]);

    TLOC_ASSERT(gl::Error().Succeeded(),
      "OpenGL: Error with glRenderbufferStorage");

    return ErrorSuccess;
  }

  RenderbufferObject::error_type
    RenderbufferObject::
    InitializeWithoutStorage()
  {
    Bind b(this);
    return ErrorSuccess;
  }

  // -----------------------------------------------------------------------
  // explicit instantiations

#define TLOC_EXPLICITLY_INSTANTIATE_PARAMS_INTERNAL_FORMAT(_type_)\
  template RenderbufferObject::Params::this_type&\
    RenderbufferObject::Params::InternalFormat<_type_>()

  using namespace p_renderbuffer_object::internal_format;
  TLOC_EXPLICITLY_INSTANTIATE_PARAMS_INTERNAL_FORMAT(RGBA4);
  TLOC_EXPLICITLY_INSTANTIATE_PARAMS_INTERNAL_FORMAT(RGB565);
  TLOC_EXPLICITLY_INSTANTIATE_PARAMS_INTERNAL_FORMAT(RGB5_A1);
  TLOC_EXPLICITLY_INSTANTIATE_PARAMS_INTERNAL_FORMAT(DepthComponent16);
  TLOC_EXPLICITLY_INSTANTIATE_PARAMS_INTERNAL_FORMAT(StencilIndex8);

};};};

// -----------------------------------------------------------------------
// explicit instantiations

using namespace tloc::gfx_gl;

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(RenderbufferObject);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(RenderbufferObject::Bind);