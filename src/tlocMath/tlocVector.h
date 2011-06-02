#ifndef VECTOR_3_H
#define VECTOR_3_H

#include "tlocCore\tlocBase.h"
#include "tlocCore\tlocStandardFuncs.h"

#include <cmath>

typedef unsigned int FwUInt32;

// If defined, easy math operations such as +,-,/,* will be available
// otherwise, explicit functions must be called. This can be selectively
// turned on/off for different files depending on performance requirements
#define FW_VECTOR_ALLOW_EASY_OPERATIONS

#define FW_VECTOR_ENABLE_ASSERTS

#define FW_FORCE_INLINE __forceinline
#define FW_FI FW_FORCE_INLINE

namespace tloc
{

#define ITERATE_VECTOR for (FwUInt32 i = 0; i < aSize; ++i)

  template <typename T, FwUInt32 aSize>
  class Vector
  {
  public:
    // Empty default constructor
    Vector();
    Vector(T aValue);
    Vector(const Vector<T, aSize>& aVector);

    FW_FI T& operator[](FwUInt32 aIndex);
    FW_FI const T& operator[](FwUInt32 aIndex) const;

    // Modifies this vector so that all values of this vector equal aValue
    FW_FI void Set(T aValue);

    // Modifies this vector so that all values are zero
    FW_FI void Zero();

    // Swaps the vector with the incoming vector
    FW_FI void Swap(Vector<T, aSize>& aVector);

    // Negate this vector
    FW_FI void Neg();

    // Modifies this vector by storing the negation of the incoming vector
    FW_FI void Neg(const Vector<T, aSize>& aVector);

    // All values of this vector will equal the incoming vector
    FW_FI void operator=(const Vector<T, aSize>& aVector);

    // Modifies this vector by adding the incoming vector
    FW_FI void Add(const Vector<T, aSize>& aVector);

    // Modifies this vector by adding the incoming vectors and storing the 
    // result in this vector
    FW_FI void Add(const Vector<T, aSize>& aVector1, 
                   const Vector<T, aSize>& aVector2);

    // Modifies this vector by subtracting the incoming vector
    FW_FI void Sub(const Vector<T, aSize>& aVector);

    // Modifies this vector by subtracting the incoming vectors and storing 
    // the result in this vector
    FW_FI void Sub(const Vector<T, aSize>& aVector1, 
                   const Vector<T, aSize>& aVector2);

    // Multiply each element of this vector by the elements of the incoming 
    // Vector
    FW_FI void Mul(const Vector<T, aSize>& aVector);
    
    // Modifies this vector by multiplying the incoming vectors and storing 
    // the result in this vector
    FW_FI void Mul(const Vector<T, aSize>& aVector1, 
                   const Vector<T, aSize>& aVector2);    

    // Multiplies each element of this vector by the constant and stores the
    // the result in this vector
    FW_FI void Mul(const T aReal);    

    // Divides each element of this vector by the elements of the incoming 
    // Vector
    FW_FI void Div(const Vector<T, aSize>& aVector);    

    // Modifies this vector by dividing the incoming vectors and storing 
    // the result in this vector
    FW_FI void Div(const Vector<T, aSize>& aVector1, 
             const Vector<T, aSize>& aVector2);    

    // Divides each element of this vector by the constant and stores the
    // the result in this vector
    FW_FI void Div(const T aReal);    

    // Used by Length()
    FW_FI void LengthSquared(T& aReal) const;

    // Same as Length() but returns the value instead
    FW_FI T LengthSquared() const;

    // This is a costly operation, consider using LengthSquared() if possible
    FW_FI void Length(T& aReal) const;

    // Same as Length() but returns the value instead
    FW_FI T Length() const;

    // Normalizes this vector
    FW_FI void Norm();    

    // Same as Norm(), but returns the length as well
    FW_FI T NormLength();

    // Modifies this vector to store the normalized version of the incoming
    // vector. Consider using FastNorm() taking into account the accuracy
    // requirements.
    FW_FI void Norm(const Vector<T, aSize>& aVector);

    // Same as Norm() but returns the length as well
    FW_FI T NormLength(const Vector<T, aSize>& aVector);

    // Modifies this vector to store the normalized version of the incoming
    // vector with an approx 3% error. Inverse square root code taken from
    // http://www.codemaestro.com/reviews/9 (originally from Quake)
    FW_FI void FastNorm(const Vector<T, aSize>& aVector);

    // Same as FastNorm() but modifies this vector directly
    FW_FI void FastNorm();

    // Returns the distance between two vectors (expensive operation)
    FW_FI T Distance(const Vector<T, aSize>& aVector);

    // Returns the distance squared between two vectors (faster than 
    // Distance())
    FW_FI T DistanceSquared(const Vector<T, aSize>& aVector);

    // Returns the dot product between this and the incoming vector
    FW_FI T Dot(const Vector<T, aSize>& aVector);

    // Returns the absolute dot product between this and the incoming vector
    FW_FI T DotAbs(const Vector<T, aSize>& aVector);

    // Modifies this vector by storing the midpoint between this vector
    // and the incoming vector
    FW_FI void Midpoint(const Vector<T, aSize>& aVector);

    // Modifies this vector by storing the midpoint between the two 
    // incoming vectors
    FW_FI void Midpoint(const Vector<T, aSize>& aVector1,
                        const Vector<T, aSize>& aVector2);

  protected:

    T values[aSize];
  };

  template<typename T>
  class Vector3 : public Vector<T, 3>
  {
  public:
    Vector3() {}
    Vector3(T aValue) 
    {
      values[0] = aValue;
      values[1] = aValue;
      values[2] = aValue;
    }
    Vector3(T aX, T aY, T aZ)
    {
      values[0] = aX;
      values[1] = aY;
      values[2] = aZ;
    }
    Vector3(const Vector3<T>& aVector)
    {
      values[0] = aVector[0];
      values[1] = aVector[1];
      values[2] = aVector[2];
    }

    // Modifies this vector by storing the cross product between this vector
    // and the incoming vector
    FW_FI void Cross(const Vector3<T>& aVector);

    // Modifies this vector by storing the cross product between the two
    // incoming vectors
    FW_FI void Cross(const Vector3<T>& aVector1, 
                     const Vector3<T>& aVector2);

  };

  typedef Vector3<float> Vec3f;

#include "tlocVector.inl"

};

#endif