#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_QUAD_H_

#include <tlocCore/smart_ptr/tlocSharedPtr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocMath/types/tlocRectangle.h>

namespace tloc { namespace graphics { namespace component_system {

  class Quad : public tloc::core::component_system::Component_T<Quad>
  {
  public:
    typedef Quad                                this_type;
    typedef Component_T<this_type>              base_type;
    typedef f32                                 real_type;
    typedef math::types::Rectangle<real_type>   rect_type;

  public:
    Quad();
    Quad(const rect_type& a_rect);

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(rect_type, GetRectangleRef, m_rect);
    TLOC_DECL_AND_DEF_SETTER(rect_type, SetRectangle, m_rect);

  private:
    rect_type m_rect;
  };

  typedef core::smart_ptr::SharedPtr<Quad>    QuadPtr;
  typedef core::component_system::
    ComponentPool_TI<QuadPtr>                 QuadPool;

};};};

#endif