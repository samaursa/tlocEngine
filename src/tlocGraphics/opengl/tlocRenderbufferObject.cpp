#include "tlocRenderbufferObject.h"

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocError.h>

namespace tloc { namespace graphics { namespace gl {

  // ///////////////////////////////////////////////////////////////////////
  // RenderbufferObject

  RenderbufferObject::Bind::
    Bind(const RenderbufferObject& a_rbo)
  {
    object_handle handle = a_rbo.GetHandle();
    glBindRenderbuffer(GL_RENDERBUFFER, handle);

    TLOC_ASSERT(gl::Error().Succeeded(),
      "OpenGL: Error with glRenderbufferStorage");
  }

  RenderbufferObject::Bind::
    ~Bind()
  {
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
    Bind b(*this);
    glRenderbufferStorage(GL_RENDERBUFFER, m_params.GetFormatType(),
      m_params.GetDimensions()[0], m_params.GetDimensions()[1]);

    TLOC_ASSERT(gl::Error().Succeeded(),
      "OpenGL: Error with glRenderbufferStorage");

    return ErrorSuccess;
  }

};};};