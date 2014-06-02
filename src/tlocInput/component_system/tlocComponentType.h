#pragma once
#ifndef _TLOC_INPUT_COMPONENT_SYSTEM_COMPONENT_TYPE_H_
#define _TLOC_INPUT_COMPONENT_SYSTEM_COMPONENT_TYPE_H_

#include <tlocInput/tlocInputBase.h>

#include <tlocInput/component_system/tlocComponentType.h>

namespace tloc { namespace input { namespace component_system {

  namespace components
  {
    enum type
    {
      k_arcball_control = core::component_system::components_group::input,

      count
    }; typedef tl_int value_type;
  };

};};};

#endif
