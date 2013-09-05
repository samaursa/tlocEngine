#ifndef _TLOC_ANIMATION_TYPES_KEYFRAME_H_
#define _TLOC_ANIMATION_TYPES_KEYFRAME_H_

#include <tlocAnimation/tlocAnimationBase.h>

#include <tlocCore/types/tlocBasicTypes.h>
#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/containers/tloc_containers.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocMath/types/tlocVector2.h>
#include <tlocMath/types/tlocVector3.h>
#include <tlocMath/types/tlocVector4.h>

#include <tlocMath/types/tlocMatrix2.h>
#include <tlocMath/types/tlocMatrix3.h>
#include <tlocMath/types/tlocMatrix4.h>

namespace tloc { namespace animation { namespace types {

  // ///////////////////////////////////////////////////////////////////////
  // Keyframe

  template <typename T>
  class Keyframe_T
  {
  public:
    enum
    {
      k_linear,
      k_ease_in_cubic,
      k_ease_out_cubic,
      k_ease_in_out_cubic,
      k_ease_in_quadratic,
      k_ease_out_quadratic,
      k_ease_in_out_quadratic,
      k_ease_in_sin,
      k_ease_out_sin,
      k_ease_in_out_sin,

      k_count
    };

  public:
    typedef T                                     value_type;
    typedef tl_size                               index_type;
    typedef core_t::StrongType_T<index_type, 0>   interpolation_type;

  public:
    Keyframe_T();

    Keyframe_T(value_type a_value, index_type a_frameNumber,
             interpolation_type a_type = interpolation_type(k_linear));

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(value_type, GetValue, m_value);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(index_type, GetFrame, m_frameNumber);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (index_type, GetInterpolationType, m_interpolationType);

  private:
    value_type  m_value;
    index_type  m_frameNumber;
    index_type  m_interpolationType;

  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef Keyframe_T<f32>                       keyframe_f32;
  typedef Keyframe_T<math_t::Vec2f32>           keyframe_vec2f32;
  typedef Keyframe_T<math_t::Vec3f32>           keyframe_vec3f32;
  typedef Keyframe_T<math_t::Vec4f32>           keyframe_vec4f32;

  typedef Keyframe_T<f64>                       keyframe_f64;
  typedef Keyframe_T<math_t::Vec2f64>           keyframe_vec2f64;
  typedef Keyframe_T<math_t::Vec3f64>           keyframe_vec3f64;
  typedef Keyframe_T<math_t::Vec4f64>           keyframe_vec4f64;

  typedef Keyframe_T<math_t::Mat2f32>           keyframe_mat2f32;
  typedef Keyframe_T<math_t::Mat3f32>           keyframe_mat3f32;
  typedef Keyframe_T<math_t::Mat4f32>           keyframe_mat4f32;

  typedef Keyframe_T<math_t::Mat2f64>           keyframe_mat2f64;
  typedef Keyframe_T<math_t::Mat3f64>           keyframe_mat3f64;
  typedef Keyframe_T<math_t::Mat4f64>           keyframe_mat4f64;

  // ///////////////////////////////////////////////////////////////////////
  // KeyframeSet

  template <typename T_KeyframeType>
  class KeyframeSet_T
  {
  public:
    typedef T_KeyframeType                              keyframe_type;
    typedef KeyframeSet_T<keyframe_type>                value_type;
    typedef typename
            core_conts::tl_array<keyframe_type>::type   cont_type;
    typedef core_sptr::SharedPtr<cont_type>             cont_type_sptr;
    typedef typename
            core_conts::tl_array<cont_type_sptr>::type  cont_set_type;
    typedef tl_size                                     size_type;

    typedef core_t::StrongType_T<size_type, 0>          set_index;
    typedef core::Pair<size_type, size_type>            index_pair;

  public:
    KeyframeSet_T();
    explicit KeyframeSet_T(const cont_set_type& a_keyframes);

    size_type AddKeyframe(const keyframe_type& a_keyframe,
                          set_index a_setIndex = set_index(0));

    void      ModifyKeyframe(const keyframe_type& a_keyframe, size_type a_index,
                             set_index a_setIndex = set_index(0));
    void      ModifyKeyframes(const cont_type& a_coords,
                              set_index a_setIndex = set_index(0));
    void      RemoveKeyframe(size_type a_index,
                             set_index a_setIndex = set_index(0));
    void      ClearKeyframes(set_index a_setIndex = set_index(0));

    const keyframe_type& GetKeyframe(size_type a_index,
                                     set_index a_setIndex = set_index(0)) const;
    cont_type_sptr GetKeyframes(set_index a_setIndex = set_index(0)) const;

    void      NextFrame();
    void      PrevFrame();

    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumSets, m_keyframeSets.size());
    TLOC_DECL_AND_DEF_GETTER(size_type, GetCurrentKeyframeSet, m_currentSet);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetCurrentFrame, m_currentFrame);
    TLOC_DECL_GETTER(size_type, GetTotalFrames);
    TLOC_DECL_GETTER(size_type, GetNumFramesCurrKeyframePair);
    TLOC_DECL_AND_DEF_GETTER(index_pair, GetCurrentKeyframePair, m_currentKeyframePair);

    TLOC_DECL_SETTER_BY_VALUE(size_type, SetCurrentFrame);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(size_type, SetCurrentKeyframeSet, m_currentSet);

  private:
    void      DoResizeSetToAccomodate(set_index a_index);

  private:
    cont_set_type   m_keyframeSets;
    size_type       m_currentSet;
    size_type       m_currentFrame;
    index_pair      m_currentKeyframePair;

  };

  // -----------------------------------------------------------------------
  // typedefs

  typedef KeyframeSet_T<keyframe_f32>           keyframe_set_f32;
  typedef KeyframeSet_T<keyframe_vec2f32>       keyframe_set_vec2f32;
  typedef KeyframeSet_T<keyframe_vec3f32>       keyframe_set_vec3f32;
  typedef KeyframeSet_T<keyframe_vec4f32>       keyframe_set_vec4f32;

  typedef KeyframeSet_T<keyframe_f64>           keyframe_set_f64;
  typedef KeyframeSet_T<keyframe_vec2f64>       keyframe_set_vec2f64;
  typedef KeyframeSet_T<keyframe_vec3f64>       keyframe_set_vec3f64;
  typedef KeyframeSet_T<keyframe_vec4f64>       keyframe_set_vec4f64;

  typedef KeyframeSet_T<keyframe_mat2f32>       keyframe_set_mat2f32;
  typedef KeyframeSet_T<keyframe_mat3f32>       keyframe_set_mat3f32;
  typedef KeyframeSet_T<keyframe_mat4f32>       keyframe_set_mat4f32;

  typedef KeyframeSet_T<keyframe_mat2f64>       keyframe_set_mat2f64;
  typedef KeyframeSet_T<keyframe_mat3f64>       keyframe_set_mat3f64;
  typedef KeyframeSet_T<keyframe_mat4f64>       keyframe_set_mat4f64;

};};};

#endif