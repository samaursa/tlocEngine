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
    typedef u32 value_type;

    typedef HashtableElement<value_type>    e_type;
    typedef SinglyList<e_type, true>::type  singly_type;
    typedef DoublyList<e_type, true>::type  doubly_type;
    typedef Array<e_type>                   array_type;

    template <typename T_List, typename T_Key, bool T_CacheHash, bool T_Unique>
    struct HT
    {
      typedef HashtablePolicy<T_Key, use_self<T_Key>, hash<T_Key>, 
        hash_to_range_mod, range_hash_default, equal_to<T_Key>, 
        prime_rehash_policy, T_List, T_CacheHash, T_Unique> type;
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
  
  template <template <typename T_List> class T_Method>
  struct TestMethod
  {
    static void AllVariations()
    {
      T_Method<HashtableFixture::Hashtable<doubly_nohash_unique> >();
      T_Method<HashtableFixture::Hashtable<singly_nohash_unique> >();
      T_Method<HashtableFixture::Hashtable<singlydoubly_nohash_unique> >();
      T_Method<HashtableFixture::Hashtable<doublysingly_nohash_unique> >();
      T_Method<HashtableFixture::Hashtable<doublyarray_nohash_unique> >();
      T_Method<HashtableFixture::Hashtable<array_nohash_unique> >();
      T_Method<HashtableFixture::Hashtable<arraysingly_nohash_unique> >();
      T_Method<HashtableFixture::Hashtable<arraydouble_nohash_unique> >();
    }
  };

#define TestMethodAllVariations(T_Type) \
    T_Type<Hashtable<singly_nohash_unique> >(); \
    T_Type<Hashtable<doubly_nohash_unique> >(); \
    T_Type<Hashtable<singlydoubly_nohash_unique> >(); \
    T_Type<Hashtable<doublysingly_nohash_unique> >(); \
    T_Type<Hashtable<doublyarray_nohash_unique> >(); \
    T_Type<Hashtable<array_nohash_unique> >(); \
    T_Type<Hashtable<arraysingly_nohash_unique> >(); \
    T_Type<Hashtable<arraydouble_nohash_unique> >();

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
    // Unfrotunately, uncommenting the following crashes the VS 2008 compiler.
    // Seems to be a bug. We will have to settle for #define 
    //TestMethod<TestCtors>::AllVariations();

    TestMethodAllVariations(TestCtors);
  }

  template <typename T_List>
  void TestInsert()
  {
    T_List h(3);

    h.insert(5);

    // Should be added to bucket # 2
    T_List::iterator itr = h.begin();

    CHECK( (*itr) == 5);
  }

  TEST_CASE_METHOD(HashtableFixture, "Core/Containers/Hashtable/insert", "")
  {
    TestMethodAllVariations(TestInsert);
  }

};