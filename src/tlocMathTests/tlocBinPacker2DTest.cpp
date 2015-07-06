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

    bin_vso b(MakeArgs(core_ds::MakeTuple(2, 2)));
    b->push_back(case_type(rect_type(width(1), height(1)) ));
    b->push_back(case_type(rect_type(width(1), height(1)) ));
    b->push_back(case_type(rect_type(width(1), height(1)) ));
    b->push_back(case_type(rect_type(width(1), height(1)) ));

    optimize::BinPacker2D bp(b.get());
    auto err = bp.Process<optimize::GuillotineBinPack>();
    CHECK(err == ErrorSuccess);
  }
};