#include "tlocStaticText.h"

#include <tlocGraphics/component_system/tlocStaticText.h>

#include <tlocPrefab/graphics/tlocSceneNode.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;
  using core_sptr::MakeShared;

  // ///////////////////////////////////////////////////////////////////////
  // StaticText

  StaticText::entity_ptr
    StaticText::
    Create(BufferArgW a_text, font_ptr a_font)
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_text, a_font);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticText::
    Add(entity_ptr a_ent, BufferArgW a_text, font_ptr a_font)
  {
    using namespace gfx_cs::components;

    typedef ComponentPoolManager                  pool_mgr;

    if (a_ent->HasComponent<gfx_cs::SceneNode>() == false)
    { SceneNode(m_entMgr, m_compPoolMgr).Add(a_ent); }

    typedef gfx_cs::static_text_pool              st_pool;
    gfx_cs::static_text_pool_vptr                 stPool;

    if (m_compPoolMgr->Exists(gfx_cs::components::static_text) == false)
    { stPool = m_compPoolMgr->CreateNewPool<gfx_cs::StaticText>(); }
    else
    { stPool = m_compPoolMgr->GetPool<gfx_cs::StaticText>(); }

    st_pool::iterator itrSt = stPool->GetNext();
    (*itrSt)->SetValue(MakeShared<gfx_cs::StaticText>(a_text, a_font, m_alignment));

    m_entMgr->InsertComponent(a_ent, *(*itrSt)->GetValuePtr());
  }

};};};