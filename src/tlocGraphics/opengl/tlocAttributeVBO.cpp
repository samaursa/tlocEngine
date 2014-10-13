#include "tlocAttributeVBO.h"

#include <tlocCore/logging/tlocLogger.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>

namespace tloc { namespace graphics { namespace gl {

  namespace {

    typedef AttributeVBO::StrideInfo                stride_info;
    typedef AttributeVBO::stride_info_cont          stride_info_cont;
    typedef f32                                     real_type;

    using namespace gfx_t;
    using namespace core_conts;
    using namespace core_ds;
    using namespace math_t;

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const Array<s32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(1)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<s32> >())
                   );

      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const Array<Tuple2s32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Tuple2s32> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const Array<Tuple3s32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Tuple3s32> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const Array<Tuple4s32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(4)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Tuple4s32> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const Array<f32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(1)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<f32> >())
                   );

      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const Array<Vec2f32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vec2f32> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const Array<Vec3f32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vec3f32> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const Array<Vec4f32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(4)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vec4f32> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fp>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert3fp::attrib_1_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fpc>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*7)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert3fpc::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(4)
                   .StrideInBytes(sizeof(real_type)*7)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert3fpc::attrib_2_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fpt>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*5)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert3fpt::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*5)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert3fpt::attrib_2_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fpn>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*6)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert3fpn::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*6)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert3fpn::attrib_2_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fpnc>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*10)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert3fpnc::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*10)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert3fpnc::attrib_2_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(4)
                   .StrideInBytes(sizeof(real_type)*10)
                   .DataStartIndex(6)
                   .GLType(type_to_gl::Get<Array<Vert3fpnc::attrib_3_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fpnt>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*8)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert3fpnt::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*8)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert3fpnt::attrib_2_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*8)
                   .DataStartIndex(6)
                   .GLType(type_to_gl::Get<Array<Vert3fpnt::attrib_3_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fpnct>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*12)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert3fpnct::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*12)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert3fpnct::attrib_2_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(4)
                   .StrideInBytes(sizeof(real_type)*12)
                   .DataStartIndex(6)
                   .GLType(type_to_gl::Get<Array<Vert3fpnct::attrib_3_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*12)
                   .DataStartIndex(9)
                   .GLType(type_to_gl::Get<Array<Vert3fpnct::attrib_4_type::value_type> >())
                   );
      
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

  // ///////////////////////////////////////////////////////////////////////
  // AttributeVBO

  AttributeVBO::
    AttributeVBO()
    : m_usage(GL_NONE)
    , m_target(GL_NONE)
    , m_enabled(true)
    , m_dirty(true)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const AttributeVBO::StrideInfo&
    AttributeVBO::
    GetStrideInfo(size_type a_interleaveIndex) const
  { return m_strideInfo[a_interleaveIndex]; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  AttributeVBO::gl_enum_type
    AttributeVBO::
    GetInterleavedType(size_type a_interleaveIndex) const
  {
    return GetStrideInfo(a_interleaveIndex).m_glType;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  AttributeVBO::error_type
    AttributeVBO::
    Validate() const
  {
    if (m_strideInfo.size() == 0)
    { return TLOC_ERROR(gfx_err::error_attribute_vbo_has_no_data); }
    else if (m_names.size() == 0)
    { return TLOC_ERROR(gfx_err::error_attribute_vbo_has_no_names); }
    else if (m_names.size() != m_strideInfo.size())
    { return TLOC_ERROR(gfx_err::error_attribute_vbo_interleave_name_size_mismatch); }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    AttributeVBO::
    IsValid() const
  { return Validate() == ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Type>
  AttributeVBO::this_type&
    AttributeVBO::
    DoBufferData(gfx_t::gl_int a_target, gfx_t::gl_int a_usage, 
                 const core_conts::Array<T_Type>& a_array)
  {
    TLOC_ASSERT(a_array.empty() == false, "a_array has no elements");

    VertexBufferObject::UnsafeBind b(m_vbo, a_target);

    m_type        = gfx_t::type_to_gl::Get<Array<T_Type> >();
    m_usage       = a_usage;
    m_target      = a_target;
    m_dataSize    = a_array.size();
    m_strideInfo  = DoGetStrideInfo(a_array);

    glBufferData(m_target, 
                 sizeof(T_Type) * m_dataSize, 
                 &a_array[0], 
                 a_usage);
    {
      gl::Error err; TLOC_UNUSED(err);
      TLOC_ASSERT(err.Succeeded(), "glBufferData() failed");
    }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Type>
  const AttributeVBO::this_type&
    AttributeVBO::
    DoBufferSubData(const core_conts::Array<T_Type>& a_array, 
                    offset_index a_offset_index) const
  {
    TLOC_ASSERT(a_array.empty() == false, "a_array has no elements");

    const gl_enum_type type = gfx_t::type_to_gl::Get<Array<T_Type> >();
    TLOC_ASSERT(type == m_type, 
                "Attempting to update buffer with a mismatched type");

    using core_utils::CastNumber;
    const gfx_t::gl_sizei dataSize = a_array.size();

    TLOC_LOG_GFX_ERR_IF
      (dataSize + a_offset_index > CastNumber<gfx_t::gl_sizei>(m_dataSize))
      << "Attempting to update buffer will cause overflow";

    TLOC_LOG_GFX_WARN_IF
      (m_usage == p_vbo::usage::StaticDraw::s_glParamName ||
       m_usage == p_vbo::usage::StaticRead::s_glParamName ||
       m_usage == p_vbo::usage::StaticCopy::s_glParamName)
        << "Attempting to update buffer created with GL_STATIC_* usage";

    VertexBufferObject::UnsafeBind b(m_vbo, m_target);

    glBufferSubData(m_target, 
                    sizeof(T_Type) * a_offset_index, 
                    sizeof(T_Type) * dataSize,
                    &a_array[0]);
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
  DoBufferData<_type_>(gfx_t::gl_int, gfx_t::gl_int, const core_conts::Array<_type_>&);\
  template const AttributeVBO::this_type& AttributeVBO::\
  DoBufferSubData<_type_>(const core_conts::Array<_type_>&, AttributeVBO::offset_index) const

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