#include "tlocTestCommon.h"

#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocCore/utilities/tlocPointerUtils.h>

#include <tlocCore/types/tlocTypes.h>
#include <tlocCore/types/tlocTemplateParams.h>

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArray.inl.h>
#include <tlocCore/containers/tlocList.h>
#include <tlocCore/containers/tlocList.inl.h>

namespace TestingMemory
{
  using namespace tloc;

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
    using namespace core::containers;

    int someArray[50];
    char someCharArray[30];
    Array<int> dynArray; dynArray.resize(20);
    List<int> dynList; dynList.resize(5);

    CHECK(core::utils::ArraySize(someArray) == 50);
    CHECK(core::utils::ArraySize(someCharArray) == 30);
    CHECK(core::utils::ArraySize(dynArray) == 20);
    CHECK(core::utils::ArraySize(dynList) == 5);
  }

  TEST_CASE("Core/Utilities/IsSamePointer", "")
  {
    s32* n = new s32(5); //-V508
    tl_uintptr ptr = core_utils::GetMemoryAddress(n);
    CHECK(ptr == (tl_uintptr)n);

    s32* p = new s32(6); //-V508
    tl_uintptr ptr2 = core_utils::GetMemoryAddress(p);
    CHECK(ptr2 == (tl_uintptr)p);

    CHECK(core_utils::IsSamePointer(n, ptr) == true);
    CHECK(core_utils::IsSamePointer(n, p) == false);
    CHECK(core_utils::IsSamePointer(ptr, ptr2) == false);
    CHECK(core_utils::IsSamePointer(p, ptr2) == true);
  }

  TEST_CASE("Core/Utilities/EnumCounter", "")
  {
    enum
    {
      zero  = 0,
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

    CHECK( (core_utils::EnumToIndex<zero, true>::result) == 0);
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

  TEST_CASE("Core/Utilities/ParamVariableWithSetter", "")
  {
    struct params
    {
      typedef params      this_type;

      TLOC_DECL_PARAM_VAR(bool, SetParam1, m_param1);
      TLOC_DECL_PARAM_VAR(bool, SetParam2, m_param2);
      TLOC_DECL_PARAM_VAR(bool, SetParam3, m_param3);
    };

    params p = params().SetParam1(true).SetParam2(false).SetParam3(true);

    CHECK(p.m_param1);
    CHECK_FALSE(p.m_param2);
    CHECK(p.m_param3);
  }
};