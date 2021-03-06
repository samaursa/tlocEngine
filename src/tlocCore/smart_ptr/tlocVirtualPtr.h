#ifndef _TLOC_CORE_SMART_PTR_VIRTUAL_PTR_H_
#define _TLOC_CORE_SMART_PTR_VIRTUAL_PTR_H_

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/smart_ptr/tlocSmartPtr.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.h>
#include <tlocCore/configs/tlocBuildConfig.h>

namespace tloc { namespace core { namespace smart_ptr {

  template <typename T, typename T_BuildConfig = core_cfg::BuildConfig::build_config_type>
  class VirtualPtr
    : public SmartPtr
  {
    template <class U, class T2> friend class VirtualPtr;

  public:
    typedef SmartPtr                                  base_type;

    typedef T                                         value_type;
    typedef T_BuildConfig                             build_config;
    typedef VirtualPtr<value_type, build_config>      this_type;

    typedef T*                                        pointer;
    typedef T const *                                 const_pointer;
    typedef T&                                        reference;
    typedef T const &                                 const_reference;

    typedef tl_long                                   ref_count_type;

  public:
    VirtualPtr();
    VirtualPtr(std::nullptr_t);
    explicit VirtualPtr(const pointer a_rawPtr);
    VirtualPtr(const this_type& a_other);

    template <typename T_Other>
    VirtualPtr(const VirtualPtr<T_Other, build_config>& a_other);

    template <typename T_Other, typename T_Policy>
    explicit VirtualPtr(const SharedPtr<T_Other, T_Policy>& a_other);

    template <typename T_Other>
    explicit VirtualPtr(const UniquePtr<T_Other>& a_other);

    ~VirtualPtr();

    template <typename T_Other>
    this_type&  operator=(VirtualPtr<T_Other, build_config> a_other);

    template <typename T_Other, typename T_Policy>
    this_type&  operator=(const SharedPtr<T_Other, T_Policy>& a_other);

    template <typename T_Other>
    this_type&  operator=(const UniquePtr<T_Other>& a_other);

    this_type&  operator=(this_type a_other);

    pointer             operator->() const;
    reference           operator* () const;

    operator            bool() const;

    // @brief Dangerous to use this, prefer VirtualPtr<> semantics
    pointer             get() const;

    ref_count_type      use_count() const;
    bool                unique() const;
    void                reset();

    template <typename T_Other>
    void                reset(T_Other* a_ptr);

    template <typename T_Other>
    void                swap(VirtualPtr<T_Other, build_config>& a_other);
    void                swap(this_type& a_other);

    // @brief Internal use only. See reasoning in SharedPtr<>
    ref_count_type*     DoExposeCounter() const;

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
    void  DoAddRef();
    void* DoGetTrackablePtrAddress() const;
    void  DoRemoveRef();

  private:
    pointer           m_rawPtr;
    ref_count_type*   m_refCount;
  };

  // -----------------------------------------------------------------------
  // template definitions

  template <typename T, typename T_BuildType>
  template <typename T_Other>
  VirtualPtr<T, T_BuildType>::
    VirtualPtr(const VirtualPtr<T_Other, build_config>& a_other)
    : m_rawPtr(a_other.get())
    , m_refCount(m_rawPtr ? new ref_count_type(0) : nullptr)
  {
    using namespace core_mem::tracking::priv;

    // add the connected address only if it is not already added from other
    // casts
    if (DoIsMemoryAddressTracked((void*)m_rawPtr) == false)
    {
      DoTrackConnectedMemoryAddress( (void*) a_other.get(), (void*) m_rawPtr );
    }
    DoAddRef();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, typename T_BuildType>
  template <typename T_Other, typename T_Policy>
  VirtualPtr<T, T_BuildType>::
    VirtualPtr(const SharedPtr<T_Other, T_Policy>& a_other)
    : m_rawPtr(a_other.get())
    , m_refCount(m_rawPtr ? new ref_count_type(0) : nullptr)
  {
    using namespace core_mem::tracking::priv;

    // add the connected address only if it is not already added from other
    // casts
    if (DoIsMemoryAddressTracked((void*)m_rawPtr) == false)
    {
      DoTrackConnectedMemoryAddress( (void*) a_other.get(), (void*) m_rawPtr );
    }
    DoAddRef();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, typename T_BuildType>
  template <typename T_Other>
  VirtualPtr<T, T_BuildType>::
    VirtualPtr(const UniquePtr<T_Other>& a_other)
    : m_rawPtr(a_other.get())
    , m_refCount(m_rawPtr ? new ref_count_type(0) : nullptr)
  {
    DoAddRef();
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, typename T_BuildType>
  template <typename T_Other>
  typename VirtualPtr<T, T_BuildType>::this_type&
    VirtualPtr<T, T_BuildType>::
    operator= (VirtualPtr<T_Other, build_config> a_other)
  {
    this->swap(a_other);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, typename T_BuildType>
  template <typename T_Other, typename T_Policy>
  typename VirtualPtr<T, T_BuildType>::this_type&
    VirtualPtr<T, T_BuildType>::
    operator= (const SharedPtr<T_Other, T_Policy>& a_other)
  {
    this_type(a_other).swap(*this);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, typename T_BuildType>
  template <typename T_Other>
  typename VirtualPtr<T, T_BuildType>::this_type&
    VirtualPtr<T, T_BuildType>::
    operator= (const UniquePtr<T_Other>& a_other)
  {
    this_type(a_other).swap(*this);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, typename T_BuildType>
  template <typename T_Other>
  void
    VirtualPtr<T, T_BuildType>::
    reset(T_Other* a_ptr)
  {
    this_type(a_ptr).swap(*this);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, typename T_BuildType>
  template <typename T_Other>
  void
    VirtualPtr<T, T_BuildType>::
    swap(VirtualPtr<T_Other, build_config>& a_other)
  {
    core::swap(a_other.m_rawPtr, m_rawPtr);
    core::swap(a_other.m_refCount, m_refCount);
  }

  // -----------------------------------------------------------------------
  // friend functions - casting

  template <typename T_Other, typename build_config, typename U>
  VirtualPtr<T_Other, build_config>
    static_pointer_cast(const VirtualPtr<U, build_config>& a_vp)
  {
    typedef VirtualPtr<T_Other, build_config>    return_type;

    return return_type(static_cast<T_Other*>(a_vp.m_rawPtr));
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T_Other, typename build_config, typename U>
  VirtualPtr<T_Other, build_config>
    const_pointer_cast(const VirtualPtr<U, build_config>& a_vp)
  {
    typedef VirtualPtr<T_Other, build_config>   return_type;

    return return_type(const_cast<T_Other*>(a_vp.m_rawPtr));
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
    VirtualPtr();
    VirtualPtr(std::nullptr_t);
    explicit VirtualPtr(const pointer a_rawPtr);
    VirtualPtr(const this_type& a_other);

    template <typename T_Other>
    VirtualPtr(const VirtualPtr<T_Other, build_config>& a_other);

    template <typename T_Other, typename T_Policy>
    explicit VirtualPtr(const SharedPtr<T_Other, T_Policy>& a_other);

    template <typename T_Other>
    explicit VirtualPtr(const UniquePtr<T_Other>& a_other);

    template <typename T_Other>
    this_type&  operator=(VirtualPtr<T_Other, build_config> a_other);

    template <typename T_Other, typename T_Policy>
    this_type&  operator=(const SharedPtr<T_Other, T_Policy>& a_other);

    template <typename T_Other>
    this_type& operator=(const UniquePtr<T_Other>& a_other);

    this_type& operator=(this_type a_other);

    pointer             operator->() const;
    reference           operator* () const;

    operator            bool() const;

    // @brief Dangerous to use this, prefer VirtualPtr<> semantics
    pointer             get() const;

    ref_count_type      use_count() const;
    bool                unique() const;
    void                reset();

    template <typename T_Other>
    void                reset(T_Other* a_ptr);

    template <typename T_Other>
    void                swap(VirtualPtr<T_Other, build_config>& a_other);
    void                swap(this_type& a_other);

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

  template <typename T>
  template <typename T_Other>
  VirtualPtr<T, core_cfg::p_build_config::Release>::
    VirtualPtr(const VirtualPtr<T_Other, core_cfg::p_build_config::Release>& a_other)
    : m_rawPtr(a_other.get())
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  template <typename T_Other, typename T_Policy>
  VirtualPtr<T, core_cfg::p_build_config::Release>::
    VirtualPtr(const SharedPtr<T_Other, T_Policy>& a_other)
    : m_rawPtr(a_other.get())
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  template <typename T_Other>
  VirtualPtr<T, core_cfg::p_build_config::Release>::
    VirtualPtr(const UniquePtr<T_Other>& a_other)
    : m_rawPtr(a_other.get())
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  template <typename T_Other>
  typename VirtualPtr<T, core_cfg::p_build_config::Release>::this_type&
    VirtualPtr<T, core_cfg::p_build_config::Release>::
    operator= (VirtualPtr<T_Other, build_config> a_other)
  {
    this->swap(a_other);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  template <typename T_Other, typename T_Policy>
  typename VirtualPtr<T, core_cfg::p_build_config::Release>::this_type&
    VirtualPtr<T, core_cfg::p_build_config::Release>::
    operator= (const SharedPtr<T_Other, T_Policy>& a_other)
  {
    this_type(a_other).swap(*this);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  template <typename T_Other>
  typename VirtualPtr<T, core_cfg::p_build_config::Release>::this_type&
    VirtualPtr<T, core_cfg::p_build_config::Release>::
    operator= (const UniquePtr<T_Other>& a_other)
  {
    this_type(a_other).swap(*this);
    return *this;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  template <typename T_Other>
  void
    VirtualPtr<T, core_cfg::p_build_config::Release>::
    reset(T_Other* a_ptr)
  {
    this_type(a_ptr).swap(*this);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  template <typename T_Other>
  void
    VirtualPtr<T, core_cfg::p_build_config::Release>::
    swap(VirtualPtr<T_Other, build_config>& a_other)
  {
    core::swap(a_other.m_rawPtr, m_rawPtr);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

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

  // -----------------------------------------------------------------------
  // Global operators

  template <class T, class U>
  bool operator ==(const VirtualPtr<T>& a, const VirtualPtr<U>& b)
  { return a.get() == b.get(); }

  template <class T, class U>
  bool operator !=(const VirtualPtr<T>& a, const VirtualPtr<U>& b)
  { return a.get() != b.get(); }

  template <class T, class U>
  bool operator <(const VirtualPtr<T>& a, const VirtualPtr<U>& b)
  {
    using tloc::core::less;
    using tloc::type_traits::common_type;

    return less<typename common_type<T*, U*>::type>()( a.get(), b.get() );
  }

  template <class T, class U>
  bool operator >(const VirtualPtr<T>& a, const VirtualPtr<U>& b)
  { return b < a; }

  template <class T, class U>
  bool operator <=(const VirtualPtr<T>& a, const VirtualPtr<U>& b)
  { return !(b < a); }

  template <class T, class U>
  bool operator >=(const VirtualPtr<T>& a, const VirtualPtr<U>& b)
  { return !(a < b); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <class T>
  bool operator ==(const VirtualPtr<T>& a, nullptr_t)
  { return !a; }

  template <class T>
  bool operator ==(nullptr_t, const VirtualPtr<T>& b)
  { return !b; }

  template <class T>
  bool operator !=(const VirtualPtr<T>& a, nullptr_t)
  { return (bool)a; }

  template <class T>
  bool operator !=(nullptr_t, const VirtualPtr<T>& b)
  { return (bool)b; }

  template <class T>
  bool operator <(const VirtualPtr<T>& a, nullptr_t)
  { return tloc::core::less<T*>()(a.get(), nullptr ); }

  template <class T>
  bool operator <(nullptr_t, const VirtualPtr<T>& b)
  { return tloc::core::less<T*>()(nullptr, b.get()); }

  template <class T>
  bool operator <=(const VirtualPtr<T>& a, nullptr_t)
  { return !(nullptr < a); }

  template <class T>
  bool operator <=(nullptr_t, const VirtualPtr<T>& b)
  { return !(b < nullptr); }

  template <class T>
  bool operator >(const VirtualPtr<T>& a, nullptr_t)
  { return nullptr <= a; }

  template <class T>
  bool operator >(nullptr_t, const VirtualPtr<T>& b)
  { return !(b < nullptr); }

  template <class T>
  bool operator >=(const VirtualPtr<T>& a, nullptr_t)
  { return !(a < nullptr); }

  template <class T>
  bool operator >=(nullptr_t, const VirtualPtr<T>& b)
  { return !(nullptr < b); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <class T, class U, class T_NullPolicy>
  bool operator ==(const VirtualPtr<T>& a, const SharedPtr<U, T_NullPolicy>& b)
  { return a.get() == b.get(); }

  template <class T, class U, class T_NullPolicy>
  bool operator ==(const SharedPtr<T, T_NullPolicy>& a, const VirtualPtr<U>& b)
  { return a.get() == b.get(); }

  template <class T, class U, class T_NullPolicy>
  bool operator !=(const VirtualPtr<T>& a, const SharedPtr<U, T_NullPolicy>& b)
  { return a.get() != b.get(); }

  template <class T, class U, class T_NullPolicy>
  bool operator !=(const SharedPtr<T, T_NullPolicy>& a, const VirtualPtr<U>& b)
  { return a.get() != b.get(); }

  template <class T, class U, class T_NullPolicy>
  bool operator < (const VirtualPtr<T>& a, const SharedPtr<U, T_NullPolicy>& b)
  { return a.get() < b.get(); }

  template <class T, class U, class T_NullPolicy>
  bool operator < (const SharedPtr<T, T_NullPolicy>& a, const VirtualPtr<U>& b)
  { return a.get() < b.get(); }

  template <class T, class U, class T_NullPolicy>
  bool operator <= (const VirtualPtr<T>& a, const SharedPtr<U, T_NullPolicy>& b)
  { return a.get() <= b.get(); }

  template <class T, class U, class T_NullPolicy>
  bool operator <= (const SharedPtr<T, T_NullPolicy>& a, const VirtualPtr<U>& b)
  { return a.get() <= b.get(); }

  template <class T, class U, class T_NullPolicy>
  bool operator > (const VirtualPtr<T>& a, const SharedPtr<U, T_NullPolicy>& b)
  { return a.get() > b.get(); }

  template <class T, class U, class T_NullPolicy>
  bool operator > (const SharedPtr<T, T_NullPolicy>& a, const VirtualPtr<U>& b)
  { return a.get() > b.get(); }

  template <class T, class U, class T_NullPolicy>
  bool operator >= (const VirtualPtr<T>& a, const SharedPtr<U, T_NullPolicy>& b)
  { return a.get() >= b.get(); }

  template <class T, class U, class T_NullPolicy>
  bool operator >= (const SharedPtr<T, T_NullPolicy>& a, const VirtualPtr<U>& b)
  { return a.get() >= b.get(); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <class T, class U>
  bool operator ==(const VirtualPtr<T>& a, const UniquePtr<U>& b)
  { return a.get() == b.get(); }

  template <class T, class U>
  bool operator ==(const UniquePtr<T>& a, const VirtualPtr<U>& b)
  { return a.get() == b.get(); }

  template <class T, class U>
  bool operator !=(const VirtualPtr<T>& a, const UniquePtr<U>& b)
  { return a.get() != b.get(); }

  template <class T, class U>
  bool operator !=(const UniquePtr<T>& a, const VirtualPtr<U>& b)
  { return a.get() != b.get(); }

  template <class T, class U>
  bool operator < (const VirtualPtr<T>& a, const UniquePtr<U>& b)
  { return a.get() < b.get(); }

  template <class T, class U>
  bool operator < (const UniquePtr<T>& a, const VirtualPtr<U>& b)
  { return a.get() < b.get(); }

  template <class T, class U>
  bool operator <= (const VirtualPtr<T>& a, const UniquePtr<U>& b)
  { return a.get() <= b.get(); }

  template <class T, class U>
  bool operator <= (const UniquePtr<T>& a, const VirtualPtr<U>& b)
  { return a.get() <= b.get(); }

  template <class T, class U>
  bool operator > (const VirtualPtr<T>& a, const UniquePtr<U>& b)
  { return a.get() > b.get(); }

  template <class T, class U>
  bool operator > (const UniquePtr<T>& a, const VirtualPtr<U>& b)
  { return a.get() > b.get(); }

  template <class T, class U>
  bool operator >= (const VirtualPtr<T>& a, const UniquePtr<U>& b)
  { return a.get() >= b.get(); }

  template <class T, class U>
  bool operator >= (const UniquePtr<T>& a, const VirtualPtr<U>& b)
  { return a.get() >= b.get(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  tl_size GetUseCount(const VirtualPtr<T>& a_vptr)
  { return a_vptr.use_count(); }

  template <typename T>
  VirtualPtr<T>
    ToVirtualPtr(VirtualPtr<T> a_vptr)
  { return a_vptr; }

  template <typename T, typename T_CopyPolicy>
  VirtualPtr<T>
    ToVirtualPtr(const SharedPtr<T, T_CopyPolicy>& a_sptr)
  { return VirtualPtr<T>(a_sptr); }

  template <typename T>
  VirtualPtr<T>
    ToVirtualPtr(const UniquePtr<T>& a_uptr)
  { return VirtualPtr<T>(a_uptr); }

  // -----------------------------------------------------------------------
  // algorithms

  namespace algos {

    namespace virtual_ptr
    {
      struct DeleteAndReset
      {
        template <typename T>
        void operator()(core_sptr::VirtualPtr<T>& a_vptr)
        {
          T* rawPtr = a_vptr.get();
          a_vptr.reset();

          delete rawPtr;
        }
      };
    };

  };

};};};

#define TLOC_TYPEDEF_VIRTUAL_PTR(_type_, _typedef_)\
  typedef tloc::core_sptr::VirtualPtr<_type_>  _typedef_##_vptr;\
  typedef tloc::core_sptr::VirtualPtr<const _type_>  const_##_typedef_##_vptr

#define TLOC_TYPEDEF_THIS_TYPE_VIRTUAL_PTR()\
  typedef tloc::core_sptr::VirtualPtr<this_type>  this_type_vptr;\
  typedef tloc::core_sptr::VirtualPtr<const this_type>  const_this_type_vptr

#define TLOC_EXTERN_TEMPLATE_VIRTUAL_PTR(_type_)\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core_sptr::VirtualPtr<_type_>);\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core_sptr::VirtualPtr<const _type_>)

#endif