#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_PRIMITIVE_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_PRIMITIVE_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/containers/tlocContainers.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/types/tlocVertex.h>

namespace tloc { namespace graphics { namespace component_system {

  class IPrimitive : public core::component_system::Component_T<IPrimitive>
  {
  protected:
    typedef core::component_system::Component_T<IPrimitive>   base_type;

    typedef types::Vert3fpnc                              vert_type;
    typedef core::containers::tl_array<vert_type>::type   cont_type;
    typedef cont_type::iterator                           iterator;
    typedef cont_type::const_iterator                     const_iterator;

  public:
    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(cont_type, GetVertexes, m_vertexes);

  protected:
    IPrimitive(components::value_type a_id);
    TLOC_DECL_AND_DEF_GETTER_DIRECT(cont_type, DoGetVertexes, m_vertexes);

  protected:
    cont_type m_vertexes;
  };

};};};

#endif