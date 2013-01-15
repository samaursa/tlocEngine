#ifndef _TLOC_MATH_COMPONENT_SYSTEM_COMPONENT_TYPE_H_
#define _TLOC_MATH_COMPONENT_SYSTEM_COMPONENT_TYPE_H_

#include <tlocMath/tlocMathBase.h>

#include <tlocCore/component_system/tlocComponentType.h>

namespace tloc { namespace math { namespace component_system {

  namespace components
  {
    enum type
    {
      transform = core::component_system::components_group::math,

      count
    }; typedef tl_int value_type;
  };

};};};

#endif