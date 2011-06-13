#ifndef TLOC_MATRIX_H
#define TLOC_MATRIX_H

namespace tloc
{
  template <typename T, typename T_ROWS, typename T_COLS>
  class Matrix
  {
  public:

    // Empty default constructor
    Matrix();
    Matrix(const Matrix<T, T_ROWS, T_COLS>& aMatrix);
    
  };
};

#endif