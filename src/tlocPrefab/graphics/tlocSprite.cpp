#include "tlocSprite.h"

#include <tlocGraphics/component_system/tlocTextureAnimator.h>

namespace tloc { namespace prefab { namespace graphics { namespace priv {

  using namespace gfx_med;
  using namespace p_sprite_loader::parser;

  template <typename SpriteLoaderIterator>
  void
    DoAddSpriteAnimation(core_cs::Entity* a_entity,
                         core_cs::EntityManager* a_mgr,
                         core_cs::ComponentPoolManager* a_poolMgr,
                         SpriteLoaderIterator a_begin,
                         SpriteLoaderIterator a_end,
                         bool a_loop,
                         tl_size a_fps,
                         bool a_append)
  {
    TLOC_ASSERT_NOT_NULL(a_entity);

    using namespace gfx_cs;
    using namespace gfx_cs::components;

    typedef gfx_cs::texture_animator_sptr_pool      ta_pool;
    gfx_cs::texture_animator_sptr_pool_sptr         taPool;

    gfx_cs::TextureAnimator* ta = nullptr;

    if (a_entity->HasComponent(texture_animator) && a_append)
    {
      ta = a_entity->GetComponent<TextureAnimator>();
    }
    else
    {
      if (a_poolMgr->Exists(texture_animator) == false)
      { taPool = a_poolMgr->CreateNewPool<texture_animator_sptr>(); }
      else
      { taPool = a_poolMgr->GetPool<texture_animator_sptr>(); }

      ta_pool::iterator itrTa = taPool->GetNext();
      itrTa->SetValue(texture_animator_sptr(new TextureAnimator()) );

      texture_animator_sptr taPtr = itrTa->GetValue();
      ta = taPtr.get();
    }

    TextureCoords tcoord;
    for (int i = 0; a_begin != a_end; ++i, ++a_begin)
    {
      SpriteInfo si = *a_begin;

      tcoord.AddCoord(TextureCoords::vec_type(si.m_texCoordEnd[0],
                                              si.m_texCoordStart[1]),
                                              TextureCoords::set_index(i));
      tcoord.AddCoord(TextureCoords::vec_type(si.m_texCoordStart),
                                              TextureCoords::set_index(i));
      tcoord.AddCoord(TextureCoords::vec_type(si.m_texCoordEnd),
                                              TextureCoords::set_index(i));
      tcoord.AddCoord(TextureCoords::vec_type(si.m_texCoordStart[0],
                                              si.m_texCoordEnd[1]),
                                              TextureCoords::set_index(i));
    }

    TLOC_ASSERT_NOT_NULL(ta);

    const TextureAnimator::size_type currSetIndex =
      ta->GetCurrentSpriteSetIndex();

    ta->AddSpriteSet(tcoord);
    ta->SetCurrentSpriteSet(ta->GetNumSpriteSets() - 1);
    ta->SetLooping(a_loop);
    ta->SetFPS(a_fps);

    ta->SetCurrentSpriteSet(currSetIndex);

    a_mgr->InsertComponent(a_entity, ta);
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  template void
    DoAddSpriteAnimation<SpriteLoader_SpriteSheetPacker::iterator>
    (core_cs::Entity* a_entity,
     core_cs::EntityManager*,
     core_cs::ComponentPoolManager*,
     SpriteLoader_SpriteSheetPacker::iterator,
     SpriteLoader_SpriteSheetPacker::iterator,
     bool, tl_size, bool);

  template void
    DoAddSpriteAnimation<SpriteLoader_SpriteSheetPacker::const_iterator>
    (core_cs::Entity* a_entity,
     core_cs::EntityManager*,
     core_cs::ComponentPoolManager*,
     SpriteLoader_SpriteSheetPacker::const_iterator,
     SpriteLoader_SpriteSheetPacker::const_iterator,
     bool, tl_size, bool);

};};};};