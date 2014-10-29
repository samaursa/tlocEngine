#ifndef _TLOC_GRAPHICS_GL_FRAMEBUFFER_OBJECT_H_
#define _TLOC_GRAPHICS_GL_FRAMEBUFFER_OBJECT_H_

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>

#include <tlocGraphics/opengl/tlocObject.h>
#include <tlocGraphics/opengl/tlocRenderbufferObject.h>
#include <tlocGraphics/opengl/tlocTextureObject.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_fbo {

    namespace priv {
      struct FramebufferObjectParamsBase { };
    };

    namespace target {

      typedef s32   value_type;

      namespace priv {
        struct TargetParamsBase :
          public p_fbo::priv::FramebufferObjectParamsBase { };
      };

      struct Framebuffer : public priv::TargetParamsBase
      { static const value_type s_glParamName; };

      struct DrawFramebuffer : public priv::TargetParamsBase
      { static const value_type s_glParamName; };

      struct ReadFramebuffer : public priv::TargetParamsBase
      { static const value_type s_glParamName;};
    };

    namespace attachment {

      typedef s32   value_type;

      namespace priv {
        struct AttachmentParamsBase :
          public p_fbo::priv::FramebufferObjectParamsBase { };
      };

      template <value_type T_ColorAttachmentIndex>
      struct ColorAttachment : public priv::AttachmentParamsBase
      {
        enum { k_attachmentIndex = T_ColorAttachmentIndex };

        TLOC_STATIC_ASSERT(T_ColorAttachmentIndex >= 0,
                           Invalid_color_attachment_index);

        static const value_type s_glParamName;
      };

      struct Depth : public priv::AttachmentParamsBase
      { static const value_type s_glParamName; };

      struct Stencil : public priv::AttachmentParamsBase
      { static const value_type s_glParamName; };

      struct DepthStencil : public priv::AttachmentParamsBase
      { static const value_type s_glParamName; };
    };

    struct Default : public priv::FramebufferObjectParamsBase{ };
  };

  // backward compatibility
  namespace p_framebuffer_object = p_fbo;

  // ///////////////////////////////////////////////////////////////////////
  // Framebuffer Object

  class FramebufferObject
    : public Object_T<FramebufferObject, p_object::OnlyID>
  {
  public:
    typedef FramebufferObject                             this_type;
    typedef Object_T<this_type, p_object::OnlyID>         base_type;
    typedef base_type::object_handle                      object_handle;
    typedef base_type::error_type                         error_type;

    typedef RenderbufferObject                            rbo_type;
    typedef TextureObject                                 to_type;
    typedef TextureObjectShadow                           to_shadow_type;

    typedef core_conts::Array<rbo_type>                   rbo_cont;
    typedef core_conts::Array<to_type>                    to_cont;
    typedef core_conts::Array<to_shadow_type>             to_shadow_cont;

    typedef rbo_cont::iterator                            rbo_cont_iterator;
    typedef rbo_cont::const_iterator                      rbo_cont_const_iterator;
    typedef to_cont::iterator                             to_cont_iterator;
    typedef to_cont::const_iterator                       to_cont_const_iterator;

    typedef to_type::dimension_type                       dimension_type;

  public:
    struct UnsafeBind
      : public core_bclass::NonCopyable_I
    {
    public:
      typedef FramebufferObject                           fbo_type;
      typedef p_fbo::target::value_type    target_type;

    public:
      UnsafeBind(const fbo_type& a_fbo, target_type a_target);
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
      typedef T_Target                                    target_type;

    public:
      Bind_T(const fbo_type& a_fbo);
    };

  public:
    template <typename T_Target>
    struct LateBind_T
      : public core_bclass::NonCopyable_I
    {
    public:
      typedef FramebufferObject                           fbo_type;
      typedef T_Target                                    target_type;
      typedef core_sptr::UniquePtr<Bind_T<target_type> >  bind_ptr;

    public:
      void Bind(const fbo_type& a_fbo);

    private:
      bind_ptr  m_bind;
    };

  public:
    typedef Bind_T<p_fbo::target::Framebuffer>     bind;
    typedef Bind_T<p_fbo::target::DrawFramebuffer> bind_draw;
    typedef Bind_T<p_fbo::target::ReadFramebuffer> bind_read;

    TLOC_TYPEDEF_UNIQUE_PTR(bind, bind);
    TLOC_TYPEDEF_UNIQUE_PTR(bind_draw, bind_draw);
    TLOC_TYPEDEF_UNIQUE_PTR(bind_read, bind_read);

  public:
    FramebufferObject();
    ~FramebufferObject();

    FramebufferObject(const this_type& a_other);

    template <typename T_Target, typename T_Attachment,
              typename T_RenderOrTexturebuffer>
    error_type Attach(const T_RenderOrTexturebuffer& a_bufferObject);

    template <typename T_RenderOrTexturebuffer>
    error_type Detach(const T_RenderOrTexturebuffer& a_bufferObject);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (rbo_cont, GetRenderBufferObjects, m_renderbufferObjects);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (to_cont, GetTextureobjects, m_textureObjets);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (to_shadow_cont, GetTextureobjectsShadow, m_textureObjetsShadow);

  protected:
    // This constructor should be only be used by platforms that require a
    // FBO with an ID of 0 explicitly
    FramebufferObject(p_fbo::Default);

  private:
    typedef p_fbo::target::value_type      target_value_type;
    typedef p_fbo::attachment::value_type  attachment_value_type;

    error_type DoAttach(target_value_type a_target,
                        attachment_value_type a_attachment,
                        const rbo_type& a_rbo);

    error_type DoAttach(target_value_type a_target,
                        attachment_value_type a_attachment,
                        const to_type& a_to);

    error_type DoAttach(target_value_type a_target,
                        attachment_value_type a_attachment,
                        const to_shadow_type& a_to);

  private:
    void DoCheckInternalFormatAgainstTargetAttachment
      ( p_fbo::target::value_type a_target,
        p_fbo::attachment::value_type a_attachment,
        const rbo_type& a_rbo);

    void DoCheckInternalFormatAgainstTargetAttachment
      ( p_fbo::target::value_type a_target,
        p_fbo::attachment::value_type a_attachment,
        const to_type& a_to);

    void DoCheckInternalFormatAgainstTargetAttachment
      ( p_fbo::target::value_type a_target,
        p_fbo::attachment::value_type a_attachment,
        const to_shadow_type& a_to);

  private:
    rbo_cont        m_renderbufferObjects;
    to_cont         m_textureObjets;
    to_shadow_cont  m_textureObjetsShadow;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_Target, typename T_Attachment,
            typename T_RenderOrTexturebuffer>
  FramebufferObject::error_type
    FramebufferObject::
    Attach(const T_RenderOrTexturebuffer& a_bufferObject)
  {
    // -----------------------------------------------------------------------
    // Sanity checks

    using namespace p_fbo::target::priv;
    using namespace p_fbo::attachment::priv;

    TLOC_STATIC_ASSERT
      ((Loki::Conversion<T_Target, TargetParamsBase>::exists), Invalid_target_param);

    TLOC_STATIC_ASSERT
      ((Loki::Conversion<T_Attachment, AttachmentParamsBase>::exists), Invalid_attachment_param);

    tloc::type_traits::AssertTypeIsSupported<T_RenderOrTexturebuffer,
      RenderbufferObject, TextureObject, TextureObjectShadow>();

    // -----------------------------------------------------------------------
    // Internal attach method

    return DoAttach(T_Target::s_glParamName, T_Attachment::s_glParamName,
                    a_bufferObject);
  }

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(FramebufferObject, framebuffer_object);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(FramebufferObject, framebuffer_object);

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(FramebufferObject);
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(FramebufferObject);

  TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(FramebufferObject::bind);
  TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(FramebufferObject::bind_draw);
  TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(FramebufferObject::bind_read);


};};};

#endif
