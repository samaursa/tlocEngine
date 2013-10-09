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

  namespace p_keyframe
  {
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
  };

  template <typename T>
  class Keyframe_T
  {
  public:
    typedef T                                     value_type;
    typedef tl_size                               index_type;
    typedef core_t::StrongType_T<index_type, 0>   interpolation_type;
    typedef core_t::StrongType_T<index_type, 1>   relative_frame_number;

  public:
    Keyframe_T();

    Keyframe_T(value_type a_value, index_type a_frameNumber,
             interpolation_type a_type = interpolation_type(p_keyframe::k_linear));

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(value_type, GetValue, m_value);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(index_type, GetFrame, m_frameNumber);
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT
      (index_type, GetInterpolationType, m_interpolationType);

    TLOC_DECL_AND_DEF_SETTER(value_type, SetValue, m_value);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(index_type, SetFrame, m_frameNumber);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(index_type, SetInterpolationType,
                                      m_interpolationType);

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
  // KeyframeSequence_T

  template <typename T_KeyframeType>
  class KeyframeSequence_T
  {
  public:
    typedef T_KeyframeType                              keyframe_type;
    typedef KeyframeSequence_T<keyframe_type>           this_type;

    typedef typename
            core_conts::tl_array<keyframe_type>::type   cont_type;
    typedef typename cont_type::iterator                iterator;
    typedef typename cont_type::const_iterator          const_iterator;
    typedef core_sptr::SharedPtr<cont_type>             cont_type_sptr;

    typedef tl_size                                     size_type;
    typedef core::Pair<keyframe_type,
                       keyframe_type>                   kf_pair;

    typedef core_t::StrongType_T<bool, 0>               loop;

  public:
    KeyframeSequence_T();
    template <typename T_KeyframeContainer>
    explicit KeyframeSequence_T(const T_KeyframeContainer& a_sequence);

    void      AddKeyframe(const keyframe_type& a_keyframe);

    template <typename T_KeyframeContainer>
    void      AddKeyframes(const T_KeyframeContainer& a_sequence);

    void      RemoveKeyframe(size_type a_index);

    // returns true if a frame change occurs
    bool      NextFrame();
    bool      PrevFrame();
    void      SetCurrentFrame(size_type a_frame);

    kf_pair   GetKeyframePairAtCurrentFrame();

    // standard container methods that are exposed
    keyframe_type&        operator[](size_type a_index);
    const keyframe_type&  operator[](size_type a_index) const;
    void                  clear();
    size_type             size();

    size_type             GetFramesBetweenCurrentPair();
    size_type             GetFramesBetween(size_type a_index1, size_type a_index2);

    TLOC_DECL_AND_DEF_GETTER(size_type, GetCurrentFrame, m_currentFrame);
    TLOC_DECL_AND_DEF_GETTER(size_type, GetTotalFrames, m_totalFrames);

    TLOC_DECL_PARAM_VAR(bool, Loop, m_loop);
    TLOC_DECL_PARAM_VAR(bool, StopOnLastFrame, m_stopOnLastFrame);

  private:
    size_type       DoGetSecondIndex();

  private:
    cont_type_sptr  m_keyframes;
    size_type       m_currentFrame;
    size_type       m_totalFrames;
    size_type       m_currentPairIndex;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_KeyframeType>
  template <typename T_KeyframeContainer>
  KeyframeSequence_T<T_KeyframeType>::
    KeyframeSequence_T(const T_KeyframeContainer& a_sequence)
    : m_loop(false)
    , m_stopOnLastFrame(true)
    , m_keyframes(new cont_type())
    , m_currentFrame(0)
    , m_totalFrames(0)
    , m_currentPairIndex(0)
  {
    type_traits::AssertTypeIsSupported
      <typename T_KeyframeContainer::value_type,
       keyframe_type>();

    m_keyframes->resize(a_sequence.size());
    core::copy_all(a_sequence, m_keyframes->begin());
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_KeyframeType>
  template <typename T_KeyframeContainer>
  void
    KeyframeSequence_T<T_KeyframeType>::
    AddKeyframes(const T_KeyframeContainer& a_sequence)
  {
    type_traits::AssertTypeIsSupported
      <typename T_KeyframeContainer::value_type,
       keyframe_type>();

    typename T_KeyframeContainer::const_iterator itr = a_sequence.begin(),
                                                 itrEnd = a_sequence.end();

    for (; itr != itrEnd; ++itr)
    {
      m_keyframes->push_back(*itr);
    }
  }

  // -----------------------------------------------------------------------
  // typedefs

  typedef KeyframeSequence_T<keyframe_f32>           keyframe_sequence_f32;
  typedef KeyframeSequence_T<keyframe_vec2f32>       keyframe_sequence_vec2f32;
  typedef KeyframeSequence_T<keyframe_vec3f32>       keyframe_sequence_vec3f32;
  typedef KeyframeSequence_T<keyframe_vec4f32>       keyframe_sequence_vec4f32;

  typedef KeyframeSequence_T<keyframe_f64>           keyframe_sequence_f64;
  typedef KeyframeSequence_T<keyframe_vec2f64>       keyframe_sequence_vec2f64;
  typedef KeyframeSequence_T<keyframe_vec3f64>       keyframe_sequence_vec3f64;
  typedef KeyframeSequence_T<keyframe_vec4f64>       keyframe_sequence_vec4f64;

  typedef KeyframeSequence_T<keyframe_mat2f32>       keyframe_sequence_mat2f32;
  typedef KeyframeSequence_T<keyframe_mat3f32>       keyframe_sequence_mat3f32;
  typedef KeyframeSequence_T<keyframe_mat4f32>       keyframe_sequence_mat4f32;

  typedef KeyframeSequence_T<keyframe_mat2f64>       keyframe_sequence_mat2f64;
  typedef KeyframeSequence_T<keyframe_mat3f64>       keyframe_sequence_mat3f64;
  typedef KeyframeSequence_T<keyframe_mat4f64>       keyframe_sequence_mat4f64;

};};};

#endif