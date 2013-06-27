#include "tlocQuad.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  Quad::Quad()
    : base_type(k_component_type)
    , m_rect(rect_type::width(1.0f), rect_type::height(1.0f))
  { }

  Quad::Quad(const rect_type& a_rect)
    : base_type(k_component_type)
    , m_rect(a_rect)
  { }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiations

  // SmartPtr
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Quad);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(quad_sptr);

};};};