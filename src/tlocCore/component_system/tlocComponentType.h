#ifndef TLOC_COMPONENT_TYPE_H
#define TLOC_COMPONENT_TYPE_H

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocTypes.h>

namespace tloc { namespace core { namespace component_system {

  namespace components_group
  {
    // Built-in component types. These are (theoretically) the fastest component
    // types. We (will) also allow setting component types dynamically which
    // will have a slight runtime cost.
    enum type
    {
      core		 = 0,
      math		 = 20,
      graphics = 40,
      input		 = 60,
      physics  = 80,
      sound    = 100,
      ai       = 120,

      count    = 140
    };
  };

  namespace components
  {
    // the component type (used for indexing)
    typedef tl_int value_type;

    enum type
    {
      listener= components_group::core, // used for callback functionality

      count
    };

    namespace detail
    {
      void componentsCheck();
    };
  };

};};};

#endif