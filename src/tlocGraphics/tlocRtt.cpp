#include "tlocRtt.h"

#include <tlocCore/logging/tlocLogger.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace graphics {

  // ///////////////////////////////////////////////////////////////////////
  // Rtt_T

#define TLOC_RTT_TEMPS  typename T_DepthPrecision
#define TLOC_RTT_PARAMS T_DepthPrecision

  template <TLOC_RTT_TEMPS>
  Rtt_T<TLOC_RTT_PARAMS>::
    Rtt_T(dim_type a_dim, renderer_ptr a_renderer)
    : m_dim(a_dim)
  { 
    if (m_renderer == nullptr)
    {
      m_fbo = core_sptr::MakeShared<fbo_ptr::value_type>();

      auto_cref rParams = gfx_rend::p_renderer::GetParamsCommon(m_fbo, a_dim);
      m_renderer = core_sptr::MakeShared<renderer_type>(rParams);
    }
    else
    {
      auto rParams = m_renderer->GetParams();

      if (rParams.GetFBO() == nullptr)
      {
        TLOC_LOG_GFX_INFO_FILENAME_ONLY() 
          << "RTT Renderer does not have an FBO attached - creating FBO.";

        m_fbo = core_sptr::MakeShared<fbo_ptr::value_type>();
        rParams.SetFBO(m_fbo);
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RTT_TEMPS>
  auto
    Rtt_T<TLOC_RTT_PARAMS>::
    AddColorAttachment(tl_int a_attachmentIndex, 
                       const to_params& a_toParams) -> to_ptr
  { 
    switch(a_attachmentIndex)
    {
    case 0:   return AddColorAttachment<0, gfx_t::Color>(a_toParams);
    case 1:   return AddColorAttachment<1, gfx_t::Color>(a_toParams);
    case 2:   return AddColorAttachment<2, gfx_t::Color>(a_toParams);
    case 3:   return AddColorAttachment<3, gfx_t::Color>(a_toParams);
    case 4:   return AddColorAttachment<4, gfx_t::Color>(a_toParams);
    case 5:   return AddColorAttachment<5, gfx_t::Color>(a_toParams);
    case 6:   return AddColorAttachment<6, gfx_t::Color>(a_toParams);
    case 7:   return AddColorAttachment<7, gfx_t::Color>(a_toParams);
    case 8:   return AddColorAttachment<8, gfx_t::Color>(a_toParams);
    case 9:   return AddColorAttachment<9, gfx_t::Color>(a_toParams);
    case 10:  return AddColorAttachment<10, gfx_t::Color>(a_toParams);
    case 11:  return AddColorAttachment<11, gfx_t::Color>(a_toParams);
    case 12:  return AddColorAttachment<12, gfx_t::Color>(a_toParams);
    case 13:  return AddColorAttachment<13, gfx_t::Color>(a_toParams);
    case 14:  return AddColorAttachment<14, gfx_t::Color>(a_toParams);
    case 15:  return AddColorAttachment<15, gfx_t::Color>(a_toParams);
    default:  return AddColorAttachment<0, gfx_t::Color>(a_toParams);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RTT_TEMPS>
  auto
    Rtt_T<TLOC_RTT_PARAMS>::
    AddColorAttachment(tl_int a_attachmentIndex, to_ptr a_to) -> to_ptr
  { 
    switch(a_attachmentIndex)
    {
    case 0:   return AddColorAttachment<0>(a_to);
    case 1:   return AddColorAttachment<1>(a_to);
    case 2:   return AddColorAttachment<2>(a_to);
    case 3:   return AddColorAttachment<3>(a_to);
    case 4:   return AddColorAttachment<4>(a_to);
    case 5:   return AddColorAttachment<5>(a_to);
    case 6:   return AddColorAttachment<6>(a_to);
    case 7:   return AddColorAttachment<7>(a_to);
    case 8:   return AddColorAttachment<8>(a_to);
    case 9:   return AddColorAttachment<9>(a_to);
    case 10:  return AddColorAttachment<10>(a_to);
    case 11:  return AddColorAttachment<11>(a_to);
    case 12:  return AddColorAttachment<12>(a_to);
    case 13:  return AddColorAttachment<13>(a_to);
    case 14:  return AddColorAttachment<14>(a_to);
    case 15:  return AddColorAttachment<15>(a_to);
    default:  return AddColorAttachment<0>(a_to);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RTT_TEMPS>
  auto
    Rtt_T<TLOC_RTT_PARAMS>::
    AddDepthAttachment() -> to_ptr
  { return AddDepthAttachment<gfx_gl::p_texture_object::target::Tex2D, 
                              gfx_t::color_f32_r>(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_RTT_TEMPS>
  auto
    Rtt_T<TLOC_RTT_PARAMS>::
    AddShadowDepthAttachment() -> to_shadow_ptr
  { 
    return AddDepthAttachment<gfx_gl::p_texture_object::target::Tex2DShadow, 
                              gfx_t::color_f32_r>
      (gfx_gl::p_texture_object::GetShadowParams()); 
  }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class Rtt_T<f32>;
  template class Rtt_T<f64>;

};};

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
using namespace tloc::graphics;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Rtt);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Rtt_depth32);
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Rtt_depth64);

TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(Rtt);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(Rtt_depth32);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(Rtt_depth64);