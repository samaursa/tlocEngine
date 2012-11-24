#pragma once
#ifndef _TLOC_PHYSICS_BOX2D_SHAPE_H_
#define _TLOC_PHYSICS_BOX2D_SHAPE_H_

#include <tlocCore/tlocBase.h>
#include <tlocCore/utilities/tlocUtils.h>

#include <Box2D/Collision/Shapes/b2Shape.h>

namespace tloc { namespace physics { namespace box2d {

  class Shape
  {
  public:
    friend class RigidBodyShape;

  public:
    typedef Shape   this_type;
    typedef b2Shape shape_value_type;
    
    typedef f32     float_type;

  public:
    virtual ~Shape()
    {
    }

    virtual TLOC_DECL_GETTER(float_type, GetRadius) = 0;
    virtual TLOC_DECL_SETTER(float_type, SetRadius) = 0;

  protected:
    virtual const shape_value_type* GetShapeValue() const = 0;

  };

};};};

#endif