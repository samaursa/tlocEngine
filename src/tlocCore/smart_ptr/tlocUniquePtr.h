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
    typename T                      value_type;
    typename T*                     pointer;
    typename T const *              const_pointer;
    typename T&                     reference;
    typename T const &              const_reference;

    typename UniquePtr<value_type>  this_type;

  public:
    UniquePtr();
    explicit UniquePtr(pointer a_rawPtr);
    UniquePtr(const this_type& a_other);

    template <typename T_Other>
    UniquePtr(<const UniquePtr<T_Other>& a_other);
    ~UniquePtr();

    template <typename T_Other>
    this_type& operator=(const UniquePtr<T_Other>& a_other);
    this_type& operator=(const this_type& a_other);

    pointer   release(pointer a_ptr = pointer() );
    void      reset(pointer a_ptr = pointer() );
    void      swap(this_type& a_other);

    pointer   get() const;
    operator  bool() const;

    reference operator*() const;
    pointer   operator->() const;

  };

};};};

#endif