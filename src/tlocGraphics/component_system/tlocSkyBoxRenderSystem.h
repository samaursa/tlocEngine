#pragma once
#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_SKYBOX_SYSTEM_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_SKYBOX_SYSTEM_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/component_system/tlocECS.h>

#include <tlocCore/component_system/tlocEntityProcessingSystem.h>
#include <tlocCore/component_system/tlocEventManager.h>
#include <tlocCore/component_system/tlocEntityManager.h>

#include <tlocGraphics/component_system/tlocMeshRenderSystem.h>

namespace tloc {
  namespace graphics {
    namespace component_system {

      class SkyBoxRenderSystem
        : public core_cs::EntityProcessingSystem
      {
      public:
        typedef core_cs::EntityProcessingSystem                 base_type;
        typedef SkyBoxRenderSystem                              this_type;
        typedef core_cs::ecs_uptr                               ecs_ptr;
        typedef mesh_render_system_vptr                         mesh_sys_ptr;
        typedef gfx_rend::renderer_depth32_sptr                 renderer_ptr;

      public:
        SkyBoxRenderSystem(event_manager_ptr, entity_manager_ptr);

        virtual error_type InitializeEntity(entity_ptr) override;

        virtual void       ProcessEntity(entity_ptr, f64 a_deltaT) override;
        virtual void       Post_ProcessActiveEntities(f64 a_delttaT) override;

        void               SetCamera(const_entity_ptr a_cameraEntity);
        void               SetRenderer(renderer_ptr a_renderer);

      private:
        ecs_ptr            m_scene;
        mesh_sys_ptr       m_meshSys;
        renderer_ptr       m_renderer;
      };

      // -----------------------------------------------------------------------
      // typedefs

      TLOC_TYPEDEF_ALL_SMART_PTRS(SkyBoxRenderSystem, skybox_render_system);
      TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT_NO_COPY_NO_DEF_CTOR(SkyBoxRenderSystem, skybox_render_system);

    };
  };
};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::SkyBoxRenderSystem);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT_NO_COPY_CTOR_NO_DEF_CTOR(tloc::gfx_cs::SkyBoxRenderSystem);

#endif
