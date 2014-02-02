#ifndef _TLOC_CORE_SMART_PTR_VIRTUAL_PTR_INL_
#define _TLOC_CORE_SMART_PTR_VIRTUAL_PTR_INL_

#ifndef _TLOC_CORE_SMART_PTR_VIRTUAL_PTR_H_
#error "Must include header before including the inline file"
#endif

#include "tlocVirtualPtr.h"

namespace tloc { namespace core { namespace smart_ptr {

#define TLOC_VIRTUAL_PTR_TEMPS  typename T, typename T_BuildConfig
#define TLOC_VIRTUAL_PTR_PARAMS T, T_BuildConfig
#define TLOC_VIRTUAL_PTR_TYPE   typename VirtualPtr<T, T_BuildConfig>

  // ///////////////////////////////////////////////////////////////////////
  // VirtualPtr<>

  template <TLOC_VIRTUAL_PTR_TEMPS>
  VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    VirtualPtr()
    : m_rawPtr(nullptr)
    , m_refCount(nullptr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    VirtualPtr(std::nullptr_t)
    : m_rawPtr(nullptr)
    , m_refCount(nullptr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    VirtualPtr(pointer a_rawPtr)
    : m_rawPtr(a_rawPtr)
    , m_refCount(a_rawPtr ? new ref_count_type(0) : nullptr)
  {
    DoAddRef();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    VirtualPtr(const this_type& a_other)
    : m_rawPtr(a_other.m_rawPtr)
    , m_refCount(a_other.m_refCount)
  {
    DoAddRef();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    ~VirtualPtr()
  {
    DoRemoveRef();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  TLOC_VIRTUAL_PTR_TYPE::this_type&
    VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    operator=(this_type a_other)
  {
    this->swap(a_other);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  TLOC_VIRTUAL_PTR_TYPE::pointer
    VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    operator->() const
  {
    TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference nullptr");
    return m_rawPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  TLOC_VIRTUAL_PTR_TYPE::reference
    VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    operator*() const
  {
    TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference nullptr");
    return *m_rawPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    operator bool() const
  { return get() != nullptr; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  TLOC_VIRTUAL_PTR_TYPE::pointer
    VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    get() const
  {
    return m_rawPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  TLOC_VIRTUAL_PTR_TYPE::ref_count_type
    VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    use_count() const
  {
    return m_refCount ? *m_refCount : 0;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  bool
    VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    unique() const
  {
    return use_count() == 1;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  void
    VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    reset()
  { DoRemoveRef(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  void
    VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    swap(this_type& a_other)
  {
    core::swap(a_other.m_rawPtr, m_rawPtr);
    core::swap(a_other.m_refCount, m_refCount);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  TLOC_VIRTUAL_PTR_TYPE::ref_count_type*
    VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    DoExposeCounter() const
  {
    return m_refCount;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  void
    VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    DoAddRef()
  {
    if (m_refCount)
    {
      if (*m_refCount == 0)
      { priv::DoAddVirtualPtrRef( (void*) m_rawPtr); }

      ++*m_refCount;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_TEMPS>
  void
    VirtualPtr<TLOC_VIRTUAL_PTR_PARAMS>::
    DoRemoveRef()
  {
    if (m_refCount)
    {
      --*m_refCount;
      if (use_count() == 0)
      {
        priv::DoRemoveVirtualPtrRef( (void*) m_rawPtr);
        delete m_refCount;
      }
    }

    m_rawPtr = nullptr;
    m_refCount = nullptr;
  }

  // ///////////////////////////////////////////////////////////////////////
  // VirtualPtr<Release>

#define TLOC_VIRTUAL_PTR_RELEASE_TEMPS  typename T
#define TLOC_VIRTUAL_PTR_RELEASE_PARAMS T, core_cfg::p_build_config::Release
#define TLOC_VIRTUAL_PTR_RELEASE_TYPE   typename VirtualPtr<T, core_cfg::p_build_config::Release>

  template <TLOC_VIRTUAL_PTR_RELEASE_TEMPS>
  VirtualPtr<TLOC_VIRTUAL_PTR_RELEASE_PARAMS>::
    VirtualPtr()
    : m_rawPtr(nullptr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_RELEASE_TEMPS>
  VirtualPtr<TLOC_VIRTUAL_PTR_RELEASE_PARAMS>::
    VirtualPtr(std::nullptr_t)
    : m_rawPtr(nullptr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_RELEASE_TEMPS>
  VirtualPtr<TLOC_VIRTUAL_PTR_RELEASE_PARAMS>::
    VirtualPtr(pointer a_rawPtr)
    : m_rawPtr(a_rawPtr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_RELEASE_TEMPS>
  VirtualPtr<TLOC_VIRTUAL_PTR_RELEASE_PARAMS>::
    VirtualPtr(const this_type& a_other)
    : m_rawPtr(a_other.m_rawPtr)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_RELEASE_TEMPS>
  TLOC_VIRTUAL_PTR_RELEASE_TYPE::this_type&
    VirtualPtr<TLOC_VIRTUAL_PTR_RELEASE_PARAMS>::
    operator= (this_type a_other)
  {
    m_rawPtr = a_other.get();

    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_RELEASE_TEMPS>
  TLOC_VIRTUAL_PTR_RELEASE_TYPE::pointer
    VirtualPtr<TLOC_VIRTUAL_PTR_RELEASE_PARAMS>::
    get() const
  {
    return m_rawPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_RELEASE_TEMPS>
  TLOC_VIRTUAL_PTR_RELEASE_TYPE::pointer
    VirtualPtr<TLOC_VIRTUAL_PTR_RELEASE_PARAMS>::
    operator->() const
  {
    TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference nullptr");
    return m_rawPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_RELEASE_TEMPS>
  TLOC_VIRTUAL_PTR_RELEASE_TYPE::reference
    VirtualPtr<TLOC_VIRTUAL_PTR_RELEASE_PARAMS>::
    operator*() const
  {
    TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference nullptr");
    return *m_rawPtr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_RELEASE_TEMPS>
  VirtualPtr<TLOC_VIRTUAL_PTR_RELEASE_PARAMS>::
    operator bool() const
  { return get() != nullptr; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_RELEASE_TEMPS>
  TLOC_VIRTUAL_PTR_RELEASE_TYPE::ref_count_type
    VirtualPtr<TLOC_VIRTUAL_PTR_RELEASE_PARAMS>::
    use_count() const
  { return 1; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_RELEASE_TEMPS>
  bool
    VirtualPtr<TLOC_VIRTUAL_PTR_RELEASE_PARAMS>::
    unique() const
  { return true; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_RELEASE_TEMPS>
  void
    VirtualPtr<TLOC_VIRTUAL_PTR_RELEASE_PARAMS>::
    reset()
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <TLOC_VIRTUAL_PTR_RELEASE_TEMPS>
  void
    VirtualPtr<TLOC_VIRTUAL_PTR_RELEASE_PARAMS>::
    swap(this_type& a_other)
  {
    core::swap(a_other.m_rawPtr, m_rawPtr);
  }

};};};

#endif