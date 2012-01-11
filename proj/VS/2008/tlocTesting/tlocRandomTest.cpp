#include "tlocTestCommon.h"

#include "tlocCore/tlocRandom.h"

namespace TestingRandom
{
  using namespace tloc;

  TEST_CASE("Math/Random/RngWell512", "")
  {
    using namespace tloc::core;

    const u32 numberOfTests = 100;

    for (u32 i = 0; i < numberOfTests; ++i)
    {
      f32 randomNumber = g_defaultRNG.GetRandomFloat();
      CHECK( (randomNumber >= 0 && randomNumber < 1.0f) == true);
    }

    for (u32 i = 0; i < numberOfTests; ++i)
    {
      f32 randomNumber = g_defaultRNG.GetRandomFloat(1.0f, 50.0f);
      CHECK( (randomNumber >= 1.0f && randomNumber <= 50.0f) == true);
    }

    for (u32 i = 0; i < numberOfTests; ++i)
    {
      u32 randomNumber = g_defaultRNG.GetRandomInteger(1, 100);
      CHECK( (randomNumber >= 1 && randomNumber <= 100) == true);
    }
  }

};