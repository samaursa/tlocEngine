#include "tlocVertexArrayObject.h"

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>

namespace tloc { namespace graphics { namespace gl {

  // ///////////////////////////////////////////////////////////////////////
  // Bind

  VertexArrayObject::Bind::
    Bind(const vao_ptr a_vao)
  {
    object_handle handle = a_vao->GetHandle();
    glBindVertexArray(handle);

    TLOC_ASSERT(gl::Error().Succeeded(), "OpenGL: Error with glBindVertexArray");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  VertexArrayObject::Bind::
    ~Bind()
  {
    glBindVertexArray(0);
    TLOC_ASSERT(gl::Error().Succeeded(), "OpenGL: Error with glBindVertexArray(0)");
  }

  // ///////////////////////////////////////////////////////////////////////
  // VertexArrayObject

  VertexArrayObject::
    VertexArrayObject()
  {
    object_handle handle;
    glGenVertexArrays(1, &handle);
    SetHandle(handle);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  VertexArrayObject::
    ~VertexArrayObject()
  {
    if (IsLastRef() && GetHandle() != 0)
    {
      object_handle handle = GetHandle();
      glDeleteVertexArrays(1, &handle);
    }
  }

};};};

// ///////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_gl;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(VertexArrayObject);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(VertexArrayObject);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(VertexArrayObject::Bind);