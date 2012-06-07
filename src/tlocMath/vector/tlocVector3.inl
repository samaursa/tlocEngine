#ifndef TLOC_VECTOR_3_INL
#define TLOC_VECTOR_3_INL

#ifndef TLOC_VECTOR_3_H
#error "Must include header before including the inline file"
#endif

#include <tlocCore/tlocAlgorithms.inl>
#include <tlocMath/tlocMath.inl>
#include <tlocMath/vector/tlocVector.inl>

namespace tloc { namespace math {

  //////////////////////////////////////////////////////////////////////////
  // Vector3

  //------------------------------------------------------------------------
  // Constructors

  template <typename T>
  TL_FI Vector3<T>::Vector3()
  {
  }

  template <typename T>
  TL_FI Vector3<T>::Vector3(const T& aValue)
  {
    m_values[0] = aValue;
    m_values[1] = aValue;
    m_values[2] = aValue;
  }

  template <typename T>
  TL_FI Vector3<T>::Vector3(const T& aX, const T& aY, const T& aZ)
  {
    m_values[0] = aX;
    m_values[1] = aY;
    m_values[2] = aZ;
  }

  template <typename T>
  TL_FI Vector3<T>::Vector3(const Vector3<T>& aVector)
  {
    m_values[0] = aVector[0];
    m_values[1] = aVector[1];
    m_values[2] = aVector[2];
  }

  template <typename T>
  TL_FI Vector3<T>::Vector3(const Vector<T, 3>& aVector)
  {
    m_values[0] = aVector[0];
    m_values[1] = aVector[1];
    m_values[2] = aVector[2];
  }

  //------------------------------------------------------------------------
  // Math operations

  template <typename T>
  TL_FI Vector3<T>& Vector3<T>::Cross(const Vector3<T>& aVector)
  {
    /*
    y * rkVector.z - z * rkVector.y,
    z * rkVector.x - x * rkVector.z,
    x * rkVector.y - y * rkVector.x);
    */

    Vector3<T> temp(*this);

    m_values[0] = temp[1] * aVector[2] - temp[2] * aVector[1];
    m_values[1] = temp[2] * aVector[0] - temp[0] * aVector[2];
    m_values[2] = temp[0] * aVector[1] - temp[1] * aVector[0];

    return *this;
  }

  template <typename T>
  TL_FI void Vector3<T>::Cross(const Vector3<T>& aVector1,
    const Vector3<T>& aVector2)
  {
    this->operator=(aVector1);
    Cross(aVector2);
  }

  template <typename T>
  TL_FI void Vector3<T>::FastNorm(const Vector3<T>& aVector)
  {
    f32 lLength;
    lLength = (f32)aVector.LengthSquared();

    // Calculate length inverse
    float xhalf = 0.5f*lLength;
    int i = *(int*)&lLength; // get bits for floating value
    i = 0x5f375a86- (i>>1); // gives initial guess y0
    lLength = *(float*)&i; // convert bits back to float
    lLength = lLength*(1.5f-xhalf*lLength*lLength); // Newton step, repeating increases accuracy

    m_values[0] *= lLength;
    m_values[1] *= lLength;
    m_values[2] *= lLength;
  }

  template <typename T>
  TL_FI void Vector3<T>::FastNorm()
  {
    f32 lLength;
    lLength = (f32)this->LengthSquared();

    // Calculate length inverse
    f32 xhalf = 0.5f*lLength;
    s32 i = *(s32*)&lLength; // get bits for floating value
    i = 0x5f375a86- (i>>1); // gives initial guess y0
    lLength = *(f32*)&i; // convert bits back to float
    lLength = lLength*(1.5f-xhalf*lLength*lLength); // Newton step, repeating increases accuracy

    m_values[0] *= (T)lLength;
    m_values[1] *= (T)lLength;
    m_values[2] *= (T)lLength;
  }

};};

#endif