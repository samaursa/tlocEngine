#include "tlocTestCommon.h"

#include <tlocMath/types/tlocVector4.h>
#include <tlocGraphics/types/tlocColor.h>

namespace TestingColor
{
  using namespace tloc;
  using namespace tloc::graphics::types;

#define CHECK_COLOR_4(_tuple4_, _r_, _g_, _b_, _a_)\
    CHECK(_tuple4_.Get()[0] == _r_);\
    CHECK(_tuple4_.Get()[1] == _g_);\
    CHECK(_tuple4_.Get()[2] == _b_);\
    CHECK(_tuple4_.Get()[3] == _a_)


  TEST_CASE("Graphics/types/Color", "")
  {
    SECTION("u8 color", "")
    {
      Color c = Color(0.5f, 0.5f, 0.5f, 1.0f);
      CHECK(c[0] == 127);
      CHECK(c[1] == 127);
      CHECK(c[2] == 127);
      CHECK(c[3] == 255);

      c = Color(25, 35, 45, 55);
      CHECK(c[0] == 25);
      CHECK(c[1] == 35);
      CHECK(c[2] == 45);
      CHECK(c[3] == 55);

      Color::int_type colorInInt = c.GetAs<p_color::format::RGBA>();
      CHECK(colorInInt == 0x19232D37);

      colorInInt = c.GetAs<p_color::format::ABGR>();
      CHECK(colorInInt == 0x372D2319);

      colorInInt = c.GetAs<p_color::format::ARGB>();
      CHECK(colorInInt == 0x3719232D);

      colorInInt = c.GetAs<p_color::format::BGRA>();
      CHECK(colorInInt == 0x2D231937);

      Color d;
      CHECK(d[0] == 0);
      CHECK(d[1] == 0);
      CHECK(d[2] == 0);
      CHECK(d[3] == 0);

      d = c;
      CHECK(d[0] == 25);
      CHECK(d[1] == 35);
      CHECK(d[2] == 45);
      CHECK(d[3] == 55);

      Color e(d);
      CHECK(e[0] == 25);
      CHECK(e[1] == 35);
      CHECK(e[2] == 45);
      CHECK(e[3] == 55);

      Color f = e + d;
      CHECK(f[0] == 50);
      CHECK(f[1] == 70);
      CHECK(f[2] == 90);
      CHECK(f[3] == 110);

      f += e;
      CHECK(f[0] == 75);
      CHECK(f[1] == 105);
      CHECK(f[2] == 135);
      CHECK(f[3] == 165);

      f = e * e;
      // Note: The following calculations will overflow and wrap around
      CHECK(f[0] == (Color::value_type)(e[0] * e[0]) );
      CHECK(f[1] == (Color::value_type)(e[1] * e[1]) );
      CHECK(f[2] == (Color::value_type)(e[2] * e[2]) );
      CHECK(f[3] == (Color::value_type)(e[3] * e[3]) );

      f = e;
      f *= e;
      CHECK(f[0] == (Color::value_type)(e[0] * e[0]) );
      CHECK(f[1] == (Color::value_type)(e[1] * e[1]) );
      CHECK(f[2] == (Color::value_type)(e[2] * e[2]) );
      CHECK(f[3] == (Color::value_type)(e[3] * e[3]) );

      f = e - e;
      CHECK(f[0] == 0);
      CHECK(f[1] == 0);
      CHECK(f[2] == 0);
      CHECK(f[3] == 0);

      f = e;
      f -= e;
      CHECK(f[0] == 0);
      CHECK(f[1] == 0);
      CHECK(f[2] == 0);
      CHECK(f[3] == 0);

      CHECK(f != e);
      CHECK(e != f);
      f = e;
      CHECK(f == e);
      CHECK(e == f);
    }

    SECTION("float color4", "")
    {
      color_f32_rgba c(0.25f, 0.35f, 0.45f, 0.55f);
      CHECK(c[0] == Approx(0.25));
      CHECK(c[1] == Approx(0.35));
      CHECK(c[2] == Approx(0.45));
      CHECK(c[3] == Approx(0.55));

      c = color_f32_rgba(25, 35, 45, 55);
      CHECK(c[0] == Approx(25.0f/255.0f));
      CHECK(c[1] == Approx(35.0f/255.0f));
      CHECK(c[2] == Approx(45.0f/255.0f));
      CHECK(c[3] == Approx(55.0f/255.0f));

      Color::int_type colorInInt = c.GetAs<p_color::format::RGBA>();
      CHECK(colorInInt == 0x19232D37);

      colorInInt = c.GetAs<p_color::format::ABGR>();
      CHECK(colorInInt == 0x372D2319);

      colorInInt = c.GetAs<p_color::format::ARGB>();
      CHECK(colorInInt == 0x3719232D);

      colorInInt = c.GetAs<p_color::format::BGRA>();
      CHECK(colorInInt == 0x2D231937);

      color_f32_rgba d;
      CHECK(d[0] == 0);
      CHECK(d[1] == 0);
      CHECK(d[2] == 0);
      CHECK(d[3] == 0);

      d = c;
      CHECK(d[0] == Approx(25.0f/255.0f));
      CHECK(d[1] == Approx(35.0f/255.0f));
      CHECK(d[2] == Approx(45.0f/255.0f));
      CHECK(d[3] == Approx(55.0f/255.0f));

      color_f32_rgba e(d);
      CHECK(e[0] == Approx(25.0f/255.0f));
      CHECK(e[1] == Approx(35.0f/255.0f));
      CHECK(e[2] == Approx(45.0f/255.0f));
      CHECK(e[3] == Approx(55.0f/255.0f));

      color_f32_rgba f = e + d;
      CHECK(f[0] == Approx(50.0f/255.0f));
      CHECK(f[1] == Approx(70.0f/255.0f));
      CHECK(f[2] == Approx(90.0f/255.0f));
      CHECK(f[3] == Approx(110.0f/255.0f));

      //f += e;
      //CHECK(f[0] == 75);
      //CHECK(f[1] == 105);
      //CHECK(f[2] == 135);
      //CHECK(f[3] == 165);

      //f = e * e;
      //// Note: The following calculations will overflow and wrap around
      //CHECK(f[0] == (Color::value_type)(e[0] * e[0]) );
      //CHECK(f[1] == (Color::value_type)(e[1] * e[1]) );
      //CHECK(f[2] == (Color::value_type)(e[2] * e[2]) );
      //CHECK(f[3] == (Color::value_type)(e[3] * e[3]) );

      //f = e;
      //f *= e;
      //CHECK(f[0] == (Color::value_type)(e[0] * e[0]) );
      //CHECK(f[1] == (Color::value_type)(e[1] * e[1]) );
      //CHECK(f[2] == (Color::value_type)(e[2] * e[2]) );
      //CHECK(f[3] == (Color::value_type)(e[3] * e[3]) );

      //f = e - e;
      //CHECK(f[0] == 0);
      //CHECK(f[1] == 0);
      //CHECK(f[2] == 0);
      //CHECK(f[3] == 0);

      //f = e;
      //f -= e;
      //CHECK(f[0] == 0);
      //CHECK(f[1] == 0);
      //CHECK(f[2] == 0);
      //CHECK(f[3] == 0);

      //CHECK(f != e);
      //CHECK(e != f);
      //f = e;
      //CHECK(f == e);
      //CHECK(e == f);
    }

    SECTION("float color3", "")
    {
      color_f32_rgb c(0.25f, 0.35f, 0.45f);
      CHECK(c[0] == Approx(0.25));
      CHECK(c[1] == Approx(0.35));
      CHECK(c[2] == Approx(0.45));

      c = color_f32_rgb(25, 35, 45);
      CHECK(c[0] == Approx(25.0f/255.0f));
      CHECK(c[1] == Approx(35.0f/255.0f));
      CHECK(c[2] == Approx(45.0f/255.0f));

      color_f32_rgb d;
      CHECK(d[0] == 0);
      CHECK(d[1] == 0);
      CHECK(d[2] == 0);

      d = c;
      CHECK(d[0] == Approx(25.0f/255.0f));
      CHECK(d[1] == Approx(35.0f/255.0f));
      CHECK(d[2] == Approx(45.0f/255.0f));

      color_f32_rgb e(d);
      CHECK(e[0] == Approx(25.0f/255.0f));
      CHECK(e[1] == Approx(35.0f/255.0f));
      CHECK(e[2] == Approx(45.0f/255.0f));

      color_f32_rgb f = e + d;
      CHECK(f[0] == Approx(50.0f/255.0f));
      CHECK(f[1] == Approx(70.0f/255.0f));
      CHECK(f[2] == Approx(90.0f/255.0f));
    }

    SECTION("float color2", "")
    {
      color_f32_rg c(0.25f, 0.35f);
      CHECK(c[0] == Approx(0.25));
      CHECK(c[1] == Approx(0.35));

      c = color_f32_rg(25, 35);
      CHECK(c[0] == Approx(25.0f/255.0f));
      CHECK(c[1] == Approx(35.0f/255.0f));

      color_f32_rg d;
      CHECK(d[0] == 0);
      CHECK(d[1] == 0);

      d = c;
      CHECK(d[0] == Approx(25.0f/255.0f));
      CHECK(d[1] == Approx(35.0f/255.0f));

      color_f32_rg e(d);
      CHECK(e[0] == Approx(25.0f/255.0f));
      CHECK(e[1] == Approx(35.0f/255.0f));

      color_f32_rg f = e + d;
      CHECK(f[0] == Approx(50.0f/255.0f));
      CHECK(f[1] == Approx(70.0f/255.0f));
    }

    SECTION("float color1", "")
    {
      color_f32_r c(0.25f);
      CHECK(c[0] == Approx(0.25));

      c = color_f32_r(25);
      CHECK(c[0] == Approx(25.0f/255.0f));

      color_f32_r d;
      CHECK(d[0] == 0);

      d = c;
      CHECK(d[0] == Approx(25.0f/255.0f));

      color_f32_r e(d);
      CHECK(e[0] == Approx(25.0f/255.0f));

      color_f32_r f = e + d;
      CHECK(f[0] == Approx(50.0f/255.0f));
    }
  }

  TEST_CASE("Graphics/types/Color/Get and GetAs", "")
  {
    Color c(25, 35, 45, 55);
    CHECK_COLOR_4(c, 25, 35, 45, 55);

    math::types::Vec4f cVec;

    c.GetAs<p_color::format::RGBA>(cVec);
    CHECK_COLOR_4(c, 25, 35, 45, 55);
    CHECK(cVec[0] == Approx(0.09803921568627450980392156862745f));
    CHECK(cVec[1] == Approx(0.13725490196078431372549019607843));
    CHECK(cVec[2] == Approx(0.17647058823529411764705882352941));
    CHECK(cVec[3] == Approx(0.21568627450980392156862745098039));

    c.GetAs<p_color::format::ABGR>(cVec);
    CHECK_COLOR_4(c, 25, 35, 45, 55);
    CHECK(cVec[0] == Approx(0.21568627450980392156862745098039));
    CHECK(cVec[1] == Approx(0.17647058823529411764705882352941));
    CHECK(cVec[2] == Approx(0.13725490196078431372549019607843));
    CHECK(cVec[3] == Approx(0.09803921568627450980392156862745f));

    c.GetAs<p_color::format::ARGB>(cVec);
    CHECK_COLOR_4(c, 25, 35, 45, 55);
    CHECK(cVec[0] == Approx(0.21568627450980392156862745098039));
    CHECK(cVec[1] == Approx(0.09803921568627450980392156862745f));
    CHECK(cVec[2] == Approx(0.13725490196078431372549019607843));
    CHECK(cVec[3] == Approx(0.17647058823529411764705882352941));

    c.GetAs<p_color::format::BGRA>(cVec);
    CHECK_COLOR_4(c, 25, 35, 45, 55);
    CHECK(cVec[0] == Approx(0.17647058823529411764705882352941));
    CHECK(cVec[1] == Approx(0.13725490196078431372549019607843));
    CHECK(cVec[2] == Approx(0.09803921568627450980392156862745f));
    CHECK(cVec[3] == Approx(0.21568627450980392156862745098039));

    cVec = c.GetAs<p_color::format::BGRA, math_t::Vec4f>();
    CHECK(cVec[0] == Approx(0.17647058823529411764705882352941));
    CHECK(cVec[1] == Approx(0.13725490196078431372549019607843));
    CHECK(cVec[2] == Approx(0.09803921568627450980392156862745f));
    CHECK(cVec[3] == Approx(0.21568627450980392156862745098039));

  }

  TEST_CASE("Graphics/types/Color/SetAs", "")
  {
    Color c(25, 35, 45, 55);
    CHECK_COLOR_4(c, 25, 35, 45, 55);

    c.SetAs(0, 0, 1, 255);
    CHECK_COLOR_4(c, 0, 0, 1, 255);
    c.SetAs(0.5f, 0.5f, 0.5f, 0.5f);
    CHECK_COLOR_4(c, 127, 127, 127, 127);
  }

  TEST_CASE("Graphics/types/Color/operatos", "")
  {
    SECTION("Multiplication and division with scalars", "")
    {
      SECTION("Multiplication", "")
      {
        Color c(255, 255, 255, 255);
        c = c * 0.5f;
        CHECK_COLOR_4(c, 127, 127, 127, 127);

        Color c2(1, 2, 3, 4);
        c2 *= 1.0f;
        CHECK_COLOR_4(c2, 1, 2, 3, 4);
      }

      SECTION("Division", "")
      {
        Color c(255, 255, 255, 255);
        c = c / 2.0f;
        CHECK_COLOR_4(c, 127, 127, 127, 127);

        Color c2(1, 2, 3, 4);
        c2 /= 1.0f;
        CHECK_COLOR_4(c2, 1, 2, 3, 4);
      }
    }
  }
};