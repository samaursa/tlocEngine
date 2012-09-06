#include "tlocTestCommon.h"

#include <tlocCore/utilities/tlocGroupID.h>
#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl>

namespace TestingGroupID
{
  USING_TLOC;

  struct obj : public core::utils::GroupID<obj>
  {
  };

  TEST_CASE("Core/Utilities/GroupID", "")
  {
    const tl_int count = 20;

    {
      core::Array<obj> a;
      a.push_back(obj());
      CHECK(a.back().GetUniqueGroupID() == 2); // obj was created twice

      for (tl_int i = 0; i < count; ++i)
      {
        a.push_back(obj());
      }

      CHECK(a.back().GetUniqueGroupID() > count);
    }

    {
      core::Array<obj> a;

      for (tl_int i = 0; i < count; ++i)
      {
        a.push_back(obj());
      }

      bool testPassed = true;
      for (core::Array<obj>::iterator itr = a.begin(), itrEnd = a.end();
           itr != itrEnd; ++itr)
      {
        for (core::Array<obj>::iterator itr2 = itr, itrEnd2 = a.end();
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