#include "tlocKeyframe.h"
#include "tlocKeyframe.inl.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace animation { namespace types {

  // -----------------------------------------------------------------------
  // Keyframe_T explicit instantiations

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

  // -----------------------------------------------------------------------
  // KeyframeSequence_T explicit instantiations

  template class KeyframeSequence_T<keyframe_f32>;
  template class KeyframeSequence_T<keyframe_vec2f32>;
  template class KeyframeSequence_T<keyframe_vec3f32>;
  template class KeyframeSequence_T<keyframe_vec4f32>;

  template class KeyframeSequence_T<keyframe_f64>;
  template class KeyframeSequence_T<keyframe_vec2f64>;
  template class KeyframeSequence_T<keyframe_vec3f64>;
  template class KeyframeSequence_T<keyframe_vec4f64>;

  template class KeyframeSequence_T<keyframe_mat2f32>;
  template class KeyframeSequence_T<keyframe_mat3f32>;
  template class KeyframeSequence_T<keyframe_mat4f32>;

  template class KeyframeSequence_T<keyframe_mat2f64>;
  template class KeyframeSequence_T<keyframe_mat3f64>;
  template class KeyframeSequence_T<keyframe_mat4f64>;

  // -----------------------------------------------------------------------
  // KeyframeSet_T explicit instantiations

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