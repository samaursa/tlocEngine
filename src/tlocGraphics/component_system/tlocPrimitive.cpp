#include "tlocPrimitive.h"

namespace tloc { namespace graphics { namespace component_system {

  namespace p_primitive {

    // -----------------------------------------------------------------------
    // ArrayOfStructures

    ArrayOfStructures::
      ArrayOfStructures()
      : m_vertexes(new cont_type())
    { }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      ArrayOfStructures::
      AddVertex(const vert_type& a_vertex)
    {
      m_vertexes->push_back(a_vertex);
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    ArrayOfStructures::vert_type
      ArrayOfStructures::
      GetVertex(size_type a_position) const
    {
      return (*m_vertexes)[a_position];
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      ArrayOfStructures::
      ModifyVertex(size_type a_position, const vert_type& a_vertex)
    {
      (*m_vertexes)[a_position] = a_vertex;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    ArrayOfStructures::size_type
      ArrayOfStructures::
      size() const
    {
      return m_vertexes->size();
    }

    // -----------------------------------------------------------------------
    // StructureOfArrays

    StructureOfArrays::
      StructureOfArrays()
      : m_positions(new cont_pos_type())
      , m_normals(new cont_norm_type())
      , m_tcoords(new cont_tcoord_type())
    { }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      StructureOfArrays::
      AddVertex(const vert_type& a_vertex)
    {
      pos_type     pos(a_vertex.GetPosition());
      norm_type    norm(a_vertex.GetNormal());
      tcoord_type  tcoord(a_vertex.GetTexCoord());

      m_positions->push_back(pos);
      m_normals->push_back(norm);
      m_tcoords->push_back(tcoord);
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    StructureOfArrays::vert_type
      StructureOfArrays::
      GetVertex(size_type a_position) const
    {
      vert_type vertex;
      vertex.SetPosition( (*m_positions)[a_position]);
      vertex.SetNormal( (*m_normals)[a_position]);
      vertex.SetTexCoord( (*m_tcoords)[a_position]);

      return vertex;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    void
      StructureOfArrays::
      ModifyVertex(size_type a_position, const vert_type& a_vertex)
    {
      pos_type     pos(a_vertex.GetPosition());
      norm_type    norm(a_vertex.GetNormal());
      tcoord_type  tcoord(a_vertex.GetTexCoord());

      (*m_positions)[a_position] = pos;
      (*m_normals)[a_position]   = norm;
      (*m_tcoords)[a_position]   = tcoord;
    }

    // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

    StructureOfArrays::size_type
      StructureOfArrays::
      size() const
    {
      TLOC_ASSERT(m_positions->size() == m_normals->size() &&
                  m_positions->size() == m_tcoords->size(),
                  "Strucure of arrays size mismatch. Check logic of AddVertex "
                  "and ModifyVertex methods");
      return m_positions->size();
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