#ifndef _TLOC_GRAPHICS_GL_VERTEX_BUFFER_OBJECT_H_
#define _TLOC_GRAPHICS_GL_VERTEX_BUFFER_OBJECT_H_

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/containers/tlocArray.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  // ///////////////////////////////////////////////////////////////////////
  // VBO options

  namespace p_vbo
  {
    namespace target {

      typedef gfx_t::gl_enum             value_type;

      struct ArrayBuffer              { static const value_type s_glParamName; };
      struct CopyReadBuffer           { static const value_type s_glParamName; };
      struct CopyWriteBuffer          { static const value_type s_glParamName; };
      struct ElementArrayBuffer       { static const value_type s_glParamName; };
      struct PixelPackBuffer          { static const value_type s_glParamName; };
      struct PixelUnpackBuffer        { static const value_type s_glParamName; };
      struct TextureBuffer            { static const value_type s_glParamName; };
      struct TransformFeedbackBuffer  { static const value_type s_glParamName; };
    };

    namespace usage {

      typedef gfx_t::gl_enum             value_type;

      struct StreamDraw             { static const value_type s_glParamName; };
      struct StreamRead             { static const value_type s_glParamName; };
      struct StreamCopy             { static const value_type s_glParamName; };
      struct StaticDraw             { static const value_type s_glParamName; };
      struct StaticRead             { static const value_type s_glParamName; };
      struct StaticCopy             { static const value_type s_glParamName; };
      struct DynamicDraw            { static const value_type s_glParamName; };
      struct DynamicRead            { static const value_type s_glParamName; };
      struct DynamicCopy            { static const value_type s_glParamName; };

    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // VertexBufferObject

  class VertexBufferObject
    : public Object_T<VertexBufferObject, p_object::OnlyID>
  {
  public:
    typedef VertexBufferObject                              this_type;
    typedef Object_T<this_type, p_object::OnlyID>           base_type;

  public:

    template <typename T_Target>
    struct Bind_T
      : public core_bclass::NonCopyable_I
    {
    public:
      typedef T_Target                                      target_type;

    public:
      Bind_T(const this_type&  a_vbo);
      ~Bind_T();
    };

  public:

    template <typename T_Target> friend struct Bind_T;

    typedef Bind_T<p_vbo::target::ArrayBuffer>          bind_array_buffer;
    typedef Bind_T<p_vbo::target::ElementArrayBuffer>   bind_element_array_buffer;
    typedef Bind_T<p_vbo::target::PixelPackBuffer>      bind_pixel_pack_buffer;
    typedef Bind_T<p_vbo::target::PixelUnpackBuffer>    bind_pixel_unpack_buffer;

    typedef core_str::String                            string_type;

    TLOC_TYPEDEF_UNIQUE_PTR(bind_array_buffer, bind_array_buffer);
    TLOC_TYPEDEF_UNIQUE_PTR(bind_element_array_buffer, bind_element_array_buffer);
    TLOC_TYPEDEF_UNIQUE_PTR(bind_pixel_pack_buffer, bind_pixel_pack_buffer);
    TLOC_TYPEDEF_UNIQUE_PTR(bind_pixel_unpack_buffer, bind_pixel_unpack_buffer);

  public:
    VertexBufferObject();
    ~VertexBufferObject();

    template <typename T_Target, typename T_Usage, typename T_Type>
    this_type& Data(const core_conts::Array<T_Type>& a_array);

    TLOC_DECL_AND_DEF_GETTER(gfx_t::gl_enum, GetType, m_type);
    TLOC_DECL_AND_DEF_GETTER(gfx_t::gl_enum, GetUsage, m_usage);
    TLOC_DECL_AND_DEF_GETTER(gfx_t::gl_enum, GetTarget, m_target);
    TLOC_DECL_AND_DEF_GETTER(gfx_t::gl_sizei, GetDataSize, m_dataSize);

  private:
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(gfx_t::gl_enum, DoSetType, m_type);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(gfx_t::gl_enum, DoSetUsage, m_usage);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(gfx_t::gl_enum, DoSetTarget, m_target);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(gfx_t::gl_enum, DoSetDataSize, m_dataSize);

  private:
    template <typename T_Target, typename T_Type>
    this_type& DoData(gfx_t::gl_int a_usage, 
                      const core_conts::Array<T_Type>& a_array);

  private:
    gfx_t::gl_enum  m_type;
    gfx_t::gl_enum  m_usage;
    gfx_t::gl_enum  m_target;
    gfx_t::gl_sizei m_dataSize;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_Target, typename T_Usage, typename T_Type>
  VertexBufferObject::this_type&
    VertexBufferObject::
    Data(const core_conts::Array<T_Type>& a_array)
  {
    type_traits::AssertTypeIsSupported<T_Usage, 
      p_vbo::usage::StreamDraw, p_vbo::usage::StreamRead,
      p_vbo::usage::StreamCopy, p_vbo::usage::StaticDraw,
      p_vbo::usage::StaticRead, p_vbo::usage::StaticCopy,
      p_vbo::usage::DynamicDraw, p_vbo::usage::DynamicRead,
      p_vbo::usage::DynamicCopy>();

    type_traits::AssertTypeIsSupported<T_Type, f32, 
       math_t::Vec2f32, math_t::Vec3f32, math_t::Vec4f32>();

    return DoData<T_Target, T_Type>(T_Usage::s_glParamName, a_array);
  }

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(VertexBufferObject, vbo);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(VertexBufferObject, vbo);

  // ///////////////////////////////////////////////////////////////////////
  // AttributeVBO

  class AttributeVBO
    : public VertexBufferObject
  {
  public:
    typedef VertexBufferObject                      base_type;
    typedef AttributeVBO                            this_type;

  public:
    AttributeVBO();

  public:
    TLOC_DECL_AND_DEF_GETTER(bool, IsEnabled, m_enabled);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(bool, SetEnabled, m_enabled);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetName, m_name);
    TLOC_DECL_AND_DEF_SETTER_CHAIN(string_type, SetName, m_name);

  private:
    string_type     m_name;
    bool            m_enabled;

  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(AttributeVBO, attributeVBO);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(AttributeVBO, attributeVBO);

};};};

#endif