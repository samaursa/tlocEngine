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

  tl_size rendererCount = 0;

  Renderer::Renderer() : m_flags(count)
  {
    ++rendererCount;
    TLOC_ASSERT(rendererCount <= 1, "More than one renderer not supported!");
  }

  Renderer::error_type Renderer::Initialize()
  {
    TLOC_ASSERT(m_flags[initialized] == false, "Renderer already initialized");

    if (OpenGLExt::Initialize() != OpenGLExt::error_none)
    { return common_error_types::error_initialize; }

    m_flags.Mark(initialized);
    return common_error_types::error_success;
  }

};};