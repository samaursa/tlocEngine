#include "tlocTestCommon.h"

#include <tlocGraphics/opengl/tlocObject.h>

#include <tlocCore/tlocAlgorithms.h>
#include <tlocCore/tlocAlgorithms.inl.h>

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
      CHECK(obj.use_count() == 0);

      {
        glObject temp = obj;
        CHECK(obj.use_count() == 1);
        CHECK(temp.GetHandle() == 9);
        CHECK(glObject::m_destroyCount == 0);
      }

      CHECK(glObject::m_destroyCount == 0);
    }

    CHECK(glObject::m_destroyCount == 1);
  }

  TEST_CASE("Graphics/gl/Object/algorithms", "")
  {
    glObject objects[10];
    glObject* itr = objects;
    glObject* itrEnd = objects + 10;

    for (tl_int i = 0; i < 10; ++i)
    {
      objects[i].SetHandle(i);
    }

    glObject* res = core::find_if(itr, itrEnd, gl::algos::find::object::ByHandle(5));
    CHECK(res != itrEnd);
    CHECK(res->GetHandle() == 5);

    res = core::find_if(itr, itrEnd, gl::algos::find::object::ByHandle(10));
    CHECK(res == itrEnd);
  }
};