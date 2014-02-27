#pragma once
#ifndef _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_H_
#define _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_H_

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/configs/tlocBuildConfig.h>
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
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<>

  template <typename T,
            typename T_BuildConfig = core_cfg::BuildConfig::build_config_type>
  class VirtualStackObjectBase_TI
  {
  public:
    typedef T                                                 value_type;
    typedef T*                                                value_type_pointer;

    typedef const T*                                          const_value_type_pointer;

    typedef T_BuildConfig                                     build_config;

    typedef VirtualStackObjectBase_TI<value_type, build_config>   this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>               pointer;
    typedef core::smart_ptr::VirtualPtr<const value_type>         const_pointer;

  private:
    typedef UniquePtr<value_type>                             value_type_uptr;

  public:
    explicit VirtualStackObjectBase_TI(const value_type& a_other);
    VirtualStackObjectBase_TI(const this_type& a_other);
    ~VirtualStackObjectBase_TI();

    this_type&          operator=(this_type a_other);
    this_type&          operator=(const value_type& a_other);
    void                swap(this_type& a_other);

    value_type&         operator*();
    const value_type&   operator*() const;

    value_type_pointer             operator->();
    const_value_type_pointer       operator->() const;

    const pointer&                  get();
    const const_pointer&            get() const;

    bool operator==(const this_type& a_other) const
    { return m_ptr == a_other.m_ptr; }
    bool operator<(const this_type& a_other) const
    { return m_ptr < a_other.m_ptr; }
    TLOC_DECLARE_OPERATORS(this_type);

  protected:

    value_type_uptr       m_value;
    pointer               m_ptr;
    mutable const_pointer m_constPtr;
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<Release>

  template <typename T>
  class VirtualStackObjectBase_TI<T, core_cfg::p_build_config::Release>
  {
  public:
    typedef T                                                 value_type;
    typedef T*                                                value_type_pointer;
    typedef const T*                                          const_value_type_pointer;

    typedef core_cfg::p_build_config::Release                 build_config;

    typedef VirtualStackObjectBase_TI<value_type, build_config>   this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>               pointer;
    typedef core::smart_ptr::VirtualPtr<const value_type>         const_pointer;

  public:
    explicit VirtualStackObjectBase_TI(const value_type& a_other);
    VirtualStackObjectBase_TI(const this_type& a_other);
    ~VirtualStackObjectBase_TI();

    this_type&          operator=(const this_type& a_other);
    this_type&          operator=(const value_type& a_other);
    void                swap(this_type& a_other);

    value_type&         operator*();
    const value_type&   operator*() const;

    pointer             operator->();
    const_pointer       operator->() const;

    pointer                get();
    const_pointer          get() const; // intentionally returned by value

    bool operator==(const this_type& a_other) const
    { return &m_value == &a_other.m_value; }
    bool operator<(const this_type& a_other) const
    { return &m_value < &a_other.m_value; }
    TLOC_DECLARE_OPERATORS(this_type);

  protected:
    value_type        m_value;
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObject_T<DefaultCtor>

  template <typename T,
            typename T_DefaultCtor = p_virtual_stack_object::default_ctor::Available>
  class VirtualStackObject_T
    : public VirtualStackObjectBase_TI<T, core_cfg::BuildConfig::build_config_type>
  {
  public:
    typedef VirtualStackObjectBase_TI<T,
      core_cfg::BuildConfig::build_config_type>                 base_type;

    typedef VirtualStackObject_T<T, T_DefaultCtor>              this_type;

    typedef typename base_type::value_type                      value_type;
    typedef typename base_type::build_config                    build_config;
    typedef typename base_type::pointer                         pointer;

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
    using base_type::swap;
    using base_type::operator=;
    using base_type::operator==;
    using base_type::operator!=;
    using base_type::operator>;
    using base_type::operator<=;
    using base_type::operator>=;
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObject_T<NoDefaultCtor>

  template <typename T>
  class VirtualStackObject_T<T, p_virtual_stack_object::default_ctor::NotAvail>
     : public VirtualStackObjectBase_TI<T, core_cfg::BuildConfig::build_config_type>
  {
  public:
    typedef VirtualStackObjectBase_TI<T,
      core_cfg::BuildConfig::build_config_type>                 base_type;

    typedef VirtualStackObject_T<T>                             this_type;

    typedef typename base_type::value_type                      value_type;
    typedef typename base_type::build_config                    build_config;
    typedef typename base_type::pointer                         pointer;

  public:
    explicit VirtualStackObject_T(const value_type& a_other)
      : base_type(a_other)
    { }

    ~VirtualStackObject_T()
    { }

  public:
    using base_type::get;
    using base_type::swap;
    using base_type::operator=;
    using base_type::operator==;
    using base_type::operator!=;
    using base_type::operator>;
    using base_type::operator<=;
    using base_type::operator>=;
  };

};};};

  // -----------------------------------------------------------------------
  // typedefs

#define TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(_type_, _typedef_)\
  typedef tloc::core_sptr::VirtualStackObject_T<_type_>  _typedef_##_vso

#define TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR(_type_, _typedef_)\
  typedef tloc::core_sptr::VirtualStackObject_T<_type_, tloc::core_sptr::p_virtual_stack_object::default_ctor::NotAvail>  _typedef_##_vso

#endif