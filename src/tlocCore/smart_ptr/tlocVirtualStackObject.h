#pragma once
#ifndef _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_H_
#define _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_H_

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/configs/tlocBuildConfig.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>

namespace tloc { namespace core { namespace smart_ptr {

  namespace p_virtual_stack_object
  {
    namespace default_ctor
    {
      struct Available {};
      struct NotAvail {};
    };

    namespace equality
    {
      struct Available {};
      struct NotAvail {};
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<>

  template <typename T,
            typename T_BuildConfig = core_cfg::BuildConfig::build_config_type>
  class VirtualStackObjectBase_TI
    : core_bclass::NonCopyable_I
  {
  protected:
    typedef T                                                 value_type;
    typedef T*                                                pointer;

    typedef T                                                 value_type;
    typedef const T*                                          const_pointer;

    typedef T_BuildConfig                                     build_config;

    typedef VirtualStackObjectBase_TI<value_type, build_config>   this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>               ptr_type;
    typedef core::smart_ptr::VirtualPtr<const value_type>         const_ptr_type;

  public:
    explicit VirtualStackObjectBase_TI(const value_type& a_other);
    ~VirtualStackObjectBase_TI();

    value_type&         operator*();
    const value_type&   operator*() const;

    pointer             operator->();
    const_pointer       operator->() const;

    ptr_type            get();
    const_ptr_type      get() const;

  protected:

    value_type        m_value;
    ptr_type          m_valuePtr;
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<Release>

  template <typename T>
  class VirtualStackObjectBase_TI<T, core_cfg::p_build_config::Release>
    : core_bclass::NonCopyable_I
  {
  protected:
    typedef T                                                 value_type;
    typedef T*                                                pointer;

    typedef T                                                 value_type;
    typedef const T*                                          const_pointer;

    typedef core_cfg::p_build_config::Release                 build_config;

    typedef VirtualStackObjectBase_TI<value_type, build_config>   this_type;
    typedef pointer                                               ptr_type;
    typedef const_pointer                                         const_ptr_type;

  public:
    explicit VirtualStackObjectBase_TI(const value_type& a_other);
    ~VirtualStackObjectBase_TI();

    value_type&         operator*();
    const value_type&   operator*() const;

    pointer             operator->();
    const_pointer       operator->() const;

    ptr_type            get();
    const_ptr_type      get() const; // intentionally returned by value

  protected:
    value_type        m_value;
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObject_T<DefaultCtor, Equality>

  template <typename T,
            typename T_DefaultCtor = p_virtual_stack_object::default_ctor::Available,
            typename T_Equality = p_virtual_stack_object::equality::Available>
  class VirtualStackObject_T
    : public VirtualStackObjectBase_TI<T, core_cfg::BuildConfig::build_config_type>
  {
  public:
    typedef VirtualStackObjectBase_TI<T,
      core_cfg::BuildConfig::build_config_type>                 base_type;

    typedef VirtualStackObject_T<T, T_DefaultCtor, T_Equality>  this_type;

    typedef typename base_type::value_type                      value_type;
    typedef typename base_type::build_config                    build_config;
    typedef typename base_type::ptr_type                        ptr_type;

  public:
    VirtualStackObject_T()
      : base_type(value_type())
    { }

    explicit VirtualStackObject_T(const value_type& a_other)
      : base_type(a_other)
    { }

    ~VirtualStackObject_T()
    { }

  public:
    using base_type::get;

    bool operator==(const this_type& a_other) const
    { return m_value == a_other.m_value; }
    bool operator==(const value_type& a_other) const
    { return m_value == a_other; }
    bool operator!=(const this_type& a_other) const
    { return m_value != a_other.m_value; }
    bool operator!=(const value_type& a_other) const
    { return m_value != a_other; }

  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObject_T<NoDefaultCtor, Equality>

  template <typename T>
  class VirtualStackObject_T
    <
     T,
     p_virtual_stack_object::default_ctor::NotAvail,
     p_virtual_stack_object::equality::Available
    > : public VirtualStackObjectBase_TI<T, core_cfg::BuildConfig::build_config_type>
  {
  public:
    typedef VirtualStackObjectBase_TI<T,
      core_cfg::BuildConfig::build_config_type>                 base_type;

    typedef VirtualStackObject_T<T>                             this_type;

    typedef typename base_type::value_type                      value_type;
    typedef typename base_type::build_config                    build_config;
    typedef typename base_type::ptr_type                        ptr_type;

  public:
    explicit VirtualStackObject_T(const value_type& a_other)
      : base_type(a_other)
    { }

    ~VirtualStackObject_T()
    { }

  public:
    using base_type::get;

    bool operator==(const this_type& a_other) const
    { return m_value == a_other.m_value; }
    bool operator==(const value_type& a_other) const
    { return m_value == a_other; }
    bool operator!=(const this_type& a_other) const
    { return m_value != a_other.m_value; }
    bool operator!=(const value_type& a_other) const
    { return m_value != a_other; }
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObject_T<DefaultCtor, NoEquality>

  template <typename T>
  class VirtualStackObject_T
    <
     T,
     p_virtual_stack_object::default_ctor::Available,
     p_virtual_stack_object::equality::NotAvail
    > : public VirtualStackObjectBase_TI<T, core_cfg::BuildConfig::build_config_type>
  {
  public:
    typedef VirtualStackObjectBase_TI<T,
      core_cfg::BuildConfig::build_config_type>                 base_type;

    typedef VirtualStackObject_T<T>                             this_type;

    typedef typename base_type::value_type                      value_type;
    typedef typename base_type::build_config                    build_config;
    typedef typename base_type::ptr_type                        ptr_type;

  public:
    VirtualStackObject_T()
      : base_type(value_type())
    { }

    explicit VirtualStackObject_T(const value_type& a_other)
      : base_type(a_other)
    { }

    ~VirtualStackObject_T()
    { }

  public:
    using base_type::get;

    template <typename T_Dummy>
    bool operator==(const T_Dummy& a_other)
    {
      TLOC_STATIC_ASSERT_FALSE(T_Dummy, Operator_equalequal_explicitly_forbidden);
    }

    template <typename T_Dummy>
    bool operator!=(const T_Dummy& a_other)
    {
      TLOC_STATIC_ASSERT_FALSE(T_Dummy, Operator_notequal_explicitly_forbidden);
    }
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObject_T<NoDefaultCtor, NoEquality>

  template <typename T>
  class VirtualStackObject_T
    <
     T,
     p_virtual_stack_object::default_ctor::NotAvail,
     p_virtual_stack_object::equality::NotAvail
    > : public VirtualStackObjectBase_TI<T, core_cfg::BuildConfig::build_config_type>
  {
  public:
    typedef VirtualStackObjectBase_TI<T,
      core_cfg::BuildConfig::build_config_type>                 base_type;

    typedef VirtualStackObject_T<T>                             this_type;

    typedef typename base_type::value_type                      value_type;
    typedef typename base_type::build_config                    build_config;
    typedef typename base_type::ptr_type                        ptr_type;

  public:
    explicit VirtualStackObject_T(const value_type& a_other)
      : base_type(a_other)
    { }

    ~VirtualStackObject_T()
    { }

  public:
    using base_type::get;

    template <typename T_Dummy>
    bool operator==(const T_Dummy& a_other)
    {
      TLOC_STATIC_ASSERT_FALSE(T_Dummy, Operator_equalequal_explicitly_forbidden);
    }

    template <typename T_Dummy>
    bool operator!=(const T_Dummy& a_other)
    {
      TLOC_STATIC_ASSERT_FALSE(T_Dummy, Operator_notequal_explicitly_forbidden);
    }
  };

  // -----------------------------------------------------------------------
  // typedefs

};};};

  // -----------------------------------------------------------------------
  // typedefs

#define TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(_type_, _typedef_)\
  typedef tloc::core_sptr::VirtualStackObject_T<_type_>  _typedef_##_vso

#define TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR(_type_, _typedef_)\
  typedef tloc::core_sptr::VirtualStackObject_T<_type_, tloc::core_sptr::p_virtual_stack_object::default_ctor::NotAvail>  _typedef_##_vso

#define TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_EQUALITY(_type_, _typedef_)\
  typedef tloc::core_sptr::VirtualStackObject_T<_type_, tloc::core_sptr::p_virtual_stack_object::default_ctor::Available, tloc::core_sptr::p_virtual_stack_object::equality::NotAvail>  _typedef_##_vso

#define TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR_AND_EQUALITY(_type_, _typedef_)\
  typedef tloc::core_sptr::VirtualStackObject_T<_type_, tloc::core_sptr::p_virtual_stack_object::default_ctor::NotAvail, tloc::core_sptr::p_virtual_stack_object::equality::NotAvail>  _typedef_##_vso

#endif