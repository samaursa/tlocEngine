#include "tlocTestCommon.h"

#include "tlocCore/tlocUtils.h"
#include "tlocCore/tlocTypes.h"

namespace TestingMemory
{
  USING_TLOC;

  TEST_CASE("Core/Utilities", "Testing operator macro")
  {
    struct simpleStruct
    {
      typedef simpleStruct object;

      simpleStruct(s32 val) : m_int(val) {}

      bool operator==(const simpleStruct& a_other) const
      { return m_int == a_other.m_int; }
      bool operator<(const simpleStruct& a_other) const
      { return m_int < a_other.m_int; }
      TLOC_DECLARE_OPERATORS(simpleStruct);

      s32 m_int;
    };

    simpleStruct a(1), b(2), c(3), d(1);

    CHECK(a == d);
    CHECK(d >= a);
    CHECK(d <= a);
    CHECK(a != b);

    CHECK(a < b);
    CHECK(b > a);
    CHECK(c >= a);
    CHECK(a <= c);
  }

  TEST_CASE("Core/Utilities/IsSamePointer", "")
  {
    s32* n = new s32(5);
    tl_size ptr = (tl_size)n;

    s32* p = new s32(6);
    tl_size ptr2 = (tl_size)p;

    CHECK(core::IsSamePointer(n, ptr) == true);
    CHECK(core::IsSamePointer(n, p) == false);
    CHECK(core::IsSamePointer(ptr, ptr2) == false);
    CHECK(core::IsSamePointer(p, ptr2) == true);

  }
};