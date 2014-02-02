#pragma once
#ifndef _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_H_
#define _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_H_

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/configs/tlocBuildConfig.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>

namespace tloc { namespace core { namespace smart_ptr {

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObject<>

  template <typename T, typename T_BuildConfig = core_cfg::BuildConfig::build_config_type>
  class VirtualStackObject
    : core_bclass::NonCopyable_I
  {
  public:
    typedef T                                                 value_type;
    typedef T_BuildConfig                                     build_config;

    typedef VirtualStackObject<value_type, build_config>      this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>           ptr_type;

  public:
    VirtualStackObject();
    explicit VirtualStackObject(const value_type& a_other);
    VirtualStackObject(const this_type& a_other);
    ~VirtualStackObject();

    this_type& operator=(this_type a_other);
    this_type& operator=(const value_type& a_newValue);

    operator value_type&();
    operator const value_type&() const;

    ptr_type        get();
    const ptr_type& get() const;

    bool operator==(const this_type& a_other);
    bool operator==(const value_type& a_other);
    bool operator!=(const this_type& a_other);
    bool operator!=(const value_type& a_other);

    void swap(this_type& a_other);

  private:

    value_type        m_value;
    ptr_type          m_valuePtr;
  };

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObject<Release>

  template <typename T>
  class VirtualStackObject<T, core_cfg::p_build_config::Release>
    : core_bclass::NonCopyable_I
  {
  public:
    typedef T                                                 value_type;
    typedef core_cfg::p_build_config::Release                 build_config;

    typedef VirtualStackObject<value_type, build_config>      this_type;
    typedef core::smart_ptr::VirtualPtr<value_type>           ptr_type;

  public:
    VirtualStackObject();
    explicit VirtualStackObject(const value_type& a_other);
    VirtualStackObject(const this_type& a_other);
    ~VirtualStackObject();

    this_type& operator=(this_type a_other);
    this_type& operator=(const value_type& a_newValue);

    operator value_type&();
    operator const value_type&() const;

    ptr_type        get();
    const ptr_type& get() const;

    bool operator==(const this_type& a_other);
    bool operator==(const value_type& a_other);
    bool operator!=(const this_type& a_other);
    bool operator!=(const value_type& a_other);

    void swap(this_type& a_other);

  private:
    value_type        m_value;
  };

};};};

#endif