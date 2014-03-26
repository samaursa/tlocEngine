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