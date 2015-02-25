#ifndef _TLOC_CORE_TYPES_ANY_H_
#define _TLOC_CORE_TYPES_ANY_H_

#include <tlocCore/tlocCoreBase.h>
#include <tlocCore/types/tlocBasicTypes.h>

namespace tloc { namespace core { namespace types {

  // This code is a modified version of Any from CodeProject written by
  // Christopher Diggins.

  //////////////////////////////////////////////////////////////////////////
  // Any policies and type selection helpers

  namespace p_any
  {
    namespace detail
    {
      struct None
      { };

      struct Empty
      { };

      struct Policy_I
      {
        virtual void Delete(void** a_unknownType) = 0;
        virtual void Copy(void const* a_source, void** a_dest) = 0;
        virtual void Clone(void* const* a_source, void** a_dest) = 0;
        virtual void Move(void* const* a_source, void** a_dest) =  0;
        virtual void* GetValue(void** a_source) = 0;

        virtual void const* GetValue(void* const * a_source) const = 0;
        virtual size_t GetSize() const = 0;
      };

      template <typename T>
      struct Policy_IT : public Policy_I
      {
      public:
        typedef tl_size     size_type;
        typedef T           value_type;

      public:
        virtual size_type GetSize() const;
        value_type const* CastSource(void const* a_source);
        value_type const* CastSource(void* const* a_source);
      };

      template <typename T>
      struct SimpleType_T : public Policy_IT<T>
      {
      public:
        typedef T                         value_type;
        typedef Policy_IT<value_type>     base_type;

      public:
        virtual void  Delete(void** a_unknownType);
        virtual void  Copy(void const* a_source, void** a_dest);
        virtual void  Clone(void* const* a_source, void** a_dest);
        virtual void  Move(void* const* a_source, void** a_dest);
        virtual void* GetValue(void** a_source);

        virtual void const * GetValue(void* const * a_source) const;
      };

      template <typename T>
      struct ComplexType_T : public Policy_IT<T>
      {
        typedef T                         value_type;
        typedef Policy_IT<value_type>     base_type;

        using base_type::CastSource;

        virtual void Delete(void** a_unknownType);
        virtual void Copy(void const* a_source, void** a_dest);
        virtual void Clone(void* const* a_source, void** a_dest);
        virtual void Move(void* const* a_source, void** a_dest);
        virtual void* GetValue(void** a_source);

        virtual void const * GetValue(void* const * a_source) const;
      };
    }

    template <typename T>
    struct SelectPolicy
    {
      typedef detail::ComplexType_T<T>  type;
    };

    template <typename T>
    struct SelectPolicy<T*>
    {
      typedef detail::SimpleType_T<T*> type;
    };

    //------------------------------------------------------------------------
    // Specializing basic types
#define TLOC_ANY_SPECIALIZE_SIMPLE_TYPE(_type_) \
    template<> struct SelectPolicy<_type_> \
    { typedef detail::SimpleType_T<_type_> type; }

    TLOC_ANY_SPECIALIZE_SIMPLE_TYPE(s8);
    TLOC_ANY_SPECIALIZE_SIMPLE_TYPE(s16);
    TLOC_ANY_SPECIALIZE_SIMPLE_TYPE(s32);
    TLOC_ANY_SPECIALIZE_SIMPLE_TYPE(s64);

    TLOC_ANY_SPECIALIZE_SIMPLE_TYPE(u8);
    TLOC_ANY_SPECIALIZE_SIMPLE_TYPE(u16);
    TLOC_ANY_SPECIALIZE_SIMPLE_TYPE(u32);
    TLOC_ANY_SPECIALIZE_SIMPLE_TYPE(u64);

    TLOC_ANY_SPECIALIZE_SIMPLE_TYPE(f32);
    TLOC_ANY_SPECIALIZE_SIMPLE_TYPE(f64);

#undef TLOC_ANY_SPECIALIZE_SIMPLE_TYPE
    //------------------------------------------------------------------------

    template <typename T>
    detail::Policy_I* GetPolicy();

  };

  //////////////////////////////////////////////////////////////////////////
  // Any Class

  class Any
  {
  public:
    typedef Any         this_type;

  public:
    Any();
    Any(const this_type& a_other);

    template <typename T>
    Any(const T& a_other);

    ~Any();

    template <typename T>
    void Assign(const T& a_other);
    void Assign(const this_type& a_other);

    template <typename T>
    void Update(const T& a_other);
    template <typename T>
    void UpdateOrAssign(const T& a_other);

    template <typename T>
    this_type& operator= (const T& a_other);
    this_type& operator= (const this_type& a_other);

    this_type& swap(this_type& a_other);

    template <typename T>
    T& Cast();

    template <typename T>
    T const & Cast() const;

    bool IsEmpty() const;
    void Reset();
    bool IsSameType(const this_type& a_other) const;

  private:

  private:
    typedef p_any::detail::Policy_I   policy_base_type;
    policy_base_type* m_policy;
    void*             m_object;
  };

  // -----------------------------------------------------------------------
  // swap function

  TL_I void swap(Any& a, Any& b)
  { a.swap(b); }

};};};

#include "tlocAny.inl.h"

#endif