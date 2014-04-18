#include "tlocDynamicText.h"

#include <tlocGraphics/component_system/tlocText.h>

#include <tlocPrefab/graphics/tlocSceneNode.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

  // ///////////////////////////////////////////////////////////////////////
  // Text

  DynamicText::entity_ptr
    DynamicText::
    Create(BufferArgW a_text)
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_text);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DynamicText::
    Add(entity_ptr a_ent, BufferArgW a_text)
  {
    using namespace gfx_cs::components;

    typedef ComponentPoolManager                  pool_mgr;

    if (a_ent->HasComponent<gfx_cs::SceneNode>() == false)
    { SceneNode(m_entMgr, m_compPoolMgr).Add(a_ent); }

    typedef gfx_cs::text_pool              st_pool;
    gfx_cs::text_pool_vptr                 stPool;

    if (m_compPoolMgr->Exists(gfx_cs::components::text) == false)
    { stPool = m_compPoolMgr->CreateNewPool<gfx_cs::Text>(); }
    else
    { stPool = m_compPoolMgr->GetPool<gfx_cs::Text>(); }

    st_pool::iterator itrSt = stPool->GetNext();
    (*itrSt)->SetValue(gfx_cs::Text(a_text, m_alignment));

    m_entMgr->InsertComponent(a_ent, (*itrSt)->GetValue());
  }

};};};