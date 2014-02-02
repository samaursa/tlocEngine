#pragma once
#ifndef _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_INL_
#define _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_INL_

#ifndef _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_H_
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>

#include "tlocVirtualStackObject.h"

namespace tloc { namespace core { namespace smart_ptr {

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObject_T<>

#define TLOC_VIRTUAL_STACK_OBJECT_TEMPS   typename T, typename T_BuildConfig
#define TLOC_VIRTUAL_STACK_OBJECT_PARAMS  T, T_BuildConfig
#define TLOC_VIRTUAL_STACK_OBJECT_TYPE    typename VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    VirtualStackObject()
    : m_value()
    , m_valuePtr(&m_value)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    VirtualStackObject(const value_type& a_other)
    : m_value(a_other)
    , m_valuePtr(&m_value)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    VirtualStackObject(const this_type& a_other)
    : m_value(a_other.m_value)
    , m_valuePtr(&m_value)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    ~VirtualStackObject()
  {
    TLOC_ASSERT_LOW_LEVEL(m_valuePtr.unique(),
      "This object appears to be still in use");

    // this ensures that no checks are performed after m_value is automatically
    // deleted
    m_valuePtr.reset();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_TYPE::this_type&
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator=(this_type a_other)
  {
    a_other.swap(*this);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_TYPE::this_type&
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator=(const value_type& a_newValue)
  {
    this_type(a_newValue).swap(*this);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator value_type&()
  { return m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator value_type const&() const
  { return m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_TYPE::ptr_type
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    get()
  { return m_valuePtr; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  const TLOC_VIRTUAL_STACK_OBJECT_TYPE::ptr_type&
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    get() const
  { return m_valuePtr; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  bool
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator==(const this_type& a_other)
  { return m_value == a_other.m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  bool
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator==(const value_type& a_other)
  { return m_value == a_other; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  bool
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator!=(const this_type& a_other)
  { return m_value != a_other.m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  bool
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator!=(const value_type& a_other)
  { return m_value != a_other; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  void
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    swap(this_type& a_other)
  {
    using core::swap;

    swap(m_value, a_other.m_value);
  }

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObject_T<Release>

#define TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS   typename T
#define TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS  T, core_cfg::p_build_config::Release
#define TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TYPE    typename VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    VirtualStackObject()
    : m_value()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    VirtualStackObject(const value_type& a_other)
    : m_value(a_other)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    VirtualStackObject(const this_type& a_other)
    : m_value(a_other.m_value)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    ~VirtualStackObject()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TYPE::this_type&
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    operator=(this_type a_other)
  {
    a_other.swap(*this);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TYPE::this_type&
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    operator=(const value_type& a_newValue)
  {
    this_type(a_newValue).swap(*this);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    operator value_type&()
  { return m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    operator value_type const&() const
  { return m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TYPE::ptr_type
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    get()
  { return ptr_type(&m_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  const TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TYPE::ptr_type&
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    get() const
  { return ptr_type(&m_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  bool
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    operator==(const this_type& a_other)
  { return m_value == a_other.m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  bool
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    operator==(const value_type& a_other)
  { return m_value == a_other; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  bool
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    operator!=(const this_type& a_other)
  { return m_value != a_other.m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  bool
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    operator!=(const value_type& a_other)
  { return m_value != a_other; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  void
    VirtualStackObject<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    swap(this_type& a_other)
  {
    using core::swap;

    swap(m_value, a_other.m_value);
  }

};};};

#endif