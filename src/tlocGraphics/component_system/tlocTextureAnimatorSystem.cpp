#include "tlocTextureAnimatorSystem.h"

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>
#include <tlocCore/component_system/tlocEntity.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/data_structures/tlocVariadic.h>

#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocGraphics/component_system/tlocTextureAnimator.h>

namespace tloc { namespace graphics { namespace component_system {

  using namespace core_ds;

  typedef TextureAnimatorSystem::error_type    error_type;

  //////////////////////////////////////////////////////////////////////////
  // QuadRenderSystem

  TextureAnimatorSystem::
    TextureAnimatorSystem(event_manager_sptr a_eventMgr,
                          entity_manager_sptr a_entityMgr)
     : base_type(a_eventMgr, a_entityMgr,
                 Variadic<component_type, 1>(components::texture_animator))
     , m_totalTime(0)
  { }

  error_type
    TextureAnimatorSystem::
    Pre_Initialize()
  { return ErrorSuccess; }

  error_type
    TextureAnimatorSystem::
    InitializeEntity(const entity_manager*, const entity_type* a_ent)
  {
    const entity_type* ent = a_ent;

    gfx_cs::TextureAnimator* texAnim =
      ent->GetComponent<gfx_cs::TextureAnimator>();
    texAnim->SetStartTime(0);

    return ErrorSuccess;
  }

  error_type
    TextureAnimatorSystem::
    ShutdownEntity(const entity_manager*, const entity_type*)
  { return ErrorSuccess; }

  void
    TextureAnimatorSystem::
    Pre_ProcessActiveEntities(f64 a_deltaT)
  {
    m_totalTime += a_deltaT;
  }

  void
    TextureAnimatorSystem::
    ProcessEntity(const entity_manager*, const entity_type* a_ent, f64)
  {
    using namespace core::component_system;
    using math_t::Vec4f32;
    using math_t::Vec2f32;

    typedef gfx_cs::TextureCoords                 tex_coords;

    const entity_type* ent = a_ent;

    gfx_cs::TextureAnimator* texAnim =
      ent->GetComponent<gfx_cs::TextureAnimator>();

    f64 diff = m_totalTime - texAnim->GetStartTime();
    f64 fps = 1.0f / core_utils::CastNumber<f64>(texAnim->GetFPS());

    while (diff > fps)
    {

      if (texAnim->IsPaused() == false &&
          texAnim->IsStopped() == false)
      {
        texAnim->NextFrame();
      }

      texAnim->SetStartTime(texAnim->GetStartTime() + fps);
      diff = m_totalTime - texAnim->GetStartTime();
    }

    if (ent->HasComponent(components::texture_coords) &&
        texAnim->IsSpriteSetChanged())
    {
      gfx_cs::TextureCoords* coordPtr =
        ent->GetComponent<gfx_cs::TextureCoords>();

      *coordPtr = texAnim->GetSpriteSet(texAnim->GetCurrentSpriteSetIndex());

      texAnim->SetSpriteSetChanged(false);
    }
  }

  void TextureAnimatorSystem::
    Post_ProcessActiveEntities(f64)
  { }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiations

  template class core_sptr::SharedPtr<TextureAnimatorSystem>;

};};};