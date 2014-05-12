#include "tlocQuad.h"

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocPrefab/graphics/tlocTextureCoords.h>
#include <tlocPrefab/math/tlocTransform.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

  using gfx_cs::quad_sptr;
  using core_sptr::MakeShared;

  using gfx_cs::texture_coords_sptr;

  using math_t::Rectangle_T;

  Quad::entity_ptr
    Quad::
    Create()
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  void
    Quad::
    Add(entity_ptr a_ent)
  {
    using namespace gfx_cs::components;
    using namespace math_cs::components;

    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // quad component

    typedef ComponentPoolManager      pool_mgr;

    // Create the quad (and the quad pool if necessary)
    typedef gfx_cs::quad_pool         quad_pool;

    gfx_cs::quad_pool_vptr quadPool
      = m_compPoolMgr->GetOrCreatePool<gfx_cs::Quad>();

    quad_pool::iterator itrQuad = quadPool->GetNext();
    (*itrQuad)->SetValue(MakeShared<gfx_cs::Quad>(m_rect) );

    m_entMgr->InsertComponent(a_ent, *(*itrQuad)->GetValuePtr());

    // Create the texture coords (and the texture coord pool if necessary)
    if (m_texCoords)
    {
      pref_gfx::TextureCoords(m_entMgr, m_compPoolMgr)
      .AddCoord(math_t::Vec2f32(1.0f, 1.0f))
      .AddCoord(math_t::Vec2f32(0.0f, 1.0f))
      .AddCoord(math_t::Vec2f32(1.0f, 0.0f))
      .AddCoord(math_t::Vec2f32(0.0f, 0.0f))
      .Add(a_ent);
    }
  }

};};};