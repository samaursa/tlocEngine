#include "tlocArcBall.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/component_system/tlocComponentPoolManager.inl.h>

namespace tloc { namespace graphics { namespace component_system {

  enum
  {
    k_moving = 0,
    k_flipVertical,
    k_flipHorizontal,
    k_count
  };

  // ///////////////////////////////////////////////////////////////////////
  // ArcBall

  ArcBall::
    ArcBall()
    : base_type("ArcBall")
    , m_focusPoint(vec_type::ZERO)
    , m_verticalAngle(0.0f)
    , m_horizontalAngle(0.0f)
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  ArcBall::
    ArcBall(const vec_type& a_focusPoint)
    : base_type("ArcBall")
    , m_focusPoint(a_focusPoint)
    , m_verticalAngle(0.0f)
    , m_horizontalAngle(0.0f)
    , m_flags(k_count)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBall::
    Reset()
  {
    m_verticalAngle = angle_type(0.0f);
    m_horizontalAngle = angle_type(0.0f);
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBall::
    FlipVertical()
  { m_flags.Toggle(k_flipVertical); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBall::
    FlipHorizontal()
  { m_flags.Toggle(k_flipHorizontal); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBall::
    MoveVertical(const angle_type& a_angle)
  {
    if (m_flags.IsUnMarked(k_flipVertical))
    {
      m_verticalAngle = a_angle;
      m_verticalAngle *= angle_type(-1.0f);
    }
    else
    {
      m_verticalAngle = a_angle;
    }
  }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    ArcBall::
    MoveHorizontal(const angle_type& a_angle)
  {
    if (m_flags.IsUnMarked(k_flipHorizontal))
    {
      m_horizontalAngle = a_angle;
      m_horizontalAngle *= angle_type(-1.0f);
    }
    else
    {
      m_horizontalAngle = a_angle;
    }
  }

};};};

//////////////////////////////////////////////////////////////////////////
// explicit instantiations

#include <tlocCore/smart_ptr/tloc_smart_ptr.inl.h>

using namespace tloc::gfx_cs;

// SmartPtr
TLOC_EXPLICITLY_INSTANTIATE_ALL_SMART_PTRS(ArcBall);
TLOC_EXPLICITLY_INSTANTIATE_VIRTUAL_STACK_OBJECT(ArcBall);
TLOC_EXPLICITLY_INSTANTIATE_COMPONENT_POOL(ArcBall);