#ifndef _TLOC_PREFAB_GRAPHICS_SPRITE_H_
#define _TLOC_PREFAB_GRAPHICS_SPRITE_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/media/tlocSprite.h>
#include <tlocGraphics/component_system/tlocTextureAnimator.h>

namespace tloc { namespace prefab { namespace graphics {

  class SpriteAnimation
    : public Prefab_TI<gfx_cs::TextureAnimator>
  {
  public:
    typedef Prefab_TI<component_type>         base_type;
    typedef SpriteAnimation                   this_type;
    typedef tl_size                           size_type;

  public:
    SpriteAnimation(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    template <typename SpriteLoaderIterator>
    component_ptr Construct(SpriteLoaderIterator a_begin, 
                            SpriteLoaderIterator a_end,
                            component_ptr a_existing = nullptr) const;

    template <typename SpriteLoaderIterator>
    void
      Add(entity_ptr a_entity,
          SpriteLoaderIterator a_begin,
          SpriteLoaderIterator a_end) const;

    template <typename T_ContOfSpriteLoaderItrBeginEndPair>
    void
      Add(entity_ptr a_entity,
          T_ContOfSpriteLoaderItrBeginEndPair a_spriteLoaderIterators);

    TLOC_DECL_PARAM_VAR(bool,       Loop, m_loop);
    TLOC_DECL_PARAM_VAR(tl_size,    Fps, m_fps);
    TLOC_DECL_PARAM_VAR(size_type,  StartingFrame, m_startingFrame);
    TLOC_DECL_PARAM_VAR(bool,       Paused, m_paused);
    TLOC_DECL_PARAM_VAR(tl_size,    SetIndex, m_setIndex);

  private:

    template <typename SpriteLoaderIterator>
    void
      DoAdd(entity_ptr a_entity,
            SpriteLoaderIterator a_begin, SpriteLoaderIterator a_end) const;

    template <typename SpriteLoaderIterator>
    component_ptr
      DoConstructSpriteAnimation(SpriteLoaderIterator a_begin,
                                 SpriteLoaderIterator a_end, 
                                 component_ptr a_existing) const;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename SpriteLoaderIterator>
  SpriteAnimation::component_ptr 
    SpriteAnimation::
    Construct(SpriteLoaderIterator a_begin, 
              SpriteLoaderIterator a_end, 
              component_ptr a_existing) const
  {
    type_traits::AssertTypeIsSupported
      <SpriteLoaderIterator, 
       sprite_sheet_str::iterator,
       sprite_sheet_str::const_iterator,
       sprite_sheet_ul::iterator,
       sprite_sheet_ul::const_iterator>();

    return DoConstructSpriteAnimation(a_begin, a_end, a_existing);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename SpriteLoaderIterator>
  void
    SpriteAnimation::
    Add(entity_ptr a_entity,
        SpriteLoaderIterator a_begin,
        SpriteLoaderIterator a_end) const
  {
    using namespace gfx_med;

    type_traits::AssertTypeIsSupported
      <SpriteLoaderIterator, 
       sprite_sheet_str::iterator,
       sprite_sheet_str::const_iterator,
       sprite_sheet_ul::iterator,
       sprite_sheet_ul::const_iterator>();

    DoAdd(a_entity, a_begin, a_end);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_ContOfSpriteLoaderItrBeginEndPair>
  void
    SpriteAnimation::
    Add(entity_ptr a_entity,
        T_ContOfSpriteLoaderItrBeginEndPair a_spriteLoaderIterators)
  {
    using namespace gfx_med;

    typedef T_ContOfSpriteLoaderItrBeginEndPair           cont_type;
    typedef typename cont_type::value_type                pair_type;
    typedef typename pair_type::first_type                pair_type_first;
    typedef typename pair_type::second_type               pair_type_second;

    typedef typename cont_type::iterator                  itr_type;

    type_traits::AssertTypeIsSupported
      <pair_type_first,
       sprite_sheet_str::iterator,
       sprite_sheet_str::const_iterator,
       sprite_sheet_ul::iterator,
       sprite_sheet_ul::const_iterator>();

    type_traits::AssertTypeIsSupported
      <pair_type_second, 
       sprite_sheet_str::iterator,
       sprite_sheet_str::const_iterator,
       sprite_sheet_ul::iterator,
       sprite_sheet_ul::const_iterator>();

    for (itr_type itr = a_spriteLoaderIterators.begin(),
                  itrEnd = a_spriteLoaderIterators.end();
                  itr != itrEnd; ++itr)
    {
      Add(a_entity, itr->first, itr->second);
    }
  }

};};};

#endif