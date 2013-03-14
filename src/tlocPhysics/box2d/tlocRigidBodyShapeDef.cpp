#include "tlocRigidBodyShapeDef.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl>
#include <tlocCore/utilities/tlocType.h>

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
    using core::utils::CastTo32;
    typedef b2PolygonShape          polygon_shape_internal_type;
    typedef rect_type::point_type   point_type;

    polygon_shape_internal_type* rect = new polygon_shape_internal_type;

    float_internal_type halfWidth =
      CastTo32<float_internal_type, float_type>( a_rect.GetWidth() ) / 2.f;
    float_internal_type halfHeight =
      CastTo32<float_internal_type, float_type>( a_rect.GetHeight() ) / 2.f;

    point_type position = a_rect.GetPosition();

    rect->SetAsBox(halfWidth, halfHeight, b2Vec2(position[0], position[1]), 0.f);

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

  void RigidBodyShapeDef::DoSetParent(const entity_type* a_parent)
  {
    m_fixtureDef.userData = const_cast<entity_type*>(a_parent);
  }

  //////////////////////////////////////////////////////////////////////////
  // Explicit instantiations

  template class core::smart_ptr::SharedPtr<b2Shape>;

};};};
