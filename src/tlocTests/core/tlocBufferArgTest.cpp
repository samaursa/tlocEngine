#include "tlocTestCommon.h"

#include <tlocCore/memory/tlocBufferArg.h>

#include <tlocCore/string/tlocString.h>

namespace TestingBufferPtr
{
  using namespace tloc;
  using namespace core;
  using namespace string;

  TEST_CASE("Core/Memory/BufferPtr", "")
  {
    {
      const char* someBuff = "ABCDEFGHIJKLMNOPQRST";
      BufferArg buffPtr(someBuff);
      CHECK(buffPtr.IsValid() == true);

      const char8* implicitConversion = buffPtr;
      CHECK(core_mem::StrCmp(implicitConversion, buffPtr) == 0);

      // Added this test because the normal StrCmp function is not selected
      // because implicit type conversion is not allowed in templated functions
      BufferArg buffPtr2(someBuff);
      CHECK(core_mem::StrCmp(buffPtr, buffPtr2) == 0);
    }

    {
      char* someBuff = "ABCDEFGHIJKLMNOPQRST";
      BufferArg buffPtr(someBuff);
      CHECK(buffPtr.IsValid() == true);
    }

    {
      char someBuff[] = {'a', 'b', 'c', 'd', '\0'};
      BufferArg buffPtr(someBuff);
      CHECK(buffPtr.IsValid() == true);
      CHECK( (StrCmp("abcd", buffPtr) == 0) );
    }

    {
      String someStr = "ABCDEFGHIJKLMNOP";
      BufferArg buffPtr(someStr);
      CHECK(buffPtr.IsValid() == true);
      CHECK(StrCmp(someStr.c_str(), buffPtr) == 0);
    }
    {
      const tl_size maxSize = BufferArg::GetMaxAllowedBuffSize();

      String someStr(maxSize + 1, 'a');
      BufferArg buffPtr(someStr.c_str());
      CHECK(buffPtr.IsValid() == false);
    }
  }
};