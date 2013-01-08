#include "tlocTestCommon.h"

#include <tlocCore/memory/tlocBufferArg.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/string/tlocString.inl>

namespace TestingBufferPtr
{
  using namespace tloc;
  using namespace core;
  using namespace string;

  TEST_CASE("Core/Memory/BufferPtr", "")
  {
    {
      const char* someBuff = "ABCDEFGHIJKLMNOPQRST";
      memory::BufferArg buffPtr(someBuff);
      CHECK(buffPtr.IsValid() == true);
    }
    {
      String someStr = "ABCDEFGHIJKLMNOP";
      memory::BufferArg buffPtr(someStr);
      CHECK(buffPtr.IsValid() == true);
      CHECK(StrCmp(someStr.c_str(), buffPtr.GetPtr()) == 0);
    }
    {
      const tl_size maxSize = memory::BufferArg::GetMaxAllowedBuffSize();

      String someStr(maxSize + 1, 'a');
      memory::BufferArg buffPtr(someStr.c_str());
      CHECK(buffPtr.IsValid() == false);
    }
  }
};