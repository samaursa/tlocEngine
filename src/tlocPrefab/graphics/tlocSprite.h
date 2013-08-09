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
                           tl_size a_fps,
                           tl_size a_setIndex,
                           tl_size a_startingFrame,
                           bool a_paused);

  };

  class SpriteAnimation
    : public Prefab_I
  {
  public:
    typedef SpriteAnimation       this_type;
    typedef tl_size               size_type;

  public:
    SpriteAnimation(core_cs::EntityManager*  a_entMgr,
                    core_cs::ComponentPoolManager* a_poolMgr)
                    : Prefab_I(a_entMgr, a_poolMgr)
                    , m_loop(true)
                    , m_fps(24)
                    , m_startingFrame(0)
                    , m_paused(false)
                    , m_setIndex(0)
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
                                 a_begin, a_end, m_loop, m_fps, m_setIndex,
                                 m_startingFrame, m_paused);
    }

    template <typename T_ContOfSpriteLoaderItrBeginEndPair>
    void
      Add(entity_type* a_entity,
          T_ContOfSpriteLoaderItrBeginEndPair a_spriteLoaderIterators)
    {
      using namespace gfx_med;
      using namespace p_sprite_loader::parser;

      typedef T_ContOfSpriteLoaderItrBeginEndPair           cont_type;
      typedef typename cont_type::value_type                pair_type;
      typedef typename pair_type::first_type                pair_type_first;
      typedef typename pair_type::second_type               pair_type_second;

      typedef typename cont_type::iterator                  itr_type;

      type_traits::AssertTypeIsSupported
        <pair_type_first,
         SpriteLoader_SpriteSheetPacker::iterator,
         SpriteLoader_SpriteSheetPacker::const_iterator>();

      type_traits::AssertTypeIsSupported
        <pair_type_second,
         SpriteLoader_SpriteSheetPacker::iterator,
         SpriteLoader_SpriteSheetPacker::const_iterator>();

      // We cannot add multiple sprite sheets without append, let the user know
      // LOG: convert following assert into a log
      TLOC_ASSERT(m_append,
        "Append is set to falsed, unable to generate multiple spritesheets");

      for (itr_type itr = a_spriteLoaderIterators.begin(),
                    itrEnd = a_spriteLoaderIterators.end();
                    itr != itrEnd; ++itr)
      {
        Add(a_entity, itr->first, itr->second);
      }
    }

    TLOC_DECL_PARAM_VAR(bool,       Loop, m_loop);
    TLOC_DECL_PARAM_VAR(tl_size,    Fps, m_fps);
    TLOC_DECL_PARAM_VAR(size_type,  StartingFrame, m_startingFrame);
    TLOC_DECL_PARAM_VAR(bool,       Paused, m_paused);
    TLOC_DECL_PARAM_VAR(tl_size,    SetIndex, m_setIndex);
  };

};};};

#endif