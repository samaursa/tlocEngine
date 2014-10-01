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
  };

  // ///////////////////////////////////////////////////////////////////////
  // Bind

#define TLOC_VBO_BIND_TEMPS   typename T_Target
#define TLOC_VBO_BIND_PARAMS  T_Target
#define TLOC_VBO_BIND_TYPE    typename VertexBufferObject::Bind_T<TLOC_VBO_BIND_PARAMS>

  template <TLOC_VBO_BIND_TEMPS>
  VertexBufferObject::Bind_T<TLOC_VBO_BIND_PARAMS>::
    Bind_T(const vbo_ptr a_vbo)
    : m_vbo(a_vbo)
  {
    TLOC_ASSERT (a_vbo->GetTarget() == GL_NONE || 
                 target_type::s_glParamName == a_vbo->GetTarget(), 
                 "Previous Bind() operation on this buffer used a different target.");

    object_handle handle = a_vbo->GetHandle();
    gl::vertex_buffer_object::Bind(target_type::s_glParamName, handle);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VBO_BIND_TEMPS>
  VertexBufferObject::Bind_T<TLOC_VBO_BIND_PARAMS>::
    ~Bind_T()
  {
    gl::vertex_buffer_object::UnBind(target_type::s_glParamName);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VBO_BIND_TEMPS>
  template <typename T_Usage, typename T_Type>
  void
    VertexBufferObject::Bind_T<TLOC_VBO_BIND_PARAMS>::
    DoData(const core_conts::Array<T_Type>& a_array)
  {
    TLOC_ASSERT(a_array.empty() == false, "a_array has no elements");

    using namespace core_conts; using namespace core_sptr;

    // temporarily create an attribute to get the required information
    gl::Attribute temp;
    VirtualPtr<const Array<T_Type> > arrayPtr(&a_array);

    temp.SetValueAs(arrayPtr, p_shader_variable_ti::Pointer());

    const p_vbo::target::value_type target = target_type::s_glParamName;
    const p_vbo::usage::value_type usage = typename T_Usage::s_glParamName;

    const size_type arraySize = a_array.size();

    m_vbo->DoSetType(temp.GetType());
    m_vbo->DoSetUsage(usage);
    m_vbo->DoSetTarget(target);
    m_vbo->DoSetDataSize(arraySize);

    glBufferData(target, sizeof(T_Type) * arraySize, &a_array[0], usage);
    {
      gl::Error err; TLOC_UNUSED(err);
      TLOC_ASSERT(err.Succeeded(), "glBufferData() failed");
    }
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
    : m_type(GL_NONE)
    , m_usage(GL_NONE)
    , m_dataSize(0)
  { }

};};};

using namespace tloc::gfx_gl;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(VertexBufferObject);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(VertexBufferObject::bind_array_buffer);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(VertexBufferObject::bind_element_array_buffer);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(VertexBufferObject::bind_pixel_pack_buffer);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(VertexBufferObject::bind_pixel_unpack_buffer);