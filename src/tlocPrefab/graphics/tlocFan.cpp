#include "tlocFan.h"

#include <tlocMath/component_system/tlocComponentType.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocGraphics/component_system/tlocFan.h>
#include <tlocGraphics/component_system/tlocTextureCoords.h>

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

  Fan::entity_ptr
    Fan::
    Create()
  {
    entity_ptr ent = m_entMgr->CreateEntity();
    Add(ent);

    return ent;
  }

  void
    Fan::
    Add(entity_ptr a_ent)
  {
    typedef ComponentPoolManager    pool_mgr;
    typedef gfx_cs::fan_pool        fan_pool;

    gfx_cs::fan_pool_vptr           fanPool;

    // Create the fan (and the fan pool if necessary)
    if (m_compPoolMgr->Exists(fan) == false)
    { fanPool = m_compPoolMgr->CreateNewPool<gfx_cs::Fan>(); }
    else
    { fanPool = m_compPoolMgr->GetPool<gfx_cs::Fan>(); }

    fan_pool::iterator itr = fanPool->GetNext();
    (*itr)->SetValue(
      MakeShared<gfx_cs::Fan>(m_circle, gfx_cs::Fan::sides(m_numSides)
      ));

    typedef math_cs::transform_f32_pool         t_pool;
    math_cs::transform_f32_pool_vptr            tPool;

    if (m_compPoolMgr->Exists(transform) == false)
    { tPool = m_compPoolMgr->CreateNewPool<math_cs::Transformf32>(); }
    else
    { tPool = m_compPoolMgr->GetPool<math_cs::Transformf32>(); }

    t_pool::iterator itrTransform = tPool->GetNext();
    (*itrTransform)->SetValue(MakeShared<Transform>());

    // Create an entity from the manager and return to user
    m_entMgr->InsertComponent(a_ent, *(*itrTransform)->GetValue() );
    m_entMgr->InsertComponent(a_ent, *(*itr)->GetValue() );

    // Create the texture coords (and the texture coord pool if necessary)
    if (m_texCoords)
    {
      typedef gfx_cs::texture_coords_pool         tcoord_pool;
      gfx_cs::texture_coords_pool_vptr            tCoordPool;

      if (m_compPoolMgr->Exists(texture_coords) == false)
      { tCoordPool = m_compPoolMgr->CreateNewPool<gfx_cs::TextureCoords>(); }
      else
      { tCoordPool = m_compPoolMgr->GetPool<gfx_cs::TextureCoords>(); }

      tcoord_pool::iterator itrTCoord = tCoordPool->GetNext();
      TextureCoords tc;

      typedef math_t::Circlef32 circle_type;
      // Create the texture co-ordinates
      circle_type circForTex;
      circForTex.SetRadius(0.5f);

      using math_t::degree_f32;
      const f32 angleInterval = 360.0f/m_numSides;

      tc.AddCoord(math_t::Vec2f32(0.5f, 0.5f));
      for (f32 i = 0; i <= m_numSides; ++i)
      {
        math_t::Vec2f32 newTexCoord =
          circForTex.GetCoord(degree_f32(angleInterval * i));
        newTexCoord += math_t::Vec2f32(0.5f, 0.5f); // tex co-ordinates start from 0, 0
        tc.AddCoord(newTexCoord);
      }

      (*itrTCoord)->SetValue(MakeShared<TextureCoords>(tc) );
      m_entMgr->InsertComponent(a_ent, *(*itrTCoord)->GetValue() );
    }
  }

};};};