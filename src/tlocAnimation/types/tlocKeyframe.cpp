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

#define KEYFRAME_SET_TEMPS  typename T
#define KEYFRAME_SET_PARAMS T
#define KEYFRAME_SET_TYPE   typename KeyframeSet_T<KEYFRAME_SET_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    KeyframeSet_T()
    : m_currentSet(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    KeyframeSet_T(const cont_set_type& a_keyframes)
    : m_keyframeSets(a_keyframes)
    , m_currentSet(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <KEYFRAME_SET_TEMPS>
  KEYFRAME_SET_TYPE::size_type
    KeyframeSet_T<KEYFRAME_SET_PARAMS>::
    AddKeyframe(const keyframe_type& a_keyframe, set_index a_setIndex)
  {
    DoResizeSetToAccomodate(a_setIndex);
    m_keyframeSets[a_setIndex]->push_back(a_keyframe);
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