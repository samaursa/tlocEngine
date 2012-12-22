#include "tlocQuad.h"

#include <tlocCore/smart_ptr/tlocSmartPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

namespace tloc { namespace graphics { namespace component_system {

  Quad::Quad()
    : base_type(component_system::components::quad)
    , m_size(1.0f)
  { }

  Quad::Quad(size a_scale)
    : base_type(component_system::components::quad)
    , m_size(a_scale)
  { }

  void Quad::SetSize(size a_scale)
  { m_size = a_scale; }

  // SmartPtr
  template core::smart_ptr::SharedPtr<Quad>;

  // Pool
  template core::component_system::ComponentPool_TI<QuadPtr>;

};};};