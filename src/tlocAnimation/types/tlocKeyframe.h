#ifndef _TLOC_ANIMATION_TYPES_KEYFRAME_H_
#define _TLOC_ANIMATION_TYPES_KEYFRAME_H_

#include <tlocAnimation/tlocAnimationBase.h>

#include <tlocCore/types/tlocBasicTypes.h>

namespace tloc { namespace animation { namespace types {

  template <typename T>
  class Keyframe
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
    typedef T                       value_type;
    typedef tl_int                  frame_type;

  public:

  private:
    frame_type  m_frame;
    value_type  m_value;

  };

};};};

#endif