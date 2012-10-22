#include "tlocTestCommon.h"

#include <tlocCore/types/tlocAny.h>
#include <tlocCore/types/tlocAny.inl>

// We are using std::string instead of our string to try to segregate the tests
// as much as possible from the rest of the engine code
#include <string>

namespace TestingAnyType
{
  using namespace tloc;
  using namespace core;

  struct AnyTracker
  {
    AnyTracker()
    {
      m_ctorCount++;
    }

    AnyTracker(const AnyTracker&)
    {
      m_ctorCount++;
    }

    ~AnyTracker()
    {
      m_dtorCount++;
    }

    static tl_size m_ctorCount, m_dtorCount;
  };

  tl_size AnyTracker::m_ctorCount;
  tl_size AnyTracker::m_dtorCount;

  struct ComplexObject
  {
    std::string m_string;
  };

  TEST_CASE("core/types/Any", "")
  {
    {
      types::Any  a;

      CHECK(a.IsEmpty());
      a.Assign((tl_int)1);
      CHECK_FALSE(a.IsEmpty());
      a.IsSameType(tl_int());

      a.Reset();
      CHECK(a.IsEmpty());
      a.Assign(AnyTracker());
      CHECK(AnyTracker::m_ctorCount == 2);
      CHECK(AnyTracker::m_dtorCount == 1);
    }

    CHECK(AnyTracker::m_dtorCount == 2);

    {
      types::Any a, b;

      a.Assign((tl_int)1);
      b.Assign((tl_int)2);

      CHECK(a.Cast<tl_int>() == 1);
      CHECK(b.Cast<tl_int>() == 2);

      a.Swap(b);
      CHECK(a.Cast<tl_int>() == 2);
      CHECK(b.Cast<tl_int>() == 1);
    }

    {
      types::Any a, b;

      a.Assign(std::string("Hello"));
      b.Assign(std::string("World"));

      CHECK(a.Cast<std::string>().compare("Hello") == 0);
      CHECK(b.Cast<std::string>().compare("World") == 0);

      a.Swap(b);

      CHECK(a.Cast<std::string>().compare("World") == 0);
      CHECK(b.Cast<std::string>().compare("Hello") == 0);
    }
  }

};