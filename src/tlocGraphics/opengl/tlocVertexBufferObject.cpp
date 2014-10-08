#include "tlocVertexBufferObject.h"

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_vbo {
    namespace target {

      const value_type ArrayBuffer::s_glParamName = GL_ARRAY_BUFFER;
      const value_type CopyReadBuffer::s_glParamName = GL_COPY_READ_BUFFER;
      const value_type CopyWriteBuffer::s_glParamName = GL_COPY_WRITE_BUFFER;
      const value_type ElementArrayBuffer::s_glParamName = GL_ELEMENT_ARRAY_BUFFER;
      const value_type PixelPackBuffer::s_glParamName = GL_PIXEL_PACK_BUFFER;
      const value_type PixelUnpackBuffer::s_glParamName = GL_PIXEL_UNPACK_BUFFER;
      const value_type TextureBuffer::s_glParamName = GL_TEXTURE_BUFFER;
      const value_type TransformFeedbackBuffer::s_glParamName = GL_TRANSFORM_FEEDBACK_BUFFER;

    };

    namespace usage {

      const value_type StreamDraw::s_glParamName = GL_STREAM_DRAW;
      const value_type StreamRead::s_glParamName = GL_STREAM_READ;
      const value_type StreamCopy::s_glParamName = GL_STREAM_COPY;
      const value_type StaticDraw::s_glParamName = GL_STATIC_DRAW;
      const value_type StaticRead::s_glParamName = GL_STATIC_READ;
      const value_type StaticCopy::s_glParamName = GL_STATIC_COPY;
      const value_type DynamicDraw::s_glParamName = GL_DYNAMIC_DRAW;
      const value_type DynamicRead::s_glParamName = GL_DYNAMIC_READ;
      const value_type DynamicCopy::s_glParamName = GL_DYNAMIC_COPY;

    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Bind

#define TLOC_VBO_BIND_TEMPS   typename T_Target
#define TLOC_VBO_BIND_PARAMS  T_Target
#define TLOC_VBO_BIND_TYPE    typename VertexBufferObject::Bind_T<TLOC_VBO_BIND_PARAMS>

  template <TLOC_VBO_BIND_TEMPS>
  VertexBufferObject::Bind_T<TLOC_VBO_BIND_PARAMS>::
    Bind_T(const this_type& a_vbo)
  {
    object_handle handle = a_vbo.GetHandle();
    gl::vertex_buffer_object::Bind(target_type::s_glParamName, handle);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VBO_BIND_TEMPS>
  VertexBufferObject::Bind_T<TLOC_VBO_BIND_PARAMS>::
    ~Bind_T()
  {
    gl::vertex_buffer_object::UnBind(target_type::s_glParamName);
  }

  // ///////////////////////////////////////////////////////////////////////
  // LateBind

#define TLOC_VBO_LATE_BIND_TEMPS   typename T_Target
#define TLOC_VBO_LATE_BIND_PARAMS  T_Target
#define TLOC_VBO_LATE_BIND_TYPE    typename VertexBufferObject::Bind_T<TLOC_VBO_LATE_BIND_PARAMS>

  template <TLOC_VBO_LATE_BIND_TEMPS>
  void
  VertexBufferObject::LateBind_T<TLOC_VBO_LATE_BIND_PARAMS>::
    Bind(const this_type& a_vbo)
  {
    m_bind.reset(new bind_ptr::value_type());
  }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template struct VertexBufferObject::Bind_T<p_vbo::target::ArrayBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::CopyReadBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::CopyWriteBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::ElementArrayBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::PixelPackBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::PixelUnpackBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::TextureBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::TransformFeedbackBuffer>;


  // ///////////////////////////////////////////////////////////////////////
  // VertexBufferObject

  VertexBufferObject::
    VertexBufferObject()
    : base_type()
  { 
    object_handle handle = gfx_gl::vertex_buffer_object::Generate();
    SetHandle(handle);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  VertexBufferObject::
    ~VertexBufferObject()
  {
    if (IsLastRef() && GetHandle() != 0)
    {
      object_handle handle = GetHandle();
      gfx_gl::vertex_buffer_object::Destroy(handle);
    }
  }

};};};

using namespace tloc;
using namespace tloc::gfx_gl;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(VertexBufferObject);

TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(VertexBufferObject::bind_array_buffer);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(VertexBufferObject::bind_element_array_buffer);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(VertexBufferObject::bind_pixel_pack_buffer);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(VertexBufferObject::bind_pixel_unpack_buffer);

#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(VertexBufferObject);