#include "tlocCircleShape.h"

#include <tlocMath/vector/tlocVector2.inl>

namespace tloc { namespace physics { namespace box2d {

  //////////////////////////////////////////////////////////////////////////
  // CircleShape

  void CircleShape::
    GetPositionLocal(vec_type& a_position)
  {
    b2Vec2& position = m_shape.m_p;
    a_position[0] = position.x;
    a_position[1] = position.y;
  }

  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void CircleShape::
    SetPositionLocal(const vec_type& a_position)
  {
    b2Vec2& position = m_shape.m_p;
    position.x = a_position[0];
    position.y = a_position[1];
  }

};};};
