#include "tlocMath.h"
#include "tlocMath.inl"

#include <limits>

namespace tloc
{

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

  //------------------------------------------------------------------------
  // Constants

  template <typename T>
  const T Math<T>::PI               = (T)(4.0f*atan(1.0f));
  template <typename T>
  const T Math<T>::EPSILON          = std::numeric_limits<T>::epsilon();
  template <typename T>
  const T Math<T>::ZERO_TOLERANCE   = std::numeric_limits<T>::epsilon();
  template <typename T>
  const T Math<T>::MAX_REAL         = std::numeric_limits<T>::max();
  template <typename T>
  const T Math<T>::TWO_PI           = Math<T>::PI * 2.0f;
  template <typename T>
  const T Math<T>::HALF_PI          = Math<T>::PI * 0.5f;
  template <typename T>
  const T Math<T>::INV_PI           = (T)(1.0f / Math<T>::PI);
  template <typename T>
  const T Math<T>::INV_TWO_PI       = (T)(1.0f / Math<T>::TWO_PI);
  template <typename T>
  const T Math<T>::DEG_TO_RAD       = (T)(Math<T>::PI/180.0f);
  template <typename T>
  const T Math<T>::RAD_TO_DEG       = (T)(180.0f/Math<T>::PI);
  template <typename T>
  const T Math<T>::LOGN_2           = Math<T>::Log(2.0f);
  template <typename T>
  const T Math<T>::LOGN_10          = Math<T>::Log(10.0f);
  template <typename T>
  const T Math<T>::INV_LOGN_2       = 1.0f / Math<T>::LOGN_2;
  template <typename T>
  const T Math<T>::INV_LOGN_10      = 1.0f / Math<T>::LOGN_10;
  template <typename T>
  const T Math<T>::m_cosTable[64]   = {0};
  template <typename T>
  const T Math<T>::m_sinTable[64]   = {0};

  //------------------------------------------------------------------------
  // Explicitly template instantiation

  template class Math<f32>;
  template class Math<f64>;
  template class Math<f128>;
}