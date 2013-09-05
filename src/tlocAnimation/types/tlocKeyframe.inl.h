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
    , m_interpolationType(k_linear)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_TEMPS>
  Keyframe_T<TL_KEYFRAME_PARAMS>::
    Keyframe_T(value_type a_value, index_type a_frameNumber,
    interpolation_type a_type = interpolation_type(k_linear))
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
    cont_type::iterator itr = m_keyframes->begin() + a_index;
    m_keyframes->erase(itr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  void
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    NextFrame()
  {
    const size_type totalFrames = GetTotalFrames();

    TLOC_ASSERT(m_currentFrame < totalFrames,
      "m_currentFrame is at an invalid index");

    ++m_currentFrame;
    if (m_currentFrame > totalFrames)
    {
      if (m_loop || m_stopOnLastFrame == false)
      { m_currentFrame = 0; }
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
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  void
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    PrevFrame()
  {
    const size_type totalFrames = GetTotalFrames();

    TLOC_ASSERT(m_currentFrame < totalFrames,
      "m_currentFrame is at an invalid index");

    if (m_currentFrame == 0)
    {
      if (m_loop || m_stopOnLastFrame)
      { m_currentFrame = m_keyframes->size() - 1; }
    }
    else
    {
      --m_currentFrame;

      if (operator[](m_currentPairIndex).GetFrame() > m_currentFrame)
      {
        TLOC_ASSERT(m_currentPairIndex > 0,
          "m_currentPairIndx will go out of bounds");
        --m_currentPairIndex;
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SEQUENCE_TEMPS>
  TL_KEYFRAME_SEQUENCE_TYPE::kf_pair
    KeyframeSequence_T<TL_KEYFRAME_SEQUENCE_PARAMS>::
    GetKeyframePairAtCurrentFrame()
  {
    const size_type secondIndex =
      m_currentPairIndex == m_keyframes->size() - 1 ?
      m_currentPairIndex : m_currentPairIndex + 1;

    return core::MakePair(operator[](m_currentPairIndex),
                          operator[](secondIndex));
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

  // ///////////////////////////////////////////////////////////////////////
  // KeyframeSet

#define TL_KEYFRAME_SET_TEMPS  typename T_KeyframeType
#define TL_KEYFRAME_SET_PARAMS T_KeyframeType
#define TL_KEYFRAME_SET_TYPE   typename KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    KeyframeSet_T()
    : m_currentSet(0)
    , m_currentFrame(0)
    , m_currentKeyframePair(core::MakePair(0, 0))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    KeyframeSet_T(const cont_set_type& a_keyframes)
    : m_keyframeSets(a_keyframes)
    , m_currentFrame(0)
    , m_currentKeyframePair(core::MakePair(0, 0))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  TL_KEYFRAME_SET_TYPE::size_type
    KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    AddKeyframe(const keyframe_type& a_keyframe, set_index a_setIndex)
  {
    DoResizeSetToAccomodate(a_setIndex);
    m_keyframeSets[a_setIndex]->push_back(a_keyframe);

    // we start with the first two keyframes as a pair
    if (m_currentKeyframePair.first == 0 &&
        m_currentKeyframePair.second == 0 &&
        m_keyframeSets[a_setIndex]->size() > 1)
    {
      m_currentKeyframePair = core::MakePair(0, 1);
    }

    return m_keyframeSets.size() - 1;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    ModifyKeyframe(const keyframe_type& a_keyframe, size_type a_index,
                   set_index a_setIndex)
  {
    DoResizeSetToAccomodate(a_setIndex);
    (*m_keyframeSets[a_setIndex])[a_index] = a_keyframe;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    ModifyKeyframes(const cont_type& a_coords, set_index a_setIndex)
  {
    DoResizeSetToAccomodate(a_setIndex);
    (*m_keyframeSets[a_setIndex]) = a_coords;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    RemoveKeyframe(size_type a_index, set_index a_setIndex)
  {
    cont_type::iterator itr = m_keyframeSets[a_setIndex]->begin() + a_index;
    m_keyframeSets[a_setIndex]->erase(itr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    ClearKeyframes(set_index a_setIndex)
  {
    m_keyframeSets[a_setIndex]->clear();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  const TL_KEYFRAME_SET_TYPE::keyframe_type&
    KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    GetKeyframe(size_type  a_index, set_index a_setIndex) const
  {
    return (*m_keyframeSets[a_setIndex])[a_index];
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  TL_KEYFRAME_SET_TYPE::cont_type_sptr
    KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    GetKeyframeSet(set_index a_setIndex) const
  {
    return m_keyframeSets[a_setIndex];
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    NextFrame()
  {
    TLOC_ASSERT(m_keyframeSets.size() > 0, "No keyframes in set");

    ++m_currentFrame;

    const size_type secondKfFrame =
      (*m_keyframeSets[m_currentSet])[m_currentKeyframePair.second].GetFrame();

    if ( secondKfFrame < m_currentFrame)
    {
      m_currentKeyframePair.first = m_currentKeyframePair.second;
      ++m_currentKeyframePair.second;

      if (m_currentKeyframePair.second >= m_keyframeSets[m_currentSet]->size())
      {
        --m_currentKeyframePair.second;
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    PrevFrame()
  {
    TLOC_ASSERT(m_keyframeSets.size() > 0, "No keyframe sets");
    TLOC_ASSERT(m_keyframeSets[m_currentSet]->size() > 0, "No keyframes in set");

    const size_type secondKfFrame =
      (*m_keyframeSets[m_currentSet])[m_currentKeyframePair.second].GetFrame();

    if (m_currentFrame == 0)
    {
      m_currentKeyframePair.first = 0;
      m_currentKeyframePair.second = 1;

      if ( m_currentKeyframePair.second == m_keyframeSets[m_currentSet]->size())
      {
        m_currentKeyframePair.second = 0;
      }
    }
    else
    {
      --m_currentFrame;

      if (secondKfFrame > m_currentFrame)
      {
        --m_currentKeyframePair.first;
        --m_currentKeyframePair.second;
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    SetCurrentFrame(size_type a_currentFrame)
  {
    cont_type::iterator itr     = m_keyframeSets[m_currentSet]->begin(),
                        itrEnd  = m_keyframeSets[m_currentSet]->end();

    size_type counter = 0;
    while (itr != itrEnd)
    {
      keyframe_type& kf = *itr;

      if (kf.GetFrame() <= a_currentFrame)
      {
        if (counter == m_keyframeSets[m_currentSet]->size() - 1)
        {
          m_currentKeyframePair = core::MakePair(counter, counter);
        }
        else
        {
          m_currentKeyframePair = core::MakePair(counter, counter + 1);
        }

        break;
      }

      ++itr;
      ++counter;
    }

    m_currentFrame = a_currentFrame;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  const TL_KEYFRAME_SET_TYPE::size_type
    KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    GetTotalFrames() const
  {
    if (m_keyframeSets.size() > 0 &&
        m_keyframeSets[m_currentSet]->size() > 0)
    {
      return m_keyframeSets[m_currentSet]->back().GetFrame();
    }

    return 0;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  const TL_KEYFRAME_SET_TYPE::size_type
    KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    GetNumFramesCurrKeyframePair() const
  {
    if (m_keyframeSets.size() > 0 &&
        m_keyframeSets[m_currentSet]->size() > m_currentKeyframePair.second)
    {
      return (*m_keyframeSets[m_currentSet])[m_currentKeyframePair.second].GetFrame() -
             (*m_keyframeSets[m_currentSet])[m_currentKeyframePair.first].GetFrame();

    }

    return 0;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TL_KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<TL_KEYFRAME_SET_PARAMS>::
    DoResizeSetToAccomodate(set_index a_index)
  {
    if (a_index >= m_keyframeSets.size())
    { m_keyframeSets.push_back(cont_type_sptr(new cont_type()) ); }
  }

  // -----------------------------------------------------------------------
  // undefine macros
#undef TL_KEYFRAME_TEMPS
#undef TL_KEYFRAME_PARAMS
#undef TL_KEYFRAME_TYPE

#undef KEYFRAME_SEQUENCE_

};};};

#endif