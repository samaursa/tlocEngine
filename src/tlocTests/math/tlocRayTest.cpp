#include "tlocTestCommon.h"

#include <tlocMath/types/tlocRay.h>
#include <tlocMath/component_system/tlocTransform.h>
#include <tlocMath/types/tlocAngle.h>

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

  TEST_CASE("math/types/Ray2/operations", "")
  {
    typedef math_t::Ray2f32         ray_type;
    typedef ray_type::vec_type      vec_type;
    typedef ray_type::dir_vec_type  dir_vec_type;

    ray_type  r1(ray_type::origin(vec_type(1, 2)) );
    ray_type  r2(ray_type::origin(vec_type(3, 5)) );

    ray_type res = r1 + r2;
    CHECK( (res.GetOrigin() == vec_type(4, 7)) );
    CHECK( (res.GetDirection() == dir_vec_type(0, 0, 1)) );

    res = r1 - r2;
    CHECK( (res.GetOrigin() == vec_type(-2, -3)) );
    CHECK( (res.GetDirection() == dir_vec_type(0, 0, 1)) );
  }

  TEST_CASE("math/types/Ray3/operations", "")
  {
    typedef math_t::Ray3f32         ray_type;
    typedef ray_type::vec_type      vec_type;
    typedef ray_type::dir_vec_type  dir_vec_type;

    ray_type r1(ray_type::origin(vec_type(1, 2, 3)),
                ray_type::direction(dir_vec_type(0, 1, 0)) );
    ray_type r2(ray_type::origin(vec_type(4, 3, 2)),
                ray_type::direction(dir_vec_type(0, 2, 0)) );

    ray_type res = r1 + r2;
    CHECK( (res.GetOrigin() == vec_type(5, 5, 5)) );
    CHECK( (res.GetDirection() == vec_type(0, 1, 0)) );

    res = r1 - r2;
    CHECK( (res.GetOrigin() == vec_type(-3, -1, 1)) );
    CHECK( (res.GetDirection() == dir_vec_type(0, -1, 0)) );

    ray_type r3(ray_type::origin(vec_type(0, 0, 1)),
                ray_type::direction(dir_vec_type(0, 1, 0)) );

    math_t::Mat3f32 rot;
    rot.MakeRotation(math_t::Vec3f32(1, 0, 0), math_t::degree_f32(90.0f));
    math_cs::Transformf32  t;
    t.SetOrientation(rot);

    res = r3 * t.GetTransformation();

    CHECK( (res.GetOrigin() == vec_type(0, -1, 0)) );
    CHECK( (res.GetDirection() == vec_type(0, 0, 1)) );

    res = r3 * rot;

    CHECK( (res.GetOrigin() == vec_type(0, -1, 0)) );
    CHECK( (res.GetDirection() == vec_type(0, 0, 1)) );
  }
};