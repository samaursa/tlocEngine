#include "tlocAttribute.h"

namespace tloc { namespace graphics { namespace gl {

  Attribute::
    Attribute()
    : m_isAttribArray(false)
  { }

  Attribute::
    Attribute(const this_type& a_other)
    : base_type(a_other)
    , m_isAttribArray(a_other.m_isAttribArray)
  { }

  Attribute::this_type&
    Attribute::
    operator=(this_type a_other)
  {
    swap(a_other);
    return *this;
  }

  void
    Attribute::
    swap(this_type& a_other)
  {
    using core::swap;
    swap(m_isAttribArray, a_other.m_isAttribArray);
    base_type::swap(a_other);
  }

  void
    Attribute::
    Reset()
  {
    m_isAttribArray = false;
    base_type::Reset();
  }

};};};

//------------------------------------------------------------------------
// Explicit Instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/containers/tlocArray.inl.h>

using namespace tloc::gfx_gl;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Attribute);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Attribute);
TLOC_EXPLICITLY_INSTANTIATE_ARRAY(attribute_sptr);