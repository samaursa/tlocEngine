#ifndef _TLOC_GRAPHICS_COMPONENT_SYSTEM_SKYBOX_H_
#define _TLOC_GRAPHICS_COMPONENT_SYSTEM_SKYBOX_H_

#include <tlocGraphics/tlocGraphicsBase.h>

#include <tlocCore/smart_ptr/tloc_smart_ptr.h>
#include <tlocCore/tlocPair.h>

#include <tlocCore/component_system/tlocComponentPoolManager.h>
#include <tlocCore/component_system/tlocComponent.h>
#include <tlocCore/component_system/tlocEntity.h>

#include <tlocGraphics/component_system/tlocComponentType.h>
#include <tlocGraphics/opengl/tlocTextureObject.h>

namespace tloc { namespace graphics { namespace component_system {

  class SkyBoxRenderSystem;

  class SkyBox
    : public core_cs::Component_T<SkyBox, 
                                  core_cs::component_group::k_graphics,
                                  components::k_skybox>
  {
  public:
    friend class SkyBoxRenderSystem;

    typedef SkyBox                                      this_type;
    typedef core_cs::Component_T
      <this_type, k_component_group, k_component_type>  base_type;
    typedef gfx_gl::TextureObjectCubeMap                tex_obj_type;

  public:
    SkyBox(tex_obj_type a_cubeMap);

  private:
    tex_obj_type m_cubeMap;

  public:
    TLOC_DECL_AND_DEF_GETTER_AUTO(GetCubeMap, m_cubeMap);
  };

  //------------------------------------------------------------------------
  // typedefs

  TLOC_TYPEDEF_ALL_SMART_PTRS(SkyBox, skybox);
  TLOC_TYPEDEF_VIRTUAL_STACK_OBJECT(SkyBox, skybox);
  TLOC_TYPEDEF_COMPONENT_POOL(SkyBox, skybox);

};};};

// -----------------------------------------------------------------------
// extern template

TLOC_EXTERN_TEMPLATE_ALL_SMART_PTRS(tloc::gfx_cs::SkyBox);
TLOC_EXTERN_TEMPLATE_VIRTUAL_STACK_OBJECT(tloc::gfx_cs::SkyBox);


#endif