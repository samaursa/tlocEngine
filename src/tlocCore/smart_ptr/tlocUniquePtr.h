#ifndef _TLOC_CORE_SMART_PTR_SHARED_PTR_H_
#define _TLOC_CORE_SMART_PTR_SHARED_PTR_H_

#include <tlocCore/utilities/tlocUtils.h>
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

};};};

#endif