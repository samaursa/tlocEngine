#include "tlocTestCommon.h"

#include <tlocGraphics/view_projection/tlocFrustum.h>

namespace TestingFrustum
{
  using namespace tloc;
  using namespace tloc::graphics;

  TEST_CASE("graphics/view_projection/Frustum", "")
  {
    using namespace tloc::graphics::types;

    AspectRatio ar( AspectRatio::width(1024.0f), AspectRatio::height(768.0f) );
    FOV fov(math::Degree(60.0f), ar, p_FOV::vertical());

    view_proj::Frustum::Params params(fov);
    params.SetFar(1000.0f);
    params.SetNear(5.0f);

    view_proj::Frustum fr(params);
    //fr.BuildFrustum();

    //math::Mat4f projMat = fr.GetProjectionMatrix();
  }
};