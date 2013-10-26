#include "tlocFramebufferObject.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>
#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_framebuffer_object {

    namespace target {
      const value_type  DrawFramebuffer::s_glParamName = GL_DRAW_FRAMEBUFFER;
      const value_type  ReadFramebuffer::s_glParamName = GL_READ_FRAMEBUFFER;
    };

    namespace attachment {

      const value_type  MaxColorAttachments::s_glParamName = GL_MAX_COLOR_ATTACHMENTS;

      const value_type  ColorAttachment<0>::s_glParamName  = GL_COLOR_ATTACHMENT0;
      const value_type  ColorAttachment<1>::s_glParamName  = GL_COLOR_ATTACHMENT1;
      const value_type  ColorAttachment<2>::s_glParamName  = GL_COLOR_ATTACHMENT2;
      const value_type  ColorAttachment<3>::s_glParamName  = GL_COLOR_ATTACHMENT3;
      const value_type  ColorAttachment<4>::s_glParamName  = GL_COLOR_ATTACHMENT4;
      const value_type  ColorAttachment<5>::s_glParamName  = GL_COLOR_ATTACHMENT5;
      const value_type  ColorAttachment<6>::s_glParamName  = GL_COLOR_ATTACHMENT6;
      const value_type  ColorAttachment<7>::s_glParamName  = GL_COLOR_ATTACHMENT7;
      const value_type  ColorAttachment<8>::s_glParamName  = GL_COLOR_ATTACHMENT8;
      const value_type  ColorAttachment<9>::s_glParamName  = GL_COLOR_ATTACHMENT9;
      const value_type  ColorAttachment<10>::s_glParamName = GL_COLOR_ATTACHMENT10;
      const value_type  ColorAttachment<11>::s_glParamName = GL_COLOR_ATTACHMENT11;
      const value_type  ColorAttachment<12>::s_glParamName = GL_COLOR_ATTACHMENT12;
      const value_type  ColorAttachment<13>::s_glParamName = GL_COLOR_ATTACHMENT13;
      const value_type  ColorAttachment<14>::s_glParamName = GL_COLOR_ATTACHMENT14;
      const value_type  ColorAttachment<15>::s_glParamName = GL_COLOR_ATTACHMENT15;

      const value_type  Depth::s_glParamName = GL_DEPTH_ATTACHMENT;
      const value_type  Stencil::s_glParamName = GL_STENCIL_ATTACHMENT;
      const value_type  DepthStencil::s_glParamName = GL_DEPTH_STENCIL_ATTACHMENT;
    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // Bind

  FramebufferObject::Bind::
    Bind()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FramebufferObject::Bind::
    Bind(const FramebufferObject& a_fbo)
  {
    object_handle handle = a_fbo.GetHandle();
    glBindFramebuffer(GL_FRAMEBUFFER, handle);

    TLOC_ASSERT(gl::Error().Succeeded(),
      "OpenGL: Error with glBindFramebuffer");
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FramebufferObject::Bind::
    ~Bind()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
    SetHandle(0);
  }

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

  FramebufferObject::this_type&
    FramebufferObject::GetDefaultFramebuffer()
  {
    static FramebufferObject g_defaultFBO =
      FramebufferObject(p_framebuffer_object::Default());

    static bool checkFramebufferStatus = true;

    // Check the status of the Framebuffer once to ensure that there is indeed
    // a default Framebuffer with an ID of 0
    if (checkFramebufferStatus)
    {
      gfx_t::gl_enum res = glCheckFramebufferStatus(g_defaultFBO.GetHandle());
      TLOC_UNUSED(res);
      TLOC_ASSERT(res == GL_FRAMEBUFFER_COMPLETE,
        "Default Framebuffer doesn't appear to complete "
        "(or there may be no default Framebuffer in the first place)");
      checkFramebufferStatus = false;
    }

    return g_defaultFBO;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FramebufferObject::error_type
    FramebufferObject::
    DoAttach(p_framebuffer_object::target::value_type a_target,
             p_framebuffer_object::attachment::value_type a_attachment,
             const rbo_type& a_rbo)
  {
    Bind b(*this);
    glFramebufferRenderbuffer(a_target, a_attachment, GL_RENDERBUFFER,
                              a_rbo.GetHandle());

    m_renderbufferObjects.push_back(a_rbo);

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  FramebufferObject::error_type
    FramebufferObject::
    DoAttach(p_framebuffer_object::target::value_type a_target,
             p_framebuffer_object::attachment::value_type a_attachment,
             const to_type& a_to)
  {
    Bind b(*this);

    const to_type::Params& toParams = a_to.GetParams();

    if (toParams.GetTextureType() == p_texture_object::target::Tex1D::s_glParamName)
    {
      glFramebufferTexture1D(a_target, a_attachment,
                             toParams.GetTextureType(), a_to.GetHandle(), 0);
    }
    else if (toParams.GetTextureType() == p_texture_object::target::Tex2D::s_glParamName)
    {
      glFramebufferTexture2D(a_target, a_attachment,
                             toParams.GetTextureType(), a_to.GetHandle(), 0);
    }
    else // if (toParams.GetTextureType() == p_texture_object::target::Tex3D::s_glParamName)
    {
      TLOC_ASSERT_WIP();
    }

    m_textureObjets.push_back(a_to);

    return ErrorSuccess;
  }

  // ///////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(FramebufferObject);


};};};