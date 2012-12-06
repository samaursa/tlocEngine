#include "tlocTestCommon.h"

#include <tlocCore/smart_ptr/tlocSmartPtr.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/containers/tlocContainers.inl>

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
}
