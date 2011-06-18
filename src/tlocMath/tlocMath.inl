namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Math<T>

  template <typename T>
  TL_FI T Math<T>::Ceil(const T& aValue)
  { 
    return ceil(aValue); 
  }

  template <typename T>
  TL_FI T Math<T>::Floor(const T& aValue)
  {
    return floor(aValue);
  }

  template <typename T>
  TL_FI T Math<T>::Abs(const T& aValue)
  { 
    return abs(aValue); 
  }

  template <typename T>
  TL_FI T Math<T>::ATan(const T& aValue) 
  { 
    return atan(aValue); 
  }

  template <typename T>
  TL_FI T Math<T>::ATan2(const T& aValue1, const T& aValue2)
  { 
    return atan2(aValue1, aValue2); 
  }

  template <typename T>
  TL_FI bool Math<T>::IsNaN(const T& aValue)
  { 
    return aValue != aValue; 
  }
  
  template <typename T>
  TL_FI bool Math<T>::Approx(const T& aValue1, const T& aValue2, T eps /* = T */)
  {
    T toCompare = Abs(aValue1 - aValue2);
    return (toCompare < eps);
  }

  template <typename T>
  TL_FI T Math<T>::Degree(const T& aValueInRadian)
  {
    return aValueInRadian  * (T)TL_RAD_TO_DEGREE_CONSTANT;
  }

  template <typename T>
  TL_FI T Math<T>::Radian(const T& aValueInDegrees)
  {
    return aValueInDegrees * (T)TL_DEGREE_TO_RAD_CONSTANT;
  }

  template <typename T>
  TL_FI T Math<T>::Sqrt(const T& aValue)
  {
    return sqrt(aValue);
  }
};