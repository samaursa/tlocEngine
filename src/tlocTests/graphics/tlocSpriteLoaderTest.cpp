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

    sl_ssp.Init(fileContents, gfx_t::Dimension2u(core_ds::MakeTuple(1820, 1260)) );

    CHECK(sl_ssp.GetSpriteInfo().size() == 104);

    // we will check the first couple of lines and the last couple of lines
    // NOTE: y-coords are 1.0f - ### because SpriteSheetPacker starts y-coord
    // from top while OpenGL y-coord starts from the bottom
    CHECK(sl_ssp.GetSpriteInfo()[0].GetName().compare("red_idle_0001") == 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[0].GetStartingPos(), 0, 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[0].GetDimensions(), 140, 140);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[0].GetTexCoordStart(), 0, 1.0f - 0);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[0].GetTexCoordEnd(), 140.0f/1820.0f, 1.0f - 140.0f/1260.0f);

    CHECK(sl_ssp.GetSpriteInfo()[1].GetName().compare("red_idle_0002") == 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[1].GetStartingPos(), 140, 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[1].GetDimensions(), 140, 140);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[1].GetTexCoordStart(), 140.0f/1820.0f, 1.0f - 0);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[1].GetTexCoordEnd(), 140.0f/1820.0f + 140.0f/1820.0f,
                                                         1.0f - 140.0f/1260.0f);

    CHECK(sl_ssp.GetSpriteInfo()[9].GetName().compare("red_idle_0010") == 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[9].GetStartingPos(), 420, 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[9].GetDimensions(), 140, 140);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[9].GetTexCoordStart(), 420.0f/1820.0f, 1.0f - 0);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[9].GetTexCoordEnd(), 420.0f/1820.0f + 140.0f/1820.0f,
                                                         1.0f - 140.0f/1260.0f);

    CHECK(sl_ssp.GetSpriteInfo()[103].GetName().compare("red_idle_0104") == 0);
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[103].GetStartingPos(), 700, 1120);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[103].GetTexCoordStart(), 700.0f/1820.0f, 1.0f - 1120.0f/1260.0f);
    CHECK_VEC2F(sl_ssp.GetSpriteInfo()[103].GetTexCoordEnd(), 700.0f/1820.0f + 140.0f/1820.0f,
                                                           1.0f - (1120.0f/1260.0f + 140.0f/1260.0f));
    CHECK_TUP2S(sl_ssp.GetSpriteInfo()[103].GetDimensions(), 140, 140);

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

    sl_tp.Init(fileContents, gfx_t::Dimension2u(core_ds::MakeTuple(2380, 2040)) );

    CHECK(sl_tp.GetSpriteInfo().size() == 52);

    CHECK(sl_tp.GetSpriteInfo()[0].GetName().compare("animation_spawn_alpha_000.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[0].GetStartingPos(), 0, 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[0].GetDimensions(), 340, 340);

    CHECK(sl_tp.GetSpriteInfo()[50].GetName().compare("animation_spawn_alpha_050.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[50].GetStartingPos(), 680, 1700);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[50].GetDimensions(), 340, 340);

    CHECK(sl_tp.GetSpriteInfo()[51].GetName().compare("animation_spawn_alpha_051.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[51].GetStartingPos(), 1700, 1360);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[51].GetDimensions(), 340, 340);
  }

  TEST_CASE("Graphics/media/SpriteLoader/TexturePackerMultiple", "")
  {
    SpriteLoader_TexturePacker sl_tp;

    core_io::FileIO_ReadA
      txtFile(core_io::Path(g_texture_packer_multiple_path.c_str()) );

    REQUIRE(txtFile.Open() == ErrorSuccess);

    core_str::String fileContents;
    txtFile.GetContents(fileContents);

    sl_tp.Init(fileContents, gfx_t::Dimension2u(core_ds::MakeTuple(5000, 4000)) );

    CHECK(sl_tp.GetSpriteInfo().size() == 842);

    CHECK(sl_tp.GetSpriteInfo()[0].GetName().compare("Wake_Happy_01.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[0].GetStartingPos(), 0, 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[0].GetDimensions(), 200, 200);

    CHECK(sl_tp.GetSpriteInfo()[8].GetName().compare("idle_angry1_01.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[8].GetStartingPos(), 1600, 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[8].GetDimensions(), 200, 200);

    CHECK(sl_tp.GetSpriteInfo()[30].GetName().compare("idle_angry2_01.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[30].GetStartingPos(), 400, 200);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[30].GetDimensions(), 200, 200);

    CHECK(sl_tp.GetSpriteInfo()[52].GetName().compare("idle_angry3_01.png") == 0);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[52].GetStartingPos(), 400, 200);
    CHECK_TUP2S(sl_tp.GetSpriteInfo()[52].GetDimensions(), 200, 200);

    SpriteLoader_TexturePacker::const_iterator itr, itrEnd;

    itr     = sl_tp.begin("Wake_Happy");
    itrEnd  = sl_tp.end("Wake_Happy");

    CHECK( (itr->GetName().compare(sl_tp.GetSpriteInfo()[0].GetName()) == 0) );
    CHECK( itr->GetStartingPos() == sl_tp.GetSpriteInfo()[0].GetStartingPos() );
    CHECK( itr->GetDimensions() == sl_tp.GetSpriteInfo()[0].GetDimensions());
    CHECK( core::distance(itr, itrEnd) == 8);

    itr     = sl_tp.begin("idle_angry1");
    itrEnd  = sl_tp.end("idle_angry1");

    CHECK( (itr->GetName().compare(sl_tp.GetSpriteInfo()[8].GetName()) == 0) );
    CHECK( itr->GetStartingPos() == sl_tp.GetSpriteInfo()[8].GetStartingPos() );
    CHECK( itr->GetDimensions() == sl_tp.GetSpriteInfo()[8].GetDimensions());
    CHECK( core::distance(itr, itrEnd) == 22);

    itr     = sl_tp.begin("idle_angry2");
    itrEnd  = sl_tp.end("idle_angry2");

    CHECK( (itr->GetName().compare(sl_tp.GetSpriteInfo()[30].GetName()) == 0) );
    CHECK( itr->GetStartingPos() == sl_tp.GetSpriteInfo()[30].GetStartingPos() );
    CHECK( itr->GetDimensions() == sl_tp.GetSpriteInfo()[30].GetDimensions());
    CHECK( core::distance(itr, itrEnd) == 22);
  }

  TEST_CASE("Graphics/media/SpriteLoader/algorithms", "")
  {
    SpriteLoader_TexturePacker sl_tp;

    core_io::FileIO_ReadA
      txtFile(core_io::Path(g_texture_packer_multiple_path.c_str()) );

    REQUIRE(txtFile.Open() == ErrorSuccess);

    core_str::String fileContents;
    txtFile.GetContents(fileContents);

    sl_tp.Init(fileContents, gfx_t::Dimension2u(core_ds::MakeTuple(5000, 4000)) );

    CHECK(sl_tp.GetSpriteInfo().size() == 842);

    SpriteLoader_TexturePacker::iterator itr;

    itr = core::find_if(sl_tp.begin(), sl_tp.end(),
                        algos::compare::sprite_info::MakeName("Wake_Happy_01.png"));

    CHECK(itr->GetName().compare("Wake_Happy_01.png") == 0);
    CHECK_TUP2S(itr->GetStartingPos(), 0, 0);
    CHECK_TUP2S(itr->GetDimensions(), 200, 200);

    itr = core::find_if(sl_tp.begin(), sl_tp.end(),
                        algos::compare::sprite_info::NameBegins("idle"));

    CHECK(itr->GetName().compare("idle_angry1_01.png") == 0);
    CHECK_TUP2S(itr->GetStartingPos(), 1600, 0);
    CHECK_TUP2S(itr->GetDimensions(), 200, 200);
  }
};