#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTypes.inl>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl>

namespace TestingHashMap
{
  using namespace tloc;
  using namespace core;
  using namespace core::containers;

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

  struct foo
  {
    tl_int m_value;
  };

  TEST_CASE_METHOD(HashMapFixture, "Core/Containers/HashMap/Ctors", "")
  {
    HashMap<char8*, s32, hash<char8*>, eqstr, true> test;

    char* someKey = (char*)"asdf";

    test[someKey] = 10;

    CHECK(test[someKey] == 10);

    const tl_size count = 10;
    typedef tl_hash_map<tl_int, foo*>::type my_map;
    my_map test2;
    CHECK(test2.size() == 0);
    for (int i = 0; i < count; ++i)
    {
      test2[i] = new foo();
      test2[i]->m_value = i;
    }
    CHECK(test2.size() == count);

    CHECK(test2[1]->m_value == 1);
    CHECK(test2.size() == count);

    my_map::iterator itr = test2.find(1);
    CHECK(itr != test2.end());
    CHECK( (*itr).second->m_value == 1);

    itr = test2.find(15);
    CHECK(itr == test2.end());
  }



};