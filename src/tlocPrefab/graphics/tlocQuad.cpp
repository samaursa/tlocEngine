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

  Quad::entity_type*
    Quad::
    Create()
  {
    Entity* ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  void
    Quad::
    Add(entity_type* a_ent)
  {
    using namespace gfx_cs::components;
    using namespace math_cs::components;

    typedef ComponentPoolManager      pool_mgr;

    // Create the quad (and the quad pool if necessary)
    typedef gfx_cs::quad_sptr_pool    quad_pool;
    gfx_cs::quad_sptr_pool_sptr       quadPool;

    if (m_compPoolMgr->Exists(quad) == false)
    { quadPool = m_compPoolMgr->CreateNewPool<quad_sptr>(); }
    else
    { quadPool = m_compPoolMgr->GetPool<quad_sptr>(); }

    quad_pool::iterator itrQuad = quadPool->GetNext();
    itrQuad->SetValue(quad_sptr(new gfx_cs::Quad(m_rect) ));

    // Create the transform component (and the transform pool if necessary)
    typedef math_cs::transform_f32_sptr_pool  t_pool;
    math_cs::transform_f32_sptr_pool_sptr     tPool;

    if (m_compPoolMgr->Exists(transform) == false)
    { tPool = m_compPoolMgr->CreateNewPool<transform_sptr>(); }
    else
    { tPool = m_compPoolMgr->GetPool<transform_sptr>(); }

    t_pool::iterator itrTransform = tPool->GetNext();
    itrTransform->SetValue(transform_sptr(new Transform()) );

    // Create an entity from the manager and return to user
    m_entMgr->InsertComponent(a_ent, itrTransform->GetValue().get() );
    m_entMgr->InsertComponent(a_ent, itrQuad->GetValue().get() );

    // Create the texture coords (and the texture coord pool if necessary)
    if (m_texCoords)
    {
      typedef gfx_cs::texture_coords_sptr_pool  tcoord_pool;
      gfx_cs::texture_coords_sptr_pool_sptr     tCoordPool;

      if (m_compPoolMgr->Exists(texture_coords) == false)
      { tCoordPool = m_compPoolMgr->CreateNewPool<texture_coords_sptr>(); }
      else
      { tCoordPool = m_compPoolMgr->GetPool<texture_coords_sptr>(); }

      tcoord_pool::iterator itrTCoord = tCoordPool->GetNext();
      texture_coords_sptr tc(new TextureCoords());
      tc->AddCoord(math_t::Vec2f32(1.0f, 1.0f));
      tc->AddCoord(math_t::Vec2f32(0.0f, 1.0f));
      tc->AddCoord(math_t::Vec2f32(1.0f, 0.0f));
      tc->AddCoord(math_t::Vec2f32(0.0f, 0.0f));
      itrTCoord->SetValue(tc);
      m_entMgr->InsertComponent(a_ent, itrTCoord->GetValue().get() );
    }
  }

};};};