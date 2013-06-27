#include "tlocTestCommon.h"

#include <tlocCore/types/tlocAny.h>
#include <tlocCore/types/tlocAny.inl.h>

// We are using std::string instead of our string to try to segregate the tests
// as much as possible from the rest of the engine code
#include <string>

namespace TestingAnyType
{
  using namespace tloc;
  using namespace core;

#define CHECK_MATH_VEC3(_vec_, _x_, _y_, _z_)\
  CHECK(_vec_.x == _x_);\
  CHECK(_vec_.y == _y_);\
  CHECK(_vec_.z == _z_)

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

  struct MathVec
  {
    MathVec(tl_float a_x, tl_float a_y, tl_float a_z)
      : x(a_x), y(a_y), z(a_z)
    { }

    tl_float x, y, z;
  };

  TEST_CASE("core/types/Any", "")
  {
    {
      types::Any a;
      a = 10.0f;
      CHECK_FALSE(a.IsEmpty());
      CHECK(a.Cast<float>() == Approx(10.0f));
    }
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

      a.swap(b);
      CHECK(a.Cast<tl_int>() == 2);
      CHECK(b.Cast<tl_int>() == 1);

      swap(a, b);
      CHECK(b.Cast<tl_int>() == 2);
      CHECK(a.Cast<tl_int>() == 1);
    }

    {
      types::Any a, b;

      a.Assign(std::string("Hello"));
      b.Assign(std::string("World"));

      CHECK(a.Cast<std::string>().compare("Hello") == 0);
      CHECK(b.Cast<std::string>().compare("World") == 0);

      a.swap(b);

      CHECK(a.Cast<std::string>().compare("World") == 0);
      CHECK(b.Cast<std::string>().compare("Hello") == 0);
    }

    {
      types::Any a, b;

      a.Assign(MathVec(1, 2, 3));
      b.Assign(MathVec(4, 5, 6));

      TLOC_ASSERT(tloc::core::memory::IsValidHeapPointer( &( a.Cast<MathVec>()) ), "!");

      CHECK_MATH_VEC3(a.Cast<MathVec>(), 1, 2, 3);
      CHECK_MATH_VEC3(b.Cast<MathVec>(), 4, 5, 6);

      a.swap(b);

      CHECK_MATH_VEC3(a.Cast<MathVec>(), 4, 5, 6);
      CHECK_MATH_VEC3(b.Cast<MathVec>(), 1, 2, 3);
    }

    {
      // Bug fix
      types::Any a, b;
      a = MathVec(1, 2, 3);
      b = a;

      CHECK_MATH_VEC3(a.Cast<MathVec>(), 1, 2, 3);
      CHECK_MATH_VEC3(b.Cast<MathVec>(), 1, 2, 3);
    }
  }
};