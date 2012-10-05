#include "tlocTestCommon.h"

#include <tlocGraphics/opengl/tlocObject.h>

namespace TestingGLShaderObject
{
  using namespace tloc::graphics;

  TEST_CASE("Graphics/gl/Object", "")
  {
    gl::Object obj;
    obj.SetHandle(9);
    CHECK(obj.GetHandle() == 9);
  }
};