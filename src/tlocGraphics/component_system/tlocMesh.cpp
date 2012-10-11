#include "tlocMesh.h"

namespace tloc { namespace graphics { namespace component_system {

  //------------------------------------------------------------------------
  // Primitive

  IPrimitive::IPrimitive(components::value_type a_id) : base_type(a_id)
  { }

  //------------------------------------------------------------------------
  // Mesh

  Mesh::Mesh() : IPrimitive(component_system::components::mesh)
  { }

  //------------------------------------------------------------------------
  // Quad

  Quad::Quad() : IPrimitive(component_system::components::quad)
  { }

  Quad::Quad(const rect_type& a_vector)
    : IPrimitive(component_system::components::quad)
  {
    typedef base_type::cont_type::value_type::position_value_type   vec_type;

    base_type::cont_type& verts = DoGetVertexes();
    verts.resize(4);

    vec_type vertSE(a_vector.GetCoord<rect_type::bottom>(),
                    0,
                    a_vector.GetCoord<rect_type::right>());
    vec_type vertNE(a_vector.GetCoord<rect_type::top>(),
                    0,
                    a_vector.GetCoord<rect_type::right>());
    vec_type vertNW(a_vector.GetCoord<rect_type::top>(),
                    0,
                    a_vector.GetCoord<rect_type::left>());
    vec_type vertSW(a_vector.GetCoord<rect_type::bottom>(),
                    0,
                    a_vector.GetCoord<rect_type::left>());

    verts[vert_se::k_index].SetPosition(vertSE);
    verts[vert_ne::k_index].SetPosition(vertNE);
    verts[vert_nw::k_index].SetPosition(vertNW);
    verts[vert_sw::k_index].SetPosition(vertSW);
  }

};};};