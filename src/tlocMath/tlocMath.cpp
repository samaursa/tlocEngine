#include "tlocMath.h"
#include "tlocMath.inl.h"

#include <limits>

namespace tloc
{

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

  namespace math 
  {
    // -----------------------------------------------------------------------
    // global functions

    bool 
      IsPowerOfTwo( const tl_uint& aValue )
    {
      return (aValue != 0) && ((aValue & (aValue - 1)) == 0);
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    u32 
      FastPowOfTwo( const u32& aPower )
    {
      return 0x00000001 << aPower;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    s32 
      FastSignInt( const f32& aRealIn )
    {
      if (((s32&)aRealIn & 0x7FFFFFF)==0) return 0;
      return (signed ((s32&)aRealIn & 0x80000000) >> 31) | 1;
    }
  };

  //------------------------------------------------------------------------
  // Explicitly template instantiation

#include "tlocMathExplicitMacros.h"
  TLOC_EXPLICITLY_INSTANTIATE_MATH(f32);
  TLOC_EXPLICITLY_INSTANTIATE_MATH(f64);
  TLOC_EXPLICITLY_INSTANTIATE_MATH(f128);
}