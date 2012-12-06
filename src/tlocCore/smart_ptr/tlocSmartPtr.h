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
    SharedPtr()
      : m_rawPtr(nullptr)
      , m_refCount(nullptr)
    { }

    SharedPtr(pointer a_rawPtr)
      : m_rawPtr(a_rawPtr)
      , m_refCount(a_rawPtr ? new ref_count_type(0) : nullptr)
    {
      DoAddRef();
    }

    SharedPtr(const this_type& a_other)
      : m_rawPtr(a_other.m_rawPtr), m_refCount(a_other.m_refCount)
    {
      // Mainly for containers
      DoAddRef();
    }

    ~SharedPtr()
    {
      DoRemoveRef();
    }

    this_type& operator= (const this_type& a_other)
    {
      DoRemoveRef();
      m_rawPtr = a_other.m_rawPtr;
      m_refCount = a_other.m_refCount;
      DoAddRef();

      return *this;
    }

    pointer Expose()
    { return m_rawPtr; }

    const_pointer Expose() const
    { return m_rawPtr; }

    pointer operator->() const
    {
      TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference NULL ptr!");
      return m_rawPtr;
    }

    reference operator*() const
    {
      TLOC_ASSERT_LOW_LEVEL(m_rawPtr, "Trying to dereference NULL ptr!");
      return *m_rawPtr;
    }

    ref_count_type GetRefCount() const
    {
      return m_refCount ? *m_refCount : 0;
    }

  private:
    void DoAddRef()
    {
      if (m_refCount)
      { ++*m_refCount; }
    }

    void DoRemoveRef()
    {
      if (m_refCount)
      {
        --*m_refCount;
        if (GetRefCount() == 0)
        {
          delete m_rawPtr;
          delete m_refCount;
        }
      }
    }

  private:
    pointer           m_rawPtr;
    ref_count_type*   m_refCount;
  };

};};};

#endif