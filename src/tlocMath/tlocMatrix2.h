#pragma once
#ifndef TLOC_MATRIX_2_H
#define TLOC_MATRIX_2_H

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTable.h"
#include "tlocMath/tlocVector.h"
#include "tlocMath/tlocMatrix.h"

namespace tloc
{
  template <typename T>
  class Matrix2 : public Matrix<T, 2>
  {
  public:
    //------------------------------------------------------------------------
    // Constructors

    // Empty default constructor
    TL_FI Matrix2();
    TL_FI Matrix2(const Matrix2<T>& aMatrix);

    TL_FI explicit Matrix2(const T& aValue);
    TL_FI Matrix2(const T values[MATRIX_SIZE], TABLE_ORDER aOrder);

  };

#include "tlocMatrix2.inl"
};

#endif