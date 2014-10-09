#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_ELLIPSE_RENDER_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_ELLIPSE_RENDER_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>

#include <tlocGraphics/component_system/tlocRenderSystem.h>

#include <tlocMath/types/tlocVector3.h>

namespace tloc { namespace graphics { namespace component_system {

  class FanRenderSystem
    : public gfx_cs::RenderSystem_TI<renderer::renderer_sptr>
  {
  public:
    typedef gfx_cs::RenderSystem_TI<renderer::renderer_sptr>  base_type;

    typedef math::types::Vec3f32                              vec3_type;
    typedef math::types::Vec2f32                              vec2_type;

    typedef core::containers::tl_array<vec3_type>::type       vec3_cont_type;

  public:
    FanRenderSystem(event_manager_ptr a_eventMgr,
                    entity_manager_ptr a_entityMgr);

    virtual error_type InitializeEntity(entity_ptr a_ent);
    virtual error_type ShutdownEntity(entity_ptr a_ent);

    virtual void ProcessEntity(entity_ptr a_ent, f64 a_deltaT);

    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&) {}

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(FanRenderSystem, fan_render_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(FanRenderSystem, fan_render_system);

};};};

#endif