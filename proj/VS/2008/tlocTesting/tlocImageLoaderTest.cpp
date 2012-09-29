#include "tlocTestCommon.h"
#include <tlocCore/platform/tlocPlatform.h>

#if defined(TLOC_OS_IPHONE)
#import <Foundation/Foundation.h>
#endif

#include <tlocCore/string/tlocString.h>
#include <tlocCore/string/tlocString.inl>

#include <tlocGraphics/media/tlocImageLoader.h>

#include <3rdParty/Graphics/lodepng/lodepng.h>
#include <3rdParty/Graphics/lodepng/lodepng.c>

namespace TestingImageLoader
{
  using namespace tloc;
  using namespace tloc::graphics;

#if defined(TLOC_OS_IPHONE)
  core::String g_resourcePath([[[NSBundle mainBundle] resourcePath]
                               cStringUsingEncoding:[NSString defaultCStringEncoding]]);
  core::String g_png_test_1_path(g_resourcePath + core::String("/png_test_1.png"));
#else
  core::String g_png_test_1_path("./png_test_1.png");
#endif

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
    core::io::Path path(g_png_test_1_path.c_str());
    CHECK(png.Load(path) == common_error_types::error_success);
  }
};