#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace graphics { namespace component_system {

  class Quad
    : public core_cs::Component_T<Quad, components::quad>
  {
  public:
    typedef Quad                                      this_type;
    typedef Component_T<this_type, components::quad>  base_type;
    typedef f32                                       real_type;
    typedef math::types::Rectangle_T<real_type>       rect_type;

  public:
    Quad();
    explicit Quad(const rect_type& a_rect);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(rect_type, GetRectangleRef, m_rect);
    TLOC_DECL_AND_DEF_COMPONENT_SETTER(rect_type, SetRectangle, m_rect);

  private:
    rect_type m_rect;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(Quad, quad);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Quad, quad);
  TLOC_TYPEDEF_COMPONENT_POOL(Quad, quad);

};};};

#endif