#ifndef _TLOC_PREFAB_GRAPHICS_SCENE_NODE_H_
#define _TLOC_PREFAB_GRAPHICS_SCENE_NODE_H_

#include <tlocPrefab/tlocPrefabBase.h>

#include <tlocCore/component_system/tlocEntity.h>
#include <tlocCore/component_system/tlocEntityManager.h>
#include <tlocCore/component_system/tlocComponentPoolManager.h>

#include <tlocGraphics/component_system/tlocSceneNode.h>

namespace tloc { namespace prefab { namespace graphics {

  class SceneNode
    : public Prefab_TI<gfx_cs::SceneNode>
  {
  public:
    typedef Prefab_TI<component_type>     base_type;
    typedef SceneNode                     this_type;
    typedef gfx_cs::SceneNode             scene_node_type;
    typedef gfx_cs::scene_node_vptr       scene_node_ptr;

  public:
    SceneNode(entity_mgr_ptr a_entMgr, comp_pool_mgr_ptr a_poolMgr);

    component_ptr   Construct(entity_ptr a_nodeEntity) const;

    entity_ptr      Create() const;
    void            Add(entity_ptr a_ent) const;

    TLOC_DECL_PARAM_VAR(scene_node_ptr, Parent, m_parent);
  };

};};};

#endif