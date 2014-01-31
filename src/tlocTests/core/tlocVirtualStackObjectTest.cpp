#include "tlocTestCommon.h"

#include <tlocCore/smart_ptr/tlocVirtualStackObject.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>

using namespace tloc;
using namespace core_sptr;

namespace TestingVirtualStackObject
{
  TEST_CASE("core/smart_ptr/VirtualStackObject/ctors", "")
  {
    VirtualStackObject<int> onStack(10);
    CHECK( (onStack == 10 ) );

    int onStackCopy = onStack;
    CHECK(onStackCopy == 10);

    VirtualStackObject<int>::ptr_type ptrToVSO = onStack.get();
    CHECK(*ptrToVSO == 10);

    VirtualStackObject<int> onStack2(onStack);
    CHECK( (onStack2 == 10) );
  }

  TEST_CASE("core/smart_ptr/VirtualStackObject/operators", "")
  {
    SECTION("comparison", "")
    {
      VirtualStackObject<int> s1(10), s2(20), s3(10);
      CHECK( (s1 == s3) );
      CHECK( (s1 != s2) );
      CHECK_FALSE( (s1 == s2) );
    }

    SECTION("operator=()", "")
    {
      VirtualStackObject<int>  s1(10);
      VirtualStackObject<int>  s2(20);
      s2 = s1;
      CHECK( (s1 == s2) );
    }
  }
}