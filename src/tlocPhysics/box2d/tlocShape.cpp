#include "tlocShape.h"

#include <tlocCore/smart_ptr/tlocSmartPtr.inl>

namespace tloc { namespace physics { namespace box2d {

  //////////////////////////////////////////////////////////////////////////
  // Shape

  Shape::~Shape()
  {
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  Shape::Shape(shape_internal_type_ptr a_shapePtr)
    : m_shape(a_shapePtr)
  {
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  const Shape::shape_internal_type_ptr
    Shape::
    DoGetInternalShape() const
  {
    return m_shape;
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  template class core::smart_ptr::SharedPtr<b2Shape>;

};};};
