#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_DYNAMIC_TEXT_RENDER_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_DYNAMIC_TEXT_RENDER_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>

#include <tlocGraphics/media/tlocFont.h>
#include <tlocGraphics/component_system/tlocDynamicText.h>
#include <tlocGraphics/component_system/tlocTextRenderSystem_TI.h>

namespace tloc { namespace graphics { namespace component_system {

  class DynamicTextRenderSystem
    : public gfx_cs::TextRenderSystem_TI<gfx_cs::DynamicText>
  {
  public:
    typedef gfx_cs::DynamicText                               text_type;
    typedef gfx_cs::TextRenderSystem_TI<text_type>            base_type;

    typedef base_type::text_quads_pair                        text_quads_pair;
    typedef base_type::text_quads_cont                        text_quads_cont;

    typedef gfx_med::font_sptr                                font_ptr;
    typedef core_str::String                                  string_type;
    typedef math_t::Mat2f32                                   scale_type;
    typedef tl_float                                          real_type;

  public:
    DynamicTextRenderSystem(event_manager_ptr a_eventMgr,
                     entity_manager_ptr a_entityMgr,
                     const font_ptr& a_initializedFont);
    
    ~DynamicTextRenderSystem();

    virtual void ProcessEntity(entity_ptr a_ent, f64 a_deltaT);
    virtual void Post_ProcessActiveEntities(f64 a_deltaT);

    virtual error_type ShutdownEntity(entity_ptr a_ent);

    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&);
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&);

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&);
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&);

    using base_type::MarkForReinit;

  private:
    using base_type::m_fontEntityMgr;
    using base_type::m_fontCompMgr;
    using base_type::m_allText;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(DynamicTextRenderSystem, dyn_text_render_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(DynamicTextRenderSystem, dyn_text_render_system);

};};};

#endif