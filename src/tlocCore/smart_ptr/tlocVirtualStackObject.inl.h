#pragma once
#ifndef _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_INL_
#define _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_INL_

#ifndef _TLOC_CORE_SMART_PTR_VIRTUAL_STACK_OBJECT_H_
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocAlgorithms.inl.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/utilities/tlocPointerUtils.h>

#include "tlocVirtualStackObject.h"

namespace tloc { namespace core { namespace smart_ptr {

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<>

#define TLOC_VIRTUAL_STACK_OBJECT_TEMPS   typename T, typename T_BuildConfig
#define TLOC_VIRTUAL_STACK_OBJECT_PARAMS  T, T_BuildConfig
#define TLOC_VIRTUAL_STACK_OBJECT_TYPE    typename VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    VirtualStackObjectBase_TI(const value_type& a_other)
    : m_value(a_other)
  {
    // m_ptr and m_constPtr are populated when accessed
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    VirtualStackObjectBase_TI(const this_type& a_other)
    : m_value(a_other.m_value)
  {
    // m_ptr and m_constPtr are populated when accessed
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    ~VirtualStackObjectBase_TI()
  {
    DoSetVirtualPtr();

    TLOC_ASSERT(m_ptr ? m_ptr.get() == &m_value : nullptr,
      "VirtualPtr does not appear to be tracking m_value");
    TLOC_ASSERT_LOW_LEVEL(m_ptr.unique(),
      "This object appears to be still in use");

    // this ensures that no checks are performed after m_value is automatically
    // deleted
    m_ptr.reset();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_TYPE::this_type&
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator=(this_type a_other)
  {
    a_other.swap(*this);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_TYPE::this_type&
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator=(const value_type& a_other)
  {
    this_type temp(a_other);
    temp.swap(*this);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  void
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    swap(this_type& a_other)
  {
    using core::swap;

    swap(m_value, a_other.m_value);
    DoSetVirtualPtr();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_TYPE::value_type&
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator*()
  { return m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  const TLOC_VIRTUAL_STACK_OBJECT_TYPE::value_type&
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator*() const
  { return m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_TYPE::value_type_pointer
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator->()
  { return &m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_TYPE::const_value_type_pointer
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    operator->() const
  { return &m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_TYPE::pointer
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    get()
  {
    DoSetVirtualPtr();
    return m_ptr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_TYPE::const_pointer
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    get() const
  {
    DoSetVirtualPtr();
    return const_pointer(&m_value);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  void
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    DoSetVirtualPtr()
  {
    if (m_ptr)
    {
      tl_uintptr addressOfvptr = core_utils::GetMemoryAddress(m_ptr.get());
      tl_uintptr addressOfvalue = core_utils::GetMemoryAddress(&m_value);

      // NOTE: Assertion here means that you still have VirtualPtrs who are
      // holding on to a now incorrect address. This is usually caused by a
      // reallocation of a container
      TLOC_ASSERT( (m_ptr.unique() ? true : addressOfvalue == addressOfvptr),
        "Address of value has changed - VirtualPtrs now invalid");

      if (addressOfvptr != addressOfvalue)
      {
        m_ptr.reset(&m_value);
      }
    }
    else
    {
      m_ptr.reset(&m_value);
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_TEMPS>
  void
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_PARAMS>::
    DoSetVirtualPtr() const
  {
    if (m_ptr)
    {
      tl_uintptr addressOfvptr = core_utils::GetMemoryAddress(m_constPtr.get());
      tl_uintptr addressOfvalue = core_utils::GetMemoryAddress(&m_value);

      // NOTE: Assertion here means that you still have VirtualPtrs who are
      // holding on to a now incorrect address. This is usually caused by a
      // reallocation of a container
      TLOC_ASSERT( (m_constPtr.unique() ? true : addressOfvalue == addressOfvptr),
        "Address of value has changed - VirtualPtrs now invalid");

      if (addressOfvptr != addressOfvalue)
      {
        value_type* nonConstVal = const_cast<value_type*>(&m_value);
        m_ptr.reset(nonConstVal);
      }
    }
    else
    {
      value_type* nonConstVal = const_cast<value_type*>(&m_value);
      m_ptr.reset(nonConstVal);
    }
  }

  // ///////////////////////////////////////////////////////////////////////
  // VirtualStackObjectBase_TI<Release>

#define TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS   typename T
#define TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS  T, core_cfg::p_build_config::Release
#define TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TYPE    typename VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    VirtualStackObjectBase_TI(const value_type& a_other)
    : m_value(a_other)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    VirtualStackObjectBase_TI(const this_type& a_other)
    : m_value(a_other.m_value)
    , m_ptr(&m_value)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    ~VirtualStackObjectBase_TI()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TYPE::this_type&
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    operator=(const this_type& a_other)
  {
    this_type(a_other).swap(*this);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  void
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    swap(this_type& a_other)
  {
    using core::swap;

    swap(m_value, a_other.m_value);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TYPE::value_type&
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    operator*()
  { return m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  const TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TYPE::value_type&
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    operator*() const
  { return m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TYPE::pointer
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    operator->()
  { return &m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TYPE::const_pointer
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    operator->() const
  { return &m_value; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TYPE::pointer
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    get()
  { return pointer(&m_value); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TEMPS>
  TLOC_VIRTUAL_STACK_OBJECT_RELEASE_TYPE::const_pointer
    VirtualStackObjectBase_TI<TLOC_VIRTUAL_STACK_OBJECT_RELEASE_PARAMS>::
    get() const
  { return pointer(&m_value); }

};};};

#define TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(_type_)\
  template class tloc::core_sptr::VirtualStackObjectBase_TI<_type_>;\
  template class tloc::core_sptr::VirtualStackObject_T<_type_>

#define TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR(_type_)\
  template class tloc::core_sptr::VirtualStackObjectBase_TI<_type_>;\
  template class tloc::core_sptr::VirtualStackObject_T<_type_, tloc::core_sptr::p_virtual_stack_object::default_ctor::NotAvail>

#define TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_EQUALITY(_type_)\
  template class tloc::core_sptr::VirtualStackObjectBase_TI<_type_>;\
  template class tloc::core_sptr::VirtualStackObject_T<_type_, tloc::core_sptr::p_virtual_stack_object::default_ctor::Available, tloc::core_sptr::p_virtual_stack_object::equality::NotAvail>

#define TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT_NO_DEF_CTOR_AND_EQUALITY(_type_)\
  template class tloc::core_sptr::VirtualStackObjectBase_TI<_type_>;\
  template class tloc::core_sptr::VirtualStackObject_T<_type_, tloc::core_sptr::p_virtual_stack_object::default_ctor::NotAvail, tloc::core_sptr::p_virtual_stack_object::equality::NotAvail>

#endif