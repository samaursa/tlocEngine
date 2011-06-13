//////////////////////////////////////////////////////////////////////////
// Matrix<N, N>

//------------------------------------------------------------------------
// Macros

#define ITERATE_MATRIX for (u32 i = 0; i < TABLE_SIZE; ++i)

//------------------------------------------------------------------------
// Constructors

template <typename T, u32 T_SIZE>
TL_FI Matrix<T, T_SIZE>::Matrix()
: Table() {}

template <typename T, u32 T_SIZE>
TL_FI Matrix<T, T_SIZE>::Matrix(const Matrix<T, T_SIZE>& aMatrix)
: Table(aMatrix) {}

template <typename T, u32 T_SIZE>
TL_FI Matrix<T, T_SIZE>::Matrix(const T& aValue)
: Table(aValue) {}

template <typename T, u32 T_SIZE>
TL_FI Matrix<T, T_SIZE>::Matrix(const T values[MATRIX_SIZE], MATRIX_ORDER aOrder)
: Table(values, aOrder) {}