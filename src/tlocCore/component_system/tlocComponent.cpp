#include "tlocComponent.h"
#include "tlocComponent.inl.h"

namespace tloc { namespace core { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // Component::Info

  Component::Info::
    Info()
    : m_groupIndex(component_group::k_invalid)
    , m_type(component_group::k_invalid)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Component::Info::
    IsValid() const
  {
    return m_groupIndex < component_group::k_count &&
           m_groupIndex != component_group::k_invalid &&
           m_type != components::k_invalid;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Component::Info::
    operator==(const this_type& a_other) const
  { 
    return m_groupIndex == a_other.m_groupIndex &&
           m_type == a_other.m_type;
  }

  // ///////////////////////////////////////////////////////////////////////
  // Component

  Component::
    Component()
    : base_type("Invalid Component")
    , m_updateRequired(false)
    , m_enabled(false)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Component::
    Component(info_type a_compInfo, BufferArg a_debugName)
    : base_type(a_debugName)
    , m_compInfo(a_compInfo)
    , m_updateRequired(true)
    , m_enabled(true)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Component::
    Component(const this_type& a_other)
    : base_type(a_other) 
    , m_compInfo(a_other.m_compInfo)
    , m_updateRequired(true)
    , m_enabled(a_other.m_enabled)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Component::
    ~Component() { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Component::this_type&
    Component::
    operator =(this_type a_other) 
  {
    swap(a_other);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Component::
    swap(this_type& a_other)
  {
    using core::swap;
    swap(m_compInfo, a_other.m_compInfo);
    swap(m_updateRequired, a_other.m_updateRequired);
    swap(m_enabled, a_other.m_enabled);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Component::
    operator ==(const this_type& a_other) const
  {
    return m_compInfo == a_other.m_compInfo &&
           m_updateRequired == a_other.m_updateRequired &&
           m_enabled == a_other.m_enabled;
  }

  // -----------------------------------------------------------------------
  
  namespace algos { namespace component {

    namespace compare {

        // -----------------------------------------------------------------------
        // explicit instnatiations

        template struct ComponentGroup_T<core::use_self<Component> >;
        template struct ComponentGroup_T<core::use_pointee>;

        template struct ComponentType_T<core::use_self<Component> >;
        template struct ComponentType_T<core::use_pointee>;

    };

    namespace comparison {

      namespace component_type
      {
        // -----------------------------------------------------------------------
        // explicit instnatiations

        template struct LessThan_T<core::use_self<Component> >;
        template struct LessThan_T<core::use_pointee>;
      };

      namespace component_group
      {
        // -----------------------------------------------------------------------
        // explicit instnatiations

        template struct LessThan_T<core::use_self<Component> >;
        template struct LessThan_T<core::use_pointee>;
      };

    };

  };};

};};};

#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc;
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(core_cs::Component);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(core_cs::Component);


TLOC_EXPLICITLY_INSTANTIATE_ARRAY(core_cs::component_vptr);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(core_cs::component_sptr);