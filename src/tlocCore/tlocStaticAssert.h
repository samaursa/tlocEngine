/// This implementation is written by Gregory Pakosz: http://stackoverflow.com/a/1980156/368599
/// Some names were changed to avoid future conflicts.

#ifndef _TLOC_CORE_STATIC_ASSERT_H_
#define _TLOC_CORE_STATIC_ASSERT_H_

#include <tlocCore/types/tlocTypeTraits.h>

#define STATIC_ASSERT_CONCATENATE(arg1, arg2)   STATIC_ASSERT_CONCATENATE1(arg1, arg2)
#define STATIC_ASSERT_CONCATENATE1(arg1, arg2)  STATIC_ASSERT_CONCATENATE2(arg1, arg2)
#define STATIC_ASSERT_CONCATENATE2(arg1, arg2)  arg1##arg2

#define STATIC_ASSERT(expression, message) static_assert((expression), message)

// ///////////////////////////////////////////////////////////////////////
// Static Assert

// TODO: solve static assert problems on LLVM
#ifndef TLOC_DISABLE_STATIC_ASSERT
# define TLOC_STATIC_ASSERT(_Expression, _Msg) STATIC_ASSERT((_Expression), #_Msg)
#else
# define TLOC_STATIC_ASSERT(_Expression, _Msg)
#endif

# define TLOC_STATIC_ASSERT_FALSE(_type_, _Msg) \
  TLOC_STATIC_ASSERT((Loki::IsSameType<_type_, UniqueDummyStruct>::value), _Msg)

# define TLOC_STATIC_ASSERT_WIP() \
  TLOC_STATIC_ASSERT(false, This_Function_Is_Unfinished)

# define TLOC_STATIC_ASSERT_IS_POINTER(_Type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_Type_>::isPointer, "Type must be a POINTER")
# define TLOC_STATIC_ASSERT_IS_NOT_POINTER(_Type_) \
  TLOC_STATIC_ASSERT( (!Loki::TypeTraits<_Type_>::isPointer), "Type CANNOT be a POINTER")
# define TLOC_STATIC_ASSERT_IS_REFERENCE(_Type_) \
  TLOC_STATIC_ASSERT( (Loki::TypeTraits<_Type_>::isReference), "Type MUST be a REFERENCE")
# define TLOC_STATIC_ASSERT_IS_NOT_REFERENCE(_Type_) \
  TLOC_STATIC_ASSERT( (!Loki::TypeTraits<_Type_>::isReference), "Type CANNOT be a REFERENCE")

# define TLOC_STATIC_ASSERT_IS_FLOAT(_type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_type_>::isFloat, "Type MUST be a FLOAT")
# define TLOC_STATIC_ASSERT_IS_ARITH(_type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_type_>::isArith, "Type MUST be an ARITHMETIC")
# define TLOC_STATIC_ASSERT_IS_INTEGRAL(_type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_type_>::isIntegral, "Type MUST be an INTEGRAL")
# define TLOC_STATIC_ASSERT_SUPPORTED(_type_, ...) \
  TLOC_STATIC_ASSERT( (type_traits::is_any<_type_, __VA_ARGS__>::value), "Type passed is NOT supported")
# define TLOC_STATIC_ASSERT_NOT_SUPPORTED(_type_, ...) \
  TLOC_STATIC_ASSERT( !(type_traits::is_any<_type_, __VA_ARGS__>::value), "Type passed is NOT supported")


#endif