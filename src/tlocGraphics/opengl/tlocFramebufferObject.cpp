#include "tlocFramebufferObject.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace gl {

  // ///////////////////////////////////////////////////////////////////////
  // Bind

  FramebufferObject::Bind::
    Bind(const FramebufferObject& a_fbo)
  {
    object_handle handle = a_fbo.GetHandle();
    glBindFramebuffer(GL_FRAMEBUFFER, handle);

    TLOC_ASSERT(gl::Error().Succeeded(),
      "OpenGL: Error with glRenderbufferStorage");
  }

  FramebufferObject::Bind::
    ~Bind()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  // ///////////////////////////////////////////////////////////////////////
  // FramebufferObject

  FramebufferObject::
    FramebufferObject()
  {
    object_handle handle;
    glGenFramebuffers(1, &handle);
    SetHandle(handle);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FramebufferObject::
    ~FramebufferObject()
  {
    if (IsLastRef())
    {
      object_handle handle = GetHandle();
      glDeleteFramebuffers(1, &handle);
    }
  }

  // ///////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(FramebufferObject);


};};};