#include "tlocScale.h"

namespace tloc { namespace math { namespace utils {

  namespace priv {

    // If the user switched the types in the ctor (i.e. T_ValueType1 in Scale<>
    // matches T_Type2 in ctor) then we need to select the appropriate function.
    struct TypesSwitched {};
    struct TypesNotSwitched {};

    template <typename T_Type1, typename T_Type2>
    void DoInitialize(const core::Range_T<T_Type1> a_range1,
                      const core::Range_T<T_Type2> a_range2,
                      core::Range_T<T_Type1>& a_rangeToSet1,
                      core::Range_T<T_Type2>& a_rangeToSet2,
                      TypesNotSwitched)
    {
      a_rangeToSet1 = a_range1;
      a_rangeToSet2 = a_range2;
    }

    template <typename T_Type1, typename T_Type2>
    void DoInitialize(const core::Range_T<T_Type1> a_range1,
                      const core::Range_T<T_Type2> a_range2,
                      core::Range_T<T_Type2>& a_rangeToSet1,
                      core::Range_T<T_Type1>& a_rangeToSet2,
                      TypesSwitched)
    {
      a_rangeToSet2 = a_range1;
      a_rangeToSet1 = a_range2;
    }

    template <typename T_Type1, typename T_Type2>
    void DoInitialize(const core::Range_T<T_Type1> a_range1,
                      const core::Range_T<T_Type2> a_range2,
                      core::Range_T<T_Type1>& a_rangeToSet1,
                      core::Range_T<T_Type2>& a_rangeToSet2,
                      TypesSwitched)
    {
      a_rangeToSet2 = a_range1;
      a_rangeToSet1 = a_range2;
    }

  }

#define SCALE_TEMPS   typename T_ValueType1, typename T_ValueType2
#define SCALE_PARAMS  T_ValueType1, T_ValueType2
#define SCALE_TYPE    template Scale<SCALE_PARAMS>

  template <SCALE_TEMPS>
  template <typename T_Type1, typename T_Type2>
  void Scale<SCALE_PARAMS>::
    DoInitialize(const core::Range_T<T_Type1> a_range1,
                 const core::Range_T<T_Type2> a_range2)
  {
    typedef Loki::Select<
      Loki::IsSameType<T_Type1, value_type_1>::value,
      priv::TypesNotSwitched, priv::TypesSwitched>::Result type_switched_or_not;

    priv::DoInitialize<T_Type1, T_Type2>
      (a_range1, a_range2, m_range1, m_range2, type_switched_or_not());
  }

  template <SCALE_TEMPS>
  bool Scale<SCALE_PARAMS>::
    DoIsRange1Larger() const
  {
    return false;
  }

  template <SCALE_TEMPS>
  template <typename T>
  T Scale<SCALE_PARAMS>::
    ScaleUp(T a_valueToScale)
  {

  }

  template <SCALE_TEMPS>
  template <typename T>
  T Scale<SCALE_PARAMS>::
    ScaleDown(T a_valueToScale)
  {
  }

  //------------------------------------------------------------------------
  // Explicit instantiation

#define TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type1_, _type2_)\
  template class Scale<_type1_, _type2_>;\
  \
  template void \
  Scale<_type1_, _type2_>::DoInitialize(core::Range_T<_type1_>,\
                                        core::Range_T<_type2_>);\
  \
  template void \
  Scale<_type1_, _type2_>::DoInitialize(core::Range_T<_type2_>,\
                                        core::Range_T<_type1_>)

#define TLOC_EXPLICITLY_INSTANTIATE_SCALE_ALL_TYPES(_type_)\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, s8);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, s16);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, s32);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, s64);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, u8);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, u16);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, u32);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, u64);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, f32);\
  TLOC_EXPLICITLY_INSTANTIATE_SCALE(_type_, f64)

  TLOC_EXPLICITLY_INSTANTIATE_SCALE_ALL_TYPES(s8);

};};};