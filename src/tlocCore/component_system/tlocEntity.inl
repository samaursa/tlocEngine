#ifndef TLOC_ENTITY_INL 
#define TLOC_ENTITY_INL 

#ifndef TLOC_ENTITY_H 
#error "Must include header before including the inline file"
#endif

#include "tlocEntity.h"

namespace tloc { namespace core { namespace component_system {

  Entity::Entity(entity_id a_id)
    : m_id(a_id)
  {
    m_allComponents.resize(components::count);
  }

  bool Entity::HasComponent(component_type a_type)
  {
    return m_allComponents[a_type].size() > 0;
  }

  const Entity::component_list&
    Entity::GetComponents(component_type a_type)
  {
    return m_allComponents[a_type];
  }
    
};};};