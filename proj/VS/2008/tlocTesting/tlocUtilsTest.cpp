#include "tlocTestCommon.h"

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/utilities/tlocPointerUtils.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTemplateParams.h>

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl>
#include <tlocCore/containers/tlocList.h>
#include <tlocCore/containers/tlocList.inl>

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

  TEST_CASE("Core/Utilities/ArraySize", "Testing array size utility")
  {
    int someArray[50];
    char someCharArray[30];
    core::Array<int> dynArray; dynArray.resize(20);
    core::List<int> dynList; dynList.resize(5);

    CHECK(core::utils::ArraySize(someArray) == 50);
    CHECK(core::utils::ArraySize(someCharArray) == 30);
    CHECK(core::utils::ArraySize(dynArray) == 20);
    CHECK(core::utils::ArraySize(dynList) == 5);
  }

  TEST_CASE("Core/Utilities/IsSamePointer", "")
  {
    s32* n = new s32(5); //-V508
    tl_size ptr = (tl_size)n;

    s32* p = new s32(6); //-V508
    tl_size ptr2 = (tl_size)p;

    CHECK(core::utils::IsSamePointer(n, ptr) == true);
    CHECK(core::utils::IsSamePointer(n, p) == false);
    CHECK(core::utils::IsSamePointer(ptr, ptr2) == false);
    CHECK(core::utils::IsSamePointer(p, ptr2) == true);
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
      count = core::utils::EnumCounter<five>::result,
    };

    CHECK( count == 5);

    CHECK( (core::utils::EnumToIndex<five>::result) == 4);
    CHECK( (core::utils::EnumToIndex<one>::result) == 0);

    CHECK( (core::utils::EnumToIndex<five, true>::result) == 5);
    CHECK( (core::utils::EnumToIndex<one>::result) == 0);
  }

  TEST_CASE("Core/Utilities/NestedFunction", "")
  {
    TL_NESTED_FUNC_BEGIN(AddTwoNumbers) s32 AddTwoNumbers(s32 a, s32 b)
    {
      return a + b;
    }
    TL_NESTED_FUNC_END();

    CHECK( (TL_NESTED_CALL(AddTwoNumbers)(5, 5) == 10) );

    TL_NESTED_FUNC_BEGIN(AddToRef) void AddToRef(s32& a_inOut)
    {
      a_inOut++;
    }
    TL_NESTED_FUNC_END();

    s32 testNum = 0;
    TL_NESTED_CALL(AddToRef)(testNum);
    CHECK(testNum == 1);
  }

  struct getSet
  {
    getSet(tl_int a) : const_a(a) {}

    TLOC_DECL_AND_DEF_GETTER(tl_int, GetA, a);

    TLOC_DECL_AND_DEF_GETTER(tl_float, GetB, b);
    TLOC_DECL_AND_DEF_GETTER(tl_float*, GetC, c);

    TLOC_DECL_AND_DEF_GETTERS_DIRECT(tl_int, GetADirect, a);
    TLOC_DECL_AND_DEF_GETTER_DIRECT(const tl_int, GetConstADirect, const_a);

    TLOC_DECL_AND_DEF_GETTER_DIRECT(tl_float, GetBDirect, b);
    TLOC_DECL_AND_DEF_GETTER_DIRECT(tl_float*, GetCDirect, c);

    TLOC_DECL_AND_DEF_SETTER(tl_int, SetA, a);
    TLOC_DECL_AND_DEF_SETTER(tl_float*, SetC, c);

    void operator=(const getSet& a_other)
    {
      a = a_other.a;
      b = a_other.b;
      c = a_other.c;
    }

    tl_int          a;
    const tl_int    const_a;

    tl_float        b;
    tl_float*       c;
  };

  TEST_CASE("Core/Utilities/GetterSetter", "Getter setter macros")
  {
    getSet g(314);
    tl_float f = 3.0f;
    tl_float ff = 5.0f;

    g.a = 1;
    g.b = 2.0f;
    g.c = &f;

    CHECK(g.GetA() == 1);
    CHECK(g.GetB() == Approx(2.0f));
    CHECK(g.GetC() == &f);

    g.GetADirect() = 2;
    g.GetBDirect() = 3.0f;
    g.GetCDirect() = &ff;

    CHECK(g.GetADirect() == 2);
    CHECK(g.GetBDirect() == Approx(3.0f));
    CHECK(g.GetCDirect() == &ff);

    g.SetA(3);
    tl_float fff = 9.0f;
    g.SetC(&fff);

    CHECK(g.GetA() == 3);
    CHECK( *(g.GetC()) == Approx(9.0f));
  }
};