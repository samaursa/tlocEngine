#include "tlocTestCommon.h"

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/memory/tlocMemoryPool.inl>

namespace TestingMemoryPool
{
  USING_TLOC;

  TEST_CASE("Core/MemoryPool/General", "")
  {
    core::MemoryPoolIndex<tl_int> myPool;
    myPool.Initialize(10);
  }
};