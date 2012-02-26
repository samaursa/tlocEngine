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
};