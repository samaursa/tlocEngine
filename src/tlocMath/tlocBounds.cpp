#include "tlocBounds.h"

#include <tlocCore/tlocAlgorithms.h>

namespace tloc { namespace math {

  // ///////////////////////////////////////////////////////////////////////
  // Bounds_T

#define BOUNDS_TEMPS  typename T_VecType
#define BOUNDS_PARAMS T_VecType

  namespace {

    using namespace math_t;

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    Vec3f32 
      GetMin(Vec3f32 a_other, Vec3f32 a_current)
    {
      Vec3f32 toRet;
      toRet[0] = core::tlMin(a_other[0], a_current[0]);
      toRet[1] = core::tlMin(a_other[1], a_current[1]);
      toRet[2] = core::tlMin(a_other[2], a_current[2]);
      return toRet;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    Vec2f32 
      GetMin(Vec2f32 a_other, Vec2f32 a_current)
    {
      Vec2f32 toRet;
      toRet[0] = core::tlMin(a_other[0], a_current[0]);
      toRet[1] = core::tlMin(a_other[1], a_current[1]);
      return toRet;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    Vec3f32 
      GetMax(Vec3f32 a_other, Vec3f32 a_current)
    {
      Vec3f32 toRet;
      toRet[0] = core::tlMax(a_other[0], a_current[0]);
      toRet[1] = core::tlMax(a_other[1], a_current[1]);
      toRet[2] = core::tlMax(a_other[2], a_current[2]);
      return toRet;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    Vec2f32 
      GetMax(Vec2f32 a_other, Vec2f32 a_current)
    {
      Vec2f32 toRet;
      toRet[0] = core::tlMax(a_other[0], a_current[0]);
      toRet[1] = core::tlMax(a_other[1], a_current[1]);
      return toRet;
    }

  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <BOUNDS_TEMPS>
  Bounds_T<BOUNDS_PARAMS>::
    Bounds_T(const vec_type& a_allPoints)
  {
    vec_type min = a_allPoints[0], max = a_allPoints[0];
    for (auto& point : a_allPoints)
    {
      min = GetMin(point, min);
      max = GetMax(point, max);
    }
  }

};};