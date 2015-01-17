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

    template <typename T>
    Vector_T<T, 3>
      DoGetMin(Vector_T<T, 3> a_other, Vector_T<T, 3> a_current)
    {
      Vector_T<T, 3> toRet;
      toRet[0] = core::tlMin(a_other[0], a_current[0]);
      toRet[1] = core::tlMin(a_other[1], a_current[1]);
      toRet[2] = core::tlMin(a_other[2], a_current[2]);
      return toRet;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T>
    Vector_T<T, 2> 
      DoGetMin(Vector_T<T, 2> a_other, Vector_T<T, 2> a_current)
    {
      Vector_T<T, 2> toRet;
      toRet[0] = core::tlMin(a_other[0], a_current[0]);
      toRet[1] = core::tlMin(a_other[1], a_current[1]);
      return toRet;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T>
    Vector_T<T, 3> 
      DoGetMax(Vector_T<T, 3> a_other, Vector_T<T, 3> a_current)
    {
      Vector_T<T, 3> toRet;
      toRet[0] = core::tlMax(a_other[0], a_current[0]);
      toRet[1] = core::tlMax(a_other[1], a_current[1]);
      toRet[2] = core::tlMax(a_other[2], a_current[2]);
      return toRet;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    template <typename T>
    Vector_T<T, 2> 
      DoGetMax(Vector_T<T, 2> a_other, Vector_T<T, 2> a_current)
    {
      Vector_T<T, 2> toRet;
      toRet[0] = core::tlMax(a_other[0], a_current[0]);
      toRet[1] = core::tlMax(a_other[1], a_current[1]);
      return toRet;
    }

  };

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <BOUNDS_TEMPS>
  Bounds_T<BOUNDS_PARAMS>::
    Bounds_T(const vec_cont& a_allPoints)
  {
    auto min = a_allPoints[0], max = a_allPoints[0];
    for (auto itr = a_allPoints.begin(), itrEnd = a_allPoints.end();
         itr != itrEnd; ++itr)
    {
      min = DoGetMin(*itr, min);
      max = DoGetMax(*itr, max);
    }
  }

  // -----------------------------------------------------------------------
  // explicit instantiation

  template class Bounds_T<Vec2f32>;
  template class Bounds_T<Vec2f64>;
  template class Bounds_T<Vec3f32>;
  template class Bounds_T<Vec3f64>;

};};