#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_ELLIPSE_RENDER_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_ELLIPSE_RENDER_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>
#include <tlocGraphics/component_system/tlocRenderSystem.h>

#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix4.h>
#include <tlocMath/projection/tlocFrustum.h>
#include <tlocMath/component_system/tlocComponentType.h>

namespace tloc { namespace graphics { namespace component_system {

  class FanRenderSystem
    : public gfx_cs::RenderSystem_TI<renderer::renderer_sptr>
  {
  public:
    typedef gfx_cs::RenderSystem_TI<renderer::renderer_sptr>  base_type;
    using base_type::component_type;
    using base_type::error_type;

    using base_type::event_manager;
    using base_type::entity_manager;
    using base_type::entity_type;
    using base_type::event_type;
    using base_type::event_value_type;

    typedef math::types::Vec3f32                              vec3_type;
    typedef math::types::Vec2f32                              vec2_type;

    typedef core::containers::tl_array<vec3_type>::type       vec3_cont_type;
    typedef core_sptr::SharedPtr<vec3_cont_type>              vec3_cont_ptr;

    typedef core::containers::tl_array<vec2_type>::type       vec2_cont_type;
    typedef core_sptr::SharedPtr<vec2_cont_type>              vec2_cont_ptr;

    typedef gl::shader_program_sptr                           shader_prog_ptr;

  public:
    FanRenderSystem(event_manager_sptr a_eventMgr,
                    entity_manager_sptr a_entityMgr);

    virtual error_type InitializeEntity(const entity_manager* a_mgr,
                                        const entity_type* a_ent);
    virtual error_type ShutdownEntity(const entity_manager* a_mgr,
                                      const entity_type* a_ent);

    virtual void ProcessEntity(const entity_manager* a_mgr,
                               const entity_type* a_ent,
                               f64 a_deltaT);
    virtual void Post_ProcessActiveEntities(f64 a_deltaT);

    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&) {}

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}

  private:
    shader_prog_ptr     m_shaderPtr;

    gl::shader_operator_sptr  m_mvpOperator;
    gl::uniform_sptr          m_uniVpMat;

    vec3_cont_ptr             m_vertList;
    gl::attribute_sptr        m_vData;
    gl::attribute_sptr        m_tData;
  };

  //------------------------------------------------------------------------
  // typedefs

  typedef core_sptr::SharedPtr<FanRenderSystem>  fan_render_system_sptr;

};};};

#endif