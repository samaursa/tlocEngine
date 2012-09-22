#ifndef TLOC_GRAPHICS_RENDERER_H
#define TLOC_GRAPHICS_RENDERER_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/utilities/tlocObjectCounter.h>
#include <tlocCore/error/tlocError.h>
#include <tlocGraphics/error/tlocErrorTypes.h>

namespace tloc { namespace graphics {

  class Renderer : core::utils::ObjectCounter<Renderer>
  {
  public:
    typedef core::utils::ObjectCounter<Renderer>  base_type;
    typedef core::error::Error                    error_type;
    typedef core::utils::Checkpoints              check_type;

  public:
    Renderer();
    error_type Initialize();

    using base_type::GetCurrentObjectCount;

  private:
    check_type  m_flags;

  };

};};

#endif