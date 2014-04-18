#include "tlocTextRenderSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/containers/tlocArray.inl.h>

#include <tlocGraphics/component_system/tlocText.h>
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

  typedef TextRenderSystem::error_type    error_type;

  // ///////////////////////////////////////////////////////////////////////
  // TextRenderSystem

  TextRenderSystem::
    TextRenderSystem(event_manager_ptr a_eventMgr, 
                     entity_manager_ptr a_entityMgr,
                     const font_ptr& a_initializedFont)
    : base_type(a_eventMgr, a_entityMgr, a_initializedFont)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TextRenderSystem::
    ~TextRenderSystem()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TextRenderSystem::
    ProcessEntity(entity_ptr a_ent, f64 )
  { 
    text_sptr dynamicText = a_ent->GetComponent<Text>();

    if (dynamicText->IsUpdateRequired())
    {
      if (dynamicText->IsTextUpdated())
      {
        using gfx_cs::SceneNode;
        gfx_cs::scene_node_sptr sn = a_ent->GetComponent<SceneNode>();

        for (SceneNode::node_cont_iterator itr = sn->begin(), itrEnd = sn->end();
             itr != itrEnd; ++itr)
        {
          m_fontEntityMgr->DestroyEntity( (*itr)->GetEntity() );
        }

        while (sn->size() > 0)
        { sn->RemoveChild(*sn->begin()); }

        m_fontEntityMgr->Update();

        // remove the cached entity
        text_quads_cont::iterator itr = 
          find_if_all(m_allText, 
          core::algos::compare::pair::MakeFirst(const_entity_ptr(a_ent)));

        if (itr != m_allText.end())
        { m_allText.erase(itr); }

        m_fontCompMgr->RecycleAllUnused();
        InitializeEntity(a_ent);
      }

      if (dynamicText->IsAlignmentUpdated())
      {
      text_quads_cont::const_iterator itr = core::find_if_all
        (m_allText, core::algos::compare::pair::MakeFirst(const_entity_ptr(a_ent)));

      TLOC_ASSERT(itr != m_allText.end(), 
                  "Text should be stored in m_allText container");

      DoAlignText(*itr);
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    TextRenderSystem::
    ShutdownEntity(entity_ptr a_ent)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TextRenderSystem::
    OnComponentInsert(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TextRenderSystem::
    OnComponentRemove(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TextRenderSystem::
    OnComponentDisable(const core_cs::EntityComponentEvent&)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TextRenderSystem::
    OnComponentEnable(const core_cs::EntityComponentEvent&)
  { }

};};};

using namespace tloc::gfx_cs;

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(TextRenderSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(TextRenderSystem);