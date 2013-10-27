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

  core_str::String
    g_texture_packer_path(GetAssetsPath() +
                          core_str::String("spriteTexturePacker.xml"));

  core_str::String
    g_texture_packer_multiple_path(GetAssetsPath() +
                          core_str::String("multipleSpriteTexturePacker.xml"));


#define CHECK_TUP2S(tup,x,y) CHECK((tup[0]) == x); \
                             CHECK((tup[1]) == y)

#define CHECK_VEC2F(vec,x,y) CHECK((vec[0]) == (Approx(x)) ); \
                             CHECK((vec[1]) == (Approx(y)) )

  TEST_CASE("Graphics/media/SpriteLoader/SpriteSheetPacker", "")
  {
    SpriteLoader_SpriteSheetPacker  sl_ssp;

    core_io::FileIO_ReadA txtFile(core_io::Path(g_sprite_loader_path.c_str()) );

    REQUIRE(txtFile.Open() == ErrorSuccess);

    core_str::String fileContents;
    txtFile.GetContents(fileContents);

    sl_ssp.Init(fileContents, gfx_t::Dimension2u(1820, 1260));

    CHECK(sl_ssp.GetSpriteInfo().size() == 104);

    // we will check the first couple of lines and the last couple of lines
    // NOTE: y-coords are 1.0f - ### because SpriteSheetPacker starts y-coord
    // from top while OpenGL y-coord starts from the bottom
    CHECK(sl_ssp.GetSpriteInfo()[0].m_name.compare("red_idle_0001") == 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[0].m_startingPos, 0, 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[0].m_dimensions, 140, 140);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[0].m_texCoordStart, 0, 1.0f - 0);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[0].m_texCoordEnd, 140.0f/1820.0f, 1.0f - 140.0f/1260.0f);

    CHECK(sl_ssp.GetSpriteInfo()[1].m_name.compare("red_idle_0002") == 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[1].m_startingPos, 140, 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[1].m_dimensions, 140, 140);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[1].m_texCoordStart, 140.0f/1820.0f, 1.0f - 0);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[1].m_texCoordEnd, 140.0f/1820.0f + 140.0f/1820.0f,
                                                         1.0f - 140.0f/1260.0f);

    CHECK(sl_ssp.GetSpriteInfo()[9].m_name.compare("red_idle_0010") == 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[9].m_startingPos, 420, 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[9].m_dimensions, 140, 140);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[9].m_texCoordStart, 420.0f/1820.0f, 1.0f - 0);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[9].m_texCoordEnd, 420.0f/1820.0f + 140.0f/1820.0f,
                                                         1.0f - 140.0f/1260.0f);

    CHECK(sl_ssp.GetSpriteInfo()[103].m_name.compare("red_idle_0104") == 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[103].m_startingPos, 700, 1120);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[103].m_texCoordStart, 700.0f/1820.0f, 1.0f - 1120.0f/1260.0f);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[103].m_texCoordEnd, 700.0f/1820.0f + 140.0f/1820.0f,
                                                           1.0f - (1120.0f/1260.0f + 140.0f/1260.0f));
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[103].m_dimensions, 140, 140);

    SpriteLoader_SpriteSheetPacker::const_iterator itr, itrEnd;

    itr = sl_ssp.begin("red_idle");
    itrEnd = sl_ssp.end("red_idle");

    CHECK(itr == sl_ssp.begin());
    CHECK(itr != sl_ssp.end());
    CHECK(itrEnd == sl_ssp.end());
  }

  TEST_CASE("Graphics/media/SpriteLoader/TexturePacker", "")
  {
    SpriteLoader_TexturePacker sl_tp;

    core_io::FileIO_ReadA txtFile(core_io::Path(g_texture_packer_path.c_str()) );

    REQUIRE(txtFile.Open() == ErrorSuccess);

    core_str::String fileContents;
    txtFile.GetContents(fileContents);

    sl_tp.Init(fileContents, gfx_t::Dimension2u(2380, 2040));

    CHECK(sl_tp.GetSpriteInfo().size() == 52);

    CHECK(sl_tp.GetSpriteInfo()[0].m_name.compare("animation_spawn_alpha_000.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[0].m_startingPos, 0, 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[0].m_dimensions, 340, 340);

    CHECK(sl_tp.GetSpriteInfo()[50].m_name.compare("animation_spawn_alpha_050.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[50].m_startingPos, 680, 1700);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[50].m_dimensions, 340, 340);

    CHECK(sl_tp.GetSpriteInfo()[51].m_name.compare("animation_spawn_alpha_051.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[51].m_startingPos, 1700, 1360);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[51].m_dimensions, 340, 340);
  }

  TEST_CASE("Graphics/media/SpriteLoader/TexturePackerMultiple", "")
  {
    SpriteLoader_TexturePacker sl_tp;

    core_io::FileIO_ReadA
      txtFile(core_io::Path(g_texture_packer_multiple_path.c_str()) );

    REQUIRE(txtFile.Open() == ErrorSuccess);

    core_str::String fileContents;
    txtFile.GetContents(fileContents);

    sl_tp.Init(fileContents, gfx_t::Dimension2u(5000, 4000));

    CHECK(sl_tp.GetSpriteInfo().size() == 842);

    CHECK(sl_tp.GetSpriteInfo()[0].m_name.compare("Wake_Happy_01.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[0].m_startingPos, 0, 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[0].m_dimensions, 200, 200);

    CHECK(sl_tp.GetSpriteInfo()[8].m_name.compare("idle_angry1_01.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[8].m_startingPos, 1600, 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[8].m_dimensions, 200, 200);

    CHECK(sl_tp.GetSpriteInfo()[30].m_name.compare("idle_angry2_01.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[30].m_startingPos, 400, 200);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[30].m_dimensions, 200, 200);

    CHECK(sl_tp.GetSpriteInfo()[52].m_name.compare("idle_angry3_01.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[52].m_startingPos, 400, 200);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[52].m_dimensions, 200, 200);

    SpriteLoader_TexturePacker::const_iterator itr, itrEnd;

    itr     = sl_tp.begin("Wake_Happy");
    itrEnd  = sl_tp.end("Wake_Happy");

    CHECK( (itr->m_name.compare(sl_tp.GetSpriteInfo()[0].m_name) == 0) );
    CHECK( itr->m_startingPos == sl_tp.GetSpriteInfo()[0].m_startingPos );
    CHECK( itr->m_dimensions == sl_tp.GetSpriteInfo()[0].m_dimensions);
    CHECK( core::distance(itr, itrEnd) == 8);

    itr     = sl_tp.begin("idle_angry1");
    itrEnd  = sl_tp.end("idle_angry1");

    CHECK( (itr->m_name.compare(sl_tp.GetSpriteInfo()[8].m_name) == 0) );
    CHECK( itr->m_startingPos == sl_tp.GetSpriteInfo()[8].m_startingPos );
    CHECK( itr->m_dimensions == sl_tp.GetSpriteInfo()[8].m_dimensions);
    CHECK( core::distance(itr, itrEnd) == 22);

    itr     = sl_tp.begin("idle_angry2");
    itrEnd  = sl_tp.end("idle_angry2");

    CHECK( (itr->m_name.compare(sl_tp.GetSpriteInfo()[30].m_name) == 0) );
    CHECK( itr->m_startingPos == sl_tp.GetSpriteInfo()[30].m_startingPos );
    CHECK( itr->m_dimensions == sl_tp.GetSpriteInfo()[30].m_dimensions);
    CHECK( core::distance(itr, itrEnd) == 22);
  }
};