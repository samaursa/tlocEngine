#include "tlocRenderer.h"
#include <tlocCore/platform/tlocPlatform.h>

namespace tloc { namespace graphics {

  //------------------------------------------------------------------------
  // Template Macros

#define RENDERER_BASE_TEMP    typename T_Derived
#define RENDERER_BASE_PARAMS  T_Derived
#define RENDERER_BASE_TYPE    typename RendererBase<RENDERER_BASE_PARAMS>

#define RENDERER_TEMP   typename T_Platform
#define RENDERER_PARAMS T_Platform
#define RENDERER_TYPE   typename Renderer_T<RENDERER_PARAMS>

  namespace
  {
    enum flags
    {
      initialized = 0,
      count
    };
  };

  //------------------------------------------------------------------------
  // RenderBase

  template <RENDERER_BASE_TEMP>
  RendererBase<RENDERER_BASE_PARAMS>::RendererBase() : m_flags(count)
  {
    TLOC_ASSERT(GetCurrentObjectCount() <= 1,
                "More than one renderer simultaneously is not supported!");
  }

  template <RENDERER_BASE_TEMP>
  RENDERER_BASE_TYPE::error_type
    RendererBase<RENDERER_BASE_PARAMS>::Initialize()
  {
    return static_cast<derived_type*>(this)->DoInitialize();
  }

  template <RENDERER_BASE_TEMP>
  bool RendererBase<RENDERER_BASE_PARAMS>::IsInitialized()
  {
    return GetCurrentObjectCount() > 0;
  }

  //------------------------------------------------------------------------
  // Renderer - Generic Implementation

  template <RENDERER_TEMP>
  RENDERER_TYPE::error_type
    Renderer_T<RENDERER_PARAMS>::DoInitialize()
  {
    m_flags.Mark(initialized);
    return common_error_types::error_success;
  }

};};

//------------------------------------------------------------------------
// Renderer - Windows Implementation
#if defined(TLOC_WIN32) || defined(TLOC_WIN64)
# include <tlocGraphics/opengl/tlocOpenGLExt.h>

namespace tloc { namespace graphics {

#define RENDERER_WIN_TEMP
#define RENDERER_WIN_PARAMS core::Platform_win
#define RENDERER_WIN_TYPE   Renderer_T<RENDERER_WIN_PARAMS>

  RENDERER_WIN_TYPE::error_type
    Renderer_T<RENDERER_WIN_PARAMS>::DoInitialize()
  {
    if (m_flags[initialized] == false)
    {
      error_type res = gl::OpenGLExt::Initialize();
      if (res != common_error_types::error_initialize)
      { return res; }

      m_flags.Mark(initialized);
      return common_error_types::error_success;
    }

    return common_error_types::error_already_initialized;
  }

};};
#endif

//------------------------------------------------------------------------
// Explicitly Instantiate Renderer

namespace tloc { namespace graphics {
  template class RendererBase<Renderer_T<> >;
};};