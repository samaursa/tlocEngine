#include "tlocPrimitive.h"

namespace tloc { namespace graphics { namespace component_system {

  namespace p_primitive {

    // -----------------------------------------------------------------------
    // ArrayOfStructures

    void
      ArrayOfStructures::
      AddVertex(const vert_type& a_vertex)
    {
      m_vertexes.push_back(a_vertex);
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    ArrayOfStructures::vert_type
      ArrayOfStructures::
      GetVertex(size_type a_position) const
    {
      return m_vertexes[a_position];
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      ArrayOfStructures::
      ModifyVertex(size_type a_position, const vert_type& a_vertex)
    {
      m_vertexes[a_position] = a_vertex;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    ArrayOfStructures::size_type
      ArrayOfStructures::
      size() const
    {
      return m_vertexes.size();
    }

    // -----------------------------------------------------------------------
    // StructureOfArrays

    void
      StructureOfArrays::
      AddVertex(const vert_type& a_vertex)
    {
      vert_pos_type     pos; pos.SetPosition(a_vertex.GetPosition());
      vert_norm_type    norm; norm.SetNormal(a_vertex.GetNormal());
      vert_tcoord_type  tcoord; tcoord.SetTexCoord(a_vertex.GetTexCoord());

      m_positions.push_back(pos);
      m_normals.push_back(norm);
      m_tcoords.push_back(tcoord);
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    StructureOfArrays::vert_type
      StructureOfArrays::
      GetVertex(size_type a_position) const
    {
      vert_type vertex;
      vertex.SetPosition(m_positions[a_position].GetPosition());
      vertex.SetNormal(m_normals[a_position].GetNormal());
      vertex.SetTexCoord(m_tcoords[a_position].GetTexCoord());

      return vertex;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      StructureOfArrays::
      ModifyVertex(size_type a_position, const vert_type& a_vertex)
    {
      vert_pos_type     pos; pos.SetPosition(a_vertex.GetPosition());
      vert_norm_type    norm; norm.SetNormal(a_vertex.GetNormal());
      vert_tcoord_type  tcoord; tcoord.SetTexCoord(a_vertex.GetTexCoord());

      m_positions[a_position] = pos;
      m_normals[a_position]   = norm;
      m_tcoords[a_position]   = tcoord;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    StructureOfArrays::size_type
      StructureOfArrays::
      size() const
    {
      TLOC_ASSERT(m_positions.size() == m_normals.size() &&
                  m_positions.size() == m_tcoords.size(),
                  "Strucure of arrays size mismatch. Check logic of AddVertex "
                  "and ModifyVertex methods");
      return m_positions.size();
    }

  };

  // -----------------------------------------------------------------------
  // Primitive_TI

#define PRIMITIVE_TEMPS   typename T_VertexStoragePolicy
#define PRIMITIVE_PARAMS  T_VertexStoragePolicy
#define PRIMITIVE_TYPE    typename Primitive_TI<PRIMITIVE_PARAMS>

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  template <PRIMITIVE_TEMPS>
  Primitive_TI<PRIMITIVE_PARAMS>::
    Primitive_TI()
  { }

  // -----------------------------------------------------------------------
  // explicit instantiations

  template class Primitive_TI<p_primitive::ArrayOfStructures>;
  template class Primitive_TI<p_primitive::StructureOfArrays>;

};};};