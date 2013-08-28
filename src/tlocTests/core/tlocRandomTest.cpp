#include "tlocTestCommon.h"

#include <tlocCore/rng/tlocRandom.h>

namespace TestingRandom
{
  using namespace tloc;

  TEST_CASE("Math/Random/RngWell512", "")
  {
    using namespace tloc::core;

    const u32 numberOfTests = 100;

    bool testPassed = true;
    for (u32 i = 0; i < numberOfTests; ++i)
    {
      tl_float randomNumber = rng::g_defaultRNG.GetRandomFloat();
      if( (randomNumber >= 0 && randomNumber < 1.0f) == false)
      { testPassed = false; break; }
    }
    CHECK(testPassed);

    testPassed = true;
    for (u32 i = 0; i < numberOfTests; ++i)
    {
      tl_float randomNumber = rng::g_defaultRNG.GetRandomFloat(1.0f, 50.0f);
      if( (randomNumber >= 1.0f && randomNumber < 50.0f) == false)
      { testPassed = false; break; }
    }
    CHECK(testPassed);

    testPassed = true;
    for (u32 i = 0; i < numberOfTests; ++i)
    {
      tl_int randomNumber = rng::g_defaultRNG.GetRandomInteger(1, 7);
      if( (randomNumber >= 1 && randomNumber < 7) == false)
      { testPassed = false; break; }
    }
    CHECK(testPassed);
  }

};