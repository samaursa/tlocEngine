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

  TEST_CASE("Graphics/media/SpriteLoader/", "")
  {
    SpriteLoader_SpriteSheetPacker  sl_ssp;

    core_io::FileIO_ReadA txtFile(core_io::Path(g_sprite_loader_path.c_str()) );

    REQUIRE(txtFile.Open() == ErrorSuccess);

    core_str::String fileContents;
    txtFile.GetContents(fileContents);

    sl_ssp.Init(fileContents);

    CHECK(sl_ssp.GetSpriteInfo().size() == 104);

    // we will check the first couple of lines and the last couple of lines
    CHECK(sl_ssp.GetSpriteInfo()[0].m_name.compare("red_idle_0001") == 0);
    CHECK(sl_ssp.GetSpriteInfo()[0].m_startingPos[0] == 0);
    CHECK(sl_ssp.GetSpriteInfo()[0].m_startingPos[1] == 0);
    CHECK(sl_ssp.GetSpriteInfo()[0].m_endingPos[0] == 140);
    CHECK(sl_ssp.GetSpriteInfo()[0].m_endingPos[1] == 140);

    CHECK(sl_ssp.GetSpriteInfo()[1].m_name.compare("red_idle_0002") == 0);
    CHECK(sl_ssp.GetSpriteInfo()[1].m_startingPos[0] == 140);
    CHECK(sl_ssp.GetSpriteInfo()[1].m_startingPos[1] == 0);
    CHECK(sl_ssp.GetSpriteInfo()[1].m_endingPos[0] == 140);
    CHECK(sl_ssp.GetSpriteInfo()[1].m_endingPos[1] == 140);

    CHECK(sl_ssp.GetSpriteInfo()[9].m_name.compare("red_idle_0010") == 0);
    CHECK(sl_ssp.GetSpriteInfo()[9].m_startingPos[0] == 420);
    CHECK(sl_ssp.GetSpriteInfo()[9].m_startingPos[1] == 0);
    CHECK(sl_ssp.GetSpriteInfo()[9].m_endingPos[0] == 140);
    CHECK(sl_ssp.GetSpriteInfo()[9].m_endingPos[1] == 140);

    CHECK(sl_ssp.GetSpriteInfo()[103].m_name.compare("red_idle_0104") == 0);
    CHECK(sl_ssp.GetSpriteInfo()[103].m_startingPos[0] == 700);
    CHECK(sl_ssp.GetSpriteInfo()[103].m_startingPos[1] == 1120);
    CHECK(sl_ssp.GetSpriteInfo()[103].m_endingPos[0] == 140);
    CHECK(sl_ssp.GetSpriteInfo()[103].m_endingPos[1] == 140);
  }
};