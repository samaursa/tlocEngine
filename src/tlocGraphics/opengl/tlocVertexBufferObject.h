#ifndef _TLOC_GRAPHICS_GL_VERTEX_BUFFER_OBJECT_H_
#define _TLOC_GRAPHICS_GL_VERTEX_BUFFER_OBJECT_H_

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

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

    template <typename T_Target, typename T_Usage>
    struct Bind_T
      : public core_bclass::NonCopyable_I
    {
    public:
      typedef core_sptr::VirtualPtr<VertexBufferObject>     vbo_ptr;
      typedef T_Target                                      target_type;

    public:
      Bind_T(vbo_ptr  a_vbo);
      ~Bind_T();

      void Data();

    private:
      vbo_ptr   m_vbo;
    };

  public:

    typedef Bind_T<p_vbo::target::ArrayBuffer>          bind_array_buffer;
    typedef Bind_T<p_vbo::target::ElementArrayBuffer>   bind_element_array_buffer;
    typedef Bind_T<p_vbo::target::PixelPackBuffer>      bind_pixel_pack_buffer;
    typedef Bind_T<p_vbo::target::PixelUnpackBuffer>    bind_pixel_unpack_buffer;

    TLOC_TYPEDEF_UNIQUE_PTR(bind_array_buffer, bind_array_buffer);
    TLOC_TYPEDEF_UNIQUE_PTR(bind_element_array_buffer, bind_element_array_buffer);
    TLOC_TYPEDEF_UNIQUE_PTR(bind_pixel_pack_buffer, bind_pixel_pack_buffer);
    TLOC_TYPEDEF_UNIQUE_PTR(bind_pixel_unpack_buffer, bind_pixel_unpack_buffer);

  public:
    VertexBufferObject();
    ~VertexBufferObject();
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(VertexBufferObject, vbo);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(VertexBufferObject, vbo);

};};};

#endif