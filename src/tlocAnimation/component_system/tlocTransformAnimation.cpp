#include "tlocTransformAnimation.h"

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace animation { namespace component_system {

  namespace {

    enum
    {
      k_looping,
      k_paused,
      k_stopped,
      k_reverse,
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
    , m_totalTime(0)
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TransformAnimation::KeyframeSequenceSetType::
    KeyframeSequenceSetType(const KeyframeSequenceSetType& a_other)
    : m_kfSeq(a_other.m_kfSeq)
    , m_frameDeltaT(a_other.m_frameDeltaT)
    , m_startTime(a_other.m_startTime)
    , m_totalTime(a_other.m_totalTime)
    , m_flags(a_other.m_flags)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TransformAnimation::KeyframeSequenceSetType::
    KeyframeSequenceSetType(const kf_seq_type& a_keyframes)
    : m_kfSeq(a_keyframes)
    , m_frameDeltaT(1.0f / 24.0f)
    , m_startTime(0)
    , m_totalTime(0)
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

  TransformAnimation::kf_seq_type&
    TransformAnimation::
    GetCurrentKeyframeSequence()
  {
    return m_kfSeqSet[GetCurrentKeyframeSequenceIndex()].m_kfSeq;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const TransformAnimation::kf_seq_type&
    TransformAnimation::
    GetCurrentKeyframeSequence() const
  {
    return m_kfSeqSet[GetCurrentKeyframeSequenceIndex()].m_kfSeq;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    NextFrame()
  {
    bool updated = false;

    if (m_kfSeqSet[m_currentSeq].m_flags.IsUnMarked(k_reverse))
    { updated = m_kfSeqSet[m_currentSeq].m_kfSeq.NextFrame(); }
    else
    { updated = m_kfSeqSet[m_currentSeq].m_kfSeq.PrevFrame(); }

    if (updated)
    { m_kfSeqSet[m_currentSeq].m_flags.Mark(k_keyframeSetChanged); }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    PrevFrame()
  {
    bool updated = false;

    if (m_kfSeqSet[m_currentSeq].m_flags.IsUnMarked(k_reverse))
    { updated = m_kfSeqSet[m_currentSeq].m_kfSeq.PrevFrame(); }
    else
    { updated = m_kfSeqSet[m_currentSeq].m_kfSeq.NextFrame(); }

    if (updated)
    { m_kfSeqSet[m_currentSeq].m_flags.Mark(k_keyframeSetChanged); }
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

  void
    TransformAnimation::
    GotoBegin()
  {
    if (m_kfSeqSet[m_currentSeq].m_flags.IsMarked(k_reverse) == false)
    {
      m_kfSeqSet[m_currentSeq].m_kfSeq.GotoBegin();
    }
    else
    {
      m_kfSeqSet[m_currentSeq].m_kfSeq.GotoEnd();
    }

    m_kfSeqSet[m_currentSeq].m_flags.Mark(k_keyframeSetChanged);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    GotoEnd()
  {
    if (m_kfSeqSet[m_currentSeq].m_flags.IsMarked(k_reverse) == false)
    {
      m_kfSeqSet[m_currentSeq].m_kfSeq.GotoEnd();
    }
    else
    {
      m_kfSeqSet[m_currentSeq].m_kfSeq.GotoBegin();
    }

    m_kfSeqSet[m_currentSeq].m_flags.Mark(k_keyframeSetChanged);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    TransformAnimation::
    IsLooping() const
  { return m_kfSeqSet[m_currentSeq].m_flags.IsMarked(k_looping); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    TransformAnimation::
    IsPaused() const
  { return m_kfSeqSet[m_currentSeq].m_flags.IsMarked(k_paused); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    TransformAnimation::
    IsStopped() const
  { return m_kfSeqSet[m_currentSeq].m_flags.IsMarked(k_stopped); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    TransformAnimation::
    IsReversed() const
  { return m_kfSeqSet[m_currentSeq].m_flags.IsMarked(k_reverse); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    TransformAnimation::
    IsKFSequenceChanged() const
  { return m_kfSeqSet[m_currentSeq].m_flags.IsMarked(k_keyframeSetChanged); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  TransformAnimation::size_type
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
    SetReverse(bool a_reverse)
  {
    m_kfSeqSet[m_currentSeq].m_flags[k_reverse] = a_reverse;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetKFSequenceChanged(bool a_changed)
  { m_kfSeqSet[m_currentSeq].m_flags[k_keyframeSetChanged] = a_changed; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    TransformAnimation::
    SetCurrentKFSequence(size_type a_spriteSetIndex)
  {
    TLOC_ASSERT(a_spriteSetIndex < GetTotalKeyframeSequences(), "Index out of bounds!");
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

};};};

// ///////////////////////////////////////////////////////////////////////
// explicit instantiations

using namespace tloc::anim_cs;

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(TransformAnimation);
TLOC_EXPLICITLY_INSTANTIATE_UNIQUE_PTR(TransformAnimation);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(TransformAnimation);