#include "tlocTestCommon.h"

#include <tlocCore/utilities/tlocGroupID.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl>

namespace TestingGroupID
{
  using namespace tloc;
  using namespace tloc::core::containers;

  struct obj : public core::utils::GroupID<obj>
  {
  };

  TEST_CASE("Core/Utilities/GroupID", "")
  {
    const s32 count = 20;

    {
      Array<obj> a;
      a.push_back(obj());
      CHECK(a.back().GetUniqueGroupID() == 2); // obj was created twice

      for (s32 i = 0; i < count; ++i)
      {
        a.push_back(obj());
      }

      CHECK(a.back().GetUniqueGroupID() > count);
    }

    {
      Array<obj> a;

      for (s32 i = 0; i < count; ++i)
      {
        a.push_back(obj());
      }

      bool testPassed = true;
      for (Array<obj>::iterator itr = a.begin(), itrEnd = a.end();
           itr != itrEnd; ++itr)
      {
        for (Array<obj>::iterator itr2 = itr, itrEnd2 = a.end();
             itr2 != itrEnd2;)
        {
          ++itr2;
          if (itr->GetUniqueGroupID() == itr2->GetUniqueGroupID())
          {
            testPassed = false;
            break;
          }
        }
      }

      // Uniqueness test failed
      CHECK(testPassed);
    }
  }
};