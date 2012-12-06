#ifndef _TLOC_CORE_SMART_PTR_H_
#define _TLOC_CORE_SMART_PTR_H_

#include <tlocCore/tlocBase.h>

namespace tloc { namespace core { namespace smart_ptr {

  template <typename T_Value>
  class SharedPtr
  {
  public:
    typedef T_Value                 value_type;
    typedef T_Value*                pointer;
    typedef T_Value const *         const_pointer;
    typedef T_Value&                reference;
    typedef T_Value const &         const_reference;

    typedef tl_int                  ref_count_type;
    typedef SharedPtr<value_type>   this_type;

  public:
    SharedPtr();
    SharedPtr(pointer a_rawPtr);
    SharedPtr(const this_type& a_other);
    ~SharedPtr();

    this_type& operator= (const this_type& a_other);

    pointer       Expose();
    const_pointer Expose() const;

    pointer   operator->() const;
    reference operator*() const;

    ref_count_type GetRefCount() const;

  private:
    void DoAddRef();
    void DoRemoveRef();

  private:
    pointer           m_rawPtr;
    ref_count_type*   m_refCount;
  };

};};};

#endif