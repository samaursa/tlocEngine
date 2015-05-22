#ifndef _TLOC_GRAPHICS_GL_ATTRIBUTE_VBO_H_
#define _TLOC_GRAPHICS_GL_ATTRIBUTE_VBO_H_

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/data_structures/tlocTuple.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/platform/tlocPlatform.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>
#include <tlocMath/types/tlocMatrix2.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>

#include <tlocGraphics/opengl/tlocObject.h>
#include <tlocGraphics/types/tlocVertex.h>
#include <tlocGraphics/opengl/tlocVertexBufferObject.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace gl {

  // ///////////////////////////////////////////////////////////////////////
  // AttributeVBO

  class AttributeVBO
  {
  public:
    typedef AttributeVBO                                    this_type;
    typedef gfx_t::gl_enum                                  gl_enum_type;
    typedef core_str::String                                string_type;
    typedef core_conts::Array<string_type>                  string_cont;
    typedef core_conts::Array<gl_enum_type>                 gl_enum_cont;
    typedef tl_size                                         size_type;
    typedef core_err::Error                                 error_type;

    typedef core_t::StrongType_T<gfx_t::gl_sizei, 0>        offset_index;

  public:
    struct StrideInfo
    {
    public:
      typedef StrideInfo                                    this_type;
      typedef gfx_t::gl_int                                 gl_int_type;

    public:
      StrideInfo();

      // NumElements - Can be 1, 2, 3 or 4 even if total elements exceed that number. 
      // e.g. Vec4 will be 4, Mat4 will be 4
      TLOC_DECL_PARAM_VAR(gl_int_type,  NumElements, m_numElements);
      // TotalElements - e.g. Vec4 will be 4, Mat4 will be 16
      TLOC_DECL_PARAM_VAR(gl_int_type,    TotalElements, m_totalElements);
      // GLType - see tlocGLType
      TLOC_DECL_PARAM_VAR(gl_enum_type, GLType, m_glType);
      // StrideInBytes - Stide for each interleaved type
      TLOC_DECL_PARAM_VAR(gl_int_type, StrideInBytes, m_strideInBytes);
      // DataStartIndex - The interleaved type starts from here
      TLOC_DECL_PARAM_VAR(size_type,    DataStartIndex, m_dataStartIndex);
    };
    typedef core_conts::Array<StrideInfo>                   stride_info_cont;

  public:
    AttributeVBO();

    this_type&        CopyFrom(const this_type& a_other);

    template <typename T_Target, typename T_Usage, typename T_Type>
    this_type&        SetValueAs(const core_conts::Array<T_Type>& a_array);

    template <typename T_Type>
    const this_type&  UpdateData(const core_conts::Array<T_Type>& a_array, 
                                 offset_index a_offset = offset_index(0)) const;

    template <typename T_Type>
    const this_type&  GetValueAs(core_conts::Array<T_Type>& a_out, 
                                 offset_index a_offset = offset_index(0)) const;

    const StrideInfo& GetStrideInfo(size_type a_interleaveIndex) const;
    gl_enum_type      GetInterleavedType(size_type a_interleaveIndex) const;

    error_type        Validate() const;
    bool              IsValid() const;

  public:
    TLOC_DECL_AND_DEF_GETTER(bool, IsEnabled, m_enabled);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(bool, SetEnabled, m_enabled);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(gl_enum_type, SetDivisor, m_divisor);

    const string_type& GetName(size_type a_nameIndex = 0) const;
    this_type&         AddName(BufferArg a_name);

    TLOC_DECL_AND_DEF_GETTER
      (string_cont::const_iterator, begin_names, m_names.begin());
    TLOC_DECL_AND_DEF_GETTER
      (string_cont::const_iterator, end_names, m_names.end());

    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (string_cont::iterator, begin_names, m_names.begin());
    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (string_cont::iterator, end_names, m_names.end());

    TLOC_DECL_AND_DEF_GETTER(VertexBufferObject, GetVBO, m_vbo);
    TLOC_DECL_AND_DEF_GETTER(gl_enum_type,    GetType, m_type);
    TLOC_DECL_AND_DEF_GETTER(gl_enum_type,    GetUsage, m_usage);
    TLOC_DECL_AND_DEF_GETTER(gl_enum_type,    GetTarget, m_target);
    TLOC_DECL_AND_DEF_GETTER(gl_enum_type,    GetDivisor, m_divisor);
    TLOC_DECL_AND_DEF_GETTER(gfx_t::gl_sizei, GetDataSize, m_dataSize);
    TLOC_DECL_AND_DEF_GETTER(size_type, size_names, m_names.size());
    TLOC_DECL_AND_DEF_GETTER(size_type, size_strideInfo, m_strideInfo.size());

  private:
    template <typename T_Type>
    this_type& DoBufferData(gfx_t::gl_int a_target, gfx_t::gl_int a_usage, 
                            const core_conts::Array<T_Type>& a_array);

    template <typename T_Type>
    const this_type& DoBufferSubData(const core_conts::Array<T_Type>& a_array, 
                                     offset_index a_offset) const;

    template <typename T_Type>
    const this_type&  DoGetValueAs(core_conts::Array<T_Type>& a_out, 
                                   offset_index a_offset) const;

  private:
    VertexBufferObject  m_vbo;
    gl_enum_type        m_type;
    gl_enum_type        m_usage;
    gl_enum_type        m_target;
    gl_enum_type        m_divisor;
    gfx_t::gl_sizei     m_dataSize;
    gfx_t::gl_sizei     m_dataTypeSize;
    string_cont         m_names;

    stride_info_cont    m_strideInfo;

    bool                m_enabled;

  };

  // -----------------------------------------------------------------------
  // template definitions
  
  namespace priv {
  
  template <typename T_Type>
    void DoCheckAttributeVBOType(core_plat::p_platform_info::win)
    {
      type_traits::AssertTypeIsSupported<T_Type,
          u32, s32, f32, 

          core_ds::Tuple2s32, core_ds::Tuple3s32, core_ds::Tuple4s32,
          core_ds::Tuple2u32, core_ds::Tuple3s32, core_ds::Tuple4u32,

          math_t::Vec2f32, math_t::Vec3f32, math_t::Vec4f32,

          math_t::Mat2f32, math_t::Mat3f32, math_t::Mat4f32,

          gfx_t::Vert2fp, gfx_t::Vert2fpc, gfx_t::Vert2fpt, gfx_t::Vert2fpn, 
          gfx_t::Vert2fpnc, gfx_t::Vert2fpnt, gfx_t::Vert2fpnct,

          gfx_t::Vert3fp, gfx_t::Vert3fpc, gfx_t::Vert3fpt, gfx_t::Vert3fpn, 
          gfx_t::Vert3fpnc, gfx_t::Vert3fpnt, gfx_t::Vert3fpnct,

          gfx_t::Vert2fpnto, gfx_t::Vert3fpnto,

          gfx_t::Vert3TBN, gfx_t::Vert4fo
         >();
    }
    
    template <typename T_Type>
    void DoCheckAttributeVBOType(core_plat::p_platform_info::iphone)
    {
      type_traits::AssertTypeIsSupported<T_Type,
          s32, f32,

          core_ds::Tuple2s32, core_ds::Tuple3s32, core_ds::Tuple4s32,

          math_t::Vec2f32, math_t::Vec3f32, math_t::Vec4f32,

          math_t::Mat2f32, math_t::Mat3f32, math_t::Mat4f32,

          gfx_t::Vert2fp, gfx_t::Vert2fpc, gfx_t::Vert2fpt, gfx_t::Vert2fpn, 
          gfx_t::Vert2fpnc, gfx_t::Vert2fpnt, gfx_t::Vert2fpnct,

          gfx_t::Vert3fp, gfx_t::Vert3fpc, gfx_t::Vert3fpt, gfx_t::Vert3fpn, 
          gfx_t::Vert3fpnc, gfx_t::Vert3fpnt, gfx_t::Vert3fpnct,

          gfx_t::Vert2fpnto, gfx_t::Vert3fpnto,

          gfx_t::Vert3TBN, gfx_t::Vert4fo
         >();
    }
  }

  template <typename T_Target, typename T_Usage, typename T_Type>
  AttributeVBO::this_type&
    AttributeVBO::
    SetValueAs(const core_conts::Array<T_Type>& a_array)
  {
    type_traits::AssertTypeIsSupported<T_Usage, 
      p_vbo::usage::StreamDraw, p_vbo::usage::StreamRead,
      p_vbo::usage::StreamCopy, p_vbo::usage::StaticDraw,
      p_vbo::usage::StaticRead, p_vbo::usage::StaticCopy,
      p_vbo::usage::DynamicDraw, p_vbo::usage::DynamicRead,
      p_vbo::usage::DynamicCopy>();

    priv::DoCheckAttributeVBOType<T_Type>(core_plat::PlatformInfo::platform_type());

    return DoBufferData<T_Type>(T_Target::s_glParamName, 
                                T_Usage::s_glParamName, a_array);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Type>
  const AttributeVBO::this_type&
    AttributeVBO::
    UpdateData(const core_conts::Array<T_Type>& a_array, 
               offset_index a_offset_index) const
  {
    priv::DoCheckAttributeVBOType<T_Type>(core_plat::PlatformInfo::platform_type());

    return DoBufferSubData<T_Type>(a_array, a_offset_index);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  
  template <typename T_Type>
  const AttributeVBO::this_type&
    AttributeVBO::
    GetValueAs(core_conts::Array<T_Type>& a_out, offset_index a_offset_index) const
  {
    priv::DoCheckAttributeVBOType<T_Type>(core_plat::PlatformInfo::platform_type());

    return DoGetValueAs<T_Type>(a_out, a_offset_index);
  }

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(AttributeVBO, attributeVBO);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(AttributeVBO, attributeVBO);

};};};

#endif