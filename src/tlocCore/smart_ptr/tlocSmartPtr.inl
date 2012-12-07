#ifndef _TLOC_CORE_SMART_PTR_INL_
#define _TLOC_CORE_SMART_PTR_INL_

#ifndef _TLOC_CORE_SMART_PTR_H_
#error "Must include header before including the inline file"
#endif

#include "tlocSmartPtr.h"

namespace tloc { namespace core { namespace smart_ptr {

#define SHARED_PTR_TEMPS  typename T
#define SHARED_PTR_PARAMS T
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
    // Mainly for containers
    DoAddRef();
  }

  template <SHARED_PTR_TEMPS>
  template <typename T_Other>
  SharedPtr<SHARED_PTR_PARAMS>::SharedPtr(const SharedPtr<T_Other>& a_other)
    : m_rawPtr  (a_other.Expose() )
    , m_refCount(a_other.DoExposeCounter() )
  {
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
    m_rawPtr = a_other.Expose();
    m_refCount = a_other.DoExposeCounter();
    DoAddRef();

    return *this;
  }

  template <SHARED_PTR_TEMPS>
  template <typename T_Other> void 
  SharedPtr<SHARED_PTR_PARAMS>::CastFrom(const SharedPtr<T_Other>& a_other)
  {
    DoRemoveRef();
    m_rawPtr = static_cast<pointer>(a_other.Expose());
    m_refCount = a_other.DoExposeCounter();
    DoAddRef();
  }

  template <SHARED_PTR_TEMPS>
  SHARED_PTR_TYPE::pointer
  SharedPtr<SHARED_PTR_PARAMS>::Expose() const
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
  SHARED_PTR_TYPE::ref_count_type
  SharedPtr<SHARED_PTR_PARAMS>::GetRefCount() const
  {
    return m_refCount ? *m_refCount : 0;
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
      if (GetRefCount() == 0)
      {
        delete m_rawPtr;
        delete m_refCount;
      }
    }
  }

};};};

#endif