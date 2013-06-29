#ifndef _TLOC_PREFAB_GRAPHICS_SPRITE_H_
#define _TLOC_PREFAB_GRAPHICS_SPRITE_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/media/tlocSpriteLoader.h>

namespace tloc { namespace prefab { namespace graphics {

  namespace priv {

  template <typename SpriteLoaderIterator>
    void
      DoAddSpriteAnimation(core_cs::Entity* a_entity,
                           core_cs::EntityManager* a_mgr,
                           core_cs::ComponentPoolManager* a_poolMgr,
                           SpriteLoaderIterator a_begin,
                           SpriteLoaderIterator a_end,
                           bool a_loop,
                           tl_size a_fps);

  };

  class SpriteAnimation
    : public Prefab_I
  {
  public:
    typedef SpriteAnimation       this_type;

  public:
    SpriteAnimation(core_cs::EntityManager*  a_entMgr,
                    core_cs::ComponentPoolManager* a_poolMgr)
                    : Prefab_I(a_entMgr, a_poolMgr)
                    , m_loop(true)
                    , m_fps(24)
    { }

    template <typename SpriteLoaderIterator>
    void
      Add(entity_type* a_entity,
          SpriteLoaderIterator a_begin,
          SpriteLoaderIterator a_end)
    {
      using namespace gfx_med;
      using namespace p_sprite_loader::parser;

      type_traits::AssertTypeIsSupported
        <SpriteLoaderIterator,
        SpriteLoader_SpriteSheetPacker::iterator,
        SpriteLoader_SpriteSheetPacker::const_iterator>();

      priv::DoAddSpriteAnimation(a_entity, m_entMgr, m_compPoolMgr,
                                 a_begin, a_end, m_loop, m_fps);
    }

    TLOC_DECL_PARAM_VAR(bool, Loop, m_loop);
    TLOC_DECL_PARAM_VAR(tl_size, Fps, m_fps);
  };

};};};

#endif