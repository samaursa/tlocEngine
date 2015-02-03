#pragma once

#include <tlocGraphics/tlocGraphicsBase.h>
#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // Raypick

  class Raypick
    : public core_cs::Component_T<Raypick, 
                                  core_cs::component_group::k_graphics,
                                  components::k_raypick>
  {
  public:
    typedef Raypick                                   this_type;
    typedef core_cs::Component_T<this_type,
      core_cs::component_group::k_graphics,
      components::k_raypick>                          base_type;

  public:
    Raypick();

    TLOC_DECL_AND_DEF_GETTER(bool, GetIsDistanceChecked, m_distanceChecked);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(bool, SetDistanceChecked, m_distanceChecked);

  private:
    bool m_distanceChecked;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(Raypick, raypick);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(Raypick, raypick);
  TLOC_TYPEDEF_COMPONENT_POOL(Raypick, raypick);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::Raypick);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_cs::Raypick);