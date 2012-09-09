#include "tlocTestCommon.h"

#include <tlocGraphics/opengl/tlocObject.h>

namespace TestingGLShaderObject
{
  using namespace tloc::graphics;

  TEST_CASE("Graphics/ShaderComponent", "")
  {
    gl::Object obj;
    obj.GetHandle() = 9;
    CHECK(obj.GetHandle() == 9);
  }
};