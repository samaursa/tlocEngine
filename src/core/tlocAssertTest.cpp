#include "tlocTestCommon.h"

#include <tlocCore/tlocAssert.h>

namespace TestingAssert
{
  TEST_CASE("Test assertion throw", "")
  {
    TLOC_TEST_ASSERT
    {
      throw tloc::tests::exception::Assert();
    }
    TLOC_TEST_ASSERT_CHECK();
  }
};