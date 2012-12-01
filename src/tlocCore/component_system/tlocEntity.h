#ifndef TLOC_ENTITY_H
#define TLOC_ENTITY_H

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/component_system/tlocComponentType.h>

namespace tloc { namespace core { namespace component_system {

  class EntityWorld;
  class EntityManager;
  class Component;

  class Entity
  {
  public:
    friend class EntityManager;

    typedef components::value_type          component_type;
    typedef tl_array<Component*>::type      component_list;
    typedef tl_array<component_list>::type  component_list_list;
    typedef tl_uint                         entity_id;
    typedef tl_size                         size_type;

    Entity(entity_id  a_id);

    bool                        HasComponent(component_type a_type) const;
    const component_list&       GetComponents(component_type a_type) const;

    entity_id                   GetID() const;
    size_type                   GetIndex() const;
    const component_list_list&  GetComponentsList() const;

  protected:

    void                  SetID(entity_id a_id);
    void                  SetIndex(size_type a_index);

    component_list&       GetComponents(component_type a_type);
    void                  InsertComponent(Component* a_type);

    component_list_list&        GetComponentsList();

  private:

    entity_id           m_id;
    size_type           m_index;
    component_list_list m_allComponents;
  };

  typedef tl_array<Entity*>::type                              entity_array;
  typedef tl_array<Entity*, core::Array_Unordered>::type       entity_array_o;

};};};

#endif