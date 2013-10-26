#include "tlocRenderer.h"
#include <tlocCore/platform/tlocPlatform.h>

namespace tloc { namespace graphics { namespace renderer {

  //------------------------------------------------------------------------
  // Template Macros

#define RENDERER_TEMPS  typename T_DepthPrecision
#define RENDERER_PARAMS T_DepthPrecision
#define RENDERER_TYPE   typename Renderer_T<RENDERER_PARAMS>

  // ///////////////////////////////////////////////////////////////////////
  // Renderer_T<>Params

  template <RENDERER_TEMPS>
  Renderer_T<RENDERER_TEMPS>::Params::
    Params()
  {
    using namespace p_renderer::depth_function;
    using namespace p_renderer::blend_function;
    using namespace p_renderer::enable;
  }

  // ///////////////////////////////////////////////////////////////////////
  // Renderer_T<>

  template <RENDERER_TEMPS>
  Renderer_T<RENDERER_PARAMS>::
    Renderer_T(const Params& a_params)
    : m_params(a_params)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  RENDERER_TYPE::error_type
    Renderer_T<RENDERER_PARAMS>::
    Start() const
  {
    TLOC_ASSERT(IsInitialized(), "Renderer not initialized");
    // enable FBO
    m_fboBinder = FramebufferObject::Bind(m_params.FBO());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  RENDERER_TYPE::error_type
    Renderer_T<RENDERER_PARAMS>::
    End() const
  {
    TLOC_ASSERT(IsInitialized(), "Renderer not initialized");
    m_fboBinder = FramebufferObject::Bind();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  RENDERER_TYPE::error_type
    Renderer_T<RENDERER_PARAMS>::
    DoInitialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  RENDERER_TYPE::error_type
    Renderer_T<RENDERER_PARAMS>::
    DoDestroy()
  { return ErrorSuccess; }


};};};