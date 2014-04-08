#include "tlocTestCommon.h"

#include <tlocGraphics/media/tlocImage.h>
#include <tlocCore/utilities/tlocContainerUtils.h>

namespace TestingImage
{
  using namespace tloc;
  using namespace tloc::gfx_med;
  using namespace tloc::gfx_t;

  TEST_CASE("tloc/graphics/Image/LoadFromMemory", "")
  {
    SECTION("From Memory uchar8", "")
    {
      uchar8 pixels[8] =
      {
        0, 16, 32, 255,
        32, 64, 128, 128
      };

      Image::const_uchar8_ptr pixelsPtr(pixels);

      Image img;
      img.LoadFromMemory(pixelsPtr, core_ds::MakeTuple(2, 1), 4);

      CHECK(img.GetDimensions()[0] == 2);
      CHECK(img.GetDimensions()[1] == 1);

      CHECK(img.GetPixel(0, 0)[0] == 0);
      CHECK(img.GetPixel(0, 0)[1] == 16);
      CHECK(img.GetPixel(0, 0)[2] == 32);
      CHECK(img.GetPixel(0, 0)[3] == 255);

      CHECK(img.GetPixel(1, 0)[0] == 32);
      CHECK(img.GetPixel(1, 0)[1] == 64);
      CHECK(img.GetPixel(1, 0)[2] == 128);
      CHECK(img.GetPixel(1, 0)[3] == 128);
    }

    SECTION("From Memory uchar8", "")
    {
      gfx_t::Color c1(0, 16, 32, 255);
      gfx_t::Color c2(32, 64, 128, 128);

      Image::pixel_container_type pixelCont;
      pixelCont.push_back(c1);
      pixelCont.push_back(c2);

      Image img;
      img.LoadFromMemory(pixelCont, core_ds::MakeTuple(2, 1));

      CHECK(img.GetPixels()[0] == c1);
      CHECK(img.GetPixels()[1] == c2);
    }
  }

  TEST_CASE("tloc/graphics/Image/Create", "")
  {
    const gfx_t::Color c1(1.0f, 0.1f, 0.2f, 0.3f);

    Image img;
    img.Create(core_ds::MakeTuple(2, 2), c1);

    CHECK(img.GetWidth() == 2);
    CHECK(img.GetHeight() == 2);

    CHECK(img.GetPixels()[0] == c1);
    CHECK(img.GetPixels()[1] == c1);
    CHECK(img.GetPixels()[2] == c1);
    CHECK(img.GetPixels()[3] == c1);
  }

  TEST_CASE("tloc/graphics/Image/AddPadding", "")
  {
    const gfx_t::Color c1 = gfx_t::Color::COLOR_BLACK;
    const gfx_t::Color c2 = gfx_t::Color::COLOR_WHITE;

    SECTION("1x1 Padding", "")
    {
      Image img;
      img.Create(core_ds::MakeTuple(2, 2), c1);

      CHECK(img.GetWidth() == 2);
      CHECK(img.GetHeight() == 2);

      const Image::dimension_type padding = core_ds::MakeTuple(1, 1);
      img.AddPadding(padding, c2);

      CHECK(img.GetWidth() == 4);
      CHECK(img.GetHeight() == 4);

      CHECK(img.GetPixels()[0] == c2);
      CHECK(img.GetPixels()[1] == c2);
      CHECK(img.GetPixels()[2] == c2);
      CHECK(img.GetPixels()[3] == c2);

      CHECK(img.GetPixels()[4] == c2);
      CHECK(img.GetPixels()[5] == c1);
      CHECK(img.GetPixels()[6] == c1);
      CHECK(img.GetPixels()[7] == c2);

      CHECK(img.GetPixels()[8] == c2);
      CHECK(img.GetPixels()[9] == c1);
      CHECK(img.GetPixels()[10] == c1);
      CHECK(img.GetPixels()[11] == c2);

      CHECK(img.GetPixels()[12] == c2);
      CHECK(img.GetPixels()[13] == c2);
      CHECK(img.GetPixels()[14] == c2);
      CHECK(img.GetPixels()[15] == c2);
    }

    SECTION("0x1 Padding", "")
    {
      Image img;
      img.Create(core_ds::MakeTuple(2, 2), c1);

      CHECK(img.GetWidth() == 2);
      CHECK(img.GetHeight() == 2);

      const Image::dimension_type padding = core_ds::MakeTuple(0, 1);
      img.AddPadding(padding, c2);

      CHECK(img.GetWidth() == 2);
      CHECK(img.GetHeight() == 4);

      CHECK(img.GetPixels()[0] == c2);
      CHECK(img.GetPixels()[1] == c2);

      CHECK(img.GetPixels()[2] == c1);
      CHECK(img.GetPixels()[3] == c1);

      CHECK(img.GetPixels()[4] == c1);
      CHECK(img.GetPixels()[5] == c1);

      CHECK(img.GetPixels()[6] == c2);
      CHECK(img.GetPixels()[7] == c2);
    }

    SECTION("1x0 Padding", "")
    {
      Image img;
      img.Create(core_ds::MakeTuple(2, 2), c1);

      CHECK(img.GetWidth() == 2);
      CHECK(img.GetHeight() == 2);

      const Image::dimension_type padding = core_ds::MakeTuple(1, 0);
      img.AddPadding(padding, c2);

      CHECK(img.GetWidth() == 4);
      CHECK(img.GetHeight() == 2);

      CHECK(img.GetPixels()[0] == c2);
      CHECK(img.GetPixels()[1] == c1);
      CHECK(img.GetPixels()[2] == c1);
      CHECK(img.GetPixels()[3] == c2);

      CHECK(img.GetPixels()[4] == c2);
      CHECK(img.GetPixels()[5] == c1);
      CHECK(img.GetPixels()[6] == c1);
      CHECK(img.GetPixels()[7] == c2);
    }

    SECTION("2x2 Padding", "")
    {
      Image img;
      img.Create(core_ds::MakeTuple(2, 2), c1);

      CHECK(img.GetWidth() == 2);
      CHECK(img.GetHeight() == 2);

      const Image::dimension_type padding = core_ds::MakeTuple(2, 2);
      img.AddPadding(padding, c2);

      CHECK(img.GetWidth() == 6);
      CHECK(img.GetHeight() == 6);

      for (tl_size x = 0; x < img.GetWidth(); ++x)
      {
        for (tl_size y = 0; y < img.GetHeight(); ++y)
        {
          if (x < padding[0] || x > 2 ||
              y < padding[1] || y > 2)
          {
            CHECK(img.GetPixel(x, y) == c2);
          }
          else
          {
            CHECK(img.GetPixel(x, y) == c1);
          }
        }
      }
    }
  }

  TEST_CASE("tloc/graphics/Image/GetSet", "")
  {
    gfx_t::Color c1(0, 16, 32, 255);
    gfx_t::Color c2(32, 64, 128, 128);

    Image::pixel_container_type pixelCont;
    pixelCont.push_back(c1);
    pixelCont.push_back(c2);

    Image img;
    img.LoadFromMemory(pixelCont, core_ds::MakeTuple(2, 1));

    CHECK(img.GetPixel(0, 0) == c1);
    CHECK(img.GetPixel(1, 0) == c2);

    img.SetPixel(0, 0, c2);
    img.SetPixel(1, 0, c1);

    CHECK(img.GetPixel(0, 0) == c2);
    CHECK(img.GetPixel(1, 0) == c1);
  }

};