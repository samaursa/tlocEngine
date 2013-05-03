#include "tlocTestCommon.h"

#include <tlocMath/types/tlocRay.h>

namespace TestingRay
{
  using namespace tloc;
  using namespace math;

  template <typename T, tl_size T_Size>
  void TestRay()
  {
    typedef math_t::Ray_T<T, T_Size>  ray_type;

    ray_type r;
    ray_type r2(typename ray_type::origin(math_t::Vector<T, T_Size>(1)),
                typename ray_type::direction(math_t::Vector<T, T_Size>(2)) );

    r = r2;

    CHECK( (r.GetOrigin() == r2.GetOrigin()) );
    CHECK( (r.GetDirection() == r2.GetDirection()) );
  }

  TEST_CASE("math/types/Ray", "")
  {
    TestRay<f32, 2>();
    TestRay<f64, 2>();

    TestRay<f32, 3>();
    TestRay<f64, 3>();
  }
};