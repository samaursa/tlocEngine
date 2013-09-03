#include "tlocTransformAnimation.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace animation { namespace component_system {

  namespace {

    enum
    {
      k_looping,
      k_paused,
      k_stopped,
      k_keyframeSetChanged,
      k_count
    };

  };

  // ///////////////////////////////////////////////////////////////////////
  // KeyframeSetInfo

  TransformAnimation::KeyframeSetInfo::
    KeyframeSetInfo()
    : m_frameDeltaT(24)
    , m_startTime(0)
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TransformAnimation::KeyframeSetInfo::
    KeyframeSetInfo(const keyframe_set_type& a_keyframes)
    : m_keyframes(a_keyframes)
    , m_frameDeltaT(24)
    , m_startTime(0)
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TransformAnimation::KeyframeSetInfo::
    KeyframeSetInfo(const KeyframeSetInfo& a_other)
    : m_keyframes(a_other.m_keyframes)
    , m_frameDeltaT(a_other.m_frameDeltaT)
    , m_startTime(a_other.m_startTime)
    , m_flags(a_other.m_flags)
  { }

  // ///////////////////////////////////////////////////////////////////////
  // TextureAnimation

  TransformAnimation::
    TransformAnimation()
    : base_type(k_component_type)
    , m_currentSet(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    AddKeyframeSet(const keyframe_set_type& a_keyframe)
  {
    m_keyframeSets.push_back(KeyframeSetInfo(a_keyframe));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    ModifyKeyframeSet(const keyframe_set_type& a_keyframe, size_type a_index)
  {
    m_keyframeSets[a_index] = KeyframeSetInfo(a_keyframe);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    RemoveKeyframeSet(size_type a_index)
  {
    cont_type::iterator itr = m_keyframeSets.begin();
    core::advance(itr, a_index);
    m_keyframeSets.erase(itr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TransformAnimation::keyframe_set_type&
    TransformAnimation::
    GetKeyframeSet(size_type a_index)
  {
    return m_keyframeSets[a_index].m_keyframes;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const TransformAnimation::keyframe_set_type&
    TransformAnimation::
    GetKeyframeSet(size_type a_index) const
  {
    return m_keyframeSets[a_index].m_keyframes;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    NextFrame()
  {
    m_keyframeSets[m_currentSet].m_keyframes.NextFrame();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    PrevFrame()
  {
    m_keyframeSets[m_currentSet].m_keyframes.PrevFrame();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const bool
    TransformAnimation::
    IsLooping() const
  { return m_keyframeSets[m_currentSet].m_flags.IsMarked(k_looping); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const bool
    TransformAnimation::
    IsPaused() const
  { return m_keyframeSets[m_currentSet].m_flags.IsMarked(k_paused); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const bool
    TransformAnimation::
    IsStopped() const
  { return m_keyframeSets[m_currentSet].m_flags.IsMarked(k_stopped); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const bool
    TransformAnimation::
    IsTransformSetChanged() const
  { return m_keyframeSets[m_currentSet].m_flags.IsMarked(k_keyframeSetChanged); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const TransformAnimation::size_type
    TransformAnimation::
    GetFPS() const
  { return static_cast<size_type>(1.0f / m_keyframeSets[m_currentSet].m_frameDeltaT); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetLooping(bool a_looping)
  { m_keyframeSets[m_currentSet].m_flags[k_looping] = a_looping; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetPaused(bool a_pause)
  { m_keyframeSets[m_currentSet].m_flags[k_paused] = a_pause; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetStopped(bool a_stop)
  {
    m_keyframeSets[m_currentSet].m_flags[k_stopped] = a_stop;
    if (a_stop)
    { SetFrame(0); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetTransformSetChanged(bool a_changed)
  { m_keyframeSets[m_currentSet].m_flags[k_keyframeSetChanged] = a_changed; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetCurrentTransformSet(size_type a_spriteSetIndex)
  {
    TLOC_ASSERT(a_spriteSetIndex < GetNumKeyframeSets(), "Index out of bounds!");
    m_currentSet = a_spriteSetIndex;
    m_keyframeSets[m_currentSet].m_flags.Mark(k_keyframeSetChanged);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetFPS(size_type a_fps)
  {
    m_keyframeSets[m_currentSet].m_frameDeltaT =
      1.0f / core_utils::CastNumber<tl_float>(a_fps);
  }

  // ///////////////////////////////////////////////////////////////////////
  // explicit instantiations

  // SmartPtr
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(TransformAnimation);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(transform_animation_sptr);

};};};