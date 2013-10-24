#ifndef _TLOC_GRAPHICS_GL_FRAMEBUFFER_OBJECT_H_
#define _TLOC_GRAPHICS_GL_FRAMEBUFFER_OBJECT_H_

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/types/tlocTypeTraits.h>

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
        enum { k_attachmenIndex = T_ColorAttachmentIndex };

        TLOC_STATIC_ASSERT(T_ColorAttachmentIndex >= 0,
                           Invalid_color_attachment_index);
      };

      struct Depth                { static const value_type s_glParamName; };
      struct Stencil              { static const value_type s_glParamName; };
      struct DepthStencil         { static const value_type s_glParamName; };
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Framebuffer Object

  class FramebufferObject
    : public Object_T<FramebufferObject, p_object::OnlyID>
  {
  public:
    typedef FramebufferObject                               this_type;
    typedef Object_T<this_type, p_object::OnlyID>           base_type;
    typedef base_type::object_handle                        object_handle;
    typedef base_type::error_type                           error_type;

    typedef RenderbufferObject                              rbo_type;
    typedef TextureObject                                   to_type;

  public:
    struct Bind
    {
      Bind(const FramebufferObject& a_fbo);
      ~Bind();
    };

  public:
    FramebufferObject();
    ~FramebufferObject();

    template <typename T_Target, typename T_Attachment,
              typename T_RenderOrTexturebuffer>
    error_type Attach(T_Target a_targe, T_Attachment a_attachment,
                T_RenderOrTexturebuffer  a_bufferObject);

  private:
    error_type DoAttach(p_framebuffer_object::target::value_type a_target,
                        p_framebuffer_object::attachment::value_type a_attachment,
                        rbo_type  a_rbo);

    error_type DoAttach(p_framebuffer_object::target::value_type a_target,
                        p_framebuffer_object::attachment::value_type a_attachment,
                        to_type  a_rbo);
  };

  // -----------------------------------------------------------------------
  // template definitions

    template <typename T_Target, typename T_Attachment,
              typename T_RenderOrTexturebuffer>
  FramebufferObject::error_type
    FramebufferObject::
    Attach(T_Target a_targe, T_Attachment a_attachment,
           T_RenderOrTexturebuffer a_bufferObject)
  {
    // -----------------------------------------------------------------------
    // Sanity checks

    using namespace p_framebuffer_object::target;
    using namespace p_framebuffer_object::attachment;

    tloc::type_traits::AssertTypeIsSupported<T_Target,
      DrawFramebuffer, ReadFramebuffer>();

    tloc::type_traits::AssertTypeIsSupported<T_Attachment,
      ColorAttachment, Depth, Stencil, DepthStencil>();

    tloc::type_traits::AssertTypeIsSupported<T_RenderOrTexturebuffer,
      RenderbufferObject, TextureObject>();

    TLOC_ASSERT(T_Attachment::k_attachmentIndex <
                MaxColorAttachments::s_glParamName,
                "Attachment index exceeded maximum allowed attachments");

    // -----------------------------------------------------------------------
    // Internal attach method

    DoAttach(T_Target::s_glParamName, T_Attachment::s_glParamName,
             a_bufferObject);
  }

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(FramebufferObject, framebuffer_object);

};};};

#endif