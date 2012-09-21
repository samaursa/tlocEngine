#include "tlocTestCommon.h"

#include <tlocGraphics/media/tlocImageLoader.h>

namespace TestingImageLoader
{
  using namespace tloc;
  using namespace tloc::graphics;

  TEST_CASE("Graphics/media/ImageLoaderPng", "")
  {
    media::ImageLoaderPng  png;
    core::io::Path path("./png_test_1.png");
    CHECK(png.Load(path) == common_error_types::error_success);
  }
};