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
    typedef s32 value_type;

    typedef HashtableElement<value_type>    e_type;
    typedef SinglyList<e_type, true>::type  singly_type;
    typedef DoublyList<e_type, true>::type  doubly_type;
    typedef Array<e_type>                   array_type;

    template <typename T_List, typename T_Key, bool T_CacheHash, bool T_Unique>
    struct HT
    {
      typedef HashtablePolicy<u32, use_self<T_Key>, hash<T_Key>, 
        hash_to_range_mod, range_hash_default, equal_to<T_Key>, 
        prime_rehash_policy, T_List, T_CacheHash, T_Unique> type;

      //typedef HashtablePolicy<u32, use_self<u32>, hash<u32>, hash_to_range_mod,
      //  range_hash_default, equal_to<u32>, prime_rehash_policy, T_List,
      //  false, true> type;
    };

    typedef HT<SinglyList<singly_type, true>::type, value_type, false, true>::type
      singly_nohash_unique;
    typedef HT<DoublyList<doubly_type, true>::type, value_type, false, true>::type
      doubly_nohash_unique;
    typedef HT<SinglyList<doubly_type, true>::type, value_type, false, true>::type
      singlydoubly_nohash_unique;
    typedef HT<SinglyList<array_type, true>::type, value_type, false, true>::type
      singlyarray_nohash_unique;
    typedef HT<DoublyList<singly_type, true>::type, value_type, false, true>::type
      doublysingly_nohash_unique;
    typedef HT<DoublyList<array_type, true>::type, value_type, false, true>::type
      doublyarray_nohash_unique;
    typedef HT<Array<array_type>, value_type, false, true>::type
      array_nohash_unique;
    typedef HT<Array<singly_type>, value_type, false, true>::type
      arraysingly_nohash_unique;
    typedef HT<Array<doubly_type>, value_type, false, true>::type
      arraydouble_nohash_unique;
  };

  template <typename T_List>
  void TestCtors()
  {
    T_List h(3);
    CHECK(h.bucket_count() == 3);

    T_List h2(10);
    CHECK(h2.bucket_count() == 11);

    T_List h3(h2);
    CHECK(h3.bucket_count() == 11);
  }

  TEST_CASE_METHOD(HashtableFixture, "Core/Containers/Hashtable/Ctors", "")
  {
    TestCtors<Hashtable<doubly_nohash_unique> >();
    TestCtors<Hashtable<singly_nohash_unique> >();
    TestCtors<Hashtable<singlydoubly_nohash_unique> >();
    TestCtors<Hashtable<doublysingly_nohash_unique> >();
    TestCtors<Hashtable<doublyarray_nohash_unique> >();
    TestCtors<Hashtable<array_nohash_unique> >();
    TestCtors<Hashtable<arraysingly_nohash_unique> >();
    TestCtors<Hashtable<arraydouble_nohash_unique> >();
  }

};