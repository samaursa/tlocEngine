#include "tlocTestCommon.h"

#include <tlocCore/tlocBase.h>
#include <tlocCore/memory/tlocMemory.h>
#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTypes.inl.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/utilities/tlocType.h>

#include <tlocCore/containers/tlocList.h>
#include <tlocCore/containers/tlocList.inl.h>

#include <tlocCore/string/tlocString.h>

#include <tlocCore/tlocFunctional.h>

#include <tlocCore/containers/tlocHashtable.h>
#include <tlocCore/containers/tlocHashtable.inl.h>

namespace TestingHashtable
{
  using namespace tloc;
  using namespace core;
  using namespace core::containers;

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

    template <typename T_HashT, typename T_Key, bool T_CacheHash, bool T_Unique, typename T_Hasher = hash<T_Key> >
    struct HT
    {
      typedef HashtablePolicy<T_Key, use_self<T_Key>, T_Hasher,
        hash_to_range_mod, range_hash_default, equal_to<T_Key>,
        prime_rehash_policy, T_HashT, T_CacheHash, T_Unique> type;
    };

    // Unique keys - Not Stored Hash
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

    // Non-unique keys - Not Stored Hash
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

    // Unique keys - Stored Hash
    typedef HT<SinglyList<singly_type, true>::type, value_type, true, true>::type
      singly_hash_unique;
    typedef HT<DoublyList<doubly_type, true>::type, value_type, true, true>::type
      doubly_hash_unique;
    typedef HT<SinglyList<doubly_type, true>::type, value_type, true, true>::type
      singlydoubly_hash_unique;
    typedef HT<SinglyList<array_type, true>::type, value_type, true, true>::type
      singlyarray_hash_unique;
    typedef HT<DoublyList<singly_type, true>::type, value_type, true, true>::type
      doublysingly_hash_unique;
    typedef HT<DoublyList<array_type, true>::type, value_type, true, true>::type
      doublyarray_hash_unique;
    typedef HT<Array<array_type>, value_type, true, true>::type
      array_hash_unique;
    typedef HT<Array<singly_type>, value_type, true, true>::type
      arraysingly_hash_unique;
    typedef HT<Array<doubly_type>, value_type, true, true>::type
      arraydouble_hash_unique;

    // Non-unique keys - Stored hash
    typedef HT<SinglyList<singly_type, true>::type, value_type, true, false>::type
      singly_hash_nounique;
    typedef HT<DoublyList<doubly_type, true>::type, value_type, true, false>::type
      doubly_hash_nounique;
    typedef HT<SinglyList<doubly_type, true>::type, value_type, true, false>::type
      singlydoubly_hash_nounique;
    typedef HT<SinglyList<array_type, true>::type, value_type, true, false>::type
      singlyarray_hash_nounique;
    typedef HT<DoublyList<singly_type, true>::type, value_type, true, false>::type
      doublysingly_hash_nounique;
    typedef HT<DoublyList<array_type, true>::type, value_type, true, false>::type
      doublyarray_hash_nounique;
    typedef HT<Array<array_type>, value_type, true, false>::type
      array_hash_nounique;
    typedef HT<Array<singly_type>, value_type, true, false>::type
      arraysingly_hash_nounique;
    typedef HT<Array<doubly_type>, value_type, true, false>::type
      arraydouble_hash_nounique;
  };

  template <template <typename T_HashT> class T_Method>
  struct TestMethod
  {
    static void AllVariations()
    {
      T_Method<Hashtable<HashtableFixture::doubly_nohash_unique> >();
      T_Method<Hashtable<HashtableFixture::singly_nohash_unique> >();
      T_Method<Hashtable<HashtableFixture::singlydoubly_nohash_unique> >();
      T_Method<Hashtable<HashtableFixture::doublysingly_nohash_unique> >();
      T_Method<Hashtable<HashtableFixture::doublyarray_nohash_unique> >();
      T_Method<Hashtable<HashtableFixture::array_nohash_unique> >();
      T_Method<Hashtable<HashtableFixture::arraysingly_nohash_unique> >();
      T_Method<Hashtable<HashtableFixture::arraydouble_nohash_unique> >();
    }
  };

#define TestMethodAllVariationsUniqueHashNotStored(T_Type) \
    T_Type<Hashtable<singly_nohash_unique> >(); \
    T_Type<Hashtable<doubly_nohash_unique> >(); \
    T_Type<Hashtable<singlydoubly_nohash_unique> >(); \
    T_Type<Hashtable<doublysingly_nohash_unique> >(); \
    T_Type<Hashtable<doublyarray_nohash_unique> >(); \
    T_Type<Hashtable<array_nohash_unique> >(); \
    T_Type<Hashtable<arraysingly_nohash_unique> >(); \
    T_Type<Hashtable<arraydouble_nohash_unique> >();

#define TestMethodAllVariationsNoUniqueHashNotStored(T_Type) \
    T_Type<Hashtable<singly_nohash_nounique> >(); \
    T_Type<Hashtable<doubly_nohash_nounique> >(); \
    T_Type<Hashtable<singlydoubly_nohash_nounique> >(); \
    T_Type<Hashtable<doublysingly_nohash_nounique> >(); \
    T_Type<Hashtable<doublyarray_nohash_nounique> >(); \
    T_Type<Hashtable<array_nohash_nounique> >(); \
    T_Type<Hashtable<arraysingly_nohash_nounique> >(); \
    T_Type<Hashtable<arraydouble_nohash_nounique> >();

#define TestMethodAllVariationsUniqueHashStored(T_Type) \
  T_Type<Hashtable<singly_hash_unique> >(); \
  T_Type<Hashtable<doubly_hash_unique> >(); \
  T_Type<Hashtable<singlydoubly_hash_unique> >(); \
  T_Type<Hashtable<doublysingly_hash_unique> >(); \
  T_Type<Hashtable<doublyarray_hash_unique> >(); \
  T_Type<Hashtable<array_hash_unique> >(); \
  T_Type<Hashtable<arraysingly_hash_unique> >(); \
  T_Type<Hashtable<arraydouble_hash_unique> >();

#define TestMethodAllVariationsNoUniqueHashStored(T_Type) \
  T_Type<Hashtable<singly_hash_nounique> >(); \
  T_Type<Hashtable<doubly_hash_nounique> >(); \
  T_Type<Hashtable<singlydoubly_hash_nounique> >(); \
  T_Type<Hashtable<doublysingly_hash_nounique> >(); \
  T_Type<Hashtable<doublyarray_hash_nounique> >(); \
  T_Type<Hashtable<array_hash_nounique> >(); \
  T_Type<Hashtable<arraysingly_hash_nounique> >(); \
  T_Type<Hashtable<arraydouble_hash_nounique> >();

#define USE_TYPEDEFS \
  typedef typename Loki::Select< Loki::IsSameType<type_true, \
    typename T_HashT::unique_keys>::value, \
    Pair<typename T_HashT::iterator, bool>, \
    typename T_HashT::iterator>::Result selected_result; \
  typedef typename Loki::Select< Loki::IsSameType<type_true, \
    typename T_HashT::unique_keys>::value, \
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

    TestMethodAllVariationsUniqueHashNotStored(TestCtors);
    TestMethodAllVariationsNoUniqueHashNotStored(TestCtors);
    TestMethodAllVariationsUniqueHashStored(TestCtors);
    TestMethodAllVariationsNoUniqueHashStored(TestCtors);
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
      typename T_HashT::iterator itr = h.begin();

      Pair<bool, typename T_HashT::size_type> result =
        itr.GetCurrBucketNumber();
      REQUIRE(result.first == true);
      CHECK(result.second == 5 % 3); // bucket #2
      CHECK( (*itr) == 5);

      selected_result itr2 = h.insert(6);
      itr = iterator_deref()(itr2);
      CHECK( (*itr) == 6);

      result = itr.GetCurrBucketNumber();
      REQUIRE(result.first == true);
      CHECK(result.second == 0); // 6 should be in bucket #0

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
      typename T_HashT::iterator itrEnd = h.end();

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

      TL_NESTED_FUNC_BEGIN(CheckBucket)
        void CheckBucket(typename T_HashT::iterator a_itr,
                         tl_size a_valueToCheck)
      {
        CHECK(a_itr.GetCurrBucketNumber().second == a_valueToCheck);
      }
      TL_NESTED_FUNC_END();

      // One last check to make sure they were all added to the right buckets
      itr = h.find(7);
      TL_NESTED_CALL(CheckBucket)(itr, 0);
      itr = h.find(8);
      TL_NESTED_CALL(CheckBucket)(itr, 1);
      itr = h.find(5);
      TL_NESTED_CALL(CheckBucket)(itr, 5);
      itr = h.find(6);
      TL_NESTED_CALL(CheckBucket)(itr, 6);
    }

    //------------------------------------------------------------------------
    // iterator						insert(const_iterator a_position,
    //                           const value_type& a_value);
    {
      T_HashT h;
      typename T_HashT::iterator dummyItr = h.begin();

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
      typename T_HashT::value_type v[] =
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

      T_HashT h;
      h.insert(v, v + 14);
      typename T_HashT::iterator itr;

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
        type_true>::value ? 1 : 10));
    }
  }

  TEST_CASE_METHOD(HashtableFixture, "Core/Containers/Hashtable/insert", "")
  {
    TestMethodAllVariationsUniqueHashNotStored(TestInsert);
    TestMethodAllVariationsNoUniqueHashNotStored(TestInsert);
    TestMethodAllVariationsUniqueHashStored(TestCtors);
    TestMethodAllVariationsNoUniqueHashStored(TestCtors);
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

      typename T_HashT::iterator itr;
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

      typename T_HashT::iterator itr;
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
          type_true>::value ? 1 : numOfInserts));
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

      Pair<typename T_HashT::iterator, typename T_HashT::iterator> p =
        h.equal_range(3);

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
    TestMethodAllVariationsUniqueHashNotStored(TestFind);
    TestMethodAllVariationsNoUniqueHashNotStored(TestFind);
    TestMethodAllVariationsUniqueHashStored(TestCtors);
    TestMethodAllVariationsNoUniqueHashStored(TestCtors);
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
    TestMethodAllVariationsUniqueHashNotStored(TestSize);
    TestMethodAllVariationsNoUniqueHashNotStored(TestSize);
    TestMethodAllVariationsUniqueHashStored(TestCtors);
    TestMethodAllVariationsNoUniqueHashStored(TestCtors);
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
      typename T_HashT::value_type v[] =
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

      T_HashT h;
      h.insert(v, v + 14);

      typename T_HashT::iterator itr = h.erase(h.begin(), h.end());
      CHECK(h.size() == 0);
      CHECK(itr == h.end());

      h.insert(v, v + 14);
      CHECK(h.size() == 14);
    }
  }

  TEST_CASE_METHOD(HashtableFixture, "Core/Containers/Hashtable/erase", "")
  {
    TestMethodAllVariationsUniqueHashNotStored(TestErase);
    TestMethodAllVariationsNoUniqueHashNotStored(TestErase);
    TestMethodAllVariationsUniqueHashStored(TestCtors);
    TestMethodAllVariationsNoUniqueHashStored(TestCtors);
  }

  template <typename T_HashT>
  void TestBuckets()
  {
    USE_TYPEDEFS;

    T_HashT h;
  }

  TEST_CASE_METHOD(HashtableFixture, "Core/Containers/Hashtable/buckets", "")
  {
  }

  TEST_CASE_METHOD(HashtableFixture, "Core/Containers/Hashtable/with void", "")
  {
    using core::containers::Hashtable;

    typedef HashtableElement<void*>             void_elem_type;
    typedef DoublyList<void_elem_type>::type    bucket_type;
    typedef DoublyList<bucket_type>::type       bucket_holder_type;

    typedef HashtableFixture::HT
      <
        bucket_holder_type, void*, false, false
      >::type doubly_nohash_nounique;

    typedef Hashtable<doubly_nohash_nounique> ht_type;
    typedef ht_type::iterator                 ht_itr_type;

    ht_type voidTable;

    void* int1 = new int(1);
    void* int2 = new int(2);
    void* int3 = new int(3);
    void* int4 = new int(4);

    voidTable.insert(int1);
    voidTable.insert(int2);

    CHECK(voidTable.find(int3) == voidTable.end());
    CHECK(voidTable.find(int4) == voidTable.end());
    CHECK(voidTable.find(int1) != voidTable.end());
    CHECK(voidTable.find(int2) != voidTable.end());

    {
      ht_itr_type itr = voidTable.find(int1);
      CHECK( *itr == int1);
    }

    {
      ht_itr_type itr = voidTable.find(int2);
      CHECK( *itr == int2);
    }
  }

  TEST_CASE_METHOD(HashtableFixture, "Core/Containers/Hashtable/with const char*", "")
  {
    using core::containers::Hashtable;

    typedef HashtableElement<const core_str::String>      void_elem_type;
    typedef DoublyList<void_elem_type>::type              bucket_type;
    typedef DoublyList<bucket_type>::type                 bucket_holder_type;

    typedef HashtableFixture::HT
      <
        bucket_holder_type, core_str::String, false, false
      >::type doubly_nohash_nounique;

    typedef Hashtable<doubly_nohash_nounique> ht_type;
    typedef ht_type::iterator                 ht_itr_type;

    ht_type stringTable;

    const core_str::String str1 = "This";
    const core_str::String str2 = "is";
    const core_str::String str3 = "absolutely";
    const core_str::String str4 = "great";

    stringTable.insert(str1);
    stringTable.insert(str2);

    CHECK(stringTable.find(str3) == stringTable.end());
    CHECK(stringTable.find(str4) == stringTable.end());
    CHECK(stringTable.find(str1) != stringTable.end());
    CHECK(stringTable.find(str2) != stringTable.end());

    CHECK(stringTable.size() == 2);

    {
      ht_itr_type itr = stringTable.find(str1);
      CHECK( *itr == str1);
    }

    {
      ht_itr_type itr = stringTable.find(str2);
      CHECK( *itr == str2);
    }

    CHECK(stringTable.erase(str1) == 1);
    CHECK(stringTable.size() == 1);
  }

};