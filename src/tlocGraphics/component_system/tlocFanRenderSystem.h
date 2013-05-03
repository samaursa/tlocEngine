#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_ELLIPSE_RENDER_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_ELLIPSE_RENDER_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>

#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocMatrix4.h>
#include <tlocMath/projection/tlocFrustum.h>
#include <tlocMath/component_system/tlocComponentType.h>

namespace tloc { namespace graphics { namespace component_system {

  class FanRenderSystem
    : public core::component_system::EntityProcessingSystem
  {
  public:
    typedef core::component_system::EntityProcessingSystem  base_type;
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
    typedef core::containers::tl_array<vec2_type>::type       vec2_cont_type;
    typedef math::types::Mat4f32                              matrix_type;

    typedef gl::ShaderProgramPtr                              shader_prog_ptr;

  public:
    FanRenderSystem(event_manager_sptr a_eventMgr,
                    entity_manager_sptr a_entityMgr);

    void AttachCamera(const entity_type* a_cameraEntity);

    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(const entity_manager* a_mgr,
                                        const entity_type* a_ent);
    virtual error_type ShutdownEntity(const entity_manager* a_mgr,
                                      const entity_type* a_ent);

    virtual void Pre_ProcessActiveEntities();
    virtual void ProcessEntity(const entity_manager* a_mgr,
                               const entity_type* a_ent);
    virtual void Post_ProcessActiveEntities();

    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&) {}

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}

  private:
    shader_prog_ptr     m_shaderPtr;
    const entity_type*  m_sharedCam;
    matrix_type         m_vpMatrix;

    vec3_cont_type          m_vertList;
    vec2_cont_type          m_texList;
    gl::ShaderOperatorPtr   m_projectionOperator;
    gl::AttributePtr        m_vData;
    gl::AttributePtr        m_tData;
  };

};};};

#endif