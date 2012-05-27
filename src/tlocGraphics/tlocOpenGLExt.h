#ifndef TLOC_OPEN_GL_EXT_H
#define TLOC_OPEN_GL_EXT_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>

namespace tloc { namespace graphics {

  ///-------------------------------------------------------------------------
  /// Currently used to wrap GLEW, may change later
  ///-------------------------------------------------------------------------
  class OpenGLExt
  {
  public:

    enum
    {
      error_none,
      error_init,
      error_already_init
    }; typedef u32 error_type;

    static error_type Initialize();
    static bool       IsInitialized();
    static u32        GetLastError();

  private:

    OpenGLExt();

    // TODO: Make atomic
    static bool m_initialized;
    static u32  m_error;

  };

};};

#endif