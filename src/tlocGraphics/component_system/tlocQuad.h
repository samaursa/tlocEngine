#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace graphics { namespace component_system {

  class Quad
    : public tloc::core::component_system::Component_T<Quad, components::quad>
  {
  public:
    typedef Quad                                      this_type;
    typedef Component_T<this_type, components::quad>  base_type;
    typedef f32                                       real_type;
    typedef math::types::Rectangle_T<real_type>       rect_type;

  public:
    Quad();
    Quad(const rect_type& a_rect);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(rect_type, GetRectangleRef, m_rect);
    TLOC_DECL_AND_DEF_COMPONENT_SETTER(rect_type, SetRectangle, m_rect);

  private:
    rect_type m_rect;
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_SHARED_PTR(Quad, quad);

  typedef core::component_system::
    ComponentPool_TI<quad_sptr>                 QuadPool;

};};};

#endif