#include "tlocRigidBodyShapeDef.h"

namespace tloc { namespace physics { namespace box2d {

  //////////////////////////////////////////////////////////////////////////
  // RigidBodyShapeDef

  RigidBodyShapeDef::RigidBodyShapeDef(const shape_type& a_shape)
  {
    SetShape(a_shape);
    SetFriction(0.2f);
    SetRestitution(0.0f);
    SetDensity(0.0f);
    SetSensor(false);
  }

  void RigidBodyShapeDef::SetShape(const shape_type& a_shape)
  {
    m_internalShape = a_shape.DoGetInternalShape();
    m_fixtureDef.shape = m_internalShape.get();
  }

};};};
