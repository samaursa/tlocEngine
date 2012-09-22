#include "tlocTestCommon.h"

#include <tlocGraphics/media/tlocImageLoader.h>

#include <3rdParty/Graphics/lodepng/lodepng.h>
#include <3rdParty/Graphics/lodepng/lodepng.c>

namespace TestingImageLoader
{
  using namespace tloc;
  using namespace tloc::graphics;

  TEST_CASE("Graphics/media/ImageLoaderPng/Load", "")
  {
    media::ImageLoaderPng  png;
    core::io::Path path("./png_test_1.png");
    CHECK(png.Load(path) == common_error_types::error_success);
  }

  TEST_CASE("Graphics/media/ImageLoaderPng/GetImage", "")
  {
    media::ImageLoaderPng png;
    core::io::Path path("./png_test_1.png");
    REQUIRE(png.Load(path) == common_error_types::error_success);

    bool testPassed = true;
    const media::Image& img = png.GetImage();
    TLOC_UNUSED_2(testPassed, img);
  }
};