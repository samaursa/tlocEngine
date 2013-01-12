#include "tlocFan.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/component_system/tlocComponentPoolManager.inl>

namespace tloc { namespace graphics { namespace component_system {

  Fan::Fan()
    : base_type(component_system::components::fan)
    , m_ellipse(ellipse_type::diameter(1.0f))
    , m_sides(sides(8))
  { }

  Fan::Fan(const ellipse_type& a_ellipse, sides a_sides)
    : base_type(component_system::components::fan)
    , m_ellipse(a_ellipse)
    , m_sides(a_sides)
  { }

  // SmartPtr
  template core::smart_ptr::SharedPtr<Fan>;

  // Pool
  template core::component_system::ComponentPool_TI<FanPtr>;

};};};