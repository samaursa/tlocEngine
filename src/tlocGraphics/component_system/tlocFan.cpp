#include "tlocFan.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

namespace tloc { namespace graphics { namespace component_system {

  Fan::Fan()
    : base_type(k_component_type)
    , m_ellipse(ellipse_type::diameter(1.0f))
    , m_sides(sides(8))
  { }

  Fan::Fan(const ellipse_type& a_ellipse, sides a_sides)
    : base_type(k_component_type)
    , m_ellipse(a_ellipse)
    , m_sides(a_sides)
  { }

  // SmartPtr
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(Fan);

  // Pool
  template class core::component_system::ComponentPool_TI<fan_sptr>;

};};};