#ifndef TLOC_GL_OBJECT_H
#define TLOC_GL_OBJECT_H

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/error/tlocError.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/string/tlocString.h>

#include <tlocCore/base_classes/tlocNonCopyable.h>

namespace tloc { namespace graphics { namespace gl {

  namespace p_object
  {
    struct OnlyID{};
    struct WithError{};
  };

  class ObjectBase
  {
  public:
    typedef u32 object_handle; // GLuint is u32

    bool IsValid();

    void swap(ObjectBase& a_other)
    {
      using core::swap;
      swap(m_handle, a_other.m_handle);
    }

    TLOC_DECL_AND_DEF_GETTER(object_handle, GetHandle, m_handle);

  protected:
    ObjectBase();

    TLOC_DECL_AND_DEF_SETTER(object_handle, SetHandle, m_handle);

  private:
    object_handle m_handle;
  };

  // ///////////////////////////////////////////////////////////////////////
  // ObjectRefCounted

  template <typename T_Derived>
  class ObjectRefCounted : public ObjectBase
  {
  public:
    typedef tl_size                             size_type;
    typedef T_Derived                           derived_type;
    typedef ObjectRefCounted<derived_type>      this_type;
    typedef ObjectBase                          base_type;

  public:
    ObjectRefCounted(const ObjectRefCounted& a_other)
      : ObjectBase()
      , m_refCount(nullptr)
    {
      SetHandle(a_other.GetHandle());
      m_refCount = a_other.m_refCount;
      ++(*m_refCount);
    }

    ~ObjectRefCounted()
    {
      if (m_refCount)
      {
        size_type refCount = *m_refCount;

        if ( IsLastRef() )
        {
          delete m_refCount;
          m_refCount = nullptr;
        }
        else
        { --(refCount); }

        if (m_refCount)
        { *m_refCount = refCount; }
      }
    }

    this_type& operator=(ObjectRefCounted a_other)
    {
      swap(a_other);
      return *this;
    }

    void swap(this_type& a_other)
    {
      using core::swap;
      swap(m_refCount, a_other.m_refCount);
      base_type::swap(a_other);
    }

    void SetHandle(object_handle const & a_handle)
    {
      TLOC_ASSERT(m_refCount == nullptr, "Object already has a handle!");
      m_refCount = new size_type(0);

      base_type::SetHandle(a_handle);
    }

    TLOC_DECL_AND_DEF_GETTER(size_type, use_count, *m_refCount );

    bool IsLastRef()
    { return m_refCount == nullptr || use_count() == 0; }

  protected:

    ObjectRefCounted()
      : ObjectBase()
      , m_refCount(nullptr)
    { }

  private:
    size_type* m_refCount;
  };

  // ///////////////////////////////////////////////////////////////////////
  // Object_T<T_Derived, OnlyID>

  template < typename T_Derived,
             typename T_Policy = p_object::OnlyID >
  class Object_T
    : public ObjectRefCounted<T_Derived>
  {
  public:
    typedef ObjectRefCounted<T_Derived> base_type;
    typedef T_Derived                   derived_type;
    typedef base_type::object_handle    object_handle;
    typedef core::error::Error          error_type;

    typedef Object_T<derived_type, T_Policy> this_type;

  public:
    Object_T()
      : base_type()
    { }

    Object_T(const this_type& a_other)
      : base_type(a_other)
    { }

    Object_T(const derived_type& a_other)
      : base_type(a_other)
    { }
  };

  // ///////////////////////////////////////////////////////////////////////
  // Object_T<T_Derived, WithError>

  template<typename T_Derived>
  class Object_T<T_Derived, p_object::WithError>
    : public ObjectRefCounted<T_Derived>
  {
  public:
    typedef ObjectRefCounted<T_Derived> base_type;
    typedef T_Derived                   derived_type;
    typedef base_type::object_handle    object_handle;
    typedef core::error::Error          error_type;
    typedef core::string::String        string_type;

    typedef Object_T<derived_type>      this_type;

  public:

    Object_T()
      : base_type()
    { }

    Object_T(const this_type& a_other)

      : base_type(a_other)
    { }

    Object_T(const derived_type& a_other)
      : base_type(a_other)
    { }

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(string_type, GetError, m_error);

  protected:
    TLOC_DECL_AND_DEF_SETTER(string_type, DoSetError, m_error);

  private:
    string_type m_error;
  };

  // -----------------------------------------------------------------------
  // algorithms

  namespace algos { namespace find {

    namespace object {

      struct ByHandle
      {
        typedef ObjectBase::object_handle         object_handle;

        ByHandle(object_handle  a_handleToSearch)
          : m_handleToSearch(a_handleToSearch)
        { }

        bool operator()(const ObjectBase& a_object)
        { return m_handleToSearch == a_object.GetHandle(); }

      private:
        object_handle m_handleToSearch;
      };
    };

  };};

};};};

#endif