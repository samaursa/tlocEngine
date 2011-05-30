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
    Vector();
    Vector(T aValue);
    Vector(const Vector<T, aSize>& aVector);

    FW_FI T& operator[](FwUInt32 aIndex);
    FW_FI const T& operator[](FwUInt32 aIndex) const;

    FW_FI void Zero();
    FW_FI void Swap(Vector<T, aSize>& aVector);
    // Negate this vector
    FW_FI void Neg();
    // Modifies this vector by storing the negation of the incoming vector
    FW_FI void Neg(const Vector<T, aSize>& aVector);

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

    // This is a costly operation, consider using LengthSquared() if possible
    FW_FI void Length(T& aReal) const;

    // Normalizes this vector
    FW_FI void Norm();    

    // Same as Norm(), but returns the length as well
    FW_FI T NormLength();

    // Modifies this vector to store the normalized version of the incoming
    // vector. Consider using FastNorm() taking into account the accuracy
    // requirements.
    FW_FI void Norm(const Vector<T, aSize>& aVector);

    // Same as Norm() but returns the length as well
    FW_FI void NormLength(const Vector<T, aSize>& aVector);

    // Modifies this vector to store the normalized version of the incoming
    // vector with an approx 3% error. Inverse square root code taken from
    // http://www.codemaestro.com/reviews/9 (originally from Quake)
    FW_FI void FastNorm(const Vector<T, aSize>& aVector);

    // Same as FastNorm() but modifies this vector directly
    FW_FI void FastNorm();

  private:

    T values[aSize];
  };

#include "tlocVector.inl"

};

#endif