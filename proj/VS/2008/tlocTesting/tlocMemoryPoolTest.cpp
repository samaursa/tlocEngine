#include "tlocTestCommon.h"

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/memory/tlocMemoryPool.inl>

namespace TestingMemoryPool
{
  USING_TLOC;

  TEST_CASE("Core/MemoryPool/General", "")
  {
    const tl_int count = 10;

    core::MemoryPoolIndex<tl_int> myPool;
    myPool.Initialize(count);

    CHECK(myPool.GetAvail() == count);

    for (tl_int i = 0; i < count; ++i)
    {
      myPool.GetNext();
    }

    CHECK(myPool.GetUsed() == count);

    for (tl_int i = 0; i < count; ++i)
    {
      myPool.Recycle(i);
    }

    CHECK(myPool.GetAvail() == count);

  }
};