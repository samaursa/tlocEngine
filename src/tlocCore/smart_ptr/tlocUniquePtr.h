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
    // for accessing a_other's m_rawPtr
    template <typename U> friend class UniquePtr;

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
    UniquePtr(const this_type& a_other);
    UniquePtr(this_type&& a_other);
    explicit UniquePtr(pointer a_rawPtr);

    template <typename T_Other>
    UniquePtr(UniquePtr<T_Other>&& a_other);
    ~UniquePtr();

    template <typename T_Other>
    this_type& operator=(UniquePtr<T_Other>&& a_other);
    this_type& operator=(this_type&& a_other);
    this_type& operator=(const this_type& a_other);

    pointer   release(pointer a_ptr = pointer() );
    void      reset(pointer a_ptr = pointer() );
    void      swap(this_type& a_other);

    pointer   get() const;
    operator  bool() const;

    reference operator*() const;
    pointer   operator->() const;

  public:
    //------------------------------------------------------------------------
    // friend functions - casting
    template <typename T_Other, typename U>
    friend
    UniquePtr<T_Other>
      static_pointer_cast(UniquePtr<U>& a_sp);

    template <typename T_Other, typename U>
    friend
    UniquePtr<T_Other>
      const_pointer_cast(const UniquePtr<U>& a_sp);

  private:
    void      DoDestroyRawPtr();

  private:
    pointer   m_rawPtr;

  };

  //------------------------------------------------------------------------
  // template definitions

  template <typename T>
  template <typename T_Other>
  UniquePtr<T>::
    UniquePtr(UniquePtr<T_Other>&& a_other)
    : m_rawPtr( static_cast<pointer>(a_other.m_rawPtr) )
  { a_other.m_rawPtr = nullptr; }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  template <typename T_Other>
  typename UniquePtr<T>::this_type& 
    UniquePtr<T>::
    operator= (UniquePtr<T_Other>&& a_other)
  {
    delete release();
    m_rawPtr = static_cast<pointer>(a_other.m_rawPtr);
    a_other.m_rawPtr = nullptr;
    return *this;
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

  // -----------------------------------------------------------------------
  // casting

  template <typename T, typename U>
  UniquePtr<T>
    static_pointer_cast(UniquePtr<U>& a_ptr)
  {
    typedef UniquePtr<T>   return_type;

    return_type ptr;
    U* rawPtr = a_ptr.m_rawPtr;
    a_ptr.m_rawPtr = nullptr;
    ptr.m_rawPtr = static_cast<T*>(rawPtr);

    return ptr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, typename U>
  UniquePtr<T>
    const_pointer_cast(const UniquePtr<U>& a_ptr)
  {
    typedef UniquePtr<T>   return_type;

    return_type ptr;
    U* rawPtr = a_ptr.m_rawPtr;
    const_cast<UniquePtr<U>*>(&a_ptr)->m_rawPtr = nullptr;
    ptr.m_rawPtr = static_cast<T*>(rawPtr);

    return ptr;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T>
  tl_size GetUseCount(const UniquePtr<T>& a_uptr)
  {
    return a_uptr == nullptr ? 0 : 1;
  }

  // ///////////////////////////////////////////////////////////////////////
  // MakeUnique

  template <typename T>
  UniquePtr<T>
    MakeUnique()
  { return UniquePtr<T>(new T()); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, 
            typename P1>
  UniquePtr<T>
    MakeUnique(P1&& a)
  { return UniquePtr<T>(new T(a)); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, 
            typename P1, typename P2>
  UniquePtr<T>
    MakeUnique(P1&& a, P2&& b)
  { return UniquePtr<T>(new T(a, b)); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, 
            typename P1, typename P2, typename P3>
  UniquePtr<T>
    MakeUnique(P1&& a, P2&& b, P3&& c)
  { return UniquePtr<T>(new T(a, b, c)); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, 
            typename P1, typename P2, typename P3, typename P4>
  UniquePtr<T>
    MakeUnique(P1&& a, P2&& b, P3&& c, P4&& d)
  { return UniquePtr<T>(new T(a, b, c, d)); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, 
            typename P1, typename P2, typename P3, typename P4,
            typename P5>
  UniquePtr<T>
    MakeUnique(P1&& a, P2&& b, P3&& c, P4&& d, P5&& e)
  { return UniquePtr<T>(new T(a, b, c, d, e)); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, 
            typename P1, typename P2, typename P3, typename P4,
            typename P5, typename P6>
  UniquePtr<T>
    MakeUnique(P1&& a, P2&& b, P3&& c, P4&& d, P5&& e, P6&& f)
  { return UniquePtr<T>(new T(a, b, c, d, e, f)); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, 
            typename P1, typename P2, typename P3, typename P4,
            typename P5, typename P6, typename P7>
  UniquePtr<T>
    MakeUnique(P1&& a, P2&& b, P3&& c, P4&& d, P5&& e, P6&& f, P7&& g)
  { return UniquePtr<T>(new T(a, b, c, d, e, f, g)); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, 
            typename P1, typename P2, typename P3, typename P4,
            typename P5, typename P6, typename P7, typename P8>
  UniquePtr<T>
    MakeUnique(P1&& a, P2&& b, P3&& c, P4&& d, P5&& e, P6&& f, P7&& g, P8&& h)
  { return UniquePtr<T>(new T(a, b, c, d, e, f, g, h)); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, 
            typename P1, typename P2, typename P3, typename P4,
            typename P5, typename P6, typename P7, typename P8,
            typename P9>
  UniquePtr<T>
    MakeUnique(P1&& a, P2&& b, P3&& c, P4&& d, P5&& e, P6&& f, P7&& g, P8&& h, P9&& i)
  { return UniquePtr<T>(new T(a, b, c, d, e, f, g, h, i)); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <typename T, 
            typename P1, typename P2, typename P3, typename P4,
            typename P5, typename P6, typename P7, typename P8,
            typename P9, typename P10>
  UniquePtr<T>
    MakeUnique(P1&& a, P2&& b, P3&& c, P4&& d, P5&& e, P6&& f, P7&& g, P8&& h, P9&& i, P10&& j)
  { return UniquePtr<T>(new T(a, b, c, d, e, f, g, h, i, j)); }

};};};

#define TLOC_TYPEDEF_UNIQUE_PTR(_type_, _typedef_)\
  typedef tloc::core_sptr::UniquePtr<_type_>  _typedef_##_uptr;\
  typedef tloc::core_sptr::UniquePtr<const _type_>  const_##_typedef_##_uptr

#define TLOC_EXTERN_TEMPLATE_UNIQUE_PTR(_type_)\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core_sptr::UniquePtr<_type_>);\
  TLOC_EXTERN_TEMPLATE_CLASS(tloc::core_sptr::UniquePtr<const _type_>)

#endif