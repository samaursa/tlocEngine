#pragma once

#include <tlocGraphics/tlocGraphicsBase.h>
#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocMath/types/tlocRectangle.h>
#include <tlocMath/types/tlocCuboid.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // BoundingBox2D

  class BoundingBox2D
    : public core_cs::Component_T<BoundingBox2D,
                                  core_cs::component_group::k_graphics,
                                  components::k_bounding_box_2d>
  {
  public:
    typedef BoundingBox2D                     this_type;
    typedef core_cs::Component_T<this_type,
      core_cs::component_group::k_graphics,
      components::k_bounding_box_2d>          base_type;
    typedef math_t::Rectf_c                   bounds_type;

  public:
    BoundingBox2D();
    BoundingBox2D(const bounds_type& a_newBounds);

    TLOC_DECL_AND_DEF_GETTER(bounds_type, Get, m_boundingBox);

  private:
    bounds_type m_boundingBox;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(BoundingBox2D, bounding_box_2d);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(BoundingBox2D, bounding_box_2d);
  TLOC_TYPEDEF_COMPONENT_POOL(BoundingBox2D, bounding_box_2d);

  // ///////////////////////////////////////////////////////////////////////
  // BoundingBox3D

  class BoundingBox3D
    : public core_cs::Component_T<BoundingBox3D,
                                  core_cs::component_group::k_graphics,
                                  components::k_bounding_box_3d>
  {
  public:
    typedef BoundingBox3D                     this_type;
    typedef core_cs::Component_T<this_type,
      core_cs::component_group::k_graphics,
      components::k_bounding_box_3d>          base_type;
    typedef math_t::Cuboidf                   bounds_type;

  public:
    BoundingBox3D();
    BoundingBox3D(const bounds_type& a_newBounds);

    TLOC_DECL_AND_DEF_GETTER(bounds_type, Get, m_boundingBox);

  private:
    bounds_type m_boundingBox;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(BoundingBox3D, bounding_box_3d);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(BoundingBox3D, bounding_box_3d);
  TLOC_TYPEDEF_COMPONENT_POOL(BoundingBox3D, bounding_box_3d);
  
};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::BoundingBox2D);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_cs::BoundingBox2D);

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::BoundingBox3D);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_cs::BoundingBox3D);
