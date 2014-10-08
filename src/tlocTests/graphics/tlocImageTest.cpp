#include "tlocTestCommon.h"

#include <tlocGraphics/media/tlocImage.h>
#include <tlocCore/utilities/tlocContainerUtils.h>

namespace TestingImage
{
  using namespace tloc;
  using namespace tloc::gfx_med;
  using namespace tloc::gfx_t;

  TEST_CASE("tloc/graphics/Image", "Smart pointers")
  {
    { image_rgba_vso  img; image_rgba_vptr  imgPtr = img.get(); }
    { image_rgb_vso   img; image_rgb_vptr   imgPtr = img.get(); }
    { image_rg_vso    img; image_rg_vptr    imgPtr = img.get(); }
    { image_r_vso     img; image_r_vptr     imgPtr = img.get(); }
    { image_f32_r_vso img; image_f32_r_vptr imgPtr = img.get(); }

    { image_stream_rgba_vso  img; image_stream_rgba_vptr  imgPtr = img.get(); }
    { image_stream_rgb_vso   img; image_stream_rgb_vptr   imgPtr = img.get(); }
    { image_stream_rg_vso    img; image_stream_rg_vptr    imgPtr = img.get(); }
    { image_stream_r_vso     img; image_stream_r_vptr     imgPtr = img.get(); }
    { image_stream_f32_r_vso img; image_stream_f32_r_vptr imgPtr = img.get(); }

    { image_rgba::pixel_container_type  cont; }
    { image_rgb::pixel_container_type   cont; }
    { image_rg::pixel_container_type    cont; }
    { image_r::pixel_container_type     cont; }
    { image_f32_r::pixel_container_type cont; }

    { image_stream_rgba::pixel_container_type  cont; }
    { image_stream_rgb::pixel_container_type   cont; }
    { image_stream_rg::pixel_container_type    cont; }
    { image_stream_r::pixel_container_type     cont; }
    { image_stream_f32_r::pixel_container_type cont; }
  }

  TEST_CASE("tloc/graphics/Image/Load", "")
  {
    SECTION("From Memory uchar8", "")
    {
      uchar8 pixels[8] =
      {
        0, 16, 32, 255,
        32, 64, 128, 128
      };
      Image::color_ptr pixelsPtr(pixels);

      uchar8 pixels2[8] =
      {
        1, 2, 3, 4,
        5, 6, 7, 8 
      };
      Image::color_ptr pixelsPtr2(pixels2);

      SECTION("Image_T<Internal>", "")
      {
        TLOC_TEST_ASSERT
        {
          Image img;
          CHECK_FALSE(img.IsValid());
          img.Load(pixelsPtr, core_ds::MakeTuple(2, 1), 3);
        }
        TLOC_TEST_ASSERT_CHECK();

        Image img;
        CHECK_FALSE(img.IsValid());
        img.Load(pixelsPtr, core_ds::MakeTuple(2, 1), 4);
        CHECK(img.IsValid());

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

        img.Load(pixelsPtr2, core_ds::MakeTuple(2, 1), 4);
        CHECK(img.IsValid());

        CHECK(img.GetDimensions()[0] == 2);
        CHECK(img.GetDimensions()[1] == 1);

        CHECK(img.GetPixel(0, 0)[0] == 1);
        CHECK(img.GetPixel(0, 0)[1] == 2);
        CHECK(img.GetPixel(0, 0)[2] == 3);
        CHECK(img.GetPixel(0, 0)[3] == 4);

        CHECK(img.GetPixel(1, 0)[0] == 5);
        CHECK(img.GetPixel(1, 0)[1] == 6);
        CHECK(img.GetPixel(1, 0)[2] == 7);
        CHECK(img.GetPixel(1, 0)[3] == 8);
      }

      SECTION("Image_T<External>", "")
      {
        TLOC_TEST_ASSERT
        {
          image_stream_rgba img;
          CHECK_FALSE(img.IsValid());
          img.Load(pixelsPtr, core_ds::MakeTuple(2, 1), 3);
        }
        TLOC_TEST_ASSERT_CHECK();

        image_stream_rgba img;
        CHECK_FALSE(img.IsValid());

        TLOC_TEST_ASSERT
        {
          img.SetPixel(0, 0, image_stream_rgba::color_type(1, 2, 3, 4));
        }
        TLOC_TEST_ASSERT_CHECK();

        {
          uchar8* tempPixels = new uchar8[8];
          Image::color_ptr tempPixelsPtr(tempPixels);

          img.Load(tempPixelsPtr, core_ds::MakeTuple(2, 1), 4);

          delete[] tempPixels;
        }

        img.Load(pixelsPtr, core_ds::MakeTuple(2, 1), 4);
        CHECK(img.IsValid());

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

        img.Load(pixelsPtr2, core_ds::MakeTuple(2, 1), 4);
        CHECK(img.IsValid());

        CHECK(img.GetDimensions()[0] == 2);
        CHECK(img.GetDimensions()[1] == 1);

        CHECK(img.GetPixel(0, 0)[0] == 1);
        CHECK(img.GetPixel(0, 0)[1] == 2);
        CHECK(img.GetPixel(0, 0)[2] == 3);
        CHECK(img.GetPixel(0, 0)[3] == 4);

        CHECK(img.GetPixel(1, 0)[0] == 5);
        CHECK(img.GetPixel(1, 0)[1] == 6);
        CHECK(img.GetPixel(1, 0)[2] == 7);
        CHECK(img.GetPixel(1, 0)[3] == 8);
      }
    }

    SECTION("From Memory uchar8", "")
    {
      gfx_t::Color c1(0, 16, 32, 255);
      gfx_t::Color c2(32, 64, 128, 128);

      Image::pixel_container_type pixelCont;
      pixelCont.push_back(c1);
      pixelCont.push_back(c2);

      Image img;
      img.Load(pixelCont, core_ds::MakeTuple(2, 1));

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
          if (x < padding[0] || x >= 2 + padding[0] ||
              y < padding[1] || y >= 2 + padding[1])
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
    SECTION("Get/Set Pixel", "")
    {
      gfx_t::Color c1(0, 16, 32, 255);
      gfx_t::Color c2(32, 64, 128, 128);

      Image::pixel_container_type pixelCont;
      pixelCont.push_back(c1);
      pixelCont.push_back(c2);

      Image img;
      img.Load(pixelCont, core_ds::MakeTuple(2, 1));

      CHECK(img.GetPixel(0, 0) == c1);
      CHECK(img.GetPixel(1, 0) == c2);

      img.SetPixel(0, 0, c2);
      img.SetPixel(1, 0, c1);

      CHECK(img.GetPixel(0, 0) == c2);
      CHECK(img.GetPixel(1, 0) == c1);
    }

    SECTION("Get/Set Pixel", "")
    {
      const gfx_t::Color c1 = gfx_t::Color::COLOR_BLACK;
      const gfx_t::Color c2 = gfx_t::Color::COLOR_WHITE;
      const gfx_t::Color c3 = gfx_t::Color(255, 0, 0, 255);

      Image img;
      img.Create(core_ds::MakeTuple(2, 2), c1);
      img.SetPixel(0, 0, c3);
      img.SetPixel(1, 1, c3);
      img.AddPadding(core_ds::MakeTuple(1, 1), c2);

      image_sptr img2 = img.GetImage(0, 0, core_ds::MakeTuple(1, 1));
      CHECK(img2->GetPixel(0, 0) == c2);

      SECTION("Square sections", "")
      {
        img2 = img.GetImage(0, 0, core_ds::MakeTuple(2, 2));
        CHECK(img2->GetPixel(0, 0) == c2);
        CHECK(img2->GetPixel(1, 0) == c2);
        CHECK(img2->GetPixel(0, 1) == c2);
        CHECK(img2->GetPixel(1, 1) == c3);

        img2 = img.GetImage(1, 1, core_ds::MakeTuple(2, 2));
        CHECK(img2->GetPixel(0, 0) == c3);
        CHECK(img2->GetPixel(1, 0) == c1);
        CHECK(img2->GetPixel(0, 1) == c1);
        CHECK(img2->GetPixel(1, 1) == c3);
      }

      SECTION("Non square sections", "")
      {
        img2 = img.GetImage(1, 1, core_ds::MakeTuple(1, 2));
        CHECK(img2->GetPixel(0, 0) == c3);
        CHECK(img2->GetPixel(0, 1) == c1);

        img2 = img.GetImage(1, 1, core_ds::MakeTuple(2, 1));
        CHECK(img2->GetPixel(0, 0) == c3);
        CHECK(img2->GetPixel(1, 0) == c1);
      }

      SECTION("Getting the whole image - aka copy", "")
      {
        img2 = img.GetImage(0, 0, core_ds::MakeTuple(4, 4));
        REQUIRE(img2->GetDimensions() == img.GetDimensions());
        for (tl_size i = 0; i < img.GetWidth() * img.GetHeight(); ++i)
        {
          CHECK(img2->GetPixels()[i] == img.GetPixels()[i]);
        }
      }

      const gfx_t::Color c4(255, 0, 0, 0);

      img2->Create(core_ds::MakeTuple(2, 2), c4);
      img.SetImage(1, 1, *img2);

      CHECK(img.GetPixel(1, 1) == c4);
      CHECK(img.GetPixel(2, 1) == c4);
      CHECK(img.GetPixel(1, 2) == c4);
      CHECK(img.GetPixel(2, 2) == c4);

      img2->Create(core_ds::MakeTuple(4, 4), c4);
      img.SetImage(0, 0, *img2);

      for (tl_size i = 0; i < img.GetWidth() * img.GetHeight(); ++i)
      {
        CHECK(img.GetPixels()[i] == c4);
      }
    }

    SECTION("Get/Set Pixel (external storage)", "")
    {
      uchar8 pixels[8] =
      {
        0, 16, 32, 255,
        32, 64, 128, 128
      };
      Image::color_ptr pixelsPtr(pixels);

      image_stream_rgba img;
      CHECK_FALSE(img.IsValid());
      img.Load(pixelsPtr, core_ds::MakeTuple(2, 1), 4);
      CHECK(img.IsValid());

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

      img.SetPixel(0, 0, image_stream_rgba::color_type(1, 2, 3, 4) );
      img.SetPixel(1, 0, image_stream_rgba::color_type(3, 4, 5, 6) );

      CHECK(img.GetPixel(0, 0)[0] == 1); CHECK(pixels[0] == 1);
      CHECK(img.GetPixel(0, 0)[1] == 2); CHECK(pixels[1] == 2);
      CHECK(img.GetPixel(0, 0)[2] == 3); CHECK(pixels[2] == 3);
      CHECK(img.GetPixel(0, 0)[3] == 4); CHECK(pixels[3] == 4);

      CHECK(img.GetPixel(1, 0)[0] == 3); CHECK(pixels[4] == 3);
      CHECK(img.GetPixel(1, 0)[1] == 4); CHECK(pixels[5] == 4);
      CHECK(img.GetPixel(1, 0)[2] == 5); CHECK(pixels[6] == 5);
      CHECK(img.GetPixel(1, 0)[3] == 6); CHECK(pixels[7] == 6);

    }
  }

};