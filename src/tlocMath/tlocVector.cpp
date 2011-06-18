#include "tlocMath/tlocVector.h"

namespace tloc
{
  template Vector<f32, 2>;
  template Vector<f64, 2>;
  template Vector<f32, 3>;
  template Vector<f64, 3>;
  template Vector<f32, 4>;
  template Vector<f64, 4>;

  template<typename T, u32 T_SIZE> 
  const Vector<T, T_SIZE> Vector<T, T_SIZE>::ZERO(0);

  template<typename T, u32 T_SIZE> 
  const Vector<T, T_SIZE> Vector<T, T_SIZE>::ONE(1);

};