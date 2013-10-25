#include "tlocFramebufferObject.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

#include <tlocGraphics/opengl/tlocOpenGL.h>
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
    Bind(const FramebufferObject& a_fbo)
  {
    object_handle handle = a_fbo.GetHandle();
    glBindFramebuffer(GL_FRAMEBUFFER, handle);

    TLOC_ASSERT(gl::Error().Succeeded(),
      "OpenGL: Error with glRenderbufferStorage");
  }

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
    ~FramebufferObject()
  {
    if (IsLastRef())
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
    glFramebufferTexture2D(a_target, a_attachment,
      a_to.GetParams().GetTextureType(), a_to.GetHandle(), 0);

    m_textureObjets.push_back(a_to);

    return ErrorSuccess;
  }

  // ///////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(FramebufferObject);


};};};