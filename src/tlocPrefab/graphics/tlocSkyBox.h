#ifndef _TLOC_PREFAB_GRAPHICS_SKYBOX_H_
#define _TLOC_PREFAB_GRAPHICS_SKYBOX_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocSkyBox.h>
#include <tlocGraphics/opengl/tlocTextureObject.h>

namespace tloc { namespace prefab { namespace graphics {

  class SkyBox
    : public Prefab_TI<SkyBox, gfx_cs::SkyBox>
  {
  public:
    typedef SkyBox                                      this_type;
    typedef Prefab_TI<this_type, component_type>        base_type;

    typedef gfx_gl::TextureObjectCubeMap                tex_obj_type;

  public:
    SkyBox(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr   Construct(tex_obj_type a_cubeMap);

    entity_ptr      Create(tex_obj_type a_cubeMap);
    void            Add   (entity_ptr a_ent, 
                           tex_obj_type a_cubeMap);
  };

};};};

#endif