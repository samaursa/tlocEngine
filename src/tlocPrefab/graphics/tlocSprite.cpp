#include "tlocSprite.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocGraphics/component_system/tlocTextureAnimator.h>
#include <tlocGraphics/media/tlocSprite.h>

namespace tloc { namespace prefab { namespace graphics { namespace priv {

  using namespace gfx_med;
  using namespace p_sprite_loader::parser;

  template <typename SpriteLoaderIterator>
  void
    DoAddSpriteAnimation(core_cs::entity_vptr a_entity,
                         core_cs::entity_manager_vptr a_mgr,
                         core_cs::component_pool_mgr_vptr a_poolMgr,
                         SpriteLoaderIterator a_begin,
                         SpriteLoaderIterator a_end,
                         bool a_loop,
                         tl_size a_fps,
                         tl_size a_setIndex,
                         tl_size a_startingFrame,
                         bool a_paused)
  {
    TLOC_ASSERT_NOT_NULL(a_entity);
    TLOC_ASSERT(a_begin != a_end, "No sprite info available");

    typedef typename PointeeType<SpriteLoaderIterator>::value_type     sprite_info;

    using namespace gfx_cs;
    using namespace gfx_cs::components;

    typedef gfx_cs::texture_animator_pool           ta_pool;
    gfx_cs::texture_animator_pool_vptr              taPool;

    gfx_cs::texture_animator_vptr ta = nullptr;

    const tl_size size = a_entity->GetComponents(texture_animator).size();

    if (size && a_setIndex < size)
    {
      ta = a_entity->GetComponent<gfx_cs::TextureAnimator>(a_setIndex);
    }
    else
    {
      if (a_poolMgr->Exists(texture_animator) == false)
      { taPool = a_poolMgr->CreateNewPool<gfx_cs::TextureAnimator>(); }
      else
      { taPool = a_poolMgr->GetPool<gfx_cs::TextureAnimator>(); }

      ta_pool::iterator itrTa = taPool->GetNext();
      (*itrTa)->SetValue(TextureAnimator() );

      ta = (*itrTa)->GetValue();

      a_mgr->InsertComponent(a_entity, ta);
    }

    TextureCoords tcoord;
    for (int i = 0; a_begin != a_end; ++i, ++a_begin)
    {
      sprite_info si = *a_begin;

      tcoord.AddCoord(TextureCoords::vec_type(si.GetTexCoordEnd()[0],
                                              si.GetTexCoordStart()[1]),
                                              TextureCoords::set_index(i));
      tcoord.AddCoord(TextureCoords::vec_type(si.GetTexCoordStart()),
                                              TextureCoords::set_index(i));
      tcoord.AddCoord(TextureCoords::vec_type(si.GetTexCoordEnd()),
                                              TextureCoords::set_index(i));
      tcoord.AddCoord(TextureCoords::vec_type(si.GetTexCoordStart()[0],
                                              si.GetTexCoordEnd()[1]),
                                              TextureCoords::set_index(i));
    }

    TLOC_ASSERT_NOT_NULL(ta);

    const TextureAnimator::size_type currSetIndex =
      ta->GetCurrentSpriteSeqIndex();

    ta->AddSpriteSet(tcoord);
    ta->SetCurrentSpriteSequence(ta->GetNumSpriteSequences() - 1);
    ta->SetLooping(a_loop);
    ta->SetFPS(a_fps);
    ta->SetFrame(a_startingFrame);
    ta->SetPaused(a_paused);

    ta->SetCurrentSpriteSequence(currSetIndex);
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  using gfx_med::sprite_sheet_ul;

#define TLOC_EXPLICITLY_INSTANTIATE_DO_ADD_SPRITE_ANIM(_type_)\
  template void\
    DoAddSpriteAnimation<_type_>\
    (core_cs::entity_vptr a_entity,\
     core_cs::entity_manager_vptr,\
     core_cs::component_pool_mgr_vptr,\
     _type_,\
     _type_,\
     bool, tl_size, tl_size, tl_size, bool)

  TLOC_EXPLICITLY_INSTANTIATE_DO_ADD_SPRITE_ANIM(sprite_sheet_ul::iterator);
  TLOC_EXPLICITLY_INSTANTIATE_DO_ADD_SPRITE_ANIM(sprite_sheet_ul::const_iterator);

  TLOC_EXPLICITLY_INSTANTIATE_DO_ADD_SPRITE_ANIM(sprite_sheet_str::iterator);
  TLOC_EXPLICITLY_INSTANTIATE_DO_ADD_SPRITE_ANIM(sprite_sheet_str::const_iterator);

};};};};