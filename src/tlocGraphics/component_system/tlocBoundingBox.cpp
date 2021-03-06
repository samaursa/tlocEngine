#include "tlocBoundingBox.h"

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // BoundingBox2D

  BoundingBox2D::
    BoundingBox2D()
    : base_type("BoundingBox2D")
    , m_boundingBox(bounds_type::width(1), bounds_type::height(1))
    , m_circular(false)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BoundingBox2D::
    BoundingBox2D(const bounds_type& a_newBounds)
    : base_type("BoundingBox2D")
    , m_boundingBox(a_newBounds)
    , m_circular(false)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BoundingBox2D::
    BoundingBox2D(const circular_bounds_type& a_newBounds)
    : base_type("BoundingBox2D")
    , m_circularBounds(a_newBounds)
    , m_circular(true)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    BoundingBox2D::
    GetBounds() const -> bounds_type
  {
    TLOC_ASSERT(m_circular == false, "Bounds are circular");
    return m_boundingBox;
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  auto
    BoundingBox2D::
    GetCircularBounds() const -> circular_bounds_type
  {
    TLOC_ASSERT(m_circular, "Bounds are NOT circular");
    return m_circularBounds;
  }

  // ///////////////////////////////////////////////////////////////////////
  // BoundingBox3D

  BoundingBox3D::
    BoundingBox3D()
    : base_type("BoundingBox3D")
    , m_boundingBox(bounds_type::width(1), bounds_type::height(1), 
                    bounds_type::depth(1))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BoundingBox3D::
    BoundingBox3D(const bounds_type& a_newBounds)
    : base_type("BoundingBox3D")
    , m_boundingBox(a_newBounds)
  { }

};};};

// -----------------------------------------------------------------------
// Explicit Instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

using namespace tloc::gfx_cs;

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(BoundingBox2D);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(BoundingBox2D);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(BoundingBox2D);

TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(BoundingBox3D);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(BoundingBox3D);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(BoundingBox3D);
