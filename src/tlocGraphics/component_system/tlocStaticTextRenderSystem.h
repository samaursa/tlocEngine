#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_STATIC_TEXT_RENDER_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_STATIC_TEXT_RENDER_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>

#include <tlocGraphics/media/tlocFont.h>
#include <tlocGraphics/component_system/tlocStaticText.h>
#include <tlocGraphics/component_system/tlocTextRenderSystem_TI.h>

namespace tloc { namespace graphics { namespace component_system {

  class StaticTextRenderSystem
    : public gfx_cs::TextRenderSystem_TI<gfx_cs::StaticText>
  {
  public:
    typedef gfx_cs::StaticText                                text_type;
    typedef gfx_cs::TextRenderSystem_TI<text_type>            base_type;

    typedef core_str::String                                  string_type;
    typedef math_t::Mat2f32                                   scale_type;
    typedef tl_float                                          real_type;

  public:
    typedef core::Pair<const_entity_ptr, 
                       core_cs::const_entity_ptr_array>       text_quads_pair;
    typedef core_conts::Array<text_quads_pair>                text_quads_cont;

  public:
    StaticTextRenderSystem(event_manager_ptr a_eventMgr,
                           entity_manager_ptr a_entityMgr);
    
    ~StaticTextRenderSystem();

    virtual void ProcessEntity(entity_ptr a_ent, f64 a_deltaT);

    virtual error_type ShutdownEntity(entity_ptr a_ent);

    virtual void OnComponentInsert(const core_cs::EntityComponentEvent&);
    virtual void OnComponentRemove(const core_cs::EntityComponentEvent&);

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&);
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&);
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(StaticTextRenderSystem, static_text_render_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(StaticTextRenderSystem, static_text_render_system);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::StaticTextRenderSystem);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::StaticTextRenderSystem);

#endif