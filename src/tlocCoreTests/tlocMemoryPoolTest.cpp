#include "tlocTestCommon.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/memory/tlocMemoryPool.inl.h>

// testing explicit instantiation
#ifndef TLOC_COMPILER_VISUAL_CPP_2013
TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_USING_WRAPPER(tl_int, 100);
#endif

namespace TestingMemoryPool
{
  using namespace tloc;
  using namespace core::memory;

  struct indexed
  {
    typedef tl_int                                          value_type;

    indexed()
    { m_ctorCount++; }

    indexed(const indexed& a_other)
      : m_element(a_other.m_element)
      , m_index(a_other.m_index)
    { m_ctorCount++; }

    ~indexed()
    { m_dtorCount++; }

    bool operator == (const indexed& a_rhs) const
    {
      return m_element == a_rhs.m_element;
    }

    TLOC_DECL_AND_DEF_GETTER(tl_int, GetIndex, m_index);
    TLOC_DECL_AND_DEF_GETTER_DIRECT(tl_int, DoGetIndexRef, m_index);

    tl_int m_element;
    tl_int m_index;

    static tl_int m_dtorCount;
    static tl_int m_ctorCount;
  };

  tl_int indexed::m_ctorCount;
  tl_int indexed::m_dtorCount;

#define RESET_CTOR_AND_DTOR_COUNT()\
    indexed::m_dtorCount = 0;\
    indexed::m_ctorCount = 0

  typedef p_memory_pool_index::allocation::On_Stack p_on_stack;
  typedef p_memory_pool_index::allocation::On_Heap  p_on_heap;
  typedef p_memory_pool_index::indexing::Wrapper    p_wrapper;
  typedef p_memory_pool_index::indexing::User       p_user;

  //------------------------------------------------------------------------
  // Helper functions

  template <typename T_Elem1, typename T_Elem2>
  bool CheckElement(const T_Elem1& a, const T_Elem2& b, p_on_stack)
  {
    return a == b;
  }

  template <typename T_Elem1, typename T_Elem2>
  bool CheckElement(const T_Elem1& a, const T_Elem2& b, p_on_heap)
  {
    return *a == b;
  }

  template <typename T_Elem1, typename T_IndexType>
  void SetIndex(T_Elem1 a, T_IndexType a_index, p_on_stack)
  {
    a->m_index = a_index;
  }

  template <typename T_Elem1, typename T_IndexType>
  void SetIndex(T_Elem1 a, T_IndexType a_index, p_on_heap)
  {
    (*a)->m_index = a_index;
  }

  template <typename T_Elem1>
  tl_int
    GetIndex(T_Elem1 a, p_on_stack, p_wrapper)
  {
    return (*a)->GetIndex();
  }

  template <typename T_Elem1>
  tl_int
    GetIndex(T_Elem1 a, p_on_heap, p_wrapper)
  {
    return (tl_int)(*a)->GetIndex();
  }

  template <typename T_Elem1>
  tl_int
    GetIndex(T_Elem1 a, p_on_stack, p_user)
  {
    return (*a)->GetIndex();
  }

  template <typename T_Elem1>
  tl_int
    GetIndex(T_Elem1 a, p_on_heap, p_user)
  {
    return (tl_int) (*a)->GetIndex();
  }

  template <typename T_Elem1, typename T_Elem2>
  void
    SetValue(T_Elem1 a, const T_Elem2& b, p_on_stack, p_wrapper)
  {
    (*a)->SetValue(b);
  }

  template <typename T_Elem1, typename T_Elem2>
  void
    SetValue(T_Elem1 a, const T_Elem2& b, p_on_heap, p_wrapper)
  {
    (*a)->SetValue(b);
  }


  template <typename T_Elem1, typename T_Elem2>
  void
    SetValue(T_Elem1 a, const T_Elem2& b, p_on_stack, p_user)
  {
    (*a)->m_element = b;
  }

  template <typename T_Elem1, typename T_Elem2>
  void SetValue(T_Elem1 a, const T_Elem2& b, p_on_heap, p_user)
  {
    (*a)->m_element = b;
  }

  template <typename T_Elem1>
  typename T_Elem1::value_type::pointer
    GetValue(T_Elem1& a, p_on_stack, p_wrapper)
  {
    return a->GetValuePtr();
  }

  template <typename T_Elem1>
  typename T_Elem1::value_type::pointer
    GetValue(T_Elem1& a, p_on_heap, p_wrapper)
  {
    return a->GetValuePtr();
  }

  template <typename T_Elem1>
  typename T_Elem1::pointer
    GetValue(T_Elem1& a, p_on_stack, p_user)
  {
    return a.get();
  }

  template <typename T_Elem1>
  T_Elem1
    GetValue(T_Elem1& a, p_on_heap, p_user)
  {
    return a;
  }

  //------------------------------------------------------------------------
  // Tests

  struct AllPools
  {
    enum {k_poolSize = 100};

    typedef p_memory_pool_index::allocation::On_Heap    on_heap;
    typedef p_memory_pool_index::allocation::On_Stack   on_stack;
    typedef p_memory_pool_index::indexing::User         user;

    //typedef MemoryPoolIndexed<tl_uint, k_poolSize>        fixed_mem_pool;
    typedef MemoryPoolIndexed<tl_uint>                    dyn_mem_pool;

    //typedef MemoryPoolIndexed<indexed, k_poolSize, user>  user_fixed_mem_pool;
    typedef MemoryPoolIndexed<indexed, 0, user>           user_dyn_mem_pool;

    //fixed_mem_pool                          m_uintFixedStack;
    dyn_mem_pool                            m_uintStack;

    //user_fixed_mem_pool                     m_userFixedStack;
    user_dyn_mem_pool                       m_userHeap;
  };

  template <typename T_PoolType>
  void TestResize()
  {
    typedef T_PoolType    pool_type;

    {
      pool_type pool(AllPools::k_poolSize);
      CHECK( (pool.GetAvail() == AllPools::k_poolSize) );
    }

    {
      pool_type pool;
      CHECK(pool.GetAvail() == 1); // default starting size is 1
      pool.Resize(AllPools::k_poolSize);
      CHECK( (pool.GetAvail() == AllPools::k_poolSize) );
    }
  }

  TEST_CASE_METHOD(AllPools, "Core/MemoryPool/resize", "")
  {
    //TestResize<fixed_mem_pool>();
    TestResize<dyn_mem_pool>();

    RESET_CTOR_AND_DTOR_COUNT();
    //TestResize<user_fixed_mem_pool>();
    //CHECK(indexed::m_ctorCount > 0);
    //CHECK(indexed::m_dtorCount > 0);
    //CHECK(indexed::m_dtorCount == indexed::m_ctorCount);

    RESET_CTOR_AND_DTOR_COUNT();
    TestResize<user_dyn_mem_pool>();
    CHECK(indexed::m_ctorCount > 0);
    CHECK(indexed::m_dtorCount > 0);
    CHECK(indexed::m_dtorCount == indexed::m_ctorCount);
  }

  template <typename T_PoolType>
  void TestSizeQueries()
  {
    typedef T_PoolType    pool_type;

    pool_type pool;

    CHECK(pool.GetTotal() == 1); // default starting size is 1
    CHECK(pool.GetAvail() == 1); // default starting size is 1
    CHECK(pool.GetUsed() == 0);

    pool.Resize(0); // should NOT crash
    pool.Resize(AllPools::k_poolSize);

    CHECK( (pool.GetTotal() == AllPools::k_poolSize) );
    CHECK( (pool.GetAvail() == AllPools::k_poolSize) );
    CHECK(pool.GetUsed() == 0);
  }

  TEST_CASE_METHOD(AllPools, "Core/MemoryPool/SizeQueries", "")
  {
    //TestSizeQueries<fixed_mem_pool>();
    TestSizeQueries<dyn_mem_pool>();

    RESET_CTOR_AND_DTOR_COUNT();
    //TestSizeQueries<user_fixed_mem_pool>();
    //CHECK(indexed::m_ctorCount > 0);
    //CHECK(indexed::m_dtorCount > 0);
    //CHECK(indexed::m_dtorCount == indexed::m_ctorCount);

    RESET_CTOR_AND_DTOR_COUNT();
    TestSizeQueries<user_dyn_mem_pool>();
    CHECK(indexed::m_ctorCount > 0);
    CHECK(indexed::m_dtorCount > 0);
    CHECK(indexed::m_dtorCount == indexed::m_ctorCount);
  }

  template <typename T_PoolType>
  void TestFind()
  {
    typedef T_PoolType                                      pool_type;
    typedef typename pool_type::iterator                    iterator;
    typedef typename pool_type::policy_allocation_type      p_alloc_type;
    typedef typename pool_type::policy_indexing_type        p_index_type;

    pool_type pool(AllPools::k_poolSize);
    iterator itr = pool.GetNext();

    iterator itrFound = pool.Find(*itr);
    CHECK( (pool[GetIndex(itr, p_alloc_type(), p_index_type())] == *itrFound) );
  }

  TEST_CASE_METHOD(AllPools, "Core/MemoryPool/Find", "")
  {
    //TestFind<fixed_mem_pool>();
    TestFind<dyn_mem_pool>();

    RESET_CTOR_AND_DTOR_COUNT();
    //TestFind<user_fixed_mem_pool>();
    TestFind<user_dyn_mem_pool>();
    CHECK(indexed::m_ctorCount > 0);
    CHECK(indexed::m_dtorCount > 0);
    CHECK(indexed::m_dtorCount == indexed::m_ctorCount);
  }

  template <typename T_PoolType>
  void TestGetAndRecycle()
  {
    typedef T_PoolType    pool_type;
    typedef typename pool_type::policy_allocation_type p_alloc_type;
    typedef typename pool_type::policy_indexing_type   p_index_type;
    typedef typename pool_type::pointer                pointer;
    typedef typename pool_type::iterator               iterator;
    typedef typename pointer::value_type               value_type;

    pool_type pool(AllPools::k_poolSize);

    CHECK( (pool.GetAvail() == AllPools::k_poolSize) );

    for (tl_int i = 0; i < AllPools::k_poolSize; ++i)
    {
      pool.GetNext();
    }

    CHECK( (pool.GetUsed() == AllPools::k_poolSize) );
    CHECK(pool.GetAvail() == 0);

    for (tl_int i = 0; i < AllPools::k_poolSize; ++i)
    {
      pool.RecycleAtIndex(0);
    }

    CHECK( (pool.GetAvail() == AllPools::k_poolSize) );

    for (tl_int i = 0; i < AllPools::k_poolSize; ++i)
    {
      SetValue(pool.GetNext(), i, p_alloc_type(), p_index_type() );
    }

    bool recycleTestPassed = true;
    for (tl_int i = 0; i < AllPools::k_poolSize; ++i)
    {
      const tl_int indexToRecycle = 0;
      pointer elementToCheckPtr =
        GetValue(pool[0], typename pool_type::policy_allocation_type(),
                          typename pool_type::policy_indexing_type() );

      const value_type elementToCheck = *elementToCheckPtr;

      pool.RecycleAtIndex(indexToRecycle);

      for (typename T_PoolType::iterator itr = pool.begin(), itrEnd = pool.end();
           itr != itrEnd; ++itr)
      {
        const value_type tempElement =
          *GetValue(*itr, typename pool_type::policy_allocation_type(),
                          typename pool_type::policy_indexing_type());

        if (tempElement == elementToCheck)
        {
          recycleTestPassed = false;
          goto recycle_test_finished;
        }
      }
    }
recycle_test_finished:
    CHECK(recycleTestPassed);

    for (tl_int i = 0; i < AllPools::k_poolSize; ++i)
    {
      SetValue(pool.GetNext(), i, p_alloc_type(), p_index_type() );
    }

    iterator itr = pool.RecycleElement(pool.begin());
    CHECK(itr == pool.begin());
    CHECK(pool.GetAvail() == 1);
    
    itr = pool.RecycleElement(pool.begin());
    CHECK(itr == pool.begin());
    CHECK(pool.GetAvail() == 2);

    pool.RecycleAll();
    CHECK(pool.GetAvail() == pool.GetTotal());
  }

  TEST_CASE_METHOD(AllPools, "Core/MemoryPool/GetAndRecycle", "")
  {
    //TestGetAndRecycle<fixed_mem_pool>();
    TestGetAndRecycle<dyn_mem_pool>();

    RESET_CTOR_AND_DTOR_COUNT();
    //TestGetAndRecycle<user_fixed_mem_pool>();
    //CHECK(indexed::m_ctorCount > 0);
    //CHECK(indexed::m_dtorCount > 0);
    //CHECK(indexed::m_dtorCount == indexed::m_ctorCount);

    RESET_CTOR_AND_DTOR_COUNT();
    TestGetAndRecycle<user_dyn_mem_pool>();
    CHECK(indexed::m_ctorCount > 0);
    CHECK(indexed::m_dtorCount > 0);
    CHECK(indexed::m_dtorCount == indexed::m_ctorCount);
  }

  typedef std::true_type           dynamic_pool_type;
  typedef std::false_type          static_pool_type;

  template <typename T_PoolType>
  void TestGrowthHelper(T_PoolType& a_pool, dynamic_pool_type)
  {
    typedef T_PoolType                                      pool_type;
    typedef typename pool_type::policy_allocation_type      p_alloc_type;
    typedef typename pool_type::policy_indexing_type        p_index_type;

    typename T_PoolType::size_type prevSize = a_pool.GetTotal();

    T_PoolType p;
    for (tl_int i = 0; i < AllPools::k_poolSize; ++i)
    {
      p.GetNext();
    }

    p.GetNext();

    typename T_PoolType::iterator elem = a_pool.GetNext();
    CHECK(a_pool.IsValid( elem ) );

    CHECK(GetIndex(elem, p_alloc_type(), p_index_type()) ==
          (typename T_PoolType::index_type)prevSize);
    CHECK(a_pool.GetTotal() > prevSize);
  }

  template <typename T_PoolType>
  void TestGrowthHelper(T_PoolType& a_pool, static_pool_type)
  {
    typename T_PoolType::size_type prevSize = a_pool.GetTotal();

    CHECK(a_pool.IsValid( a_pool.GetNext() ) == false);
    CHECK(a_pool.GetTotal() == prevSize);
  }

  template <typename T_PoolType>
  void TestGrowth()
  {
    typedef T_PoolType    pool_type;

    pool_type pool(AllPools::k_poolSize);

    CHECK( (pool.GetAvail() == AllPools::k_poolSize) );

    // Exhaust all available elements
    for (tl_int i = 0; i < AllPools::k_poolSize; ++i)
    {
      pool.GetNext();
    }

    CHECK(pool.GetAvail() == 0);

    // Test growth depending on pool type
    TestGrowthHelper(pool, typename T_PoolType::container_dynamic_type());
  }

  TEST_CASE_METHOD(AllPools, "Core/MemoryPool/GetNext_Growth", "Test GetNext growth")
  {
    //TestGrowth<fixed_mem_pool>();
    TestGrowth<dyn_mem_pool>();

    RESET_CTOR_AND_DTOR_COUNT();
    //TestGrowth<user_fixed_mem_pool>();
    //CHECK(indexed::m_ctorCount > 0);
    //CHECK(indexed::m_dtorCount > 0);
    //CHECK(indexed::m_dtorCount == indexed::m_ctorCount);

    RESET_CTOR_AND_DTOR_COUNT();
    TestGrowth<user_dyn_mem_pool>();
    CHECK(indexed::m_ctorCount > 0);
    CHECK(indexed::m_dtorCount > 0);
    CHECK(indexed::m_dtorCount == indexed::m_ctorCount);
  }
};
