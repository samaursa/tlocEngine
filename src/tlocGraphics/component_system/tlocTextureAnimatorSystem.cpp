#include "tlocTextureAnimatorSystem.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/data_structures/tlocVariadic.h>
#include <tlocCore/logging/tlocLogger.h>

#include <tlocGraphics/component_system/tlocTextureCoords.h>
#include <tlocGraphics/component_system/tlocTextureAnimator.h>

TLOC_DEFINE_THIS_FILE_NAME();

namespace tloc { namespace graphics { namespace component_system {

  using namespace core_ds;

  typedef TextureAnimatorSystem::error_type    error_type;

  //////////////////////////////////////////////////////////////////////////
  // QuadRenderSystem

  TextureAnimatorSystem::
    TextureAnimatorSystem(event_manager_ptr a_eventMgr,
                          entity_manager_ptr a_entityMgr)
     : base_type(a_eventMgr, a_entityMgr,
                 register_type().Add<TextureAnimator>(), 
                 "TextureAnimatorSystem")
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  error_type
    TextureAnimatorSystem::
    Pre_Initialize()
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


  error_type
    TextureAnimatorSystem::
    InitializeEntity(entity_ptr a_ent)
  {
    const auto size = a_ent->size_components<TextureAnimator>();
    const auto textureCoordsSize = a_ent->size_components<TextureCoords>();

    TLOC_LOG_GFX_WARN_FILENAME_ONLY_IF(size > textureCoordsSize) 
      << "Entity " << *a_ent << " has " << size 
      << " TextureAnimators and only " << textureCoordsSize << " TextureCoords";

    for (tl_size i = 0; i < size; ++i)
    {
      gfx_cs::texture_animator_sptr texAnim =
        a_ent->GetComponent<gfx_cs::TextureAnimator>(i);
      texAnim->SetStartTime(0);
    }

    return ErrorSuccess;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


  error_type
    TextureAnimatorSystem::
    ShutdownEntity(entity_ptr)
  { return ErrorSuccess; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


  void
    TextureAnimatorSystem::
    Pre_ProcessActiveEntities(f64 )
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


  void
    TextureAnimatorSystem::
    ProcessEntity(entity_ptr a_ent, f64 a_deltaT)
  {
    using namespace core::component_system;
    using math_t::Vec4f32;
    using math_t::Vec2f32;

    typedef gfx_cs::TextureCoords                 tex_coords;

    const tl_size size = a_ent->size_components<TextureAnimator>();

    for (tl_size i = 0; i < size; ++i)
    {
      gfx_cs::texture_animator_sptr texAnim =
        a_ent->GetComponent<gfx_cs::TextureAnimator>(i);

      if (texAnim->IsEnabled() == false) { continue; }

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

      if (a_ent->HasComponent<TextureCoords>() && texAnim->IsSpriteSeqChanged())
      {
        if (a_ent->HasComponent<gfx_cs::TextureCoords>(i))
        {
          gfx_cs::texture_coords_sptr coordPtr =
            a_ent->GetComponent<gfx_cs::TextureCoords>(i);

          TLOC_ASSERT(coordPtr,
            "Texture coords don't exist for corresponding texture animator");

          *coordPtr = texAnim->GetSpriteSequence(texAnim->GetCurrentSpriteSeqIndex());

          texAnim->SetSpriteSequenceChanged(false);
        }
        else
        {
          TLOC_LOG_GFX_WARN_FILENAME_ONLY() 
            << "Entity " << *a_ent << " does not have enough "
            << "TextureCoords. " << "Disabling " << i << "th TextureAnimator";
          DoGetEntityManager()->DisableComponent(core::MakePair(a_ent, texAnim));
        }
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


  void TextureAnimatorSystem::
    Post_ProcessActiveEntities(f64)
  { }

};};};


//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(TextureAnimatorSystem);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(TextureAnimatorSystem);