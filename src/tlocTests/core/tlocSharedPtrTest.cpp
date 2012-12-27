#include "tlocTestCommon.h"

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/smart_ptr/tlocSharedPtr.inl>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl>

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/memory/tlocMemoryPool.inl>

namespace TestingSharedPtr
{
  using namespace tloc;
  using namespace core;

  struct SharedStruct
  {
    SharedStruct(tl_int a_value) : m_value(a_value)
    { ++m_numCtors; }

    ~SharedStruct()
    { ++m_numDtors; }

    tl_int m_value;

    static tl_int m_numCtors;
    static tl_int m_numDtors;
  };

  tl_int SharedStruct::m_numCtors;
  tl_int SharedStruct::m_numDtors;

  void ResetSharedStructStaticVars()
  {
    SharedStruct::m_numCtors = 0;
    SharedStruct::m_numDtors = 0;
  }

  void PassSharedPtr(const smart_ptr::SharedPtr<SharedStruct>& a_other)
  {
    tl_int currCount = a_other.use_count();
    smart_ptr::SharedPtr<SharedStruct> localPtr = a_other;
    CHECK(localPtr.use_count() == currCount + 1);
  }

#define CHECK_CTOR_DTOR_COUNT(_ctorCount_, _dtorCount_)\
  CHECK(SharedStruct::m_numCtors == _ctorCount_);\
  CHECK(SharedStruct::m_numDtors == _dtorCount_)

  TEST_CASE("core/smart_ptr/shared_ptr", "")
  {
    {
      smart_ptr::SharedPtr<SharedStruct> sp(nullptr);
      CHECK_FALSE(sp);
    }

    {
      smart_ptr::SharedPtr<SharedStruct> sp( new SharedStruct(5) );
      CHECK(sp);
      CHECK_CTOR_DTOR_COUNT(1, 0);
      CHECK(sp.use_count() == 1);
      smart_ptr::SharedPtr<SharedStruct> sp2 = sp;
      CHECK_CTOR_DTOR_COUNT(1, 0);
      CHECK(sp.use_count() == 2);

      CHECK(sp->m_value == 5);
      CHECK(sp2->m_value == 5);

      CHECK( (*sp).m_value == 5);
      CHECK( (*sp2).m_value == 5);

      CHECK_CTOR_DTOR_COUNT(1, 0);
      PassSharedPtr(sp);
      CHECK_CTOR_DTOR_COUNT(1, 0);
    }
    CHECK_CTOR_DTOR_COUNT(1, 1);

    {
      smart_ptr::SharedPtr<SharedStruct> sp;
      CHECK_FALSE(sp);
      // This SHOULD fire an assertion - because null copy is disabled
      // smart_ptr::SharedPtr<Shared> sp2 = sp;
      CHECK(sp.use_count() == 0);
      //CHECK(sp2.use_count() == 0);

    } // Should not crash when being destroyed

    {
      typedef smart_ptr::SharedPtr<SharedStruct,
              smart_ptr::p_shared_ptr::null_copy::Allow> shared_ptr_type;

      shared_ptr_type sp;
      shared_ptr_type sp2 = sp; // Should NOT fire an assertion

      CHECK(sp.use_count() == 0);
      CHECK(sp2.use_count() == 0);

    } // Should not crash when being destroyed

    {
      ResetSharedStructStaticVars();

      smart_ptr::SharedPtr<SharedStruct> sp(new SharedStruct(10));
      smart_ptr::SharedPtr<SharedStruct> sp2 = sp;
      CHECK(sp.use_count() == 2);

      smart_ptr::SharedPtr<SharedStruct> sp3(new SharedStruct(50));
      sp2 = sp3;
      CHECK(sp.use_count() == 1);
      CHECK(sp3.use_count() == 2);

      CHECK_CTOR_DTOR_COUNT(2, 0);
      sp = sp3;
      CHECK_CTOR_DTOR_COUNT(2, 1);
      CHECK(sp3.use_count() == 3);
    }
    CHECK_CTOR_DTOR_COUNT(2, 2);

    {
      ResetSharedStructStaticVars();

      smart_ptr::SharedPtr<SharedStruct> sp(new SharedStruct(10));
      smart_ptr::SharedPtr<SharedStruct> sp2(new SharedStruct(5));

      CHECK(sp->m_value == 10);
      CHECK(sp2->m_value == 5);

      sp.swap(sp2);

      CHECK(sp->m_value == 5);
      CHECK(sp2->m_value == 10);

      CHECK_CTOR_DTOR_COUNT(2, 0);
    }
    CHECK_CTOR_DTOR_COUNT(2, 2);
  }

  TEST_CASE("core/smart_ptr/shared_ptr/const", "")
  {
    {
      smart_ptr::SharedPtr<const SharedStruct> sp(nullptr);
      CHECK_FALSE(sp);
    }

    {
      smart_ptr::SharedPtr<const SharedStruct> sp(new SharedStruct(10));
      CHECK(sp);
    }
  }

  TEST_CASE("core/smart_ptr/shared_ptr/reset", "")
  {
    {
      ResetSharedStructStaticVars();

      smart_ptr::SharedPtr<SharedStruct> sp(new SharedStruct(50));
      CHECK_CTOR_DTOR_COUNT(1, 0);
      sp.reset();
      CHECK_CTOR_DTOR_COUNT(1, 1);
    }

    {
      ResetSharedStructStaticVars();

      smart_ptr::SharedPtr<SharedStruct> sp(new SharedStruct(50));
      smart_ptr::SharedPtr<SharedStruct> sp2(sp);
      sp.reset();

      CHECK_CTOR_DTOR_COUNT(1, 0);
    }

    {
      ResetSharedStructStaticVars();

      smart_ptr::SharedPtr<SharedStruct> sp(new SharedStruct(50));
      CHECK_CTOR_DTOR_COUNT(1, 0);
      sp.reset(new SharedStruct(10));
      CHECK_CTOR_DTOR_COUNT(2, 1);

      CHECK(sp.use_count() == 1);

      smart_ptr::SharedPtr<SharedStruct> sp2(sp);
      CHECK(sp.use_count() == 2);
      sp.reset();
      CHECK_CTOR_DTOR_COUNT(2, 1);
      sp2.reset();
      CHECK_CTOR_DTOR_COUNT(2, 2);
    }
  }

  template <typename T_ContainerType>
  void TestContainers()
  {
    ResetSharedStructStaticVars();

    typedef smart_ptr::SharedPtr<SharedStruct>      shared_ptr_type;
    typedef T_ContainerType                   shared_array_type;

    const tl_int count = 2;

    {
      shared_array_type sa;
      for (int i = 0; i < count; ++i)
      { sa.push_back( shared_ptr_type(new SharedStruct(i)) ); }

      CHECK(SharedStruct::m_numCtors == count);

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
      CHECK_CTOR_DTOR_COUNT(count, 0);
    }
    CHECK_CTOR_DTOR_COUNT(count, count);
  }

  TEST_CASE("core/smart_ptr/shared_ptr/with_containers", "")
  {
    TestContainers<tl_array<smart_ptr::SharedPtr<SharedStruct> >::type>();
    TestContainers<tl_singly_list<smart_ptr::SharedPtr<SharedStruct> >::type>();
    TestContainers<tl_doubly_list<smart_ptr::SharedPtr<SharedStruct> >::type>();
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
