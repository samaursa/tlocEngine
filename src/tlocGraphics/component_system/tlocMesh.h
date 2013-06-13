#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_MESH_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_MESH_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocGraphics/component_system/tlocPrimitive.h>

namespace tloc { namespace graphics { namespace component_system {

  template <typename T_VertexType>
  class Mesh_T
    : public Primitive_TI<T_VertexType>
    , public core_cs::Component_T<Mesh_T<T_VertexType>, components::mesh>
  {
  public:
    typedef T_VertexType                              vert_type;
    typedef Primitive_TI<vert_type>                   base_primitive_type;
    typedef Mesh_T<vert_type>                         this_type;
    typedef Component_T<this_type, components::mesh>  base_type;
  };

  //------------------------------------------------------------------------
  // typedef

  typedef Mesh_T<types::Vert3fp>          Mesh_Pos;
  typedef Mesh_T<types::Vert3fpt>         Mesh_PosTex;
  typedef Mesh_T<types::Vert3fpn>         Mesh_PosNorm;
  typedef Mesh_T<types::Vert3fpnc>        Mesh_PosNormCol;
  typedef Mesh_T<types::Vert3fpnct>       Mesh_PosNormColTex;

};};};

#endif