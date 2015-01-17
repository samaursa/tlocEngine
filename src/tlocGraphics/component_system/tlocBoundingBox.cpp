#include "tlocBoundingBox.h"

namespace tloc { namespace math { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // BoundingBox2D

  BoundingBox2D::
    BoundingBox2D()
    : base_type("BoundingBox2D")
    , m_boundingBox(bounds_type::width(1), bounds_type::height(1))
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  BoundingBox2D::
    BoundingBox2D(const bounds_type& a_newBounds)
    : base_type("BoundingBox2D")
    , m_boundingBox(a_newBounds)
  { }

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