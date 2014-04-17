#include "tlocTestCommon.h"

#include <tlocCore/types/tlocTemplateParams.h>

namespace TestingTemplateParams
{
  using namespace tloc;
  using namespace core;
  using namespace types;

  TEST_CASE("core/types/ParamList", "")
  {
    SECTION("OneParam", "")
    {
      ParamList<tl_int> 
        p = MakeArgs(1);
      CHECK(p.m_param1 == 1);
    }

    SECTION("TwoParams", "")
    {
      ParamList<tl_int, tl_int> 
        p = MakeArgs(1, 2);
      CHECK(p.m_param1 == 1); CHECK(p.m_param2 == 2);
    }

    SECTION("ThreeParams", "")
    {
      ParamList<tl_int, tl_int, tl_int> 
        p = MakeArgs(1, 2, 3);
      CHECK(p.m_param1 == 1); CHECK(p.m_param2 == 2); CHECK(p.m_param3 == 3);
    }

    SECTION("FourParams", "")
    {
      ParamList<tl_int, tl_int, tl_int, tl_int> 
        p = MakeArgs(1, 2, 3, 4);
      CHECK(p.m_param1 == 1); CHECK(p.m_param2 == 2); CHECK(p.m_param3 == 3);
      CHECK(p.m_param4 == 4); 
    }

    SECTION("FiveParams", "")
    {
      ParamList<tl_int, tl_int, tl_int, tl_int,
                tl_int> 
                p = MakeArgs(1, 2, 3, 4, 5);

      CHECK(p.m_param1 == 1); CHECK(p.m_param2 == 2); CHECK(p.m_param3 == 3);
      CHECK(p.m_param4 == 4); CHECK(p.m_param5 == 5);
    }

    SECTION("SixParams", "")
    {
      ParamList<tl_int, tl_int, tl_int, tl_int,
                tl_int, tl_int> 
        p = MakeArgs(1, 2, 3, 4, 5, 6);

      CHECK(p.m_param1 == 1); CHECK(p.m_param2 == 2); CHECK(p.m_param3 == 3);
      CHECK(p.m_param4 == 4); CHECK(p.m_param5 == 5); CHECK(p.m_param6 == 6);
    }

    SECTION("SevenParams", "")
    {
      ParamList<tl_int, tl_int, tl_int, tl_int,
                tl_int, tl_int, tl_int> 
        p = MakeArgs(1, 2, 3, 4, 5, 6, 7);

      CHECK(p.m_param1 == 1); CHECK(p.m_param2 == 2); CHECK(p.m_param3 == 3);
      CHECK(p.m_param4 == 4); CHECK(p.m_param5 == 5); CHECK(p.m_param6 == 6);
      CHECK(p.m_param7 == 7);
    }
    
    SECTION("EightParams", "")
    {
      ParamList<tl_int, tl_int, tl_int, tl_int,
                tl_int, tl_int, tl_int, tl_int> 
        p = MakeArgs(1, 2, 3, 4, 5, 6, 7, 8);

      CHECK(p.m_param1 == 1); CHECK(p.m_param2 == 2); CHECK(p.m_param3 == 3);
      CHECK(p.m_param4 == 4); CHECK(p.m_param5 == 5); CHECK(p.m_param6 == 6);
      CHECK(p.m_param7 == 7); CHECK(p.m_param8 == 8);
    }

    SECTION("NineParams", "")
    {
      ParamList<tl_int, tl_int, tl_int, tl_int,
                tl_int, tl_int, tl_int, tl_int,
                tl_int>
        p = MakeArgs(1, 2, 3, 4, 5, 6, 7, 8, 9);

      CHECK(p.m_param1 == 1); CHECK(p.m_param2 == 2); CHECK(p.m_param3 == 3);
      CHECK(p.m_param4 == 4); CHECK(p.m_param5 == 5); CHECK(p.m_param6 == 6);
      CHECK(p.m_param7 == 7); CHECK(p.m_param8 == 8); CHECK(p.m_param9 == 9);
    }

    SECTION("TenParams", "")
    {
      ParamList<tl_int, tl_int, tl_int, tl_int,
                tl_int, tl_int, tl_int, tl_int,
                tl_int, tl_int>
        p = MakeArgs(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

      CHECK(p.m_param1 == 1); CHECK(p.m_param2 == 2); CHECK(p.m_param3 == 3);
      CHECK(p.m_param4 == 4); CHECK(p.m_param5 == 5); CHECK(p.m_param6 == 6);
      CHECK(p.m_param7 == 7); CHECK(p.m_param8 == 8); CHECK(p.m_param9 == 9);
      CHECK(p.m_param10 == 10);
    }
  }
};