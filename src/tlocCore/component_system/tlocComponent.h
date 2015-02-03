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

  class EntityManager;

  class Component 
    : public base_classes::DebugName
    , public utils::ObjectCounter<Component>
  {
    friend class EntityManager;

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
    Component(const this_type& a_other);
    virtual  ~Component();

    this_type& operator=(this_type a_other);
    void       swap(this_type& a_other);

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

  typedef containers::tl_array<component_vptr>::type  component_ptr_array;
  typedef containers::tl_array<component_sptr>::type  component_sptr_array;

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

    explicit Component_T(BufferArg a_debugName)
      : base_type(info_type()
                    .GroupIndex(k_component_group)
                    .Type(k_component_type), 
                  a_debugName) 
    { }

    using group_id_base_type::GetUniqueGroupID;
  };

  // -----------------------------------------------------------------------

  namespace algos { namespace component {

    namespace compare {

      // ///////////////////////////////////////////////////////////////////////
      // ComponentGroup_T

      TLOC_DECL_ALGO_WITH_CTOR_UNARY(ComponentGroup_T, Component::component_group_type, );
      TLOC_DEFINE_ALGO_WITH_CTOR_UNARY(ComponentGroup_T, )
      {
        return extract()( a ).GetInfo().m_groupIndex == m_value;
      }

      // -----------------------------------------------------------------------
      // typedefs

      typedef ComponentGroup_T<core::use_reference>     ComponentGroup;
      typedef ComponentGroup_T<core::use_pointee>       ComponentGroupPointer;

      // -----------------------------------------------------------------------
      // extern template 
      TLOC_EXTERN_TEMPLATE_STRUCT(ComponentGroup_T<core::use_reference>);
      TLOC_EXTERN_TEMPLATE_STRUCT(ComponentGroup_T<core::use_pointee>);

      // ///////////////////////////////////////////////////////////////////////
      // ComponentType_T

      TLOC_DECL_ALGO_WITH_CTOR_UNARY(ComponentType_T, Component::info_type, );
      TLOC_DEFINE_ALGO_WITH_CTOR_UNARY(ComponentType_T, )
      {
        TLOC_ASSERT(extract()( a ).GetInfo().m_groupIndex == m_value.m_groupIndex,
                    "Comparing component types from different component groups");
        return extract()( a ).GetInfo().m_type == m_value.m_type;
      }

      // -----------------------------------------------------------------------
      // typedefs

      typedef ComponentType_T<core::use_reference>      ComponentType;
      typedef ComponentType_T<core::use_pointee>        ComponentType_Deref;

      // -----------------------------------------------------------------------
      // extern template 
      TLOC_EXTERN_TEMPLATE_STRUCT(ComponentGroup_T<core::use_reference>);
      TLOC_EXTERN_TEMPLATE_STRUCT(ComponentGroup_T<core::use_pointee>);

    };

    namespace comparison {

      namespace component_type
      {
        TLOC_DECL_ALGO_BINARY(LessThan_T, const);
        TLOC_DEFINE_ALGO_BINARY(LessThan_T, const)
        {
          TLOC_ASSERT(extract()(a).GetInfo().m_groupIndex == 
                      extract()(b).GetInfo().m_groupIndex,
                      "Component 'a' and 'b' are from different component groups");

          return extract()(a).GetInfo().m_type < extract()(b).GetInfo().m_type;
        }

        // -----------------------------------------------------------------------
        // typedefs

        typedef LessThan_T<core::use_reference>       LessThan;
        typedef LessThan_T<core::use_pointee>         LessThan_Deref;

        // -----------------------------------------------------------------------
        // extern template 
        TLOC_EXTERN_TEMPLATE_STRUCT(LessThan_T<core::use_reference>);
        TLOC_EXTERN_TEMPLATE_STRUCT(LessThan_T<core::use_pointee>);
      };

      namespace component_group
      {
        TLOC_DECL_ALGO_BINARY(LessThan_T, const);
        TLOC_DEFINE_ALGO_BINARY(LessThan_T, const)
        {
            return extract()(a).GetInfo().m_groupIndex < 
                   extract()(b).GetInfo().m_groupIndex; 
        }

        // -----------------------------------------------------------------------
        // typedefs

        typedef LessThan_T<core::use_reference>       LessThan;
        typedef LessThan_T<core::use_pointee>         LessThan_Deref;

        // -----------------------------------------------------------------------
        // extern template 
        TLOC_EXTERN_TEMPLATE_STRUCT(LessThan_T<core::use_reference>);
        TLOC_EXTERN_TEMPLATE_STRUCT(LessThan_T<core::use_pointee>);
      };

    };

  };};

};};};

//------------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::core_cs::Component);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::core_cs::Component);

TLOC_EXTERN_TEMPLATE_ARRAY(tloc::core_cs::component_vptr);
TLOC_EXTERN_TEMPLATE_ARRAY(tloc::core_cs::component_sptr);

#include <tlocCore/logging/tlocLog.h>

namespace tloc { namespace core {

  namespace logging {

    template <typename T_Logger, typename T_BuildConfig>
    Log_T<T_Logger, T_BuildConfig>&
      operator << (Log_T<T_Logger, T_BuildConfig>& a_log,
                   const core_cs::Component& a_comp)
    {
      a_log << "(" << a_comp.GetDebugName() << ")[" 
        << core_utils::MemoryAddress(&a_comp) << "]";

      return a_log;
    }

  };

};};

#endif