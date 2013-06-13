#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_PRIMITIVE_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_PRIMITIVE_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/containers/tlocContainers.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/types/tlocVertex.h>

namespace tloc { namespace graphics { namespace component_system {

  template <typename T_VertexType = types::Vert3fpn>
  class Primitive_TI
  {
  protected:
    typedef T_VertexType                                    vert_type;
    typedef typename core_conts::tl_array<vert_type>::type  cont_type;
    typedef typename cont_type::iterator                    iterator;
    typedef typename cont_type::const_iterator              const_iterator;
    typedef tl_size                                         size_type;

  public:
    TLOC_DECL_AND_DEF_GETTER(iterator, begin, m_vertexes.begin());
    TLOC_DECL_AND_DEF_GETTER(iterator, end, m_vertexes.end());

    void AddVertex(const vert_type& a_vertex);
    void ModifyVertex(size_type a_position, const vert_type& a_vertex);

  protected:
    Primitive_TI();
    TLOC_DECL_AND_DEF_GETTER_DIRECT(cont_type, DoGetVertexes, m_vertexes);

  protected:
    cont_type m_vertexes;
  };

  //------------------------------------------------------------------------
  // template definitions

  template <typename T_ComponentType>
  Primitive_TI<T_ComponentType>::
    Primitive_TI()
  { }

  template <typename T_ComponentType>
  void
    Primitive_TI<T_ComponentType>::
    AddVertex(const vert_type& a_vertex)
  {
    m_vertexes.push_back(a_vertex);
  }

  template <typename T_ComponentType>
  void
    Primitive_TI<T_ComponentType>::
    ModifyVertex(size_type a_position, const vert_type& a_vertex)
  {
    m_vertexes[a_position] = a_vertex;
  }

};};};

#endif