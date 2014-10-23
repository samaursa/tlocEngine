#include "tlocTestCommon.h"

#include <tlocGraphics/opengl/tlocAttributeVBO.h>
#include <tlocGraphics/types/tlocVertex.h>
#include <tlocGraphics/window/tlocWindow.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.inl.h>
#include <tlocCore/smart_ptr/tlocVirtualStackObject.inl.h>

#if defined (TLOC_OS_WIN)
# define CHECK_ATTRIBUTE_VBO_VALUE(_attrib_vbo_, _array_, _value_) \
    _attrib_vbo_.GetValueAs(_array_); \
    CHECK(_array_.size() == 1); \

# define CHECK_ATTRIBUTE_VBO_VERT3FP(_attrib_vbo_, _array_, _vert_) \
    _attrib_vbo_.GetValueAs(_array_); \
    CHECK(_array_.size() == 1); \
    CHECK(_array_[0].GetPosition() == _vert_.GetPosition())

# define CHECK_ATTRIBUTE_VBO_VERT3FPC(_attrib_vbo_, _array_, _vert_) \
    _attrib_vbo_.GetValueAs(_array_); \
    CHECK(_array_.size() == 1); \
    CHECK(_array_[0].GetPosition() == _vert_.GetPosition()); \
    CHECK(_array_[0].GetColor() == _vert_.GetColor())

# define CHECK_ATTRIBUTE_VBO_VERT3FPT(_attrib_vbo_, _array_, _vert_) \
    _attrib_vbo_.GetValueAs(_array_); \
    CHECK(_array_.size() == 1); \
    CHECK(_array_[0].GetPosition() == _vert_.GetPosition()); \
    CHECK(_array_[0].GetTexCoord() == _vert_.GetTexCoord())

# define CHECK_ATTRIBUTE_VBO_VERT3FPN(_attrib_vbo_, _array_, _vert_) \
    _attrib_vbo_.GetValueAs(_array_); \
    CHECK(_array_.size() == 1); \
    CHECK(_array_[0].GetPosition() == _vert_.GetPosition()); \
    CHECK(_array_[0].GetNormal() == _vert_.GetNormal())

# define CHECK_ATTRIBUTE_VBO_VERT3FPNC(_attrib_vbo_, _array_, _vert_) \
    _attrib_vbo_.GetValueAs(_array_); \
    CHECK(_array_.size() == 1); \
    CHECK(_array_[0].GetPosition() == _vert_.GetPosition()); \
    CHECK(_array_[0].GetNormal() == _vert_.GetNormal()); \
    CHECK(_array_[0].GetColor() == _vert_.GetColor())

# define CHECK_ATTRIBUTE_VBO_VERT3FPNT(_attrib_vbo_, _array_, _vert_) \
    _attrib_vbo_.GetValueAs(_array_); \
    CHECK(_array_.size() == 1); \
    CHECK(_array_[0].GetPosition() == _vert_.GetPosition()); \
    CHECK(_array_[0].GetNormal() == _vert_.GetNormal()); \
    CHECK(_array_[0].GetTexCoord() == _vert_.GetTexCoord())

# define CHECK_ATTRIBUTE_VBO_VERT3FPNCT(_attrib_vbo_, _array_, _vert_) \
    _attrib_vbo_.GetValueAs(_array_); \
    CHECK(_array_.size() == 1); \
    CHECK(_array_[0].GetPosition() == _vert_.GetPosition()); \
    CHECK(_array_[0].GetNormal() == _vert_.GetNormal()); \
    CHECK(_array_[0].GetColor() == _vert_.GetColor()); \
    CHECK(_array_[0].GetTexCoord() == _vert_.GetTexCoord())

# define CHECK_ATTRIBUTE_VBO_MULTIPLE_VERT3FPNCT(_attrib_vbo_, _array_, _num_, _vert_) \
    _attrib_vbo_.GetValueAs(_array_); \
    CHECK(_array_.size() == _num_); \
    for (tl_int i = 0; i < _num_; ++i) \
    { \
      CHECK(_array_[i].GetPosition() == _vert_.GetPosition()); \
      CHECK(_array_[i].GetNormal() == _vert_.GetNormal()); \
      CHECK(_array_[i].GetColor() == _vert_.GetColor()); \
      CHECK(_array_[i].GetTexCoord() == _vert_.GetTexCoord()); \
    }

#elif defined (TLOC_OS_IPHONE)
# define CHECK_ATTRIBUTE_VBO_VALUE(_attrib_vbo_, _array_, _value_)
# define CHECK_ATTRIBUTE_VBO_VERT3FP(_attrib_vbo_, _array_, _vert_)
# define CHECK_ATTRIBUTE_VBO_VERT3FPC(_attrib_vbo_, _array_, _vert_)
# define CHECK_ATTRIBUTE_VBO_VERT3FPT(_attrib_vbo_, _array_, _vert_)
# define CHECK_ATTRIBUTE_VBO_VERT3FPN(_attrib_vbo_, _array_, _vert_)
# define CHECK_ATTRIBUTE_VBO_VERT3FPNC(_attrib_vbo_, _array_, _vert_)
# define CHECK_ATTRIBUTE_VBO_VERT3FPNT(_attrib_vbo_, _array_, _vert_)
# define CHECK_ATTRIBUTE_VBO_VERT3FPNCT(_attrib_vbo_, _array_, _vert_)
# define CHECK_ATTRIBUTE_VBO_MULTIPLE_VERT3FPNCT(_attrib_vbo_, _array_, _num_, _vert_)

#else
# error WIP
#endif

namespace TestingAttributeVariable
{
  using namespace tloc;
  using namespace graphics;
  using namespace core_ds;
  using namespace core_conts;
  using namespace math_t;
  using namespace gfx_win;
  using namespace gfx_t;

  TEST_CASE("Graphics/gl/Attribute/copy", "")
  {

    typedef win::Window::graphics_mode         graphics_mode;

    Window window;
    window.Create(graphics_mode(graphics_mode::Properties(1, 1)),
      WindowSettings("AttributeVBO Test"));

    REQUIRE(gl::InitializePlatform() == ErrorSuccess);

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");
      Array<f32> array(1, 1.0f);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VALUE(a, array, Approx(1.0f));
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");
      Array<Vec2f32> array(1, Vec2f32(1.0f, 2.0f));
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VALUE(a, array, Vec2f32(1.0f, 2.0f));
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");
      Array<Vec3f32> array(1, Vec3f32(1.0f, 2.0f, 3.0f));
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VALUE(a, array, Vec3f32(1.0, 2.0f, 3.0f));
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");
      Array<Vec4f32> array(1, Vec4f32(1.0f, 2.0f, 3.0f, 4.0f));
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VALUE(a, array, Vec4f32(1.0, 2.0f, 3.0f, 4.0f));
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert3fp v; 
      v.SetPosition(Vec3f32(0.0f, 1.0f, 2.0f));

      Array<Vert3fp> array(1, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VERT3FP(a, array, v);
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert3fpc v; 
      v.SetPosition(Vec3f32(0.0f, 1.0f, 2.0f));
      v.SetColor(gfx_t::Color::COLOR_RED);

      Array<Vert3fpc> array(1, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VERT3FPC(a, array, v);
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert3fpt v; 
      v.SetPosition(Vec3f32(0.0f, 1.0f, 2.0f));
      v.SetTexCoord(Vec2f32(0.0f, 1.0f));

      Array<Vert3fpt> array(1, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VERT3FPT(a, array, v);
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert3fpn v; 
      v.SetPosition(Vec3f32(0.0f, 1.0f, 2.0f));
      v.SetNormal(Vec3f32::UNIT_X);

      Array<Vert3fpn> array(1, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VERT3FPN(a, array, v);
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert3fpnc v; 
      v.SetPosition(Vec3f32(0.0f, 1.0f, 2.0f));
      v.SetColor(gfx_t::Color::COLOR_RED);
      v.SetNormal(Vec3f32::UNIT_X);

      Array<Vert3fpnc> array(1, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VERT3FPNC(a, array, v);
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert3fpnt v; 
      v.SetPosition(Vec3f32(0.0f, 1.0f, 2.0f));
      v.SetTexCoord(Vec2f32(0.0f, 1.0f));
      v.SetNormal(Vec3f32::UNIT_X);

      Array<Vert3fpnt> array(1, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VERT3FPNT(a, array, v);
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert3fpnct v; 
      v.SetPosition(Vec3f32(0.0f, 1.0f, 2.0f));
      v.SetTexCoord(Vec2f32(0.0f, 1.0f));
      v.SetNormal(Vec3f32::UNIT_X);
      v.SetColor(gfx_t::Color::COLOR_RED);

      Array<Vert3fpnct> array(1, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VERT3FPNCT(a, array, v);
    }

    SECTION("Arrays with more than 1 value", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert3fpnct v; 
      v.SetPosition(Vec3f32(0.0f, 1.0f, 2.0f));
      v.SetTexCoord(Vec2f32(0.0f, 1.0f));
      v.SetNormal(Vec3f32::UNIT_X);
      v.SetColor(gfx_t::Color::COLOR_RED);

      Array<Vert3fpnct> array(3, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_MULTIPLE_VERT3FPNCT(a, array, 3, v);
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert2fpc v; 
      v.SetPosition(Vec2f32(0.0f, 1.0f));
      v.SetColor(gfx_t::Color::COLOR_RED);

      Array<Vert2fpc> array(1, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VERT3FPC(a, array, v);
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert2fpt v; 
      v.SetPosition(Vec2f32(0.0f, 1.0f));
      v.SetTexCoord(Vec2f32(0.0f, 1.0f));

      Array<Vert2fpt> array(1, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VERT3FPT(a, array, v);
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert2fpn v; 
      v.SetPosition(Vec2f32(0.0f, 1.0f));
      v.SetNormal(Vec3f32::UNIT_X);

      Array<Vert2fpn> array(1, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VERT3FPN(a, array, v);
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert2fpnc v; 
      v.SetPosition(Vec2f32(0.0f, 1.0f));
      v.SetColor(gfx_t::Color::COLOR_RED);
      v.SetNormal(Vec3f32::UNIT_X);

      Array<Vert2fpnc> array(1, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VERT3FPNC(a, array, v);
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert2fpnt v; 
      v.SetPosition(Vec2f32(0.0f, 1.0f));
      v.SetTexCoord(Vec2f32(0.0f, 1.0f));
      v.SetNormal(Vec3f32::UNIT_X);

      Array<Vert2fpnt> array(1, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VERT3FPNT(a, array, v);
    }

    SECTION("Arrays", "")
    {
      gl::AttributeVBO a;
      a.AddName("TestVarArray");

      Vert2fpnct v; 
      v.SetPosition(Vec2f32(0.0f, 1.0f));
      v.SetTexCoord(Vec2f32(0.0f, 1.0f));
      v.SetNormal(Vec3f32::UNIT_X);
      v.SetColor(gfx_t::Color::COLOR_RED);

      Array<Vert2fpnct> array(1, v);
      a.SetValueAs<gl::p_vbo::target::ArrayBuffer, 
                   gl::p_vbo::usage::StaticDraw>(array);

      array.clear();
      CHECK_ATTRIBUTE_VBO_VERT3FPNCT(a, array, v);
    }
  }
};