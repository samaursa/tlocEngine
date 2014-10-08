#include "tlocObject.h"

#include <tlocGraphics/opengl/tlocOpenGL.h>

TLOC_INTENTIONALLY_EMPTY_SOURCE_FILE();

namespace tloc { namespace graphics { namespace gl {

  ObjectBase::
    ObjectBase()
    : m_handle(0)
  { }

  bool
    ObjectBase::
    IsValid()
  {
    return m_handle != 0;
  }

  void
    ObjectBase::ResetHandle()
  {
    m_handle = 0;
  }

  void
    ObjectBase::
    SetHandle(object_handle a_handle)
  {
    TLOC_ASSERT(gl::IsPlatformInitialized(),
      "OpenGL platform not yet initialized");
    m_handle = a_handle;
  }

};};};