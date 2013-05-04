#ifndef TLOC_COMPONENT_H
#define TLOC_COMPONENT_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/utilities/tlocObjectCounter.h>
#include <tlocCore/utilities/tlocGroupID.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>

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
    typedef components::value_type          component_type;
    typedef utils::ObjectCounter<Component> counter_type;
    typedef counter_type::size_type         counter_size_type;

    explicit Component(component_type a_type)
      : m_type(a_type)
      , m_updateRequired(true)
      , m_enabled(true)
    { }

    TLOC_DECL_AND_DEF_GETTER(component_type, GetType, m_type);
    TLOC_DECL_AND_DEF_GETTER(bool, GetUpdateRequired, m_updateRequired);
    TLOC_DECL_AND_DEF_GETTER(counter_size_type, GetTotalComponents,
                             counter_type::GetCurrentObjectCount());
    TLOC_DECL_AND_DEF_GETTER(bool, GetEnabled, m_enabled);

    TLOC_DECL_AND_DEF_SETTER(bool, SetUpdateRequired, m_updateRequired);
    TLOC_DECL_AND_DEF_SETTER(bool, SetEnabled, m_enabled);

  protected:
    component_type m_type;
    bool           m_updateRequired;
    bool           m_enabled;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(Component, component);

  typedef containers::tl_array<Component*>::type      component_ptr_array;
  typedef containers::tl_array<component_sptr>::type  component_sptr_array;

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