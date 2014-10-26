#ifndef TLOC_COMPONENT_H
#define TLOC_COMPONENT_H

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponentType.h>
#include <tlocCore/base_classes/tlocDebugName.h>
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

  class Component 
    : public base_classes::DebugName
    , public utils::ObjectCounter<Component>
  {
  public:
    typedef Component                       this_type;
    typedef base_classes::DebugName         base_type;
    typedef component_group::value_type    component_group_type;
    typedef components::value_type          component_type;
    typedef utils::ObjectCounter<Component> counter_type;
    typedef counter_type::size_type         counter_size_type;

  public:
    struct Info
    {
    public:
      typedef Info                          this_type;

    public:
      Info();

      bool IsValid() const;

      bool operator==(const this_type& a_other) const;
      TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

    public:
      TLOC_DECL_PARAM_VAR(component_group_type, GroupIndex, m_groupIndex);
      TLOC_DECL_PARAM_VAR(component_group_type, Type, m_type);
    }; typedef Info                         info_type;

  public:
    Component();
    explicit Component(info_type a_type, BufferArg a_debugName);
    explicit Component(const this_type& a_other);
    virtual  ~Component();

    // although not theoretically needed, the compiler fails to compare two
    // components and instead tried to use global operator== for iterators.
    bool operator==(const this_type& a_other) const;
    TLOC_DECLARE_OPERATOR_NOT_EQUAL(this_type);

    TLOC_DECL_AND_DEF_GETTER(info_type, GetInfo, m_compInfo);
    TLOC_DECL_AND_DEF_GETTER(bool, IsUpdateRequired, m_updateRequired);
    TLOC_DECL_AND_DEF_GETTER(counter_size_type, GetTotalComponents,
                             counter_type::GetCurrentObjectCount());
    TLOC_DECL_AND_DEF_GETTER(bool, IsEnabled, m_enabled);

    TLOC_DECL_AND_DEF_SETTER(bool, SetUpdateRequired, m_updateRequired);

    using base_type::GetDebugName;
    using base_type::SetDebugName;

  protected:
    // Only EntityManager is allowed to change this
    TLOC_DECL_AND_DEF_SETTER(bool, SetEnabled, m_enabled);

  protected:
    info_type             m_compInfo;
    bool                  m_updateRequired;
    bool                  m_enabled;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(Component, component);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Component, component);

  TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(Component);
  TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(Component);

  typedef containers::tl_array<component_vptr>::type  component_ptr_array;
  typedef containers::tl_array<component_sptr>::type  component_sptr_array;

  TLOC_EXTERN_TEMPLATE_ARRAY(component_vptr);
  TLOC_EXTERN_TEMPLATE_ARRAY(component_sptr);

  //////////////////////////////////////////////////////////////////////////
  // Component_T<>

  template <typename T_Component, 
            tl_int T_ComponentGroup, 
            tl_int T_ComponentType>
  class Component_T : private utils::GroupID<T_Component>,
                      public Component
  {
  public:
    enum { k_component_group  = T_ComponentGroup };
    enum { k_component_type   = T_ComponentType };

  public:
    typedef Component                             base_type;
    typedef base_type::component_type             component_type;
    typedef utils::GroupID<T_Component>           group_id_base_type;

    explicit Component_T(info_type a_type, BufferArg a_debugName)
      : base_type(a_type, a_debugName) {}

    using group_id_base_type::GetUniqueGroupID;
  };

  // -----------------------------------------------------------------------

  namespace algos { namespace component {

    namespace compare {

      // ///////////////////////////////////////////////////////////////////////
      // ComponentGroup_T

      template <typename T_ExtractMethod = core::use_self<Component> >
      struct ComponentGroup_T
      {
        typedef Component::component_group_type     comp_group_type;
        typedef T_ExtractMethod                     et;

        ComponentGroup_T(comp_group_type a_groupIndex)
          : m_groupIndex(a_groupIndex)
        { }

        // true if a < b
        template <typename T>
        bool operator()(const T& a)
        {
          return et()(b).GetInfo().m_groupIndex == m_groupIndex;
        }

        comp_group_type   m_groupIndex;
      };

      // -----------------------------------------------------------------------
      // typedefs

      typedef ComponentGroup_T<>                    ComponentGroup;
      typedef ComponentGroup_T<core::use_pointee>   ComponentGroupPointer;

      // -----------------------------------------------------------------------
      // extern template 
      TLOC_EXTERN_TEMPLATE_STRUCT(ComponentGroup_T<core::use_self<Component> >);
      TLOC_EXTERN_TEMPLATE_STRUCT(ComponentGroup_T<core::use_pointee>);

      // ///////////////////////////////////////////////////////////////////////
      // ComponentType_T

      template <typename T_ExtractMethod = core::use_self<Component> >
      struct ComponentType_T
      {
        typedef Component::info_type                info_type;
        typedef T_ExtractMethod                     et;

        ComponentType_T(info_type a_info)
          : m_info(a_info)
        { }

        // true if a < b
        template <typename T>
        bool operator()(const T& a)
        {
          TLOC_ASSERT(et()(a).GetInfo().m_groupIndex == m_info.m_groupIndex,
                      "Comparing component types from different component groups");
          return et()(a).GetInfo().m_type == m_info.m_type;
        }

        info_type   m_info;
      };

      // -----------------------------------------------------------------------
      // typedefs

      typedef ComponentType_T<>                     ComponentType;
      typedef ComponentType_T<core::use_pointee>    ComponentTypePointer;

      // -----------------------------------------------------------------------
      // extern template 
      TLOC_EXTERN_TEMPLATE_STRUCT(ComponentGroup_T<core::use_self<Component> >);
      TLOC_EXTERN_TEMPLATE_STRUCT(ComponentGroup_T<core::use_pointee>);

    };

    namespace comparison {

      namespace component_type
      {
        template <typename T_ExtractMethod = core::use_self<Component> >
        struct LessThan_T
        {
          typedef T_ExtractMethod                     et;

          // true if a < b
          template <typename T>
          bool operator()(const T& a, const T& b)
          {
            TLOC_ASSERT(et()(a).GetInfo().m_groupIndex == et()(b).GetInfo().m_groupIndex,
                        "Component 'a' and 'b' are from different component groups");

            return et()(a).GetInfo().m_type < 
                   et()(b).GetInfo().m_type;
          }
        };

        // -----------------------------------------------------------------------
        // typedefs

        typedef LessThan_T<>                          LessThan;
        typedef LessThan_T<core::use_pointee>         LessThanPointer;

        // -----------------------------------------------------------------------
        // extern template 
        TLOC_EXTERN_TEMPLATE_STRUCT(LessThan_T<core::use_self<Component> >);
        TLOC_EXTERN_TEMPLATE_STRUCT(LessThan_T<core::use_pointee>);
      };

      namespace component_group
      {
        template <typename T_ExtractMethod = core::use_self<Component> >
        struct LessThan_T
        {
          typedef T_ExtractMethod                     et;

          // true if a < b
          template <typename T>
          bool operator()(const T& a, const T& b)
          { 
            return et()(a).GetInfo().m_groupIndex < 
                   et()(b).GetInfo().m_groupIndex; 
          }
        };

        // -----------------------------------------------------------------------
        // typedefs

        typedef LessThan_T<>                          LessThan;
        typedef LessThan_T<core::use_pointee>         LessThanPointer;

        // -----------------------------------------------------------------------
        // extern template 
        TLOC_EXTERN_TEMPLATE_STRUCT(LessThan_T<core::use_self<Component> >);
        TLOC_EXTERN_TEMPLATE_STRUCT(LessThan_T<core::use_pointee>);
      };

    };

  };};


};};};

#endif