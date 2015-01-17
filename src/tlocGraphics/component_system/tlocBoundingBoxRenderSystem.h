#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_BOUNDING_BOX_RENDER_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_BOUNDING_BOX_RENDER_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocECS.h>
#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocGraphics/component_system/tlocMeshRenderSystem.h>

namespace tloc { namespace graphics { namespace component_sytem {

  class BoundingBoxRenderSystem
    : public core_cs::EntityProcessingSystem
  {
  public:
    typedef core_cs::EntityProcessingSystem                     base_type;
    typedef BoundingBoxRenderSystem                             this_type;

  public:

  private:


  };

};};};

#endif