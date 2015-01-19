#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_BOUNDING_BOX_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_BOUNDING_BOX_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>

namespace tloc { namespace graphics { namespace component_system {

  class BoundingBoxSystem
    : public core_cs::EntityProcessingSystem
  {
  public:
    typedef core_cs::EntityProcessingSystem                     base_type;
    typedef BoundingBoxSystem                                   this_type;

  public:
    BoundingBoxSystem(event_manager_ptr, entity_manager_ptr);

    virtual error_type Pre_Initialize();
    virtual error_type InitializeEntity(entity_ptr);
    virtual error_type ShutdownEntity(entity_ptr);

    virtual void Pre_ProcessActiveEntities(f64 );
    virtual void ProcessEntity(entity_ptr, f64 a_deltaT);
    virtual void Post_ProcessActiveEntities(f64 );

    virtual void OnComponentDisable(const core_cs::EntityComponentEvent&) {}
    virtual void OnComponentEnable(const core_cs::EntityComponentEvent&) {}

  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(BoundingBoxSystem, bounding_box_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(BoundingBoxSystem, bounding_box_system);

};};};

// -----------------------------------------------------------------------
// extern templates

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::BoundingBoxSystem);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::BoundingBoxSystem);

#endif