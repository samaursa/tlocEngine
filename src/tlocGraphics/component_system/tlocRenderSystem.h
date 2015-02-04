#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_TI_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_RENDER_SYSTEM_TI_H_

#include <tlocCore/data_structures/tlocVariadic.h>
#include <tlocCore/utilities/tlocCheckpoints.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>

#include <tlocMath/types/tlocMatrix4.h>

#include <tlocGraphics/component_system/tlocRenderSystem_I.h>
#include <tlocGraphics/opengl/tlocShaderProgram.h>
#include <tlocGraphics/tlocGraphicsBase.h>
#include <tlocGraphics/renderer/tlocRenderer.h>
#include <tlocGraphics/opengl/tlocShaderOperator.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace p_render_system {

    struct Attribute    {};
    struct AttributeVBO {};

  };

  template <typename T_RendererSptr>
  class RenderSystem_TI
    : public core_cs::EntityProcessingSystem
    , public RenderSystem_I
  {
  public:
    TLOC_STATIC_ASSERT(
      (Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_sptr>::value ||
       Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_depth32_sptr>::value ||
       Loki::IsSameType<T_RendererSptr, gfx_rend::renderer_depth64_sptr>::value),
       Unsupported_renderer_Renderer_must_be_a_shared_ptr);

  public:
    typedef core_cs::EntityProcessingSystem               base_type;
    typedef RenderSystem_I                                other_base_type;
    typedef T_RendererSptr                                renderer_type;
    typedef RenderSystem_TI<renderer_type>                this_type;

    typedef typename
      renderer_type::value_type::render_one_frame_uptr    rof_uptr;
    typedef math::types::Mat4f32                          matrix_type;

    typedef gl::ShaderOperator                            so_type;
    typedef gl::uniform_vptr                              uniform_ptr;
    typedef gl::shader_operator_vptr                      shader_operator_ptr;
    typedef gl::const_shader_program_vptr                 const_shader_prog_ptr;

    typedef typename entity_count_cont::iterator            entity_count_itr;
    typedef core::Pair<entity_count_itr, entity_count_itr>  entity_count_itr_pair;
    typedef core_conts::Array<entity_count_itr_pair>        entity_count_itr_cont;

  public:

    void         SetCamera(const_entity_ptr a_cameraEntity);

    TLOC_DECL_AND_DEF_GETTER(const_entity_ptr, GetCamera, m_sharedCam);
    TLOC_DECL_AND_DEF_GETTER(renderer_type, GetRenderer, m_renderer);
    TLOC_DECL_AND_DEF_SETTER(renderer_type, SetRenderer, m_renderer);

  protected:
    RenderSystem_TI(event_manager_ptr              a_eventMgr,
                    entity_manager_ptr             a_entityMgr,
                    register_type                  a_registerTypes,
                    BufferArg                      a_debugName);

    virtual void              ForceSortEntitiesByMaterial();
    virtual void              ForceSortEntitiesFrontToBack();
    virtual void              ForceSortEntitiesBackToFront();

    virtual void              SortEntities();

    virtual error_type        Pre_Initialize();
    virtual error_type        InitializeEntity(entity_ptr a_ent);

    virtual error_type        Post_ReInitialize();

    virtual void              Pre_ProcessActiveEntities(f64);

  protected:
    const_entity_ptr          m_sharedCam;
    renderer_type             m_renderer;
    matrix_type               m_vpMatrix;
    matrix_type               m_projMat;
    matrix_type               m_viewMatrix;
    entity_count_itr_cont     m_entPairsSegmentByMat;
  };

  // -----------------------------------------------------------------------
  // extern template

  TLOC_EXTERN_TEMPLATE_CLASS(RenderSystem_TI<gfx_rend::renderer_depth32_sptr>);
  TLOC_EXTERN_TEMPLATE_CLASS(RenderSystem_TI<gfx_rend::renderer_depth64_sptr>);

};};};

#endif