#include "tlocTestCommon.h"

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/types/tlocStrongType.inl.h>
#include <tlocCore/types/tlocTypeTraits.h>

namespace TestingStrongType
{
  using namespace tloc;
  using namespace core;

  template <typename T1, typename T2>
  typename T1::value_type AddFloats(T1 a_float1, T2 a_float2)
  {
    return a_float1 + a_float2;
  }

  struct ComplexType
  {
    ComplexType()
    { counter++; }

    ComplexType(const ComplexType&)
    { counter++; }

    float m_float1;
    float m_float2;

    static int counter;
  };

  int ComplexType::counter;

  TEST_CASE("core/types/StrongType_T", "")
  {
    typedef types::StrongType_T<tl_float, 0> type_1;
    typedef types::StrongType_T<tl_float, 1> type_2;
    typedef types::StrongType_T<tl_float, 2> type_3;
    typedef types::StrongType_T<tl_float, 3> type_4;
    typedef types::StrongType_T<tl_float, 4> type_5;

    type_1 t1(1.0f);
    type_2 t2(1.0f);
    type_3 t3(2.0f);
    type_4 t4(3.0f);

    tl_float myFloat = 5.0f;
    type_5 t5(myFloat);

    CHECK( (Loki::IsSameType<type_1, type_2>::value) == 0);
    CHECK( (Loki::IsSameType<type_1, type_1>::value) == 1);

    CHECK( AddFloats(t1, t2) == Approx(2.0f));
    CHECK( AddFloats(t2, t3) == Approx(3.0f));
    CHECK( AddFloats(t3, t4) == Approx(5.0f));
    CHECK( AddFloats(t5, t1) == Approx(6.0f));
  }

  TEST_CASE("core/types/StrongType_T/Complex", "")
  {
    // This is for testing purposes only, generally, you would want StrongType
    // to be ONLY used in function arguments to facilitate strong type checking

    typedef types::StrongType_T<ComplexType, 0> type_1;
    typedef types::StrongType_T<ComplexType, 1> type_2;
    typedef types::StrongType_T<ComplexType, 2> type_3;
    typedef types::StrongType_T<ComplexType, 3> type_4;

    CHECK(ComplexType::counter == 0);
    ComplexType c;
    CHECK(ComplexType::counter == 1);
    type_1 t1(c);
    CHECK(ComplexType::counter == 1);

    const ComplexType& d = t1;
    CHECK(&d == &c);
    CHECK(ComplexType::counter == 1);
    ComplexType e = t1;
    TLOC_UNUSED(e);
    CHECK(ComplexType::counter == 2);
  }
};