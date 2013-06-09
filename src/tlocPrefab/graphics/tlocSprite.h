#ifndef _TLOC_PREFAB_GRAPHICS_SPRITE_H_
#define _TLOC_PREFAB_GRAPHICS_SPRITE_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/media/tlocSpriteLoader.h>

namespace tloc { namespace prefab { namespace graphics {

  namespace priv {

    template <typename T_ParserType>
    void
      DoAddSpriteAnimation(core_cs::Entity* a_entity,
                           core_cs::EntityManager& a_mgr,
                           core_cs::ComponentPoolManager& a_poolMgr,
                           typename gfx_med::SpriteLoader_T <T_ParserType>::
                           const_iterator a_begin,
                           typename gfx_med::SpriteLoader_T <T_ParserType>::
                           const_iterator a_end);

  };

  template <typename T_ParserType>
  void
    AddSpriteAnimation(core_cs::Entity* a_entity,
                       core_cs::EntityManager& a_mgr,
                       core_cs::ComponentPoolManager& a_poolMgr,
                       typename gfx_med::SpriteLoader_T
                       <T_ParserType>::const_iterator a_begin,
                       typename gfx_med::SpriteLoader_T
                       <T_ParserType>::const_iterator a_end)
  {
    using namespace gfx_med;
    using namespace p_sprite_loader::parser;

    type_traits::AssertTypeIsSupported
      <T_ParserType,
       SpriteSheetPacker>();

    DoAddSpriteAnimation(a_entity, a_mgr, a_poolMgr, a_begin, a_end);
  }

};};};

#endif