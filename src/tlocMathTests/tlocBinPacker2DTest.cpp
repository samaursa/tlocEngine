#include "tlocTestCommon.h"

#include <tlocMath/optimize/tlocBinPacker2D.h>

namespace BinPacker2D
{
  using namespace tloc;
  using namespace math;
  using namespace optimize;

  TEST_CASE("math/optimize/BinPacker2D", "")
  {
    typedef Bin::case_type              case_type;
    typedef Bin::rect_type              rect_type;
    TLOC_EXPOSE_TYPEDEFS_2(rect_type, width, height);

    SECTION("Small bin test", "")
    {
      bin_vso b(MakeArgs(core_ds::MakeTuple(2, 2)));
      b->push_back(case_type(rect_type(width(1), height(1)) ));
      b->push_back(case_type(rect_type(width(1), height(1)) ));
      b->push_back(case_type(rect_type(width(1), height(1)) ));
      b->push_back(case_type(rect_type(width(1), height(1)) ));

      optimize::BinPacker2D bp(b.get());
      auto err = bp.Process<optimize::GuillotineBinPack>();
      CHECK(err == ErrorSuccess);
      CHECK(b->size_packed() == 4);
    }

    SECTION("Large bin test", "")
    {
      const tl_int binWidth = 10;
      const tl_int binHeight = 10;
      bin_vso b(MakeArgs(core_ds::MakeTuple(binWidth, binHeight)));

      SECTION("Few rectangles to pack", "")
      {
        b->push_back(case_type(rect_type(width(1), height(1))));
        b->push_back(case_type(rect_type(width(1), height(1))));
        b->push_back(case_type(rect_type(width(1), height(1))));
        b->push_back(case_type(rect_type(width(1), height(1))));

        optimize::BinPacker2D bp(b.get());
        auto err = bp.Process<optimize::GuillotineBinPack>();
        CHECK(err == ErrorSuccess);
        CHECK(b->size_packed() == 4);
      }

      SECTION("Many rectangles to pack", "")
      {
        for (tl_int i = 0; i < binWidth * binHeight; ++i)
        { b->push_back(case_type(rect_type(width(1), height(1)) )); }

        optimize::BinPacker2D bp(b.get());
        auto err = bp.Process<optimize::GuillotineBinPack>();
        CHECK(err == ErrorSuccess);
        CHECK(b->size_packed() == binWidth * binHeight);
      }

      SECTION("Different shaped rectangles", "")
      {
        b->push_back(case_type(rect_type(width(10), height(2))));
        b->push_back(case_type(rect_type(width(10), height(2))));

        b->push_back(case_type(rect_type(width(2), height(6))));
        b->push_back(case_type(rect_type(width(2), height(6))));

        b->push_back(case_type(rect_type(width(6), height(2))));
        b->push_back(case_type(rect_type(width(6), height(2))));

        b->push_back(case_type(rect_type(width(3), height(2))));
        b->push_back(case_type(rect_type(width(3), height(2))));


        optimize::BinPacker2D bp(b.get());
        auto err = bp.Process<optimize::GuillotineBinPack>();
        CHECK(err == ErrorSuccess);
        CHECK(b->size_packed() == 8);
      }
    }
  }
};