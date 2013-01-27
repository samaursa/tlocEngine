#ifndef _TLOC_CORE_SMART_PTR_UNIQUE_PTR_INL_
#define _TLOC_CORE_SMART_PTR_UNIQUE_PTR_INL_

#ifndef _TLOC_CORE_SMART_PTR_UNIQUE_PTR_H_
#error "Must include header before including the inline file"
#endif

#include "tlocUniquePtr.h"
#include <tlocCore/smart_ptr/tlocSmartPtr.inl>
#include <tlocCore/smart_ptr/tlocSmartPtrTracker.h>

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl>

namespace tloc { namespace core { namespace smart_ptr {

#define UNIQUE_PTR_TEMPS  typename T
#define UNIQUE_PTR_PARAMS T
#define UNIQUE_PTR_TYPE   typename UniquePtr<UNIQUE_PTR_PARAMS>

  template <UNIQUE_PTR_TEMPS>
  UniquePtr<UNIQUE_PTR_PARAMS>::
    UniquePtr()
    : m_rawPtr(nullptr)
  { }

  template <UNIQUE_PTR_TEMPS>
  UniquePtr<UNIQUE_PTR_PARAMS>::
    UniquePtr(nullptr_t)
    : m_rawPtr(nullptr)
  { }

  template <UNIQUE_PTR_TEMPS>
  UniquePtr<UNIQUE_PTR_PARAMS>::
    UniquePtr(pointer a_rawPtr)
    : m_rawPtr(a_rawPtr)
  { 
    priv::DoStartTrackingPtr( (void*)a_rawPtr);
  }

  template <UNIQUE_PTR_TEMPS>
  UniquePtr<UNIQUE_PTR_PARAMS>::
    UniquePtr(const this_type& a_other)
    : m_rawPtr( const_cast<this_type*>(&a_other)->release() )
  { }

  template <UNIQUE_PTR_TEMPS>
  template <typename T_Other>
  UniquePtr<UNIQUE_PTR_PARAMS>::
    UniquePtr(const UniquePtr<T_Other>& a_other)
    : m_rawPtr( static_cast<pointer>(a_other.release()) )
  { }

  template <UNIQUE_PTR_TEMPS>
  UniquePtr<UNIQUE_PTR_PARAMS>::
    ~UniquePtr()
  {
    DoDestroyRawPtr();
  }

  //template <UNIQUE_PTR_TEMPS>
  //template <typename T_Other>
  //UNIQUE_PTR_TYPE::this_type& UniquePtr<UNIQUE_PTR_PARAMS>::
  //  operator= (const UniquePtr<T_Other>& a_other)
  //{
  //  m_rawPtr = const_cast<this_type*>(&a_other)->release();
  //}

  //template <UNIQUE_PTR_TEMPS>
  //UNIQUE_PTR_TYPE::this_type& UniquePtr<UNIQUE_PTR_PARAMS>::
  //  operator= (const this_type& a_other)
  //{
  //  m_rawPtr = const_cast<this_type*>(&a_other)->release();
  //}

  template <UNIQUE_PTR_TEMPS>
  UNIQUE_PTR_TYPE::pointer  UniquePtr<UNIQUE_PTR_PARAMS>::
    release(pointer a_ptr)
  {
    pointer toReturn = m_rawPtr;
    m_rawPtr = a_ptr;
    return toReturn;
  }

  template <UNIQUE_PTR_TEMPS>
  void UniquePtr<UNIQUE_PTR_PARAMS>::
    reset(pointer a_ptr)
  {
    DoDestroyRawPtr();
    this_type(a_ptr).swap(*this);
  }

  template <UNIQUE_PTR_TEMPS>
  void UniquePtr<UNIQUE_PTR_PARAMS>::
    swap(this_type& a_other)
  {
    tlSwap(a_other.m_rawPtr, m_rawPtr);
  }

  template <UNIQUE_PTR_TEMPS>
  UNIQUE_PTR_TYPE::pointer  UniquePtr<UNIQUE_PTR_PARAMS>::
    get() const
  {
    return m_rawPtr;
  }

  template <UNIQUE_PTR_TEMPS>
  UniquePtr<UNIQUE_PTR_PARAMS>::
    operator bool() const
  {
    return get() != nullptr;
  }

  template <UNIQUE_PTR_TEMPS>
  UNIQUE_PTR_TYPE::reference UniquePtr<UNIQUE_PTR_PARAMS>::
    operator*() const
  {
    TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference NULL ptr!");
    return *m_rawPtr;
  }

  template <UNIQUE_PTR_TEMPS>
  UNIQUE_PTR_TYPE::pointer UniquePtr<UNIQUE_PTR_PARAMS>::
    operator->() const
  {
    TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference NULL ptr!");
    return m_rawPtr;
  }

  template <UNIQUE_PTR_TEMPS>
  void UniquePtr<UNIQUE_PTR_PARAMS>::
    DoDestroyRawPtr()
  {
    if (m_rawPtr)
    { 
      priv::DoStopTrackingPtr( (void*)m_rawPtr);
      delete m_rawPtr;
      m_rawPtr = nullptr;
    }
  }

};};};

#endif