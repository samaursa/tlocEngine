#include "tlocRenderer.h"

#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

#include <tlocGraphics/opengl/tlocOpenGLIncludes.h>
#include <tlocGraphics/opengl/tlocError.h>

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

    namespace enable_disable {

      const value_type Blend::s_glParamName         = GL_BLEND;
      const value_type DepthTest::s_glParamName     = GL_DEPTH_TEST;
      const value_type CullFace::s_glParamName      = GL_CULL_FACE;
      const value_type LineSmooth::s_glParamName    = GL_LINE_SMOOTH;
      const value_type PolygonSmooth::s_glParamName = GL_POLYGON_SMOOTH;

    };

    namespace clear {

      const value_type ColorBufferBit::s_glParamName   = GL_COLOR_BUFFER_BIT;
      const value_type DepthBufferBit::s_glParamName   = GL_DEPTH_BUFFER_BIT;
      const value_type StencilBufferBit::s_glParamName = GL_STENCIL_BUFFER_BIT;

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
    : m_clearColor(0.0f, 0.0f, 0.0f, 1.0f)
    , m_fbo(gfx_gl::FramebufferObject::GetDefaultFramebuffer())
    , m_clearBits(0)
  {
    using namespace p_renderer;

    DepthFunction<depth_function::Less>();
    BlendFunction<blend_function::One, blend_function::Zero>();
  }

  // ///////////////////////////////////////////////////////////////////////
  // Renderer_T<>::RenderOneFrame

  template <RENDERER_TEMPS>
  Renderer_T<RENDERER_PARAMS>::RenderOneFrame::
    RenderOneFrame()
    : m_renderer(nullptr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  Renderer_T<RENDERER_PARAMS>::RenderOneFrame::
    RenderOneFrame(const this_type* a_renderer)
    : m_renderer(a_renderer)
  {
    TLOC_ASSERT_NOT_NULL(m_renderer);
    m_renderer->DoStart();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  Renderer_T<RENDERER_PARAMS>::RenderOneFrame::
    RenderOneFrame(const RenderOneFrame& a_other)
    : m_renderer(a_other.m_renderer)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  Renderer_T<RENDERER_PARAMS>::RenderOneFrame::
    ~RenderOneFrame()
  {
    if (m_renderer)
    { m_renderer->DoEnd(); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  RENDERER_TYPE::RenderOneFrame&
    Renderer_T<RENDERER_PARAMS>::RenderOneFrame::
    operator=(RenderOneFrame a_other)
  {
    swap(a_other);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  void
    Renderer_T<RENDERER_PARAMS>::RenderOneFrame::
    swap(RenderOneFrame& a_other)
  {
    using core::swap;
    swap(m_renderer, a_other.m_renderer);
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
    ApplyRenderSettings() const
  {
    math_t::Vec4f32 col = m_params.m_clearColor.GetAs
      <gfx_t::p_color::format::RGBA, math_t::Vec4f32>();

    glClearColor(col[0], col[1], col[2], col[3]);
    glDepthFunc(m_params.GetDepthFunction());
    TLOC_ASSERT(gl::Error().Succeeded(), "glDepthFunc returned an error");
    glBlendFunc(m_params.GetBlendFunction().first,
                m_params.GetBlendFunction().second);
    TLOC_ASSERT(gl::Error().Succeeded(), "glBlenFunc returned an error");

    for (enable_cont::const_iterator itr = m_params.GetFeaturesToEnable().begin(),
      itrEnd = m_params.GetFeaturesToEnable().end(); itr != itrEnd; ++itr)
    {
      glEnable(*itr);
      TLOC_ASSERT(gl::Error().Succeeded(), "glEnable returned an error");
    }

    for (enable_cont::const_iterator itr = m_params.GetFeaturesToDisable().begin(),
      itrEnd = m_params.GetFeaturesToDisable().end(); itr != itrEnd; ++itr)
    {
      glDisable(*itr);
      TLOC_ASSERT(gl::Error().Succeeded(), "glDisable returned an error");
    }

    clear_value_type clearBits = m_params.GetClearBits();
    if (clearBits != -1)
    {
      glClear(m_params.GetClearBits());
      TLOC_ASSERT(gl::Error().Succeeded(), "glClear returned an error");
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  RENDERER_TYPE::error_type
    Renderer_T<RENDERER_PARAMS>::
    DoStart() const
  {
    // enable FBO
    m_fboBinder = fbo_type::Bind(m_params.m_fbo);

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  RENDERER_TYPE::error_type
    Renderer_T<RENDERER_PARAMS>::
    DoEnd() const
  {
    m_fboBinder = gfx_gl::FramebufferObject::Bind();

    return ErrorSuccess;
  }

  // ///////////////////////////////////////////////////////////////////////
  // default renderer

  // Default params choose the default framebuffer
  renderer_sptr g_defaultRenderer;

  renderer_sptr
    GetDefaultRenderer()
  {
    static bool constructDefaultRenderer = true;
    if (constructDefaultRenderer)
    {
      g_defaultRenderer.reset(new Renderer(Renderer::Params()));
      constructDefaultRenderer = false;
    }

    return g_defaultRenderer;
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template class Renderer_T<f32>;
  template class Renderer_T<f64>;

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Renderer);
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Renderer_depth32);
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Renderer_depth64);

};};};