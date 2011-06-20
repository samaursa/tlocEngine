#pragma once
#ifndef TLOC_VECTOR_N_H
#define TLOC_VECTOR_N_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTuple.h"
#include "tlocCore/tlocStandardFuncs.h"

#include "tlocMath/tlocMath.h"

// If defined, easy math operations such as +,-,/,* will be available,
// otherwise, explicit functions must be called. This can be selectively
// turned on/off for different files depending on performance requirements
#define TLOC_VECTOR_ALLOW_EASY_OPERATIONS

// If defined, simple assertions will be enabled in this class. Enabled by
// default in debug
#ifdef TLOC_DEBUG
#define TLOC_VECTOR_ENABLE_ASSERTS
#endif

// If assertions are not enabled, we do not want TLOC_ASSERT to work anymore
#ifdef TLOC_VECTOR_ENABLE_ASSERTS
#define TLOC_ASSERT_VEC(_Expression, _Msg) TLOC_ASSERT(_Expression, _Msg)
#else
#define TLOC_ASSERT_VEC(_Expression, _Msg)
#endif

namespace tloc
{
  //////////////////////////////////////////////////////////////////////////
  // Vector<N>

  template <typename T, u32 T_Size>
  class Vector : public Tuple<T, T_Size>
  {
  public:
    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    TL_FI Vector();
    TL_FI Vector(const Vector<T, T_Size>& aVector);

    TL_FI explicit Vector(const T& aValue);    

    /*TL_FI T& operator[](u32 aIndex);
    TL_FI const T& operator[](u32 aIndex) const;*/

    //------------------------------------------------------------------------
    // Modifiers

    // Modifies this vector so that all values are zero. The vector must
    // be of numerical types
    TL_FI void Zero();

    // Negate this vector
    TL_FI void Neg();

    // Modifies this vector by storing the negation of the incoming vector
    TL_FI void Neg(const Vector<T, T_Size>& aVector);

    //// All values of this vector will equal the incoming vector
    //TL_FI Vector<T, aSize>& operator=(const Vector<T, aSize>& aVector);

    //------------------------------------------------------------------------
    // Math Operations

    // Modifies this vector by adding the incoming vector
    TL_FI void Add(const Vector<T, T_Size>& aVector);

    // Modifies this vector by adding the incoming vectors and storing the 
    // result in this vector
    TL_FI void Add(const Vector<T, T_Size>& aVector1, 
                   const Vector<T, T_Size>& aVector2);

    // Modifies this vector by subtracting the incoming vector
    TL_FI void Sub(const Vector<T, T_Size>& aVector);

    // Modifies this vector by subtracting the incoming vectors and storing 
    // the result in this vector
    TL_FI void Sub(const Vector<T, T_Size>& aVector1, 
                   const Vector<T, T_Size>& aVector2);

    // Multiply each element of this vector by the elements of the incoming 
    // Vector
    TL_FI void Mul(const Vector<T, T_Size>& aVector);
    
    // Modifies this vector by multiplying the incoming vectors and storing 
    // the result in this vector
    TL_FI void Mul(const Vector<T, T_Size>& aVector1, 
                   const Vector<T, T_Size>& aVector2);    

    // Multiplies each element of this vector by the constant and stores the
    // the result in this vector
    TL_FI void Mul(const T aReal);    

    // Divides each element of this vector by the elements of the incoming 
    // Vector
    TL_FI void Div(const Vector<T, T_Size>& aVector);    

    // Modifies this vector by dividing the incoming vectors and storing 
    // the result in this vector
    TL_FI void Div(const Vector<T, T_Size>& aVector1, 
                   const Vector<T, T_Size>& aVector2);    

    // Divides each element of this vector by the constant and stores the
    // the result in this vector
    TL_FI void Div(const T aReal);    

    // Used by Length()
    TL_FI void LengthSquared(T& aReal) const;

    // Same as Length() but returns the value instead
    TL_FI T LengthSquared() const;

    // This is a costly operation, consider using LengthSquared() if possible
    TL_FI void Length(T& aReal) const;

    // Same as Length() but returns the value instead
    TL_FI T Length() const;

    // Normalizes this vector
    TL_FI void Norm();    

    // Same as Norm(), but returns the length as well
    TL_FI T NormLength();

    // Modifies this vector to store the normalized version of the incoming
    // vector. 
    TL_FI void Norm(const Vector<T, T_Size>& aVector);

    // Same as Norm() but returns the length as well
    TL_FI T NormLength(const Vector<T, T_Size>& aVector);

    // Returns the distance between two vectors (expensive operation). Use
    // DistanceApprox() for a faster (with more error) result
    TL_FI T Distance(const Vector<T, T_Size>& aVector) const;

    // Returns the distance squared between two vectors (faster than 
    // Distance())
    TL_FI T DistanceSquared(const Vector<T, T_Size>& aVector) const;

    // Returns the dot product between this and the incoming vector
    TL_FI T Dot(const Vector<T, T_Size>& aVector) const;

    // Returns the absolute dot product between this and the incoming vector
    TL_FI T DotAbs(const Vector<T, T_Size>& aVector) const;

    // Modifies this vector by storing the midpoint between this vector
    // and the incoming vector
    TL_FI void Midpoint(const Vector<T, T_Size>& aVector);

    // Modifies this vector by storing the midpoint between the two 
    // incoming vectors
    TL_FI void Midpoint(const Vector<T, T_Size>& aVector1,
                        const Vector<T, T_Size>& aVector2);

    //------------------------------------------------------------------------
    // Comparisons

    TL_FI bool operator==(const Vector<T, T_Size>& aVector);
    TL_FI bool operator!=(const Vector<T, T_Size>& aVector);
    
    //------------------------------------------------------------------------
    // Checks

    // Returns false if the vector's values are invalid (NaN)
    TL_FI bool IsValid();
    TL_FI bool IsZero();

    //------------------------------------------------------------------------
    // Special vectors

    static const Vector<T, T_Size> ZERO;
    static const Vector<T, T_Size> ONE;    
  };

  //------------------------------------------------------------------------
  // Static const definitions
  template<typename T, u32 T_Size> 
  const Vector<T, T_Size> Vector<T, T_Size>::ZERO(Vector<T, T_Size>(0));
  template<typename T, u32 T_Size> 
  const Vector<T, T_Size> Vector<T, T_Size>::ONE(Vector<T, T_Size>(1));
};

#ifdef TLOC_FULL_SOURCE
#include "tlocVector.inl"
#endif

#endif