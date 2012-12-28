#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_SHAPE_H_
#define _TLOC_PHYSICS_BOX2D_SHAPE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.h>

#include <Box2D/Collision/Shapes/b2Shape.h>

namespace tloc { namespace physics { namespace box2d {

  ///-------------------------------------------------------------------------
  /// @brief  Shape is base helper interface class used to define a simple shape
  /// (circle, rectangle) for a RigidBodyShape.
  ///-------------------------------------------------------------------------
  class Shape
  {
  public:
    friend class RigidBodyShapeDef;

  public:
    typedef Shape   this_type;

    typedef b2Shape                                   shape_interal_type;

    typedef core::smart_ptr::SharedPtr<shape_interal_type>
                                                      shape_internal_type_ptr;

    typedef f32     float_type;

  public:
    virtual ~Shape();

  protected:
    Shape(shape_internal_type_ptr a_shapePtr);

    const shape_internal_type_ptr DoGetInternalShape() const;

  private:
    shape_internal_type_ptr m_shape;

  };

};};};

#endif