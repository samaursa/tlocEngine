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

namespace TestingHashtable 
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

    template <typename T_HashT, typename T_Key, bool T_CacheHash, bool T_Unique>
    struct HT
    {
      typedef HashtablePolicy<T_Key, use_self<T_Key>, hash<T_Key>, 
        hash_to_range_mod, range_hash_default, equal_to<T_Key>, 
        prime_rehash_policy, T_HashT, T_CacheHash, T_Unique> type;
    };

    // Unique keys
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

    // Non-unique keys
    typedef HT<SinglyList<singly_type, true>::type, value_type, false, false>::type
      singly_nohash_nounique;
    typedef HT<DoublyList<doubly_type, true>::type, value_type, false, false>::type
      doubly_nohash_nounique;
    typedef HT<SinglyList<doubly_type, true>::type, value_type, false, false>::type
      singlydoubly_nohash_nounique;
    typedef HT<SinglyList<array_type, true>::type, value_type, false, false>::type
      singlyarray_nohash_nounique;
    typedef HT<DoublyList<singly_type, true>::type, value_type, false, false>::type
      doublysingly_nohash_nounique;
    typedef HT<DoublyList<array_type, true>::type, value_type, false, false>::type
      doublyarray_nohash_nounique;
    typedef HT<Array<array_type>, value_type, false, false>::type
      array_nohash_nounique;
    typedef HT<Array<singly_type>, value_type, false, false>::type
      arraysingly_nohash_nounique;
    typedef HT<Array<doubly_type>, value_type, false, false>::type
      arraydouble_nohash_nounique;
  };
  
  template <template <typename T_HashT> class T_Method>
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

#define TestMethodAllVariationsUnique(T_Type) \
    T_Type<Hashtable<singly_nohash_unique> >(); \
    T_Type<Hashtable<doubly_nohash_unique> >(); \
    T_Type<Hashtable<singlydoubly_nohash_unique> >(); \
    T_Type<Hashtable<doublysingly_nohash_unique> >(); \
    T_Type<Hashtable<doublyarray_nohash_unique> >(); \
    T_Type<Hashtable<array_nohash_unique> >(); \
    T_Type<Hashtable<arraysingly_nohash_unique> >(); \
    T_Type<Hashtable<arraydouble_nohash_unique> >();

#define TestMethodAllVariationsNoUnique(T_Type) \
    T_Type<Hashtable<singly_nohash_nounique> >(); \
    T_Type<Hashtable<doubly_nohash_nounique> >(); \
    T_Type<Hashtable<singlydoubly_nohash_nounique> >(); \
    T_Type<Hashtable<doublysingly_nohash_nounique> >(); \
    T_Type<Hashtable<doublyarray_nohash_nounique> >(); \
    T_Type<Hashtable<array_nohash_nounique> >(); \
    T_Type<Hashtable<arraysingly_nohash_nounique> >(); \
    T_Type<Hashtable<arraydouble_nohash_nounique> >();

#define USE_TYPEDEFS \
  typedef Loki::Select< Loki::IsSameType<type_true, T_HashT::unique_keys>::value, \
  Pair<T_HashT::iterator, bool>, T_HashT::iterator>::Result selected_result; \
  typedef Loki::Select< Loki::IsSameType<type_true, T_HashT::unique_keys>::value, \
    use_first<selected_result>, use_self<selected_result> >::Result iterator_deref \


  template <typename T_HashT>
  void TestCtors()
  {
    T_HashT h(3);
    CHECK(h.bucket_count() == 3);

    T_HashT h2(10);
    CHECK(h2.bucket_count() == 11);

    T_HashT h3(h2);
    CHECK(h3.bucket_count() == 11);
  }

  TEST_CASE_METHOD(HashtableFixture, "Core/Containers/Hashtable/Ctors", "")
  {
    // Unfortunately, uncommenting the following crashes the VS 2008 compiler.
    // Seems to be a bug. We will have to settle for #define 
    //TestMethod<TestCtors>::AllVariations();

    //TestMethodAllVariationsUnique(TestCtors);
    //TestMethodAllVariationsNoUnique(TestCtors);
  }

  template <typename T_HashT>
  void TestInsert()
  {
    USE_TYPEDEFS;

    //------------------------------------------------------------------------
    // insert_return_type  insert(const value_type& a_value);

    {
      T_HashT h(3);

      h.insert(5);

      // Should be added to bucket # 2
      T_HashT::iterator itr = h.begin();

      Pair<bool, T_HashT::size_type> result = itr.GetCurrBucketNumber();
      REQUIRE(result.first == true);
      CHECK(result.second == 5 % 3); // bucket #2
      CHECK( (*itr) == 5);

      selected_result itr2 = h.insert(6);
      itr = iterator_deref()(itr2);
      CHECK( (*itr) == 6);

      result = itr.GetCurrBucketNumber();
      REQUIRE(result.first == true);
      CHECK(result.second == 0) // 6 should be in bucket #0

        itr2 = h.insert(7);
      itr = iterator_deref()(itr2);
      CHECK( (*itr) == 7);

      itr2 = h.insert(8);
      itr = iterator_deref()(itr2);
      CHECK( (*itr) == 8);

      CHECK(h.bucket_count() == 7);
      result = itr.GetCurrBucketNumber();
      REQUIRE(result.first == true);
      CHECK(result.second == 8 % 7);

      itr = h.find(5);
      result = itr.GetCurrBucketNumber();
      REQUIRE(result.first == true);
      CHECK(result.second == 5 % 7); // If passed, rehash was successful

      itr = h.begin();
      T_HashT::iterator itrEnd = h.end();

      REQUIRE(h.size() == 4);

      REQUIRE(itr != itrEnd);
      CHECK( (*(itr++)) == 7);
      REQUIRE(itr != itrEnd);
      CHECK( (*(itr++)) == 8);
      REQUIRE(itr != itrEnd);
      CHECK( (*(itr++)) == 5);
      REQUIRE(itr != itrEnd);
      CHECK( (*(itr++)) == 6);

      CHECK(h.size() == 4);

      CHECK( (itr == itrEnd) == true);

      // One last check to make sure they were all added to the right buckets
      itr = h.find(7);
      CHECK(itr.GetCurrBucketNumber().second == 0);
      itr = h.find(8);
      CHECK(itr.GetCurrBucketNumber().second == 1);
      itr = h.find(5);
      CHECK(itr.GetCurrBucketNumber().second == 5);
      itr = h.find(6);
      CHECK(itr.GetCurrBucketNumber().second == 6);
    }

    //------------------------------------------------------------------------
    // iterator						insert(const_iterator a_position, 
    //                           const value_type& a_value);
    {
      T_HashT h;
      T_HashT::iterator dummyItr = h.begin();

      dummyItr = h.insert(dummyItr, 9);
      CHECK( (*dummyItr) == 9);
      dummyItr = h.insert(dummyItr, 10);
      CHECK( (*dummyItr) == 10);

      CHECK(h.size() == 2);
    }

    //------------------------------------------------------------------------
    // template <typename T_InputItr>
    // void                insert(T_InputItr a_first, T_InputItr a_last);
    {
      T_HashT::value_type v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

      T_HashT h;
      h.insert(v, v + 14);
      T_HashT::iterator itr;

      for (u32 i = 1; i < 15; ++i)
      {
        itr = h.find(i);
        CHECK(itr != h.end());
      }
    }

    //------------------------------------------------------------------------
    // Test multiple inserts
    {
      T_HashT h;
      
      for (u32 i = 0; i < 10; ++i)
      {
        h.insert(5);
      }

      CHECK(h.count(5) == (Loki::IsSameType<typename T_HashT::unique_keys, 
        type_true>::value ? 1 : 10))
    }
  }

  TEST_CASE_METHOD(HashtableFixture, "Core/Containers/Hashtable/insert", "")
  {
    TestMethodAllVariationsUnique(TestInsert);
    TestMethodAllVariationsNoUnique(TestInsert);
  }

  template <typename T_HashT>
  void TestFind()
  {
    USE_TYPEDEFS;

    //------------------------------------------------------------------------
    // TL_FI iterator        find(const key_type& a_key);
    {
      T_HashT h;

      for (u32 i = 0; i < 16; i = i + 3)
      {
        h.insert(i);
      }

      T_HashT::iterator itr;
      for (u32 i = 0; i < 16; i = i + 3)
      {
        itr = h.find(i);
        CHECK(itr != h.end());
      }
    }

    //------------------------------------------------------------------------
    // TL_FI iterator        find_by_hash(u32 a_hashCode);
    {
      T_HashT h;
      for (u32 i = 0; i < 16; i = i + 3)
      {
        h.insert(i);
      }

      T_HashT::iterator itr;
      for (u32 i = 0; i < 16; i = i + 3)
      {
        itr = h.find_by_hash(i);
        CHECK(itr != h.end());
      }
    }

    //------------------------------------------------------------------------
    // TL_FI size_type       count(const key_type& a_key) const;
    {
      T_HashT h;
      const u32 numOfInserts = 3;
      for (u32 i = 0; i < 10; ++i)
      {
        for (u32 j = 0; j < numOfInserts; ++j)
        {
          h.insert(i);
        }
      }

      for (u32 i = 0; i < 10; ++i)
      {
        CHECK(h.count(i) == (Loki::IsSameType<typename T_HashT::unique_keys, 
          type_true>::value ? 1 : numOfInserts))
      }
    }

    //------------------------------------------------------------------------
    // TL_FI Pair<iterator, iterator>   equal_range(const key_type& a_key);
    {
      T_HashT h;
      for (u32 i = 0; i < 10; ++i)
      {
        h.insert(i);
        h.insert(i);
        h.insert(i);
      }

      Pair<T_HashT::iterator, T_HashT::iterator> p = h.equal_range(3);

      u32 count = 0;
      for (; p.first != p.second; ++(p.first))
      {
        ++count;
      }

      CHECK(count == (Loki::IsSameType<typename T_HashT::unique_keys, 
          type_true>::value ? 1 : 3));
    }
  }

  TEST_CASE_METHOD(HashtableFixture, "Core/Containers/Hashtable/find", "")
  {
    TestMethodAllVariationsUnique(TestFind);
    TestMethodAllVariationsNoUnique(TestFind);
  }

  template <typename T_HashT>
  void TestSize()
  {
    USE_TYPEDEFS;

    T_HashT h;

    for (u32 i = 0; i < 100; ++i)
    {
      h.insert(i);
    }

    CHECK(h.size() == 100);
  }

  TEST_CASE_METHOD(HashtableFixture, "Core/Containers/Hashtable/size", "")
  {
    TestMethodAllVariationsUnique(TestSize);
    TestMethodAllVariationsNoUnique(TestSize);
  }

  template <typename T_HashT>
  void TestErase()
  {
    USE_TYPEDEFS;

    //------------------------------------------------------------------------
    // size_type           erase(const key_type& a_key);
    {
      T_HashT h;
      for (u32 i = 0; i < 100; ++i)
      {
        h.insert(i);
      }

      CHECK(h.size() == 100);

      for (u32 i = 0; i < 100; ++i)
      {
        h.erase(i);
      }

      CHECK(h.size() == 0);
    }

    //------------------------------------------------------------------------
    //iterator            erase(iterator a_first, iterator a_last);
    {
      T_HashT::value_type v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

      T_HashT h;
      h.insert(v, v + 14);

      T_HashT::iterator itr = h.erase(h.begin(), h.end());
      CHECK(h.size() == 0);
      CHECK(itr == h.end());

      h.insert(v, v + 14);
      CHECK(h.size() == 14);
    }
  }

  TEST_CASE_METHOD(HashtableFixture, "Core/Containers/Hashtable/erase", "")
  {
    TestMethodAllVariationsUnique(TestErase);
    TestMethodAllVariationsNoUnique(TestErase);
  }
};