#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_BOUNDING_BOX_RENDER_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_BOUNDING_BOX_RENDER_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocECS.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocECS.h>

#include <tlocGraphics/component_system/tlocRenderSystem.h>
#include <tlocGraphics/component_system/tlocMeshRenderSystem.h>

namespace tloc { namespace graphics { namespace component_system {

  template <typename T_RendererSptr = gfx_rend::renderer_sptr>
  class BoundingBoxRenderSystem_T
    : public RenderSystem_TI<T_RendererSptr>
  {
  public:
    typedef T_RendererSptr                                      renderer_type;
    typedef RenderSystem_TI<renderer_type>                      base_type;
    typedef BoundingBoxRenderSystem_T                           this_type;
    typedef core_sptr::VirtualPtr
      <MeshRenderSystem_T<renderer_type>>                       mesh_sys_ptr;

  public:
    BoundingBoxRenderSystem_T(event_manager_ptr, entity_manager_ptr);

    virtual error_type  Pre_Initialize() override;
    virtual error_type  InitializeEntity(entity_ptr) override;
    virtual error_type  Post_Initialize() override;

    void                SetCamera(const_entity_ptr a_cameraEntity);
    void                SetRenderer(renderer_type a_renderer);

    virtual void        Pre_ProcessActiveEntities(f64) override;
    virtual void        ProcessEntity(entity_ptr, f64 a_deltaT) override;

  private:
    core_cs::ECS                    m_scene;
    mesh_sys_ptr                    m_meshSys;
  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef BoundingBoxRenderSystem_T<>             BoundingBoxRenderSystem;

  TLOC_TYPEDEF_ALL_SMART_PTRS(BoundingBoxRenderSystem, bounding_box_render_sys);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(BoundingBoxRenderSystem, bounding_box_render_sys);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::BoundingBoxRenderSystem);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::BoundingBoxRenderSystem);

#endif