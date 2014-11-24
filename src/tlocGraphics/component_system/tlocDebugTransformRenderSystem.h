#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_DEBUG_TRANSFORM_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_DEBUG_TRANSFORM_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocGraphics/component_system/tlocRenderSystem.h>
#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocSceneGraphSystem.h>
#include <tlocGraphics/component_system/tlocMaterialSystem.h>
#include <tlocGraphics/component_system/tlocTextureAnimatorSystem.h>

#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>

namespace tloc { namespace graphics { namespace component_system {

  class DebugTransformRenderSystem
    : public gfx_cs::RenderSystem_TI<renderer::renderer_sptr>
  {
  public:
    typedef gfx_cs::RenderSystem_TI<renderer::renderer_sptr>      base_type;

    typedef math::types::Vec3f32                              vec3_type;
    typedef math::types::Vec4f32                              vec4_type;
    typedef math::types::Mat4f32                              matrix_type;
    typedef gfx_t::Vert3fpc                                   vertex_type;
    typedef core_conts::Array<vertex_type>                    vertex_cont;

    typedef vec3_type::value_type                             real_type;

    typedef gl::const_shader_program_vptr                     const_shader_prog_ptr;
    typedef gl::uniform_vptr                                  uniform_ptr;
    typedef gl::vao_vso                                       vao_vso;

  public:
    DebugTransformRenderSystem(event_manager_ptr  a_eventMgr,
                               entity_manager_ptr a_entityMgr);

    ~DebugTransformRenderSystem();

    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(entity_ptr a_ent);
    virtual error_type Post_Initialize();

    virtual error_type ShutdownEntity(entity_ptr a_ent);

    virtual void ProcessEntity(entity_ptr a_ent, f64 a_deltaT);
    virtual void Post_ProcessActiveEntities(f64 a_deltaT);

    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&);
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&);

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&);
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&);

    TLOC_DECL_AND_DEF_GETTER(real_type, GetScale, m_scale);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(real_type, SetScale, m_scale);

  private:
    core_cs::component_pool_mgr_vso m_linesPoolMgr;
    core_cs::event_manager_vso      m_linesEventMgr;
    core_cs::entity_manager_vso     m_linesEntMgr;
    gfx_cs::material_system_vso     m_linesMaterialSys;

    gl::shader_operator_vso         m_linesOperator;
    vao_vso                         m_vao;
    uniform_ptr                     m_uniVpMat;
    
    core_cs::entity_vptr            m_linesMaterial;
    const_shader_prog_ptr           m_shaderPtr;
    vertex_cont                     m_lineList;

    real_type                       m_scale;
  };

  // -----------------------------------------------------------------------
  // typedefs 

  TLOC_TYPEDEF_ALL_SMART_PTRS(DebugTransformRenderSystem, debug_transform_render_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(DebugTransformRenderSystem, debug_transform_render_system);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::DebugTransformRenderSystem);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::DebugTransformRenderSystem);

#endif