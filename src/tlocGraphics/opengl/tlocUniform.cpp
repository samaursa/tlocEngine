#include "tlocUniform.h"

#include <tlocGraphics/opengl/tlocOpenGL.h>

namespace tloc { namespace graphics { namespace gl {

  Uniform::
    Uniform()
  { }

  Uniform::
    Uniform(const this_type& a_other)
    : base_type(a_other)
  { }

  Uniform::this_type&
    Uniform::
    operator=(this_type a_other)
  {
    swap(a_other);
    return *this;
  }

  void
    Uniform::
    swap(this_type& a_other)
  {
    base_type::swap(a_other);
  }

};};};

//------------------------------------------------------------------------
// typedefs

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/containers/tlocArray.inl.h>

using namespace tloc::gfx_gl;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(Uniform);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(Uniform);

TLOC_EXPLICITLY_INSTANTIATE_ARRAY(uniform_sptr);