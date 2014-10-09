#ifndef _TLOC_GRAPHICS_GL_ATTRIBUTE_VBO_H_
#define _TLOC_GRAPHICS_GL_ATTRIBUTE_VBO_H_

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/data_structures/tlocTuple.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>

#include <tlocGraphics/opengl/tlocObject.h>
#include <tlocGraphics/types/tlocVertex.h>
#include <tlocGraphics/opengl/tlocVertexBufferObject.h>

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
      typedef tl_size                                       size_type;

  public:
    struct StrideInfo
    {
    public:
      typedef StrideInfo                                    this_type;
      typedef gfx_t::gl_sizei                               gl_size_type;
      typedef gfx_t::gl_int                                 gl_int_type;

    public:
      StrideInfo();

      // size param in glVertexAttribPointer
      TLOC_DECL_PARAM_VAR(gl_int_type, NumElements, m_numElements);
      TLOC_DECL_PARAM_VAR(gl_size_type, StrideInBytes, m_strideInBytes);
      TLOC_DECL_PARAM_VAR(size_type, DataStartIndex, m_dataStartIndex);
    };
    typedef core_conts::Array<StrideInfo>                   stride_info_cont;

  public:
    AttributeVBO();

  public:
    TLOC_DECL_AND_DEF_GETTER(bool, IsEnabled, m_enabled);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(bool, SetEnabled, m_enabled);

    const string_type& GetName(tl_int a_nameIndex = 0) const;
    this_type&         AddName(BufferArg a_name);

    TLOC_DECL_AND_DEF_GETTER
      (string_cont::const_iterator, begin_names, m_names.begin());
    TLOC_DECL_AND_DEF_GETTER
      (string_cont::const_iterator, end_names, m_names.end());

    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (string_cont::iterator, begin_names, m_names.begin());
    TLOC_DECL_AND_DEF_GETTER_NON_CONST
      (string_cont::iterator, end_names, m_names.end());

    template <typename T_Target, typename T_Usage, typename T_Type>
    this_type& SetValueAs(const core_conts::Array<T_Type>& a_array);

    TLOC_DECL_AND_DEF_GETTER(VertexBufferObject, GetVBO, m_vbo);
    TLOC_DECL_AND_DEF_GETTER(gl_enum_type,    GetType, m_type);
    TLOC_DECL_AND_DEF_GETTER(gl_enum_type,    GetUsage, m_usage);
    TLOC_DECL_AND_DEF_GETTER(gl_enum_type,    GetTarget, m_target);
    TLOC_DECL_AND_DEF_GETTER(gfx_t::gl_sizei, GetDataSize, m_dataSize);

    const StrideInfo& GetStrideInfo(size_type a_interleaveIndex) const;

  private:
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(gl_enum_type, DoSetType, m_type);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(gl_enum_type, DoSetUsage, m_usage);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(gl_enum_type, DoSetTarget, m_target);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(gl_enum_type, DoSetDataSize, m_dataSize);

  private:
    template <typename T_Target, typename T_Type>
    this_type& DoData(gfx_t::gl_int a_usage, 
                      const core_conts::Array<T_Type>& a_array);

  private:
    VertexBufferObject  m_vbo;
    gl_enum_type        m_type;
    gl_enum_type        m_usage;
    gl_enum_type        m_target;
    gfx_t::gl_sizei     m_dataSize;
    string_cont         m_names;

    stride_info_cont    m_strideInfo;

    bool                m_enabled;
    bool                m_dirty;

  };

  // -----------------------------------------------------------------------
  // template definitions

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

    type_traits::AssertTypeIsSupported<T_Type, 
        s32, f32, 

        core_ds::Tuple2s32, core_ds::Tuple3s32, core_ds::Tuple4s32,

        math_t::Vec2f32, math_t::Vec3f32, math_t::Vec4f32,

        gfx_t::Vert3fp, gfx_t::Vert3fpc, gfx_t::Vert3fpt, gfx_t::Vert3fpn, 
        gfx_t::Vert3fpnc, gfx_t::Vert3fpnt, gfx_t::Vert3fpnct
       >();

    return DoData<T_Target, T_Type>(T_Usage::s_glParamName, a_array);
  }

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(AttributeVBO, attributeVBO);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(AttributeVBO, attributeVBO);

};};};

#endif