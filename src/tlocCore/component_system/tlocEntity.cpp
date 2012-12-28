#include "tlocEntity.h"
#include "tlocEntity.inl"

#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

namespace tloc { namespace core { namespace component_system {

  template class core::Array<Entity::component_list>;

  template class core::Array<Entity*>;
  template class core::Array<entity_sptr>;
};};};