#ifndef TLOC_ENTITY_INL
#define TLOC_ENTITY_INL

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/containers/tlocContainers.inl.h>

namespace tloc { namespace core { namespace component_system {

  TL_I Entity::Entity(entity_id a_id)
    : m_id(a_id)
    , m_index(size_type() - 1)
    , m_active(true)
  {
    m_allComponents.resize(components_group::count);
  }

  TL_I bool Entity::HasComponent(component_type a_type) const
  {
    return components_group::count > a_type ?
           m_allComponents[a_type].size() > 0 : false;
  }

  TL_I const Entity::component_list&
    Entity::GetComponents(component_type a_type) const
  {
    TLOC_ASSERT(a_type < (component_type)m_allComponents.size(),
                "Inserting an unsupported component!");
    return m_allComponents[a_type];
  }

  TL_I Entity::component_list&
    Entity::DoGetComponents(component_type a_type)
  {
    TLOC_ASSERT(a_type < (component_type)m_allComponents.size(),
                "Inserting an unsupported component!");
    return m_allComponents[a_type];
  }

  TL_I Entity::entity_id Entity::GetID() const
  {
    return m_id;
  }

  TL_I void Entity::SetID(entity_id a_id)
  {
    m_id = a_id;
  }

  TL_I Entity::size_type Entity::GetIndex() const
  {
    return m_index;
  }

  TL_I void Entity::SetIndex(size_type a_index)
  {
    m_index = a_index;
  }

  TL_I void Entity::InsertComponent(Component* a_component)
  {
    component_type ctype = a_component->GetType();

    TLOC_ASSERT(ctype < (component_type)m_allComponents.size(),
                "Inserting an unsupported component!");
    m_allComponents[ctype].push_back(a_component);
  }

  TL_I Entity::component_list_list&
    Entity::GetComponentsList()
  {
    return m_allComponents;
  }

  TL_I const Entity::component_list_list&
    Entity::GetComponentsList() const
  {
    return m_allComponents;
  }

};};};

#endif