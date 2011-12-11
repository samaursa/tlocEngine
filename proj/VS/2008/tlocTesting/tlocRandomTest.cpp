#include "tlocTestCommon.h"

#include "tlocMath/tlocRngWell512.h"
#include "tlocMath/tlocRngWell512.inl"

namespace TestingRandom
{
  using namespace tloc;
  using namespace tloc::math;

  TEST_CASE("Math/Random/RngWell512", "")
  {
    rng_well_512 random;

    const u32 numberOfTests = 100;

    for (u32 i = 0; i < numberOfTests; ++i)
    {
      f32 randomNumber = random.GetRandomFloat();
      CHECK( (randomNumber >= 0 && randomNumber < 1.0f) == true);
    }

    for (u32 i = 0; i < numberOfTests; ++i)
    {
      f32 randomNumber = random.GetRandomFloat(1.0f, 50.0f);
      CHECK( (randomNumber >= 1.0f && randomNumber <= 50.0f) == true);
    }

    for (u32 i = 0; i < numberOfTests; ++i)
    {
      u32 randomNumber = random.GetRandomInteger(1, 100);
      CHECK( (randomNumber >= 1 && randomNumber <= 100) == true);
    }
  }

};