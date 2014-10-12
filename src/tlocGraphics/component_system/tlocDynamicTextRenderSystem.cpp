#include "tlocDynamicTextRenderSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/containers/tlocArray.inl.h>

#include <tlocGraphics/component_system/tlocDynamicText.h>
#include <tlocGraphics/component_system/tlocSceneNode.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocGraphics/component_system/tlocTextureAnimator.h>

#include <tlocCore/logging/tlocLogger.h>

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

  typedef DynamicTextRenderSystem::error_type    error_type;

  // ///////////////////////////////////////////////////////////////////////
  // TextRenderSystem

  DynamicTextRenderSystem::
    DynamicTextRenderSystem(event_manager_ptr a_eventMgr, 
                            entity_manager_ptr a_entityMgr)
    : base_type(a_eventMgr, a_entityMgr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  DynamicTextRenderSystem::
    ~DynamicTextRenderSystem()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DynamicTextRenderSystem::
    ProcessEntity(entity_ptr a_ent, f64 )
  { 
    dynamic_text_sptr dynamicText = a_ent->GetComponent<DynamicText>();

    if (dynamicText->IsUpdateRequired())
    {
      dynamicText->SetUpdateRequired(false);

      if (dynamicText->IsTextUpdated())
      {
        // -----------------------------------------------------------------------
        // destroy all the text quads under this node
        MarkForReinit(a_ent);
      }
      else if (dynamicText->IsAlignmentUpdated())
      {
        text_quads_cont::const_iterator itr = core::find_if_all
          (m_allText, core::algos::pair::compare::MakeFirst(const_entity_ptr(a_ent)));

        TLOC_ASSERT(itr != m_allText.end(), 
                    "Text should be stored in m_allText container");

        DoAlignText(*itr);
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DynamicTextRenderSystem::
    Post_ProcessActiveEntities(f64 a_deltaT)
  { 
    m_textEntityMgr->Update();
    m_textCompMgr->RecycleAllUnused();

    base_type::Post_ProcessActiveEntities(a_deltaT);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    DynamicTextRenderSystem::
    ShutdownEntity(entity_ptr a_ent)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DynamicTextRenderSystem::
    OnComponentInsert(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DynamicTextRenderSystem::
    OnComponentRemove(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DynamicTextRenderSystem::
    OnComponentDisable(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DynamicTextRenderSystem::
    OnComponentEnable(const core_cs::EntityComponentEvent&)
  { }

};};};

using namespace tloc::gfx_cs;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(DynamicTextRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(DynamicTextRenderSystem);