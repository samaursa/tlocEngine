#include "tlocTextureAnimator.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace {

    enum
    {
      k_looping,
      k_paused,
      k_spriteSetChanged,
      k_count
    };

  };

  TextureAnimator::
    TextureAnimator()
    : base_type(k_component_type)
    , m_currentSet(0)
    , m_fps(24)
    , m_startTime(0)
    , m_dimensions(0, 0)
    , m_flags(k_count)
  { }

  void
    TextureAnimator::
    AddSpriteSet(const coord_set& a_coord)
  {
    m_coordSets.push_back(a_coord);
  }

  void
    TextureAnimator::
    ModifySpriteSet(const coord_set& a_coord, size_type a_index)
  {
    m_coordSets[a_index] = a_coord;
  }

  void
    TextureAnimator::
    RemoveSpriteCoord(size_type a_index)
  {
    cont_type::iterator itr = m_coordSets.begin();
    core::advance(itr, a_index);
    m_coordSets.erase(itr);
  }

  TextureAnimator::coord_set
    TextureAnimator::
    GetSpriteSet(size_type a_setIndex)
  {
    return m_coordSets[a_setIndex];
  }

  const TextureAnimator::coord_set
    TextureAnimator::
    GetSpriteSet(size_type a_setIndex) const
  {
    return m_coordSets[a_setIndex];
  }

  void
    TextureAnimator::
    NextFrame()
  {
    const size_type setSize = m_coordSets[m_currentSet].GetNumSets();
    size_type currentFrame = m_coordSets[m_currentSet].GetCurrentSet();

    ++currentFrame;
    if (currentFrame >= setSize)
    {
      if (m_flags.IsMarked(k_looping))
      { currentFrame = 0; }
      else
      { currentFrame = setSize - 1; }
    }

    m_coordSets[m_currentSet].SetCurrentSet(currentFrame);
    m_flags.Mark(k_spriteSetChanged);
  }

  void
    TextureAnimator::
    PrevFrame()
  {
    const size_type setSize = m_coordSets[m_currentSet].GetNumSets();
    size_type currentFrame = m_coordSets[m_currentSet].GetCurrentSet();

    currentFrame--;
    if (currentFrame >= setSize)
    {
      if (m_flags.IsMarked(k_looping))
      { currentFrame = setSize - 1; }
      else
      { currentFrame = 0; }
    }

    m_coordSets[m_currentSet].SetCurrentSet(currentFrame);
    m_flags.Mark(k_spriteSetChanged);
  }

  const bool
    TextureAnimator::
    IsLooping() const
  { return m_flags.IsMarked(k_looping); }

  const bool
    TextureAnimator::
    IsPaused() const
  { return m_flags.IsMarked(k_paused); }

  const bool
    TextureAnimator::
    IsSpriteSetChanged() const
  { return m_flags.IsMarked(k_spriteSetChanged); }

  void
    TextureAnimator::
    SetLooping(const bool& a_looping)
  { m_flags[k_looping] = a_looping; }

  void
    TextureAnimator::
    SetPaused(const bool& a_pause)
  { m_flags[k_paused] = a_pause; }

  void
    TextureAnimator::
    SetCurrentSpriteSet(const size_type& a_spriteSetIndex)
  {
    TLOC_ASSERT(a_spriteSetIndex < GetNumSpriteSets(), "Index out of bounds!");
    m_currentSet = a_spriteSetIndex;
    m_flags.Mark(k_spriteSetChanged);
  }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiations

  // SmartPtr
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(TextureAnimator);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(texture_animator_sptr);

};};};