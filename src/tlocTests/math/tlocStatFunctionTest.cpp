#include "tlocTestCommon.h"

#include <tlocCore/iterators/tlocIterator.inl.h>
#include <tlocCore/tlocAlgorithms.inl.h>

#include <tlocCore/containers/tlocArray.h>
#include <tlocCore/containers/tlocArrayFixed.h>
#include <tlocCore/containers/tlocArrayFixed.inl.h>
#include <tlocCore/containers/tlocList.h>

#include <tlocCore/utilities/tlocContainerUtils.h>
#include <tlocMath/statistics/tlocStatFunction.h>

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
    CHECK(f.Calculate() == 22);
  }

  TEST_CASE("math/statistics/Function_T", "")
  {
    SECTION("mean", "")
    {
      TestMean<core_conts::Array<f32> >();
      TestMean<core_conts::ArrayFixed<f32, 15> >();
      TestMean<core_conts::List<f32> >();
    }
  }
}