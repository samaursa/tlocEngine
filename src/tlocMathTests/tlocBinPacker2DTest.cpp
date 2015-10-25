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

    SECTION("Assertion tests", "")
    {
      bin_vso b(MakeArgs(core_ds::MakeTuple(2, 2)));

      TLOC_TEST_ASSERT
      {
        b->push_back(case_type(rect_type(width(1), height(0))));
      } TLOC_TEST_ASSERT_CHECK();
      
      TLOC_TEST_ASSERT
      {
        b->push_back(case_type(rect_type(width(0), height(1)) ));
      } TLOC_TEST_ASSERT_CHECK();
    }

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

    SECTION("Small bin not large enough", "")
    {
      bin_vso b(MakeArgs(core_ds::MakeTuple(2, 2)));
      b->SetAutoExpand(false);
      b->push_back(case_type(rect_type(width(2), height(2)) ));
      b->push_back(case_type(rect_type(width(1), height(1)) ));

      optimize::BinPacker2D bp(b.get());
      auto err = bp.Process<optimize::GuillotineBinPack>();
      CHECK_FALSE(err == ErrorSuccess);
      CHECK(b->size_packed() == 1);
    }

    SECTION("Large bin not large enough - rotation NOT ALLOWED", "")
    {
      bin_vso b(MakeArgs(core_ds::MakeTuple(10, 10)));
      b->SetAutoExpand(false);
      b->push_back(case_type(rect_type(width(6), height(10)) ));
      b->push_back(case_type(rect_type(width(10), height(1)) ));

      optimize::BinPacker2D bp(b.get());
      auto err = bp.Process<optimize::GuillotineBinPack>();
      CHECK_FALSE(err == ErrorSuccess);
      CHECK(b->size_packed() == 1);
    }

    SECTION("Large bin not large enough - rotation ALLOWED", "")
    {
      bin_vso b(MakeArgs(core_ds::MakeTuple(10, 10)));
      b->SetAutoExpand(false);
      b->push_back(case_type(rect_type(width(6), height(10)) ));
      b->push_back(case_type(rect_type(width(10), height(1)) ));

      optimize::BinPacker2D bp(b.get());

      p_guillotine_bin_pack::Params p;
      p.AllowRotation(true);

      auto err = bp.Process<optimize::GuillotineBinPack>(p);
      CHECK(err == ErrorSuccess);
      CHECK(b->size_packed() == 2);
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
      
      SECTION("Test Autoexpand with power of two", "")
      {
        b->push_back(case_type(rect_type(width(10), height(2))));
        b->push_back(case_type(rect_type(width(10), height(2))));

        b->push_back(case_type(rect_type(width(2), height(6))));
        b->push_back(case_type(rect_type(width(2), height(6))));

        b->push_back(case_type(rect_type(width(6), height(2))));
        b->push_back(case_type(rect_type(width(6), height(2))));

        b->push_back(case_type(rect_type(width(3), height(2))));
        b->push_back(case_type(rect_type(width(3), height(2))));

        b->push_back(case_type(rect_type(width(13), height(79))));

        optimize::BinPacker2D bp(b.get());
        b->SetAutoExpand(true).SetPowerOfTwo(true);

        auto err = bp.Process<optimize::GuillotineBinPack>();
        CHECK(err == ErrorSuccess);
        CHECK(b->size_packed() == 9);
      }

      SECTION("Test Autoexpand without power of two", "")
      {
        b->push_back(case_type(rect_type(width(10), height(2))));
        b->push_back(case_type(rect_type(width(10), height(2))));

        b->push_back(case_type(rect_type(width(2), height(6))));
        b->push_back(case_type(rect_type(width(2), height(6))));

        b->push_back(case_type(rect_type(width(6), height(2))));
        b->push_back(case_type(rect_type(width(6), height(2))));

        b->push_back(case_type(rect_type(width(3), height(2))));
        b->push_back(case_type(rect_type(width(3), height(2))));

        b->push_back(case_type(rect_type(width(13), height(79))));

        optimize::BinPacker2D bp(b.get());
        b->SetAutoExpand(true).SetPowerOfTwo(false);

        auto err = bp.Process<optimize::GuillotineBinPack>();
        CHECK(err == ErrorSuccess);
        CHECK(b->size_packed() == 9);
      }
    }
  }
};