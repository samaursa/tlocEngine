#include "tlocTestCommon.h"

#include <tlocGraphics/data_types/tlocVertex.h>

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
    CHECK(sizeof(types::p_vertex_t::VertexPos2f) ==
          sizeof(types::p_vertex_t::VertexPos2f::value_type));
    CHECK(sizeof(types::Vert2fp) == sizeof(types::Vert2fp::position_type));
    CHECK(sizeof(types::Vert3fp) == sizeof(types::Vert3fp::position_type));

    CHECK(sizeof(foo) == 8);

    types::Vert2fp v;
    v.GetPosition();
  }
};