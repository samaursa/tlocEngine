#include "tlocRenderer.h"

#include <tlocGraphics/opengl/tlocOpenGLExt.h>

namespace tloc { namespace graphics {

  namespace
  {
    enum flags
    {
      initialized = 0,
      count
    };
  };

  Renderer::Renderer() : m_flags(count)
  {
    TLOC_ASSERT(GetCurrentObjectCount() <= 1,
                "More than one renderer simultaneously is not supported!");
  }

  Renderer::error_type Renderer::Initialize()
  {
    if (m_flags[initialized] == false)
    {
      error_type res = OpenGLExt::Initialize();
      if (res != common_error_types::error_initialize)
      { return res; }

      m_flags.Mark(initialized);
      return common_error_types::error_success;
    }

    return common_error_types::error_already_initialized;
  }

};};