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
  core::p_memory_pool_index::Allocate_On_Heap>, 100>();\
  funcName<core::MemoryPoolIndex<tl_uint, 0,\
  core::p_memory_pool_index::Allocate_On_Heap>, 100>()

namespace TestingMemoryPool
{
  USING_TLOC;

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
    valid.m_index = 0;

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
    TEST_MEMORY_POOL_INDEX(TestInitialize);
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

  template <typename T_PoolType, tl_uint T_PoolSize>
  void TestGetAndRecycle()
  {
    typedef T_PoolType    pool_type;

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
      pool.GetNext().GetElement() = i;
    }

    bool recycleTestPassed = true;
    for (tl_int i = 0; i < T_PoolSize; ++i)
    {
      const tl_int indexToRecycle = 0;
      const pool_type::value_type elementToCheck = pool[0].GetElement();

      pool.Recycle(indexToRecycle);

      for (T_PoolType::iterator itr = pool.begin(), itrEnd = pool.end();
           itr != itrEnd; ++itr)
      {
        if (itr->GetElement() == elementToCheck)
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
    TEST_MEMORY_POOL_INDEX(TestInitialize);
  }

  typedef type_true           dynamic_pool_type;
  typedef type_false          static_pool_type;

  template <typename T_PoolType>
  void TestGrowthHelper(T_PoolType& a_pool, dynamic_pool_type)
  {
    typename T_PoolType::size_type prevSize = a_pool.GetTotal();

    T_PoolType::wrapper_type& elem = a_pool.GetNext();
    CHECK(a_pool.IsValid(elem) );

    CHECK(elem.GetIndex() == (T_PoolType::index_type)prevSize);
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
    TEST_MEMORY_POOL_INDEX(TestInitialize);
  }
};
