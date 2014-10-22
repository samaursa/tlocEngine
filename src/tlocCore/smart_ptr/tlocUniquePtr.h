#ifndef _TLOC_CORE_SMART_PTR_UNIQUE_PTR_H_
#define _TLOC_CORE_SMART_PTR_UNIQUE_PTR_H_

#include <tlocCore/memory/tlocAllocators.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/tlocFunctional.h>
#include <tlocCore/smart_ptr/tlocSmartPtr.h>

namespace tloc { namespace core { namespace smart_ptr {

  namespace p_unique_ptr
  {
  };

  template
    <
      typename T
    >
  class UniquePtr
    : public SmartPtr
  {
  public:
    typedef SmartPtr               base_type;

    typedef T                      value_type;
    typedef T*                     pointer;
    typedef T const *              const_pointer;
    typedef T&                     reference;
    typedef T const &              const_reference;

    typedef UniquePtr<value_type>  this_type;

  public:
    UniquePtr();
    UniquePtr(nullptr_t);
    explicit UniquePtr(pointer a_rawPtr);
    explicit UniquePtr(const this_type& a_other);

    template <typename T_Other>
    explicit UniquePtr(const UniquePtr<T_Other>& a_other);
    ~UniquePtr();

    // This is intentionally commented out - UniquePtr's assignment operator
    // only works with move semantics which is not available in C++03
    //template <typename T_Other>
    //this_type& operator=(const UniquePtr<T_Other>& a_other);
    //this_type& operator=(const this_type& a_other);

    pointer   release(pointer a_ptr = pointer() );
    void      reset(pointer a_ptr = pointer() );
    void      swap(this_type& a_other);

    pointer   get() const;
    operator  bool() const;

    reference operator*() const;
    pointer   operator->() const;

  private:
    void      DoDestroyRawPtr();

    this_type& operator=(const this_type& a_other);

  private:
    pointer   m_rawPtr;

  };

  //------------------------------------------------------------------------
  // template definitions

  template <typename T>
  template <typename T_Other>
  UniquePtr<T>::
    UniquePtr(const UniquePtr<T_Other>& a_other)
    : m_rawPtr( static_cast<pointer>(
                const_cast<UniquePtr<T_Other>* >(&a_other)->release()) )
  { 
    core_mem::tracking::priv::DoTrackMemoryAddress((void*)m_rawPtr);
  }

  //////////////////////////////////////////////////////////////////////////
  // Global operators

  template <class T, class U>
  bool operator ==(const UniquePtr<T>& a, const UniquePtr<U>& b)
  { return a.get() == b.get(); }

  template <class T, class U>
  bool operator !=(const UniquePtr<T>& a, const UniquePtr<U>& b)
  { return a.get() != b.get(); }

  template <class T, class U>
  bool operator <(const UniquePtr<T>& a, const UniquePtr<U>& b)
  {
    using tloc::core::less;
    using tloc::type_traits::common_type;

    return less<typename common_type<T*, U*>::type>()( a.get(), b.get() );
  }

  template <class T, class U>
  bool operator >(const UniquePtr<T>& a, const UniquePtr<U>& b)
  { return b < a; }

  template <class T, class U>
  bool operator <=(const UniquePtr<T>& a, const UniquePtr<U>& b)
  { return !(b < a); }

  template <class T, class U>
  bool operator >=(const UniquePtr<T>& a, const UniquePtr<U>& b)
  { return !(a < b); }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <class T>
  bool operator ==(const UniquePtr<T>& a, nullptr_t)
  { return !a; }

  template <class T>
  bool operator ==(nullptr_t, const UniquePtr<T>& b)
  { return !b; }

  template <class T>
  bool operator !=(const UniquePtr<T>& a, nullptr_t)
  { return (bool)a; }

  template <class T>
  bool operator !=(nullptr_t, const UniquePtr<T>& b)
  { return (bool)b; }

  template <class T>
  bool operator <(const UniquePtr<T>& a, nullptr_t)
  { return tloc::core::less<T*>()(a.get(), nullptr ); }

  template <class T>
  bool operator <(nullptr_t, const UniquePtr<T>& b)
  { return tloc::core::less<T*>()(nullptr, b.get()); }

  template <class T>
  bool operator <=(const UniquePtr<T>& a, nullptr_t)
  { return !(nullptr < a); }

  template <class T>
  bool operator <=(nullptr_t, const UniquePtr<T>& b)
  { return !(b < nullptr); }

  template <class T>
  bool operator >(const UniquePtr<T>& a, nullptr_t)
  { return nullptr <= a; }

  template <class T>
  bool operator >(nullptr_t, const UniquePtr<T>& b)
  { return !(b < nullptr); }

  template <class T>
  bool operator >=(const UniquePtr<T>& a, nullptr_t)
  { return !(a < nullptr); }

  template <class T>
  bool operator >=(nullptr_t, const UniquePtr<T>& b)
  { return !(nullptr < b); }

  // -----------------------------------------------------------------------
  // swap

  template <typename T>
  void swap(UniquePtr<T>& a, UniquePtr<T>& b)
  { a.swap(b); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  tl_size GetUseCount(const UniquePtr<T>& a_uptr)
  {
    return a_uptr == nullptr ? 0 : 1;
  }

};};};

#define TLOC_TYPEDEF_UNIQUE_PTR(_type_, _typedef_)\
  typedef tloc::core_sptr::UniquePtr<_type_>  _typedef_##_uptr;\
  typedef tloc::core_sptr::UniquePtr<const _type_>  const_##_typedef_##_uptr

#define TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(_type_)\
  TLOC_EXTERN_TEMPLATE(tloc::core_sptr::UniquePtr<_type_>);\
  TLOC_EXTERN_TEMPLATE(tloc::core_sptr::UniquePtr<const _type_>)

#endif