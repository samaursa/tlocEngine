#ifndef _TLOC_PREFAB_GRAPHICS_CUBOID_H_
#define _TLOC_PREFAB_GRAPHICS_CUBOID_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocMesh.h>

#include <tlocMath/types/tlocCuboid.h>

namespace tloc { namespace prefab { namespace graphics {

  class Cuboid
    : public Prefab_TI<Cuboid, gfx_cs::Mesh>
  {
  public:
    typedef Cuboid                                      this_type;
    typedef Prefab_TI<this_type, component_type>        base_type;
    typedef math_t::Cuboidf32                           cuboid_type;

  public:
    Cuboid(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr Construct();

    entity_ptr    Create();
    void          Add(entity_ptr a_ent);

    TLOC_DECL_PARAM_VAR(bool, TexCoords, m_texCoords);
    TLOC_DECL_PARAM_VAR(bool, Normals, m_normals);
    TLOC_DECL_PARAM_VAR(cuboid_type, Dimensions, m_cuboid);

  };

};};};

#endif