#ifndef _TLOC_CORE_SMART_PTR_SHARED_PTR_INL_
#define _TLOC_CORE_SMART_PTR_SHARED_PTR_INL_

#ifndef _TLOC_CORE_SMART_PTR_SHARED_PTR_H_
#error "Must include header before including the inline file"
#endif

#include "tlocSharedPtr.h"

#include <tlocCore/tlocAssert.h>
#include <tlocCore/smart_ptr/tlocSmartPtr.inl.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>

namespace tloc { namespace core { namespace smart_ptr {

#define SHARED_PTR_TEMPS  typename T, typename T_NullCopyPolicy
#define SHARED_PTR_PARAMS T, T_NullCopyPolicy
#define SHARED_PTR_TYPE   typename SharedPtr<SHARED_PTR_PARAMS>

  template <SHARED_PTR_TEMPS>
  SharedPtr<SHARED_PTR_PARAMS>::
    SharedPtr()
    : m_rawPtr(nullptr)
    , m_refCount(nullptr)
  { }

  template <SHARED_PTR_TEMPS>
  SharedPtr<SHARED_PTR_PARAMS>::
  SharedPtr(std::nullptr_t)
    : m_rawPtr(nullptr)
    , m_refCount(nullptr)
  { }

  template <SHARED_PTR_TEMPS>
  SharedPtr<SHARED_PTR_PARAMS>::
    SharedPtr(pointer a_rawPtr)
    : m_rawPtr(a_rawPtr)
    , m_refCount(a_rawPtr ? new ref_count_type(0) : nullptr)
  {
    DoAddRef();
  }

  template <SHARED_PTR_TEMPS>
  SharedPtr<SHARED_PTR_PARAMS>::
    SharedPtr(const this_type& a_other)
    : m_rawPtr(a_other.m_rawPtr)
    , m_refCount(a_other.m_refCount)
  {
    null_copy_policy_type::CheckNullBeforeCopy((void*)m_rawPtr);
    // Mainly for containers
    DoAddRef();
  }

  template <SHARED_PTR_TEMPS>
  SharedPtr<SHARED_PTR_PARAMS>::
    ~SharedPtr()
  {
      DoRemoveRef();
  }

  template <SHARED_PTR_TEMPS>
  SHARED_PTR_TYPE::this_type&
    SharedPtr<SHARED_PTR_PARAMS>::
    operator= (this_type a_other)
  {
    this->swap(a_other);
    return *this;
  }

  template <SHARED_PTR_TEMPS>
  template <typename T_Other, typename T_OtherPolicy>
  SHARED_PTR_TYPE::this_type&
    SharedPtr<SHARED_PTR_PARAMS>::
    operator= (SharedPtr<T_Other, T_OtherPolicy> a_other)
  {
    // NOTE: Cannot use copy-and-swap here because a_other is a different type
    // and therefore not swappable unless we want to expose everything and
    // then do some ugly casts
    DoRemoveRef();
    m_rawPtr = a_other.get();
    m_refCount = a_other.DoExposeCounter();
    DoAddRef();

    return *this;
  }

  template <SHARED_PTR_TEMPS>
  SHARED_PTR_TYPE::pointer
    SharedPtr<SHARED_PTR_PARAMS>::
    get() const
  { return m_rawPtr; }

  template <SHARED_PTR_TEMPS>
  SHARED_PTR_TYPE::ref_count_type*
    SharedPtr<SHARED_PTR_PARAMS>::
    DoExposeCounter() const
  { return m_refCount; }

  template <SHARED_PTR_TEMPS>
  SHARED_PTR_TYPE::pointer
    SharedPtr<SHARED_PTR_PARAMS>::
    operator->() const
  {
    TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference NULL ptr!");
    return m_rawPtr;
  }

  template <SHARED_PTR_TEMPS>
  SHARED_PTR_TYPE::reference
  SharedPtr<SHARED_PTR_PARAMS>::operator*() const
  {
    TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference NULL ptr!");
    return *m_rawPtr;
  }

  template <SHARED_PTR_TEMPS>
  SharedPtr<SHARED_PTR_PARAMS>::
    operator bool() const
  {
    return get() != nullptr;
  }

  template <SHARED_PTR_TEMPS>
  SHARED_PTR_TYPE::ref_count_type
  SharedPtr<SHARED_PTR_PARAMS>::use_count() const
  {
    return m_refCount ? *m_refCount : 0;
  }

  template <SHARED_PTR_TEMPS>
  bool SharedPtr<SHARED_PTR_PARAMS>::
    unique() const
  {
    return use_count() == 1;
  }

  template <SHARED_PTR_TEMPS>
  void SharedPtr<SHARED_PTR_PARAMS>::
    reset()
  {
    DoRemoveRef();
  }

  template <SHARED_PTR_TEMPS>
  void SharedPtr<SHARED_PTR_PARAMS>::
    swap(this_type& a_other)
  {
    core::swap(a_other.m_rawPtr, m_rawPtr);
    core::swap(a_other.m_refCount, m_refCount);
  }

  template <SHARED_PTR_TEMPS>
  void SharedPtr<SHARED_PTR_PARAMS>::DoAddRef()
  {
    if (m_refCount)
    {
      if (*m_refCount == 0)
      { 
        core_mem::tracking::priv::DoTrackMemoryAddress( (void*) m_rawPtr ); }

      ++*m_refCount;
    }
  }

  template <SHARED_PTR_TEMPS>
  void SharedPtr<SHARED_PTR_PARAMS>::DoRemoveRef()
  {
    if (m_refCount)
    {
      --*m_refCount;
      if (use_count() == 0)
      {
        core_mem::tracking::priv::DoUntrackMemoryAddress( (void*)m_rawPtr);

        delete m_rawPtr;
        delete m_refCount;
      }
    }

    m_rawPtr = nullptr;
    m_refCount = nullptr;
  }

};};};

#define TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(_type_)\
  template class tloc::core_sptr::SharedPtr<_type_>;\
  template class tloc::core_sptr::SharedPtr<const _type_>;\
  template class tloc::core_sptr::SharedPtr<_type_,\
  tloc::core_sptr::p_shared_ptr::null_copy::Disallow>;\
  template class tloc::core_sptr::SharedPtr<const _type_,\
  tloc::core_sptr::p_shared_ptr::null_copy::Disallow>


#endif