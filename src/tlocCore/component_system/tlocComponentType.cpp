#include "tlocComponent.h"

namespace tloc { namespace core { namespace component_system {

  namespace detail
  {
    void componentsCheck()
    {
      TLOC_STATIC_ASSERT(components::count <= components_group::math,
        Core_components_count_exceeds_allowed_limit);
    }
  };

};};};