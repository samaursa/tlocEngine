#include "tlocEntity.h"
#include "tlocEntity.inl"

#include <tlocCore/containers/tlocContainers.inl>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

namespace tloc { namespace core { namespace component_system {

  template class containers::ArrayBase<Entity::component_list>;
  template class containers::Array<Entity::component_list>;

  template class containers::ArrayBase<Entity*>;
  template class containers::Array<Entity*>;

  template class containers::ArrayBase<entity_sptr>;
  template class containers::Array<entity_sptr>;
};};};