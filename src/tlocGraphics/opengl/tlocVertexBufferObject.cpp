#include "tlocVertexBufferObject.h"

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/opengl/tlocAttribute.h>

namespace tloc { namespace graphics { namespace gl {

  namespace {

    typedef VertexBufferObject::StrideInfo                stride_info;
    typedef VertexBufferObject::stride_info_cont          stride_info_cont;
    typedef f32                                           real_type;

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<f32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(1).StrideInBytes(0)
                   .DataStartIndex(0));

      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<math_t::Vec2f32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(2).StrideInBytes(0)
                   .DataStartIndex(0));
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<math_t::Vec3f32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(3).StrideInBytes(0)
                   .DataStartIndex(0));
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<math_t::Vec4f32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(4).StrideInBytes(0)
                   .DataStartIndex(0));
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fp>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(3).StrideInBytes(0)
                   .DataStartIndex(0));
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fpt>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(3).StrideInBytes(sizeof(real_type)*5)
                   .DataStartIndex(0));

      si.push_back(stride_info().NumElements(2).StrideInBytes(sizeof(real_type)*5)
                   .DataStartIndex(3));
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fpn>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(3).StrideInBytes(sizeof(real_type)*6)
                   .DataStartIndex(0));

      si.push_back(stride_info().NumElements(3).StrideInBytes(sizeof(real_type)*6)
                   .DataStartIndex(3));
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fpnc>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(3).StrideInBytes(sizeof(real_type)*10)
                   .DataStartIndex(0));

      si.push_back(stride_info().NumElements(3).StrideInBytes(sizeof(real_type)*10)
                   .DataStartIndex(3));

      si.push_back(stride_info().NumElements(4).StrideInBytes(sizeof(real_type)*10)
                   .DataStartIndex(6));
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fpnt>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(3).StrideInBytes(sizeof(real_type)*8)
                   .DataStartIndex(0));

      si.push_back(stride_info().NumElements(3).StrideInBytes(sizeof(real_type)*8)
                   .DataStartIndex(3));

      si.push_back(stride_info().NumElements(2).StrideInBytes(sizeof(real_type)*8)
                   .DataStartIndex(6));
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fpnct>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(3).StrideInBytes(sizeof(real_type)*12)
                   .DataStartIndex(0));

      si.push_back(stride_info().NumElements(3).StrideInBytes(sizeof(real_type)*12)
                   .DataStartIndex(3));

      si.push_back(stride_info().NumElements(4).StrideInBytes(sizeof(real_type)*12)
                   .DataStartIndex(6));

      si.push_back(stride_info().NumElements(2).StrideInBytes(sizeof(real_type)*12)
                   .DataStartIndex(9));
      
      return si;
    }

  };

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
  template struct VertexBufferObject::Bind_T<p_vbo::target::CopyReadBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::CopyWriteBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::ElementArrayBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::PixelPackBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::PixelUnpackBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::TextureBuffer>;
  template struct VertexBufferObject::Bind_T<p_vbo::target::TransformFeedbackBuffer>;

  // ///////////////////////////////////////////////////////////////////////
  // VertexBufferObject::StrideInfo

  VertexBufferObject::StrideInfo::
    StrideInfo()
    : m_numElements(0)
    , m_strideInBytes(0)
    , m_dataStartIndex(0)
  { }

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const VertexBufferObject::StrideInfo&
    VertexBufferObject::
    GetStrideInfo(size_type a_interleaveIndex) const
  { return m_strideInfo[a_interleaveIndex]; }

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

    m_strideInfo = DoGetStrideInfo(a_array);

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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const AttributeVBO::string_type&
    AttributeVBO::
    GetName(tl_int a_nameIndex) const
  {
    switch(a_nameIndex)
    {
    case 0:
      return m_name;
    case 1:
      return m_name2;
    case 2:
      return m_name3;
    case 3:
      return m_name4;
    default:
      TLOC_ASSERT_FALSE("AttributeVBOs only have upto 4 possible names");
      return m_name;
    }
  }

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
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fp);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpt);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpn);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpnc);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpnt);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpnct);

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

#include <tlocCore/containers/tlocArray.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(VertexBufferObject::StrideInfo);