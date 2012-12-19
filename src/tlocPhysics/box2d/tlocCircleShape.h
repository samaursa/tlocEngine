#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_CIRCLE_SHAPE_H_
#define _TLOC_PHYSICS_BOX2D_CIRCLE_SHAPE_H_

#include <tlocCore/utilities/tlocUtils.h>

#include <tlocMath/vector/tlocVector2.h>

#include <tlocPhysics/box2d/tlocShape.h>

#include <Box2D/Collision/Shapes/b2CircleShape.h>

namespace tloc { namespace physics { namespace box2d {

  ///-------------------------------------------------------------------------
  /// @brief  CircleShape defines a circle for a RigidBodyShape.
  ///-------------------------------------------------------------------------
  class CircleShape : public Shape
  {
  public:
    typedef CircleShape                     this_type;
    typedef Shape                           base_type;
    typedef base_type::shape_interal_type   shape_interal_type;
    typedef base_type::shape_internal_type_ptr  
                                            shape_internal_type_ptr;

    typedef base_type::float_type           float_type;
    typedef math::Vec2f32                   vec_type;

    typedef b2CircleShape                   circle_shape_internal_type;

  public:
    CircleShape();

    void GetPositionLocal(vec_type& a_position);

    float_type GetRadius();

  public:
    void SetPositionLocal(const vec_type& a_position);

    void SetRadius(float_type a_radius);

  private:
    circle_shape_internal_type* DoGetInternalCircleShape();

  };

};};};

#endif