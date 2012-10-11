#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_H_

#include <tlocGraphics/component_system/tlocPrimitive.h>

#include <tlocCore/containers/tlocContainers.h>
#include <tlocCore/types/tlocStrongType.h>

#include <tlocGraphics/data_types/tlocVertex.h>
#include <tlocGraphics/data_types/tlocRectangle.h>

namespace tloc { namespace graphics { namespace component_system {

  class Quad : public IPrimitive
  {
  public:
    typedef Quad                   this_type;
    typedef IPrimitive             base_type;
    typedef types::Rectf           rect_type;

    // Order chosen based on winding order and n,s,e,w = north, south...
    typedef base_type::vert_type                     vert_type;
    typedef core::types::StrongType_T<vert_type, 0>  vert_se;
    typedef core::types::StrongType_T<vert_type, 1>  vert_ne;
    typedef core::types::StrongType_T<vert_type, 2>  vert_nw;
    typedef core::types::StrongType_T<vert_type, 3>  vert_sw;

    template <typename T_VertexPos>
    vert_type const & GetVertex() const
    { return GetVertexes()[T_VertexPos::k_index]; }

  public:
    Quad();
    Quad(const rect_type& a_rect);

    void Set(const rect_type& a_rect);
  };

};};};

#endif