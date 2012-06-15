#include "tlocTestCommon.h"

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl>

#define private public
#define protected public
#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/memory/tlocMemoryPool.inl>

#define TEST_MEMORY_POOL_INDEX(funcName)\
  funcName<core::MemoryPoolIndex<tl_uint, 100>, 100>();\
  funcName<core::MemoryPoolIndex<tl_uint>, 100>();\
  funcName<core::MemoryPoolIndex<tl_uint, 100,\
           core::p_memory_pool_index::allocation::On_Stack>, 100>();\
  funcName<core::MemoryPoolIndex<tl_uint, 0,\
           core::p_memory_pool_index::allocation::On_Heap>, 100>();\
\
  funcName<core::MemoryPoolIndex<indexed, 100,\
           core::p_memory_pool_index::allocation::On_Stack, \
           core::p_memory_pool_index::indexing::User>, 100>();\
  funcName<core::MemoryPoolIndex<indexed, 100,\
           core::p_memory_pool_index::allocation::On_Heap, \
           core::p_memory_pool_index::indexing::User>, 100>();\


namespace TestingMemoryPool
{
  USING_TLOC;

  struct indexed
  {
    bool operator == (const indexed& a_rhs)
    {
      return m_element == a_rhs.m_element;
    }

    tl_int m_element;
    tl_int m_index;
  };

  typedef core::p_memory_pool_index::allocation::On_Stack p_on_stack;
  typedef core::p_memory_pool_index::allocation::On_Heap  p_on_heap;
  typedef core::p_memory_pool_index::indexing::Wrapper    p_wrapper;
  typedef core::p_memory_pool_index::indexing::User       p_user;

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
  void SetIndex(T_Elem1& a, T_IndexType a_index, p_on_stack)
  {
    a.m_index = a_index;
  }

  template <typename T_Elem1, typename T_IndexType>
  void SetIndex(T_Elem1& a, T_IndexType a_index, p_on_heap)
  {
    a->m_index = a_index;
  }

  template <typename T_Elem1>
  tl_int GetIndex(T_Elem1& a, p_on_stack)
  {
    return (tl_int)a.m_index;
  }

  template <typename T_Elem1>
  tl_int GetIndex(T_Elem1& a, p_on_heap)
  {
    return (tl_int)a->m_index;
  }

  template <typename T_Elem1, typename T_Elem2>
  void SetElement(T_Elem1& a, const T_Elem2& b, p_on_stack, p_wrapper)
  {
    a.GetElement() = b;
  }

  template <typename T_Elem1, typename T_Elem2>
  void SetElement(T_Elem1& a, const T_Elem2& b, p_on_heap, p_wrapper)
  {
    a->GetElement() = b;
  }


  template <typename T_Elem1, typename T_Elem2>
  void SetElement(T_Elem1& a, const T_Elem2& b, p_on_stack, p_user)
  {
    a.m_element = b;
  }

  template <typename T_Elem1, typename T_Elem2>
  void SetElement(T_Elem1& a, const T_Elem2& b, p_on_heap, p_user)
  {
    a->m_element = b;
  }

  template <typename T_Elem1>
  typename T_Elem1::wrapper_value_type GetElement(T_Elem1& a, p_on_stack, p_wrapper)
  {
    return a.GetElement();
  }

  template <typename T_Elem1>
  typename Loki::TypeTraits<T_Elem1>::PointeeType::wrapper_value_type
    GetElement(T_Elem1& a, p_on_heap, p_wrapper)
  {
    return a->GetElement();
  }

  template <typename T_Elem1>
  typename T_Elem1 GetElement(T_Elem1& a, p_on_stack, p_user)
  {
    return a;
  }

  template <typename T_Elem1>
  typename Loki::TypeTraits<T_Elem1>::PointeeType
    GetElement(T_Elem1& a, p_on_heap, p_user)
  {
    return *a;
  }

  //------------------------------------------------------------------------
  // Tests

  template <typename T_PoolType, tl_uint T_PoolSize>
  void TestInitialize()
  {
    typedef T_PoolType    pool_type;

    pool_type pool;
    pool.Initialize(T_PoolSize);

    CHECK(pool.GetAvail() == T_PoolSize);
  }

  TEST_CASE("Core/MemoryPool/Initialize", "")
  {
    TEST_MEMORY_POOL_INDEX(TestInitialize);
  }

  template <typename T_PoolType, tl_uint T_PoolSize>
  void TestIsValid()
  {
    typedef typename T_PoolType::wrapper_type wrapper_type;
    T_PoolType pool;

    wrapper_type invalid;
    wrapper_type valid;
    SetIndex(valid, 0, T_PoolType::policy_allocation_type());

    wrapper_type& s_invalid = T_PoolType::npos;

    CHECK(pool.IsValid(invalid) == false);
    CHECK(pool.IsValid(valid) == false);
    CHECK(pool.IsValid(s_invalid) == false);

    pool.Initialize(T_PoolSize);

    CHECK(pool.IsValid(invalid) == false);
    CHECK(pool.IsValid(valid) == false); // we have 0 used elements
    CHECK(pool.IsValid(s_invalid) == false);

    pool.GetNext();

    CHECK(pool.IsValid(invalid) == false);
    CHECK(pool.IsValid(valid) == true);
    CHECK(pool.IsValid(s_invalid) == false);
  }

  TEST_CASE("Core/MemoryPool/IsValid", "")
  {
    //TEST_MEMORY_POOL_INDEX(TestIsValid);
  }

  template <typename T_PoolType, tl_uint T_PoolSize>
  void TestSizeQueries()
  {
    typedef T_PoolType    pool_type;

    pool_type pool;

    CHECK(pool.GetTotal() == 0);
    CHECK(pool.GetAvail() == 0);
    CHECK(pool.GetUsed() == 0);

    pool.Initialize(T_PoolSize);

    CHECK(pool.GetTotal() == T_PoolSize);
    CHECK(pool.GetAvail() == T_PoolSize);
    CHECK(pool.GetUsed() == 0);
  }

  TEST_CASE("Core/MemoryPool/SizeQueries", "")
  {
    TEST_MEMORY_POOL_INDEX(TestSizeQueries);
  }

  template <typename T_PoolType, tl_uint T_PoolSize>
  void TestGetAndRecycle()
  {
    typedef T_PoolType    pool_type;
    typedef pool_type::policy_allocation_type p_alloc_type;
    typedef pool_type::policy_indexing_type   p_index_type;

    pool_type pool;
    pool.Initialize(T_PoolSize);

    CHECK(pool.GetAvail() == T_PoolSize);

    for (tl_int i = 0; i < T_PoolSize; ++i)
    {
      pool.GetNext();
    }

    CHECK(pool.GetUsed() == T_PoolSize);
    CHECK(pool.GetAvail() == 0);

    for (tl_int i = 0; i < T_PoolSize; ++i)
    {
      pool.Recycle(0);
    }

    CHECK(pool.GetAvail() == T_PoolSize);

    for (tl_int i = 0; i < T_PoolSize; ++i)
    {
      SetElement(pool.GetNext(), i, p_alloc_type(), p_index_type() );
    }

    bool recycleTestPassed = true;
    for (tl_int i = 0; i < T_PoolSize; ++i)
    {
      const tl_int indexToRecycle = 0;
      const pool_type::value_type elementToCheck =
        GetElement(pool[0], pool_type::policy_allocation_type(),
                            pool_type::policy_indexing_type() );

      pool.Recycle(indexToRecycle);

      for (T_PoolType::iterator itr = pool.begin(), itrEnd = pool.end();
           itr != itrEnd; ++itr)
      {
        if (GetElement(*itr, pool_type::policy_allocation_type(),
          pool_type::policy_indexing_type()) == elementToCheck)
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

    T_PoolType::wrapper_type& elem = a_pool.GetNext();
    CHECK(a_pool.IsValid(elem) );

    CHECK(GetIndex(elem, T_PoolType::policy_allocation_type()) == (T_PoolType::index_type)prevSize);
    CHECK(a_pool.GetTotal() > prevSize);
  }

  template <typename T_PoolType>
  void TestGrowthHelper(T_PoolType& a_pool, static_pool_type)
  {
    typename T_PoolType::size_type prevSize = a_pool.GetTotal();

    CHECK(a_pool.IsValid(a_pool.GetNext()) == false);
    CHECK(a_pool.GetTotal() == prevSize);
  }

  template <typename T_PoolType, tl_uint T_PoolSize>
  void TestGrowth()
  {
    typedef T_PoolType    pool_type;

    pool_type pool;
    pool.Initialize(T_PoolSize);

    CHECK(pool.GetAvail() == T_PoolSize);

    // Exhaust all available elements
    for (tl_int i = 0; i < T_PoolSize; ++i)
    {
      pool.GetNext();
    }

    CHECK(pool.GetAvail() == 0);

    // Test growth depending on pool type
    TestGrowthHelper(pool, T_PoolType::container_dynamic_type());
  }

  TEST_CASE("Core/MemoryPool/GetNext_Growth", "Test GetNext growth")
  {
    TEST_MEMORY_POOL_INDEX(TestGrowth);
  }
};
