#ifndef _TLOC_GRAPHICS_GL_VERTEX_BUFFER_OBJECT_H_
#define _TLOC_GRAPHICS_GL_VERTEX_BUFFER_OBJECT_H_

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/containers/tlocArray.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

  // ///////////////////////////////////////////////////////////////////////
  // VBO options

  namespace p_vbo
  {
    namespace target {

      typedef gfx_t::gl_int             value_type;

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

      typedef gfx_t::gl_int             value_type;

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
      typedef core_sptr::VirtualPtr<VertexBufferObject>     vbo_ptr;
      typedef T_Target                                      target_type;

    public:
      Bind_T(vbo_ptr  a_vbo);
      ~Bind_T();

      template <typename T_Usage, typename T_Type>
      void Data(const core_conts::Array<T_Type>& a_array);

    private:
      template <typename T_Usage, typename T_Type>
      void DoData(const core_conts::Array<T_Type>& a_array);

    private:
      vbo_ptr   m_vbo;
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

    TLOC_DECL_AND_DEF_GETTER(gfx_t::gl_enum, GetType, m_type);
    TLOC_DECL_AND_DEF_GETTER(gfx_t::gl_enum, GetUsage, m_usage);
    TLOC_DECL_AND_DEF_GETTER(gfx_t::gl_enum, GetTarget, m_usage);
    TLOC_DECL_AND_DEF_GETTER(gfx_t::gl_sizei, GetDataSize, m_dataSize);

    TLOC_DECL_AND_DEF_SETTER(BufferArg, SetName, m_name);
    TLOC_DECL_AND_DEF_GETTER(string_type, GetName, m_name);

  private:
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(gfx_t::gl_enum, DoSetType, m_type);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(gfx_t::gl_enum, DoSetUsage, m_usage);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(gfx_t::gl_enum, DoSetTarget, m_usage);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(gfx_t::gl_enum, DoSetDataSize, m_dataSize);

  private:
    gfx_t::gl_enum  m_type;
    gfx_t::gl_enum  m_usage;
    gfx_t::gl_enum  m_target;
    gfx_t::gl_sizei m_dataSize;
    string_type     m_name;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(VertexBufferObject, vbo);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(VertexBufferObject, vbo);

};};};

#endif