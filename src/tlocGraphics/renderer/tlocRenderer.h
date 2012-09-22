#ifndef TLOC_GRAPHICS_RENDERER_H
#define TLOC_GRAPHICS_RENDERER_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/error/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics {

  class Renderer
  {
  public:
    typedef core::error::Error        error_type;
    typedef core::utils::Checkpoints  check_type;

  public:
    Renderer();
    error_type Initialize();

  private:
    check_type  m_flags;

  };

};};

#endif