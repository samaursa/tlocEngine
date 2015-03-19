// Put this here first to avoid abs function ambiguity problems
#include <3rdParty/Graphics/lodepng/lodepng.h>

#include "tlocTestCommon.h"

#include <tlocGraphics/media/tlocImageLoader.h>
#include <tlocMath/tlocMath.h>

namespace TestingImageLoader
{
  using namespace tloc;
  using namespace core::string;
  using namespace tloc::graphics;

  typedef graphics::types::Color      color_type;
  typedef graphics::types::color_rgb  color_rgb_type;

  extern color_type png_test_1[10][10];
  extern color_type png_test_2[10][10];

  String g_png_test_1_path(GetAssetsPath() + String("/images/png_test_1.png"));
  String g_png_test_2_path(GetAssetsPath() + String("/images/png_test_2.png"));

  extern color_rgb_type jpg_test_1[10][10];
  extern color_rgb_type jpg_test_2[10][10];

  String g_jpeg_test_1_path(GetAssetsPath() + String("/images/jpeg_test_1.jpg"));
  String g_jpeg_test_2_path(GetAssetsPath() + String("/images/jpeg_test_2.jpg"));

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
    auto img = png.GetImage();
    for (tl_size i_width = 0; i_width < img->GetWidth(); ++i_width)
    {
      for (tl_size j_height = 0; j_height < img->GetHeight(); ++j_height)
      {
        auto col = img->GetPixel(i_width, j_height);
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
    auto img = png.GetImage();
    for (tl_size i_width = 0; i_width < img->GetWidth(); ++i_width)
    {
      for (tl_size j_height = 0; j_height < img->GetHeight(); ++j_height)
      {
        auto col = img->GetPixel(i_width, j_height);
        if (col != png_test_2[i_width][j_height])
        {
          testPassed = false; break;
        }
      }
    }
    CHECK(testPassed);
  }

  TEST_CASE("Graphics/media/ImageLoaderJpeg/Load", "")
  {
    media::ImageLoaderJpeg  jpg;
    core::io::Path path(g_jpeg_test_1_path.c_str());
    CHECK(jpg.Load(path) == common_error_types::error_success);
  }

  TEST_CASE("Graphics/media/ImageLoaderJpeg/GetImage/jpeg_test_1", "")
  {
    media::ImageLoaderJpeg jpg;
    core::io::Path path(g_jpeg_test_1_path.c_str());
    REQUIRE(jpg.Load(path) == common_error_types::error_success);

    bool testPassed = true;
    auto img = jpg.GetImage();
    for (tl_size i_width = 0; i_width < img->GetWidth(); ++i_width)
    {
      for (tl_size j_height = 0; j_height < img->GetHeight(); ++j_height)
      {
        auto col = img->GetPixel(i_width, j_height);
        const auto hcol = jpg_test_1[i_width][j_height];
        if (math::Abs(col[0] - hcol[0]) > 2 ||
            math::Abs(col[1] - hcol[1]) > 2 ||
            math::Abs(col[2] - hcol[2]) > 2)
        {
          testPassed = false; break;
        }
      }
    }
    CHECK(testPassed);
  }

  // NOTE: Color jpg is hard to test because of lossiness

  //TEST_CASE("Graphics/media/ImageLoaderJpeg/GetImage/jpg_test_2", "")
  //{
  //  media::ImageLoaderJpeg jpg;
  //  core::io::Path path(g_jpeg_test_2_path.c_str());
  //  REQUIRE(jpg.Load(path) == common_error_types::error_success);

  //  bool testPassed = true;
  //  auto img = jpg.GetImage();
  //  for (tl_size i_width = 0; i_width < img->GetWidth(); ++i_width)
  //  {
  //    for (tl_size j_height = 0; j_height < img->GetHeight(); ++j_height)
  //    {
  //      const auto col = img->GetPixel(i_width, j_height);
  //      const auto hcol = jpg_test_2[i_width][j_height];
  //      if (math::Abs(col[0] - hcol[0]) > 2 ||
  //          math::Abs(col[1] - hcol[1]) > 2 ||
  //          math::Abs(col[2] - hcol[2]) > 2)
  //      {
  //        testPassed = false; break;
  //      }
  //    }
  //  }
  //  CHECK(testPassed);
  //}

  //------------------------------------------------------------------------
  // PNG file data

  color_type png_test_1[10][10] =
  {
    {
      //First col is black
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
    },

    {
      //Second col is white
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
    },

    {
      //Third col is black/white alternating with 50% transparency
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
    },

    {
      //Fourth col is white/black alternating with 25% transparency
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
    },

    {
      //Fifth col is all black
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
    },

    {
      //Sixth col is black/white alternating, fully opaque
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
    },

    {
      //Seventh col is all black
      color_type(0, 0, 0, 255),		color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255),	color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255),	color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255),	color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255),	color_type(0, 0, 0, 255),
    },

    {
      //Eigth col is white,white/black,black alternating
      color_type(255, 255, 255, 255),	color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255),				color_type(0, 0, 0, 255),
      color_type(255, 255, 255, 255),	color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255),				color_type(0, 0, 0, 255),
      color_type(255, 255, 255, 255),	color_type(255, 255, 255, 255),
    },

    {
      //Ninth col is all black
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
      //First col is black
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
      color_type(0, 0, 0, 255), color_type(0, 0, 0, 255),
    },

    {
      //Second col is white
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 255, 255, 255), color_type(255, 255, 255, 255),
    },

    {
      //Third col is black/white alternating with 50% transparency
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
      color_type(0, 0, 0, 128), color_type(255, 255, 255, 128),
    },

    {
      //Fourth col is white/black alternating with 25% transparency
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
      color_type(255, 255, 255, 64), color_type(0, 0, 0, 64),
    },

    {
      //Fifth col is all black
      color_type(255, 0, 0, 255), color_type(255, 0, 0, 255),
      color_type(255, 0, 0, 255), color_type(255, 0, 0, 255),
      color_type(255, 0, 0, 255), color_type(255, 0, 0, 255),
      color_type(255, 0, 0, 255), color_type(255, 0, 0, 255),
      color_type(255, 0, 0, 255), color_type(255, 0, 0, 255),
    },

    {
      //Sixth col is black/white alternating, fully opaque
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
      color_type(0, 0, 0, 255), color_type(255, 255, 255, 255),
    },

    {
      //Seventh col is all black
      color_type(0, 255, 0, 255),	color_type(0, 255, 0, 255),
      color_type(0, 255, 0, 255),	color_type(0, 255, 0, 255),
      color_type(0, 255, 0, 255),	color_type(0, 255, 0, 255),
      color_type(0, 255, 0, 255),	color_type(0, 255, 0, 255),
      color_type(0, 255, 0, 255),	color_type(0, 255, 0, 255),
    },

    {
      //Eigth col is white,white/black,black alternating
      color_type(255, 0, 0, 255), color_type(0, 255, 0, 255),
      color_type(0, 0, 255, 255),
      color_type(255, 255, 0, 255), color_type(0, 255, 255, 255),
      color_type(255, 0, 255, 255), color_type(255, 255, 255, 255),
      color_type(255, 0, 0, 255), color_type(0, 255, 0, 255),
      color_type(0, 0, 255, 255),
    },

    {
      //Ninth col is all black
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

  //------------------------------------------------------------------------
  // jpg file data

  color_rgb_type jpg_test_1[10][10] =
  {
    {
      //First col is black
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
    },

    {
      //Second col is white
      color_rgb_type(255, 255, 255), color_rgb_type(255, 255, 255),
      color_rgb_type(255, 255, 255), color_rgb_type(255, 255, 255),
      color_rgb_type(255, 255, 255), color_rgb_type(255, 255, 255),
      color_rgb_type(255, 255, 255), color_rgb_type(255, 255, 255),
      color_rgb_type(255, 255, 255), color_rgb_type(255, 255, 255),
    },

    {
      //Third col is black/white alternating with 50% transparency
      color_rgb_type(127, 127, 127), color_rgb_type(255, 255, 255),
      color_rgb_type(127, 127, 127), color_rgb_type(255, 255, 255),
      color_rgb_type(127, 127, 127), color_rgb_type(255, 255, 255),
      color_rgb_type(127, 127, 127), color_rgb_type(255, 255, 255),
      color_rgb_type(127, 127, 127), color_rgb_type(255, 255, 255),
    },

    {
      //Fourth col is white/black alternating with 25% transparency
      color_rgb_type(255, 255, 255), color_rgb_type(191, 191, 191),
      color_rgb_type(255, 255, 255), color_rgb_type(191, 191, 191),
      color_rgb_type(255, 255, 255), color_rgb_type(191, 191, 191),
      color_rgb_type(255, 255, 255), color_rgb_type(191, 191, 191),
      color_rgb_type(255, 255, 255), color_rgb_type(191, 191, 191),
    },

    {
      //Fifth col is all black
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
    },

    {
      //Sixth col is black/white alternating, fully opaque
      color_rgb_type(0, 0, 0), color_rgb_type(255, 255, 255),
      color_rgb_type(0, 0, 0), color_rgb_type(255, 255, 255),
      color_rgb_type(0, 0, 0), color_rgb_type(255, 255, 255),
      color_rgb_type(0, 0, 0), color_rgb_type(255, 255, 255),
      color_rgb_type(0, 0, 0), color_rgb_type(255, 255, 255),
    },

    {
      //Seventh col is all black
      color_rgb_type(0, 0, 0),		color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0),	color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0),	color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0),	color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0),	color_rgb_type(0, 0, 0),
    },

    {
      //Eigth col is white,white/black,black alternating
      color_rgb_type(255, 255, 255),	color_rgb_type(255, 255, 255),
      color_rgb_type(0, 0, 0),				color_rgb_type(0, 0, 0),
      color_rgb_type(255, 255, 255),	color_rgb_type(255, 255, 255),
      color_rgb_type(0, 0, 0),				color_rgb_type(0, 0, 0),
      color_rgb_type(255, 255, 255),	color_rgb_type(255, 255, 255),
    },

    {
      //Ninth col is all black
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
    },

    {
      //Tenth is 3 blacks, 3 whites then 3 blacks
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0),
      color_rgb_type(255, 255, 255),	color_rgb_type(255, 255, 255),
      color_rgb_type(255, 255, 255),	color_rgb_type(255, 255, 255),
      color_rgb_type(0, 0, 0),				color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0),
    },
  };

  color_rgb_type jpg_test_2[10][10] =
  {
    {
      //First col is black
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
      color_rgb_type(0, 0, 0), color_rgb_type(0, 0, 0),
    },

    {
      //Second col is white
      color_rgb_type(255, 255, 255), color_rgb_type(255, 255, 255),
      color_rgb_type(255, 255, 255), color_rgb_type(255, 255, 255),
      color_rgb_type(255, 255, 255), color_rgb_type(255, 255, 255),
      color_rgb_type(255, 255, 255), color_rgb_type(255, 255, 255),
      color_rgb_type(255, 255, 255), color_rgb_type(255, 255, 255),
    },

    {
      //Third col is black/white alternating with 50% transparency
      color_rgb_type(127, 127, 127), color_rgb_type(255, 255, 255),
      color_rgb_type(127, 127, 127), color_rgb_type(255, 255, 255),
      color_rgb_type(127, 127, 127), color_rgb_type(255, 255, 255),
      color_rgb_type(127, 127, 127), color_rgb_type(255, 255, 255),
      color_rgb_type(127, 127, 127), color_rgb_type(255, 255, 255),
    },

    {
      color_rgb_type(64, 0, 0), color_rgb_type(128, 0, 0),
      color_rgb_type(64, 0, 0), color_rgb_type(128, 0, 0),
      color_rgb_type(64, 0, 0), color_rgb_type(128, 0, 0),
      color_rgb_type(64, 0, 0), color_rgb_type(128, 0, 0),
      color_rgb_type(64, 0, 0), color_rgb_type(128, 0, 0),
    },

    {
      color_rgb_type(255, 0, 0), color_rgb_type(255, 0, 0),
      color_rgb_type(255, 0, 0), color_rgb_type(255, 0, 0),
      color_rgb_type(255, 0, 0), color_rgb_type(255, 0, 0),
      color_rgb_type(255, 0, 0), color_rgb_type(255, 0, 0),
      color_rgb_type(255, 0, 0), color_rgb_type(255, 0, 0),
    },

    {
      color_rgb_type(128, 128, 0), color_rgb_type(0, 64, 0),
      color_rgb_type(128, 128, 0), color_rgb_type(0, 64, 0),
      color_rgb_type(128, 128, 0), color_rgb_type(0, 64, 0),
      color_rgb_type(128, 128, 0), color_rgb_type(0, 64, 0),
      color_rgb_type(128, 128, 0), color_rgb_type(0, 64, 0),
    },

    {
      color_rgb_type(0, 255, 0),	color_rgb_type(0, 255, 0),
      color_rgb_type(0, 255, 0),	color_rgb_type(0, 255, 0),
      color_rgb_type(0, 255, 0),	color_rgb_type(0, 255, 0),
      color_rgb_type(0, 255, 0),	color_rgb_type(0, 255, 0),
      color_rgb_type(0, 255, 0),	color_rgb_type(0, 255, 0),
    },

    {
      color_rgb_type(0, 128, 0), color_rgb_type(0, 128, 128),
      color_rgb_type(0, 128, 0), color_rgb_type(0, 128, 128),
      color_rgb_type(0, 128, 0), color_rgb_type(0, 128, 128),
      color_rgb_type(0, 128, 0), color_rgb_type(0, 128, 128),
      color_rgb_type(0, 128, 0), color_rgb_type(0, 128, 128),
    },

    {
      //Ninth col is all black
      color_rgb_type(0, 0, 255), color_rgb_type(0, 0, 255),
      color_rgb_type(0, 0, 255), color_rgb_type(0, 0, 255),
      color_rgb_type(0, 0, 255), color_rgb_type(0, 0, 255),
      color_rgb_type(0, 0, 255), color_rgb_type(0, 0, 255),
      color_rgb_type(0, 0, 255), color_rgb_type(0, 0, 255),
    },

    {
      //Tenth is 3 blacks, 3 whites then 3 blacks
      color_rgb_type(0, 0, 64), color_rgb_type(128, 128, 128),
      color_rgb_type(0, 0, 64), color_rgb_type(128, 128, 128),
      color_rgb_type(0, 0, 64), color_rgb_type(128, 128, 128),
      color_rgb_type(0, 0, 64), color_rgb_type(128, 128, 128),
      color_rgb_type(0, 0, 64), color_rgb_type(128, 128, 128),
    },
  };

};