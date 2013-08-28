#ifndef _TLOC_PREFAB_GRAPHICS_MESH_H_
#define _TLOC_PREFAB_GRAPHICS_MESH_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocMesh.h>

namespace tloc { namespace prefab { namespace graphics {

  class Mesh
    : public Prefab_I
  {
  public:
    typedef Mesh                                          this_type;
    typedef core_conts::Array<gfx_cs::Mesh::vert_type>    vert_cont_type;

  public:
    Mesh(core_cs::EntityManager*  a_entMgr,
         core_cs::ComponentPoolManager* a_poolMgr)
         : Prefab_I(a_entMgr, a_poolMgr)
    { }

    entity_type* Create(const vert_cont_type& a_vertices);
    void         Add(entity_type* a_ent, const vert_cont_type& a_vertices);

  };

};};};

#endif