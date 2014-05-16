#include "tlocTextureCoords.h"

#include <tlocGraphics/component_system/tlocTextureCoords.h>

namespace tloc { namespace prefab { namespace graphics {

  // ///////////////////////////////////////////////////////////////////////
  // Coords

  TextureCoords::Coords::
    Coords()
    : m_setIndex(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TextureCoords::Coords::
    Coords(vec_type a_tcoord, size_type a_setIndex)
    : m_tcoord(a_tcoord)
    , m_setIndex(a_setIndex)
  { }

  // ///////////////////////////////////////////////////////////////////////
  // TextureCoords

  TextureCoords::
    TextureCoords(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr)
    : Prefab_I(a_entMgr, a_poolMgr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TextureCoords::entity_ptr
    TextureCoords::
    Create()
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TextureCoords::
    Add(entity_ptr a_ent)
  {
    using namespace gfx_cs::components;
    using gfx_cs::TextureCoords;

    typedef gfx_cs::texture_coords_pool       tcoord_pool;

    gfx_cs::texture_coords_pool_vptr tCoordPool
      = m_compPoolMgr->GetOrCreatePool<gfx_cs::TextureCoords>();

    tcoord_pool::iterator itrTCoord = tCoordPool->GetNext();
    TextureCoords tc;

    for (coords_cont::iterator itr = m_coords.begin(), itrEnd = m_coords.end();
         itr != itrEnd; ++itr)
    { tc.AddCoord(itr->m_tcoord, TextureCoords::set_index(itr->m_setIndex)); }

    (*itrTCoord)->SetValue(core_sptr::MakeShared<TextureCoords>(tc));

    m_entMgr->InsertComponent(a_ent, *(*itrTCoord)->GetValuePtr(), 
                              core_cs::EntityManager::orphan(true));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TextureCoords&
    TextureCoords::
    AddCoord(vec_type a_coord, set_index a_setIndex)
  {
    m_coords.push_back(Coords(a_coord, a_setIndex));
    return *this;
  }

};};};