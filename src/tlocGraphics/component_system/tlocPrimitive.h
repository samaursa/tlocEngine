#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_PRIMITIVE_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_PRIMITIVE_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/containers/tlocContainers.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/types/tlocVertex.h>

namespace tloc { namespace graphics { namespace component_system {

  namespace p_primitive
  {
    class ArrayOfStructures
    {
    public:
      enum { k_component_id = components::mesh_interleaved };

    public:
      typedef types::Vert3fpnt                                  vert_type;
      typedef core_conts::Array<vert_type>                      cont_type;
      typedef tl_size                                           size_type;

    public:
      void      AddVertex(const vert_type& a_vertex);
      vert_type GetVertex(size_type a_position) const;
      void      ModifyVertex(size_type a_position, const vert_type& a_vertex);
      size_type size() const;

    private:
      cont_type m_vertexes;
    };

    class StructureOfArrays
    {
    public:
      enum { k_component_id = components::mesh};

    public:
      typedef types::Vert3fpnt                                vert_type;
      typedef types::Vert3fp                                  vert_pos_type;
      typedef types::p_vertex_t::VertexNorm3f                 vert_norm_type;
      typedef types::p_vertex_t::TexCoord                     vert_tcoord_type;

      typedef core_conts::Array<vert_pos_type>                cont_pos_type;
      typedef core_conts::Array<vert_norm_type>               cont_norm_type;
      typedef core_conts::Array<vert_tcoord_type>             cont_tcoord_type;

      typedef tl_size                                         size_type;

    public:
      void      AddVertex(const vert_type& a_vertex);
      vert_type GetVertex(size_type a_position) const;
      void      ModifyVertex(size_type a_position, const vert_type& a_vertex);
      size_type size() const;

    private:
      cont_pos_type     m_positions;
      cont_norm_type    m_normals;
      cont_tcoord_type  m_tcoords;
    };
  };

  template <typename T_VertexStoragePolicy = p_primitive::StructureOfArrays>
  class Primitive_TI
    : public T_VertexStoragePolicy
  {
  public:
    typedef types::Vert3fpnt                                vert_type;
    typedef typename core_conts::tl_array<vert_type>::type  cont_type;
    typedef typename cont_type::iterator                    iterator;
    typedef typename cont_type::const_iterator              const_iterator;
    typedef tl_size                                         size_type;

    typedef T_VertexStoragePolicy                           base_type;

  public:
    using base_type::AddVertex;
    using base_type::GetVertex;
    using base_type::ModifyVertex;
    using base_type::size;

  protected:
    Primitive_TI();
  };

};};};

#endif