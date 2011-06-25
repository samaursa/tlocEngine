#include "tlocMath/tlocMath.h"

namespace tloc
{
  template Math<f32>;
  template Math<f64>;
  template Math<f128>;
};

#ifndef TLOC_FULL_SOURCE
#include "tlocMath.inl"
#endif

namespace tloc
{
  //------------------------------------------------------------------------
  // Constants

  // Generic Constants
  template <typename T>
  const T Math<T>::PI               = (T)(4.0*atan(1.0));
  template <typename T>
  const T Math<T>::ZERO_TOLERANCE   = (T)1e-06;
  template <typename T>
  const T Math<T>::TWO_PI           = Math<T>::PI * (T)2.0;
  template <typename T>
  const T Math<T>::HALF_PI          = Math<T>::PI * (T)0.5;
  template <typename T>
  const T Math<T>::INV_PI           = (T)(1.0 / Math<T>::PI);
  template <typename T>
  const T Math<T>::INV_TWO_PI       = (T)(1.0 / Math<T>::TWO_PI);
  template <typename T>
  const T Math<T>::DEG_TO_RAD       = (T)(Math<f32>::PI/180.0);
  template <typename T>
  const T Math<T>::RAD_TO_DEG       = (T)(180.0f/Math<f32>::PI);
  template <typename T>
  const T Math<T>::LOGN_2           = Math<T>::Log((T)2.0);
  template <typename T>
  const T Math<T>::LOGN_10          = Math<T>::Log((T)10.0);
  template <typename T>
  const T Math<T>::INV_LOGN_2       = (T)1.0 / Math<T>::LOGN_2;
  template <typename T>
  const T Math<T>::INV_LOGN_10      = (T)1.0 / Math<T>::LOGN_10;
  template <typename T>
  const T Math<T>::m_cosTable[64]   = {0};
  template <typename T>
  const T Math<T>::m_sinTable[64]   = {0};

  // Specialized f32 constants
  template<> const f32 Mathf::EPSILON         = FLT_EPSILON;
  template<> const f32 Mathf::MAX_REAL        = FLT_MAX;

  // Specialized f64 constants
  template<> const f64 Mathd::EPSILON         = DBL_EPSILON;
  template<> const f64 Mathd::MAX_REAL        = DBL_MAX;

  // Specialized f128 constants
  template<> const f128 Mathl::EPSILON         = LDBL_EPSILON;
  template<> const f128 Mathl::MAX_REAL        = LDBL_MAX;

  //------------------------------------------------------------------------
  // Functions

  template <typename T>
  Math<T> Math<T>::m_math;

  template <typename T>
  tloc::Math<T>::Math()
  {
    Initialize();
  }

  template <typename T>
  tloc::Math<T>::~Math()
  {

  }

  template <typename T>
  void tloc::Math<T>::Initialize()
  {
  }
}