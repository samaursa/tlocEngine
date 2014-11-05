#include "tlocAttributeVBO.h"

#include <tlocCore/logging/tlocLogger.h>
#include <tlocCore/platform/tlocPlatformDefines.h>

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
      DoGetStrideInfo(const Array<u32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(1)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<u32> >())
                   );

      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const Array<Tuple2u32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Tuple2u32> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const Array<Tuple3u32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Tuple3u32> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const Array<Tuple4u32>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(4)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Tuple4u32> >())
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
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert4fo>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(4)
                   .StrideInBytes(sizeof(real_type)*16)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert4fo::attrib_1_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert2fp>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(0)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert2fp::attrib_1_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert2fpc>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*6)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert2fpc::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(4)
                   .StrideInBytes(sizeof(real_type)*6)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert2fpc::attrib_2_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert2fpt>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*4)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert2fpt::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*4)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert2fpt::attrib_2_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert2fpn>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*5)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert2fpn::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*5)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert2fpn::attrib_2_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert2fpnc>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*9)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert2fpnc::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*9)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert2fpnc::attrib_2_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(4)
                   .StrideInBytes(sizeof(real_type)*9)
                   .DataStartIndex(6)
                   .GLType(type_to_gl::Get<Array<Vert2fpnc::attrib_3_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert2fpnt>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*7)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert2fpnt::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*7)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert2fpnt::attrib_2_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*7)
                   .DataStartIndex(6)
                   .GLType(type_to_gl::Get<Array<Vert2fpnt::attrib_3_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert2fpnto>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*23) // 2 + 3 + 2 + 16
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert2fpnto::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*23)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert2fpnto::attrib_2_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*23)
                   .DataStartIndex(6)
                   .GLType(type_to_gl::Get<Array<Vert2fpnto::attrib_3_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(4)
                   .StrideInBytes(sizeof(real_type)*23)
                   .DataStartIndex(8)
                   .GLType(type_to_gl::Get<Array<Vert2fpnto::attrib_4_type::value_type> >())
                   );
      
      return si;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    stride_info_cont
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert2fpnct>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*11)
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert2fpnct::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*11)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert2fpnct::attrib_2_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(4)
                   .StrideInBytes(sizeof(real_type)*11)
                   .DataStartIndex(6)
                   .GLType(type_to_gl::Get<Array<Vert2fpnct::attrib_3_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*11)
                   .DataStartIndex(9)
                   .GLType(type_to_gl::Get<Array<Vert2fpnct::attrib_4_type::value_type> >())
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
                   .StrideInBytes(sizeof(real_type)*8) // 3 + 3 + 2
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
      DoGetStrideInfo(const core_conts::Array<gfx_t::Vert3fpnto>&)
    {
      stride_info_cont si;
      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*24) // 3 + 3 + 2 + 16
                   .DataStartIndex(0)
                   .GLType(type_to_gl::Get<Array<Vert3fpnto::attrib_1_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(3)
                   .StrideInBytes(sizeof(real_type)*24)
                   .DataStartIndex(3)
                   .GLType(type_to_gl::Get<Array<Vert3fpnto::attrib_2_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(2)
                   .StrideInBytes(sizeof(real_type)*24)
                   .DataStartIndex(6)
                   .GLType(type_to_gl::Get<Array<Vert3fpnto::attrib_3_type::value_type> >())
                   );

      si.push_back(stride_info()
                   .NumElements(4)
                   .StrideInBytes(sizeof(real_type)*24)
                   .DataStartIndex(8)
                   .GLType(type_to_gl::Get<Array<Vert3fpnto::attrib_4_type::value_type> >())
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
                   .StrideInBytes(sizeof(real_type)*12) // 3 + 3 + 4 + 2
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
    : m_type(GL_NONE)
    , m_usage(GL_NONE)
    , m_target(GL_NONE)
    , m_dataSize(0)
    , m_dataTypeSize(0)
    , m_enabled(true)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#ifdef TLOC_OS_IPHONE
  void glCopyBufferSubData(GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr)
  { TLOC_ASSERT_FALSE("Copying buffer data is NOT supported on iOS"); }
#endif

  AttributeVBO::this_type&
    AttributeVBO::
    CopyFrom(const this_type& a_other)
  {
    TLOC_ASSERT(m_vbo.GetHandle() != a_other.GetVBO().GetHandle(),
                "Cannot copy into the same buffer");

    if (a_other.m_dataSize != 0)
    {
      TLOC_ASSERT(m_dataTypeSize != 0, 
                  "AttributeVBO storing some data with sizeof(T) == 0");

      // allocate the buffer
      m_vbo = VertexBufferObject();
      {
        VertexBufferObject::bind_array b(GetVBO());
        glBufferData(m_target,
                     m_dataTypeSize * m_dataSize,
                     TLOC_NULL,
                     m_usage);
        {
          gl::Error err; TLOC_UNUSED(err);
          TLOC_ASSERT(err.Succeeded(), "glBufferData() failed");
        }
      }

      // start the copying process
      VertexBufferObject::bind_copy_read  readFrom(a_other.GetVBO());
      VertexBufferObject::bind_copy_write writeTo(GetVBO());

      glCopyBufferSubData(p_vbo::target::CopyReadBuffer::s_glParamName, 
                          p_vbo::target::CopyWriteBuffer::s_glParamName,
                          0, 0, m_dataTypeSize * m_dataSize);
      {
        gl::Error err; TLOC_UNUSED(err);
        TLOC_ASSERT(err.Succeeded(), "glBufferData() failed");
      }
    }

    return *this;
  }

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

    m_type          = gfx_t::type_to_gl::Get<Array<T_Type> >();
    m_dataTypeSize  = sizeof(T_Type);
    m_usage         = a_usage;
    m_target        = a_target;
    m_dataSize      = core_utils::CastNumber<gl_sizei>(a_array.size());
    m_strideInfo    = DoGetStrideInfo(a_array);

    glBufferData(m_target, 
                 m_dataTypeSize * m_dataSize, 
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
                    offset_index a_offset) const
  {
    TLOC_ASSERT(a_array.empty() == false, "a_array has no elements");

    const gl_enum_type type = gfx_t::type_to_gl::Get<Array<T_Type> >();
    TLOC_UNUSED_RELEASE(type);
    TLOC_ASSERT(type == m_type, 
                "Attempting to update buffer with a mismatched type");

    using core_utils::CastNumber;
    const gfx_t::gl_sizei dataSize =
      core_utils::CastNumber<gl_sizei>(a_array.size());

    TLOC_LOG_GFX_ERR_IF
      (dataSize + a_offset > CastNumber<gfx_t::gl_sizei>(m_dataSize))
      << "Attempting to update buffer will cause overflow";

    TLOC_LOG_GFX_WARN_IF
      (m_usage == p_vbo::usage::StaticDraw::s_glParamName ||
       m_usage == p_vbo::usage::StaticRead::s_glParamName ||
       m_usage == p_vbo::usage::StaticCopy::s_glParamName)
        << "Attempting to update buffer created with GL_STATIC_* usage";

    VertexBufferObject::UnsafeBind b(m_vbo, m_target);

    const gfx_t::gl_int offsetInBytes = sizeof(T_Type) * a_offset;
    const gfx_t::gl_int sizeInBytes = sizeof(T_Type) * dataSize - offsetInBytes;

    glBufferSubData(m_target, offsetInBytes, sizeInBytes, &a_array[0]);
    {
      gl::Error err; TLOC_UNUSED(err);
      TLOC_LOG_GFX_ERR_IF(err.Failed()) << "glBufferSubData() failed";
    }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#ifdef TLOC_OS_IPHONE
  void glGetBufferSubData(GLenum, GLintptr, GLsizeiptr, GLvoid*)
  { TLOC_ASSERT_FALSE("Getting buffer data is NOT supported on iOS"); }
#endif

  template <typename T_Type>
  const AttributeVBO::this_type&
    AttributeVBO::
    DoGetValueAs(core_conts::Array<T_Type>& a_out, offset_index a_offset) const
  {
    TLOC_ASSERT
      (a_offset < core_utils::CastNumber<gfx_t::gl_sizei>(m_dataSize),
       "a_offsetIndex is out of bounds");

    a_out.resize(m_dataSize - a_offset);

    const gl_enum_type type = gfx_t::type_to_gl::Get<Array<T_Type> >();
    TLOC_UNUSED_RELEASE(type);
    TLOC_ASSERT(type == m_type, 
                "Mismatched types while getting the buffer");

    VertexBufferObject::UnsafeBind b(m_vbo, m_target);

    const gfx_t::gl_int offsetInBytes = sizeof(T_Type) * a_offset;
    const gfx_t::gl_int sizeInBytes = sizeof(T_Type) * m_dataSize - offsetInBytes;

    glGetBufferSubData(m_target, offsetInBytes, sizeInBytes, &a_out[0]);
    {
      gl::Error err; TLOC_UNUSED(err);
      TLOC_ASSERT(err.Succeeded(), "glGetBufferSubData() failed");
    }

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const AttributeVBO::string_type&
    AttributeVBO::
    GetName(size_type a_nameIndex) const
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
  DoBufferSubData<_type_>(const core_conts::Array<_type_>&, AttributeVBO::offset_index) const;\
  template const AttributeVBO::this_type& AttributeVBO::\
  DoGetValueAs<_type_>(core_conts::Array<_type_>&, AttributeVBO::offset_index) const

TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(s32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(u32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(f32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(core_ds::Tuple2s32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(core_ds::Tuple3s32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(core_ds::Tuple4s32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(core_ds::Tuple2u32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(core_ds::Tuple3u32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(core_ds::Tuple4u32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(math_t::Vec2f32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(math_t::Vec3f32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(math_t::Vec4f32);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert2fp);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert2fpc);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert2fpt);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert2fpn);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert2fpnc);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert2fpnt);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert2fpnct);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fp);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpc);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpt);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpn);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpnc);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpnt);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpnct);

TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert2fpnto);
TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert3fpnto);

TLOC_EXPLICITLY_INSTANTIATE_VBO_DODATA_ALL_TARGETS(gfx_t::Vert4fo);

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(AttributeVBO);

#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(AttributeVBO);

#include <tlocCore/containers/tlocArray.inl.h>
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(AttributeVBO::StrideInfo);