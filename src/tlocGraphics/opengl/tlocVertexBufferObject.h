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
    struct UnsafeBind
      : public core_bclass::NonCopyable_I
    {
    public:
      typedef p_vbo::target::value_type                     target_type;

    public:
      UnsafeBind(const this_type& a_vbo, target_type a_target);
      ~UnsafeBind();

    private:
      target_type m_target;
    };

  public:
    template <typename T_Target>
    struct Bind_T
      : public UnsafeBind
    {
    public:
      Bind_T(const this_type& a_vbo);
    };

  public:
    template <typename T_Target>
    struct LateBind_T
      : public core_bclass::NonCopyable_I
    {
    public:
      typedef T_Target                                      target_type;
      typedef core_sptr::UniquePtr<Bind_T<target_type> >    bind_ptr;

    public:
      void Bind(const this_type& a_vbo);

    private:
      bind_ptr  m_bind;
    };

  public:

    typedef Bind_T<p_vbo::target::ArrayBuffer>              bind_array;
    typedef Bind_T<p_vbo::target::CopyReadBuffer>           bind_copy_read;
    typedef Bind_T<p_vbo::target::CopyWriteBuffer>          bind_copy_write;
    typedef Bind_T<p_vbo::target::ElementArrayBuffer>       bind_element_array;
    typedef Bind_T<p_vbo::target::PixelPackBuffer>          bind_pixel_pack;
    typedef Bind_T<p_vbo::target::PixelUnpackBuffer>        bind_pixel_unpack;
    typedef Bind_T<p_vbo::target::TextureBuffer>            bind_texture;
    typedef Bind_T<p_vbo::target::TransformFeedbackBuffer>  bind_transform_feedback;

    typedef LateBind_T<p_vbo::target::ArrayBuffer>              late_bind_array;
    typedef LateBind_T<p_vbo::target::CopyReadBuffer>           late_bind_copy_read;
    typedef LateBind_T<p_vbo::target::CopyWriteBuffer>          late_bind_copy_write;
    typedef LateBind_T<p_vbo::target::ElementArrayBuffer>       late_bind_element_array;
    typedef LateBind_T<p_vbo::target::PixelPackBuffer>          late_bind_pixel_pack;
    typedef LateBind_T<p_vbo::target::PixelUnpackBuffer>        late_bind_pixel_unpack;
    typedef LateBind_T<p_vbo::target::TextureBuffer>            late_bind_texture;
    typedef LateBind_T<p_vbo::target::TransformFeedbackBuffer>  late_bind_transform_feedback;

  public:
    VertexBufferObject();
    VertexBufferObject(const this_type& a_other);

    ~VertexBufferObject();

    this_type& operator=(this_type a_other);
    void       swap(this_type& a_other);
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(VertexBufferObject, vbo);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(VertexBufferObject, vbo);

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(VertexBufferObject);
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(VertexBufferObject);

  TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(VertexBufferObject::bind_array);
  TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(VertexBufferObject::bind_copy_read);
  TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(VertexBufferObject::bind_copy_write);
  TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(VertexBufferObject::bind_element_array);
  TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(VertexBufferObject::bind_pixel_pack);
  TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(VertexBufferObject::bind_pixel_unpack);
  TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(VertexBufferObject::bind_texture);
  TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(VertexBufferObject::bind_transform_feedback);

};};};

#endif