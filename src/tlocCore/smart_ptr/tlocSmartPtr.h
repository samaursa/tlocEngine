#ifndef _TLOC_CORE_SMART_PTR_H_
#define _TLOC_CORE_SMART_PTR_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>

namespace tloc { namespace core { namespace smart_ptr {

  ///-------------------------------------------------------------------------
  /// @brief Used only for distinguishing a normal object from a SmartPtr
  ///-------------------------------------------------------------------------
  class SmartPtr
  {
  protected: // to disallow the user from doing anything with this base class
    SmartPtr()
    { /* Intentionally Empty */ }

    ~SmartPtr()
    { /* Intentionally Empty */ }
  };

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

      struct DisAllow
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
      typename T_NullCopyPolicy = p_shared_ptr::null_copy::DisAllow
    >
  class SharedPtr
    : public SmartPtr
    , public T_NullCopyPolicy
  {
  public:
    typedef T                       value_type;
    typedef T*                      pointer;
    typedef T const *               const_pointer;
    typedef T&                      reference;
    typedef T const &               const_reference;

    typedef tl_int                  ref_count_type;
    typedef SharedPtr<value_type>   this_type;

    typedef T_NullCopyPolicy        null_copy_policy_type;

  public:
    SharedPtr();
    SharedPtr(pointer a_rawPtr);
    SharedPtr(const this_type& a_other);

    template <typename T_Other>
    SharedPtr(const SharedPtr<T_Other>& a_other);

    ~SharedPtr();

    template <typename T_Other>
    this_type& operator= (const SharedPtr<T_Other>& a_other);
    this_type& operator= (const this_type& a_other);

    template <typename T_Other>
    void  CastFrom(const SharedPtr<T_Other>& a_other);

    ///-------------------------------------------------------------------------
    /// @brief Dangerous to use this. Use SharedPtr<> semantics
    ///-------------------------------------------------------------------------
    pointer       Expose() const;

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