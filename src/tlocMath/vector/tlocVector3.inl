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

  //////////////////////////////////////////////////////////////////////////
  // Template Macros

#define VECTOR_3_TYPES typename T
#define VECTOR_3_PARAMS T

  //------------------------------------------------------------------------
  // Constructors

  template <VECTOR_3_TYPES>
  TL_FI Vector3<VECTOR_3_PARAMS>::Vector3()
  {
  }

  template <VECTOR_3_TYPES>
  TL_FI Vector3<VECTOR_3_PARAMS>::Vector3(const_reference aValue)
  {
    m_values[0] = aValue;
    m_values[1] = aValue;
    m_values[2] = aValue;
  }

  template <VECTOR_3_TYPES>
  TL_FI Vector3<VECTOR_3_PARAMS>::Vector3(const_reference aX, 
                            const_reference aY, 
                            const_reference aZ)
  {
    m_values[0] = aX;
    m_values[1] = aY;
    m_values[2] = aZ;
  }

  template <VECTOR_3_TYPES>
  TL_FI Vector3<VECTOR_3_PARAMS>::Vector3(const this_type& aVector)
  {
    m_values[0] = aVector[0];
    m_values[1] = aVector[1];
    m_values[2] = aVector[2];
  }

  template <VECTOR_3_TYPES>
  TL_FI Vector3<VECTOR_3_PARAMS>::Vector3(const base_type& aVector)
  {
    m_values[0] = aVector[0];
    m_values[1] = aVector[1];
    m_values[2] = aVector[2];
  }

  //------------------------------------------------------------------------
  // Math operations

  template <VECTOR_3_TYPES>
  TL_FI typename Vector3<VECTOR_3_PARAMS>::this_type& 
    Vector3<VECTOR_3_PARAMS>::Cross(const this_type& aVector)
  {
    /*
    y * rkVector.z - z * rkVector.y,
    z * rkVector.x - x * rkVector.z,
    x * rkVector.y - y * rkVector.x);
    */

    this_type temp(*this);

    m_values[0] = temp[1] * aVector[2] - temp[2] * aVector[1];
    m_values[1] = temp[2] * aVector[0] - temp[0] * aVector[2];
    m_values[2] = temp[0] * aVector[1] - temp[1] * aVector[0];

    return *this;
  }

  template <VECTOR_3_TYPES>
  TL_FI void Vector3<VECTOR_3_PARAMS>::Cross(const this_type& aVector1,
                                            const this_type& aVector2)
  {
    *this = aVector1;
    Cross(aVector2);
  }

  template <VECTOR_3_TYPES>
  TL_FI void Vector3<VECTOR_3_PARAMS>::FastNorm(const this_type& aVector)
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

  template <VECTOR_3_TYPES>
  TL_FI void Vector3<VECTOR_3_PARAMS>::FastNorm()
  {
    f32 lLength;
    lLength = (f32)LengthSquared();

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