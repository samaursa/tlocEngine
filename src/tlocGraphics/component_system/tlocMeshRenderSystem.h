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
#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocGraphics/component_system/tlocRenderSystem.h>

#include <tlocMath/types/tlocMatrix4.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace p_mesh_render_sytem
  {
    struct Instanced    {};
    struct NonInstanced {};
  };

  template <typename T_RendererSptr = gfx_rend::renderer_sptr, 
            typename T_MeshCompType = Mesh, 
            typename T_RenderingTechnique = p_mesh_render_sytem::NonInstanced>
  class MeshRenderSystem_T
    : public gfx_cs::RenderSystem_TI<T_RendererSptr>
  {
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_sptr>::value ||
       Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_depth32_sptr>::value ||
       Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_depth64_sptr>::value),
       Unsupported_renderer_Renderer_must_be_a_shared_ptr);


    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_MeshCompType, Mesh>::value ||
       Loki::IsSameType<T_MeshCompType, MeshStatic>::value ||
       Loki::IsSameType<T_MeshCompType, Mesh2D>::value ||
       Loki::IsSameType<T_MeshCompType, Mesh2DStatic>::value), 
       Unsupported_mesh_component_type);

    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_RenderingTechnique, p_mesh_render_sytem::Instanced>::value ||
       Loki::IsSameType<T_RenderingTechnique, p_mesh_render_sytem::NonInstanced>::value),
       Select_either_istanced_or_non_instanced);

  public:
    typedef T_RendererSptr                                renderer_type;
    typedef T_MeshCompType                                mesh_comp_type;
    typedef T_RenderingTechnique                          rendering_technique;

    typedef typename mesh_comp_type::mesh_type            mesh_type;
    typedef typename mesh_comp_type::static_dynamic_type  static_dynamic_type;

    typedef MeshRenderSystem_T<renderer_type, 
                               mesh_comp_type, 
                               rendering_technique>       this_type;
    typedef gfx_cs::RenderSystem_TI<renderer_type>        base_type;

    typedef typename base_type::error_type                error_type;
    typedef typename base_type::event_manager_ptr         event_manager_ptr;
    typedef typename base_type::entity_manager_ptr        entity_manager_ptr;
    typedef typename base_type::entity_ptr                entity_ptr;
    typedef typename base_type::register_type             register_type;

    typedef math::types::Mat4f32                          matrix_type;
    typedef gl::ShaderOperator                            so_type;
    typedef gl::const_shader_program_vptr                 const_shader_prog_ptr;

  public:
    MeshRenderSystem_T(event_manager_ptr a_eventMgr,
                       entity_manager_ptr a_entityMgr);

    error_type Pre_Initialize() override;
    error_type InitializeEntity(entity_ptr a_ent) override;
    error_type Post_Initialize() override;

    error_type ShutdownEntity(entity_ptr a_ent) override;

    void Pre_ProcessActiveEntities(f64) override;
    void ProcessEntity(entity_ptr a_ent, f64 a_deltaT) override;
    void Post_ProcessActiveEntities(f64) override;

    void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    void OnComponentEnable(const core_cs::EntityComponentEvent&) {}

  private:
    //void  DoInitializeTexCoords(entity_ptr a_ent, so_type& a_so) const;
    //void  DoUpdateTexCoords(entity_ptr a_ent, so_type& a_so) const;

  private:
    const_shader_prog_ptr     m_shaderPtr;

  private:
    void         DoInitializeMesh(entity_ptr a_ent, p_mesh::Static,
                                  p_mesh_render_sytem::Instanced);
    void         DoInitializeMesh(entity_ptr a_ent, p_mesh::Static,
                                  p_mesh_render_sytem::NonInstanced);
    void         DoInitializeMesh(entity_ptr a_ent, p_mesh::Dynamic,
                                  p_mesh_render_sytem::Instanced);
    void         DoInitializeMesh(entity_ptr a_ent, p_mesh::Dynamic,
                                  p_mesh_render_sytem::NonInstanced);

    void         DoInitializeTexCoords(entity_ptr a_ent, p_mesh::Static,
                                       p_mesh_render_sytem::Instanced);
    void         DoInitializeTexCoords(entity_ptr a_ent, p_mesh::Static,
                                       p_mesh_render_sytem::NonInstanced);
    void         DoInitializeTexCoords(entity_ptr a_ent, p_mesh::Dynamic,
                                       p_mesh_render_sytem::Instanced);
    void         DoInitializeTexCoords(entity_ptr a_ent, p_mesh::Dynamic,
                                       p_mesh_render_sytem::NonInstanced);

    void         DoProcessMesh(entity_ptr a_ent, p_mesh::Static,
                               p_mesh_render_sytem::Instanced);
    void         DoProcessMesh(entity_ptr a_ent, p_mesh::Static,
                               p_mesh_render_sytem::NonInstanced);
    void         DoProcessMesh(entity_ptr a_ent, p_mesh::Dynamic,
                               p_mesh_render_sytem::Instanced);
    void         DoProcessMesh(entity_ptr a_ent, p_mesh::Dynamic,
                               p_mesh_render_sytem::NonInstanced);

    void         DoProcessTextureCoords(entity_ptr a_ent, p_mesh::Static,
                                        p_mesh_render_sytem::Instanced);
    void         DoProcessTextureCoords(entity_ptr a_ent, p_mesh::Static,
                                        p_mesh_render_sytem::NonInstanced);
    void         DoProcessTextureCoords(entity_ptr a_ent, p_mesh::Dynamic,
                                        p_mesh_render_sytem::Instanced);
    void         DoProcessTextureCoords(entity_ptr a_ent, p_mesh::Dynamic,
                                        p_mesh_render_sytem::NonInstanced);

  private:
    using base_type::m_renderer;
    using base_type::m_vpMatrix;
    using base_type::m_projMat;
    using base_type::m_viewMatrix;
  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef MeshRenderSystem_T<>              MeshRenderSystem;

  TLOC_TYPEDEF_ALL_SMART_PTRS(MeshRenderSystem, mesh_render_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(MeshRenderSystem, mesh_render_system);
  
};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::MeshRenderSystem);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::MeshRenderSystem);

#endif