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

  StaticText::
    StaticText(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : base_type(a_entMgr, a_poolMgr)
    , m_alignment(gfx_cs::alignment::k_align_left)
    , m_horAlignment(gfx_cs::horizontal_alignment::k_none)
    , m_verticalKern(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  StaticText::component_ptr
    StaticText::
    Construct(BufferArgW a_text, font_ptr a_font) const
  {
    using namespace gfx_cs::components;

    typedef ComponentPoolManager                  pool_mgr;
    typedef gfx_cs::static_text_pool              st_pool;

    gfx_cs::static_text_pool_vptr stPool 
      = m_compPoolMgr->GetOrCreatePool<gfx_cs::StaticText>();

    st_pool::iterator itrSt = stPool->GetNext();

    gfx_cs::static_text_sptr text = 
      MakeShared<gfx_cs::StaticText>(a_text, a_font, m_alignment, m_horAlignment);
    text->SetVerticalKerning(m_verticalKern);

    (*itrSt)->SetValue(text);

    return *(*itrSt)->GetValuePtr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  StaticText::entity_ptr
    StaticText::
    Create(BufferArgW a_text, font_ptr a_font) const
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent, a_text, a_font);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    StaticText::
    Add(entity_ptr a_ent, BufferArgW a_text, font_ptr a_font) const
  {
    // -----------------------------------------------------------------------
    // SceneNode component

    if (a_ent->HasComponent<gfx_cs::SceneNode>() == false)
    { SceneNode(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // StaticText component

    m_entMgr->InsertComponent(insert_params(a_ent, Construct(a_text, a_font))
                              .DispatchTo(GetListeners()) );
  }

};};};