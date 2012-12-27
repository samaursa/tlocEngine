#include "tlocTestCommon.h"

#include <tlocCore/smart_ptr/tlocUniquePtr.h>
#include <tlocCore/smart_ptr/tlocUniquePtr.inl>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl>

#include <tlocCore/memory/tlocMemoryPool.h>
#include <tlocCore/memory/tlocMemoryPool.inl>

namespace TestingUniquePtr
{
  using namespace tloc;
  using namespace core;

  struct UniqueStruct
  {
    UniqueStruct(tl_int a_value) : m_value(a_value)
    { ++m_numCtors; }

    ~UniqueStruct()
    { ++m_numDtors; }

    tl_int m_value;

    static tl_int m_numCtors;
    static tl_int m_numDtors;
  };

  tl_int UniqueStruct::m_numCtors;
  tl_int UniqueStruct::m_numDtors;

  void ResetUniqueStructStaticVars()
  {
    UniqueStruct::m_numCtors = 0;
    UniqueStruct::m_numDtors = 0;
  }

#define CHECK_CTOR_DTOR_COUNT(_ctorCount_, _dtorCount_)\
  CHECK(UniqueStruct::m_numCtors == _ctorCount_);\
  CHECK(UniqueStruct::m_numDtors == _dtorCount_)

  TEST_CASE("core/smart_ptr/unique_ptr", "")
  {
    {
      smart_ptr::UniquePtr<UniqueStruct> up = nullptr;
      CHECK_FALSE(up);
    }

    {
      smart_ptr::UniquePtr<UniqueStruct> up;
      CHECK_CTOR_DTOR_COUNT(0, 0);
    }
    CHECK_CTOR_DTOR_COUNT(0, 0);

    {
      ResetUniqueStructStaticVars();

      UniqueStruct* u = new UniqueStruct(1);
      smart_ptr::UniquePtr<UniqueStruct> up(u);
      CHECK_CTOR_DTOR_COUNT(1, 0);
    }
    CHECK_CTOR_DTOR_COUNT(1, 1);

    {
      ResetUniqueStructStaticVars();

      UniqueStruct* u = new UniqueStruct(1);
      smart_ptr::UniquePtr<UniqueStruct> up(u);
      up.reset();
      CHECK_CTOR_DTOR_COUNT(1, 1);
    }

    {
      ResetUniqueStructStaticVars();

      CHECK_CTOR_DTOR_COUNT(0, 0);
      smart_ptr::UniquePtr<UniqueStruct>  up(new UniqueStruct(5));
      CHECK(up);
      CHECK_CTOR_DTOR_COUNT(1, 0);
    }
    CHECK(UniqueStruct::m_numDtors == 1);

    {
      ResetUniqueStructStaticVars();

      smart_ptr::UniquePtr<UniqueStruct>  up(new UniqueStruct(5));
      CHECK(up);
      smart_ptr::UniquePtr<UniqueStruct>  up2(up);
      CHECK(up2);
      CHECK_FALSE(up);

      CHECK_CTOR_DTOR_COUNT(1, 0);
      up2.reset();
      CHECK_CTOR_DTOR_COUNT(1, 1);
    }

    {
      ResetUniqueStructStaticVars();

      smart_ptr::UniquePtr<UniqueStruct> up(new UniqueStruct(10));
      CHECK(up->m_value == 10);
      smart_ptr::UniquePtr<UniqueStruct> up2(new UniqueStruct(5));
      CHECK(up2->m_value == 5);

      // This should NOT compile
      //smart_ptr::UniquePtr<UniqueStruct> up3 = up2;

      CHECK( (*up).m_value == 10);
      CHECK(up.get() == &(*up));

      up.swap(up2);
      CHECK(up->m_value == 5);
      CHECK(up2->m_value == 10);
    }
  }

  template <typename T_ContainerType>
  void TestContainers()
  {
    ResetUniqueStructStaticVars();

    typedef smart_ptr::UniquePtr<UniqueStruct>      unique_ptr_type;
    typedef T_ContainerType                         shared_array_type;

    const tl_int count = 2;

    {
      shared_array_type sa;
      for (int i = 0; i < count; ++i)
      { sa.push_back( unique_ptr_type(new UniqueStruct(i)) ); }

      CHECK(UniqueStruct::m_numCtors == count);

      bool testsPassed = true;
      tl_int counter = 0;
      for (shared_array_type::iterator itr = sa.begin(), itrEnd = sa.end();
           itr != itrEnd; ++itr)
      {
        if ( (*itr)->m_value != counter)
        { testsPassed = false; break; }

        ++counter;
      }
      CHECK(testsPassed);
      CHECK_CTOR_DTOR_COUNT(count, 0);
    }

    CHECK_CTOR_DTOR_COUNT(count, count);
  }

  TEST_CASE("core/smart_ptr/unique_ptr/with containers", "")
  {
    TestContainers<tl_array<smart_ptr::UniquePtr<UniqueStruct> >::type>();
    TestContainers<tl_singly_list<smart_ptr::UniquePtr<UniqueStruct> >::type>();
    TestContainers<tl_doubly_list<smart_ptr::UniquePtr<UniqueStruct> >::type>();
  }
}