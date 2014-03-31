/// This implementation is written by Gregory Pakosz: http://stackoverflow.com/a/1980156/368599
/// Some names were changed to avoid future conflicts.

#ifndef _TLOC_CORE_STATIC_ASSERT_H_
#define _TLOC_CORE_STATIC_ASSERT_H_

#define STATIC_ASSERT_CONCATENATE(arg1, arg2)   STATIC_ASSERT_CONCATENATE1(arg1, arg2)
#define STATIC_ASSERT_CONCATENATE1(arg1, arg2)  STATIC_ASSERT_CONCATENATE2(arg1, arg2)
#define STATIC_ASSERT_CONCATENATE2(arg1, arg2)  arg1##arg2

/**
 * Usage:
 *
 * <code>STATIC_ASSERT(expression, message)</code>
 *
 * When the static assertion test fails, a compiler error message that somehow
 * contains the "STATIC_ASSERTION_FAILED_AT_LINE_xxx_message" is generated.
 *
 * /!\ message has to be a valid C++ identifier, that is to say it must not
 * contain space characters, cannot start with a digit, etc.
 *
 * STATIC_ASSERT(true, this_message_will_never_be_displayed);
 */

#define STATIC_ASSERT(expression, message)\
  struct STATIC_ASSERT_CONCATENATE(__static_assertion_at_line_, __LINE__)\
  {\
  static_assert_implementation::StaticAssertion<static_cast<bool>((expression))> STATIC_ASSERT_CONCATENATE(STATIC_ASSERT_CONCATENATE(STATIC_ASSERT_CONCATENATE(STATIC_ASSERTION_FAILED_AT_LINE_, __LINE__), _), _xxxxxxxxxxxxx_##message);\
  };\
  typedef static_assert_implementation::StaticAssertionTest<sizeof(STATIC_ASSERT_CONCATENATE(__static_assertion_at_line_, __LINE__))> STATIC_ASSERT_CONCATENATE(__static_assertion_test_at_line_, __LINE__)

  // note that we wrap the non existing type inside a struct to avoid warning
  // messages about unused variables when static assertions are used at function
  // scope
  // the use of sizeof makes sure the assertion error is not ignored by SFINAE

namespace static_assert_implementation {

  template <bool>
  struct StaticAssertion;

  template <>
  struct StaticAssertion<true>
  {
  }; // StaticAssertion<true>

  template<int i>
  struct StaticAssertionTest
  {
  }; // StaticAssertionTest<int>

} // namespace implementation

// ///////////////////////////////////////////////////////////////////////
// Static Assert

// TODO: solve static assert problems on LLVM
#ifndef TLOC_DISABLE_STATIC_ASSERT
# define TLOC_STATIC_ASSERT(_Expression, _Msg) STATIC_ASSERT(_Expression, _Msg##_xxxxxxxxxxxxx_)
#else
# define TLOC_STATIC_ASSERT(_Expression, _Msg)
#endif

# define TLOC_STATIC_ASSERT_FALSE(_type_, _Msg) \
  TLOC_STATIC_ASSERT((Loki::IsSameType<_type_, UniqueDummyStruct>::value), _Msg)

# define TLOC_STATIC_ASSERT_WIP() \
  TLOC_STATIC_ASSERT(false, This_Function_Is_Unfinished)

# define TLOC_STATIC_ASSERT_IS_POINTER(_Type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_Type_>::isPointer, Type_must_be_a_POINTER)
# define TLOC_STATIC_ASSERT_IS_NOT_POINTER(_Type_) \
  TLOC_STATIC_ASSERT( (!Loki::TypeTraits<_Type_>::isPointer), Type_CANNOT_be_a_pointer)
# define TLOC_STATIC_ASSERT_IS_REFERENCE(_Type_) \
  TLOC_STATIC_ASSERT( (Loki::TypeTraits<_Type_>::isReference), Type_must_be_a_REFERENCE)
# define TLOC_STATIC_ASSERT_IS_NOT_REFERENCE(_Type_) \
  TLOC_STATIC_ASSERT( (!Loki::TypeTraits<_Type_>::isReference), Type_CANNOT_be_a_reference)

# define TLOC_STATIC_ASSERT_IS_FLOAT(_type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_type_>::isFloat, Type_must_be_a_FLOAT)
# define TLOC_STATIC_ASSERT_IS_ARITH(_type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_type_>::isArith, Type_must_be_an_ARITHMETIC)
# define TLOC_STATIC_ASSERT_IS_INTEGRAL(_type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_type_>::isIntegral, Type_must_be_an_INTEGRAL)
# define TLOC_STATIC_ASSERT_IS_INTEGRAL(_type_) \
  TLOC_STATIC_ASSERT(Loki::TypeTraits<_type_>::isIntegral, Type_must_be_an_INTEGRAL)
# define TLOC_STATIC_ASSERT_NOT_SUPPORTED(_type_, _toCompare_) \
  TLOC_STATIC_ASSERT( !(Loki::IsSameType<_type_, _toCompare_>::value), Type_not_supported)


#endif