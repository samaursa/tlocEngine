#include "tlocHashtable.h"
#include "tlocHashtable.inl"

#include "tlocList.h"
#include "tlocList.inl"

namespace tloc { namespace core {



  //////////////////////////////////////////////////////////////////////////
  // Globals

  namespace hash_detail
  {
    //------------------------------------------------------------------------
    // Empty bucket array
    void* g_emptyBucketArray[2] = { NULL, (void*)uintptr_t(~0) };

    //------------------------------------------------------------------------
    // Array of prime numbers as per the C++ standard (copied from EASTL)
    const u32 g_primeNumberArray[] =
    {
      2u, 3u, 5u, 7u, 11u, 13u, 17u, 19u, 23u, 29u, 31u,
      37u, 41u, 43u, 47u, 53u, 59u, 61u, 67u, 71u, 73u, 79u,
      83u, 89u, 97u, 103u, 109u, 113u, 127u, 137u, 139u, 149u,
      157u, 167u, 179u, 193u, 199u, 211u, 227u, 241u, 257u,
      277u, 293u, 313u, 337u, 359u, 383u, 409u, 439u, 467u,
      503u, 541u, 577u, 619u, 661u, 709u, 761u, 823u, 887u,
      953u, 1031u, 1109u, 1193u, 1289u, 1381u, 1493u, 1613u,
      1741u, 1879u, 2029u, 2179u, 2357u, 2549u, 2753u, 2971u,
      3209u, 3469u, 3739u, 4027u, 4349u, 4703u, 5087u, 5503u,
      5953u, 6427u, 6949u, 7517u, 8123u, 8783u, 9497u, 10273u,
      11113u, 12011u, 12983u, 14033u, 15173u, 16411u, 17749u,
      19183u, 20753u, 22447u, 24281u, 26267u, 28411u, 30727u,
      33223u, 35933u, 38873u, 42043u, 45481u, 49201u, 53201u,
      57557u, 62233u, 67307u, 72817u, 78779u, 85229u, 92203u,
      99733u, 107897u, 116731u, 126271u, 136607u, 147793u,
      159871u, 172933u, 187091u, 202409u, 218971u, 236897u,
      256279u, 277261u, 299951u, 324503u, 351061u, 379787u,
      410857u, 444487u, 480881u, 520241u, 562841u, 608903u,
      658753u, 712697u, 771049u, 834181u, 902483u, 976369u,
      1056323u, 1142821u, 1236397u, 1337629u, 1447153u, 1565659u,
      1693859u, 1832561u, 1982627u, 2144977u, 2320627u, 2510653u,
      2716249u, 2938679u, 3179303u, 3439651u, 3721303u, 4026031u,
      4355707u, 4712381u, 5098259u, 5515729u, 5967347u, 6456007u,
      6984629u, 7556579u, 8175383u, 8844859u, 9569143u, 10352717u,
      11200489u, 12117689u, 13109983u, 14183539u, 15345007u,
      16601593u, 17961079u, 19431899u, 21023161u, 22744717u,
      24607243u, 26622317u, 28802401u, 31160981u, 33712729u,
      36473443u, 39460231u, 42691603u, 46187573u, 49969847u,
      54061849u, 58488943u, 63278561u, 68460391u, 74066549u,
      80131819u, 86693767u, 93793069u, 101473717u, 109783337u,
      118773397u, 128499677u, 139022417u, 150406843u, 162723577u,
      176048909u, 190465427u, 206062531u, 222936881u, 241193053u,
      260944219u, 282312799u, 305431229u, 330442829u, 357502601u,
      386778277u, 418451333u, 452718089u, 489790921u, 529899637u,
      573292817u, 620239453u, 671030513u, 725980837u, 785430967u,
      849749479u, 919334987u, 994618837u, 1076067617u, 1164186217u,
      1259520799u, 1362662261u, 1474249943u, 1594975441u,
      1725587117u, 1866894511u, 2019773507u, 2185171673u,
      2364114217u, 2557710269u, 2767159799u, 2993761039u,
      3238918481u, 3504151727u, 3791104843u, 4101556399u,
      4294967291u,
      4294967291u // Sentinel so we don't have to test result of lower_bound
    };

    const u32  g_primeCount  = (sizeof(g_primeNumberArray) / 
                                sizeof(g_primeNumberArray[0]) - 1 );
  };

  //////////////////////////////////////////////////////////////////////////
  // Rehash policies

  //------------------------------------------------------------------------
  // Prime rehash policy

#define CEILING_POS(X) ((X-(s32)(X)) > 0 ? (s32)(X+1) : (s32)(X))
#define CEILING_NEG(X) ((X-(s32)(X)) < 0 ? (s32)(X-1) : (s32)(X))
#define CEILING(X) ( ((X) > 0) ? CEILING_POS(X) : CEILING_NEG(X) )

  prime_rehash_policy::prime_rehash_policy(f32 a_maxLoadFactor) 
    : m_maxLoadFactor(a_maxLoadFactor), m_growthFactor(2.0f), m_nextResize(0)
  {
  }

  f32 prime_rehash_policy::get_max_load_factor() const
  {
    return m_maxLoadFactor;
  }

  void prime_rehash_policy::set_max_load_factor(f32 a_maxLoadFactor)
  {
    m_maxLoadFactor = a_maxLoadFactor;
  }

  prime_rehash_policy::size_type prime_rehash_policy
    ::get_next_bucket_count(size_type a_bucketCountHint) const
  {
    const u32 prime = *lower_bound(hash_detail::g_primeNumberArray, 
      hash_detail::g_primeNumberArray + hash_detail::g_primeCount, 
      a_bucketCountHint);

    m_nextResize = (u32)( CEILING(prime * m_maxLoadFactor));
    return prime;
  }

  prime_rehash_policy::size_type prime_rehash_policy
    ::get_bucket_count(prime_rehash_policy::size_type a_numOfElements) const
  {
    TLOC_ASSERT_HASH_TABLE(m_maxLoadFactor > 0.0f, 
      "m_maxLoadFactor is incorrect! (divide by zero or negative)");

    const u32 minBucketCount = u32 (a_numOfElements / m_maxLoadFactor);
    return get_next_bucket_count(minBucketCount);
  }

  Pair<bool, prime_rehash_policy::size_type> prime_rehash_policy
    ::get_rehash_required(size_type a_numOfBuckets, size_type a_numOfElements, 
                          size_type a_numOfElementsToAdd) const
  {
    if (( a_numOfElements + a_numOfElementsToAdd) > m_nextResize)
    {
      if (a_numOfBuckets == 1) { a_numOfBuckets = 0; }

      TLOC_ASSERT_HASH_TABLE(m_maxLoadFactor > 0.0f, 
        "m_maxLoadFactor is incorrect! (divide by zero or negative)");

      f32 minBucketCount = (a_numOfElements + a_numOfElementsToAdd) / 
                            m_maxLoadFactor;

      if (minBucketCount > (f32)a_numOfBuckets)
      {
        minBucketCount = tlMax(minBucketCount, m_growthFactor * a_numOfBuckets);
        const u32 prime = *lower_bound(hash_detail::g_primeNumberArray, 
          hash_detail::g_primeNumberArray + hash_detail::g_primeCount, 
          minBucketCount);
        m_nextResize = (u32)CEILING(prime * m_maxLoadFactor);

        return Pair<bool, u32>(true, prime);
      }
      else
      {
        m_nextResize = (u32)CEILING(a_numOfBuckets * m_maxLoadFactor);
        return Pair<bool, u32>(false, (u32)0);
      }
    }

    return Pair<bool, u32>(false, (u32)0);
  }

#undef CEILING_POS
#undef CEILING_NEG
#undef CEILING

  struct dummyHashFunc 
  {
    size_t operator()(s32 a_value) { return (size_t)(a_value); }
  };

  struct dummyEqualTo
  {
    typedef s32 first_argument_type;
    typedef s32 second_argument_type;
    typedef bool result_type;

    bool operator()(const s32& a, const s32& b) const { return a == b; }
  };

  //typedef HashtablePolicy<s32, use_self<s32>, hash<s32>, hash_to_range_mod, range_hash_default, 
  //  equal_to<s32>, prime_rehash_policy, List< Array<HashtableElement<s32> > >, 
  //  false, true> hashtable_policies;

  //template Hashtable<hashtable_policies>;

};};
