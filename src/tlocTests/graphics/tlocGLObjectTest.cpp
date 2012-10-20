#include "tlocTestCommon.h"

#include <tlocGraphics/opengl/tlocObject.h>

namespace TestingGLShaderObject
{
  using namespace tloc;
  using namespace tloc::graphics;

  class glObject : public gl::Object_T<glObject>
  {
  public:
    ~glObject()
    {
      if (IsLastRef())
      {
        ++m_destroyCount;
      }
    }

    static tl_size m_destroyCount;
  };

  tl_size glObject::m_destroyCount;

  TEST_CASE("Graphics/gl/Object", "")
  {
    {
      glObject obj;
      obj.SetHandle(9);
      CHECK(obj.GetHandle() == 9);
      CHECK(obj.GetRefCount() == 0);

      {
        glObject temp = obj;
        CHECK(obj.GetRefCount() == 1);
        CHECK(glObject::m_destroyCount == 0);
      }

      CHECK(glObject::m_destroyCount == 0);
    }

    CHECK(glObject::m_destroyCount == 1);
  }
};