#include "tlocTestCommon.h"

#include <tlocGraphics/opengl/tlocAttributeVBO.h>
#include <tlocGraphics/types/tlocVertex.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>

namespace TestingAttributeVariable
{
  using namespace tloc;
  using namespace tloc::graphics;

  TEST_CASE("Graphics/gl/Attribute/copy", "")
  {
    using namespace tloc::core_ds;
    using namespace tloc::core_conts;
    using namespace tloc::math_t;

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");
      Array<f32> array(1, 1.0f);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      gl::AttributeVBO aCopy(a);
      CHECK( aCopy.GetType() == a.GetType() );
      CHECK( (aCopy.GetName().compare(a.GetName()) == 0) );
      CHECK( (aCopy.GetVBO().GetHandle() == a.GetVBO().GetHandle()) );
    }
  }
};