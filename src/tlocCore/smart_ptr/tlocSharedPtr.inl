#ifndef _TLOC_CORE_SMART_PTR_SHARED_PTR_INL_
#define _TLOC_CORE_SMART_PTR_SHARED_PTR_INL_

#ifndef _TLOC_CORE_SMART_PTR_SHARED_PTR_H_
#error "Must include header before including the inline file"
#endif

#include "tlocSharedPtr.h"
#include <tlocCore/smart_ptr/tlocSmartPtr.inl>

namespace tloc { namespace core { namespace smart_ptr {

#define SHARED_PTR_TEMPS  typename T, typename T_NullCopyPolicy 
#define SHARED_PTR_PARAMS T, T_NullCopyPolicy
#define SHARED_PTR_TYPE   typename SharedPtr<SHARED_PTR_PARAMS>

  template <SHARED_PTR_TEMPS>
  SharedPtr<SHARED_PTR_PARAMS>::SharedPtr() 
    : m_rawPtr(nullptr) , m_refCount(nullptr)
  { }

  template <SHARED_PTR_TEMPS>
  SharedPtr<SHARED_PTR_PARAMS>::SharedPtr(pointer a_rawPtr)
    : m_rawPtr(a_rawPtr)
    , m_refCount(a_rawPtr ? new ref_count_type(0) : nullptr)
  {
    DoAddRef();
  }

  template <SHARED_PTR_TEMPS>
  SharedPtr<SHARED_PTR_PARAMS>::SharedPtr(const this_type& a_other)
    : m_rawPtr(a_other.m_rawPtr), m_refCount(a_other.m_refCount)
  {
    CheckNullBeforeCopy(m_rawPtr);
    // Mainly for containers
    DoAddRef();
  }

  template <SHARED_PTR_TEMPS>
  SharedPtr<SHARED_PTR_PARAMS>::~SharedPtr()
  {
      DoRemoveRef();
  }

  template <SHARED_PTR_TEMPS>
  SHARED_PTR_TYPE::this_type&
  SharedPtr<SHARED_PTR_PARAMS>::operator= (const this_type& a_other)
  {
    DoRemoveRef();
    m_rawPtr = a_other.m_rawPtr;
    m_refCount = a_other.m_refCount;
    DoAddRef();

    return *this;
  }

  template <SHARED_PTR_TEMPS>
  template <typename T_Other>
  SHARED_PTR_TYPE::this_type&
  SharedPtr<SHARED_PTR_PARAMS>::operator= (const SharedPtr<T_Other>& a_other)
  {
    DoRemoveRef();
    m_rawPtr = a_other.get();
    m_refCount = a_other.DoExposeCounter();
    DoAddRef();

    return *this;
  }

  template <SHARED_PTR_TEMPS>
  SHARED_PTR_TYPE::pointer
  SharedPtr<SHARED_PTR_PARAMS>::get() const
  { return m_rawPtr; }

  template <SHARED_PTR_TEMPS>
  SHARED_PTR_TYPE::ref_count_type*
  SharedPtr<SHARED_PTR_PARAMS>::DoExposeCounter() const
  { return m_refCount; }

  template <SHARED_PTR_TEMPS>
  SHARED_PTR_TYPE::pointer
  SharedPtr<SHARED_PTR_PARAMS>::operator->() const
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
  template <typename Y>
  void SharedPtr<SHARED_PTR_PARAMS>::
    reset(Y* a_ptr) 
  {
    *this = this_type(a_ptr);
  }

  template <SHARED_PTR_TEMPS>
  void SharedPtr<SHARED_PTR_PARAMS>::DoAddRef()
  {
    if (m_refCount)
    { ++*m_refCount; }
  }

  template <SHARED_PTR_TEMPS>
  void SharedPtr<SHARED_PTR_PARAMS>::DoRemoveRef()
  {
    if (m_refCount)
    {
      --*m_refCount;
      if (use_count() == 0)
      {
        delete m_rawPtr; m_rawPtr = nullptr;
        delete m_refCount;
      }
    }
  }

};};};

#endif