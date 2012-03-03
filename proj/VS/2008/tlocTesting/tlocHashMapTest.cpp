#include "tlocTestCommon.h"

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocTypes.inl"

#include "tlocCore/tlocHashmap.h"
#include "tlocCore/tlocHashmap.inl"

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
    HashMap<char8*, s32, hash<char8*>, eqstr> test;

    test["asdf"] = 10;

    CHECK(test["asdf"] == 10);
  }



};