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

    const tl_size size =
      ent->GetComponents(gfx_cs::TextureAnimator::k_component_type).size();

    for (tl_size i = 0; i < size; ++i)
    {
      gfx_cs::TextureAnimator* texAnim =
        ent->GetComponent<gfx_cs::TextureAnimator>(i);
      texAnim->SetStartTime(0);
    }

    return ErrorSuccess;
  }

  error_type
    TextureAnimatorSystem::
    ShutdownEntity(const entity_manager*, const entity_type*)
  { return ErrorSuccess; }

  void
    TextureAnimatorSystem::
    Pre_ProcessActiveEntities(f64 )
  { }

  void
    TextureAnimatorSystem::
    ProcessEntity(const entity_manager*, const entity_type* a_ent, f64 a_deltaT)
  {
    using namespace core::component_system;
    using math_t::Vec4f32;
    using math_t::Vec2f32;

    typedef gfx_cs::TextureCoords                 tex_coords;

    const entity_type* ent = a_ent;

    const tl_size size =
      ent->GetComponents(gfx_cs::TextureAnimator::k_component_type).size();

    for (tl_size i = 0; i < size; ++i)
    {
      gfx_cs::TextureAnimator* texAnim =
        ent->GetComponent<gfx_cs::TextureAnimator>(i);

      texAnim->SetTotalTime(texAnim->GetTotalTime() + a_deltaT);

      f64 diff = texAnim->GetTotalTime() - texAnim->GetStartTime();
      f64 fps = texAnim->GetFrameDeltaT();

      while (diff > fps)
      {
        if (texAnim->IsPaused() == false &&
          texAnim->IsStopped() == false)
        {
          texAnim->NextFrame();
        }

        texAnim->SetStartTime(texAnim->GetStartTime() + fps);
        diff = texAnim->GetTotalTime() - texAnim->GetStartTime();
      }

      if (ent->HasComponent(components::texture_coords) &&
          texAnim->IsSpriteSeqChanged())
      {
        gfx_cs::TextureCoords* coordPtr =
          ent->GetComponent<gfx_cs::TextureCoords>(i);

        TLOC_ASSERT(coordPtr,
          "Texture coords don't exist for corresponding texture animator");

        *coordPtr = texAnim->GetSpriteSequence(texAnim->GetCurrentSpriteSeqIndex());

        texAnim->SetSpriteSequenceChanged(false);
      }
    }
  }

  void TextureAnimatorSystem::
    Post_ProcessActiveEntities(f64)
  { }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiations

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(TextureAnimatorSystem);

};};};