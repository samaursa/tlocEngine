#ifndef TLOC_OPEN_GL_EXT_H
#define TLOC_OPEN_GL_EXT_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/error/tlocErrorTypes.h>

namespace tloc { namespace graphics { namespace gl {

  ///-------------------------------------------------------------------------
  /// Currently used to wrap GLEW, may change later
  ///-------------------------------------------------------------------------
  class OpenGLExt
  {
  public:
    typedef core::error::Error    error_type;

  public:
    static error_type Initialize();
    static bool       IsInitialized();
    static error_type GetLastError();

  private:

    OpenGLExt();

    // TODO: Make atomic
    static bool       m_initialized;
    static error_type m_error;

  };

};};};

#endif