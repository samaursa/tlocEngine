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

  namespace p_framebuffer_object {

    namespace target {

      typedef s32                       value_type;

      struct DrawFramebuffer      { static const value_type s_glParamName; };
      struct ReadFramebuffer      { static const value_type s_glParamName; };

    };

    namespace attachment {

      typedef s32                       value_type;

      struct MaxColorAttachments  { static const value_type s_glParamName; };

      template <value_type T_ColorAttachmentIndex>
      struct ColorAttachment
      {
        static const value_type   s_glParamName;
        enum { k_attachmentIndex = T_ColorAttachmentIndex };

        TLOC_STATIC_ASSERT(T_ColorAttachmentIndex >= 0,
                           Invalid_color_attachment_index);
      };

      struct Depth                { static const value_type s_glParamName; };
      struct Stencil              { static const value_type s_glParamName; };
      struct DepthStencil         { static const value_type s_glParamName; };
    };

    struct Default { };
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
      : public core::NonCopyable
    {
      Bind(const FramebufferObject* a_fbo);
      ~Bind();
    };
    TLOC_TYPEDEF_UNIQUE_PTR(Bind, bind);

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

    static this_type& GetDefaultFramebuffer();

  private:
    error_type DoAttach(p_framebuffer_object::target::value_type a_target,
                        p_framebuffer_object::attachment::value_type a_attachment,
                        const rbo_type& a_rbo);

    error_type DoAttach(p_framebuffer_object::target::value_type a_target,
                        p_framebuffer_object::attachment::value_type a_attachment,
                        const to_type& a_to);

    // This constructor is temporary until we have a better solution on how
    // to deal with the inconsistent behavior of default framebuffers across
    // various platforms
    FramebufferObject(p_framebuffer_object::Default);

  private:
    rbo_cont  m_renderbufferObjects;
    to_cont   m_textureObjets;
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

    using namespace p_framebuffer_object::target;
    using namespace p_framebuffer_object::attachment;

    tloc::type_traits::AssertTypeIsSupported<T_Target,
      DrawFramebuffer, ReadFramebuffer>();

    tloc::type_traits::AssertTypeIsSupported<T_Attachment,
      ColorAttachment<0>, ColorAttachment<1>, ColorAttachment<2>,
      ColorAttachment<3>, ColorAttachment<4>, ColorAttachment<5>,
      ColorAttachment<6>, ColorAttachment<7>, ColorAttachment<8>,
      ColorAttachment<9>, ColorAttachment<10>, ColorAttachment<11>,
      ColorAttachment<12>, ColorAttachment<13>, ColorAttachment<14>,
      ColorAttachment<15>, Depth, Stencil, DepthStencil>();

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