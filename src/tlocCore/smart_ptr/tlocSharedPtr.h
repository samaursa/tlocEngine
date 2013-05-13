#ifndef _TLOC_CORE_SMART_PTR_SHARED_PTR_H_
#define _TLOC_CORE_SMART_PTR_SHARED_PTR_H_

#include <tlocCore/tlocCoreBase.h>

#include <tlocCore/tlocFunctional.h>
#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/smart_ptr/tlocSmartPtr.h>

namespace tloc { namespace core { namespace smart_ptr {

  namespace p_shared_ptr
  {
    namespace null_copy
    {
      struct Allow
      {
        template <typename T_Ptr>
        void CheckNullBeforeCopy(T_Ptr )
        { /* Intentionally Empty */ }

      };

      struct Disallow
      {
        template <typename T_Ptr>
        void CheckNullBeforeCopy(T_Ptr a_rawPtr)
        {
          TLOC_ASSERT_LOW_LEVEL(a_rawPtr != nullptr,
            "Copy of NULL SharedPtr is disabled");
          TLOC_UNUSED(a_rawPtr);
        }
      };
    };
  };

  template
    <
      typename T,
      typename T_NullCopyPolicy = p_shared_ptr::null_copy::Allow
    >
  class SharedPtr
    : public SmartPtr
    , public T_NullCopyPolicy
  {
  public:
    typedef SmartPtr                base_type;

    typedef T                       value_type;
    typedef T_NullCopyPolicy        null_copy_policy_type;

    typedef T*                      pointer;
    typedef T const *               const_pointer;
    typedef T&                      reference;
    typedef T const &               const_reference;

    typedef tl_int                  ref_count_type;

    typedef SharedPtr<value_type, null_copy_policy_type>   this_type;

  public:
    SharedPtr();
    SharedPtr(nullptr_t);
    explicit SharedPtr(pointer a_rawPtr);
    SharedPtr(const this_type& a_other);

    template <typename T_Other, typename T_OtherPolicy>
    SharedPtr(const SharedPtr<T_Other, T_OtherPolicy>& a_other);
    ~SharedPtr();

    template <typename T_Other, typename T_OtherPolicy>
    this_type& operator= (const SharedPtr<T_Other, T_OtherPolicy>& a_other);
    this_type& operator= (this_type a_other);

    ///-------------------------------------------------------------------------
    /// @brief Dangerous to use this. Use SharedPtr<> semantics
    ///-------------------------------------------------------------------------
    pointer       get() const;

    ///-------------------------------------------------------------------------
    /// @brief
    /// Methods for internal use only.
    /// @note
    /// The reason this is not private is because SharedPtr<base> and
    /// SharedPtr<derived> are two different classes but can point to the
    /// same data. To support this we need the pointer to the counter.
    ///
    /// @return Can be a NULL ptr
    ///-------------------------------------------------------------------------
    ref_count_type* DoExposeCounter() const;

    pointer   operator->() const;
    reference operator*() const;
    operator  bool() const;

    ref_count_type use_count() const;
    bool           unique() const;

    void           reset();
    template <typename Y>
    void           reset(Y* a_ptr);

    template <typename T_Other>
    void           swap(SharedPtr<T_Other, null_copy_policy_type>& a_other);
    void           swap(this_type& a_other);

    //------------------------------------------------------------------------
    // friend functions - casting
    template <typename T_T, typename T_T_NullCopyPolicy, typename U>
    friend
    SharedPtr<T_T, T_T_NullCopyPolicy>
      static_pointer_cast(const SharedPtr<U, T_T_NullCopyPolicy>& a_sp);

    template <typename T_Other, typename U>
    friend
    SharedPtr<T_Other>
      static_pointer_cast(const SharedPtr<T_Other>& a_sp);

    template <typename T_T, typename T_T_NullCopyPolicy, typename U>
    friend
    SharedPtr<T_T, T_T_NullCopyPolicy>
      const_pointer_cast(const SharedPtr<U, T_T_NullCopyPolicy>& a_sp);

    template <typename T_Other, typename U>
    friend
    SharedPtr<T_Other>
      const_pointer_cast(const SharedPtr<U>& a_sp);

  private:
    void DoAddRef();
    void DoRemoveRef();

  private:
    pointer           m_rawPtr;
    ref_count_type*   m_refCount;
  };

  //------------------------------------------------------------------------
  // Template definitions

  template <typename T, typename T_NullCopyPolicy>
  template <typename T_Other, typename T_OtherPolicy>
  SharedPtr<T, T_NullCopyPolicy>::
    SharedPtr(const SharedPtr<T_Other, T_OtherPolicy>& a_other)
    : m_rawPtr  (a_other.get() )
    , m_refCount(a_other.DoExposeCounter() )
  {
    // Mainly for containers
    DoAddRef();
  }

  template <typename T, typename T_NullCopyPolicy>
  template <typename Y>
  void SharedPtr<T, T_NullCopyPolicy>::
    reset(Y* a_ptr)
  {
    this_type(a_ptr).swap(*this);
  }

  template <typename T, typename T_NullCopyPolicy>
  template <typename T_Other>
  void SharedPtr<T, T_NullCopyPolicy>::
    swap(SharedPtr<T_Other, T_NullCopyPolicy>& a_other)
  {
    using core::swap;

    swap(m_rawPtr, a_other.m_rawPtr);
    swap(m_refCount, a_other.m_refCount);
  }

  //////////////////////////////////////////////////////////////////////////
  // Global operators

  template <class T, class U>
  bool operator ==(const SharedPtr<T>& a, const SharedPtr<U>& b)
  { return a.get() == b.get(); }

  template <class T, class U>
  bool operator !=(const SharedPtr<T>& a, const SharedPtr<U>& b)
  { return a.get() != b.get(); }

  template <class T, class U>
  bool operator <(const SharedPtr<T>& a, const SharedPtr<U>& b)
  {
    using tloc::core::less;
    using tloc::type_traits::common_type;

    return less<typename common_type<T*, U*>::type>()( a.get(), b.get() );
  }

  template <class T, class U>
  bool operator >(const SharedPtr<T>& a, const SharedPtr<U>& b)
  { return b < a; }

  template <class T, class U>
  bool operator <=(const SharedPtr<T>& a, const SharedPtr<U>& b)
  { return !(b < a); }

  template <class T, class U>
  bool operator >=(const SharedPtr<T>& a, const SharedPtr<U>& b)
  { return !(a < b); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <class T>
  bool operator ==(const SharedPtr<T>& a, nullptr_t)
  { return !a; }

  template <class T>
  bool operator ==(nullptr_t, const SharedPtr<T>& b)
  { return !b; }

  template <class T>
  bool operator !=(const SharedPtr<T>& a, nullptr_t)
  { return (bool)a; }

  template <class T>
  bool operator !=(nullptr_t, const SharedPtr<T>& b)
  { return (bool)b; }

  template <class T>
  bool operator <(const SharedPtr<T>& a, nullptr_t)
  { return tloc::core::less<T*>()(a.get(), nullptr ); }

  template <class T>
  bool operator <(nullptr_t, const SharedPtr<T>& b)
  { return tloc::core::less<T*>()(nullptr, b.get()); }

  template <class T>
  bool operator <=(const SharedPtr<T>& a, nullptr_t)
  { return !(nullptr < a); }

  template <class T>
  bool operator <=(nullptr_t, const SharedPtr<T>& b)
  { return !(b < nullptr); }

  template <class T>
  bool operator >(const SharedPtr<T>& a, nullptr_t)
  { return nullptr <= a; }

  template <class T>
  bool operator >(nullptr_t, const SharedPtr<T>& b)
  { return !(b < nullptr); }

  template <class T>
  bool operator >=(const SharedPtr<T>& a, nullptr_t)
  { return !(a < nullptr); }

  template <class T>
  bool operator >=(nullptr_t, const SharedPtr<T>& b)
  { return !(nullptr < b); }

  //////////////////////////////////////////////////////////////////////////
  // casting

  template <typename T, typename T_NullCopyPolicy, typename U>
  SharedPtr<T, T_NullCopyPolicy>
    static_pointer_cast(const SharedPtr<U, T_NullCopyPolicy>& a_sp)
  {
    typedef SharedPtr<T, T_NullCopyPolicy>   return_type;

    return_type sp;
    sp.m_rawPtr = static_cast<T*>(a_sp.m_rawPtr);
    sp.m_refCount = a_sp.m_refCount;
    sp.DoAddRef();

    return sp;
  }

  template <typename T, typename U>
  SharedPtr<T>
    static_pointer_cast(const SharedPtr<U>& a_sp)
  {
    return core_sptr::static_pointer_cast
      <T, p_shared_ptr::null_copy::Allow>(a_sp);
  }

  template <typename T, typename T_NullCopyPolicy, typename U>
  SharedPtr<T, T_NullCopyPolicy>
    const_pointer_cast(const SharedPtr<U, T_NullCopyPolicy>& a_sp)
  {
    typedef SharedPtr<T, T_NullCopyPolicy>   return_type;

    return_type sp;
    sp.m_rawPtr = const_cast<T*>(a_sp.m_rawPtr);
    sp.m_refCount = a_sp.m_refCount;
    sp.DoAddRef();

    return sp;
  }

  template <typename T, typename U>
  SharedPtr<T>
    const_pointer_cast(const SharedPtr<U>& a_sp)
  {
    return static_pointer_cast<T, p_shared_ptr::null_copy::Allow>(a_sp);
  }

};};};

#define TLOC_TYPEDEF_SHARED_PTR(_type_, _typedef_)\
  typedef tloc::core_sptr::SharedPtr<_type_>  _typedef_##_sptr;\
  typedef tloc::core_sptr::SharedPtr<const _type_>  _typedef_##_const_sptr;\
  typedef tloc::core_sptr::SharedPtr<_type_, \
  tloc::core_sptr::p_shared_ptr::null_copy::Disallow>  _typedef_##_sptr_nonullcopy;\
  typedef tloc::core_sptr::SharedPtr<const _type_, \
  tloc::core_sptr::p_shared_ptr::null_copy::Disallow>  _typedef_##_const_sptr_nonullcopy

#endif