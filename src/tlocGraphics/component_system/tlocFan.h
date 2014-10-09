#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_CIRCLE_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_CIRCLE_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/component_system/tlocRenderable_TI.h>

#include <tlocMath/types/tlocCircle.h>

namespace tloc { namespace graphics { namespace component_system {

  class Fan
    : public Renderable_TI<Fan, components::fan>
  {
  public:
    typedef Fan                                       this_type;
    typedef Renderable_TI<this_type, components::fan> base_type;
    typedef tl_size                                   size_type;
    typedef f32                                       real_type;
    typedef math::types::Circle_T<real_type>          ellipse_type;

    typedef core::types::StrongType_T<size_type, 0>   sides;

  public:
    Fan();
    explicit Fan(const ellipse_type& a_ellipse, sides a_sides = sides(30) );

    TLOC_DECL_AND_DEF_GETTER_CONST_DIRECT(ellipse_type, GetEllipseRef, m_ellipse);
    TLOC_DECL_AND_DEF_COMPONENT_SETTER(ellipse_type, SetEllipse, m_ellipse);

    TLOC_DECL_AND_DEF_GETTER(size_type, GetNumSides, m_sides);
    TLOC_DECL_AND_DEF_COMPONENT_SETTER(size_type, SetNumSides, m_sides);

  private:
    ellipse_type m_ellipse;
    size_type    m_sides;
  };

  TLOC_TYPEDEF_ALL_SMART_PTRS(Fan, fan);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Fan, fan);
  TLOC_TYPEDEF_COMPONENT_POOL(Fan, fan);

};};};

#endif