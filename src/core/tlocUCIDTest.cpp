#include "tlocTestCommon.h"

#include <tlocCore/tlocUCID.h>

namespace TestingUCID
{
  using namespace tloc;
  using namespace core;

  TEST_CASE("core/UCID", "")
  {
    UCID<tl_int>    intID;
    UCID<tl_float>  floatID;

    CHECK(UCID<tl_int>() == intID);
    CHECK(UCID<tl_float>() == floatID);
    CHECK_FALSE(UCID<tl_int>() == floatID);
    CHECK_FALSE(UCID<tl_float>() == intID);
  }
};