#include "tlocCircleShape.h"

#include <tlocMath/vector/tlocVector2.inl>

namespace tloc { namespace physics { namespace box2d {

  //////////////////////////////////////////////////////////////////////////
  // CircleShape

  CircleShape::CircleShape()
    : base_type(shape_internal_type_ptr(new circle_shape_internal_type))
  {
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void CircleShape::
    GetPositionLocal(vec_type& a_position)
  {
    circle_shape_internal_type* circleShape = DoGetInternalCircleShape();

    b2Vec2& position = circleShape->m_p;
    a_position[0] = position.x;
    a_position[1] = position.y;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  CircleShape::float_type
    CircleShape::
    GetRadius()
  {
    circle_shape_internal_type* circleShape = DoGetInternalCircleShape();
    return circleShape->m_radius;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void CircleShape::
    SetPositionLocal(const vec_type& a_position)
  {
    circle_shape_internal_type* circleShape = DoGetInternalCircleShape();

    b2Vec2& position = circleShape->m_p;
    position.x = a_position[0];
    position.y = a_position[1];
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  void CircleShape::
    SetRadius(float_type a_radius)
  {
    circle_shape_internal_type* circleShape = DoGetInternalCircleShape();
    circleShape->m_radius = a_radius;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  CircleShape::circle_shape_internal_type*
    CircleShape::
    DoGetInternalCircleShape()
  {
    shape_internal_type_ptr shape = DoGetInternalShape();
    return static_cast<circle_shape_internal_type*>(shape.get());;
  }


};};};
