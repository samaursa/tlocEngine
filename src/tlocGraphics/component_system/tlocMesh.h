#ifndef TLOC_MESH_H
#define TLOC_MESH_H

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocGraphics/data_types/tlocVertex.h>
#include <tlocCore/containers/tlocContainers.h>

namespace tloc { namespace graphics { namespace component_system {

  class Mesh : public core::component_system::Component
  {
  public:
    typedef core::component_system::Component base_type;

    typedef types::Vertex<true, true, true>     vertex_type;
    typedef core::tl_array<vertex_type>::type   container_type;
    typedef container_type::iterator            iterator;
    typedef container_type::const_iterator      const_iterator;

    Mesh();

    TLOC_DECL_AND_DEF_GETTERS_DIRECT(container_type, GetVertexes, m_vertexes);

  private:
    container_type  m_vertexes;
  };

};};};

#endif