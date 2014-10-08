#include "tlocFan.h"

#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocGraphics/component_system/tlocFan.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocPrefab/math/tlocTransform.h>
#include <tlocPrefab/graphics/tlocTextureCoords.h>

namespace tloc { namespace prefab { namespace graphics {

  using core_cs::Entity;
  using core_cs::EntityManager;
  using core_cs::ComponentPoolManager;
  using core_sptr::MakeShared;

  using namespace core_cs;
  using namespace math_cs;
  using namespace math_cs::components;
  using namespace tloc::graphics::component_system;
  using namespace tloc::graphics::component_system::components;

  using math_t::Circle_T;

  // ///////////////////////////////////////////////////////////////////////
  // Fan

  Fan::
    Fan(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : base_type(a_entMgr, a_poolMgr)
    , m_circle(circle_type(circle_type::radius(1.0f)) )
    , m_numSides(8)
    , m_texCoords(true)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Fan::component_ptr
    Fan::
    Construct() const
  {
    typedef ComponentPoolManager    pool_mgr;
    typedef gfx_cs::fan_pool        fan_pool;

    gfx_cs::fan_pool_vptr fanPool 
      = m_compPoolMgr->GetOrCreatePool<gfx_cs::Fan>();

    fan_pool::iterator itr = fanPool->GetNext();
    (*itr)->SetValue(
      MakeShared<gfx_cs::Fan>(m_circle, gfx_cs::Fan::sides(m_numSides)
      ));

    return *(*itr)->GetValuePtr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Fan::entity_ptr
    Fan::
    Create() const
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  void
    Fan::
    Add(entity_ptr a_ent) const
  {
    // -----------------------------------------------------------------------
    // transform component

    if (a_ent->HasComponent<math_cs::Transform>() == false)
    { pref_math::Transform(m_entMgr, m_compPoolMgr).Add(a_ent); }

    // -----------------------------------------------------------------------
    // fan component

    m_entMgr->InsertComponent( insert_params(a_ent, Construct())
                              .DispatchTo(GetListeners()) );

    // Create the texture coords (and the texture coord pool if necessary)
    if (m_texCoords)
    {
      typedef math_t::Circlef32 circle_type;
      // Create the texture co-ordinates
      circle_type circForTex;
      circForTex.SetRadius(0.5f);

      using math_t::degree_f32;
      const f32 angleInterval = 360.0f/m_numSides;

      TextureCoords tCoords(m_entMgr, m_compPoolMgr);

      tCoords.AddCoord(math_t::Vec2f32(0.5f, 0.5f));
      for (f32 i = 0; i <= m_numSides; ++i)
      {
        math_t::Vec2f32 newTexCoord =
          circForTex.GetCoord(degree_f32(angleInterval * i));
        newTexCoord += math_t::Vec2f32(0.5f, 0.5f); // tex co-ordinates start from 0, 0
        tCoords.AddCoord(newTexCoord);
      }

      tCoords.Add(a_ent);
    }
  }

};};};