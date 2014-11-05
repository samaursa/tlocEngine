#ifndef TLOC_COMPONENT_TYPE_H
#define TLOC_COMPONENT_TYPE_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocStrongType.h>

namespace tloc { namespace core { namespace component_system {

  namespace component_group
  {
    // Built-in component types. These are (theoretically) the fastest component
    // types. We (will) also allow setting component types dynamically which
    // will have a slight runtime cost.
    enum type
    {
      k_invalid   = -1,
      k_core		  = 0,
      k_math		  ,
      k_graphics  ,
      k_input		  ,
      k_animation ,
      k_physics   ,
      k_sound     ,
      k_ai        ,
      k_user      ,

      k_count
    }; typedef tl_int     value_type;
  };

  namespace components
  {
    enum type
    {
      k_invalid   = component_group::k_invalid,
      k_listener  = 0, // used for callback functionality

      k_count
    }; typedef tl_int     value_type;

  };

};};};

#endif