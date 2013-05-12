#include "tlocTestCommon.h"

#include <tlocGraphics/component_system/tlocTextureCoords.h>

namespace TestingTextureCoords
{
  using namespace tloc;
  using namespace tloc::graphics::component_system;

  typedef gfx_cs::TextureCoords::vec_type   vec_type;

#define CHECK_VEC2F(vec,x,y) CHECK((vec[0]) == (Approx(x)) ); \
                             CHECK((vec[1]) == (Approx(y)) );

  TEST_CASE("Graphics/component_system/TextureCoords", "")
  {
    typedef gfx_cs::TextureCoords::set_index set_index;

    gfx_cs::texture_coords_sptr texCoords(new gfx_cs::TextureCoords());
    CHECK(texCoords->GetNumSets() == 0);
    CHECK(texCoords->GetCurrentSet() == 0);

    texCoords->AddCoord(vec_type(1.0f, 1.0f));
    texCoords->AddCoord(vec_type(0.0f, 1.0f));
    texCoords->AddCoord(vec_type(1.0f, 0.0f));
    texCoords->AddCoord(vec_type(0.0f, 0.0f));

    CHECK(texCoords->GetNumSets() == 1);

    TextureCoords::cont_type texArray;
    texArray.push_back(vec_type(-1.0f, -1.0f));
    texArray.push_back(vec_type( 0.0f, -1.0f));
    texArray.push_back(vec_type(-1.0f,  0.0f));
    texArray.push_back(vec_type( 0.0f,  0.0f));

    texCoords->ModifyCoords(texArray, set_index(1));

    CHECK(texCoords->GetNumSets() == 2);

    CHECK_VEC2F(texCoords->GetCoord(0, set_index(0)), 1.0f, 1.0f);
    CHECK_VEC2F(texCoords->GetCoord(1, set_index(0)), 0.0f, 1.0f);
    CHECK_VEC2F(texCoords->GetCoord(2, set_index(0)), 1.0f, 0.0f);
    CHECK_VEC2F(texCoords->GetCoord(3, set_index(0)), 0.0f, 0.0f);

    for (tl_size i = 0; i < 4; ++i)
    {
      CHECK_VEC2F(texCoords->GetCoord(i, set_index(1)),
                  texArray[i][0], texArray[i][1]);
    }
  }
};
