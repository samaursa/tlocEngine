#ifndef _TLOC_GRAPHICS_GL_FRAMEBUFFER_OBJECT_H_
#define _TLOC_GRAPHICS_GL_FRAMEBUFFER_OBJECT_H_

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocGraphics/opengl/tlocObject.h>
#include <tlocGraphics/opengl/tlocRenderbufferObject.h>
#include <tlocGraphics/opengl/tlocTextureObject.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_framebuffer_object {

    struct FBOParamBase { };

    namespace target {

      typedef s32   value_type;

      struct TargetParamBase : public FBOParamBase
      { static const value_type s_glParamName; };

      struct DrawFramebuffer : public TargetParamBase
      { static const value_type s_glParamName; };
      struct ReadFramebuffer : public TargetParamBase
      { static const value_type s_glParamName;};
    };

    namespace attachment {

      typedef s32   value_type;

      struct AttachmentParamBase : public FBOParamBase
      { static const value_type s_glParamName;};

      struct MaxColorAttachments : public AttachmentParamBase
      { static const value_type s_glParamName;};

      template <value_type T_ColorAttachmentIndex>
      struct ColorAttachment : public AttachmentParamBase
      {
        enum { k_attachmentIndex = T_ColorAttachmentIndex };

        ColorAttachment()
        {
          TLOC_ASSERT(k_attachmentIndex < MaxColorAttachments::s_glParamName,
                      "Attachment index exceeded maximum allowed attachments");
        }

        TLOC_STATIC_ASSERT(T_ColorAttachmentIndex >= 0,
                           Invalid_color_attachment_index);

        static const value_type s_glParamName;
      };

      struct Depth : public AttachmentParamBase
      { static const value_type s_glParamName; };
      struct Stencil : public AttachmentParamBase
      { static const value_type s_glParamName; };
      struct DepthStencil : public AttachmentParamBase
      { static const value_type s_glParamName; };
    };

    struct Default : public FBOParamBase { };
  };

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

    typedef core_conts::Array<rbo_type>                   rbo_cont;
    typedef core_conts::Array<to_type>                    to_cont;

    typedef rbo_cont::iterator                            rbo_cont_iterator;
    typedef rbo_cont::const_iterator                      rbo_cont_const_iterator;
    typedef to_cont::iterator                             to_cont_iterator;
    typedef to_cont::const_iterator                       to_cont_const_iterator;

  public:

    // RAII not implemented deliberately because the dtor is not exactly
    // destroying anything, just setting the framebuffer back to default.
    struct Bind
    {
      Bind();
      explicit Bind(const FramebufferObject& a_fbo);
      ~Bind();
    };

  public:
    FramebufferObject();
    ~FramebufferObject();

    template <typename T_Target, typename T_Attachment,
              typename T_RenderOrTexturebuffer>
    error_type Attach(T_Target a_targe, T_Attachment a_attachment,
                      const T_RenderOrTexturebuffer& a_bufferObject);

    template <typename T_RenderOrTexturebuffer>
    error_type Detach(const T_RenderOrTexturebuffer& a_bufferObject);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (rbo_cont, GetRenderBufferObjects, m_renderbufferObjects);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (to_cont, GetTextureobjects, m_textureObjets);

    static this_type& GetDefaultFramebuffer();

  private:
    typedef p_framebuffer_object::target::value_type      target_value_type;
    typedef p_framebuffer_object::attachment::value_type  attachment_value_type;

    error_type DoAttach(target_value_type a_target,
                        attachment_value_type a_attachment,
                        const rbo_type& a_rbo);

    error_type DoAttach(target_value_type a_target,
                        attachment_value_type a_attachment,
                        const to_type& a_to);

    // This constructor is temporary until we have a better solution on how
    // to deal with the inconsistent behavior of default framebuffers across
    // various platforms
    FramebufferObject(p_framebuffer_object::Default);

  private:
    rbo_cont  m_renderbufferObjects;
    to_cont   m_textureObjets;
    bool      m_defaultFBO;
  };

  // -----------------------------------------------------------------------
  // template definitions

    template <typename T_Target, typename T_Attachment,
              typename T_RenderOrTexturebuffer>
  FramebufferObject::error_type
    FramebufferObject::
    Attach(T_Target a_targe, T_Attachment a_attachment,
           const T_RenderOrTexturebuffer& a_bufferObject)
  {
    // -----------------------------------------------------------------------
    // Sanity checks

    using namespace p_framebuffer_object::target;
    using namespace p_framebuffer_object::attachment;

    TLOC_STATIC_ASSERT
      ((Loki::Conversion<T_Target, TargetParamBase>::exists),
       Invalid_target_param);

    TLOC_STATIC_ASSERT
      ((Loki::Conversion<T_Attachment, AttachmentParamBase>::exists),
       Invalid_attachment_param);

    tloc::type_traits::AssertTypeIsSupported<T_RenderOrTexturebuffer,
      RenderbufferObject, TextureObject>();

    TLOC_ASSERT(T_Attachment::k_attachmentIndex <
                MaxColorAttachments::s_glParamName,
                "Attachment index exceeded maximum allowed attachments");

    // -----------------------------------------------------------------------
    // Internal attach method

    return DoAttach(T_Target::s_glParamName, T_Attachment::s_glParamName,
                    a_bufferObject);
  }

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(FramebufferObject, framebuffer_object);

};};};

#endif