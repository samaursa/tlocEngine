#include "tlocAttribute.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>

namespace tloc { namespace graphics { namespace gl {

  Attribute::
    Attribute()
    : m_isAttribArray(false)
  { }

  Attribute::
    Attribute(const this_type& a_other)
    : base_type(a_other)
    , m_isAttribArray(false)
  { }

  Attribute::this_type& Attribute::
    operator=(const this_type& a_other)
  {
    base_type::operator=(a_other);
    m_isAttribArray = a_other.m_isAttribArray;
    return *this;
  }

};};};

//------------------------------------------------------------------------
// Explicit Instantiations

using namespace tloc::gfx_gl;

TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Attribute);