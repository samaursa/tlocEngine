#include "tlocKeyframe.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace animation { namespace types {

  // ///////////////////////////////////////////////////////////////////////
  // Keyframe_T

#define KEYFRAME_TEMPS  typename T
#define KEYFRAME_PARAMS T
#define KEYFRAME_TYPE   typename Keyframe_T<KEYFRAME_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_TEMPS>
  Keyframe_T<KEYFRAME_PARAMS>::
    Keyframe_T()
    : m_frameNumber(0)
    , m_interpolationType(k_linear)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_TEMPS>
  Keyframe_T<KEYFRAME_PARAMS>::
    Keyframe_T(value_type a_value, index_type a_frameNumber,
             interpolation_type a_type = interpolation_type(k_linear))
             : m_value(a_value)
             , m_frameNumber(a_frameNumber)
             , m_interpolationType(a_type)
  { }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class Keyframe_T<f32>;
  template class Keyframe_T<math_t::Vec2f32>;
  template class Keyframe_T<math_t::Vec3f32>;
  template class Keyframe_T<math_t::Vec4f32>;

  template class Keyframe_T<f64>;
  template class Keyframe_T<math_t::Vec2f64>;
  template class Keyframe_T<math_t::Vec3f64>;
  template class Keyframe_T<math_t::Vec4f64>;

  template class Keyframe_T<math_t::Mat2f32>;
  template class Keyframe_T<math_t::Mat3f32>;
  template class Keyframe_T<math_t::Mat4f32>;

  template class Keyframe_T<math_t::Mat2f64>;
  template class Keyframe_T<math_t::Mat3f64>;
  template class Keyframe_T<math_t::Mat4f64>;

  // ///////////////////////////////////////////////////////////////////////
  // KeyframeSet

#define KEYFRAME_SET_TEMPS  typename T_KeyframeType
#define KEYFRAME_SET_PARAMS T_KeyframeType
#define KEYFRAME_SET_TYPE   typename KeyframeSet_T<KEYFRAME_SET_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    KeyframeSet_T()
    : m_currentSet(0)
    , m_currentFrame(0)
    , m_currentKeyframePair(core::MakePair(0, 0))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    KeyframeSet_T(const cont_set_type& a_keyframes)
    : m_keyframeSets(a_keyframes)
    , m_currentFrame(0)
    , m_currentKeyframePair(core::MakePair(0, 0))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  KEYFRAME_SET_TYPE::size_type
    KeyframeSet_T<KEYFRAME_SET_PARAMS>::
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

  template <KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    ModifyKeyframe(const keyframe_type& a_keyframe, size_type a_index,
                   set_index a_setIndex)
  {
    DoResizeSetToAccomodate(a_setIndex);
    (*m_keyframeSets[a_setIndex])[a_index] = a_keyframe;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    ModifyKeyframes(const cont_type& a_coords, set_index a_setIndex)
  {
    DoResizeSetToAccomodate(a_setIndex);
    (*m_keyframeSets[a_setIndex]) = a_coords;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    RemoveKeyframe(size_type a_index, set_index a_setIndex)
  {
    cont_type::iterator itr = m_keyframeSets[a_setIndex]->begin() + a_index;
    m_keyframeSets[a_setIndex]->erase(itr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    ClearKeyframes(set_index a_setIndex)
  {
    m_keyframeSets[a_setIndex]->clear();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  const KEYFRAME_SET_TYPE::keyframe_type&
    KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    GetKeyframe(size_type  a_index, set_index a_setIndex) const
  {
    return (*m_keyframeSets[a_setIndex])[a_index];
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  KEYFRAME_SET_TYPE::cont_type_sptr
    KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    GetKeyframes(set_index a_setIndex) const
  {
    return m_keyframeSets[a_setIndex];
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    NextFrame()
  {
    TLOC_ASSERT(m_keyframeSets.size() > 0, "No keyframes in set");

    ++m_currentFrame;
    if ( (*m_keyframeSets[m_currentSet])[m_currentKeyframePair.second].GetFrame()
         < m_currentFrame)
    {
      m_currentKeyframePair.first = m_currentKeyframePair.second;
      ++m_currentKeyframePair.second;

      if (m_currentKeyframePair.second >= m_keyframeSets.size())
      {
        --m_currentKeyframePair.second;
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    PrevFrame()
  {
    TLOC_ASSERT(m_keyframeSets.size() > 0, "No keyframes in set");

    if (m_currentFrame == 0)
    {
      m_currentKeyframePair.first = 0;
      m_currentKeyframePair.second = 1;

      if ( (*m_keyframeSets[m_currentSet])[m_currentKeyframePair.second].GetFrame()
            == m_keyframeSets.size())
      {
        m_currentKeyframePair.second = 0;
      }
    }
    else
    {
      --m_currentFrame;

      if (m_currentKeyframePair.first > m_currentFrame)
      {
        --m_currentKeyframePair.first;
        --m_currentKeyframePair.second;
      }
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<KEYFRAME_SET_PARAMS>::
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

  template <KEYFRAME_SET_TEMPS>
  const KEYFRAME_SET_TYPE::size_type
    KeyframeSet_T<KEYFRAME_SET_PARAMS>::
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

  template <KEYFRAME_SET_TEMPS>
  void
    KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    DoResizeSetToAccomodate(set_index a_index)
  {
    if (a_index >= m_keyframeSets.size())
    { m_keyframeSets.push_back(cont_type_sptr(new cont_type()) ); }
  }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class KeyframeSet_T<keyframe_f32>;
  template class KeyframeSet_T<keyframe_vec2f32>;
  template class KeyframeSet_T<keyframe_vec3f32>;
  template class KeyframeSet_T<keyframe_vec4f32>;

  template class KeyframeSet_T<keyframe_f64>;
  template class KeyframeSet_T<keyframe_vec2f64>;
  template class KeyframeSet_T<keyframe_vec3f64>;
  template class KeyframeSet_T<keyframe_vec4f64>;

  template class KeyframeSet_T<keyframe_mat2f32>;
  template class KeyframeSet_T<keyframe_mat3f32>;
  template class KeyframeSet_T<keyframe_mat4f32>;

  template class KeyframeSet_T<keyframe_mat2f64>;
  template class KeyframeSet_T<keyframe_mat3f64>;
  template class KeyframeSet_T<keyframe_mat4f64>;

};};};