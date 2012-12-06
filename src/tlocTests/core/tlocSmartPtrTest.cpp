#include "tlocTestCommon.h"

#include <tlocCore/smart_ptr/tlocSmartPtr.h>
#include <tlocCore/smart_ptr/tlocSmartPtr.inl>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl>

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/memory/tlocMemoryPool.inl>

namespace TestingSmartPtr
{
  using namespace tloc;
  using namespace core;

  struct Shared
  {
    Shared(tl_int a_value) : m_value(a_value)
    { ++m_numCtors; }

    ~Shared()
    { ++m_numDtors; }

    tl_int m_value;

    static tl_int m_numCtors;
    static tl_int m_numDtors;
  };

  tl_int Shared::m_numCtors;
  tl_int Shared::m_numDtors;

  void PassSharedPtr(const smart_ptr::SharedPtr<Shared>& a_other)
  {
    tl_int currCount = a_other.GetRefCount();
    smart_ptr::SharedPtr<Shared> localPtr = a_other;
    CHECK(localPtr.GetRefCount() == currCount + 1);
  }

  TEST_CASE("core/smart_ptr/shared_ptr", "")
  {
    {
      smart_ptr::SharedPtr<Shared> sp( new Shared(5) );
      CHECK(Shared::m_numCtors == 1);
      CHECK(sp.GetRefCount() == 1);
      smart_ptr::SharedPtr<Shared> sp2 = sp;
      CHECK(Shared::m_numCtors == 1);
      CHECK(sp.GetRefCount() == 2);

      CHECK(sp->m_value == 5);
      CHECK(sp2->m_value == 5);

      CHECK( (*sp).m_value == 5);
      CHECK( (*sp2).m_value == 5);

      CHECK(Shared::m_numDtors == 0);
      PassSharedPtr(sp);
      CHECK(Shared::m_numDtors == 0);
    }
    CHECK(Shared::m_numDtors == 1);

    {
      smart_ptr::SharedPtr<Shared> sp;
      smart_ptr::SharedPtr<Shared> sp2 = sp; // should not crash
      CHECK(sp.GetRefCount() == 0);
      CHECK(sp2.GetRefCount() == 0);

    } // Should not crash when being destroyed

    {
      Shared::m_numCtors = 0;
      Shared::m_numDtors = 0;

      smart_ptr::SharedPtr<Shared> sp(new Shared(10));
      smart_ptr::SharedPtr<Shared> sp2 = sp;
      CHECK(sp.GetRefCount() == 2);

      smart_ptr::SharedPtr<Shared> sp3(new Shared(50));
      sp2 = sp3;
      CHECK(sp.GetRefCount() == 1);
      CHECK(sp3.GetRefCount() == 2);

      CHECK(Shared::m_numDtors == 0);
      sp = sp3;
      CHECK(Shared::m_numDtors == 1);
      CHECK(sp3.GetRefCount() == 3);
    }
    CHECK(Shared::m_numDtors == 2);
  }

  TEST_CASE("core/smart_ptr/shared_ptr/with_arrays", "")
  {
    Shared::m_numCtors = 0;
    Shared::m_numDtors = 0;

    typedef smart_ptr::SharedPtr<Shared>      shared_ptr_type;
    typedef tl_array<shared_ptr_type>::type   shared_array_type;

    const tl_int count = 100;

    {
      shared_array_type sa;
      for (int i = 0; i < count; ++i)
      { sa.push_back( new Shared(i) ); }

      CHECK(Shared::m_numCtors == count);

      bool testsPassed = true;
      tl_int counter = 0;
      for (shared_array_type::iterator itr = sa.begin(), itrEnd = sa.end();
           itr != itrEnd; ++itr)
      {
        shared_ptr_type localPtr = *itr;
        if ( (*localPtr).m_value != counter)
        { testsPassed = false; break; }

        ++counter;
      }
      CHECK(testsPassed);
      CHECK(Shared::m_numCtors == count);
      CHECK(Shared::m_numDtors == 0);
    }

    CHECK(Shared::m_numCtors == count);
    CHECK(Shared::m_numDtors == count);
  }

  struct MyComponent
  {
    MyComponent()
    {
      m_ctorCount++;
    }

    MyComponent(tl_int x, tl_int y, tl_int z)
      : x(x), y(y), z(z)
    {
      m_ctorCount++;
    }

    ~MyComponent()
    {
      m_dtorCount++;
    }

    tl_int x, y, z;

    static tl_int m_ctorCount;
    static tl_int m_dtorCount;
  };

  tl_int MyComponent::m_ctorCount;
  tl_int MyComponent::m_dtorCount;

  TEST_CASE("core/smart_ptr/shared_ptr/with_memory_pools", "")
  {
    const tl_int poolSize = 100;
    {
      typedef smart_ptr::SharedPtr<MyComponent>             my_comp_ptr;
      typedef memory::MemoryPoolIndexed<my_comp_ptr>        my_mem_pool;
      typedef my_mem_pool::iterator                         pool_type;

      my_mem_pool memPool(poolSize);
      memPool.GetNext()->GetElement() = my_comp_ptr(new MyComponent(0, 1, 2));
      memPool.GetNext()->GetElement() = my_comp_ptr(new MyComponent(1, 2, 3));

      for (tl_int i = 2; i < poolSize; ++i)
      {
        memPool.GetNext()->GetElement() =
          my_comp_ptr(new MyComponent(i, i + 1, i + 2));
      }

      CHECK(MyComponent::m_ctorCount == poolSize);

      my_mem_pool::iterator itr = memPool.begin();
      my_mem_pool::iterator itrEnd = memPool.end();

      bool testPassed = true;
      tl_int counter = 0;
      for (; itr != itrEnd; ++itr)
      {
        if (itr->GetElement()->x != counter &&
          itr->GetElement()->y != counter + 1 &&
          itr->GetElement()->z != counter + 2)
        {
          testPassed = false;
          break;
        }
        ++counter;
      }
      CHECK(testPassed);
    }
    CHECK(MyComponent::m_dtorCount == poolSize);
  }
}
