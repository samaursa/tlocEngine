#include "tlocTestCommon.h"

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/memory/tlocMemoryPool.inl>

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl>

#include <set>

namespace TestingMemoryPool
{
  USING_TLOC;

  TEST_CASE("Core/MemoryPool/General", "")
  {
    // TODO: Clean up these tests (put each one in its own TEST_CASE)

    const tl_size count = 10;

    typedef core::MemoryPoolIndex<tl_int> memory_pool_type;
    memory_pool_type myPool;
    myPool.Initialize(count);

    CHECK(myPool.GetAvail() == count);

    for (tl_int i = 0; i < count; ++i)
    {
      myPool.GetNext();
    }

    CHECK(myPool.IsValid(myPool.GetNext()) == false);
    CHECK(myPool.GetUsed() == count);

    for (tl_int i = 0; i < count; ++i)
    {
      myPool.Recycle(0);
    }

    CHECK(myPool.GetAvail() == count);

    for (tl_int i = 0; i < count; ++i)
    {
      myPool.GetNext().GetElement() = i;
    }

    for (tl_int i = 0; i < count; ++i)
    {
      const tl_int indexToRecycle = 0;
      const tl_int elementToCheck = myPool[0].GetElement();

      myPool.Recycle(indexToRecycle);

      for (memory_pool_type::iterator itr = myPool.begin(), itrEnd = myPool.end();
           itr != itrEnd; ++itr)
      {
        CHECK(itr->GetElement() != elementToCheck);
      }
    }

    CHECK(myPool.GetAvail() == count);
  }
};