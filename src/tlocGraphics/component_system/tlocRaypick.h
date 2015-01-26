#pragma once

#include <tlocGraphics/tlocGraphicsBase.h>
#include <tlocGraphics/component_system/tlocComponentType.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>

namespace tloc { namespace graphics { namespace component_system {

  // ///////////////////////////////////////////////////////////////////////
  // Raypick2D

  class Raypick2D
    : public core_cs::Component_T<Raypick2D, 
                                  core_cs::component_group::k_graphics,
                                  components::k_raypick_2d>
  {
  public:
    typedef Raypick2D                                 this_type;
    typedef core_cs::Component_T<this_type,
      core_cs::component_group::k_graphics,
      components::k_raypick_2d>                       base_type;

  public:
    Raypick2D();

    TLOC_DECL_AND_DEF_GETTER(bool, GetIsAlwaysRaypicked, m_noDistanceCheck);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(bool, SetIsAlwaysRaypicked, m_noDistanceCheck);

  private:
    bool m_noDistanceCheck;

  };

  // ///////////////////////////////////////////////////////////////////////
  // Raypick3D

  class Raypick3D
    : public core_cs::Component_T<Raypick3D, 
                                  core_cs::component_group::k_graphics,
                                  components::k_raypick_3d>
  {
  public:
    typedef Raypick3D                                 this_type;
    typedef core_cs::Component_T<this_type,
      core_cs::component_group::k_graphics,
      components::k_raypick_3d>                       base_type;

  public:
    Raypick3D();

    TLOC_DECL_AND_DEF_GETTER(bool, GetIsNoDistanceCheck, m_noDistanceCheck);
    TLOC_DECL_AND_DEF_SETTER_BY_VALUE_CHAIN(bool, SetNoDistanceCheck, m_noDistanceCheck);

  private:
    bool m_noDistanceCheck;
  };

};};};