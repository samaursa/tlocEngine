#include "tlocTestCommon.h"
#include <tlocCore/types/tlocTypeTraits.h>

namespace TESTING_TYPES
{
  using namespace tloc;

  struct base
  {
  };

  struct derived : public base
  {
  };

  struct derivedFurther : public derived
  {
  };

  struct foo
  {
  };

  TEST_CASE("core/types/type_traits/common_type/integral types", "")
  {
    /* does not work (well) with integral types as they result in data loss */
  }

  TEST_CASE("core/types/type_traits/common_type/complex types", "")
  {
    CHECK(
      (
        Loki::IsSameType
        <
          type_traits::common_type<base, derived>::type, base
        >::value
      ) == 1);

    CHECK(
      (
        Loki::IsSameType
        <
          type_traits::common_type<derived, base>::type, base
        >::value
      ) == 1);

    CHECK(
      (
        Loki::IsSameType
        <
          type_traits::common_type<derivedFurther, base>::type, base
        >::value
      ) == 1);

    CHECK(
      (
        Loki::IsSameType
        <
          type_traits::common_type<base, derivedFurther>::type, base
        >::value
      ) == 1);

    CHECK_FALSE(
      (
        Loki::IsSameType
        <
        type_traits::common_type<base, derivedFurther>::type,
        type_traits::no_common_type_exists
        >::value
      ) == 1);

    CHECK_FALSE(
      (
        Loki::IsSameType
        <
          type_traits::common_type<foo, base>::type, base
        >::value
      ) == 1);

    CHECK_FALSE(
      (
        Loki::IsSameType
        <
          type_traits::common_type<base, foo>::type, base
        >::value
      ) == 1);

    CHECK(
      (
        Loki::IsSameType
        <
          type_traits::common_type<base, foo>::type,
          type_traits::no_common_type_exists
        >::value
      ) == 1);
  }
};
