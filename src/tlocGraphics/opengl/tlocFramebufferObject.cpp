#include "tlocFramebufferObject.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/platform/tlocPlatform.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace gl {

  namespace {

    typedef types::gl_int   int_type;

#if defined (TLOC_OS_WIN)

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T_Platform>
    int_type
      DoGetMaxColorAttachments(T_Platform)
    {
      int_type maxAttachments;
      glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttachments);
      return maxAttachments;
    }

#endif

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    int_type
      DoGetMaxColorAttachments(core_plat::p_platform_info::iphone)
    { return 1; }

  }

  namespace p_framebuffer_object {

    namespace target {

#if defined (TLOC_OS_WIN)
      const value_type  Framebuffer::s_glParamName     = GL_FRAMEBUFFER;
      const value_type  DrawFramebuffer::s_glParamName = GL_DRAW_FRAMEBUFFER;
      const value_type  ReadFramebuffer::s_glParamName = GL_READ_FRAMEBUFFER;
#elif defined (TLOC_OS_IPHONE)
      const value_type  Framebuffer::s_glParamName     = GL_FRAMEBUFFER;
      const value_type  DrawFramebuffer::s_glParamName = GL_DRAW_FRAMEBUFFER_APPLE;
      const value_type  ReadFramebuffer::s_glParamName = GL_READ_FRAMEBUFFER_APPLE;
#else
# error "WIP"
#endif

    };

    namespace attachment {

      // NOTE: we are adding to GL_COLOR_ATTACHME0 for remaining attachments to
      // ensure compatibility with platforms that do not have enough color
      // attachments. The color attachment is checked at runtime when attaching
      // texture or render buffers
#if defined (TLOC_OS_WIN)

      template<> const value_type
        ColorAttachment<0>::s_glParamName  = GL_COLOR_ATTACHMENT0;
      template<> const value_type
        ColorAttachment<1>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 1;
      template<> const value_type
        ColorAttachment<2>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 2;
      template<> const value_type
        ColorAttachment<3>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 3;
      template<> const value_type
        ColorAttachment<4>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 4;
      template<> const value_type
        ColorAttachment<5>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 5;
      template<> const value_type
        ColorAttachment<6>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 6;
      template<> const value_type
        ColorAttachment<7>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 7;
      template<> const value_type
        ColorAttachment<8>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 8;
      template<> const value_type
        ColorAttachment<9>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 9;
      template<> const value_type
        ColorAttachment<10>::s_glParamName = GL_COLOR_ATTACHMENT0 + 10;
      template<> const value_type
        ColorAttachment<11>::s_glParamName = GL_COLOR_ATTACHMENT0 + 11;
      template<> const value_type
        ColorAttachment<12>::s_glParamName = GL_COLOR_ATTACHMENT0 + 12;
      template<> const value_type
        ColorAttachment<13>::s_glParamName = GL_COLOR_ATTACHMENT0 + 13;
      template<> const value_type
        ColorAttachment<14>::s_glParamName = GL_COLOR_ATTACHMENT0 + 14;
      template<> const value_type
        ColorAttachment<15>::s_glParamName = GL_COLOR_ATTACHMENT0 + 15;

      const value_type  Depth::s_glParamName = GL_DEPTH_ATTACHMENT;
      const value_type  Stencil::s_glParamName = GL_STENCIL_ATTACHMENT;
      const value_type  DepthStencil::s_glParamName = GL_DEPTH_STENCIL_ATTACHMENT;

#elif defined (TLOC_OS_IPHONE)

      template<> const value_type
        ColorAttachment<0>::s_glParamName  = GL_COLOR_ATTACHMENT0;
      template<> const value_type
        ColorAttachment<1>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 1;
      template<> const value_type
        ColorAttachment<2>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 2;
      template<> const value_type
        ColorAttachment<3>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 3;
      template<> const value_type
        ColorAttachment<4>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 4;
      template<> const value_type
        ColorAttachment<5>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 5;
      template<> const value_type
        ColorAttachment<6>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 6;
      template<> const value_type
        ColorAttachment<7>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 7;
      template<> const value_type
        ColorAttachment<8>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 8;
      template<> const value_type
        ColorAttachment<9>::s_glParamName  = GL_COLOR_ATTACHMENT0 + 9;
      template<> const value_type
        ColorAttachment<10>::s_glParamName = GL_COLOR_ATTACHMENT0 + 10;
      template<> const value_type
        ColorAttachment<11>::s_glParamName = GL_COLOR_ATTACHMENT0 + 11;
      template<> const value_type
        ColorAttachment<12>::s_glParamName = GL_COLOR_ATTACHMENT0 + 12;
      template<> const value_type
        ColorAttachment<13>::s_glParamName = GL_COLOR_ATTACHMENT0 + 13;
      template<> const value_type
        ColorAttachment<14>::s_glParamName = GL_COLOR_ATTACHMENT0 + 14;
      template<> const value_type
        ColorAttachment<15>::s_glParamName = GL_COLOR_ATTACHMENT0 + 15;

      const value_type  Depth::s_glParamName = GL_DEPTH_ATTACHMENT;
      const value_type  Stencil::s_glParamName = GL_STENCIL_ATTACHMENT;
      const value_type  DepthStencil::s_glParamName = 0;

#else
# error "WIP"
#endif
    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // Bind

  FramebufferObject::Bind::
    Bind(const FramebufferObject* a_fbo)
  {
    object_handle handle = a_fbo->GetHandle();
    glBindFramebuffer
      (p_framebuffer_object::target::Framebuffer::s_glParamName, handle);

    TLOC_ASSERT(gl::Error().Succeeded(),
      "OpenGL: Error with glBindFramebuffer");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FramebufferObject::Bind::
    ~Bind()
  {
    // On iOS, binding the frame buffer '0' corrupts the rendering and shows
    // a blank screen. Although binding to '0' is the correct way to unbind
    // the previously bound frame buffer, we see now harm (so far) in
    // not unbinding (especially since it solves the blank screen issue on
    // iOS)

    // glBindFramebuffer
    // (p_framebuffer_object::target::Framebuffer::s_glParamName, 0);
  }

  // ///////////////////////////////////////////////////////////////////////
  // FramebufferObject

  FramebufferObject::
    FramebufferObject()
  {
    object_handle handle;
    glGenFramebuffers(1, &handle);
    SetHandle(handle);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FramebufferObject::
    FramebufferObject(p_framebuffer_object::Default)
  {
    ResetHandle();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FramebufferObject::
    FramebufferObject(const this_type& a_other)
    : base_type(a_other)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FramebufferObject::
    ~FramebufferObject()
  {
    if (IsLastRef() && GetHandle() != 0)
    {
      object_handle handle = GetHandle();
      glDeleteFramebuffers(1, &handle);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FramebufferObject::error_type
    FramebufferObject::
    DoAttach(p_framebuffer_object::target::value_type a_target,
             p_framebuffer_object::attachment::value_type a_attachment,
             const rbo_type& a_rbo)
  {
    Bind b(this);
    TLOC_ASSERT(a_rbo.GetHandle() >= 0, "Invalid object ID for Renderbuffer");
    DoCheckInternalFormatAgainstTargetAttachment(a_target, a_attachment, a_rbo);

    glFramebufferRenderbuffer(a_target, a_attachment, GL_RENDERBUFFER,
                              a_rbo.GetHandle());

    gfx_t::gl_enum res = glCheckFramebufferStatus
      (p_framebuffer_object::target::Framebuffer::s_glParamName);
    TLOC_UNUSED(res);
    TLOC_ASSERT(res == GL_FRAMEBUFFER_COMPLETE,
      "Incomplete Framebuffer - did you forget to use a ColorAttachment first?");

    m_renderbufferObjects.push_back(a_rbo);

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#if defined (TLOC_OS_WIN)

  FramebufferObject::error_type
    FramebufferObject::
    DoAttach(p_framebuffer_object::target::value_type a_target,
             p_framebuffer_object::attachment::value_type a_attachment,
             const to_type& a_to)
  {
    Bind b(this);

    const to_type::Params& toParams = a_to.GetParams();
    DoCheckInternalFormatAgainstTargetAttachment(a_target, a_attachment, a_to);

    if (toParams.GetTextureType() == p_texture_object::target::Tex1D::s_glParamName)
    {
      glFramebufferTexture1D(a_target, a_attachment,
                             toParams.GetTextureType(), a_to.GetHandle(), 0);

      gfx_t::gl_enum res = glCheckFramebufferStatus
        (p_framebuffer_object::target::Framebuffer::s_glParamName);
      TLOC_UNUSED(res);
      TLOC_ASSERT(res == GL_FRAMEBUFFER_COMPLETE,
        "Incomplete Framebuffer - did you forget to use a ColorAttachment first?");
    }
    else if (toParams.GetTextureType() == p_texture_object::target::Tex2D::s_glParamName)
    {
      glFramebufferTexture2D(a_target, a_attachment,
                             toParams.GetTextureType(), a_to.GetHandle(), 0);

      gfx_t::gl_enum res = glCheckFramebufferStatus
        (p_framebuffer_object::target::Framebuffer::s_glParamName);
      TLOC_UNUSED(res);
      TLOC_ASSERT(res == GL_FRAMEBUFFER_COMPLETE,
        "Incomplete Framebuffer - did you forget to use a ColorAttachment first?");
    }
    else // if (toParams.GetTextureType() == p_texture_object::target::Tex3D::s_glParamName)
    {
      TLOC_ASSERT_WIP();
    }

    m_textureObjets.push_back(a_to);

    return ErrorSuccess;
  }

#elif defined (TLOC_OS_IPHONE)

  FramebufferObject::error_type
    FramebufferObject::
    DoAttach(p_framebuffer_object::target::value_type a_target,
             p_framebuffer_object::attachment::value_type a_attachment,
             const to_type& a_to)
  {
    TLOC_ASSERT(a_to.IsActive(),
      "TextureObject is NOT active - did you forget to call Activate()?");

    Bind b(this);

    const to_type::Params& toParams = a_to.GetParams();
    DoCheckInternalFormatAgainstTargetAttachment(a_target, a_attachment, a_to);

    if (toParams.GetTextureType() == p_texture_object::target::Tex2D::s_glParamName)
    {
      glFramebufferTexture2D(a_target, a_attachment,
                             toParams.GetTextureType(), a_to.GetHandle(), 0);

      gfx_t::gl_enum res = glCheckFramebufferStatus
        (p_framebuffer_object::target::Framebuffer::s_glParamName);
      TLOC_UNUSED(res);
      TLOC_ASSERT(res == GL_FRAMEBUFFER_COMPLETE,
        "Incomplete Framebuffer - did you forget to use a ColorAttachment first?");
    }

    m_textureObjets.push_back(a_to);

    return ErrorSuccess;
  }

#else
# error "WIP"
#endif

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Platform, typename T_RBO>
  void DoCheckSupportedDepthComponents(T_Platform, const T_RBO& a_rbo)
  {
    using namespace p_renderbuffer_object::internal_format;
    using p_texture_object::internal_format::value_type;

    value_type rboFormat = a_rbo.GetParams().GetFormatType();
    TLOC_UNUSED(rboFormat);
    TLOC_ASSERT(rboFormat == DepthComponent16::s_glParamName ||
                rboFormat == DepthComponent24::s_glParamName ||
                rboFormat == Depth24Stencil8::s_glParamName,
                "Incorrect internal format for specified attachment");
  }

  template <typename T_RBO>
  void DoCheckSupportedDepthComponents(core_plat::p_platform_info::iphone,
                                       const T_RBO& a_rbo)
  {
    using namespace p_renderbuffer_object::internal_format;
    using p_texture_object::internal_format::value_type;

    value_type rboFormat = a_rbo.GetParams().GetFormatType();
    TLOC_UNUSED(rboFormat);
    TLOC_ASSERT(rboFormat == DepthComponent24::s_glParamName ||
                rboFormat == Depth24Stencil8::s_glParamName,
                "Incorrect internal format for specified attachment");
  }

  void
    FramebufferObject::
    DoCheckInternalFormatAgainstTargetAttachment
      ( p_framebuffer_object::target::value_type a_target,
        p_framebuffer_object::attachment::value_type a_attachment,
        const rbo_type& a_rbo)
  {
    TLOC_UNUSED_3(a_target, a_attachment, a_rbo); // for release

    using  p_renderbuffer_object::internal_format::value_type;

    using namespace p_renderbuffer_object::internal_format;
    using namespace p_framebuffer_object::attachment;

    types::gl_int maxAttachments =
      DoGetMaxColorAttachments(core_plat::PlatformInfo::platform_type());

    // GL_DEPTH_COMPONENT16 is the only depth_renderable object. We can ensure
    // that that's the case by over-riding the format type, but instead we
    // will give the user the option to correct it
    if (a_attachment >= ColorAttachment<0>::s_glParamName &&
        a_attachment <= ColorAttachment<0>::s_glParamName + maxAttachments - 1)
    {
      value_type rboFormat = a_rbo.GetParams().GetFormatType();

      TLOC_UNUSED(rboFormat); // for release
      TLOC_ASSERT(rboFormat == RGBA4::s_glParamName ||
                  rboFormat == RGB565::s_glParamName ||
                  rboFormat == RGB5_A1::s_glParamName,
                  "Incorrect internal format for specified attachment");
    }
    else if (a_attachment == Depth::s_glParamName)
    {
      DoCheckSupportedDepthComponents(core_plat::PlatformInfo::platform_type(), a_rbo);
    }
    else if (a_attachment == Stencil::s_glParamName)
    {
      value_type rboFormat = a_rbo.GetParams().GetFormatType();

      TLOC_UNUSED(rboFormat); // for release
      TLOC_ASSERT(rboFormat == StencilIndex8::s_glParamName ||
                  rboFormat == Depth24Stencil8::s_glParamName,
                  "Incorrect internal format for specified attachment");
    }
    else
    {
      TLOC_ASSERT_FALSE("Unsupported internal format for specified attachment");
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    FramebufferObject::
    DoCheckInternalFormatAgainstTargetAttachment
      ( p_framebuffer_object::target::value_type a_target,
        p_framebuffer_object::attachment::value_type a_attachment,
        const to_type& a_to)
  {
    TLOC_UNUSED_3(a_target, a_attachment, a_to); // for release

    using  p_texture_object::internal_format::value_type;

    using namespace p_texture_object::internal_format;
    using namespace p_framebuffer_object::attachment;

    int maxAttachments =
      DoGetMaxColorAttachments(core_plat::PlatformInfo::platform_type());

    // GL_DEPTH_COMPONENT16 is the only depth_renderable object. We can ensure
    // that that's the case by over-riding the format type, but instead we
    // will give the user the option to correct it
    if (a_attachment >= ColorAttachment<0>::s_glParamName &&
        a_attachment <= ColorAttachment<0>::s_glParamName + maxAttachments - 1)
    {
      value_type toFormat = a_to.GetParams().GetInternalFormat();

      TLOC_UNUSED(toFormat); // for release
      TLOC_ASSERT(toFormat == Red::s_glParamName ||
                  toFormat == RG::s_glParamName ||
                  toFormat == RGB::s_glParamName ||
                  toFormat == RGBA::s_glParamName,
                  "Incorrect internal format for specified attachment");
    }
    else if (a_attachment == p_framebuffer_object::attachment::Depth::s_glParamName)
    {
      value_type toFormat = a_to.GetParams().GetInternalFormat();

      TLOC_UNUSED(toFormat); // for release
      TLOC_ASSERT(toFormat == DepthComponent::s_glParamName,
                  "Incorrect internal format for specified attachment");
    }
    else if (a_attachment == p_framebuffer_object::attachment::Stencil::s_glParamName)
    {
      value_type toFormat = a_to.GetParams().GetInternalFormat();

      TLOC_UNUSED(toFormat); // for release
      TLOC_ASSERT(toFormat ==
        p_texture_object::internal_format::DepthStencil::s_glParamName,
        "Incorrect internal format for specified attachment");
    }
    else
    {
      TLOC_ASSERT_FALSE("Unsupported internal format for specified attachment");
    }
  }

};};};

// ///////////////////////////////////////////////////////////////////////
// Explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_gl;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(FramebufferObject);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(FramebufferObject);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(FramebufferObject::Bind);