#include "catch.hpp"

#include "tlocCore/tlocBase.h"
#include "tlocCore/tlocMemory.h"
#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocTypes.inl"

#include "tlocCore/tlocList.h"
#include "tlocCore/tlocList.inl"

#include "tlocCore/tlocFunctional.h"

#define protected public
#define private public
#include "tlocCore/tlocHashtable.h"
#include "tlocCore/tlocHashtable.inl"

namespace TestingArray
{
  USING_TLOC;
  using namespace core;

  class SomeClass
  {
  public:
    int dummy;
  };

  struct HashtableFixture
  {
    typedef SinglyList<HashtableElement<s32>, true>::type element_list_type;
    typedef SinglyList<element_list_type, true>::type list_type;

    //typedef Array<HashtableElement<s32> > element_list_type;
    //typedef Array<element_list_type> list_type;

    typedef HashtablePolicy<s32, use_self<s32>, hash<s32>, hash_to_range_mod, range_hash_default,
      equal_to<s32>, prime_rehash_policy, list_type, false, true> hashtable_policies;
  };

  TEST_CASE_METHOD(HashtableFixture, "Core/Containers/Hashtable/Ctors", "")
  {
    Hashtable<hashtable_policies> h(3);

    for (u32 i = 0; i < 100; ++i)
    {
      h.DoInsertValue(i, tloc::type_false());
    }

    Hashtable<hashtable_policies>::iterator itr = h.find_by_hash(5);

  }

};