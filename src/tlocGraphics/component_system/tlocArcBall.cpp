#include "tlocArcBall.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  enum
  {
    k_moving = 0,
    k_count
  };

  // ///////////////////////////////////////////////////////////////////////
  // ArcBall

  ArcBall::
    ArcBall()
    : base_type(k_component_type)
    , m_focusPoint(vec_type::ZERO)
    , m_verticalAngle(0.0f)
    , m_horizontalAngle(0.0f)
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBall::
    ArcBall(const vec_type& a_focusPoint)
    : base_type(k_component_type)
    , m_focusPoint(a_focusPoint)
    , m_verticalAngle(0.0f)
    , m_horizontalAngle(0.0f)
    , m_flags(k_count)
  { }

  //////////////////////////////////////////////////////////////////////////
  // explicit instantiations

  // SmartPtr
  TLOC_EXPLICITLY_INSTANTIATE_SHARED_PTR(ArcBall);
  TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(arcball_sptr);

};};};