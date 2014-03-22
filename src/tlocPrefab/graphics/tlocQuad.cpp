#include "tlocQuad.h"

#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocQuad.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;

  using gfx_cs::quad_sptr;

  using gfx_cs::TextureCoords;
  using gfx_cs::texture_coords_sptr;

  using math_t::Rectangle_T;
  using math_cs::Transform;
  using math_cs::transform_sptr;

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

    typedef ComponentPoolManager      pool_mgr;

    // Create the quad (and the quad pool if necessary)
    typedef gfx_cs::quad_pool         quad_pool;
    gfx_cs::quad_pool_vptr            quadPool;

    if (m_compPoolMgr->Exists(quad) == false)
    { quadPool = m_compPoolMgr->CreateNewPool<gfx_cs::Quad>(); }
    else
    { quadPool = m_compPoolMgr->GetPool<gfx_cs::Quad>(); }

    quad_pool::iterator itrQuad = quadPool->GetNext();
    (*itrQuad)->SetValue(gfx_cs::Quad(m_rect));

    // Create the transform component (and the transform pool if necessary)
    typedef math_cs::transform_pool           t_pool;
    math_cs::transform_pool_vptr              tPool;

    if (m_compPoolMgr->Exists(transform) == false)
    { tPool = m_compPoolMgr->CreateNewPool<math_cs::Transform>(); }
    else
    { tPool = m_compPoolMgr->GetPool<math_cs::Transform>(); }

    t_pool::iterator itrTransform = tPool->GetNext();
    (*itrTransform)->SetValue(Transform());

    // Create an entity from the manager and return to user
    m_entMgr->InsertComponent(a_ent, (*itrTransform)->GetValue());
    m_entMgr->InsertComponent(a_ent, (*itrQuad)->GetValue());

    // Create the texture coords (and the texture coord pool if necessary)
    if (m_texCoords)
    {
      typedef gfx_cs::texture_coords_pool       tcoord_pool;
      gfx_cs::texture_coords_pool_vptr          tCoordPool;

      if (m_compPoolMgr->Exists(texture_coords) == false)
      { tCoordPool = m_compPoolMgr->CreateNewPool<gfx_cs::TextureCoords>(); }
      else
      { tCoordPool = m_compPoolMgr->GetPool<gfx_cs::TextureCoords>(); }

      tcoord_pool::iterator itrTCoord = tCoordPool->GetNext();
      TextureCoords tc;
      tc.AddCoord(math_t::Vec2f32(1.0f, 1.0f));
      tc.AddCoord(math_t::Vec2f32(0.0f, 1.0f));
      tc.AddCoord(math_t::Vec2f32(1.0f, 0.0f));
      tc.AddCoord(math_t::Vec2f32(0.0f, 0.0f));
      (*itrTCoord)->SetValue(tc);
      m_entMgr->InsertComponent(a_ent, (*itrTCoord)->GetValue() );
    }
  }

};};};