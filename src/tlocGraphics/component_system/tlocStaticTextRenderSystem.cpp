#include "tlocStaticTextRenderSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/containers/tlocArray.inl.h>

#include <tlocGraphics/component_system/tlocStaticText.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core_ds;

  namespace {

    const core_str::StringW
      g_symbols = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                  L"abcdefghijklmnopqrstuvwxyz" 
                  L"1234567890!@#$%^&*()_+-=[]" 
                  L"{}\\|;:'\",<.>/?`~";
  };

  //////////////////////////////////////////////////////////////////////////
  // typedefs

  typedef StaticTextRenderSystem::error_type    error_type;

  // ///////////////////////////////////////////////////////////////////////
  // StaticTextRenderSystem

  StaticTextRenderSystem::
    StaticTextRenderSystem(event_manager_ptr a_eventMgr, 
                           entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  StaticTextRenderSystem::
    ~StaticTextRenderSystem()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticTextRenderSystem::
    ProcessEntity(entity_ptr a_ent, f64 )
  { 
    static_text_sptr staticText = a_ent->GetComponent<StaticText>();

    if (staticText->IsUpdateRequired())
    {
      text_quads_cont::const_iterator itr = core::find_if_all
        (m_allText, core::algos::pair::compare::MakeFirst(const_entity_ptr(a_ent)));

      TLOC_ASSERT(itr != m_allText.end(), 
                  "StaticText should be stored in m_allText container");

      DoAlignText(*itr);
      staticText->SetUpdateRequired(false);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    StaticTextRenderSystem::
    ShutdownEntity(entity_ptr a_ent)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticTextRenderSystem::
    OnComponentInsert(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticTextRenderSystem::
    OnComponentRemove(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticTextRenderSystem::
    OnComponentDisable(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticTextRenderSystem::
    OnComponentEnable(const core_cs::EntityComponentEvent&)
  { }

};};};

using namespace tloc::gfx_cs;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(StaticTextRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(StaticTextRenderSystem);