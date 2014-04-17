#pragma once
#ifndef _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_H_
#define _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_H_

#include <tlocCore/tlocArgs.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
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
    typedef core::smart_ptr::VirtualPtr<value_type>           pointer;
    typedef core::smart_ptr::VirtualPtr<const value_type>     const_pointer;

private:
    typedef UniquePtr<value_type>                             value_type_uptr;

  public:
    VirtualStackObjectBase_TI();

    template <typename T1>
    explicit VirtualStackObjectBase_TI(const Args<T1>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    template <typename T1, typename T2>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3, typename T4>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3, T4>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3, T4, T5>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    VirtualStackObjectBase_TI(const this_type& a_other);
    ~VirtualStackObjectBase_TI();

    this_type&                operator=(const this_type& a_other);
    this_type&                operator=(const value_type& a_other);
    void                      swap(this_type& a_other);

    value_type&               operator*();
    const value_type&         operator*() const;

    value_type_pointer        operator->();
    const_value_type_pointer  operator->() const;

    pointer                   get();
    const_pointer             get() const;

    bool                      operator==(const this_type& a_other) const;
    bool                      operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:

    value_type_uptr           m_value;
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
       build_config>                                          this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>           pointer;
    typedef core::smart_ptr::VirtualPtr<const value_type>     const_pointer;

private:
    typedef UniquePtr<value_type>                             value_type_uptr;

  public:
    VirtualStackObjectBase_TI();
    ~VirtualStackObjectBase_TI();

    value_type&               operator*();
    const value_type&         operator*() const;

    value_type_pointer        operator->();
    const_value_type_pointer  operator->() const;

    pointer                   get();
    const_pointer             get() const;

    bool                      operator==(const this_type& a_other) const;
    bool                      operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:

    value_type_uptr           m_value;
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
    template <typename T1>
    explicit VirtualStackObjectBase_TI(const Args<T1>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    template <typename T1, typename T2>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3, typename T4>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3, T4>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3, T4, T5>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    VirtualStackObjectBase_TI(const this_type& a_other);
    ~VirtualStackObjectBase_TI();

    this_type&                operator=(const this_type& a_other);
    this_type&                operator=(const value_type& a_other);
    void                      swap(this_type& a_other);

    value_type&               operator*();
    const value_type&         operator*() const;

    value_type_pointer        operator->();
    const_value_type_pointer  operator->() const;

    pointer                   get();
    const_pointer             get() const;

    bool                      operator==(const this_type& a_other) const;
    bool                      operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:

    value_type_uptr           m_value;
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
    template <typename T1>
    explicit VirtualStackObjectBase_TI(const Args<T1>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    template <typename T1, typename T2>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3, typename T4>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3, T4>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3, T4, T5>& a_param)
      : m_value(New<value_type>(a_param))
    { }

    ~VirtualStackObjectBase_TI();

    value_type&               operator*();
    const value_type&         operator*() const;

    value_type_pointer        operator->();
    const_value_type_pointer  operator->() const;

    pointer                   get();
    const_pointer             get() const;

    bool                      operator==(const this_type& a_other) const;
    bool                      operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:
    value_type_uptr           m_value;
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

    template <typename T1>
    explicit VirtualStackObjectBase_TI(const Args<T1>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    template <typename T1, typename T2>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3, typename T4>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3, T4>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3, T4, T5>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    VirtualStackObjectBase_TI(const this_type& a_other);
    ~VirtualStackObjectBase_TI();

    this_type&                operator=(this_type a_other);
    this_type&                operator=(const value_type& a_other);
    void                      swap(this_type& a_other);

    value_type&               operator*();
    const value_type&         operator*() const;

    value_type_pointer        operator->();
    const_value_type_pointer  operator->() const;

    pointer                   get();
    const_pointer             get() const;

    bool                      operator==(const this_type& a_other) const;
    bool                      operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:
    value_type                m_value;
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

    value_type&               operator*();
    const value_type&         operator*() const;

    value_type_pointer        operator->();
    const_value_type_pointer  operator->() const;

    pointer                   get();
    const_pointer             get() const;

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
    template <typename T1>
    explicit VirtualStackObjectBase_TI(const Args<T1>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    template <typename T1, typename T2>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3, typename T4>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3, T4>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3, T4, T5>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    VirtualStackObjectBase_TI(const this_type& a_other);
    ~VirtualStackObjectBase_TI();

    this_type&                operator=(this_type a_other);
    this_type&                operator=(const value_type& a_other);
    void                      swap(this_type& a_other);

    value_type&               operator*();
    const value_type&         operator*() const;

    value_type_pointer        operator->();
    const_value_type_pointer  operator->() const;

    pointer                   get();
    const_pointer             get() const;

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
    template <typename T1>
    explicit VirtualStackObjectBase_TI(const Args<T1>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    template <typename T1, typename T2>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3, typename T4>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3, T4>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    explicit VirtualStackObjectBase_TI(const Args<T1, T2, T3, T4, T5>& a_param)
      : m_value(MakeOnStack<value_type>(a_param))
    { }

    ~VirtualStackObjectBase_TI();

    value_type&               operator*();
    const value_type&         operator*() const;

    value_type_pointer        operator->();
    const_value_type_pointer  operator->() const;

    pointer                   get();
    const_pointer             get() const;

    bool                      operator==(const this_type& a_other) const;
    bool                      operator<(const this_type& a_other) const;

    TLOC_DECLARE_OPERATORS(this_type);

  protected:

    value_type                m_value;
  };

  // -----------------------------------------------------------------------
  // global functions

  template <typename T, typename T_CopyCtor,
            typename T_DefCtor, typename T_BuildConfig>
  VirtualPtr<T>
    ToVirtualPtr(VirtualStackObjectBase_TI
                    <T, T_CopyCtor, T_DefCtor, T_BuildConfig>& a_vso)
  { return a_vso.get(); }

  template <typename T, typename T_CopyCtor,
            typename T_DefCtor, typename T_BuildConfig>
  VirtualPtr<const T>
    ToVirtualPtr(const VirtualStackObjectBase_TI
                    <T, T_CopyCtor, T_DefCtor, T_BuildConfig>& a_vso)
  { return a_vso.get(); }

  namespace algos { namespace compare {

    namespace virtual_stack_object {

      // ///////////////////////////////////////////////////////////////////////
      // With VirtualPtr

      template <typename T, typename T_BuildConfig>
      struct WithVirtualPtr
      {
      public:
        typedef core_sptr::VirtualPtr<T, T_BuildConfig>       pointer;

      public:
        WithVirtualPtr(pointer a_toCompare)
          : m_toCompare(a_toCompare)
        { }

        template <typename U, typename U_CopyCtor,
                  typename U_DefCtor, typename U_BuildConfig>
        bool operator()
        (const VirtualStackObjectBase_TI<U, U_CopyCtor,
                                         U_DefCtor, U_BuildConfig>& a_vso)
        { return a_vso.get() == m_toCompare; }

      private:
        pointer m_toCompare;
      };

      // -----------------------------------------------------------------------
      // MakeVirtualPtr

      template <typename T, typename T_BuildConfig>
      WithVirtualPtr<T, T_BuildConfig>
        MakeWithVirtualPtr(VirtualPtr<T, T_BuildConfig> a_ptr)
      { return WithVirtualPtr<T, T_BuildConfig>(a_ptr); }

    };

  };};

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