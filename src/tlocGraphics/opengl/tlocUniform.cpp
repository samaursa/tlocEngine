#include "tlocUniform.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace gl {

  Uniform::
    Uniform()
  { }

  Uniform::
    Uniform(const this_type& a_other)
    : base_type(a_other)
  { }

  Uniform::this_type& Uniform::
    operator=(const this_type& a_other)
  {
    base_type::operator=(a_other);
    return *this;
  }

  //------------------------------------------------------------------------
  // typedefs

  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Uniform);

};};};