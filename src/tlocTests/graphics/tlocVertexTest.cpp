#include "tlocTestCommon.h"

#include <tlocGraphics/types/tlocVertex.h>

namespace TestingGraphicsVertex
{
  using namespace tloc;
  using namespace tloc::graphics;

  struct foo : public types::p_vertex_t::VertexPos2f,
               public EmptyType_T<0>
  {
  };

  TEST_CASE("Graphics/gl/Vertex", "")
  {
    // Since these are tied closely to OpenGL types, we know the exact size
    CHECK(sizeof( types::Vert2fp) == 8 );
    CHECK(sizeof( types::Vert2fpn) == 20);
    CHECK(sizeof( types::Vert2fpnc) == (20 + sizeof(types::Color)) );
    CHECK(sizeof( types::Vert2fpnct) == (28 + sizeof(types::Color)) );
    CHECK(sizeof( types::Vert2fpt) == 16);

    CHECK(sizeof( types::Vert3fp) == 12 );
    CHECK(sizeof( types::Vert3fpn) == 24);
    CHECK(sizeof( types::Vert3fpnc) == (24 + sizeof(types::Color)) );
    CHECK(sizeof( types::Vert3fpnct) == (32 + sizeof(types::Color)) );
    CHECK(sizeof( types::Vert3fpt) == 20);
  }
};