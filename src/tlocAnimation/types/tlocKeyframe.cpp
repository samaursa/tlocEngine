#include "tlocKeyframe.h"
#include "tlocKeyframe.inl.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace animation { namespace types {

  // -----------------------------------------------------------------------
  // explicit instantiations

#define TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(_type_)\
  template class Keyframe_T<_type_>;\
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR( core_conts::Array<Keyframe_T<_type_> >)

  // -----------------------------------------------------------------------
  // Keyframe_T explicit instantiations

  using namespace math_t;

  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(f32);
  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(Vec2f32);
  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(Vec3f32);
  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(Vec4f32);

  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(f64);
  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(Vec2f64);
  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(Vec3f64);
  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(Vec4f64);

  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(Mat2f32);
  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(Mat3f32);
  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(Mat4f32);

  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(Mat2f64);
  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(Mat3f64);
  TLOC_EXPLICITLY_INSTANTIATE_KEYFRAME_T(Mat4f64);

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

};};};