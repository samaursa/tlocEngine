#ifndef _TLOC_CORE_SMART_PTR_VIRTUAL_PTR_H_
#define _TLOC_CORE_SMART_PTR_VIRTUAL_PTR_H_

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/smart_ptr/tlocSmartPtr.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocSmartPtrTracker.h>
#include <tlocCore/configs/tlocBuildConfig.h>

namespace tloc { namespace core { namespace smart_ptr {

  template <typename T, typename T_BuildConfig = core_cfg::BuildConfig::build_config_type>
  class VirtualPtr
    : public SmartPtr
  {
  public:
    typedef SmartPtr                                  base_type;

    typedef T                                         value_type;
    typedef T_BuildConfig                             build_config;
    typedef VirtualPtr<value_type, build_config>  this_type;

    typedef T*                                        pointer;
    typedef T const *                                 const_pointer;
    typedef T&                                        reference;
    typedef T const &                                 const_reference;

    typedef tl_long                                   ref_count_type;

  public:
    VirtualPtr()
      : m_rawPtr(nullptr)
      , m_refCount(nullptr)
    { }

    VirtualPtr(std::nullptr_t)
      : m_rawPtr(nullptr)
      , m_refCount(nullptr)
    { }

    explicit VirtualPtr(pointer a_rawPtr)
      : m_rawPtr(a_rawPtr)
      , m_refCount(a_rawPtr ? new ref_count_type(0) : nullptr)
    {
      DoAddRef();
    }

    VirtualPtr(const this_type& a_other)
      : m_rawPtr(a_other.m_rawPtr)
      , m_refCount(a_other.m_refCount)
    {
      DoAddRef();
    }

    template <typename T_Other>
    VirtualPtr(const VirtualPtr<T_Other, build_config>& a_other)
      : m_rawPtr(a_other.get())
      , m_refCount(a_other.DoExposeCounter() )
    {
      DoAddRef();
    }

    template <typename T_Other, typename T_Policy>
    explicit VirtualPtr(const SharedPtr<T_Other, T_Policy>& a_other)
      : m_rawPtr(a_other.get())
      , m_refCount(m_rawPtr ? new ref_count_type(0) : nullptr)
    {
      DoAddRef();
    }

    ~VirtualPtr()
    {
      DoRemoveRef();
    }

    template <typename T_Other>
    this_type&          operator= (VirtualPtr<T_Other,
                                                  build_config> a_other)
    {
      this->swap(a_other);
      return *this;
    }

    template <typename T_Other, typename T_Policy>
    this_type&          operator= (const SharedPtr<T_Other, T_Policy>& a_other)
    {
      this_type(a_other).swap(*this);
      return *this;
    }

    this_type&          operator= (this_type a_other)
    {
      this->swap(a_other);
      return *this;
    }

    // @brief Dangerous to use this, prefer VirtualPtr<> semantics
    pointer             get() const
    {
      return m_rawPtr;
    }

    // @brief Internal use only. See reasoning in SharedPtr<>
    ref_count_type*     DoExposeCounter() const
    {
      return m_refCount;
    }

    pointer             operator->() const
    {
      TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference nullptr");
      return m_rawPtr;
    }

    reference           operator* () const
    {
      TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference nullptr");
      return *m_rawPtr;
    }

    operator            bool() const
    { return get() != nullptr; }

    ref_count_type      use_count() const
    {
      return m_refCount ? *m_refCount : 0;
    }

    bool                unique() const
    {
      return use_count() == 1;
    }

    void                reset()
    {
      DoRemoveRef();
    }

    template <typename Y>
    void                reset(Y* a_ptr)
    {
      this_type(a_ptr).swap(*this);
    }

    template <typename T_Other>
    void                swap(VirtualPtr<T_Other, build_config>& a_other)
    {
      core::swap(a_other.m_rawPtr, m_rawPtr);
      core::swap(a_other.m_refCount, m_refCount);
    }

    void                swap(this_type& a_other)
    {
      core::swap(a_other.m_rawPtr, m_rawPtr);
      core::swap(a_other.m_refCount, m_refCount);
    }

    // -----------------------------------------------------------------------
    // friend functions - casting
    template <typename T_Other, typename build_config, typename U>
    friend
      VirtualPtr<T_Other, build_config>
      static_pointer_cast(const VirtualPtr<U, build_config>& a_vp);

    template <typename T_Other, typename build_config, typename U>
    friend
      VirtualPtr<T_Other, build_config>
      const_pointer_cast(const VirtualPtr<U, build_config>& a_vp);

  private:
    void DoAddRef()
    {
      if (m_refCount)
      {
        if (*m_refCount == 0)
        { priv::DoAddVirtualPtrRef( (void*) m_rawPtr); }

        ++*m_refCount;
      }
    }

    void DoRemoveRef()
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

  private:
    pointer           m_rawPtr;
    ref_count_type*   m_refCount;
  };

  // -----------------------------------------------------------------------
  // template definitions

  //template <typename T, typename T_BuildType>
  //template <typename T_Other, typename T_OtherBuildType>
  //VirtualPtr<T, T_BuildType>::
  //  VirtualPtr(const VirtualPtr<T_Other, T_OtherBuildType& a_other)

  // -----------------------------------------------------------------------
  // friend functions - casting
  template <typename T_Other, typename build_config, typename U>
  VirtualPtr<T_Other, build_config>
    static_pointer_cast(const VirtualPtr<U, build_config>& a_vp)
  {
    typedef VirtualPtr<T_Other, build_config>    return_type;

    return_type vp;
    vp.m_rawPtr = static_cast<T_Other*>(a_vp.m_rawPtr);
    vp.m_refCount = a_vp.m_refCount;
    vp.DoAddRef();

    return vp;
  }

  template <typename T_Other, typename build_config, typename U>
  VirtualPtr<T_Other, build_config>
    const_pointer_cast(const VirtualPtr<U, build_config>& a_vp)
  {
    typedef VirtualPtr<T_Other, build_config>   return_type;

    return_type vp;
    vp.m_rawPtr = const_cast<T_Other*>(a_vp.m_rawPtr);
    vp.m_refCount = a_vp.m_refCount;
    vp.DoAddRef();

    return vp;
  }

  // ///////////////////////////////////////////////////////////////////////
  // VirtualPtr<Release>

  template <typename T>
  class VirtualPtr<T, core_cfg::p_build_config::Release>
    : public SmartPtr
  {
  public:
    typedef SmartPtr                                  base_type;

    typedef T                                         value_type;
    typedef core_cfg::p_build_config::Release         build_config;
    typedef VirtualPtr<value_type, build_config>  this_type;

    typedef T*                                        pointer;
    typedef T const *                                 const_pointer;
    typedef T&                                        reference;
    typedef T const &                                 const_reference;

    typedef tl_int                                    ref_count_type;

  public:
    VirtualPtr()
      : m_rawPtr(nullptr)
    { }

    VirtualPtr(std::nullptr_t)
      : m_rawPtr(nullptr)
    { }

    explicit VirtualPtr(pointer a_rawPtr)
      : m_rawPtr(a_rawPtr)
    { }

    VirtualPtr(const this_type& a_other)
      : m_rawPtr(a_other.m_rawPtr)
    { }

    template <typename T_Other>
    VirtualPtr(const VirtualPtr<T_Other, build_config>& a_other)
      : m_rawPtr(a_other.get())
    { }

    template <typename T_Other, typename T_Policy>
    explicit VirtualPtr(const SharedPtr<T_Other, T_Policy>& a_other)
      : m_rawPtr(a_other.get())
    { }

    template <typename T_Other>
    this_type&          operator= (const VirtualPtr<T_Other,
                                                        build_config>& a_other)
    {
      m_rawPtr = a_other.get();

      return *this;
    }

    template <typename T_Other, typename T_Policy>
    this_type&          operator= (const SharedPtr<T_Other, T_Policy>& a_other)
    {
      m_rawPtr = a_other.get();

      return *this;
    }

    this_type&          operator= (this_type a_other)
    {
      m_rawPtr = a_other.get();

      return *this;
    }

    // @brief Dangerous to use this, prefer VirtualPtr<> semantics
    pointer             get() const
    {
      return m_rawPtr;
    }

    // @brief Internal use only. See reasoning in SharedPtr<>
    ref_count_type*     DoExposeCounter() const
    {
      return m_refCount;
    }

    pointer             operator->() const
    {
      TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference nullptr");
      return m_rawPtr;
    }

    reference           operator* () const
    {
      TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference nullptr");
      return *m_rawPtr;
    }

    operator            bool() const
    { return get() != nullptr; }

    ref_count_type      use_count() const
    { return 0; }

    bool                unique() const
    { return true; }

    void                reset()
    { }

    template <typename Y>
    void                reset(Y* a_ptr)
    {
      this_type(a_ptr).swap(*this);
    }

    template <typename T_Other>
    void                swap(VirtualPtr<T_Other, build_config>& a_other)
    {
      core::swap(a_other.m_rawPtr, m_rawPtr);
    }

    void                swap(this_type& a_other)
    {
      core::swap(a_other.m_rawPtr, m_rawPtr);
    }

    // -----------------------------------------------------------------------
    // friend functions - casting
    template <typename T_Other, typename U>
    friend
      VirtualPtr<T_Other, core_cfg::p_build_config::Release>
      static_pointer_cast
      (const VirtualPtr<U, core_cfg::p_build_config::Release>& a_vp);

    template <typename T_Other, typename U>
    friend
      VirtualPtr<T_Other, core_cfg::p_build_config::Release>
      const_pointer_cast
      (const VirtualPtr<U, core_cfg::p_build_config::Release>& a_vp);

  private:
    pointer           m_rawPtr;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T_Other, typename U>
  VirtualPtr<T_Other, core_cfg::p_build_config::Release>
    static_pointer_cast
    (const VirtualPtr<U, core_cfg::p_build_config::Release>& a_vp)
  {
    typedef VirtualPtr
      <T_Other, core_cfg::p_build_config::Release>   return_type;

    return_type vp;
    vp.m_rawPtr = static_cast<T_Other*>(a_vp.m_rawPtr);

    return vp;
  }

  template <typename T_Other, typename U>
  VirtualPtr<T_Other, core_cfg::p_build_config::Release>
    const_pointer_cast
    (const VirtualPtr<U, core_cfg::p_build_config::Release>& a_vp)
  {
    typedef VirtualPtr
      <T_Other, core_cfg::p_build_config::Release>   return_type;

    return_type vp;
    vp.m_rawPtr = const_cast<T_Other*>(a_vp.m_rawPtr);

    return vp;
  }

};};};

#endif