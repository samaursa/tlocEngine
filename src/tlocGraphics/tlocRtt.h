#ifndef _TLOC_GRAPHICS_RTT_H_
#define _TLOC_GRAPHICS_RTT_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/types/tlocAny.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocGraphics/opengl/tlocTextureObject.h>

namespace tloc { namespace graphics {

  template <typename T_DepthPrecision = f32>
  class Rtt_T
    : core_bclass::NonCopyable_I
  {
  public:
    typedef T_DepthPrecision                        depth_precision;
    typedef Rtt_T<depth_precision>                  this_type;

    typedef gfx_rend::Renderer_T<depth_precision>   renderer_type;
    typedef typename renderer_type::this_type_sptr  renderer_ptr;
    typedef gfx_gl::framebuffer_object_sptr         fbo_ptr;

    typedef core_t::Any                             buffer_type;
    typedef core_conts::Array<buffer_type>          color_buffers;
    typedef gfx_t::Dimension2                       dim_type;

    typedef gfx_gl::p_texture_object::Params        to_params;
    typedef gfx_gl::TextureObject                   to_type;
    typedef gfx_gl::texture_object_sptr             to_ptr;
    typedef gfx_gl::TextureObjectShadow             to_shadow_type;
    typedef gfx_gl::texture_object_shadow_sptr      to_shadow_ptr;

  public:
    Rtt_T(dim_type a_dim, 
          renderer_ptr a_renderer = nullptr);

    template <tl_int T_AttachmentIndex, typename T_ColorType>
    to_ptr  AddColorAttachment(const to_params& a_toParams = to_params());
    to_ptr  AddColorAttachment(tl_int a_attachmentIndex, 
                               const to_params& a_toParams = to_params());

    template <tl_int T_AttachmentIndex>
    to_ptr  AddColorAttachment(to_ptr a_textureObject);
    to_ptr  AddColorAttachment(tl_int a_attachmentIndex, to_ptr a_textureObject);

    template <typename T_Target, typename T_ColorType>
    core_sptr::SharedPtr<gfx_gl::TextureObject_T<T_Target>>
      AddDepthAttachment(const to_params& a_toParams = 
                         gfx_gl::p_texture_object::GetDepthParams());

    to_ptr         AddDepthAttachment();
    to_shadow_ptr  AddShadowDepthAttachment();

    TLOC_DECL_AND_DEF_GETTER(fbo_ptr, GetFBO, m_fbo);
    TLOC_DECL_AND_DEF_GETTER(renderer_ptr, GetRenderer, m_renderer);

  private:
    dim_type        m_dim;

    fbo_ptr         m_fbo;
    renderer_ptr    m_renderer;

    buffer_type     m_depthBuffer;
    color_buffers   m_colorBuffers;

  public:
    TLOC_DECL_AND_DEF_GETTER_AUTO(GetDepthBuffer, m_depthBuffer);
    TLOC_DECL_AND_DEF_CONTAINER_ALL_METHODS(_color_buffers, m_colorBuffers);
  };

  template <typename T_DepthPrecision>
  template <tl_int T_AttachmentIndex, typename T_ColorType>
  auto
    Rtt_T<T_DepthPrecision>::
    AddColorAttachment(const to_params& a_toParams) -> to_ptr
  {
    auto rttTo = core_sptr::MakeShared<to_type>(a_toParams);
    {
      using namespace gfx_med;

      typedef Image_T<p_image::dim_2d, T_ColorType>     image_type;

      image_type rttImg;
      rttImg.Create(m_dim, typename image_type::color_type::COLOR_BLACK);
      rttTo->Initialize(rttImg);
    }

    return AddColorAttachment<T_AttachmentIndex>(rttTo);
  }

  template <typename T_DepthPrecision>
  template <tl_int T_AttachmentIndex>
  auto
    Rtt_T<T_DepthPrecision>::
    AddColorAttachment(to_ptr a_to) -> to_ptr
  {
    using namespace gfx_gl::p_framebuffer_object;
    m_fbo->Attach<target::DrawFramebuffer, 
                  attachment::ColorAttachment<T_AttachmentIndex>>(*a_to);
    m_colorBuffers.push_back(a_to);

    return a_to;
  }

  template <typename T_DepthPrecision>
  template <typename T_Target, typename T_ColorType>
  core_sptr::SharedPtr<gfx_gl::TextureObject_T<T_Target>>
    Rtt_T<T_DepthPrecision>::
    AddDepthAttachment(const to_params& a_toParams)
  {
    typedef gfx_gl::TextureObject_T<T_Target>       l_to_type;

    auto rttTo = core_sptr::MakeShared<l_to_type>(a_toParams);
    {
      using namespace gfx_med;

      typedef Image_T<p_image::dim_2d, T_ColorType>     image_type;

      image_type rttImg;
      rttImg.Create(m_dim, typename image_type::color_type::COLOR_BLACK);
      rttTo->Initialize(rttImg);
    }

    using namespace gfx_gl::p_framebuffer_object;
    m_fbo->Attach<target::DrawFramebuffer, attachment::Depth>(*rttTo);
    m_depthBuffer = rttTo;

    return rttTo;
  }

  // -----------------------------------------------------------------------
  // typedefs

  typedef Rtt_T<>                                         Rtt;
  typedef Rtt_T<f32>                                      Rtt_depth32;
  typedef Rtt_T<f64>                                      Rtt_depth64;

  TLOC_TYPEDEF_ALL_SMART_PTRS(Rtt, rtt);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Rtt_depth32, rtt_depth32);
  TLOC_TYPEDEF_ALL_SMART_PTRS(Rtt_depth64, rtt_depth64);

  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(Rtt, rtt);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(Rtt_depth32, rtt_depth32);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(Rtt_depth64, rtt_depth64);

};};;

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::graphics::Rtt);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::graphics::Rtt_depth32);
TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::graphics::Rtt_depth64);

TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::graphics::Rtt);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::graphics::Rtt_depth32);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::graphics::Rtt_depth64);

#endif