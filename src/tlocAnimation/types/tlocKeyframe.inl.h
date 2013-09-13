#ifndef _TLOC_ANIMATION_TYPES_KEYFRAME_INL_
#define _TLOC_ANIMATION_TYPES_KEYFRAME_INL_

#ifndef _TLOC_ANIMATION_TYPES_KEYFRAME_H_
#error "Must include header before including the inline file"
#endif

#include "tlocKeyframe.h"

namespace tloc { namespace animation { namespace types {

  // ///////////////////////////////////////////////////////////////////////
  // Keyframe_T

#define TL_KEYFRAME_TEMPS  typename T
#define TL_KEYFRAME_PARAMS T
#define TL_KEYFRAME_TYPE   typename Keyframe_T<TL_KEYFRAME_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_TEMPS>
  Keyframe_T<TL_KEYFRAME_PARAMS>::
    Keyframe_T()
    : m_frameNumber(0)
    , m_interpolationType(p_keyframe::k_linear)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_TEMPS>
  Keyframe_T<TL_KEYFRAME_PARAMS>::
    Keyframe_T(value_type a_value, index_type a_frameNumber,
    interpolation_type a_type)
    : m_value(a_value)
    , m_frameNumber(a_frameNumber)
    , m_interpolationType(a_type)
  { }

  // ///////////////////////////////////////////////////////////////////////
  // KeyframeSequence_T

#define TL_KEYFRAME_SEQUENCE_TEMPS   typename T_KeyframeType
#define TL_KEYFRAME_SEQUENCE_PARAMS  T_KeyframeType
#define TL_KEYFRAME_SEQUENCE_TYPE    typename KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    KeyframeSequence_T()
    : m_loop(false)
    , m_stopOnLastFrame(true)
    , m_keyframes(new cont_type())
    , m_currentFrame(0)
    , m_totalFrames(0)
    , m_currentPairIndex(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  void
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    AddKeyframe(const keyframe_type& a_keyframe)
  {
    TLOC_ASSERT( (m_keyframes->size() ?
      m_keyframes->back().GetFrame() < a_keyframe.GetFrame() : true),
      "Incoming keyframe has a smaller frame number than the previous keyframe");

    m_keyframes->push_back(a_keyframe);
    m_totalFrames = a_keyframe.GetFrame();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  void
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    RemoveKeyframe(size_type a_index)
  {
    typename cont_type::iterator itr = m_keyframes->begin() + a_index;
    m_keyframes->erase(itr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  bool
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    NextFrame()
  {
    const size_type totalFrames = GetTotalFrames();

    TLOC_ASSERT(m_currentFrame <= totalFrames,
      "m_currentFrame is at an invalid index");

    ++m_currentFrame;
    if (m_currentFrame > totalFrames)
    {
      if (m_loop || m_stopOnLastFrame == false)
      {
        m_currentFrame = 0;
        m_currentPairIndex = 0;
        return true;
      }
      else
      { --m_currentFrame; }
    }
    else
    {
      if (operator[](m_currentPairIndex + 1).GetFrame() <= m_currentFrame)
      {
        ++m_currentPairIndex;
        TLOC_ASSERT(m_currentPairIndex < m_keyframes->size(),
          "m_currentPairIndex is out of bounds");

        if (m_currentPairIndex == m_keyframes->size() - 1)
        { --m_currentPairIndex; }

        return true;
      }
    }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  bool
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    PrevFrame()
  {
    const size_type totalFrames = GetTotalFrames();

    TLOC_ASSERT(m_currentFrame <= totalFrames,
      "m_currentFrame is at an invalid index");

    if (m_currentFrame == 0)
    {
      if (m_loop || m_stopOnLastFrame)
      {
        m_currentFrame = totalFrames;
        m_currentPairIndex = m_keyframes->size() - 2;
        return true;
      }
    }
    else
    {
      --m_currentFrame;

      if (operator[](m_currentPairIndex).GetFrame() > m_currentFrame)
      {
        TLOC_ASSERT(m_currentPairIndex > 0,
          "m_currentPairIndx will go out of bounds");
        --m_currentPairIndex;
        return true;
      }
    }

    return false;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  void
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    SetCurrentFrame(size_type a_frame)
  {
    m_currentFrame = 0;
    m_currentPairIndex = 0;

    for (size_type i = 0; i < a_frame; ++i)
    {
      NextFrame();
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  TL_KEYFRAME_SEQUENCE_TYPE::kf_pair
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    GetKeyframePairAtCurrentFrame()
  {
    return core::MakePair(operator[](m_currentPairIndex),
                          operator[](DoGetSecondIndex()));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  TL_KEYFRAME_SEQUENCE_TYPE::keyframe_type&
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    operator[](size_type a_index)
  {
    return (*m_keyframes)[a_index];
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  const TL_KEYFRAME_SEQUENCE_TYPE::keyframe_type&
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    operator[](size_type a_index) const
  {
    return (*m_keyframes)[a_index];
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  TL_KEYFRAME_SEQUENCE_TYPE::size_type
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    size()
  {
    return m_keyframes->size();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  void
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    clear()
  {
    m_keyframes->clear();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  TL_KEYFRAME_SEQUENCE_TYPE::size_type
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    GetFramesBetweenCurrentPair()
  {
    return GetFramesBetween(m_currentPairIndex, DoGetSecondIndex());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  TL_KEYFRAME_SEQUENCE_TYPE::size_type
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    GetFramesBetween(size_type a_index1, size_type a_index2)
  {
    return operator[](a_index2).GetFrame() - operator[](a_index1).GetFrame();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  TL_KEYFRAME_SEQUENCE_TYPE::size_type
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    DoGetSecondIndex()
  {
    return m_currentPairIndex + 1;
  }

  // -----------------------------------------------------------------------
  // undefine macros
#undef TL_KEYFRAME_TEMPS
#undef TL_KEYFRAME_PARAMS
#undef TL_KEYFRAME_TYPE

#undef TL_KEYFRAME_SEQUENCE_TEMPS
#undef TL_KEYFRAME_SEQUENCE_PARAMS
#undef TL_KEYFRAME_SEQUENCE_TYPE

};};};

#endif