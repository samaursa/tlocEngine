#include "tlocTestCommon.h"

#include <tlocCore/utilities/tlocObjectCounter.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl>

namespace TestingObjectCounter
{
  USING_TLOC;

  struct obj : public core::utils::ObjectCounter<obj>
  {
  };

  TEST_CASE("Core/Utilities/ObjectCounter", "")
  {
    CHECK(obj::GetCurrentObjectCount() == 0);

    {
      core::Array<obj> objects;
      CHECK(obj::GetCurrentObjectCount() == 0);

      const tl_int count = 100;
      for (tl_int i = 0; i < count; ++i)
      {
        objects.push_back(obj());
      }

      CHECK(obj::GetCurrentObjectCount() == count);
    }

    CHECK(obj::GetCurrentObjectCount() == 0);
  }
};