#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_STATIC_TEXT_RENDER_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_STATIC_TEXT_RENDER_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/memory/tlocBufferArg.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/io/tlocPath.h>

#include <tlocGraphics/media/tlocFont.h>
#include <tlocGraphics/component_system/tlocQuadRenderSystem.h>
#include <tlocGraphics/component_system/tlocSceneGraphSystem.h>
#include <tlocGraphics/component_system/tlocMaterialSystem.h>

namespace tloc { namespace graphics { namespace component_system {

  class StaticTextRenderSystem
    : public gfx_cs::RenderSystem_TI<renderer::renderer_sptr>
  {
  public:
    typedef gfx_cs::RenderSystem_TI<renderer::renderer_sptr>  base_type;

    typedef gfx_med::Font                                     font_type;
    typedef gfx_med::font_vso                                 font_vso;
    typedef core_str::String                                  string_type;
    typedef math_t::Mat2f32                                   scale_type;

  public:
    StaticTextRenderSystem(event_manager_ptr a_eventMgr,
                           entity_manager_ptr a_entityMgr,
                           font_vso a_initializedFont, 
                           scale_type a_globalScale = scale_type::IDENTITY);
    
    ~StaticTextRenderSystem();

    void               SetShaders(core_io::Path a_vertexShader, 
                                  core_io::Path a_fragmentShader);

    virtual error_type InitializeEntity(entity_ptr a_ent);
    virtual error_type Post_Initialize();
    virtual error_type ShutdownEntity(entity_ptr a_ent);

    virtual void Pre_ProcessActiveEntities(f64 a_deltaT);
    virtual void ProcessEntity(entity_ptr a_ent, f64 a_deltaT);
    virtual void Post_ProcessActiveEntities(f64 a_deltaT);

    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&);
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&);

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&);
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&);

  private:
    font_vso                            m_font;
    scale_type                          m_globalScale;

    core_io::Path                       m_vertexShader;
    core_io::Path                       m_fragmentShader;

    core_cs::component_pool_mgr_vso     m_fontCompMgr;
    core_cs::event_manager_vso          m_fontEventMgr;
    core_cs::entity_manager_vso         m_fontEntityMgr;
    gfx_cs::QuadRenderSystem            m_fontQuadRenderSys;
    gfx_cs::SceneGraphSystem            m_fontSceneGraphSys;
    gfx_cs::MaterialSystem              m_fontMaterialSys;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(StaticTextRenderSystem, static_text_render_system);

};};};

#endif