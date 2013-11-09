#include "tlocTextureAnimator.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace {

    enum
    {
      k_looping,
      k_paused,
      k_stopped,
      k_spriteSetChanged,
      k_count
    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // CoordSet

  TextureAnimator::CoordSet::
    CoordSet()
    : m_frameDeltaT(24)
    , m_startTime(0)
    , m_totalTime(0)
    , m_flags(k_count)
  { }

  TextureAnimator::CoordSet::
    CoordSet(const TextureCoords& a_coords)
    : m_coords(a_coords)
    , m_frameDeltaT(24)
    , m_startTime(0)
    , m_totalTime(0)
    , m_flags(k_count)
  { }

  TextureAnimator::CoordSet::
    CoordSet(const CoordSet& a_other)
    : m_coords(a_other.m_coords)
    , m_frameDeltaT(a_other.m_frameDeltaT)
    , m_startTime(a_other.m_startTime)
    , m_totalTime(a_other.m_totalTime)
    , m_flags(a_other.m_flags)
  { }

  // ///////////////////////////////////////////////////////////////////////
  // TextureAnimator

  TextureAnimator::
    TextureAnimator()
    : base_type(k_component_type)
    , m_currentSet(0)
  { }

  void
    TextureAnimator::
    AddSpriteSet(const TextureCoords& a_coord)
  {
    m_coordSets.push_back(CoordSet(a_coord));
  }

  void
    TextureAnimator::
    ModifySpriteSet(const TextureCoords& a_coord, size_type a_index)
  {
    m_coordSets[a_index] = CoordSet(a_coord);
  }

  void
    TextureAnimator::
    RemoveSpriteSet(size_type a_index)
  {
    cont_type::iterator itr = m_coordSets.begin();
    core::advance(itr, a_index);
    m_coordSets.erase(itr);
  }

  TextureCoords&
    TextureAnimator::
    GetSpriteSequence(size_type a_setIndex)
  {
    return m_coordSets[a_setIndex].m_coords;
  }

  const TextureCoords&
    TextureAnimator::
    GetSpriteSequence(size_type a_setIndex) const
  {
    return m_coordSets[a_setIndex].m_coords;
  }

  TextureCoords&
    TextureAnimator::
    GetCurrentSpriteSequence()
  { return GetSpriteSequence(GetCurrentSpriteSeqIndex()); }

  const TextureCoords&
    TextureAnimator::
    GetCurrentSpriteSequence() const
  { return GetSpriteSequence(GetCurrentSpriteSeqIndex()); }

  void
    TextureAnimator::
    NextFrame()
  {
    const size_type setSize = GetCurrentSpriteSequence().GetNumSets();
    size_type currentFrame = GetCurrentSpriteSequence().GetCurrentSet();

    ++currentFrame;
    if (currentFrame >= setSize)
    {
      if (m_coordSets[m_currentSet].m_flags.IsMarked(k_looping))
      { currentFrame = 0; }
      else
      { currentFrame = setSize - 1; }
    }

    SetFrame(currentFrame);
  }

  void
    TextureAnimator::
    SetFrame(size_type a_index)
  {
    GetCurrentSpriteSequence().SetCurrentSet(a_index);
    m_coordSets[m_currentSet].m_flags.Mark(k_spriteSetChanged);
  }

  void
    TextureAnimator::
    PrevFrame()
  {
    const size_type setSize = GetCurrentSpriteSequence().GetNumSets();
    size_type currentFrame = GetCurrentSpriteSequence().GetCurrentSet();

    currentFrame--;
    if (currentFrame >= setSize)
    {
      if (m_coordSets[m_currentSet].m_flags.IsMarked(k_looping))
      { currentFrame = setSize - 1; }
      else
      { currentFrame = 0; }
    }

    GetCurrentSpriteSequence().SetCurrentSet(currentFrame);
    m_coordSets[m_currentSet].m_flags.Mark(k_spriteSetChanged);
  }

  const bool
    TextureAnimator::
    IsLooping() const
  { return m_coordSets[m_currentSet].m_flags.IsMarked(k_looping); }

  const bool
    TextureAnimator::
    IsPaused() const
  { return m_coordSets[m_currentSet].m_flags.IsMarked(k_paused); }

  const bool
    TextureAnimator::
    IsStopped() const
  { return m_coordSets[m_currentSet].m_flags.IsMarked(k_stopped); }

  const bool
    TextureAnimator::
    IsLastFrame() const
  {
    const TextureCoords& currSeq = GetCurrentSpriteSequence();
    return currSeq.GetCurrentSet() > currSeq.GetNumSets();
  }

  const bool
    TextureAnimator::
    IsSpriteSeqChanged() const
  { return m_coordSets[m_currentSet].m_flags.IsMarked(k_spriteSetChanged); }

  const TextureAnimator::size_type
    TextureAnimator::
    GetFPS() const
  {
    return static_cast<size_type>(1.0f / m_coordSets[m_currentSet].m_frameDeltaT);
  }

  void
    TextureAnimator::
    SetLooping(bool a_looping)
  { m_coordSets[m_currentSet].m_flags[k_looping] = a_looping; }

  void
    TextureAnimator::
    SetPaused(bool a_pause)
  { m_coordSets[m_currentSet].m_flags[k_paused] = a_pause; }

  void
    TextureAnimator::
    SetStopped(bool a_stop)
  {
    m_coordSets[m_currentSet].m_flags[k_stopped] = a_stop;
    if (a_stop)
    { SetFrame(0); }
  }

  void
    TextureAnimator::
    SetSpriteSequenceChanged(bool a_changed)
  {
    m_coordSets[m_currentSet].m_flags[k_spriteSetChanged] = a_changed;
  }

  void
    TextureAnimator::
    SetCurrentSpriteSequence(size_type a_spriteSetIndex)
  {
    TLOC_ASSERT(a_spriteSetIndex < GetNumSpriteSequences(), "Index out of bounds!");
    m_currentSet = a_spriteSetIndex;
    m_coordSets[m_currentSet].m_flags.Mark(k_spriteSetChanged);
  }

  void
    TextureAnimator::
    SetFPS(size_type a_fps)
  {
    m_coordSets[m_currentSet].m_frameDeltaT =
      1.0f / core_utils::CastNumber<tl_float>(a_fps);
  }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiations

  // SmartPtr
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(TextureAnimator);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(texture_animator_sptr);

};};};