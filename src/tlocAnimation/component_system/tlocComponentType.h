#ifndef _TLOC_ANIMATION_COMPONENT_TYPE_H_
#define _TLOC_ANIMATION_COMPONENT_TYPE_H_

#include <tlocAnimation/tlocAnimationBase.h>

#include <tlocCore/component_system/tlocComponentType.h>

namespace tloc { namespace animation { namespace component_system {

  namespace components
  {
    enum type
    {
      k_transform_animation = core_cs::component_group::k_animation,
      count
    };  typedef tl_int value_type;
  };

};};};

#endif