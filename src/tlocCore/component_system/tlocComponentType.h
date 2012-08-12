#ifndef TLOC_COMPONENT_TYPE_H
#define TLOC_COMPONENT_TYPE_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>

namespace tloc { namespace core { namespace component_system {

  namespace components
  {
    // Built-in component types. These are (theoretically) the fastest component
    // types. We (will) also allow setting component types dynamically which
    // will have a slight runtime cost.
    enum type
    {
      transform = 0,
      mesh,

      count
    }; typedef tl_int value_type;
  };

};};};

#endif