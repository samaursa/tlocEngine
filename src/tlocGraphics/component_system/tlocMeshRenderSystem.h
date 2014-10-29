#pragma once
#ifndef TLOC_MESH_RENDER_SYSTEM_H
#define TLOC_MESH_RENDER_SYSTEM_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>
#include <tlocGraphics/component_system/tlocMesh.h>
#include <tlocGraphics/component_system/tlocRenderSystem.h>

#include <tlocMath/types/tlocMatrix4.h>

namespace tloc { namespace graphics { namespace component_system {

  template <typename Mesh_T>
  class MeshRenderSystem_T
    : public gfx_cs::RenderSystem_TI<renderer::renderer_sptr>
  {
  public:
    typedef gfx_cs::RenderSystem_TI<renderer::renderer_sptr>  base_type;

    typedef gl::const_shader_program_vptr                 const_shader_prog_ptr;

    typedef Mesh_T                                        mesh_type;
    typedef core_sptr::SharedPtr<mesh_type>               mesh_ptr;
    typedef typename Mesh_T::vertex_storage_policy        vertex_storage_policy;

    typedef math::types::Vec3f32                          vec3_type;

  public:
    MeshRenderSystem_T(event_manager_ptr a_eventMgr,
                       entity_manager_ptr a_entityMgr);

    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(entity_ptr a_ent);
    virtual error_type ShutdownEntity(entity_ptr a_ent);

    virtual void ProcessEntity(entity_ptr a_ent, f64 a_deltaT);

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}

    using base_type::GetCamera;
    using base_type::GetViewProjectionMatrix;

  private:
    gl::shader_operator_vso   so_mesh;
  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef MeshRenderSystem_T<Mesh>      MeshRenderSystem;

  TLOC_TYPEDEF_ALL_SMART_PTRS(MeshRenderSystem, mesh_render_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(MeshRenderSystem, mesh_render_system);

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(MeshRenderSystem);
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(MeshRenderSystem);

};};};

#endif