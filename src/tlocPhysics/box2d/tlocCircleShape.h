#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_CIRCLE_SHAPE_H_
#define _TLOC_PHYSICS_BOX2D_CIRCLE_SHAPE_H_

#include <tlocCore/utilities/tlocUtils.h>

#include <tlocMath/vector/tlocVector2.h>

#include <tlocPhysics/box2d/tlocShape.h>

#include <Box2D/Collision/Shapes/b2CircleShape.h>

namespace tloc { namespace physics { namespace box2d {

  class CircleShape : public Shape
  {
  public:
    typedef CircleShape                     this_type;
    typedef Shape                           base_type;
    typedef base_type::shape_internal_type  shape_internal_type;

    typedef base_type::float_type           float_type;
    typedef math::Vec2f32                   vec_type;

    typedef b2CircleShape                   circle_shape_internal_type;

  public:
    void GetPositionLocal(vec_type& a_position);

    virtual TLOC_DECL_AND_DEF_GETTER
      (float_type, GetRadius, m_shape.m_radius);

  public:
    void SetPositionLocal(const vec_type& a_position);

    virtual TLOC_DECL_AND_DEF_SETTER
      (float_type, SetRadius, m_shape.m_radius);

  protected:
    virtual TLOC_DECL_AND_DEF_GETTER
      (shape_internal_type*, DoGetInternalShape, (shape_internal_type*)&m_shape);

  private:
    circle_shape_internal_type m_shape;
  };

};};};

#endif