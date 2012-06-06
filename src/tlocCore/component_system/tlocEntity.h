#ifndef TLOC_ENTITY_H
#define TLOC_ENTITY_H

namespace tloc { namespace core {

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentType.h>

  class EntityWorld;
  class EntityManager;

  class Entity
  {
  public:
    typedef tl_array<Component*>::type      component_list;
    typedef tl_array<component_list>::type  component_list_list;
    typedef tl_uint                         entity_id;

    Entity(entity_id  a_id);

    bool                        HasComponent(component_type  a_type);
    const component_list&       GetComponents(component_type a_type) const;

  protected:
    entity_id           m_id;
    tl_uint             m_index;
    component_list_list m_allComponents;
  };

};};

#endif