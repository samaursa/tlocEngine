#include "tlocRenderer.h"

#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/logging/tlocLogger.h>

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

#if defined (TLOC_OS_WIN)

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

#elif defined (TLOC_OS_IPHONE)

      const value_type Zero::s_glParamName                      = GL_ZERO;
      const value_type One::s_glParamName                       = GL_ONE;
      const value_type SourceColor::s_glParamName               = GL_SRC_COLOR;
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

      const value_type OneMinusSourceColor::s_glParamName       = 0;
      const value_type Source1Color::s_glParamName              = 0;
      const value_type OneMinusSource1Color::s_glParamName      = 0;
      const value_type Source1Alpha::s_glParamName              = 0;
      const value_type OneMinusSource1Alpha::s_glParamName      = 0;

#else
# error "WIP"
#endif

    };

    namespace enable_disable {

#if defined (TLOC_OS_WIN)

      const value_type Blend::s_glParamName         = GL_BLEND;
      const value_type DepthTest::s_glParamName     = GL_DEPTH_TEST;
      const value_type CullFace::s_glParamName      = GL_CULL_FACE;
      const value_type LineSmooth::s_glParamName    = GL_LINE_SMOOTH;
      const value_type PolygonSmooth::s_glParamName = GL_POLYGON_SMOOTH;

#elif defined (TLOC_OS_IPHONE)

      const value_type Blend::s_glParamName         = GL_BLEND;
      const value_type DepthTest::s_glParamName     = GL_DEPTH_TEST;
      const value_type CullFace::s_glParamName      = GL_CULL_FACE;
      const value_type LineSmooth::s_glParamName    = 0;
      const value_type PolygonSmooth::s_glParamName = 0;

#else
# error
#endif

    };

    namespace clear {

      const value_type ColorBufferBit::s_glParamName   = GL_COLOR_BUFFER_BIT;
      const value_type DepthBufferBit::s_glParamName   = GL_DEPTH_BUFFER_BIT;
      const value_type StencilBufferBit::s_glParamName = GL_STENCIL_BUFFER_BIT;

    };

    namespace cull_face {

      const value_type Front::s_glParamName            = GL_FRONT;
      const value_type Back::s_glParamName             = GL_BACK;
      const value_type FrontAndBack::s_glParamName     = GL_FRONT_AND_BACK;

    };

    namespace polygon_mode {

#if defined (TLOC_OS_WIN)

      const value_type Point::s_glParamName            = GL_POINT;
      const value_type Line::s_glParamName             = GL_LINE;
      const value_type Fill::s_glParamName             = GL_FILL;

#elif defined (TLOC_OS_IPHONE)

      const value_type Point::s_glParamName            = TLOC_GL_UNSUPPORTED;
      const value_type Line::s_glParamName             = TLOC_GL_UNSUPPORTED;
      const value_type Fill::s_glParamName             = GL_TRUE;

#else
# error "WIP"
#endif

    };

    // ///////////////////////////////////////////////////////////////////////
    // Renderer_T<>Params

    Params::
      Params()
      : m_clearColor(0.0f, 0.0f, 0.0f, 1.0f)
      , m_pointSize(1.0f)
      , m_dim(core_ds::Variadic<dimension_type::value_type, 2>(0, 0))
      , m_clearBits(0)
      , m_faceToCull(GL_NONE)
      , m_polyMode(p_renderer::polygon_mode::Fill::s_glParamName)
    {
      using namespace p_renderer;

      SetDepthFunction<depth_function::Less>();
      SetBlendFunction<blend_function::One, blend_function::Zero>();

      GLint viewDim[4];
      glGetIntegerv(GL_VIEWPORT, viewDim);
      TLOC_ASSERT(gl::Error().Succeeded(), "Failed to get viewport dimensions");
      m_dim[0] = viewDim[2];
      m_dim[1] = viewDim[3];
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    Params::
      Params(dimension_type a_dim)
      : m_clearColor(0.0f, 0.0f, 0.0f, 1.0f)
      , m_dim(a_dim)
      , m_clearBits(0)
    {
      using namespace p_renderer;

      SetDepthFunction<depth_function::Less>();
      SetBlendFunction<blend_function::One, blend_function::Zero>();
    }

    // -----------------------------------------------------------------------

    Params  GetParamsCommon(Params::fbo_sptr a_fbo,
                            gfx_t::Dimension2 a_dim,
                            const gfx_t::Color& a_clearColor)
    {
      gfx_rend::Renderer::Params pRtt;
      pRtt.SetFBO(a_fbo);
      pRtt.AddClearBit<clear::ColorBufferBit>()
          .AddClearBit<clear::DepthBufferBit>() 
          .Disable<enable_disable::CullFace>()
          .Enable<enable_disable::DepthTest>() 
          .SetClearColor(a_clearColor) 
          .SetDimensions(a_dim);

      return pRtt;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    Params  GetParamsCommonNoDepth(Params::fbo_sptr a_fbo,
                                   gfx_t::Dimension2 a_dim,
                                   const gfx_t::Color& a_clearColor)
    {
      gfx_rend::Renderer::Params pRtt;
      pRtt.SetFBO(a_fbo);
      pRtt.AddClearBit<clear::ColorBufferBit>()
          .AddClearBit<clear::DepthBufferBit>() 
          .Disable<enable_disable::DepthTest>() 
          .Disable<enable_disable::CullFace>() 
          .SetClearColor(a_clearColor) 
          .SetDimensions(a_dim);

      return pRtt;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    Params  GetParamsCommonNoDepthNoColorClear
      (Params::fbo_sptr a_fbo, gfx_t::Dimension2 a_dim)
    {
      gfx_rend::Renderer::Params pRtt;
      pRtt.SetFBO(a_fbo);
      pRtt.AddClearBit<clear::DepthBufferBit>() 
          .Disable<enable_disable::DepthTest>() 
          .Disable<enable_disable::CullFace>() 
          .SetDimensions(a_dim);

      return pRtt;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    Params  GetParamsShadow(Params::fbo_sptr a_fbo, gfx_t::Dimension2 a_dim, 
                            const gfx_t::Color& a_clearColor)
    {
      gfx_rend::Renderer::Params pRtt;
      pRtt.SetFBO(a_fbo);
      pRtt.AddClearBit<clear::ColorBufferBit>()
          .AddClearBit<clear::DepthBufferBit>() 
          .Enable<enable_disable::DepthTest>()
          .Enable<enable_disable::CullFace>()
          .Cull<cull_face::Front>()
          .SetClearColor(a_clearColor) 
          .SetDimensions(a_dim);

      return pRtt;
    }

  };

  //------------------------------------------------------------------------
  // Template Macros

#define RENDERER_TEMPS  typename T_DepthPrecision
#define RENDERER_PARAMS T_DepthPrecision
#define RENDERER_TYPE   typename Renderer_T<RENDERER_PARAMS>

  // ///////////////////////////////////////////////////////////////////////
  // Renderer_T<>::RenderOneFrame

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
    ~RenderOneFrame()
  {
    TLOC_ASSERT_NOT_NULL(m_renderer);
    m_renderer->DoEnd();
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
  RENDERER_TYPE::this_type&
    Renderer_T<RENDERER_PARAMS>::
    AddDrawCommand(const command_type& a_command)
  { m_pass.AddDrawCommand(a_command); return *this; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#if defined (TLOC_OS_IPHONE)
  void glPolygonMode(GLenum , GLenum a_mode)
  {
    TLOC_LOG_GFX_WARN_IF(a_mode != p_renderer::polygon_mode::Fill::s_glParamName)
      << "Invalid polygon mode! OpenGL ES 2.0 only supports Fill";
  }
  void glPointSize(GLfloat a_size)
  {
    TLOC_LOG_GFX_WARN_IF(a_size != 1.0f)
      << "Invalid point size! OpenGL ES 2.0 only supports a default size of 1.0f";
  }
#endif

  template <RENDERER_TEMPS>
  RENDERER_TYPE::error_type
    Renderer_T<RENDERER_PARAMS>::
    ApplyRenderSettings() const
  {
    fbo_type::bind b(*m_params.GetFBO().get());

    math_t::Vec4f32 col = m_params.GetClearColor().template GetAs
      <gfx_t::p_color::format::RGBA, math_t::Vec4f32>();

    const dimension_type dim = m_params.GetDimensions();

    using core_utils::CastNumber;

    TLOC_LOG_GFX_ERR_IF(dim[0] == 0 || dim[1] == 0)
      << "One or both dimensions of the viewport is 0: "
      << dim[0] << ", " << dim[1];

    glViewport(0, 0, CastNumber<GLsizei>(dim[0]), CastNumber<GLsizei>(dim[1]) );

    glClearColor(col[0], col[1], col[2], col[3]);
    glDepthFunc(m_params.GetDepthFunction());
    TLOC_ASSERT(gl::Error().Succeeded(), "glDepthFunc returned an error");
    glBlendFunc(m_params.GetBlendFunction().first,
                m_params.GetBlendFunction().second);
    TLOC_ASSERT(gl::Error().Succeeded(), "glBlenFunc returned an error");
    glPolygonMode(GL_FRONT_AND_BACK, m_params.GetPolygonMode());
    TLOC_ASSERT(gl::Error().Succeeded(), "glPolygonMode returned an error");
    glPointSize(m_params.GetPointSize());
    TLOC_ASSERT(gl::Error().Succeeded(), "glPointSize returned an error");

    for (auto itr = m_params.GetFeaturesToEnable().begin(), 
              itrEnd = m_params.GetFeaturesToEnable().end(); itr != itrEnd; ++itr)
    {
      if (*itr == p_renderer::enable_disable::CullFace::s_glParamName)
      {
        if (m_params.GetFaceToCull() != GL_NONE)
        { glCullFace(m_params.GetFaceToCull()); }
        else
        {
          TLOC_LOG_GFX_WARN() << 
            "Face culling enabled but not specified (Front, Back or FrontAndBack";
        }

        TLOC_ASSERT(gl::Error().Succeeded(), "glEnable returned an error");
      }

      glEnable(*itr);
      TLOC_ASSERT(gl::Error().Succeeded(), "glEnable returned an error");
    }

    for (auto itr = m_params.GetFeaturesToDisable().begin(), 
              itrEnd = m_params.GetFeaturesToDisable().end(); itr != itrEnd; ++itr)
    {
      glDisable(*itr);
      TLOC_ASSERT(gl::Error().Succeeded(), "glDisable returned an error");
    }

    auto clearBits = m_params.GetClearBits();
    if (clearBits != -1)
    {
      glClear(m_params.GetClearBits());
      TLOC_ASSERT(gl::Error().Succeeded(), "glClear returned an error");
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  void
    Renderer_T<RENDERER_PARAMS>::
    Render()
  { 
    RenderOneFrame rof(this);
    m_pass.Draw();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  RENDERER_TYPE::error_type
    Renderer_T<RENDERER_PARAMS>::
    DoStart() const
  {
    // enable FBO
    m_fboBinder = 
      core_sptr::MakeUnique<fbo_bind_ptr::value_type>( *m_params.GetFBO().get() );

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <RENDERER_TEMPS>
  RENDERER_TYPE::error_type
    Renderer_T<RENDERER_PARAMS>::
    DoEnd() const
  {
    m_fboBinder.reset();
    gfx_gl::texture_units::image_units::ResetCount();

    return ErrorSuccess;
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template class Renderer_T<f32>;
  template class Renderer_T<f64>;

};};};

// -----------------------------------------------------------------------
// explicit instantiation

using namespace tloc::gfx_rend;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Renderer_depth32);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(Renderer_depth32);

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Renderer_depth64);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(Renderer_depth64);

TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(Renderer_depth32::RenderOneFrame);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(Renderer_depth64::RenderOneFrame);