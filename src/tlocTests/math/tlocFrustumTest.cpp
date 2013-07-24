#include "tlocTestCommon.h"

#include <tlocMath/projection/tlocFrustum.h>
#include <tlocMath/utilities/tlocScale.h>

namespace TestingFrustum
{
  using namespace tloc;

#define CHECK_MATRIX4F(mat,x1,y1,z1,w1,x2,y2,z2,w2,x3,y3,z3,w3,x4,y4,z4,w4) \
  CHECK((mat[0]) == Approx(x1)); CHECK((mat[1]) == Approx(y1));\
  CHECK((mat[2]) == Approx(z1)); CHECK((mat[3]) == Approx(w1));\
\
  CHECK((mat[4]) == Approx(x2)); CHECK((mat[5]) == Approx(y2));\
  CHECK((mat[6]) == Approx(z2)); CHECK((mat[7]) == Approx(w2));\
\
  CHECK((mat[8]) == Approx(x3)); CHECK((mat[9]) == Approx(y3));\
  CHECK((mat[10]) == Approx(z3)); CHECK((mat[11]) == Approx(w3));\
\
  CHECK((mat[12]) == Approx(x4)); CHECK((mat[13]) == Approx(y4));\
  CHECK((mat[14]) == Approx(z4)); CHECK((mat[15]) == Approx(w4))

  TEST_CASE("graphics/view_projection/Frustum<Perspective>", "")
  {
    using math_proj::FrustumPersp;
    using namespace math_proj::p_frustum;

    using namespace tloc::math::types;
    using math::types::Degree;

    AspectRatio ar( AspectRatio::width(1024.0f), AspectRatio::height(768.0f) );
    FOV fov(Degree(60.0f), ar, p_FOV::vertical());

    FrustumPersp::Params params(fov);
    params.SetFar(1000.0f).SetNear(5.0f);

    FrustumPersp fr(params);
    fr.BuildFrustum();

    math::types::Mat4f projMat = fr.GetProjectionMatrix();

    CHECK_MATRIX4F(projMat, 1.2990381, 0, 0, 0,
                            0, 1.7320509, 0, 0,
                            0, 0, -1.0100503, -1,
                            0, 0, -10.050251, 0);

    FrustumPersp::real_type tan30 = 0.57735026918962576451f;

    CHECK(fr.GetPlane<Near>()   == Approx(5.0f));
    CHECK(fr.GetPlane<Far>()    == Approx(1000.0f));
    CHECK(fr.GetPlane<Top>()    == Approx(tan30 * 5.0f));
    CHECK(fr.GetPlane<Bottom>() == Approx(-tan30 * 5.0f));
    CHECK(fr.GetPlane<Left>()   == Approx(-tan30 * 5.0f * 1024.0f / 768.0f));
    CHECK(fr.GetPlane<Right>()  == Approx(tan30 * 5.0f * 1024.0f / 768.0f));

    math::proj::Frustum frBase(fr);

    CHECK(frBase.GetPlane<Near>()   == Approx(5.0f));
    CHECK(frBase.GetPlane<Far>()    == Approx(1000.0f));
    CHECK(frBase.GetPlane<Top>()    == Approx(tan30 * 5.0f));
    CHECK(frBase.GetPlane<Bottom>() == Approx(-tan30 * 5.0f));
    CHECK(frBase.GetPlane<Left>()   == Approx(-tan30 * 5.0f * 1024.0f / 768.0f));
    CHECK(frBase.GetPlane<Right>()  == Approx(tan30 * 5.0f * 1024.0f / 768.0f));
  }

  TEST_CASE("graphics/view_projection/Frustum<Perspective>/GetRay", "")
  {
    using math_proj::FrustumPersp;
    using namespace math_proj::p_frustum;

    using namespace tloc::math::types;
    using math::types::Degree;

    AspectRatio ar( AspectRatio::width(1024.0f), AspectRatio::height(768.0f) );
    FOV fov(Degree(60.0f), ar, p_FOV::vertical());

    FrustumPersp::Params params(fov);
    params.SetFar(1000.0f).SetNear(5.0f);

    FrustumPersp fr(params);
    fr.BuildFrustum();

    math_utils::scale_tl_float::range_small smallR =
      math::MakeRangef<tl_float, math::p_range::Inclusive>().Get(-1.0f, 1.0f);
    math_utils::scale_tl_float::range_large largeRX =
      math::MakeRangef<tl_float, math::p_range::Inclusive>().Get(0.0f, 1024.0f);
    math_utils::scale_tl_float::range_large largeRY =
      math::MakeRangef<tl_float, math::p_range::Inclusive>().Get(0.0f, 768.0f);
    math_utils::scale_tl_float scx(smallR, largeRX);
    math_utils::scale_tl_float scy(smallR, largeRY);

    {
      math_t::Vec3f xyz(scx.ScaleDown(0.0f), scy.ScaleDown(0.0f), -1.0f);

      math_t::Ray3f ray = fr.GetRay(xyz);

      // at x,y,z=0,0,-1 the origin should be:
      // x = tan(fov_horizontal/2)*base
      // y = tan(fov_vertical/2)*base
      // z = -5.0f (which is the near plane)

      tl_float horFov = fov.Get<p_FOV::horizontal>().Get();
      tl_float verFov = fov.Get<p_FOV::vertical>().Get();

      CHECK(ray.GetOrigin()[0] == Approx( tan( horFov / 2.0f ) * -5.0f ) );
      CHECK(ray.GetOrigin()[1] == Approx( tan( verFov / 2.0f ) * -5.0f ) );
      CHECK(ray.GetOrigin()[2] == Approx( -5.0f ) );
    }

    {
      math_t::Vec3f xyz(scx.ScaleDown(1024.0f), scy.ScaleDown(768.0f), -1.0f);

      math_t::Ray3f ray = fr.GetRay(xyz);

      // at x,y,z=0,0,-1 the origin should be:
      // x = tan(fov_horizontal/2)*base
      // y = tan(fov_vertical/2)*base
      // z = -5.0f (which is the near plane)

      tl_float horFov = fov.Get<p_FOV::horizontal>().Get();
      tl_float verFov = fov.Get<p_FOV::vertical>().Get();

      CHECK(ray.GetOrigin()[0] == Approx( -tan( horFov / 2.0f ) * -5.0f ) );
      CHECK(ray.GetOrigin()[1] == Approx( -tan( verFov / 2.0f ) * -5.0f ) );
      CHECK(ray.GetOrigin()[2] == Approx( -5.0f ) );
    }
  }

  TEST_CASE("graphics/view_projection/Frustum<Orthographic>", "")
  {
    using math_proj::FrustumOrtho;
    using namespace math_proj::p_frustum;

    typedef FrustumOrtho::rect_type rect_type;
    rect_type rect(rect_type::left(-0.5f), rect_type::right(0.5f),
      rect_type::top(0.5f), rect_type::bottom(-0.5f));

    FrustumOrtho fr(rect, 1.0f, 10.0f);
    fr.BuildFrustum();

    math::types::Mat4f projMat = fr.GetProjectionMatrix();

    CHECK_MATRIX4F(projMat, 2.00f, 0.00f,  0.00f       ,  0.00f,
                            0.00f, 2.00f,  0.00f       ,  0.00f,
                            0.00f, 0.00f, -2.0f  / 9.0f,  0.00f,
                            0.00f, 0.00f, -11.0f / 9.0f,  1.00f);

    CHECK(fr.GetPlane<Near>()   == Approx( 1.0f));
    CHECK(fr.GetPlane<Far>()    == Approx( 10.0f));
    CHECK(fr.GetPlane<Top>()    == Approx( 0.5f));
    CHECK(fr.GetPlane<Bottom>() == Approx(-0.5f));
    CHECK(fr.GetPlane<Left>()   == Approx(-0.5f));
    CHECK(fr.GetPlane<Right>()  == Approx( 0.5f));

    math::proj::Frustum frBase(fr);

    CHECK(frBase.GetPlane<Near>()   == Approx( 1.0f));
    CHECK(frBase.GetPlane<Far>()    == Approx( 10.0f));
    CHECK(frBase.GetPlane<Top>()    == Approx( 0.5f));
    CHECK(frBase.GetPlane<Bottom>() == Approx(-0.5f));
    CHECK(frBase.GetPlane<Left>()   == Approx(-0.5f));
    CHECK(frBase.GetPlane<Right>()  == Approx( 0.5f));
  }

  TEST_CASE("graphics/view_projection/Frustum<Orthographic>/GetRay", "")
  {
    // NOTE: We made this test by comparing values to Unity which is why
    // 'right' is 8/3 (or 2.666666666...). If these tests fail, we need to get
    // better values from Unity.

    using math_proj::FrustumOrtho;
    using namespace math_proj::p_frustum;

    typedef FrustumOrtho::rect_type rect_type;
    // Unity Project is Orthographic and size is 1. Unity assumes size to be
    // Top. Left and right are then scaled to match the aspect ratio of the
    // screen (which is 1.33333... for 1024x768)
    rect_type rect(rect_type::left(-4.0f/3.0f), rect_type::right(4.0f/3.0f),
                   rect_type::top(1.0f), rect_type::bottom(-1.0f));

    FrustumOrtho fr(rect, 0.1f, 10.0f);
    fr.BuildFrustum();

    math::types::Mat4f projMat = fr.GetProjectionMatrix();

    CHECK_MATRIX4F(projMat, 0.75f, 0.00f,  0.00f       ,  0.00f,
      0.00f, 1.00f,  0.00f       ,  0.00f,
      0.00f, 0.00f,  -0.20202f   ,  0.00f,
      0.00f, 0.00f,  -1.02020f   ,  1.00f);

    CHECK(fr.GetPlane<Near>()   == Approx( 0.1f));
    CHECK(fr.GetPlane<Far>()    == Approx( 10.0f));
    CHECK(fr.GetPlane<Top>()    == Approx(  1.0f));
    CHECK(fr.GetPlane<Bottom>() == Approx( -1.0f));
    CHECK(fr.GetPlane<Left>()   == Approx( -4.0f/3.0f));
    CHECK(fr.GetPlane<Right>()  == Approx(  4.0f/3.0f));

    using math_utils::scale_f32_f32;
    typedef math_utils::scale_f32_f32::range_small range_small;
    typedef math_utils::scale_f32_f32::range_large range_large;

    range_small smallR(-1.0f, 1.05f, range_small::step_size(0.1f));
    //math_utils::scale_f32_f32::range_large largeRX(0.0f, 1024.05f, math_utils::scale_f32_f32::range_large::step_size(0.1f));
    range_large largeRX(0.0f, 1024.05f, range_large::step_size(0.1f));
    range_large largeRY(0.0f, 768.05f, range_large::step_size(0.1f));
    scale_f32_f32 scx(smallR, largeRX);
    scale_f32_f32 scy(smallR, largeRY);

    {
      math_t::Vec3f xyz(scx.ScaleDown(0.0f), scy.ScaleDown(0.0f), -1.0f);
      math_t::Ray3f ray = fr.GetRay(xyz);

      CHECK(ray.GetOrigin()[0] == Approx(-4.0f/3.0f));
      CHECK(ray.GetOrigin()[1] == Approx(-1.0f));
      CHECK(ray.GetOrigin()[2] == Approx(-0.1f));
    }

    {
      math_t::Vec3f xyz(scx.ScaleDown(1024.0f), scy.ScaleDown(768.0f), -1.0f);
      math_t::Ray3f ray = fr.GetRay(xyz);

      CHECK(ray.GetOrigin()[0] == Approx(4.0f/3.0f));
      CHECK(ray.GetOrigin()[1] == Approx(1.0f));
      CHECK(ray.GetOrigin()[2] == Approx(-0.1f));
    }
  }
};