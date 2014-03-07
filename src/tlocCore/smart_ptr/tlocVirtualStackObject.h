#pragma once
#ifndef _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_H_
#define _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_H_

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/configs/tlocBuildConfig.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>
#include <tlocCore/base_classes/tlocPolicyBase.h>

namespace tloc { namespace core { namespace smart_ptr {

  namespace p_virtual_stack_object
  {
    namespace default_ctor
    {
      struct Available {};
      struct NotAvail {};
    };

    namespace copy_ctor
    {
      struct Available {};
      struct NotAvail {};
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<T, CopyCtor::Available, DefCtor::Available>

  template <typename T,
            typename T_CopyCtor = p_virtual_stack_object::copy_ctor::Available,
            typename T_DefCtor = p_virtual_stack_object::default_ctor::Available,
            typename T_BuildConfig = core_cfg::BuildConfig::build_config_type>
  class VirtualStackObjectBase_TI
  {
  public:
    typedef T                                                 value_type;
    typedef T*                                                value_type_pointer;

    typedef const T*                                          const_value_type_pointer;

    typedef T_BuildConfig                                     build_config;

    typedef VirtualStackObjectBase_TI
      <value_type, T_CopyCtor, T_DefCtor, build_config>       this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>               pointer;
    typedef core::smart_ptr::VirtualPtr<const value_type>         const_pointer;

  private:
    typedef UniquePtr<value_type>                             value_type_uptr;

  public:
    VirtualStackObjectBase_TI();
    explicit VirtualStackObjectBase_TI(const value_type& a_other);
    VirtualStackObjectBase_TI(const this_type& a_other);
    ~VirtualStackObjectBase_TI();

    this_type&                operator=(this_type a_other);
    this_type&                operator=(const value_type& a_other);
    void                      swap(this_type& a_other);

    value_type&               operator*();
    const value_type&         operator*() const;

    value_type_pointer        operator->();
    const_value_type_pointer  operator->() const;

    const pointer&            get();
    const const_pointer&      get() const;

    bool                      operator==(const this_type& a_other) const;
    bool                      operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:

    value_type_uptr       m_value;
    pointer               m_ptr;
    mutable const_pointer m_constPtr;
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<T, CopyCtor::NotAvailable, DefaultCtor::Available>

  template <typename T,
            typename T_BuildConfig>
  class VirtualStackObjectBase_TI<T,
                                  p_virtual_stack_object::copy_ctor::NotAvail,
                                  p_virtual_stack_object::default_ctor::Available,
                                  T_BuildConfig>
    : public core_bclass::NonCopyable_I
  {
  public:
    typedef T                                                 value_type;
    typedef T*                                                value_type_pointer;

    typedef const T*                                          const_value_type_pointer;

    typedef T_BuildConfig                                     build_config;

    typedef VirtualStackObjectBase_TI
      <value_type,
       p_virtual_stack_object::copy_ctor::NotAvail,
       p_virtual_stack_object::default_ctor::Available,
       build_config>                                              this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>               pointer;
    typedef core::smart_ptr::VirtualPtr<const value_type>         const_pointer;

  private:
    typedef UniquePtr<value_type>                             value_type_uptr;

  public:
    VirtualStackObjectBase_TI();
    ~VirtualStackObjectBase_TI();

    value_type&               operator*();
    const value_type&         operator*() const;

    value_type_pointer        operator->();
    const_value_type_pointer  operator->() const;

    const pointer&            get();
    const const_pointer&      get() const;

    bool                      operator==(const this_type& a_other) const;
    bool                      operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:

    value_type_uptr       m_value;
    pointer               m_ptr;
    mutable const_pointer m_constPtr;
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<T, CopyCtor::Available, DefCtor::NotAvail>

  template <typename T,
            typename T_BuildConfig>
  class VirtualStackObjectBase_TI<T,
                                  p_virtual_stack_object::copy_ctor::Available,
                                  p_virtual_stack_object::default_ctor::NotAvail,
                                  T_BuildConfig>
  {
  public:
    typedef T                                                 value_type;
    typedef T*                                                value_type_pointer;

    typedef const T*                                          const_value_type_pointer;

    typedef T_BuildConfig                                     build_config;

    typedef VirtualStackObjectBase_TI
      <value_type,
       p_virtual_stack_object::copy_ctor::Available,
       p_virtual_stack_object::default_ctor::NotAvail,
       build_config>                                              this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>               pointer;
    typedef core::smart_ptr::VirtualPtr<const value_type>         const_pointer;

  private:
    typedef UniquePtr<value_type>                             value_type_uptr;

  public:
    explicit VirtualStackObjectBase_TI(const value_type& a_other);
    VirtualStackObjectBase_TI(const this_type& a_other);
    ~VirtualStackObjectBase_TI();

    this_type&                operator=(this_type a_other);
    this_type&                operator=(const value_type& a_other);
    void                      swap(this_type& a_other);

    value_type&               operator*();
    const value_type&         operator*() const;

    value_type_pointer        operator->();
    const_value_type_pointer  operator->() const;

    const pointer&            get();
    const const_pointer&      get() const;

    bool                      operator==(const this_type& a_other) const;
    bool                      operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:

    value_type_uptr       m_value;
    pointer               m_ptr;
    mutable const_pointer m_constPtr;
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<T, CopyCtor::NotAvailable, DefCtor::NotAvail>

  template <typename T,
            typename T_BuildConfig>
  class VirtualStackObjectBase_TI<T,
                                  p_virtual_stack_object::copy_ctor::NotAvail,
                                  p_virtual_stack_object::default_ctor::NotAvail,
                                  T_BuildConfig>
    : public core_bclass::NonCopyable_I
  {
  public:
    typedef T                                                 value_type;
    typedef T*                                                value_type_pointer;

    typedef const T*                                          const_value_type_pointer;

    typedef T_BuildConfig                                     build_config;

    typedef VirtualStackObjectBase_TI
      <value_type,
       p_virtual_stack_object::copy_ctor::NotAvail,
       p_virtual_stack_object::default_ctor::NotAvail,
       build_config>                                              this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>               pointer;
    typedef core::smart_ptr::VirtualPtr<const value_type>         const_pointer;

  private:
    typedef UniquePtr<value_type>                             value_type_uptr;

  public:
    template <typename T_CtorParam>
    VirtualStackObjectBase_TI(const T_CtorParam& a_param)
      : m_value(new value_type(a_param))
      , m_ptr(m_value)
      , m_constPtr(m_value)
    { }

    ~VirtualStackObjectBase_TI();

    value_type&               operator*();
    const value_type&         operator*() const;

    value_type_pointer        operator->();
    const_value_type_pointer  operator->() const;

    const pointer&            get();
    const const_pointer&      get() const;

    bool                      operator==(const this_type& a_other) const;
    bool                      operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:

    value_type_uptr       m_value;
    pointer               m_ptr;
    mutable const_pointer m_constPtr;
  };

  // ///////////////////////////////////////////////////////////////////////
  // ///////////////////////////////////////////////////////////////////////
  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<T, CopyCtor::Available, DefCtor::Available, Release>

  template <typename T>
  class VirtualStackObjectBase_TI <T,
                                   p_virtual_stack_object::copy_ctor::Available,
                                   p_virtual_stack_object::default_ctor::Available,
                                   core_cfg::p_build_config::Release>
  {
  public:
    typedef T                                                 value_type;
    typedef T*                                                value_type_pointer;
    typedef const T*                                          const_value_type_pointer;

    typedef core_cfg::p_build_config::Release                 build_config;

    typedef VirtualStackObjectBase_TI<value_type>                 this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>               pointer;
    typedef core::smart_ptr::VirtualPtr<const value_type>         const_pointer;

  public:
    VirtualStackObjectBase_TI();
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

    bool operator==(const this_type& a_other) const;
    bool operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:
    value_type        m_value;
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<T, CopyCtor::NotAvailable, Release>

  template <typename T>
  class VirtualStackObjectBase_TI<T,
                                  p_virtual_stack_object::copy_ctor::NotAvail,
                                  p_virtual_stack_object::default_ctor::Available,
                                  core_cfg::p_build_config::Release>
  {
  public:
    typedef T                                                 value_type;
    typedef T*                                                value_type_pointer;
    typedef const T*                                          const_value_type_pointer;

    typedef core_cfg::p_build_config::Release                 build_config;

    typedef VirtualStackObjectBase_TI
      <value_type,
       p_virtual_stack_object::copy_ctor::NotAvail,
       p_virtual_stack_object::default_ctor::Available,
       core_cfg::p_build_config::Release>                         this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>               pointer;
    typedef core::smart_ptr::VirtualPtr<const value_type>         const_pointer;

  public:
    VirtualStackObjectBase_TI();
    ~VirtualStackObjectBase_TI();

    value_type&             operator*();
    const value_type&       operator*() const;

    pointer                 operator->();
    const_pointer           operator->() const;

    pointer                 get();
    const_pointer           get() const; // intentionally returned by value

    bool                    operator==(const this_type& a_other) const;
    bool                    operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:
    value_type        m_value;
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<T, CopyCtor::NotAvailable>

  template <typename T>
  class VirtualStackObjectBase_TI<T,
                                  p_virtual_stack_object::copy_ctor::Available,
                                  p_virtual_stack_object::default_ctor::NotAvail,
                                  core_cfg::p_build_config::Release>
  {
  public:
    typedef T                                                 value_type;
    typedef T*                                                value_type_pointer;

    typedef const T*                                          const_value_type_pointer;

    typedef core_cfg::p_build_config::Release                 build_config;

    typedef VirtualStackObjectBase_TI
      <value_type,
       p_virtual_stack_object::copy_ctor::Available,
       p_virtual_stack_object::default_ctor::NotAvail,
       build_config>                                              this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>               pointer;
    typedef core::smart_ptr::VirtualPtr<const value_type>         const_pointer;

  public:
    explicit VirtualStackObjectBase_TI(const value_type& a_other);
    VirtualStackObjectBase_TI(const this_type& a_other);
    ~VirtualStackObjectBase_TI();

    this_type&                operator=(this_type a_other);
    this_type&                operator=(const value_type& a_other);
    void                      swap(this_type& a_other);

    value_type&               operator*();
    const value_type&         operator*() const;

    pointer                   operator->();
    const_pointer             operator->() const;

    pointer                   get();
    const_pointer             get() const; // intentionally returned by value

    bool                      operator==(const this_type& a_other) const;
    bool                      operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:

    value_type                m_value;
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<T, CopyCtor::NotAvailable>

  template <typename T>
  class VirtualStackObjectBase_TI<T,
                                  p_virtual_stack_object::copy_ctor::NotAvail,
                                  p_virtual_stack_object::default_ctor::NotAvail,
                                  core_cfg::p_build_config::Release>
    : public core_bclass::NonCopyable_I
  {
  public:
    typedef T                                                 value_type;
    typedef T*                                                value_type_pointer;

    typedef const T*                                          const_value_type_pointer;

    typedef core_cfg::p_build_config::Release                 build_config;

    typedef VirtualStackObjectBase_TI
      <value_type,
       p_virtual_stack_object::copy_ctor::NotAvail,
       p_virtual_stack_object::default_ctor::NotAvail,
       build_config>                                              this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>               pointer;
    typedef core::smart_ptr::VirtualPtr<const value_type>         const_pointer;

  public:
    template <typename T_CtorParam>
    VirtualStackObjectBase_TI(const T_CtorParam& a_param)
      : m_value(a_param)
    { }

    ~VirtualStackObjectBase_TI();

    value_type&               operator*();
    const value_type&         operator*() const;

    pointer                   operator->();
    const_pointer             operator->() const;

    pointer                   get();
    const_pointer             get() const; // intentionally returned by value

    bool                      operator==(const this_type& a_other) const;
    bool                      operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:

    value_type                m_value;
  };

};};};

  // -----------------------------------------------------------------------
  // typedefs

#define TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(_type_, _typedef_)\
  typedef tloc::core_sptr::VirtualStackObjectBase_TI<_type_>  _typedef_##_vso

#define TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR(_type_, _typedef_)\
  typedef tloc::core_sptr::VirtualStackObjectBase_TI<_type_, \
    tloc::core_sptr::p_virtual_stack_object::copy_ctor::Available, \
    tloc::core_sptr::p_virtual_stack_object::default_ctor::NotAvail>  _typedef_##_vso

#define TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR(_type_, _typedef_)\
  typedef tloc::core_sptr::VirtualStackObjectBase_TI<_type_, \
    tloc::core_sptr::p_virtual_stack_object::copy_ctor::NotAvail, \
    tloc::core_sptr::p_virtual_stack_object::default_ctor::Available>  _typedef_##_vso

#define TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(_type_, _typedef_)\
  typedef tloc::core_sptr::VirtualStackObjectBase_TI<_type_, \
    tloc::core_sptr::p_virtual_stack_object::copy_ctor::NotAvail, \
    tloc::core_sptr::p_virtual_stack_object::default_ctor::NotAvail>  _typedef_##_vso

#endif