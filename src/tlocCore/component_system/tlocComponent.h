#ifndef TLOC_COMPONENT_H
#define TLOC_COMPONENT_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/utilities/tlocObjectCounter.h>
#include <tlocCore/utilities/tlocGroupID.h>

namespace tloc { namespace core { namespace component_system {

  //////////////////////////////////////////////////////////////////////////
  // Component

  // This setter should be used in components or SetUpdateRequired() must be
  // called manually
#define TLOC_DECL_AND_DEF_COMPONENT_SETTER(_type_, _name_, _var_)\
  TLOC_DECL_SETTER(_type_, _name_) { SetUpdateRequired(true); _var_ = a_in; }

  class Component : private utils::ObjectCounter<Component>
  {
  public:
    typedef Component                       this_type;
    typedef components::value_type          component_type;
    typedef utils::ObjectCounter<Component> counter_type;
    typedef counter_type::size_type         counter_size_type;

    Component()
      : m_type(components_group::invalid)
      , m_updateRequired()
      , m_enabled(false)
    { }

    explicit Component(component_type a_type)
      : m_type(a_type)
      , m_updateRequired(true)
      , m_enabled(true)
    { }

    explicit Component(const this_type& a_other)
      : m_type(a_other.m_type)
      , m_updateRequired(a_other.m_updateRequired)
      , m_enabled(a_other.m_enabled)
    { }

    bool operator==(const this_type& a_other) const
    {
      return m_type == a_other.m_type &&
             m_updateRequired == a_other.m_updateRequired &&
             m_enabled == a_other.m_enabled;
    }

    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

    TLOC_DECL_AND_DEF_GETTER(component_type, GetType, m_type);
    TLOC_DECL_AND_DEF_GETTER(bool, IsUpdateRequired, m_updateRequired);
    TLOC_DECL_AND_DEF_GETTER(counter_size_type, GetTotalComponents,
                             counter_type::GetCurrentObjectCount());
    TLOC_DECL_AND_DEF_GETTER(bool, IsEnabled, m_enabled);

    TLOC_DECL_AND_DEF_SETTER(bool, SetUpdateRequired, m_updateRequired);

  protected:
    // Only EntityManager is allowed to change this
    TLOC_DECL_AND_DEF_SETTER(bool, SetEnabled, m_enabled);

  protected:
    component_type m_type;
    bool           m_updateRequired;
    bool           m_enabled;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(Component, component);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Component, component);

  typedef containers::tl_array<component_vptr>::type  component_ptr_array;

  //////////////////////////////////////////////////////////////////////////
  // Component_T<>

  template <typename T_Component, tl_int T_ComponentType>
  class Component_T : private utils::GroupID<T_Component>,
                      public Component
  {
  public:
    enum { k_component_type = T_ComponentType };

  public:
    typedef Component                             base_type;
    typedef utils::GroupID<T_Component>           group_id_base_type;

    Component_T(component_type a_type) : Component(a_type) {}

    using group_id_base_type::GetUniqueGroupID;
  };

};};};

#endif