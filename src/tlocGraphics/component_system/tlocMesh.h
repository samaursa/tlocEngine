#ifndef TLOC_MESH_H
#define TLOC_MESH_H

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/types/tlocStrongType.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/data_types/tlocVertex.h>
#include <tlocGraphics/data_types/tlocRectangle.h>

namespace tloc { namespace graphics { namespace component_system {

  class IPrimitive : public core::component_system::Component
  {
  protected:
    typedef core::component_system::Component base_type;

    typedef types::Vert3fPNC                    vert_type;
    typedef core::tl_array<vert_type>::type     cont_type;
    typedef cont_type::iterator                 iterator;
    typedef cont_type::const_iterator           const_iterator;

  public:
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(cont_type, GetVertexes, m_vertexes);

  protected:
    IPrimitive(components::value_type a_id);
    TLOC_DECL_AND_DEF_GETTER_DIRECT(cont_type, DoGetVertexes, m_vertexes);

  protected:
    cont_type m_vertexes;
  };

  class Mesh : public IPrimitive
  {
  public:
    Mesh();
  };

  class Quad : public IPrimitive
  {
  public:
    typedef Quad                   this_type;
    typedef IPrimitive             base_type;
    typedef types::Rectf           rect_type;

    // Order chosen basedon winding order (n,s,e,w = north, south...)
    typedef base_type::vert_type                     vert_type;
    typedef core::types::StrongType_T<vert_type, 0>  vert_se;
    typedef core::types::StrongType_T<vert_type, 1>  vert_ne;
    typedef core::types::StrongType_T<vert_type, 2>  vert_nw;
    typedef core::types::StrongType_T<vert_type, 0>  vert_sw;

  public:
    Quad();
    Quad(const rect_type& a_vector);

  };

};};};

#endif