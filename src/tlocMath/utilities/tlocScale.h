#ifndef _TLOC_MATH_TYPES_NORMALIZER_H_
#define _TLOC_MATH_TYPES_NORMALIZER_H_

#include <tlocCore/types/tlocStrongType.h>
#include <tlocCore/tlocRange.h>

#include <tlocMath/tlocMathBase.h>

namespace tloc { namespace math { namespace utils {

  template <typename T_ValueType1, typename T_ValueType2>
  class Scale
  {
    TLOC_STATIC_ASSERT_IS_ARITH(T_ValueType1);
    TLOC_STATIC_ASSERT_IS_ARITH(T_ValueType2);

  public:
    typedef T_ValueType1                                value_type_1;
    typedef T_ValueType2                                value_type_2;
    typedef Scale<value_type_1, value_type_2>           this_type;

    typedef core::Range_T<value_type_1>                 range_type_1;
    typedef core::Range_T<value_type_2>                 range_type_2;

    typedef tl_float                                    common_type;

  public:
    template <typename T_Type1, typename T_Type2>
    Scale(core::Range_T<T_Type1> a_range1,
          core::Range_T<T_Type2> a_range2);

    //template <typename T>
    //T Scale(T a_valueToScale);

    template <typename T>
    T ScaleUp(T a_valueToScale);

    template <typename T>
    T ScaleDown(T a_valueToScale);

  private:
    template <typename T_Type1, typename T_Type2>
    void DoInitialize(core::Range_T<T_Type1> a_range1,
                      core::Range_T<T_Type2> a_range2);

    bool DoIsRange1Larger() const;

  private:
    range_type_1 m_range1;
    range_type_2 m_range2;

  };

  //------------------------------------------------------------------------
  // template definitions

  template <typename T_ValueType1, typename T_ValueType2>
  template <typename T_Type1, typename T_Type2>
  Scale<T_ValueType1, T_ValueType2>::
    Scale(core::Range_T<T_Type1> a_range1, core::Range_T<T_Type2> a_range2)
  {
    type_traits::AssertTypeIsSupported<T_Type1, value_type_1, value_type_2>();
    type_traits::AssertTypeIsSupported<T_Type2, value_type_1, value_type_2>();

    TLOC_STATIC_ASSERT( (Loki::Select<
      Loki::IsSameType<T_Type1, value_type_1>::value,
      Loki::IsSameType<T_Type2, value_type_2>,
      Loki::IsSameType<T_Type1, value_type_2> >::value),
      Range_types_not_supported_according_to_Scale_declaration);

    TLOC_STATIC_ASSERT( (Loki::Select<
      Loki::IsSameType<T_Type2, value_type_2>::value,
      Loki::IsSameType<T_Type1, value_type_1>,
      Loki::IsSameType<T_Type2, value_type_1> >::value),
      Range_types_not_supported_according_to_Scale_declaration);

    DoInitialize(a_range1, a_range2);
  }


};};};

#endif