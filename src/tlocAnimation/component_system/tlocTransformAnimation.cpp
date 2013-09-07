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

  TransformAnimation::KeyframeSequenceSetType::
    KeyframeSequenceSetType()
    : m_frameDeltaT(1.0f / 24.0f)
    , m_startTime(0)
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TransformAnimation::KeyframeSequenceSetType::
    KeyframeSequenceSetType(const KeyframeSequenceSetType& a_other)
    : m_kfSeq(a_other.m_kfSeq)
    , m_frameDeltaT(a_other.m_frameDeltaT)
    , m_startTime(a_other.m_startTime)
    , m_flags(a_other.m_flags)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TransformAnimation::KeyframeSequenceSetType::
    KeyframeSequenceSetType(const kf_seq_type& a_keyframes)
    : m_kfSeq(a_keyframes)
    , m_frameDeltaT(1.0f / 24.0f)
    , m_startTime(0)
    , m_flags(k_count)
  { }

  // ///////////////////////////////////////////////////////////////////////
  // TextureAnimation

  TransformAnimation::
    TransformAnimation()
    : base_type(k_component_type)
    , m_currentSeq(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    AddKeyframeSet(const kf_seq_type& a_keyframe)
  {
    m_kfSeqSet.push_back(KeyframeSequenceSetType(a_keyframe));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    ModifyKeyframeSet(const kf_seq_type& a_keyframe, size_type a_index)
  {
    m_kfSeqSet[a_index] = KeyframeSequenceSetType(a_keyframe);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    RemoveKeyframeSet(size_type a_index)
  {
    cont_type::iterator itr = m_kfSeqSet.begin();
    core::advance(itr, a_index);
    m_kfSeqSet.erase(itr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TransformAnimation::kf_seq_type&
    TransformAnimation::
    GetKeyframeSequence(size_type a_index)
  {
    return m_kfSeqSet[a_index].m_kfSeq;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const TransformAnimation::kf_seq_type&
    TransformAnimation::
    GetKeyframeSequence(size_type a_index) const
  {
    return m_kfSeqSet[a_index].m_kfSeq;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    NextFrame()
  {
    m_kfSeqSet[m_currentSeq].m_kfSeq.NextFrame();
    m_kfSeqSet[m_currentSeq].m_flags.Mark(k_keyframeSetChanged);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    PrevFrame()
  {
    m_kfSeqSet[m_currentSeq].m_kfSeq.PrevFrame();
    m_kfSeqSet[m_currentSeq].m_flags.Mark(k_keyframeSetChanged);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetFrame(size_type a_index)
  {
    m_kfSeqSet[m_currentSeq].m_kfSeq.SetCurrentFrame(a_index);
    m_kfSeqSet[m_currentSeq].m_flags.Mark(k_keyframeSetChanged);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const bool
    TransformAnimation::
    IsLooping() const
  { return m_kfSeqSet[m_currentSeq].m_flags.IsMarked(k_looping); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const bool
    TransformAnimation::
    IsPaused() const
  { return m_kfSeqSet[m_currentSeq].m_flags.IsMarked(k_paused); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const bool
    TransformAnimation::
    IsStopped() const
  { return m_kfSeqSet[m_currentSeq].m_flags.IsMarked(k_stopped); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const bool
    TransformAnimation::
    IsTransformSetChanged() const
  { return m_kfSeqSet[m_currentSeq].m_flags.IsMarked(k_keyframeSetChanged); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const TransformAnimation::size_type
    TransformAnimation::
    GetFPS() const
  { return static_cast<size_type>(1.0f / m_kfSeqSet[m_currentSeq].m_frameDeltaT); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetLooping(bool a_looping)
  {
    m_kfSeqSet[m_currentSeq].m_flags[k_looping] = a_looping;
    m_kfSeqSet[m_currentSeq].m_kfSeq.Loop(a_looping);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetPaused(bool a_pause)
  { m_kfSeqSet[m_currentSeq].m_flags[k_paused] = a_pause; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetStopped(bool a_stop)
  {
    m_kfSeqSet[m_currentSeq].m_flags[k_stopped] = a_stop;
    if (a_stop)
    { SetFrame(0); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetTransformSetChanged(bool a_changed)
  { m_kfSeqSet[m_currentSeq].m_flags[k_keyframeSetChanged] = a_changed; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetCurrentTransformSet(size_type a_spriteSetIndex)
  {
    TLOC_ASSERT(a_spriteSetIndex < GetNumSequences(), "Index out of bounds!");
    m_currentSeq = a_spriteSetIndex;
    m_kfSeqSet[m_currentSeq].m_flags.Mark(k_keyframeSetChanged);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetFPS(size_type a_fps)
  {
    m_kfSeqSet[m_currentSeq].m_frameDeltaT =
      1.0f / core_utils::CastNumber<tl_float>(a_fps);
  }

  // ///////////////////////////////////////////////////////////////////////
  // explicit instantiations

  // SmartPtr
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(TransformAnimation);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(transform_animation_sptr);

};};};