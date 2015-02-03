#ifndef _TLOC_CORE_COMPONENT_SYSTEM_USER_DATA_H_
#define _TLOC_CORE_COMPONENT_SYSTEM_USER_DATA_H_

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/types/tlocAny.h>

#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

namespace tloc { namespace core { namespace component_system {

  class UserData
    : public core_cs::Component_T<UserData,
                                  core_cs::component_group::k_core,
                                  components::k_listener>
  {
  public:
    typedef UserData                                      this_type;
    typedef Component_T
      <this_type, k_component_group, k_component_type>    base_type;
    typedef core_t::Any                                   any_type;

  public:
    UserData();
    explicit UserData(const any_type& a_other);

    template <typename T_UserDataType>
    T_UserDataType& GetAs();

    template <typename T_UserDataType>
    T_UserDataType const &  GetAs() const;

    template <typename T_UserDataType>
    this_type& SetAs(const T_UserDataType& a_userData);

    template <typename T_UserDataType>
    this_type& ResetAndSetAs(const T_UserDataType& a_userData);
    
  private:
    any_type  m_data;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_UserDataType>
  T_UserDataType& 
    UserData::
    GetAs()
  { return m_data.Cast<T_UserDataType>(); }

  template <typename T_UserDataType>
  T_UserDataType const &  
    UserData::
    GetAs() const
  { return m_data.Cast<T_UserDataType>(); }

  template <typename T_UserDataType>
  auto
    UserData::
    SetAs(const T_UserDataType& a_userData) -> this_type&
  { m_data.Assign(a_userData); return *this; }

  template <typename T_UserDataType>
  auto
    UserData::
    ResetAndSetAs(const T_UserDataType& a_userData) -> this_type&
  { 
    m_data.Reset(); 
    return SetAs<T_UserDataType>(); 
  }

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(UserData, user_data);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(UserData, user_data);
  TLOC_TYPEDEF_COMPONENT_POOL(UserData, user_data);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::core_cs::UserData);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::core_cs::UserData);

#endif