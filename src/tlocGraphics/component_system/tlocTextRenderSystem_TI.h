#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXT_RENDER_SYSTEM_TI_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_TEXT_RENDER_SYSTEM_TI_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/io/tlocPath.h>

#include <tlocGraphics/component_system/tlocMaterial.h>
#include <tlocGraphics/component_system/tlocQuadRenderSystem.h>
#include <tlocGraphics/component_system/tlocSceneGraphSystem.h>
#include <tlocGraphics/component_system/tlocMaterialSystem.h>
#include <tlocGraphics/component_system/tlocTextureAnimatorSystem.h>

namespace tloc { namespace graphics { namespace component_system {

  template <typename T_TextOrStaticTextComponent>
  class TextRenderSystem_TI
    : public gfx_cs::RenderSystem_TI<renderer::renderer_sptr>
  {
  public:
    typedef gfx_cs::RenderSystem_TI<renderer::renderer_sptr>  base_type;
    typedef T_TextOrStaticTextComponent                       text_type;
    typedef core_sptr::SharedPtr<text_type>                   text_ptr;
    typedef TextRenderSystem_TI<text_type>                    this_type;

    typedef core_str::String                                  string_type;
    typedef math_t::Mat2f32                                   scale_type;
    typedef tl_float                                          real_type;

  public:
    typedef core::Pair<const_entity_ptr, 
                       core_cs::const_entity_ptr_array>       text_quads_pair;
    typedef core_conts::Array<text_quads_pair>                text_quads_cont;
    typedef text_quads_cont::iterator                         text_quads_iterator;

  public:

    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(entity_ptr a_ent);
    virtual error_type Post_Initialize();

    void               MarkForReinit(const entity_ptr a_ent);

    virtual void Pre_ProcessActiveEntities(f64 a_deltaT);
    virtual void Post_ProcessActiveEntities(f64 a_deltaT);

  protected:
    TextRenderSystem_TI(event_manager_ptr a_eventMgr,
                        entity_manager_ptr a_entityMgr);
    
    ~TextRenderSystem_TI();

    void         DoAlignText(const text_quads_pair& a_pair);

  private:
    error_type   DoReInitializeEntity(entity_ptr a_ent);
    void         DoRemoveText(const const_entity_ptr a_ent);

  protected:
    text_quads_cont                     m_allText;
    core_cs::entity_ptr_array           m_entsToReinit;

    core_cs::component_pool_mgr_vso     m_fontCompMgr;
    core_cs::event_manager_vso          m_fontEventMgr;
    core_cs::entity_manager_vso         m_fontEntityMgr;
    gfx_cs::SceneGraphSystem            m_fontSceneGraphSys;
    gfx_cs::QuadRenderSystem            m_fontQuadRenderSys;
    gfx_cs::TextureAnimatorSystem       m_fontAnimSys;
  };

};};};

#endif