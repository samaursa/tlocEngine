#ifndef _TLOC_MATH_STATISTICS_FUNCTION_H_
#define _TLOC_MATH_STATISTICS_FUNCTION_H_

#include <tlocCore/tlocAssert.h>
#include <tlocCore/utilities/tlocUtils.h>
#include <tlocCore/types/tlocTypeTraits.h>
#include <tlocCore/smart_ptr/tlocSmartPtr.h>
#include <tlocCore/utilities/tlocType.h>

namespace tloc { namespace math { namespace statistics {

  namespace p_function
  {
    // ///////////////////////////////////////////////////////////////////////
    // MethodTypeHelper

    template <typename T, bool T_IsIntegral>
    struct ValueType;

    template <typename T>
    struct ValueType<T, true>
    { typedef T                                   value_type; };

    template <typename T>
    struct ValueType<T, false>
    { typedef typename T::value_type              value_type; };

    template <typename T_ArrayType>
    struct MethodTypes
    {
      typedef typename T_ArrayType::value_type          value_type;
      typedef typename T_ArrayType::const_iterator      itr_type;

      // the type that your array is storing, if complex, must have a
      // 'value_type' float
      typedef typename ValueType<value_type,
        Loki::TypeTraits<value_type>::isFloat>::value_type real_type;
    };

    // ///////////////////////////////////////////////////////////////////////
    // Mean/Average

    struct Mean
    {
      template <typename T_ArrayType>
      typename T_ArrayType::value_type
        DoCalculate(const T_ArrayType& a_array)
      {
        TLOC_ASSERT(a_array.size() > 0, "There is no data to work with");

        typedef typename MethodTypes<T_ArrayType>::value_type   value_type;
        typedef typename MethodTypes<T_ArrayType>::itr_type     itr_type;
        typedef typename MethodTypes<T_ArrayType>::real_type    real_type;

        value_type mean = value_type(0);

        itr_type itr    = a_array.begin();
        itr_type itrEnd = a_array.end();

        for (; itr != itrEnd; ++itr)
        { mean += *itr; }

        return mean /= core_utils::CastNumber<real_type>(a_array.size());
      }
    };
    typedef Mean                    Average;

    // ///////////////////////////////////////////////////////////////////////
    // Weighted average

    namespace p_weighted_average
    {
      struct Front;
      struct Back;
    };

    template <typename T_Weighting = p_weighted_average::Back>
    struct WeightedAverage_T;

    template <>
    struct WeightedAverage_T<p_weighted_average::Front>
    {
      template <typename T_ArrayType>
      typename T_ArrayType::value_type
        DoCalculate(const T_ArrayType& a_array)
      {
        TLOC_ASSERT(a_array.size() > 0, "There is no data to work with");

        typedef typename MethodTypes<T_ArrayType>::value_type      value_type;
        typedef typename MethodTypes<T_ArrayType>::itr_type        itr_type;
        typedef typename MethodTypes<T_ArrayType>::real_type       real_type;

        const value_type multiplier = 1.0f / a_array.size();

        value_type average = 0;
        value_type currMulti = multiplier;

        itr_type itr    = a_array.begin();
        itr_type itrEnd = a_array.end();

        for (; itr != itrEnd; ++itr)
        {
          average += ((*itr) * currMulti);
          currMulti += multiplier;
        }

        average *= multiplier;

        return average;
      }
    };

    template <>
    struct WeightedAverage_T<p_weighted_average::Back>
    {
      template <typename T_ArrayType>
      typename T_ArrayType::value_type
        DoCalculate(const T_ArrayType& a_array)
      {
        TLOC_ASSERT(a_array.size() > 0, "There is no data to work with");

        typedef typename MethodTypes<T_ArrayType>::value_type      value_type;
        typedef typename MethodTypes<T_ArrayType>::itr_type        itr_type;
        typedef typename MethodTypes<T_ArrayType>::real_type       real_type;

        const value_type multiplier = 1.0f / a_array.size();

        value_type average = 0;
        value_type currMulti = 1.0f;

        itr_type itr    = a_array.begin();
        itr_type itrEnd = a_array.end();

        for (; itr != itrEnd; ++itr)
        {
          average += ((*itr) * currMulti);
          currMulti -= multiplier;
        }

        average *= multiplier;

        return average;
      }
    };
  };

  // ///////////////////////////////////////////////////////////////////////
  // Function_T

  template <typename T_ArrayPtr, typename T_Method>
  class Function_T
  {
    TLOC_STATIC_ASSERT(
      (Loki::TypeTraits<T_ArrayPtr>::isPointer ||
       Loki::Conversion<T_ArrayPtr, core_sptr::SmartPtr>::exists),
       array_ptr_MUST_be_a_pointer_to_array_or_pointer_to_container_OR_smart_ptr_to_container);

  public:
    typedef T_ArrayPtr                                      array_ptr;
    typedef T_Method                                        func_type;

    typedef Function_T<array_ptr, func_type>                this_type;

    typedef typename PointeeType<array_ptr>::value_type     array_type;
    typedef typename array_type::value_type                 value_type;

  public:
    Function_T(array_ptr a_data);
    Function_T(array_ptr a_data, func_type a_func);

    value_type Calculate();

    TLOC_DECL_AND_DEF_GETTER(value_type, GetLastResult, m_result);
    TLOC_DECL_AND_DEF_GETTER(array_ptr, GetData, m_data);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE(array_ptr, SetData, m_data);

  protected:
    func_type   m_func;
    array_ptr   m_data;
    value_type  m_result;
  };

};};};

#endif