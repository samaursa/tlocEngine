#ifndef _TLOC_PREFAB_GRAPHICS_SPRITE_H_
#define _TLOC_PREFAB_GRAPHICS_SPRITE_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/media/tlocSpriteLoader.h>

namespace tloc { namespace prefab { namespace graphics {

  namespace priv {

  template <typename SpriteLoaderIterator>
    void
      DoAddSpriteAnimation(core_cs::Entity* a_entity,
                           core_cs::EntityManager& a_mgr,
                           core_cs::ComponentPoolManager& a_poolMgr,
                           SpriteLoaderIterator a_begin,
                           SpriteLoaderIterator a_end,
                           bool a_loop,
                           tl_size a_fps);

  };

  template <typename SpriteLoaderIterator>
  void
    AddSpriteAnimation(core_cs::Entity* a_entity,
                       core_cs::EntityManager& a_mgr,
                       core_cs::ComponentPoolManager& a_poolMgr,
                       SpriteLoaderIterator a_begin,
                       SpriteLoaderIterator a_end,
                       bool a_loop = true,
                       tl_size a_fps = 24)
  {
    using namespace gfx_med;
    using namespace p_sprite_loader::parser;

    type_traits::AssertTypeIsSupported
      <SpriteLoaderIterator,
       SpriteLoader_SpriteSheetPacker::iterator,
       SpriteLoader_SpriteSheetPacker::const_iterator>();

    priv::DoAddSpriteAnimation(a_entity, a_mgr, a_poolMgr,
                               a_begin, a_end, a_loop, a_fps);
  }

};};};

#endif