#include "tlocTestCommon.h"

#include <tlocCore/io/tlocFileIO.h>
#include <tlocGraphics/media/tlocSpriteLoader.h>

namespace TestingSpriteLoader
{
  using namespace tloc;
  using namespace graphics::media;

  core_str::String
    g_sprite_loader_path(GetAssetsPath() +
                         core_str::String("spriteSheetPacker.txt"));


#define CHECK_TUP2S(tup,x,y) CHECK((tup[0]) == x); \
                             CHECK((tup[1]) == y)

#define CHECK_VEC2F(vec,x,y) CHECK((vec[0]) == (Approx(x)) ); \
                             CHECK((vec[1]) == (Approx(y)) )

  TEST_CASE("Graphics/media/SpriteLoader/", "")
  {
    SpriteLoader_SpriteSheetPacker  sl_ssp;

    core_io::FileIO_ReadA txtFile(core_io::Path(g_sprite_loader_path.c_str()) );

    REQUIRE(txtFile.Open() == ErrorSuccess);

    core_str::String fileContents;
    txtFile.GetContents(fileContents);

    sl_ssp.Init(fileContents, gfx_t::Dimension2i(1820, 1260));

    CHECK(sl_ssp.GetSpriteInfo().size() == 104);

    // we will check the first couple of lines and the last couple of lines
    CHECK(sl_ssp.GetSpriteInfo()[0].m_name.compare("red_idle_0001") == 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[0].m_startingPos, 0, 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[0].m_endingPos, 140, 140);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[0].m_texCoordStart, 0, 0);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[0].m_texCoordEnd, 140.0f/1820.0f, 140.0f/1260.0f);

    CHECK(sl_ssp.GetSpriteInfo()[1].m_name.compare("red_idle_0002") == 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[1].m_startingPos, 140, 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[1].m_endingPos, 140, 140);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[1].m_texCoordStart, 140.0f/1820.0f, 0);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[1].m_texCoordEnd, 140.0f/1820.0f, 140.0f/1260.0f);

    CHECK(sl_ssp.GetSpriteInfo()[9].m_name.compare("red_idle_0010") == 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[9].m_startingPos, 420, 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[9].m_endingPos, 140, 140);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[9].m_texCoordStart, 420.0f/1820.0f, 0);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[9].m_texCoordEnd, 140.0f/1820.0f, 140.0f/1260.0f);

    CHECK(sl_ssp.GetSpriteInfo()[103].m_name.compare("red_idle_0104") == 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[103].m_startingPos, 700, 1120);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[103].m_texCoordStart, 700.0f/1820.0f, 1120.0f/1260.0f);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[103].m_endingPos, 140, 140);

    SpriteLoader_SpriteSheetPacker::const_iterator itr, itrEnd;

    itr = sl_ssp.begin("red_idle");
    itrEnd = sl_ssp.end("red_idle");

    CHECK(itr == sl_ssp.begin());
    CHECK(itr != sl_ssp.end());
    CHECK(itrEnd == sl_ssp.end());
  }
};