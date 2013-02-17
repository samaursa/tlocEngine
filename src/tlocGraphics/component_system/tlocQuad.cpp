#include "tlocQuad.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

namespace tloc { namespace graphics { namespace component_system {

  Quad::Quad()
    : base_type(component_system::components::quad)
    , m_rect(rect_type::width(1.0f), rect_type::height(1.0f))
  { }

  Quad::Quad(const rect_type& a_rect)
    : base_type(component_system::components::quad)
    , m_rect(a_rect)
  { }

  // SmartPtr
  template class core::smart_ptr::SharedPtr<Quad>;

  // Pool
  template class core::component_system::ComponentPool_TI<QuadPtr>;

};};};