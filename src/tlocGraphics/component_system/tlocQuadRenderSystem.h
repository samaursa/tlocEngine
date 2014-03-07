#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_RENDER_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_RENDER_SYSTEM_H_

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

  class QuadRenderSystem
    : public gfx_cs::RenderSystem_TI<renderer::renderer_sptr>
  {
  public:
    typedef gfx_cs::RenderSystem_TI<renderer::renderer_sptr>  base_type;

    typedef math::types::Vec3f32                              vec3_type;
    typedef math::types::Vec2f32                              vec2_type;
    typedef math::types::Mat4f32                              matrix_type;

    typedef core::containers::tl_array<vec3_type>::type       vec3_cont_type;
    typedef core_sptr::SharedPtr<vec3_cont_type>              vec3_cont_ptr;

    typedef core::containers::tl_array<vec2_type>::type       vec2_cont_type;
    typedef core_sptr::SharedPtr<vec2_cont_type>              vec2_cont_ptr;

    typedef gl::shader_program_sptr                           shader_prog_ptr;

    typedef core_conts::ArrayFixed<gl::attribute_sptr, 4>     attributes_cont;

  public:
    QuadRenderSystem(event_manager_ptr a_eventMgr,
                     entity_manager_ptr a_entityMgr);

    virtual error_type InitializeEntity(entity_ptr a_ent);
    virtual error_type ShutdownEntity(entity_ptr a_ent);

    virtual void ProcessEntity(entity_ptr a_ent, f64 a_deltaT);
    virtual void Post_ProcessActiveEntities(f64 a_deltaT);

    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&) {}

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}

    using base_type::GetCamera;
    using base_type::GetViewProjectionMatrix;

  private:
    shader_prog_ptr     m_shaderPtr;

    gl::shader_operator_sptr m_mvpOperator;
    gl::uniform_sptr         m_uniVpMat;

    // Cache
    vec3_cont_ptr       m_quadList;
    gl::attribute_sptr  m_vData;
    attributes_cont     m_tData;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(QuadRenderSystem, quad_render_system);

};};};

#endif