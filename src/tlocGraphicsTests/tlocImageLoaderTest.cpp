// Put this here first to avoid abs function ambiguity problems
#include <3rdParty/Graphics/lodepng/lodepng.h>

#include "tlocTestCommon.h"

#include <tlocGraphics/media/tlocImageLoader.h>

namespace TestingImageLoader
{
  using namespace tloc;
  using namespace core::string;
  using namespace tloc::graphics;

  typedef graphics::types::Color  color_type;

  extern color_type png_test_1[10][10];
  extern color_type png_test_2[10][10];

  String g_png_test_1_path(GetAssetsPath() + String("/images/png_test_1.png"));
  String g_png_test_2_path(GetAssetsPath() + String("/images/png_test_2.png"));

  TEST_CASE("Graphics/media/ImageLoaderPng/Load", "")
  {
    media::ImageLoaderPng  png;
    core::io::Path path(g_png_test_1_path.c_str());
    CHECK(png.Load(path) == common_error_types::error_success);
  }

  TEST_CASE("Graphics/media/ImageLoaderPng/GetImage/png_test_1", "")
  {
    media::ImageLoaderPng png;
    core::io::Path path(g_png_test_1_path.c_str());
    REQUIRE(png.Load(path) == common_error_types::error_success);

    bool testPassed = true;
    const media::Image& img = png.GetImage();
    for (tl_size i_width = 0; i_width < img.GetWidth(); ++i_width)
    {
      for (tl_size j_height = 0; j_height < img.GetHeight(); ++j_height)
      {
        color_type col = img.GetPixel(i_width, j_height);
        if (col != png_test_1[i_width][j_height])
        {
          testPassed = false; break;
        }
      }
    }
    CHECK(testPassed);
  }

  TEST_CASE("Graphics/media/ImageLoaderPng/GetImage/png_test_2", "")
  {
    media::ImageLoaderPng png;
    core::io::Path path(g_png_test_2_path.c_str());
    REQUIRE(png.Load(path) == common_error_types::error_success);

    bool testPassed = true;
    const media::Image& img = png.GetImage();
    for (tl_size i_width = 0; i_width < img.GetWidth(); ++i_width)
    {
      for (tl_size j_height = 0; j_height < img.GetHeight(); ++j_height)
      {
        color_type col = img.GetPixel(i_width, j_height);
        if (col != png_test_2[i_width][j_height])
        {
          testPassed = false; break;
        }
      }
    }
    CHECK(testPassed);
  }

  //------------------------------------------------------------------------
  // PNG file data

  color_type png_test_1[10][10] =
  {
    {
      //First row is black
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
    },

    {
      //Second row is white
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
    },

    {
      //Third row is black/white alternating with 50% transparency
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
    },

    {
      //Fourth row is white/black alternating with 25% transparency
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
    },

    {
      //Fifth row is all black
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
    },

    {
      //Sixth row is black/white alternating, fully opaque
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
    },

    {
      //Seventh row is all black
      color_type(0, 0, 0, 255),		color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255),	color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255),	color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255),	color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255),	color_type(0, 0, 0, 255),
    },

    {
      //Eigth row is white,white/black,black alternating
      color_type(255, 255, 255, 255),	color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255),				color_type(0, 0, 0, 255),
      color_type(255, 255, 255, 255),	color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255),				color_type(0, 0, 0, 255),
      color_type(255, 255, 255, 255),	color_type(255, 255, 255, 255),
    },

    {
      //Ninth row is all black
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
    },

    {
      //Tenth is 3 blacks, 3 whites then 3 blacks
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255),
      color_type(255, 255, 255, 255),	color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255),	color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255),				color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255),
    },
  };

  color_type png_test_2[10][10] =
  {
    {
      //First row is black
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
    },

    {
      //Second row is white
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
    },

    {
      //Third row is black/white alternating with 50% transparency
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
    },

    {
      //Fourth row is white/black alternating with 25% transparency
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
    },

    {
      //Fifth row is all black
      color_type(255, 0, 0, 255), color_type(255, 0, 0, 255),
      color_type(255, 0, 0, 255), color_type(255, 0, 0, 255),
      color_type(255, 0, 0, 255), color_type(255, 0, 0, 255),
      color_type(255, 0, 0, 255), color_type(255, 0, 0, 255),
      color_type(255, 0, 0, 255), color_type(255, 0, 0, 255),
    },

    {
      //Sixth row is black/white alternating, fully opaque
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
    },

    {
      //Seventh row is all black
      color_type(0, 255, 0, 255),	color_type(0, 255, 0, 255),
      color_type(0, 255, 0, 255),	color_type(0, 255, 0, 255),
      color_type(0, 255, 0, 255),	color_type(0, 255, 0, 255),
      color_type(0, 255, 0, 255),	color_type(0, 255, 0, 255),
      color_type(0, 255, 0, 255),	color_type(0, 255, 0, 255),
    },

    {
      //Eigth row is white,white/black,black alternating
      color_type(255, 0, 0, 255), color_type(0, 255, 0, 255),
      color_type(0, 0, 255, 255),
      color_type(255, 255, 0, 255), color_type(0, 255, 255, 255),
      color_type(255, 0, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 0, 0, 255), color_type(0, 255, 0, 255),
      color_type(0, 0, 255, 255),
    },

    {
      //Ninth row is all black
      color_type(0, 0, 255, 255), color_type(0, 0, 255, 255),
      color_type(0, 0, 255, 255), color_type(0, 0, 255, 255),
      color_type(0, 0, 255, 255), color_type(0, 0, 255, 255),
      color_type(0, 0, 255, 255), color_type(0, 0, 255, 255),
      color_type(0, 0, 255, 255), color_type(0, 0, 255, 255),
    },

    {
      //Tenth is 3 blacks, 3 whites then 3 blacks
      color_type(255, 0, 0, 64), color_type(0, 255, 0, 64),
      color_type(0, 0, 255, 64),
      color_type(255, 0, 0, 128), color_type(0, 255, 0, 128),
      color_type(0, 0, 255, 128),
      color_type(255, 0, 0, 191), color_type(0, 255, 0, 191),
      color_type(0, 0, 255, 191),
      color_type(255, 255, 0, 191),
    },
  };

};