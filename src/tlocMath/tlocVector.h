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
    FW_FI const T& operator[](FwUInt32 aIndex)const;

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

    // Used by Length() and FastLength()
    FW_FI void LengthSquared(T& aReal);

    // This is a costly operation, consider FastLength() instead.
    FW_FI void Length(T& aReal);

  private:

    T values[aSize];
  };

#include "tlocVector.inl"

};

#endif