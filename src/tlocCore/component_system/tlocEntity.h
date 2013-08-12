#ifndef TLOC_ENTITY_H
#define TLOC_ENTITY_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/component_system/tlocComponentMapper.h>

namespace tloc { namespace core { namespace component_system {

  class EntityWorld;
  class EntityManager;

  class Entity
  {
  public:
    friend class EntityManager;

    typedef components::value_type                      component_type;
    typedef core::component_system::
                  component_ptr_array                   component_list;
    typedef containers::tl_array<component_list>::type  component_list_list;
    typedef tl_uint                         entity_id;
    typedef tl_size                         size_type;

    Entity(entity_id  a_id);

    bool                        HasComponent(component_type a_type) const;
    const component_list&       GetComponents(component_type a_type) const;

    template <typename T_ComponentType>
    T_ComponentType*            GetComponent(size_type a_index = 0) const;

    entity_id                   GetID() const;
    size_type                   GetIndex() const;
    const component_list_list&  GetComponentsList() const;

    void                        Activate() const;
    void                        Deactivate() const;
    TLOC_DECL_AND_DEF_GETTER(bool,  IsActive, m_active);

  protected:

    void                        SetID(entity_id a_id);
    void                        SetIndex(size_type a_index);

    component_list&             DoGetComponents(component_type a_type);
    void                        InsertComponent(Component* a_type);

    component_list_list&        GetComponentsList();

  private:

    entity_id           m_id;
    size_type           m_index;
    mutable bool        m_active;
    component_list_list m_allComponents;
  };

  //------------------------------------------------------------------------
  // template definitions

  template <typename T_ComponentType>
  T_ComponentType*
    Entity::GetComponent(size_type a_index) const
  {
    typedef ComponentMapper<T_ComponentType> cmapper;
    cmapper temp = GetComponents(T_ComponentType::k_component_type);
    return temp[a_index];
  }

  //------------------------------------------------------------------------
  // typedef

  TLOC_TYPEDEF_SHARED_PTR(Entity, entity);

  typedef containers::tl_array<Entity*>::type                entity_ptr_array;
  typedef containers::tl_array<entity_sptr>::type            entity_sptr_array;
};};};

///-------------------------------------------------------------------------
/// @note one of the few one of the few inline files we include in the
/// header because of linker issues (because it is not a template) ;)
/// http://www.parashift.com/c++-faq/inline-member-fns.html
///-------------------------------------------------------------------------
#include <tlocCore/component_system/tlocEntity.inl.h>

#endif