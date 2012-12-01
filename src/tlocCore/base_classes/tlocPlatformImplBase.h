#ifndef TLOC_PLATFORM_IMPL_BASE_H
#define TLOC_PLATFORM_IMPL_BASE_H

#include <tlocCore/tlocBase.h>
#include <tlocCore/base_classes/tlocNonCopyable.h>

namespace tloc { namespace core {

  ///-------------------------------------------------------------------------
  /// Base class for platform independent implementations of a type.
  ///
  /// A platform independent 'parent' class will have methods that it will call
  /// on a platform specific implementation (using the PIMPL idiom) which has
  /// at least the same methods as the platform independant 'parent'.
  ///
  /// Most platform specific implementations will require a pointer to the
  /// platform independent parent (e.g. for callbacks as the parent may be a
  /// dispatcher). To avoid code duplication, the platform specific
  /// implementations can derive from this class.
  ///-------------------------------------------------------------------------
  template <class T_ParentClass>
  class ImplBase : public NonCopyable
  {
  public:
    typedef T_ParentClass                             parent_type;
    typedef typename parent_type::platform_type       platform_type;

    ImplBase(parent_type* a_parent) : m_parent(a_parent)
    {
      TLOC_ASSERT_NOT_NULL(m_parent);
    }

    const parent_type* GetParent() const { return m_parent; }
    parent_type*       GetParent()       { return m_parent; }

  protected:

    parent_type*      m_parent;
  };

};};

#endif