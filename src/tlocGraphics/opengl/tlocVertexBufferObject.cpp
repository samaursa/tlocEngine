#include "tlocVertexBufferObject.h"

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/opengl/tlocAttribute.h>

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
    TLOC_ASSERT (a_vbo.GetTarget() == GL_NONE || 
                 target_type::s_glParamName == a_vbo.GetTarget(), 
                 "Previous Bind() operation on this buffer used a different target.");

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

  // -----------------------------------------------------------------------
  // explicit instantiations

  template struct VertexBufferObject::Bind_T<p_vbo::target::ArrayBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::ElementArrayBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::PixelPackBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::PixelUnpackBuffer>;

  // ///////////////////////////////////////////////////////////////////////
  // VertexBufferObject

  VertexBufferObject::
    VertexBufferObject()
    : base_type()
    , m_type(GL_NONE)
    , m_usage(GL_NONE)
    , m_target(GL_NONE)
    , m_dataSize(0)
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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Target, typename T_Type>
  VertexBufferObject::this_type&
    VertexBufferObject::
    DoData(gfx_t::gl_int a_usage, 
           const core_conts::Array<T_Type>& a_array)
  {
    TLOC_ASSERT(a_array.empty() == false, "a_array has no elements");

    using namespace core_conts; using namespace core_sptr;

    Bind_T<T_Target> b(*this);

    // temporarily create an attribute to get the required information
    core_conts::Array<T_Type> tempArray;

    gl::Attribute temp;
    VirtualPtr<Array<T_Type> > arrayPtr(&tempArray);

    temp.SetVertexArray(arrayPtr, p_shader_variable_ti::Pointer());

    const size_type arraySize = a_array.size();

    const gfx_t::gl_int target = typename T_Target::s_glParamName;

    DoSetType(temp.GetType());
    DoSetTarget(target);
    DoSetUsage(a_usage);
    DoSetDataSize(arraySize);

    glBufferData(target, sizeof(T_Type) * arraySize, &a_array[0], a_usage);
    {
      gl::Error err; TLOC_UNUSED(err);
      TLOC_ASSERT(err.Succeeded(), "glBufferData() failed");
    }

    return *this;
  }

  // ///////////////////////////////////////////////////////////////////////
  // AttributeVBO

  AttributeVBO::
    AttributeVBO()
    : base_type()
    , m_enabled(true)
  { }

};};};

using namespace tloc;
using namespace tloc::gfx_gl;

#define TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(_type_)\
  template VertexBufferObject::this_type& VertexBufferObject::\
  DoData<p_vbo::target::ArrayBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template VertexBufferObject::this_type& VertexBufferObject::\
  DoData<p_vbo::target::CopyReadBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template VertexBufferObject::this_type& VertexBufferObject::\
  DoData<p_vbo::target::CopyWriteBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template VertexBufferObject::this_type& VertexBufferObject::\
  DoData<p_vbo::target::ElementArrayBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template VertexBufferObject::this_type& VertexBufferObject::\
  DoData<p_vbo::target::PixelPackBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template VertexBufferObject::this_type& VertexBufferObject::\
  DoData<p_vbo::target::PixelUnpackBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template VertexBufferObject::this_type& VertexBufferObject::\
  DoData<p_vbo::target::TextureBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template VertexBufferObject::this_type& VertexBufferObject::\
  DoData<p_vbo::target::TransformFeedbackBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&)

TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(f32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(math_t::Vec2f32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(math_t::Vec3f32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(math_t::Vec4f32);

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(VertexBufferObject);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(AttributeVBO);

TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(VertexBufferObject::bind_array_buffer);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(VertexBufferObject::bind_element_array_buffer);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(VertexBufferObject::bind_pixel_pack_buffer);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(VertexBufferObject::bind_pixel_unpack_buffer);

#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(VertexBufferObject);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(AttributeVBO);