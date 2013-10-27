#include "tlocRenderer.h"

#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>

namespace tloc { namespace graphics { namespace renderer {

  // ///////////////////////////////////////////////////////////////////////
  // static definitions

  namespace p_renderer {

    namespace depth_function {
      const value_type Never::s_glParamName         = GL_NEVER;
      const value_type Less::s_glParamName          = GL_LESS;
      const value_type Equal::s_glParamName         = GL_EQUAL;
      const value_type LessEqual::s_glParamName     = GL_LEQUAL;
      const value_type Greater::s_glParamName       = GL_GREATER;
      const value_type NotEqual::s_glParamName      = GL_NOTEQUAL;
      const value_type GreaterEqual::s_glParamName  = GL_GEQUAL;
      const value_type Always::s_glParamName        = GL_ALWAYS;
    };

    namespace blend_function {
      const value_type Zero::s_glParamName                      = GL_ZERO;
      const value_type One::s_glParamName                       = GL_ONE;
      const value_type SourceColor::s_glParamName               = GL_SRC_COLOR;
      const value_type OneMinusSourceColor::s_glParamName       = GL_ONE_MINUS_SRC1_COLOR;
      const value_type DestinationColor::s_glParamName          = GL_DST_COLOR;
      const value_type OneMinusDestinationColor::s_glParamName  = GL_ONE_MINUS_DST_COLOR;
      const value_type SourceAlpha::s_glParamName               = GL_SRC_ALPHA;
      const value_type OneMinusSourceAlpha::s_glParamName       = GL_ONE_MINUS_SRC_ALPHA;
      const value_type DestinationAlpha::s_glParamName          = GL_ONE_MINUS_SRC_ALPHA;
      const value_type OneMinusDestinationAlpha::s_glParamName  = GL_ONE_MINUS_SRC_ALPHA;
      const value_type ConstantColor::s_glParamName             = GL_CONSTANT_COLOR;
      const value_type OneMinusConstantColor::s_glParamName     = GL_ONE_MINUS_CONSTANT_COLOR;
      const value_type ConstantAlpha::s_glParamName             = GL_CONSTANT_ALPHA;
      const value_type OneMinusConstantAlpha::s_glParamName     = GL_ONE_MINUS_CONSTANT_ALPHA;
      const value_type SourceAlphaSaturate::s_glParamName       = GL_SRC_ALPHA_SATURATE;
      const value_type Source1Color::s_glParamName              = GL_SRC1_COLOR;
      const value_type OneMinusSource1Color::s_glParamName      = GL_ONE_MINUS_SRC1_COLOR;
      const value_type Source1Alpha::s_glParamName              = GL_SRC1_ALPHA;
      const value_type OneMinusSource1Alpha::s_glParamName      = GL_ONE_MINUS_SRC1_ALPHA;
    };

  };

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
  // Renderer_T<>::RenderOneFrame

  template <RENDERER_TEMPS>
  Renderer_T<RENDERER_PARAMS>::RenderOneFrame::
    RenderOneFrame()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  Renderer_T<RENDERER_PARAMS>::RenderOneFrame::
    RenderOneFrame(this_type& a_renderer)
    : m_renderer(a_renderer)
  { m_renderer.DoStart(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  Renderer_T<RENDERER_PARAMS>::RenderOneFrame::
    ~RenderOneFrame()
  { m_renderer.DoEnd(); }

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
    ApplyRenderSettings() const
  {
    glDepthFunc(m_params.GetDepthFunction());
    glBlendFunc(m_params.GetBlendFunction());

    for (enable_cont::iterator itr = m_params.GetFeaturesToEnable().begin(),
      itrEnd = m_params.GetFeaturesToEnable().end(); itr != itrEnd; ++itr)
    { glEnable(*itr); }

    clear_value_type clearBits = 0;
    for (clear_cont::iterator itr = m_params.GetClearBits().begin(),
      itrEnd = m_params.GetClearBits().end();
      itr != itrEnd; ++itr)
    { clearBits |= *itr; }
    glClear(clearBits);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  RENDERER_TYPE::error_type
    Renderer_T<RENDERER_PARAMS>::
    DoStart() const
  {
    TLOC_ASSERT(IsInitialized(), "Renderer not initialized");
    // enable FBO
    m_fboBinder = FramebufferObject::Bind(m_params.FBO());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  RENDERER_TYPE::error_type
    Renderer_T<RENDERER_PARAMS>::
    DoEnd() const
  {
    TLOC_ASSERT(IsInitialized(), "Renderer not initialized");
    m_fboBinder = FramebufferObject::Bind();
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Renderer);
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Renderer_depth32);
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Renderer_depth64);

};};};