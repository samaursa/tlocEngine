#include "tlocSprite.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/types/tlocTypeTraits.h>

#include <tlocGraphics/component_system/tlocTextureAnimator.h>
#include <tlocGraphics/media/tlocSprite.h>

namespace tloc { namespace prefab { namespace graphics {

  using namespace gfx_med;

  // ///////////////////////////////////////////////////////////////////////
  // SpriteAnimation

  SpriteAnimation::
    SpriteAnimation(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr) 
    : base_type(a_entMgr, a_poolMgr)
    , m_loop(true)
    , m_fps(24)
    , m_startingFrame(0)
    , m_paused(false)
    , m_setIndex(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename SpriteLoaderIterator>
  void
    SpriteAnimation::
    DoAdd(entity_ptr a_entity,
          SpriteLoaderIterator a_begin, SpriteLoaderIterator a_end) const
  {
    gfx_cs::texture_animator_sptr ta = nullptr;

    const tl_size size = 
      a_entity->GetComponents(gfx_cs::TextureAnimator::k_component_type).size();

    if (size && m_setIndex < size)
    {
      ta = a_entity->GetComponent<gfx_cs::TextureAnimator>(m_setIndex);
      Construct(a_begin, a_end, ta);
    }
    else
    { 
      m_entMgr->InsertComponent( insert_params(a_entity, 
        Construct(a_begin, a_end, ta)).DispatchTo(GetListeners()) );
    }

  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename SpriteLoaderIterator>
  SpriteAnimation::component_ptr
    SpriteAnimation::
    DoConstructSpriteAnimation(SpriteLoaderIterator a_begin,
                               SpriteLoaderIterator a_end, 
                               component_ptr a_existing) const
  {
    TLOC_ASSERT(a_begin != a_end, "No sprite info available");

    typedef typename PointeeType<SpriteLoaderIterator>::value_type     sprite_info;

    using namespace gfx_cs;
    using namespace gfx_cs::components;

    typedef gfx_cs::texture_animator_pool           ta_pool;
    gfx_cs::texture_animator_pool_vptr              taPool;

    gfx_cs::texture_animator_sptr ta = a_existing;

    if (ta == nullptr)
    {
      taPool = m_compPoolMgr->GetOrCreatePool<gfx_cs::TextureAnimator>();

      ta_pool::iterator itrTa = taPool->GetNext();
      (*itrTa)->SetValue(core_sptr::MakeShared<TextureAnimator>() );

      ta = *(*itrTa)->GetValuePtr();
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
    ta->SetLooping(m_loop);
    ta->SetFPS(m_fps);
    ta->SetFrame(m_startingFrame);
    ta->SetPaused(m_paused);

    ta->SetCurrentSpriteSequence(currSetIndex);

    return ta;
  }

  //------------------------------------------------------------------------
  // Explicit instantiations

  using gfx_med::sprite_sheet_ul;

#define TLOC_EXPLICITLY_INSTANTIATE_DO_ADD_SPRITE_ANIM(_type_)\
  template SpriteAnimation::component_ptr\
    SpriteAnimation::DoConstructSpriteAnimation<_type_>\
    (_type_, _type_, SpriteAnimation::component_ptr) const;\
  \
  template void\
    SpriteAnimation::DoAdd<_type_>\
    (SpriteAnimation::entity_ptr, _type_, _type_) const


  TLOC_EXPLICITLY_INSTANTIATE_DO_ADD_SPRITE_ANIM(sprite_sheet_ul::iterator);
  TLOC_EXPLICITLY_INSTANTIATE_DO_ADD_SPRITE_ANIM(sprite_sheet_ul::const_iterator);

  TLOC_EXPLICITLY_INSTANTIATE_DO_ADD_SPRITE_ANIM(sprite_sheet_str::iterator);
  TLOC_EXPLICITLY_INSTANTIATE_DO_ADD_SPRITE_ANIM(sprite_sheet_str::const_iterator);

};};};