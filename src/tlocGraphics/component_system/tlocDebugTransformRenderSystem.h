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

    typedef vec3_type::value_type                             real_type;

    typedef core::containers::tl_array<vec3_type>::type       vec3_cont_type;
    typedef core_sptr::VirtualStackObjectBase_TI<vec3_cont_type>  vec3_cont_vso;

    typedef core::containers::tl_array<vec4_type>::type       vec4_cont_type;
    typedef core_sptr::VirtualStackObjectBase_TI<vec4_cont_type>  vec4_cont_vso;

    typedef gl::const_shader_program_vptr                     const_shader_prog_ptr;

    typedef gl::uniform_vptr                                  uniform_ptr;
    typedef gl::attribute_vptr                                attribute_ptr;

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
    uniform_ptr                     m_uniVpMat;
    attribute_ptr                   m_vData;
    attribute_ptr                   m_colData;
    
    // Cache
    vec3_cont_vso                   m_lineList;
    vec4_cont_vso                   m_lineCol;

    core_cs::entity_vptr            m_linesMaterial;
    const_shader_prog_ptr           m_shaderPtr;

    real_type                       m_scale;
  };

};};};

#endif