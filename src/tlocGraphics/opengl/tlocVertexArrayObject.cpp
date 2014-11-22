#include "tlocVertexArrayObject.h"

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace gl {

  // ///////////////////////////////////////////////////////////////////////
  // Bind

  VertexArrayObject::Bind::
    Bind(const this_type& a_vao)
  {
    object_handle handle = a_vao.GetHandle();
    gfx_gl::vertex_array_object::Bind(handle);

    TLOC_ASSERT(gl::Error().Succeeded(), "OpenGL: Error with glBindVertexArray");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  VertexArrayObject::Bind::
    ~Bind()
  {
    gfx_gl::vertex_array_object::UnBind();
    TLOC_ASSERT(gl::Error().Succeeded(), "OpenGL: Error with glBindVertexArray(0)");
  }

  // ///////////////////////////////////////////////////////////////////////
  // LateBind

  void 
    VertexArrayObject::LateBind::
    Bind(const this_type& a_vao)
  {
    m_bind = core_sptr::MakeUnique<VertexArrayObject::Bind>(a_vao);
  }

  // ///////////////////////////////////////////////////////////////////////
  // VertexArrayObject

  VertexArrayObject::
    VertexArrayObject()
  {
    object_handle handle = gfx_gl::vertex_array_object::Generate();
    SetHandle(handle);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  VertexArrayObject::
    ~VertexArrayObject()
  {
    if (IsLastRef() && GetHandle() != 0)
    {
      object_handle handle = GetHandle();
      gfx_gl::vertex_array_object::Destroy(handle);
    }
  }

};};};

// ///////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_gl;

TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(VertexArrayObject);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_PTR(VertexArrayObject);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(VertexArrayObject);

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(VertexArrayObject::Bind);

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(VertexArrayObject::LateBind);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(VertexArrayObject::LateBind);
