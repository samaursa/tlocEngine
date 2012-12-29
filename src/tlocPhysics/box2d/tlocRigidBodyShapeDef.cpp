#include "tlocRigidBodyShapeDef.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

#include <Box2D/Common/b2Math.h>
#include <Box2D/Collision/Shapes/b2Shape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

namespace tloc { namespace physics { namespace box2d {

  //////////////////////////////////////////////////////////////////////////
  // Free definitions

  namespace {

    typedef f32     float_internal_type;
    typedef b2Vec2  vec_internal_type;
  };

  //////////////////////////////////////////////////////////////////////////
  // RigidBodyShapeDef

  void RigidBodyShapeDef::DoSetShape(const rect_type& a_rect)
  {
    typedef b2PolygonShape  polygon_shape_internal_type;

    polygon_shape_internal_type* rect = new polygon_shape_internal_type;

    float_internal_type width =
      static_cast<float_internal_type>( a_rect.GetWidth() );
    float_internal_type height =
      static_cast<float_internal_type>( a_rect.GetHeight() );

    rect->SetAsBox(width, height);

    m_fixtureDef.shape = rect;
    m_internalShape = shape_internal_type_sptr(rect);
  }

  void RigidBodyShapeDef::DoSetShape(const circle_type& a_circle)
  {
    typedef b2CircleShape             circle_shape_internal_type;
    typedef circle_type::point_type   point_type;

    circle_shape_internal_type* circle = new circle_shape_internal_type;

    circle->m_radius = static_cast<float_internal_type>(a_circle.GetRadius());

    point_type position = a_circle.GetPosition();
    vec_internal_type& positionInternal = circle->m_p;
    positionInternal.x = static_cast<float_internal_type>(position[0]);
    positionInternal.y = static_cast<float_internal_type>(position[1]);

    m_fixtureDef.shape = circle;
    m_internalShape = shape_internal_type_sptr(circle);
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  template class core::smart_ptr::SharedPtr<b2Shape>;

};};};
