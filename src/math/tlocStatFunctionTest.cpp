#include "tlocTestCommon.h"

#include <tlocCore/iterators/tlocIterator.inl.h>
#include <tlocCore/tlocAlgorithms.inl.h>

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArrayFixed.h>
#include <tlocCore/containers/tlocArrayFixed.inl.h>
#include <tlocCore/containers/tlocList.h>
#include <tlocCore/containers/tlocList.inl.h>

#include <tlocCore/utilities/tlocContainerUtils.h>

#include <tlocMath/statistics/tlocStatFunction.h>
#include <tlocMath/statistics/tlocStatFunction.inl.h>

using namespace tloc;

namespace TestingStatFunction
{
  template <typename T_ArrayType>
  void TestMean()
  {
    using namespace math::statistics;

    typedef T_ArrayType                       array_type;
    typedef typename array_type::value_type   value_type;
    typedef typename array_type::iterator     itr_type;

    value_type data[] = {3, 7, 5, 13, 20, 23, 39, 23, 40, 23, 14, 12, 56, 23, 29};

    array_type dataCont;
    core::copy(data, data + core_utils::ArraySize(data),
               core::MakeBackInsertIterator(dataCont));

    Function_T<T_ArrayType*, p_function::Mean> f(&dataCont);
    CHECK(f.Calculate() == Approx(22));
    CHECK(f.GetLastResult() == Approx(22));
  }

  template <typename T_ArrayType>
  void TestWeightedAverage()
  {
    using namespace math::statistics;

    typedef T_ArrayType                       array_type;
    typedef typename array_type::value_type   value_type;
    typedef typename array_type::iterator     itr_type;

    array_type dataCont;
    dataCont.push_back(0);
    dataCont.push_back(1);

    Function_T<T_ArrayType*, p_function::WeightedAverage_T
      <p_function::p_weighted_average::Front> > f(&dataCont);

    CHECK(f.Calculate() == 0.5f);

    dataCont.push_back(2);

    {
      value_type res = ((0 * 1.0f/3.0f) + (1 * 2.0f/3.0f) + (2 * 3.0f/3.0f)) / 3.0f;
      CHECK(f.Calculate() == Approx(res) );
    }

    Function_T<T_ArrayType*, p_function::WeightedAverage_T
      <p_function::p_weighted_average::Back> > fb(&dataCont);

    {
      value_type res = ((0 * 3.0f/3.0f) + (1 * 2.0f/3.0f) + (2 * 1.0f/3.0f)) / 3.0f;
      CHECK(fb.Calculate() == Approx(res) );
    }
  }

  TEST_CASE("math/statistics/Function_T", "")
  {
    SECTION("mean", "")
    {
      TestMean<core_conts::Array<f32> >();
      TestMean<core_conts::ArrayFixed<f32, 100> >();
      TestMean<core_conts::List<f32> >();
    }

    SECTION("weighted average", "")
    {
      TestWeightedAverage<core_conts::Array<f32> >();
      TestWeightedAverage<core_conts::ArrayFixed<f32, 100> >();
      TestWeightedAverage<core_conts::List<f32> >();
    }
  }
}