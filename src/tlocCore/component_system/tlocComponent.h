#ifndef TLOC_COMPONENT_H
#define TLOC_COMPONENT_H

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/utilities/tlocObjectCounter.h>
#include <tlocCore/utilities/tlocGroupID.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>

namespace tloc { namespace core { namespace component_system {

  //////////////////////////////////////////////////////////////////////////
  // Component

  class Component : private utils::ObjectCounter<Component>
  {
  public:
    typedef components::value_type          component_type;
    typedef utils::ObjectCounter<Component> counter_type;
    typedef counter_type::size_type         counter_size_type;

    Component(component_type a_type) : m_type(a_type) {}


    // TODO: Add Activate() Deactivate() functions
    // virtual void Activate() { }
    // virtual void Deactivate() { };

    TLOC_DECL_AND_DEF_GETTER(component_type, GetType, m_type);
    TLOC_DECL_AND_DEF_GETTER(counter_size_type, GetTotalComponents,
                             counter_type::GetCurrentObjectCount());

  protected:
    component_type m_type;
  };

  //------------------------------------------------------------------------
  // typedefs
  typedef smart_ptr::SharedPtr<Component>       component_sptr;
  typedef smart_ptr::SharedPtr<const Component> component_const_sptr;

  typedef containers::tl_array<Component*>::type      component_ptr_array;
  typedef containers::tl_array<component_sptr>::type  component_sptr_array;

  //////////////////////////////////////////////////////////////////////////
  // Component_T<>

  template <typename T_Component>
  class Component_T : private utils::GroupID<T_Component>,
                      public Component
  {
  public:

    typedef Component                             base_type;
    typedef utils::GroupID<T_Component>           group_id_base_type;

    Component_T(component_type a_type) : Component(a_type) {}

    using group_id_base_type::GetUniqueGroupID;
  };

};};};

#endif