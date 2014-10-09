#include "tlocAttributeVBO.h"

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>

namespace tloc { namespace graphics { namespace gl {

  namespace {

    typedef AttributeVBO::StrideInfo                stride_info;
    typedef AttributeVBO::stride_info_cont          stride_info_cont;
    typedef f32                                     real_type;

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<s32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(1).StrideInBytes(0)
                   .DataStartIndex(0));

      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<core_ds::Tuple2s32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(2).StrideInBytes(0)
                   .DataStartIndex(0));
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<core_ds::Tuple3s32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(3).StrideInBytes(0)
                   .DataStartIndex(0));
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<core_ds::Tuple4s32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(4).StrideInBytes(0)
                   .DataStartIndex(0));
      
      return si;
    }

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
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fpc>&)
    {
      stride_info_cont si;
      si.push_back(stride_info().NumElements(3).StrideInBytes(sizeof(real_type)*7)
                   .DataStartIndex(0));

      si.push_back(stride_info().NumElements(4).StrideInBytes(sizeof(real_type)*7)
                   .DataStartIndex(3));
      
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

  // ///////////////////////////////////////////////////////////////////////
  // VertexBufferObject::StrideInfo

  AttributeVBO::StrideInfo::
    StrideInfo()
    : m_numElements(0)
    , m_strideInBytes(0)
    , m_dataStartIndex(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const AttributeVBO::StrideInfo&
    AttributeVBO::
    GetStrideInfo(size_type a_interleaveIndex) const
  { return m_strideInfo[a_interleaveIndex]; }

  // ///////////////////////////////////////////////////////////////////////
  // AttributeVBO

  AttributeVBO::
    AttributeVBO()
    : m_enabled(true)
    , m_dirty(true)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Target, typename T_Type>
  AttributeVBO::this_type&
    AttributeVBO::
    DoData(gfx_t::gl_int a_usage, 
           const core_conts::Array<T_Type>& a_array)
  {
    TLOC_ASSERT(a_array.empty() == false, "a_array has no elements");

    using namespace core_conts; using namespace core_sptr;

    VertexBufferObject::Bind_T<T_Target> b(m_vbo);

    const gfx_t::gl_enum glType     = gfx_t::type_to_gl::Get<Array<T_Type> >();
    const gfx_t::gl_int   target    = typename T_Target::s_glParamName;
    const size_type      arraySize  = a_array.size();

    DoSetType(glType);
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

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const AttributeVBO::string_type&
    AttributeVBO::
    GetName(tl_int a_nameIndex) const
  { return m_names[a_nameIndex]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  AttributeVBO::this_type&
    AttributeVBO::
    AddName(BufferArg a_name)
  { m_names.push_back(a_name.GetPtr()); return *this; }

};};};

using namespace tloc;
using namespace tloc::gfx_gl;

#define TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(_type_)\
  template AttributeVBO::this_type& AttributeVBO::\
  DoData<p_vbo::target::ArrayBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template AttributeVBO::this_type& AttributeVBO::\
  DoData<p_vbo::target::CopyReadBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template AttributeVBO::this_type& AttributeVBO::\
  DoData<p_vbo::target::CopyWriteBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template AttributeVBO::this_type& AttributeVBO::\
  DoData<p_vbo::target::ElementArrayBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template AttributeVBO::this_type& AttributeVBO::\
  DoData<p_vbo::target::PixelPackBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template AttributeVBO::this_type& AttributeVBO::\
  DoData<p_vbo::target::PixelUnpackBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template AttributeVBO::this_type& AttributeVBO::\
  DoData<p_vbo::target::TextureBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template AttributeVBO::this_type& AttributeVBO::\
  DoData<p_vbo::target::TransformFeedbackBuffer, _type_>(gfx_t::gl_int, const core_conts::Array<_type_>&)

TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(s32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(f32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(core_ds::Tuple2s32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(core_ds::Tuple3s32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(core_ds::Tuple4s32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(math_t::Vec2f32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(math_t::Vec3f32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(math_t::Vec4f32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fp);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpc);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpt);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpn);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpnc);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpnt);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpnct);

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(AttributeVBO);

#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(AttributeVBO);

#include <tlocCore/containers/tlocArray.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(AttributeVBO::StrideInfo);