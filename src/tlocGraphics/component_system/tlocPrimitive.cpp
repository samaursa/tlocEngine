#include "tlocPrimitive.h"

#include <tlocCore/tlocAssert.h>

namespace tloc { namespace graphics { namespace component_system {

  // -----------------------------------------------------------------------
  // Primitive_T

  Primitive_I::
    Primitive_I()
    : m_vertexType(0)
    , m_numVertices(0)
  { }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  bool
    Primitive_I::
    empty() const
  { return m_vertices.IsEmpty(); }

  // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

  void
    Primitive_I::
    clear()
  { m_vertices.Reset(); m_vertexType = 0; m_numVertices = 0; }

  // ///////////////////////////////////////////////////////////////////////
  // explicit instantiations

  typedef Primitive_I                                   this_type;
  typedef gfx_t::Vert3fp                                vert_type;
  typedef core_conts::Array<vert_type>                  cont_type;
  typedef core_conts::Array<vert_type>::iterator        itr_type;
  typedef core_conts::Array<vert_type>::const_iterator  const_itr_type;
  typedef core_conts::Array<vert_type>::size_type       size_type;

  template this_type&       Primitive_I::AddVertex(const vert_type&);
  template vert_type        Primitive_I::GetVertex(size_type) const;
  template this_type&       Primitive_I::ModifyVertex(size_type, const vert_type&);
  template const cont_type& Primitive_I::GetVertices() const;

  template itr_type       Primitive_I::begin<vert_type>();
  template itr_type       Primitive_I::end<vert_type>();

  template const_itr_type Primitive_I::begin<vert_type>() const;
  template const_itr_type Primitive_I::end<vert_type>() const;

};};};