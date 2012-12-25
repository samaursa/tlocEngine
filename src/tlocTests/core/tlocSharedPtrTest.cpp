#include "tlocTestCommon.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

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
    tl_int currCount = a_other.use_count();
    smart_ptr::SharedPtr<Shared> localPtr = a_other;
    CHECK(localPtr.use_count() == currCount + 1);
  }

  TEST_CASE("core/smart_ptr/shared_ptr", "")
  {
    {
      smart_ptr::SharedPtr<Shared> sp( new Shared(5) );
      CHECK(sp);
      CHECK(Shared::m_numCtors == 1);
      CHECK(sp.use_count() == 1);
      smart_ptr::SharedPtr<Shared> sp2 = sp;
      CHECK(Shared::m_numCtors == 1);
      CHECK(sp.use_count() == 2);

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
      CHECK_FALSE(sp);
      // This SHOULD fire an assertion - because null copy is disabled
      // smart_ptr::SharedPtr<Shared> sp2 = sp;
      CHECK(sp.use_count() == 0);
      //CHECK(sp2.use_count() == 0);

    } // Should not crash when being destroyed

    {
      typedef smart_ptr::SharedPtr<Shared,
              smart_ptr::p_shared_ptr::null_copy::Allow> shared_ptr_type;

      shared_ptr_type sp;
      shared_ptr_type sp2 = sp; // Should NOT fire an assertion

      CHECK(sp.use_count() == 0);
      CHECK(sp2.use_count() == 0);

    } // Should not crash when being destroyed

    {
      Shared::m_numCtors = 0;
      Shared::m_numDtors = 0;

      smart_ptr::SharedPtr<Shared> sp(new Shared(10));
      smart_ptr::SharedPtr<Shared> sp2 = sp;
      CHECK(sp.use_count() == 2);

      smart_ptr::SharedPtr<Shared> sp3(new Shared(50));
      sp2 = sp3;
      CHECK(sp.use_count() == 1);
      CHECK(sp3.use_count() == 2);

      CHECK(Shared::m_numDtors == 0);
      sp = sp3;
      CHECK(Shared::m_numDtors == 1);
      CHECK(sp3.use_count() == 3);
    }
    CHECK(Shared::m_numDtors == 2);
  }

  TEST_CASE("core/smart_ptr/shared_ptr/reset", "")
  {
    {
      Shared::m_numCtors = 0;
      Shared::m_numDtors = 0;
      smart_ptr::SharedPtr<Shared> sp(new Shared(50));
      CHECK(Shared::m_numCtors == 1);
      sp.reset();
      CHECK(Shared::m_numDtors == 1);
    }

    {
      Shared::m_numCtors = 0;
      Shared::m_numDtors = 0;
      smart_ptr::SharedPtr<Shared> sp(new Shared(50));
      smart_ptr::SharedPtr<Shared> sp2(sp);
      sp.reset();

      CHECK(Shared::m_numDtors == 0);
    }

    {
      Shared::m_numCtors = 0;
      Shared::m_numDtors = 0;
      smart_ptr::SharedPtr<Shared> sp(new Shared(50));
      CHECK(Shared::m_numCtors == 1);
      CHECK(Shared::m_numDtors == 0);
      sp.reset(new Shared(10));
      CHECK(Shared::m_numCtors == 2);
      CHECK(Shared::m_numDtors == 1);

      CHECK(sp.use_count() == 1);

      smart_ptr::SharedPtr<Shared> sp2(sp);
      CHECK(sp.use_count() == 2);
      sp.reset();
      CHECK(Shared::m_numDtors == 1);
      sp2.reset();
      CHECK(Shared::m_numDtors == 2);
    }
  }

  template <typename T_ContainerType>
  void TestContainers()
  {
    Shared::m_numCtors = 0;
    Shared::m_numDtors = 0;

    typedef smart_ptr::SharedPtr<Shared>      shared_ptr_type;
    typedef T_ContainerType                   shared_array_type;

    const tl_int count = 2;

    {
      shared_array_type sa;
      for (int i = 0; i < count; ++i)
      { sa.push_back( shared_ptr_type(new Shared(i)) ); }

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

  TEST_CASE("core/smart_ptr/shared_ptr/with_containers", "")
  {
    TestContainers<tl_array<smart_ptr::SharedPtr<Shared> >::type>();
    TestContainers<tl_singly_list<smart_ptr::SharedPtr<Shared> >::type>();
    TestContainers<tl_doubly_list<smart_ptr::SharedPtr<Shared> >::type>();
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

  struct base
  {
    base() : m_value(0)
    {
      m_ctorCount++;
    }

    virtual ~base()
    {
      m_dtorCount++;
    }

    virtual void foo(tl_int) = 0;
    tl_int m_value;

    static tl_int m_ctorCount;
    static tl_int m_dtorCount;
  };

  tl_int base::m_ctorCount;
  tl_int base::m_dtorCount;

  struct derived : public base
  {
    virtual void foo(tl_int a_num)
    {
      m_value = a_num;
    }
  };

  TEST_CASE("core/smart_ptr/shared_ptr/polymorphic_behavior", "")
  {
    {
      CHECK(base::m_ctorCount == 0);
      smart_ptr::SharedPtr<base> basePtr(new derived());
      CHECK(base::m_ctorCount == 1);
    }
    CHECK(base::m_dtorCount == 1);

    {
      smart_ptr::SharedPtr<base> basePtr(new derived());
      CHECK(basePtr->m_value == 0);
      basePtr->foo(5);
      CHECK(basePtr->m_value == 5);

      smart_ptr::SharedPtr<derived> derPtr(new derived());
      derPtr->foo(10);
      basePtr = derPtr;
      CHECK(base::m_dtorCount == 2);
      CHECK(basePtr->m_value == 10);

      smart_ptr::SharedPtr<base> basePtr2(derPtr);

      // This should fail to compile - so don't uncomment :)
      //smart_ptr::SharedPtr<derived> d(basePtr2);

      smart_ptr::SharedPtr<derived> convToDer;
      CHECK(base::m_ctorCount == 3);
      CHECK(base::m_dtorCount == 2);

      // TODO: Test with static_pointer_cast<>() when it is available
      //convToDer.CastFrom(basePtr2);
      //CHECK(convToDer->m_value == 10);
    }
    CHECK(base::m_ctorCount == 3);
    CHECK(base::m_dtorCount == 3);
  }
}
