#include "tlocTestCommon.h"

#include <tlocMath/projection/tlocFrustum.h>

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
    using math_proj::frustum_persp;
    using namespace math_proj::p_frustum;

    using namespace tloc::math::types;
    using math::types::Degree;

    AspectRatio ar( AspectRatio::width(1024.0f), AspectRatio::height(768.0f) );
    FOV fov(Degree(60.0f), ar, p_FOV::vertical());

    frustum_persp::Params params(fov);
    params.SetFar(1000.0f).SetNear(5.0f);

    frustum_persp fr(params);
    fr.BuildFrustum();

    math::types::Mat4f projMat = fr.GetProjectionMatrix();

    CHECK_MATRIX4F(projMat, 1.2990381, 0, 0, 0,
                            0, 1.7320509, 0, 0,
                            0, 0, -1.0100503, -1,
                            0, 0, -10.050251, 0);

    frustum_persp::real_type tan30 = 0.57735026918962576451f;

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

  TEST_CASE("graphics/view_projection/Frustum<Orthographic>", "")
  {
    using math_proj::frustum_ortho;
    using namespace math_proj::p_frustum;

    typedef frustum_ortho::rect_type rect_type;
    rect_type rect(rect_type::left(-0.5f), rect_type::right(0.5f),
                   rect_type::top(0.5f), rect_type::bottom(-0.5f));

    frustum_ortho fr(rect, 1.0f, 10.0f);
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
};