#pragma once
#ifndef TLOC_MESH_RENDER_SYSTEM_H
#define TLOC_MESH_RENDER_SYSTEM_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>
#include <tlocGraphics/component_system/tlocMesh.h>

#include <tlocMath/types/tlocMatrix4.h>

namespace tloc { namespace graphics { namespace component_system {

  template <typename Mesh_T>
  class MeshRenderSystem : public core::component_system::EntityProcessingSystem
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

    typedef gl::shader_program_sptr                       shader_prog_ptr;

    typedef Mesh_T                                        mesh_type;
    typedef typename Mesh_T::vertex_storage_policy        vertex_storage_policy;

    typedef math::types::Vec3f32                          vec3_type;
    typedef math::types::Mat4f32                          matrix_type;

  public:
    MeshRenderSystem(event_manager_sptr a_eventMgr,
                     entity_manager_sptr a_entityMgr);

    void AttachCamera(const entity_type* a_cameraEntity);

    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(const entity_manager* a_mgr,
                                        const entity_type* a_ent);
    virtual error_type ShutdownEntity(const entity_manager* a_mgr,
                                      const entity_type* a_ent);

    virtual void Pre_ProcessActiveEntities(f64 a_deltaT);
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
    const entity_type*  m_sharedCam;
    matrix_type         m_vpMatrix;

    gl::shader_operator_sptr m_mvpOperator;
    gl::uniform_sptr         m_uniVpMat;
  };

};};};

#endif