#include "tlocTestCommon.h"

#include <tlocMath/types/tlocPlane.h>
#include <tlocMath/component_system/tlocTransform.h>

namespace TestingRay
{
  using namespace tloc;
  using namespace math;
  using namespace math_t;

  template <typename T>
  void TestPlane()
  {
    typedef Plane_T<T>                          plane_type;
    typedef typename plane_type::vec_type       vec_type;
    typedef typename plane_type::ray_type       ray_type;

    vec_type planeOrigin = vec_type::ZERO;
    vec_type planeDir = vec_type(0, 1, 0);
    vec_type rayOrigin = vec_type(0, 2, 0);
    vec_type rayDir = vec_type(1, 0, 0) - rayOrigin;
    rayDir.Normalize();

    // the ray will intersect the plane at 1, 0, 0

    auto r = ray_type(ray_type::origin(rayOrigin), ray_type::direction(rayDir));

    auto p = plane_type(plane_type::origin(planeOrigin),
                        plane_type::direction(planeDir));

    REQUIRE_FALSE(p.GetIsParallel(r));
    auto intersectPoint = p.GetIntersect(r);

    CHECK(intersectPoint == vec_type(1, 0, 0));
  }

  TEST_CASE("math/types/Plane", "")
  {
    TestPlane<f32>();
    TestPlane<f64>();
  }

  TEST_CASE("math/types/Plane/operations", "")
  {
    typedef math_t::Plane             plane_type;
    typedef plane_type::vec_type      vec_type;

    auto p1 = plane_type( plane_type::origin(vec_type(1, 2, 3)), 
                          plane_type::direction(vec_type(0, 1, 0)) );
    auto p2 = plane_type( plane_type::origin(vec_type(4, 5, 6)), 
                          plane_type::direction(vec_type(0, 0, 1)) );

    SECTION("Addition", "")
    {
      auto newDir = vec_type(0, 1, 0) + vec_type(0, 0, 1);
      newDir.Normalize();

      auto res = p1 + p2;
      CHECK( (res.GetOrigin() == vec_type(5, 7, 9)) );
      CHECK( (res.GetDirection() == newDir) );

      res = res - p2;
      // the direction will not be the same due to normalization
      CHECK(res.GetOrigin() == p1.GetOrigin());
    }

    SECTION("Transformation", "")
    {
      auto mat = Mat4f32::IDENTITY;
      auto res = p1 * mat;
      CHECK(res == p1);

      mat.SetCol(3, Vec4f(5, 0, 0, 1));
      res = p1 * mat;
      CHECK(res.GetOrigin() == vec_type(6, 2, 3));

      auto rotMat = Mat3f32::IDENTITY;
      rotMat.MakeRotationY(Degree(90.0f));
      res = p1 * rotMat;
      CHECK(res == p1);

      rotMat.MakeRotationX(Degree(90.0f));
      res = p1 * rotMat;
      CHECK(res.GetDirection() == vec_type(0, 0, 1));
      CHECK(res.GetOrigin() == p1.GetOrigin());
    }
  }
};