#include "tlocTestCommon.h"

#include <tlocCore/memory/tlocBufferArg.h>

#include <tlocCore/string/tlocString.h>
#include <tlocCore/string/tlocString.inl.h>

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

      const char* implicitConversion = buffPtr;
      CHECK(StrCmp(implicitConversion, buffPtr) == 0);
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