#ifndef TLOC_GRAPHICS_RENDERER_H
#define TLOC_GRAPHICS_RENDERER_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/tlocAssert.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/utilities/tlocObjectCounter.h>
#include <tlocCore/error/tlocError.h>
#include <tlocCore/platform/tlocPlatform.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>

#include <tlocGraphics/error/tlocErrorTypes.h>
#include <tlocGraphics/types/tlocColor.h>
#include <tlocGraphics/opengl/tlocFramebufferObject.h>

#include <tlocGraphics/renderer/tlocDrawCommand.h>

namespace tloc { namespace graphics { namespace renderer {

  // ///////////////////////////////////////////////////////////////////////
  // Renderer

  namespace p_renderer
  {
    namespace depth_function
    {
      typedef s32                     value_type;

      struct Never        { static const value_type s_glParamName; };
      struct Less         { static const value_type s_glParamName; };
      struct Equal        { static const value_type s_glParamName; };
      struct LessEqual    { static const value_type s_glParamName; };
      struct Greater      { static const value_type s_glParamName; };
      struct NotEqual     { static const value_type s_glParamName; };
      struct GreaterEqual { static const value_type s_glParamName; };
      struct Always       { static const value_type s_glParamName; };
    };

    namespace blend_function
    {
      typedef s32                     value_type;

      struct Zero                     { static const value_type s_glParamName; };
      struct One                      { static const value_type s_glParamName; };
      struct SourceColor              { static const value_type s_glParamName; };
      struct OneMinusSourceColor      { static const value_type s_glParamName; };
      struct DestinationColor         { static const value_type s_glParamName; };
      struct OneMinusDestinationColor { static const value_type s_glParamName; };
      struct SourceAlpha              { static const value_type s_glParamName; };
      struct OneMinusSourceAlpha      { static const value_type s_glParamName; };
      struct DestinationAlpha         { static const value_type s_glParamName; };
      struct OneMinusDestinationAlpha { static const value_type s_glParamName; };
      struct ConstantColor            { static const value_type s_glParamName; };
      struct OneMinusConstantColor    { static const value_type s_glParamName; };
      struct ConstantAlpha            { static const value_type s_glParamName; };
      struct OneMinusConstantAlpha    { static const value_type s_glParamName; };
      struct SourceAlphaSaturate      { static const value_type s_glParamName; };
      struct Source1Color             { static const value_type s_glParamName; };
      struct OneMinusSource1Color     { static const value_type s_glParamName; };
      struct Source1Alpha             { static const value_type s_glParamName; };
      struct OneMinusSource1Alpha     { static const value_type s_glParamName; };
    };

    namespace enable_disable
    {
      typedef s32                     value_type;

      struct Blend                    { static const value_type s_glParamName; };
      struct DepthTest                { static const value_type s_glParamName; };
      struct CullFace                 { static const value_type s_glParamName; };
      struct LineSmooth               { static const value_type s_glParamName; };
      struct PolygonSmooth            { static const value_type s_glParamName; };
    };

    namespace clear
    {
      typedef s32                     value_type;

      struct ColorBufferBit           { static const value_type s_glParamName; };
      struct DepthBufferBit           { static const value_type s_glParamName; };
      struct StencilBufferBit         { static const value_type s_glParamName; };

    };

    namespace cull_face
    {
      typedef s32                     value_type;

      struct Front                    { static const value_type s_glParamName; };
      struct Back                     { static const value_type s_glParamName; };
      struct FrontAndBack             { static const value_type s_glParamName; };
    };

    namespace polygon_mode
    {
      typedef s32                     value_type;

      struct Point                    { static const value_type s_glParamName; };
      struct Line                     { static const value_type s_glParamName; };
      struct Fill                     { static const value_type s_glParamName; };
    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // Renderer_T<>

  template <typename T_DepthPrecision = f32>
  class Renderer_T
  {
  public:
    typedef Renderer_T<T_DepthPrecision>              this_type;

    typedef gfx_t::Color                              color_type;
    typedef p_renderer::depth_function::value_type    depth_function_value_type;
    typedef p_renderer::blend_function::value_type    blend_function_value_type;
    typedef p_renderer::enable_disable::value_type    enable_value_type;
    typedef p_renderer::enable_disable::value_type    disable_value_type;
    typedef p_renderer::clear::value_type             clear_value_type;
    typedef p_renderer::cull_face::value_type         cull_face_value_type;
    typedef p_renderer::polygon_mode::value_type      polygon_mode;
    typedef core::Pair<blend_function_value_type,
                       blend_function_value_type>     blend_pair_type;

    typedef core_conts::tl_array
            <enable_value_type>::type                 enable_cont;
    typedef core_conts::tl_array
            <disable_value_type>::type                disable_cont;

    typedef T_DepthPrecision                          depth_value_type;
    typedef s32                                       stencil_value_type;

    typedef gl::FramebufferObject                     fbo_type;
    typedef fbo_type::bind_uptr                       fbo_bind_ptr;
    typedef gl::framebuffer_object_sptr               fbo_sptr;
    typedef fbo_type::dimension_type                  dimension_type;
    typedef core_err::Error                           error_type;

    typedef RenderPass                                render_pass;
    typedef render_pass::command_type                 command_type;
    typedef render_pass::size_type                    size_type;

  public:
    struct Params
    {
    public:
      typedef Params                                  this_type;

    public:
      Params();
      Params(dimension_type a_dim);

      template <typename T_DepthFunction>
      this_type& SetDepthFunction();

      template <typename T_Source, typename T_Destination>
      this_type& SetBlendFunction();

      template <typename T_Enable>
      this_type& Enable();

      template <typename T_Disable>
      this_type& Disable();

      template <typename T_ClearValue>
      this_type& AddClearBit();

      template <typename T_Face>
      this_type& Cull();

      template <typename T_Face>
      this_type& PolygonMode();

      TLOC_DECL_AND_DEF_GETTER
        (depth_function_value_type, GetDepthFunction, m_depthFunction);
      TLOC_DECL_AND_DEF_GETTER
        (blend_pair_type, GetBlendFunction, m_blendFunction);
      TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
        (enable_cont, GetFeaturesToEnable, m_enableFeatures);
      TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
        (disable_cont, GetFeaturesToDisable, m_disableFeatures);
      TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
        (clear_value_type, GetClearBits, m_clearBits);
      TLOC_DECL_AND_DEF_GETTER
        (cull_face_value_type, GetFaceToCull, m_faceToCull);
      TLOC_DECL_AND_DEF_GETTER
        (polygon_mode, GetPolygonMode, m_polyMode);

      TLOC_DECL_AND_DEF_GETTER(color_type, GetClearColor, m_clearColor);
      TLOC_DECL_AND_DEF_SETTER_CHAIN(color_type, SetClearColor, m_clearColor);

      TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(fbo_sptr, GetFBO, m_fbo);
      TLOC_DECL_AND_DEF_SETTER_CHAIN(fbo_sptr, SetFBO, m_fbo);

      TLOC_DECL_AND_DEF_GETTER(dimension_type, GetDimensions, m_dim);
      TLOC_DECL_AND_DEF_SETTER_CHAIN(dimension_type, SetDimensions, m_dim);

    private:
      color_type                  m_clearColor;
      fbo_sptr                    m_fbo;
      dimension_type              m_dim;
      depth_function_value_type   m_depthFunction;
      blend_pair_type             m_blendFunction;
      enable_cont                 m_enableFeatures;
      disable_cont                m_disableFeatures;
      clear_value_type            m_clearBits;
      cull_face_value_type        m_faceToCull;
      polygon_mode                m_polyMode;
    };

  public:
    struct RenderOneFrame
      : core_bclass::NonCopyable_I
    {
      explicit RenderOneFrame(const this_type* a_renderer);
      ~RenderOneFrame();

    private:
      const this_type* m_renderer;
    }; friend struct RenderOneFrame;
    TLOC_TYPEDEF_UNIQUE_PTR(RenderOneFrame, render_one_frame);

  public:
    Renderer_T(const Params& a_params);

    this_type&        AddDrawCommand(const command_type& a_command);

    error_type        ApplyRenderSettings() const;
    void              Render();

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(Params, GetParams, m_params);
    TLOC_DECL_AND_DEF_SETTER(Params, SetParams, m_params);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumDrawCalls, m_pass.GetNumDrawCalls());

  private:
    error_type  DoStart() const;
    error_type  DoEnd() const;

  private:
    Params                      m_params;
    mutable fbo_bind_ptr        m_fboBinder;
    render_pass                 m_pass;
  };

  // -----------------------------------------------------------------------
  // swap

  template <typename T_DepthPrecision>
  void swap(typename Renderer_T<T_DepthPrecision>::RenderOneFrame& a,
            typename Renderer_T<T_DepthPrecision>::RenderOneFrame& b)
  { a.swap(b); }

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_DepthPrecision>
  template <typename T_DepthFunction>
  typename Renderer_T<T_DepthPrecision>::Params::this_type&
    Renderer_T<T_DepthPrecision>::Params::
    SetDepthFunction()
  {
    using namespace p_renderer::depth_function;

    tloc::type_traits::AssertTypeIsSupported
      <T_DepthFunction,
      Never, Less, Equal, LessEqual, Greater, NotEqual, GreaterEqual,
      Always>();

    m_depthFunction = T_DepthFunction::s_glParamName;
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DepthPrecision>
  template <typename T_Source, typename T_Destination>
  typename Renderer_T<T_DepthPrecision>::Params::this_type&
    Renderer_T<T_DepthPrecision>::Params::
    SetBlendFunction()
  {
    using namespace p_renderer::blend_function;

    tloc::type_traits::AssertTypeIsSupported
      <T_Source,
      Zero, One, SourceColor, OneMinusSourceColor, DestinationColor,
      OneMinusDestinationColor, SourceAlpha, OneMinusSourceAlpha,
      DestinationAlpha, OneMinusDestinationAlpha, ConstantColor,
      OneMinusConstantColor, ConstantAlpha,
      OneMinusConstantAlpha, SourceAlphaSaturate, Source1Color,
      OneMinusSource1Color, Source1Alpha, OneMinusSourceAlpha>();

    tloc::type_traits::AssertTypeIsSupported
      <T_Destination,
      Zero, One, SourceColor, OneMinusSourceColor, DestinationColor,
      OneMinusDestinationColor, SourceAlpha, OneMinusSourceAlpha,
      DestinationAlpha, OneMinusDestinationAlpha, ConstantColor,
      OneMinusConstantColor, ConstantAlpha,
      OneMinusConstantAlpha, SourceAlphaSaturate, Source1Color,
      OneMinusSource1Color, Source1Alpha, OneMinusSourceAlpha>();

    m_blendFunction.first = T_Source::s_glParamName;
    m_blendFunction.second = T_Destination::s_glParamName;
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DepthPrecision>
  template <typename T_Enable>
  typename Renderer_T<T_DepthPrecision>::Params::this_type&
    Renderer_T<T_DepthPrecision>::Params::
    Enable()
  {
    using namespace p_renderer::enable_disable;

    tloc::type_traits::AssertTypeIsSupported
      <T_Enable,
      Blend, DepthTest, CullFace, LineSmooth, PolygonSmooth>();

    TLOC_ASSERT(core::find_all(m_disableFeatures, T_Enable::s_glParamName) ==
      m_disableFeatures.end(), "You are disabling then enabling the feature");
    m_enableFeatures.push_back(T_Enable::s_glParamName);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DepthPrecision>
  template <typename T_Enable>
  typename Renderer_T<T_DepthPrecision>::Params::this_type&
    Renderer_T<T_DepthPrecision>::Params::
    Disable()
  {
    using namespace p_renderer::enable_disable;

    tloc::type_traits::AssertTypeIsSupported
      <T_Enable,
      Blend, DepthTest, CullFace, LineSmooth, PolygonSmooth>();

    TLOC_ASSERT(core::find_all(m_enableFeatures, T_Enable::s_glParamName) ==
      m_enableFeatures.end(), "You are enabling then disabling the feature");
    m_disableFeatures.push_back(T_Enable::s_glParamName);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DepthPrecision>
  template <typename T_ClearValue>
  typename Renderer_T<T_DepthPrecision>::Params::this_type&
    Renderer_T<T_DepthPrecision>::Params::
    AddClearBit()
  {
    using namespace p_renderer::clear;

    tloc::type_traits::AssertTypeIsSupported
      <T_ClearValue,
       ColorBufferBit, DepthBufferBit, StencilBufferBit>();

    m_clearBits |= T_ClearValue::s_glParamName;
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DepthPrecision>
  template <typename T_Face> 
  typename Renderer_T<T_DepthPrecision>::Params::this_type&
    Renderer_T<T_DepthPrecision>::Params::
    Cull()
  {
    using namespace p_renderer::cull_face;

    tloc::type_traits::AssertTypeIsSupported
      <T_Face,
       Front, Back, FrontAndBack>();

    m_faceToCull = T_Face::s_glParamName;
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_DepthPrecision>
  template <typename T_Mode> 
  typename Renderer_T<T_DepthPrecision>::Params::this_type&
    Renderer_T<T_DepthPrecision>::Params::
    PolygonMode()
  {
    using namespace p_renderer::polygon_mode;

    tloc::type_traits::AssertTypeIsSupported
      <T_Mode,
       Point, Line, Fill>();

    m_polyMode = T_Mode::s_glParamName;
    return *this;
  }

  // -----------------------------------------------------------------------
  // typedefs

  typedef Renderer_T<f32>               Renderer;
  typedef Renderer_T<f32>               Renderer_depth32;
  typedef Renderer_T<f64>               Renderer_depth64;

  TLOC_TYPEDEF_ALL_SMART_PTRS(Renderer, renderer);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Renderer_depth32, renderer_depth32);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Renderer_depth64, renderer_depth64);

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(Renderer, renderer);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(Renderer_depth32, renderer_depth32);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(Renderer_depth64, renderer_depth64);

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(Renderer_T<f32>);
  TLOC_EXTERN_TEMPLATE_CLASS(Renderer_T<f64>);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_rend::Renderer);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_rend::Renderer_depth32);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_rend::Renderer_depth64);

TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_rend::Renderer);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_rend::Renderer_depth32);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_rend::Renderer_depth64);

#endif