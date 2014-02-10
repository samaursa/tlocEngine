#include "tlocTestCommon.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl.h>

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/memory/tlocMemoryPool.inl.h>

#define TEST_MEMORY_POOL_INDEX(funcName)\
  funcName<MemoryPoolIndexed<tl_uint, 100>, 100>();\
  funcName<MemoryPoolIndexed<tl_uint>, 100>();\
  funcName<MemoryPoolIndexed<tl_uint, 100,\
           p_memory_pool_index::allocation::On_Stack>, 100>();\
  funcName<MemoryPoolIndexed<tl_uint, 0,\
           p_memory_pool_index::allocation::On_Heap>, 100>();\
\
  funcName<MemoryPoolIndexed<indexed, 100,\
           p_memory_pool_index::allocation::On_Stack, \
           p_memory_pool_index::indexing::User>, 100>();\
  funcName<MemoryPoolIndexed<indexed, 100,\
           p_memory_pool_index::allocation::On_Heap, \
           p_memory_pool_index::indexing::User>, 100>();\

// testing explicit instantiation
TLOC_EXPLICITLY_INSTANTIATE_MEM_POOL_ON_STACK_AND_HEAP_USING_WRAPPER(tloc::tl_uint, 100);

namespace TestingMemoryPool
{
  using namespace tloc;
  using namespace core::memory;

  struct indexed
  {
    bool operator == (const indexed& a_rhs)
    {
      return m_element == a_rhs.m_element;
    }

    TLOC_DECL_AND_DEF_GETTER(tl_int, GetIndex, m_index);
    TLOC_DECL_AND_DEF_GETTER_DIRECT(tl_int, DoGetIndexRef, m_index);

    tl_int m_element;
    tl_int m_index;
  };

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
  tl_int GetIndex(T_Elem1 a, p_on_stack)
  {
    return (tl_int)a->GetIndex();
  }

  template <typename T_Elem1>
  tl_int GetIndex(T_Elem1 a, p_on_heap)
  {
    return (tl_int) (*a)->GetIndex();
  }

  template <typename T_Elem1, typename T_Elem2>
  void SetValue(T_Elem1 a, const T_Elem2& b, p_on_stack, p_wrapper)
  {
    a->SetValue(b);
  }

  template <typename T_Elem1, typename T_Elem2>
  void SetValue(T_Elem1 a, const T_Elem2& b, p_on_heap, p_wrapper)
  {
    (*a)->SetValue(b);
  }


  template <typename T_Elem1, typename T_Elem2>
  void SetValue(T_Elem1 a, const T_Elem2& b, p_on_stack, p_user)
  {
    a->m_element = b;
  }

  template <typename T_Elem1, typename T_Elem2>
  void SetValue(T_Elem1 a, const T_Elem2& b, p_on_heap, p_user)
  {
    (*a)->m_element = b;
  }

  template <typename T_Elem1>
  typename T_Elem1::wrapper_value_type GetValue(T_Elem1& a, p_on_stack, p_wrapper)
  {
    return a.GetValue();
  }

  template <typename T_Elem1>
  typename Loki::TypeTraits<T_Elem1>::PointeeType::wrapper_value_type
    GetValue(T_Elem1& a, p_on_heap, p_wrapper)
  {
    return a->GetValue();
  }

  template <typename T_Elem1>
  T_Elem1 GetValue(T_Elem1& a, p_on_stack, p_user)
  {
    return a;
  }

  template <typename T_Elem1>
  typename Loki::TypeTraits<T_Elem1>::PointeeType
    GetValue(T_Elem1& a, p_on_heap, p_user)
  {
    return *a;
  }

  //------------------------------------------------------------------------
  // Tests

  template <typename T_PoolType, tl_uint T_PoolSize>
  void TestResize()
  {
    typedef T_PoolType    pool_type;

    {
      pool_type pool(T_PoolSize);
      CHECK(pool.GetAvail() == T_PoolSize);
    }

    {
      pool_type pool;
      CHECK(pool.GetAvail() == 1); // default starting size is 1
      pool.Resize(T_PoolSize);
      CHECK(pool.GetAvail() == T_PoolSize);
    }
  }

  TEST_CASE("Core/MemoryPool/resize", "")
  {
    TEST_MEMORY_POOL_INDEX(TestResize);
  }

  template <typename T_PoolType, tl_uint T_PoolSize>
  void TestSizeQueries()
  {
    typedef T_PoolType    pool_type;

    pool_type pool;

    CHECK(pool.GetTotal() == 1); // default starting size is 1
    CHECK(pool.GetAvail() == 1); // default starting size is 1
    CHECK(pool.GetUsed() == 0);

    pool.Resize(0); // should NOT crash
    pool.Resize(T_PoolSize);

    CHECK(pool.GetTotal() == T_PoolSize);
    CHECK(pool.GetAvail() == T_PoolSize);
    CHECK(pool.GetUsed() == 0);
  }

  TEST_CASE("Core/MemoryPool/SizeQueries", "")
  {
    TEST_MEMORY_POOL_INDEX(TestSizeQueries);
  }

  template <typename T_PoolType, tl_uint T_PoolSize>
  void TestFind()
  {
    typedef T_PoolType                                      pool_type;
    typedef typename pool_type::iterator                    iterator;
    typedef typename pool_type::policy_allocation_type      pol_alloc_type;

    pool_type pool(T_PoolSize);
    iterator itr = pool.GetNext();

    iterator itrFound = pool.Find(*itr);
    CHECK(pool[GetIndex(itr, pol_alloc_type())] == *itrFound);
  }

  TEST_CASE("Core/MemoryPool/Find", "")
  {
    TEST_MEMORY_POOL_INDEX(TestFind);
  }

  template <typename T_PoolType, tl_uint T_PoolSize>
  void TestGetAndRecycle()
  {
    typedef T_PoolType    pool_type;
    typedef typename pool_type::policy_allocation_type p_alloc_type;
    typedef typename pool_type::policy_indexing_type   p_index_type;

    pool_type pool(T_PoolSize);

    CHECK(pool.GetAvail() == T_PoolSize);

    for (tl_int i = 0; i < T_PoolSize; ++i)
    {
      pool.GetNext();
    }

    CHECK(pool.GetUsed() == T_PoolSize);
    CHECK(pool.GetAvail() == 0);

    for (tl_int i = 0; i < T_PoolSize; ++i)
    {
      pool.RecycleAtIndex(0);
    }

    CHECK(pool.GetAvail() == T_PoolSize);

    for (tl_int i = 0; i < T_PoolSize; ++i)
    {
      SetValue(pool.GetNext(), i, p_alloc_type(), p_index_type() );
    }

    bool recycleTestPassed = true;
    for (tl_int i = 0; i < T_PoolSize; ++i)
    {
      const tl_int indexToRecycle = 0;
      const typename pool_type::value_type elementToCheck =
        GetValue(pool[0], typename pool_type::policy_allocation_type(),
                            typename pool_type::policy_indexing_type() );

      pool.RecycleAtIndex(indexToRecycle);

      for (typename T_PoolType::iterator itr = pool.begin(), itrEnd = pool.end();
           itr != itrEnd; ++itr)
      {
        if (GetValue(*itr, typename pool_type::policy_allocation_type(),
          typename pool_type::policy_indexing_type()) == elementToCheck)
        {
          recycleTestPassed = false;
          goto recycle_test_finished;
        }
      }
    }
recycle_test_finished:
    CHECK(recycleTestPassed);
  }

  TEST_CASE("Core/MemoryPool/GetAndRecycle", "")
  {
    TEST_MEMORY_POOL_INDEX(TestGetAndRecycle);
  }

  typedef type_true           dynamic_pool_type;
  typedef type_false          static_pool_type;

  template <typename T_PoolType>
  void TestGrowthHelper(T_PoolType& a_pool, dynamic_pool_type)
  {
    typename T_PoolType::size_type prevSize = a_pool.GetTotal();

    typename T_PoolType::iterator elem = a_pool.GetNext();
    CHECK(a_pool.IsValid( elem ) );

    CHECK(GetIndex(elem, typename T_PoolType::policy_allocation_type()) ==
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

  template <typename T_PoolType, tl_uint T_PoolSize>
  void TestGrowth()
  {
    typedef T_PoolType    pool_type;

    pool_type pool(T_PoolSize);

    CHECK(pool.GetAvail() == T_PoolSize);

    // Exhaust all available elements
    for (tl_int i = 0; i < T_PoolSize; ++i)
    {
      pool.GetNext();
    }

    CHECK(pool.GetAvail() == 0);

    // Test growth depending on pool type
    TestGrowthHelper(pool, typename T_PoolType::container_dynamic_type());
  }

  TEST_CASE("Core/MemoryPool/GetNext_Growth", "Test GetNext growth")
  {
    TEST_MEMORY_POOL_INDEX(TestGrowth);
  }
};
