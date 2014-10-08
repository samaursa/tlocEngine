#include "tlocVertexBufferObject.h"

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>

namespace tloc { namespace graphics { namespace gl {

  // ///////////////////////////////////////////////////////////////////////
  // Bind

  VertexBufferObject::Bind::
    Bind(const vbo_ptr a_vbo)
  {
    object_handle handle = a_vbo->GetHandle();
    TLOC_UNUSED(handle);

    TLOC_ASSERT(gl::Error().Succeeded(), "OpenGL: Error with glBindVertexBuffer");
  }

};};};