#ifndef _TLOC_ANIMATION_COMPONENT_TYPE_H_
#define _TLOC_ANIMATION_COMPONENT_TYPE_H_

#include <tlocAnimation/tlocAnimationBase.h>

#include <tlocCore/component_system/tlocComponentType.h>

namespace tloc { namespace animation { namespace component_system {

  namespace components
  {
    enum type
    {
      transform_animation = core::component_system::component_group::animation,
      count
    };  typedef tl_int value_type;
  };

};};};

#endif