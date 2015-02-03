#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_CAMERA_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_CAMERA_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>

#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>

namespace tloc { namespace graphics { namespace component_system {

  class CameraSystem
    : public core_cs::EntityProcessingSystem
  {
  public:
    typedef core_cs::EntityProcessingSystem                 base_type;
    typedef CameraSystem                                    this_type;

  public:
    CameraSystem(event_manager_ptr, entity_manager_ptr);

    virtual error_type InitializeEntity(entity_ptr) override;
    virtual void       ProcessEntity(entity_ptr, f64 a_deltaT) override;
  };

  // -----------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(CameraSystem, camera_system);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(CameraSystem, camera_system);
  
};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::CameraSystem);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::CameraSystem);

#endif
