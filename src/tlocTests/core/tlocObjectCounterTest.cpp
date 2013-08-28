#include "tlocTestCommon.h"

#include <tlocCore/utilities/tlocObjectCounter.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl.h>

namespace TestingObjectCounter
{
  using namespace tloc;

  struct obj : public core::utils::ObjectCounter<obj>
  {
  };

  TEST_CASE("Core/Utilities/ObjectCounter", "")
  {
    CHECK(obj::GetCurrentObjectCount() == 0);

    {
      core::containers::Array<obj> objects;
      CHECK(obj::GetCurrentObjectCount() == 0);

      const s32 count = 100;
      for (s32 i = 0; i < count; ++i)
      {
        objects.push_back(obj());
      }

      CHECK(obj::GetCurrentObjectCount() == count);
    }

    CHECK(obj::GetCurrentObjectCount() == 0);
  }
};