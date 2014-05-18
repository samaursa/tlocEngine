#ifndef _TLOC_PREFAB_GRAPHICS_MESH_H_
#define _TLOC_PREFAB_GRAPHICS_MESH_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocMesh.h>

namespace tloc { namespace prefab { namespace graphics {

  class Mesh
    : public Prefab_TI<gfx_cs::Mesh>
  {
  public:
    typedef Prefab_TI<component_type>                     base_type;
    typedef Mesh                                          this_type;
    typedef core_conts::Array<gfx_cs::Mesh::vert_type>    vert_cont_type;

  public:
    Mesh(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr Construct(const vert_cont_type& a_vertices) const;

    entity_ptr   Create(const vert_cont_type& a_vertices) const;
    void         Add(entity_ptr a_ent, const vert_cont_type& a_vertices) const;

    TLOC_DECL_PARAM_VAR(bool, TexCoords, m_texCoords);
    TLOC_DECL_PARAM_VAR(bool, Normals, m_normals);

  };

};};};

#endif