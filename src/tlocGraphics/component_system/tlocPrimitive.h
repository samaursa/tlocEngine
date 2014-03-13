#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_PRIMITIVE_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_PRIMITIVE_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/smart_ptr/tlocVirtualPtr.h>

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
      typedef core_sptr::VirtualPtr<cont_type>                  cont_sptr;

    public:
      ArrayOfStructures();

      void      AddVertex(const vert_type& a_vertex);
      vert_type GetVertex(size_type a_position) const;
      void      ModifyVertex(size_type a_position, const vert_type& a_vertex);
      size_type size() const;
      void      clear();

    private:
      cont_sptr m_vertexes;
    };

    class StructureOfArrays
    {
    public:
      enum { k_component_id = components::mesh};

    public:
      typedef types::Vert3fpnt                                vert_type;
      typedef math_t::Vec3f32                                 pos_type;
      typedef math_t::Vec3f32                                 norm_type;
      typedef math_t::Vec2f32                                 tcoord_type;

      typedef core_conts::Array<pos_type>                     cont_pos_type;
      typedef core_conts::Array<norm_type>                    cont_norm_type;
      typedef core_conts::Array<tcoord_type>                  cont_tcoord_type;

      typedef core_sptr::VirtualPtr<cont_pos_type>            cont_pos_ptr;
      typedef core_sptr::VirtualPtr<cont_norm_type>           cont_norm_ptr;
      typedef core_sptr::VirtualPtr<cont_tcoord_type>         cont_tcoord_ptr;

      typedef tl_size                                         size_type;

    public:
      StructureOfArrays();

      void      AddVertex(const vert_type& a_vertex);
      vert_type GetVertex(size_type a_position) const;
      void      ModifyVertex(size_type a_position, const vert_type& a_vertex);
      size_type size() const;
      void      clear();

      TLOC_DECL_AND_DEF_GETTER(cont_pos_ptr, GetPositions, m_positions);
      TLOC_DECL_AND_DEF_GETTER(cont_norm_ptr, GetNormals, m_normals);
      TLOC_DECL_AND_DEF_GETTER(cont_tcoord_ptr, GetTCoords, m_tcoords);

    private:
      cont_pos_ptr     m_positions;
      cont_norm_ptr    m_normals;
      cont_tcoord_ptr  m_tcoords;
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