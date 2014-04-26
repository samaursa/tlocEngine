#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_H_

#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/data_structures/tlocVariadic.h>

#include <tlocMath/types/tlocMatrix4.h>

#include <tlocGraphics/tlocGraphicsBase.h>
#include <tlocGraphics/renderer/tlocRenderer.h>

namespace tloc { namespace graphics { namespace component_system {

  template <typename T_RendererSptr>
  class RenderSystem_TI
    : public core_cs::EntityProcessingSystem
  {
  public:
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_sptr>::value ||
       Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_depth32_sptr>::value ||
       Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_depth64_sptr>::value),
       Unsupported_renderer_Renderer_must_be_a_shared_ptr);

  public:
    typedef core_cs::EntityProcessingSystem               base_type;
    using base_type::component_type;
    using base_type::error_type;

    typedef T_RendererSptr                                renderer_type;
    typedef typename
      renderer_type::value_type::render_one_frame_uptr    rof_uptr;

    using base_type::event_manager;
    using base_type::entity_manager;
    using base_type::entity_type;
    using base_type::event_type;
    using base_type::entity_ptr;
    using base_type::event_value_type;

    typedef math::types::Mat4f32                              matrix_type;

  public:
    template <size_type T_VarSize>
    RenderSystem_TI(event_manager_ptr              a_eventMgr,
                    entity_manager_ptr             a_entityMgr,
                    const core_ds::Variadic
                      <component_type, T_VarSize>&  a_typeFlags);

    void         SetCamera(const_entity_ptr a_cameraEntity);

    virtual error_type InitializeEntity(entity_ptr a_ent);

    virtual void Pre_ProcessActiveEntities(f64);
    virtual void Post_ProcessActiveEntities(f64);

    TLOC_DECL_AND_DEF_GETTER(const_entity_ptr, GetCamera, m_sharedCam);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (matrix_type, GetViewProjectionMatrix, m_vpMatrix);
    TLOC_DECL_AND_DEF_GETTER(renderer_type, GetRenderer, m_renderer);
    TLOC_DECL_AND_DEF_SETTER(renderer_type, SetRenderer, m_renderer);

  private:
    const_entity_ptr      m_sharedCam;
    renderer_type         m_renderer;
    rof_uptr              m_renderOneFrame;
    matrix_type           m_vpMatrix;

  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_RendererSptr>
  template <tl_size T_VarSize>
  RenderSystem_TI<T_RendererSptr>::
    RenderSystem_TI(event_manager_ptr a_eventMgr,
                   entity_manager_ptr a_entityMgr,
                   const core_ds::Variadic
                    <component_type, T_VarSize>&  a_typeFlags)
    : base_type(a_eventMgr, a_entityMgr, a_typeFlags)
    , m_sharedCam(nullptr)
    , m_renderer(nullptr)
  { }

};};};

#endif