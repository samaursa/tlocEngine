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

#endif