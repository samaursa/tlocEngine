#include "tlocDynamicText.h"

#include <tlocGraphics/component_system/tlocDynamicText.h>
#include <tlocPrefab/graphics/tlocSceneNode.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;
  using core_sptr::MakeShared;

  // ///////////////////////////////////////////////////////////////////////
  // Text

  DynamicText::
    DynamicText(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : base_type(a_entMgr, a_poolMgr)
    , m_alignment(gfx_cs::alignment::k_align_left)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  DynamicText::component_ptr
    DynamicText::
    Construct(BufferArgW a_text, font_ptr a_font) const
  {
    using namespace gfx_cs::components;

    typedef ComponentPoolManager                    pool_mgr;
    typedef gfx_cs::dynamic_text_pool               st_pool;

    gfx_cs::dynamic_text_pool_vptr stPool
      = m_compPoolMgr->GetOrCreatePool<gfx_cs::DynamicText>();

    st_pool::iterator itrSt = stPool->GetNext();
    (*itrSt)->SetValue(MakeShared<gfx_cs::DynamicText>(a_text, a_font, m_alignment));

    return *(*itrSt)->GetValuePtr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  DynamicText::entity_ptr
    DynamicText::
    Create(BufferArgW a_text, font_ptr a_font) const
  { 
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_text, a_font);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    DynamicText::
    Add(entity_ptr a_ent, BufferArgW a_text, font_ptr a_font) const
  {
    // -----------------------------------------------------------------------
    // SceneNode component

    if (a_ent->HasComponent<gfx_cs::SceneNode>() == false)
    { SceneNode(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // DynamicText component

    m_entMgr->InsertComponent(a_ent, Construct(a_text, a_font));
  }

};};};