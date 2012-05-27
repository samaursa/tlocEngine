#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTypes.inl>

#include <tlocCore/containers/tlocHashmap.h>
#include <tlocCore/containers/tlocHashmap.inl>

namespace TestingHashMap
{
  USING_TLOC;
  using namespace core;

  struct HashMapFixture
  {

  };

  struct eqstr
  {
    bool operator()(const char8* s1, const char8* s2) const
    {
      return strcmp(s1, s2) == 0;
    }
  };

  TEST_CASE_METHOD(HashMapFixture, "Core/Containers/HashMap/Ctors", "")
  {
    HashMap<char8*, s32, hash<char8*>, eqstr, true> test;

    char* someKey = "asdf";

    test[someKey] = 10;

    CHECK(test[someKey] == 10);
  }



};