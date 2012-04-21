#include "tlocTestCommon.h"

#include "tlocCore/tlocUtils.h"
#include "tlocCore/tlocTypes.h"
#include "tlocCore/tlocTemplateParams.h"

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

  TEST_CASE("Core/Utilities/TemplateParams", "")
  {
    ParamList<u32> p1 = {1};
    CHECK(p1.m_param1 == 1);

    ParamList<u32, u32> p2 = {1, 2};
    CHECK(p2.m_param1 == 1);
    CHECK(p2.m_param2 == 2);

    ParamList<u32, u32, u32> p3 = {1, 2, 3};
    CHECK(p3.m_param1 == 1);
    CHECK(p3.m_param2 == 2);
    CHECK(p3.m_param3 == 3);

    ParamList<u32, u32, u32, u32> p4 = {1, 2, 3, 4};
    CHECK(p4.m_param1 == 1);
    CHECK(p4.m_param2 == 2);
    CHECK(p4.m_param3 == 3);
    CHECK(p4.m_param4 == 4);

    ParamList<u32, u32, u32, u32, u32> p5 = {1, 2, 3, 4, 5};
    CHECK(p5.m_param1 == 1);
    CHECK(p5.m_param2 == 2);
    CHECK(p5.m_param3 == 3);
    CHECK(p5.m_param4 == 4);
    CHECK(p5.m_param5 == 5);

    ParamList<u32, u32, u32, u32, u32, u32> p6 = {1, 2, 3, 4, 5, 6};
    CHECK(p6.m_param1 == 1);
    CHECK(p6.m_param2 == 2);
    CHECK(p6.m_param3 == 3);
    CHECK(p6.m_param4 == 4);
    CHECK(p6.m_param5 == 5);
    CHECK(p6.m_param6 == 6);

    ParamList<u32, u32, u32, u32, u32, u32, u32> p7 = {1, 2, 3, 4, 5, 6, 7};
    CHECK(p7.m_param1 == 1);
    CHECK(p7.m_param2 == 2);
    CHECK(p7.m_param3 == 3);
    CHECK(p7.m_param4 == 4);
    CHECK(p7.m_param5 == 5);
    CHECK(p7.m_param6 == 6);
    CHECK(p7.m_param7 == 7);

    ParamList<u32, u32, u32, u32, u32, u32, u32, u32> p8 =
    {1, 2, 3, 4, 5, 6, 7, 8};
    CHECK(p8.m_param1 == 1);
    CHECK(p8.m_param2 == 2);
    CHECK(p8.m_param3 == 3);
    CHECK(p8.m_param4 == 4);
    CHECK(p8.m_param5 == 5);
    CHECK(p8.m_param6 == 6);
    CHECK(p8.m_param7 == 7);
    CHECK(p8.m_param8 == 8);

    ParamList<u32, u32, u32, u32, u32, u32, u32, u32, u32> p9 =
    {1, 2, 3, 4, 5, 6, 7, 8, 9};
    CHECK(p9.m_param1 == 1);
    CHECK(p9.m_param2 == 2);
    CHECK(p9.m_param3 == 3);
    CHECK(p9.m_param4 == 4);
    CHECK(p9.m_param5 == 5);
    CHECK(p9.m_param6 == 6);
    CHECK(p9.m_param7 == 7);
    CHECK(p9.m_param8 == 8);
    CHECK(p9.m_param9 == 9);

    ParamList<u32, u32, u32, u32, u32, u32, u32, u32, u32, u32> p10 =
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    CHECK(p10.m_param1 == 1);
    CHECK(p10.m_param2 == 2);
    CHECK(p10.m_param3 == 3);
    CHECK(p10.m_param4 == 4);
    CHECK(p10.m_param5 == 5);
    CHECK(p10.m_param6 == 6);
    CHECK(p10.m_param7 == 7);
    CHECK(p10.m_param8 == 8);
    CHECK(p10.m_param9 == 9);
    CHECK(p10.m_param10 == 10);
  }

  TEST_CASE("Core/Utilities/EnumCounter", "")
  {
    enum
    {
      one   = 1 << 0,
      two   = 1 << 1,
      three = 1 << 2,
      four  = 1 << 3,
      five  = 1 << 4,
      count = core::EnumCounter<five>::result,
    };

    CHECK( (core::EnumCounter<count>::result) == 5);
    CHECK( (core::EnumCounter<count, true>::result) == 6);

    CHECK( (core::EnumToIndex<five>::result) == 4);
    CHECK( (core::EnumToIndex<one>::result) == 0);

    CHECK( (core::EnumToIndex<five, true>::result) == 5);
    CHECK( (core::EnumToIndex<one>::result) == 1);
  }
};