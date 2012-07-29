#include "tlocEntity.h"
#include <tlocCore/containers/tlocContainers.inl>

namespace tloc { namespace core { namespace component_system {

  template class Array<Entity*>;
  template class Array<Entity*, Array_Unordered>;

};};};