#include "tlocTestCommon.h"

#include <tlocGraphics/types/tlocVertex.h>
#include <tlocMath/types/tlocVector3.h>

namespace TestingGraphicsVertex
{
  using namespace tloc;
  using namespace tloc::graphics;

  struct foo : public types::p_vertex_t::VertexPos2f,
               public EmptyType_T<0>
  {
  };

#define CHECK_VEC3F(vec,x,y,z) CHECK((vec[0]) == (Approx(x)) ); \
                               CHECK((vec[1]) == (Approx(y)) ); \
                               CHECK((vec[2]) == (Approx(z)) );

#define CHECK_VEC2F(vec,x,y) CHECK((vec[0]) == (Approx(x)) ); \
                             CHECK((vec[1]) == (Approx(y)) );

  TEST_CASE("Graphics/gl/Vertex", "")
  {
    // Since these are tied closely to OpenGL types, we know the exact size
    CHECK(sizeof( types::Vert2fp) == 8 );
    CHECK(sizeof( types::Vert2fpn) == 20);
    CHECK(sizeof( types::Vert2fpnc) == (20 + sizeof(math_t::Vec4f32)) );
    CHECK(sizeof( types::Vert2fpnct) == (28 + sizeof(math_t::Vec4f32)) );
    CHECK(sizeof( types::Vert2fpt) == 16);

    CHECK(sizeof( types::Vert3fp) == 12 );
    CHECK(sizeof( types::Vert3fpn) == 24);
    CHECK(sizeof( types::Vert3fpnc) == (24 + sizeof(math_t::Vec4f32)) );
    CHECK(sizeof( types::Vert3fpnct) == (32 + sizeof(math_t::Vec4f32)) );
    CHECK(sizeof( types::Vert3fpt) == 20);

    types::Vert3fpnct v;
    v.SetPosition(math_t::Vec3f32(1, 2, 3));
    v.SetNormal(math_t::Vec3f32(0, 1, 0));
    v.SetTexCoord(math_t::Vec2f32(1, 0));

    CHECK_VEC3F(v.GetPosition(), 1, 2, 3);
    CHECK_VEC3F(v.GetNormal(), 0, 1, 0);
    CHECK_VEC2F(v.GetTexCoord(), 1, 0);
  }
};