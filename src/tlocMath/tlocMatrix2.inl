//////////////////////////////////////////////////////////////////////////
// Matrix2f<T>

//------------------------------------------------------------------------
// Constructors

template <typename T>
TL_FI Matrix2<T>::Matrix2() 
: Matrix() {}

template <typename T>
TL_FI Matrix2<T>::Matrix2(const Matrix2<T>& aMatrix) 
: Matrix(aMatrix) {}

template <typename T>
TL_FI Matrix2<T>::Matrix2(const T& aValue) 
: Matrix(aValue) {}

template <typename T>
TL_FI Matrix2<T>::Matrix2(const T values[MATRIX_SIZE], TABLE_ORDER aOrder)
: Matrix(values, aOrder) {}