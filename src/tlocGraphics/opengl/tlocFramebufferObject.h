#ifndef _TLOC_GRAPHICS_GL_FRAMEBUFFER_OBJECT_H_
#define _TLOC_GRAPHICS_GL_FRAMEBUFFER_OBJECT_H_

#include <tlocCore/tloc_core.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>

#include <tlocGraphics/opengl/tlocObject.h>

namespace tloc { namespace graphics { namespace gl {

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

  public:
    struct Bind
    {
      Bind(const FramebufferObject& a_fbo);
      ~Bind();

    }; friend struct Bind;

  public:
    FramebufferObject();
    ~FramebufferObject();
  };

};};};

#endif