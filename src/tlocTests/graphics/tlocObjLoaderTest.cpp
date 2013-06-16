#include "tlocTestCommon.h"

#include <tlocCore/io/tlocFileIO.h>
#include <tlocGraphics/media/tlocObjLoader.h>

namespace TestingSpriteLoader
{
  using namespace tloc;
  using namespace graphics::media;

  core_str::String
    GetFilePath(const char* a_fileName)
  {
    return GetAssetsPath() + core_str::String(a_fileName);
  }

#define CHECK_VEC3F(vec,x,y,z) CHECK((vec[0]) == (Approx(x)) ); \
                               CHECK((vec[1]) == (Approx(y)) ); \
                               CHECK((vec[2]) == (Approx(z)) );

#define CHECK_VEC2F(vec,x,y) CHECK((vec[0]) == (Approx(x)) ); \
                             CHECK((vec[1]) == (Approx(y)) );

  TEST_CASE("Graphics/media/ObjLoader/cube.obj", "")
  {
    core_io::Path filePath(GetFilePath("models/cube.obj").c_str());
    core_io::FileIO_ReadA txtFile(filePath);

    REQUIRE(txtFile.Open() == ErrorSuccess);

    core_str::String fileContents;
    txtFile.GetContents(fileContents);

    ObjLoader o;
    REQUIRE(o.Init(fileContents) == ErrorSuccess);
    CHECK(o.GetNumPositions() == 8);
    CHECK(o.GetNumNormals() == 6);
    CHECK(o.GetNumTCoords() == 0);

    REQUIRE(o.GetNumGroups() == 1);
    CHECK(o.GetGroup(0).m_name.compare("cube") == 0);
    CHECK(o.GetGroup(0).m_posIndices.size() == 12*3);
    CHECK(o.GetGroup(0).m_normIndices.size() == 12*3);
    CHECK(o.GetGroup(0).m_tcoordIndices.size() == 0);

    math_t::Vec3f32 pos;
    pos = *o.begin_pos();
    CHECK_VEC3F(pos, 0, 0, 0);
    pos = *(o.begin_pos() + 6);
    CHECK_VEC3F(pos, 1, 1, 0);

    ObjLoader::vert_cont_type vertices;
    o.GetUnpacked(vertices, 0);
    CHECK(vertices.size() == 36);

    CHECK_VEC3F(vertices[0].GetPosition(), 0, 0, 0);
    CHECK_VEC3F(vertices[0].GetNormal(), 0, 0, -1);

  }

  TEST_CASE("Graphics/media/ObjLoader/diamond.obj", "")
  {
    core_io::Path filePath(GetFilePath("models/diamond.obj").c_str());
    core_io::FileIO_ReadA txtFile(filePath);

    REQUIRE(txtFile.Open() == ErrorSuccess);

    core_str::String fileContents;
    txtFile.GetContents(fileContents);

    ObjLoader o;
    REQUIRE(o.Init(fileContents) == ErrorSuccess);

    CHECK(o.GetNumPositions() == 6);
    CHECK(o.GetNumNormals() == 0);
    CHECK(o.GetNumTCoords() == 0);

    REQUIRE(o.GetNumGroups() == 1);
    CHECK(o.GetGroup(0).m_name.compare("Object001") == 0);
    CHECK(o.GetGroup(0).m_posIndices.size() == 9*3);
    CHECK(o.GetGroup(0).m_normIndices.size() == 0);
    CHECK(o.GetGroup(0).m_tcoordIndices.size() == 0);

    math_t::Vec3f32 pos;
    pos = *o.begin_pos();
    CHECK_VEC3F(pos, 0, 0, 78.0f);
    pos = *(o.begin_pos() + 4);
    CHECK_VEC3F(pos, -45, 45, 0);
  }

  TEST_CASE("Graphics/media/ObjLoader/violin_case.obj", "")
  {
    core_io::Path filePath(GetFilePath("models/violin_case.obj").c_str());
    core_io::FileIO_ReadA txtFile(filePath);

    REQUIRE(txtFile.Open() == ErrorSuccess);

    core_str::String fileContents;
    txtFile.GetContents(fileContents);

    ObjLoader o;
    REQUIRE(o.Init(fileContents) == ErrorSuccess);
    CHECK(o.GetNumPositions() == 1080);
    CHECK(o.GetNumNormals() == 0);
    CHECK(o.GetNumTCoords() == 0);

    REQUIRE(o.GetNumGroups() == 5);
    // No easy way to know how many faces there are in the file unless the
    // file is opened in Blender and triangulated
    CHECK(o.GetGroup(0).m_posIndices.size() > 944);
    CHECK(o.GetGroup(0).m_normIndices.size() == 0);
    CHECK(o.GetGroup(0).m_tcoordIndices.size() == 0);

    math_t::Vec3f32 pos;
    pos = *o.begin_pos();
    CHECK_VEC3F(pos, 1.277130f, 0.241420f, -0.073923);
    pos = *(o.begin_pos() + 4);
    CHECK_VEC3F(pos, 1.253589f, 0.243404f, -0.046365f);

    // first quad, only line 1096 of obj file
    REQUIRE(o.GetGroup(0).m_posIndices.size() > 944);
    CHECK(o.GetGroup(0).m_posIndices[0] == 1076);
    CHECK(o.GetGroup(0).m_posIndices[1] == 1075);
    CHECK(o.GetGroup(0).m_posIndices[2] == 1080);
    CHECK(o.GetGroup(0).m_posIndices[3] == 1076);
    CHECK(o.GetGroup(0).m_posIndices[4] == 1080);
    CHECK(o.GetGroup(0).m_posIndices[5] == 1079);

    // second quad, only line 1096 of obj file
    CHECK(o.GetGroup(0).m_posIndices[6] == 1072);
    CHECK(o.GetGroup(0).m_posIndices[7] == 1077);
    CHECK(o.GetGroup(0).m_posIndices[8] == 1078);
    CHECK(o.GetGroup(0).m_posIndices[9] == 1072);
    CHECK(o.GetGroup(0).m_posIndices[10] == 1078);
    CHECK(o.GetGroup(0).m_posIndices[11] == 1057);
  }

  void TestTwoCubes(const char* a_fileName)
  {
    core_io::Path filePath(GetFilePath(a_fileName).c_str());
    core_io::FileIO_ReadA txtFile(filePath);

    REQUIRE(txtFile.Open() == ErrorSuccess);

    core_str::String fileContents;
    txtFile.GetContents(fileContents);

    ObjLoader o;
    REQUIRE(o.Init(fileContents) == ErrorSuccess);

    CHECK(o.GetNumPositions() == 16); // two cubes
    CHECK(o.GetNumNormals() == 6); // two cubes sharing same normals
    CHECK(o.GetNumTCoords() == 28);

    REQUIRE(o.GetNumGroups() == 2);
    CHECK(o.GetGroup(0).m_name.compare("Cube.000_Cube.002") == 0);
    CHECK(o.GetGroup(0).m_posIndices.size() == 12*3);
    CHECK(o.GetGroup(0).m_normIndices.size() == 12*3);
    CHECK(o.GetGroup(0).m_tcoordIndices.size() == 12*3);

    CHECK(o.GetGroup(1).m_name.compare("Cube.001") == 0);
    CHECK(o.GetGroup(1).m_posIndices.size() == 12*3);
    CHECK(o.GetGroup(1).m_normIndices.size() == 12*3);
    CHECK(o.GetGroup(1).m_tcoordIndices.size() == 12*3);

    {
      ObjLoader::vert_cont_type vertices;
      o.GetUnpacked(vertices, 0);
      CHECK(vertices.size() == 36);

      CHECK_VEC3F(vertices[0].GetPosition(), -1.0f, 1.0f, -1.018634f);
      CHECK_VEC2F(vertices[0].GetTexCoord(), 0.250044, 0.250043);
      CHECK_VEC3F(vertices[0].GetNormal(), -1, 0, 0);
    }

    {
      ObjLoader::vert_cont_type vertices;
      o.GetUnpacked(vertices, 1);
      CHECK(vertices.size() == 36);

      CHECK_VEC3F(vertices[0].GetPosition(), -1.0f, 1.0f, 3.037524);
      CHECK_VEC2F(vertices[0].GetTexCoord(), 0.250044, 0.250043);
      CHECK_VEC3F(vertices[0].GetNormal(), -1, 0, 0);
    }
  }

  TEST_CASE("Graphics/media/ObjLoader/two_cubes_as_groups.obj", "")
  {
    TestTwoCubes("models/two_cubes_tri_g.obj");
    TestTwoCubes("models/two_cubes_tri_o.obj");
  }

};