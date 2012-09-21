#include "tlocTestCommon.h"

#include <tlocGraphics/media/tlocImageLoader.h>

#include <3rdParty/Graphics/lodepng/lodepng.h>
#include <3rdParty/Graphics/lodepng/lodepng.c>

namespace TestingImageLoader
{
  using namespace tloc;
  using namespace tloc::graphics;

  TEST_CASE("Graphics/media/ImageLoaderPng", "")
  {
    /*unsigned int error;
    unsigned char* image;
    unsigned int width, height;
    unsigned char* png;
    size_t pngsize;

    lodepng_load_file(&png, &pngsize, "./png_test_1.png");
    error = lodepng_decode32(&image, &width, &height, png, pngsize);
    CHECK(error == 0);*/

    media::ImageLoaderPng  png;
    core::io::Path path("./png_test_1.png");
    CHECK(png.Load(path) == common_error_types::error_success);
  }
};